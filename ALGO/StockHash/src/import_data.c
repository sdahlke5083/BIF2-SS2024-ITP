// import_data.c
#include "import_data.h"

void importStockData(MyHashTables* ht, char* filePath, char* symbol) {
    
    #ifdef DEBUG
    printf("Importing stock data from file: %s\n", filePath);
    #endif

    FILE *file = fopen(filePath, "r");

    if (!file) {
        perror("Failed find file:");
        return;
    }

    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        //skip header of the csv file
        if (strstr(line, "Date") != NULL)
        {
            continue;
        }
        parseLine(ht, line, symbol);
    }

    fclose(file);
}

// Helper function to parse a line from the CSV file
void parseLine(MyHashTables *ht, char *line, char *symbol)
{
    Stock* st = searchStock(ht, symbol);
    if (st == NULL)
    {
        perror("Stock not found in hash table\n");
        return;
    }
    char *token;
    int column = 0;
    int day = -1;

    // CSV format: Date,Open,High,Low,Close,Adj Close,Volume
    token = strtok(line, ",");
    while (token != NULL && day < 30 && column < 7)
    {
        struct tm date = {0};
        switch (column)
        {
            case 0: // Date
                // convert YYYY-MM-DD to date format
                date = convert_date(token);
                if (date.tm_year == -1) //missing or invalid date
                    return;
                if (!isWithinLast30Days(date))
                    return;
                if (isNewerThanExistingData(st, date)){
                    if (day <= 0) { // if day is not yet set, remove old data and set day
                        day = removeOldData(st, date);
                    }
                }
                st->prices[day].date = date;
                break;
            case 1: // Open
                st->prices[day].open = atof(token);
                break;
            case 2: // High
                st->prices[day].high = atof(token);
                break;
            case 3: // Low
                st->prices[day].low = atof(token);
                break; 
            case 4: // Close
                st->prices[day].close = atof(token);
                break;
            case 5: // Adj Close
                st->prices[day].adjClose = atof(token);
                break;
            case 6: // Volume
                st->prices[day].volume = atoi(token);
                day++;
                break;
        }
        token = strtok(NULL, ",");
        column++;
    }
}

struct tm convert_date(char* date)
{
    struct tm tm = {0};
    if(strlen(date) != 10)
    {
        printf("Invalid date format: %s\n", date);
        tm.tm_year = -1;
        return tm;
    }
    tm.tm_year = atoi(date) - 1900;
    tm.tm_mon = atoi(date + 5) - 1;
    tm.tm_mday = atoi(date + 8);
    return tm;
}

int isWithinLast30Days(struct tm date)
{
    // get current date
    time_t now;
    time(&now);
    struct tm *today = localtime(&now);
    time_t todayTime = mktime(today);
    // convert date to time_t
    time_t date_time = mktime(&date);

    // check if date is within the last 30 days (31 days * 24 hours * 60 minutes * 60 seconds)
    // 31 to get the last 30 days inclusive
    if (difftime(todayTime, date_time) > 31 * 24 * 60 * 60)
    {
        return 0;
    }
    return 1;
}

int isNewerThanExistingData(Stock* st, struct tm date)
{
    // loop through existing data
    for (int i = 0; i < 30; i++)
    {
        // if date is same or greater than existing data, return 0
        if (st->prices[i].date.tm_year >= date.tm_year && st->prices[i].date.tm_mon >= date.tm_mon && st->prices[i].date.tm_mday >= date.tm_mday)
        {
            return 0;
        }
    }
    return 1;
}

int removeOldData(Stock* st, struct tm date)
{
    int indexToInsertTo = 0;
    // loop through existing data
    for (int i = 0; i < 30; i++)
    {
        // if date is within the last 30 days, move data to the beginning of the array
        if (isWithinLast30Days(st->prices[i].date))
        {
            st->prices[indexToInsertTo] = st->prices[i];
            indexToInsertTo++;
        }
        else // clear old data
        {
            st->prices[i].open = 0;
            st->prices[i].high = 0;
            st->prices[i].low = 0;
            st->prices[i].close = 0;
            st->prices[i].adjClose = 0;
            st->prices[i].volume = 0;
        }
        // if date is default return index to insert new data - shorten some loops
        if (st->prices[i].date.tm_year == 0)
        {
            return i;
        }
    }
    return indexToInsertTo;
}