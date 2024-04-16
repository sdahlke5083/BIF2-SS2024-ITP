// hash_table.c
#include "hash_table.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Initialize the hash table
void initMyHashTables(MyHashTables* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->shortNameHashTable[i] = NULL;
        ht->shortNameHashTableSize = 0;
    }
}

// A simple hash function called the djb2 hash
int hash(const char* key) {
    unsigned long hash = 5381; // Prime number for better distribution
    int c; // Character to hash

    // Iterate over each character in the key
    while ((c = *key++)) {
        // c to Upper for case insensitivity
        hash = ((hash << 5) + hash) + toupper(c); // hash * 33 + c
    }
    // Return the hash value modulo the table size to ensure it fits within the table
    return hash % TABLE_SIZE;
}

// Handle collision using quadratic probing
int quadraticProbing( StockNode* const ht[], const char* key, int* index) {
    int hashValue = hash(key);
    int i = 0;
    int newIndex = hashValue;

    while (ht[newIndex] != NULL && ht[newIndex]->status == 1 && strcmp(ht[newIndex]->stock.symbol, key) != 0)
    {
        i++;
        newIndex = (hashValue + i * i) % TABLE_SIZE;
        if (i > TABLE_SIZE) { // We've looped through the table
            return -1; // Table full
        }
    }
    *index = newIndex;
    return ht[newIndex] != NULL ? ht[newIndex]->status : 0;
}

// Insert a stock into the hash table
void insertStock(MyHashTables* ht, Stock stock) {
    int index = 0;
    int quadraticProbingResult = quadraticProbing(ht->shortNameHashTable, stock.symbol, &index);
    if (quadraticProbingResult != 1) { // Check if the stock already exists
        if(quadraticProbingResult == 2){ // Check if is just marked as deleted
            ht->shortNameHashTable[index]->status = 1; // Mark as occupied
            return;
        }
        
        // add the stock to the hash table
        ht->shortNameHashTable[index] = (StockNode*)malloc(sizeof(StockNode));
        // Check if memory allocation was successful
        if (ht->shortNameHashTable[index] == NULL) {
            printf("Memory allocation failed. Could not add stock.\n");
            return;
        }
        // Copy the stock data
        strcpy(ht->shortNameHashTable[index]->stock.name, stock.name);
        strcpy(ht->shortNameHashTable[index]->stock.symbol, stock.symbol);
        strcpy(ht->shortNameHashTable[index]->stock.wkn, stock.wkn);
        ht->shortNameHashTable[index]->stock.valid = 1; // Mark as valid
        ht->shortNameHashTable[index]->status = 1; // Mark as occupied
        ht->shortNameHashTableSize++; // Increment the size
    }
}

void insertStockLoad(MyHashTables* ht, StockNode* stockNode, int index){
    ht->shortNameHashTable[index] = stockNode;
    ht->shortNameHashTableSize++;
    #ifdef DEBUG
        // print loaded info
        printf("inserted stock: %s - %s\n", ht->shortNameHashTable[index]->stock.symbol, ht->shortNameHashTable[index]->stock.name);
        const char *m = stockNode->stock.symbol;
        printf("check id: %i\n", hash(m));
    #endif
}

// Search for a stock in the hash table
Stock* searchStock(const MyHashTables* ht, const char* symbol) {
    int index = 0;

    // if stock is found, return the stock
    if (quadraticProbing(ht->shortNameHashTable, symbol, &index) == 1){
        return &ht->shortNameHashTable[index]->stock;
    }
    // else stock not found or deleted or table full

    return NULL; // Stock not found
}

// Delete a stock from the hash table
void deleteStock(MyHashTables* ht, const char* symbol) {
    int index = 0;

    if(quadraticProbing(ht->shortNameHashTable, symbol, &index) == 1){
        ht->shortNameHashTable[index]->status = 2; // Mark as deleted
        ht->shortNameHashTableSize--;              // Decrement the size
        printf("Stock %s deleted successfully.\n", symbol);
        return;
    }

    printf("Stock %s not found.\n", symbol);
}

// plot the stock data
void plotStock(const Stock* stock) {
    /*
    ASCII Boxplot Conceptual Sketch for Stock Data Visualization

    Overview:
    This ASCII art representation is intended to visualize stock data over a period of 30 days.
    The plot dynamically scales based on the range of stock prices (min to max) and displays
    the closing price for each day.

    Example:

    Value (Min (┴), Max(┬), Adj. Close(┼))
    200 |    ┬
        | ┬  |           ┬     ┬
    150 | |  |  ┬     ┬  |     ┼  ┬
        | ┼  ┼  ┼     ┼  ┼     ┴  ┼  ┬
    100 | |  ┴  |     ┴  |        ┴  ┴  ┬
        | ┴     ┴        ┴              ┴
     50 |____________________________________
          01 02 03 04 05 06 07 08 09 10 11 12
        Days
    */

    // Calculate the minimum and maximum closing prices
    double minPrice = stock->prices[0].low;
    double maxPrice = stock->prices[0].high;
    for (int i = 1; i < 30; i++)
    {
        if (stock->prices[i].open > 0)
        {
            if (stock->prices[i].low < minPrice)
            {
                minPrice = stock->prices[i].low;
            }
            if (stock->prices[i].high > maxPrice)
            {
                maxPrice = stock->prices[i].high;
            }
        }
    }

    // Calculate the range of prices
    double priceRange = maxPrice - minPrice;
    // Calculate scale factor for the plot
    double scaleFactor = priceRange / 20;

    // Calculate the number of rows and columns for the plot
    int numRows = (int)(priceRange / scaleFactor + 1);
    int numCols = 30;

    // Create a 2D array to store the plot data
    char plot[numRows][numCols];

    // Initialize the plot array with spaces
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            plot[i][j] = ' ';
        }
    }

    // Plot the closing prices
    for (int i = 0; i < 30; i++)
    {
        if (stock->prices[i].open <= 0)
            continue;
        int row = (int)((maxPrice - stock->prices[i].low) / scaleFactor);
        int col = i;

        // Plot | for the range of prices (-- because low is at the higher index and high is at the lower index of the array)
        for (int r = row; r > (int)((maxPrice - stock->prices[i].high) / scaleFactor); r--)
            plot[r][col] = '|';

        // add symbols for low, high and adjClose
        row = (int)((maxPrice - stock->prices[i].low) / scaleFactor);
        plot[row][col] = '-';
        row = (int)((maxPrice - stock->prices[i].high) / scaleFactor);
        plot[row][col] = '+';
        row = (int)((maxPrice - stock->prices[i].adjClose) / scaleFactor);
        plot[row][col] = '*';
    }

    // Print the plot
    printf("Stock Data Visualization: %s (%s)\n", stock->name, stock->symbol);
    printf("\n Value (Min[-], Max[+], Adj. Close[*])\n");
    for (int i = 0; i < numRows; i++)
    {
        double price = maxPrice - (i);
        printf("  %3.0f |", price);
        for (int j = 0; j < numCols; j++)
        {
            if (stock->prices[j].open <= 0)
                continue;
            printf(" %c ", plot[i][j]);
        }
        printf("\n");
    }
    printf("  Day: ");
    for (int i = 0; i < numCols; i++)
    {
        if (stock->prices[i].date.tm_mday <= 0)
            continue;
        printf("%02d ", stock->prices[i].date.tm_mday);
    }
    printf("\n  Mon: ");
    for (int i = 0; i < numCols; i++)
    {
        if (stock->prices[i].date.tm_mday <= 0)
            continue;
        printf("%02d ", stock->prices[i].date.tm_mon + 1);
    }

    printf("\n\n");
}

// free the memory allocated for the hash table
void freeMyHashTables(MyHashTables* ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->shortNameHashTable[i] != NULL) {
            free(ht->shortNameHashTable[i]);
        }
    }
}


// functions for debugging
void printMyHashTables(const MyHashTables* ht) {
    if(ht->shortNameHashTableSize == 0){
        printf("No stocks in the hash table.\n");
        return;
    }
    printf("Stocks in the hash table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->shortNameHashTable[i] != NULL && ht->shortNameHashTable[i]->status == 1) {
            printf("%i: %s (%s)\n", i, ht->shortNameHashTable[i]->stock.name, ht->shortNameHashTable[i]->stock.symbol);
            if(ht->shortNameHashTable[i]->stock.prices[0].open != 0){
                for(int j = 0; j < 30; j++){
                    if(ht->shortNameHashTable[i]->stock.prices[j].open == 0)
                        break;
                    char time[12];
                    strftime(time, sizeof(time), "%d.%m.%Y", &(ht->shortNameHashTable[i]->stock.prices[j].date));
                    printf("\t %s: %f\n", time, ht->shortNameHashTable[i]->stock.prices[j].open);
                }
            }
        }
    }
    printf("\n");
}

