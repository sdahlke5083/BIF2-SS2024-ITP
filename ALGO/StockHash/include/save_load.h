// save_load.h
#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H
#include <direct.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "hash_table.h"

void saveMyHashTables(const MyHashTables *ht, char *filePath);
void loadMyHashTables(MyHashTables* ht, char* filePath);
void saveMyHashTablesDefault(const MyHashTables* ht);
void loadMyHashTablesDefault(MyHashTables* ht);
void create_directory_if_not_exists(const char *dir_path);


#endif // SAVE_LOAD_H
