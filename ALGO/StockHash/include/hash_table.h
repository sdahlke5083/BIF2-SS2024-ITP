// hash_table.h
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 1303 // Prime number for better distribution
#include <time.h>
#include <ctype.h>

// Structure to hold a single day's stock price data
typedef struct {
    struct tm date;
    double open;
    double high;
    double low;
    double close;
    double adjClose;
    long volume;
} StockPrice;

// Stock structure
typedef struct {
    char symbol[6]; // Stock symbol
    char name[256]; // Full name of the company
    char wkn[12]; // Wertpapierkennnummer (WKN)
    StockPrice prices[30]; // Last 30 days of price data
    int valid; // Flag to check if entry is valid
} Stock;

// Node structure for the hash table (chaining method for collision resolution)
typedef struct StockNode {
    Stock stock;
    int status; // 0 = empty, 1 = occupied, 2 = deleted
} StockNode;

// Hash table structure
typedef struct {
    int shortNameHashTableSize; // Size of the hash table
    StockNode* shortNameHashTable[TABLE_SIZE]; // Array of StockNode pointers
} MyHashTables;

// Function declarations
void initMyHashTables(MyHashTables* ht);
int hash(const char* key);
int quadraticProbing(StockNode* const ht[], const char* key, int* index);
void insertStock(MyHashTables* ht, Stock stock);
void insertStockLoad(MyHashTables *ht, StockNode *stockNode, int index);
Stock *searchStock(const MyHashTables *ht, const char *key);
void deleteStock(MyHashTables* ht, const char* key);
void plotStock(const Stock* stock);
void freeMyHashTables(MyHashTables* ht);

// Optional functions for debugging
void printMyHashTables(const MyHashTables* ht);

#endif // HASH_TABLE_H
