// import_data.h
#ifndef IMPORT_DATA_H
#define IMPORT_DATA_H

// system includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
// my includes
#include "hash_table.h" // Include the hash table definition

// Function to import stock data from a CSV file
void importStockData(MyHashTables* ht, char* filePath, char* symbol);
void parseLine(MyHashTables *ht, char *line, char *symbol);
struct tm convert_date(char* date);
int isWithinLast30Days(struct tm date);
int isNewerThanExistingData(Stock* st, struct tm date);
int removeOldData(Stock* st, struct tm date);

#endif // import_data_H
