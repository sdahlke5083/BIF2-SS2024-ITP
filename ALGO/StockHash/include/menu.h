// menu.h
#ifndef MENU_H
#define MENU_H
// system includes
#include <stdio.h>
#include <io.h> // for File access
// my includes
#include "hash_table.h"
#include "import_data.h"
#include "save_load.h"

void displayMenu();
void processMenuOption(int option, MyHashTables* ht);

void addStock(MyHashTables* ht);
void deleteStockUI(MyHashTables* ht);
void searchStockUI(const MyHashTables* ht);
void importStockDataUI(MyHashTables* ht);
void plotStockPricesUI(const MyHashTables *ht);
void saveHashTablesUI(const MyHashTables *ht);
void loadHashTablesUI(MyHashTables *ht);

#endif // MENU_H
