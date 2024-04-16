// save_load.c
#include "save_load.h"
char *defaultSavePath = "saves";
char *defaultSaveFile = "mysave.stockhash";

void saveMyHashTablesDefault(const MyHashTables *ht)
{
    saveMyHashTables(ht, defaultSavePath);
}

void loadMyHashTablesDefault(MyHashTables *ht)
{
    loadMyHashTables(ht, defaultSavePath);
}

void saveMyHashTables(const MyHashTables *ht, char *filePath)
{
    // concat file path with default save file name
    char *fileName = malloc(strlen(filePath) + strlen(defaultSaveFile) + 3);
    strcpy(fileName, filePath);
    strcat(fileName, "/");
    strcat(fileName, defaultSaveFile);

    create_directory_if_not_exists(filePath);

    FILE *file = fopen(fileName, "w+");
    if (!file) {
        printf("Failed to open or create file for writing\n");
        return;
    }

    #ifdef DEBUG
    printf("Saving to file: %s\n", fileName);
    #endif

    // save to file as json useing cJSON
    cJSON* myHts = cJSON_CreateObject();
    cJSON* stockTableShortName = cJSON_CreateObject();
    //cJSON* stockTableLongName = cJSON_CreateObject();

    // iterate through the hash table and save each stock
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (ht->shortNameHashTable[i] != NULL) {
            cJSON* stock = cJSON_CreateObject();
            cJSON_AddNumberToObject(stock, "hashedIndex", i);
            cJSON_AddStringToObject(stock, "symbol", ht->shortNameHashTable[i]->stock.symbol);
            cJSON_AddStringToObject(stock, "name", ht->shortNameHashTable[i]->stock.name);
            cJSON_AddStringToObject(stock, "wkn", ht->shortNameHashTable[i]->stock.wkn);

            cJSON* prices = cJSON_CreateArray();
            for (int j = 0; j < 30; j++) {
                cJSON* price = cJSON_CreateObject();
                cJSON_AddNumberToObject(price, "open", ht->shortNameHashTable[i]->stock.prices[j].open);
                cJSON_AddNumberToObject(price, "high", ht->shortNameHashTable[i]->stock.prices[j].high);
                cJSON_AddNumberToObject(price, "low", ht->shortNameHashTable[i]->stock.prices[j].low);
                cJSON_AddNumberToObject(price, "close", ht->shortNameHashTable[i]->stock.prices[j].close);
                cJSON_AddNumberToObject(price, "adjClose", ht->shortNameHashTable[i]->stock.prices[j].adjClose);
                cJSON_AddNumberToObject(price, "volume", ht->shortNameHashTable[i]->stock.prices[j].volume);
                cJSON* date = cJSON_CreateObject();
                cJSON_AddNumberToObject(date, "tm_sec", ht->shortNameHashTable[i]->stock.prices[j].date.tm_sec);
                cJSON_AddNumberToObject(date, "tm_min", ht->shortNameHashTable[i]->stock.prices[j].date.tm_min);
                cJSON_AddNumberToObject(date, "tm_hour", ht->shortNameHashTable[i]->stock.prices[j].date.tm_hour);
                cJSON_AddNumberToObject(date, "tm_mday", ht->shortNameHashTable[i]->stock.prices[j].date.tm_mday);
                cJSON_AddNumberToObject(date, "tm_mon", ht->shortNameHashTable[i]->stock.prices[j].date.tm_mon);
                cJSON_AddNumberToObject(date, "tm_year", ht->shortNameHashTable[i]->stock.prices[j].date.tm_year);
                cJSON_AddItemToObject(price, "date", date);
                
                cJSON_AddItemToArray(prices, price);
            }
            cJSON_AddItemToObject(stock, "prices", prices);

            cJSON_AddItemToObject(stockTableShortName, ht->shortNameHashTable[i]->stock.symbol, stock);
            //cJSON_AddItemToObject(stockTableLongName, ht->shortNameHashTable[i]->stock.name, stock);
        }
    }

    cJSON_AddItemToObject(myHts, "shortNameHashTable", stockTableShortName);
    cJSON_AddNumberToObject(myHts, "shortNameHashTableSize", ht->shortNameHashTableSize);
    //cJSON_AddItemToObject(myHts, "longNameHashTable", stockTableLongName);

    // write to file
    char *jsonString = cJSON_Print(myHts);
    if (jsonString) {
        fputs(jsonString, file);
        free(jsonString);
    } else {
        printf("Failed to convert cJSON to string\n");
    }
    cJSON_Delete(myHts);

    fclose(file);
    free(fileName);
}

void loadMyHashTables(MyHashTables* ht, char* filePath) {
    // concat file path with default save file name
    char *fileName = malloc(strlen(filePath) + strlen(defaultSaveFile) + 3);
    strcpy(fileName, filePath);
    strcat(fileName, "/");
    strcat(fileName, defaultSaveFile);

    FILE* file = fopen(fileName, "r");
    if (!file) {
        printf("Failed to open file for reading\n");
        return;
    }

    #ifdef DEBUG
    printf("Loading from file: %s\n", filePath);
    #endif

    // read file as json using cJSON
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(fileSize + 1);
    if (!buffer) {
        printf("Failed to allocate memory for file buffer\n");
        fclose(file);
        return;
    }

    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';

    cJSON* myHts = cJSON_Parse(buffer);
    if (!myHts) {
        printf("Failed to parse cJSON from file\n");
        free(buffer);
        fclose(file);
        free(fileName);
        return;
    }

    cJSON* stockTableShortName = cJSON_GetObjectItem(myHts, "shortNameHashTable");
    //cJSON* stockTableLongName = cJSON_GetObjectItem(myHts, "longNameHashTable");

    // clear the hash table
    freeMyHashTables(ht);
    initMyHashTables(ht);

    // iterate through the json object and load each stock
    cJSON* stock;
    cJSON_ArrayForEach(stock, stockTableShortName) {
        int hashedIndex = cJSON_GetObjectItem(stock, "hashedIndex")->valueint;
        cJSON* symbol = cJSON_GetObjectItem(stock, "symbol");
        cJSON* name = cJSON_GetObjectItem(stock, "name");
        cJSON* wkn = cJSON_GetObjectItem(stock, "wkn");

        cJSON* prices = cJSON_GetObjectItem(stock, "prices");
        cJSON* price;
        int i = 0;

        StockNode* newNode = (StockNode*)malloc(sizeof(StockNode));
        strcpy(newNode->stock.symbol, symbol->valuestring);
        strcpy(newNode->stock.name, name->valuestring);
        strcpy(newNode->stock.wkn, wkn->valuestring);
        cJSON_ArrayForEach(price, prices) {
            cJSON* open = cJSON_GetObjectItem(price, "open");
            cJSON* high = cJSON_GetObjectItem(price, "high");
            cJSON* low = cJSON_GetObjectItem(price, "low");
            cJSON* close = cJSON_GetObjectItem(price, "close");
            cJSON* adjClose = cJSON_GetObjectItem(price, "adjClose");
            cJSON* volume = cJSON_GetObjectItem(price, "volume");
            cJSON* date = cJSON_GetObjectItem(price, "date");

            newNode->stock.prices[i].open = open->valuedouble;
            newNode->stock.prices[i].high = high->valuedouble;
            newNode->stock.prices[i].low = low->valuedouble;
            newNode->stock.prices[i].close = close->valuedouble;
            newNode->stock.prices[i].adjClose = adjClose->valuedouble;
            newNode->stock.prices[i].volume = volume->valueint;
            // date struct
            newNode->stock.prices[i].date.tm_sec = cJSON_GetObjectItem(date, "tm_sec")->valueint;
            newNode->stock.prices[i].date.tm_min = cJSON_GetObjectItem(date, "tm_min")->valueint;
            newNode->stock.prices[i].date.tm_hour = cJSON_GetObjectItem(date, "tm_hour")->valueint;
            newNode->stock.prices[i].date.tm_mday = cJSON_GetObjectItem(date, "tm_mday")->valueint;
            newNode->stock.prices[i].date.tm_mon = cJSON_GetObjectItem(date, "tm_mon")->valueint;
            newNode->stock.prices[i].date.tm_year = cJSON_GetObjectItem(date, "tm_year")->valueint;

            i++;
        }
        newNode->status = 1;
        insertStockLoad(ht, newNode, hashedIndex);
        #ifdef DEBUG
        // print newNode info
        printf("Loaded Stock: %s - %s in %i\n", newNode->stock.symbol, newNode->stock.name, hashedIndex);
        #endif
    }

    if(ht->shortNameHashTableSize != cJSON_GetObjectItem(myHts, "shortNameHashTableSize")->valueint) {
        printf("File loaded but with Error:\n");
        printf("Hash table size mismatch between SaveFile and imported Data.\n");
    }else{
        printf("File loaded successfully.\n");
    }

    free(buffer);
    fclose(file);
    free(fileName);
}

void create_directory_if_not_exists(const char *dir_path)
{
    if (_mkdir(dir_path) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Failed to create directory");
        }
    }
}