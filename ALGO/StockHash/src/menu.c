// menu.c
#include "menu.h"

void displayMenu() {
    printf("Stock Management System\n");
    printf("-----------------------\n");
    printf("1. Add Stock\n");
    printf("2. Delete Stock\n");
    printf("3. Search for a Stock\n");
    printf("4. Import Stock Data from CSV\n");
    printf("5. Plot Stock Data\n");
    printf("6. Save Hash Table to File\n");
    printf("7. Load Hash Table from File\n");
    printf("8. Quit\n");
    printf("-----------------------\n");
    #ifdef DEBUG
    printf("DEBUG MODE: ON\n");
    printf("9. Print debug list\n");
    printf("-----------------------\n");
    #endif
    printf("Select an option: ");
}

void processMenuOption(int option, MyHashTables* ht) {
    switch(option) {
        case 1:
			addStock(ht);
			break;
        case 2:
            deleteStockUI(ht);
            break;
        case 3:
            searchStockUI(ht);
            break;
        case 4:
            importStockDataUI(ht);
            break;
        case 5:
            plotStockPricesUI(ht);
            break;
        case 6:
            saveHashTablesUI(ht);
            break;
        case 7:
            loadHashTablesUI(ht);
            break;
        case 8:
            printf("Quitting...\n");
            break;
        #ifdef DEBUG
        case 9:
            printMyHashTables(ht);
            break;
        #endif
        default:
            printf("Invalid option. Please try again.\n");
    }
}

void addStock(MyHashTables* ht) {
    Stock s;
    printf("Enter stock symbol: ");
    scanf("%s", s.symbol); // Make sure to handle input safely in real applications
    printf("Enter company name: ");
    scanf(" %255[^\n]", s.name); // Simplified for brevity
    printf("Enter WKN: ");
    scanf("%s", s.wkn);
    s.valid = 1; // Mark the stock as valid/active

    insertStock(ht, s);
    printf("Stock added successfully.\n");

    printf("Press Any Key to Continue\n");
    getchar();
}

void deleteStockUI(MyHashTables* ht) {
    char symbol[6];
    int errCount = 0;

    #ifdef DEBUG
    // print possible stocks
    printMyHashTables(ht);
    #endif

    if(ht->shortNameHashTableSize > 0){
        do
        {
            // if not first input and stock not found
            if (symbol[0] != '\0')
            {
                printf("Stock not found - Try other or exit with 0.\n");
                errCount++;
                if (errCount > 3 || symbol[0] == '0')
                {
                    printf("Too many errors or exit. Exiting delete.\n");
                    return;
                }
            }
            printf("Enter stock symbol to delete: ");
            scanf("%s", symbol);
        } while (searchStock(ht, symbol) == NULL);

        deleteStock(ht, symbol);
        printf("If the stock existed, it has been deleted.\n");
    }
    else
    {
        printf("No stocks to delete.\n");
    }

    printf("Press Any Key to Continue\n");
    getchar();
}

void searchStockUI(const MyHashTables* ht) {
    char symbol[6];
    printf("Enter stock symbol to search for: ");
    scanf("%s", symbol);
    Stock* s = searchStock(ht, symbol);
    if (s != NULL) {
        printf("Stock Found: %s - %s\n", s->symbol, s->name);
        printf("Latest course:");
        // search which id is latest price and print it
        int lastId = 29;
        while (s->prices[lastId].open <= 0 && lastId > 0)
        {
            lastId--;
        }
        if(lastId > 0){
            StockPrice* p = &s->prices[lastId];
            char date[11];
            strftime(date, sizeof(date), "%d.%m.%y", &s->prices[lastId].date);
            printf("Date: %s \n Open: %2.2f \t High: %2.2f \t Low: %2.2f \n Close: %2.2f \t Adj Close: %2.2f \t Volume: %li\n", date, p->open, p->high, p->low, p->close, p->adjClose, p->volume);
        }
        else
            printf(" No data available.\n");
        } else {
        printf("Stock not found.\n");
    }

    printf("Press Any Key to Continue\n");
    getchar();
}

void importStockDataUI(MyHashTables* ht) {
    char filename[256];
    char symbol[6];
    int errCount = 0;
    // define stock to import prices
    do {
        // if not first input and stock not found
        if(symbol[0] != '\0'){
            printf("Stock not found.\n");
            errCount++;
            if(errCount > 3){
                printf("Too many errors. Exiting import.\n");
                return;
            }
        }
        printf("Enter stock symbol to import data for: ");
        scanf("%s", symbol);
    } while (searchStock(ht, symbol) == NULL);

    printf("Enter filename to import: ");
    // scanf with whitespace specifier to allow spaces in filename
    scanf(" %255[^\n]", filename);

    //  trim high comma at beginning and end if present
    int move = 0;
    if (filename[0] == '"' || filename[0] == '\'' || filename[0] == '`')
        move = 1;
    if (filename[strlen(filename) - 1] == '"' || filename[strlen(filename) - 1] == '\'' || filename[strlen(filename) - 1] == '`')
        filename[strlen(filename) - 1] = '\0';
    // replace backslashes with forward slashes
    for (int i = 0; i < strlen(filename); i++)
    {
        if(move)
            filename[i] = filename[i + 1];
        if (filename[i] == '\\')
        {
            filename[i] = '/';
        }
    }

    // chek if the file exists
    if (_access(filename, 0) != -1) {
        importStockData(ht, filename, symbol);
        printf("Stock data imported successfully.\n");
    } else {
        printf("File not found.\n");
    }

    printf("Press Any Key to Continue\n");
    getchar();
    return;
}

void plotStockPricesUI(const MyHashTables* ht) {
    char symbol[6];
    int errCount = 0;

    // define stock to import prices
    do
    {
        // if not first input and stock not found
        if (symbol[0] != '\0')
        {
            printf("Stock not found.\n");
            errCount++;
            if (errCount > 3)
            {
                printf("Too many errors. Exiting import.\n");
                return;
            }
        }
        printf("Enter stock symbol to import data for: ");
        scanf("%s", symbol);
    } while (searchStock(ht, symbol) == NULL);

    // get stock
    Stock* stock = searchStock(ht, symbol);

    plotStock(stock);

    printf("Press Any Key to Continue\n");
    getchar();
}

void saveHashTablesUI(const MyHashTables* ht) {
    
    // ask if default path should be used
    char answer;
    printf("Do you want to use the default path for saving? (Y/n): ");
    scanf(" %c", &answer);
    if(answer == 'Y' || answer == 'y'){
        saveMyHashTablesDefault(ht);
    }
    else{
        char filename[256];
        printf("Enter path to save: ");
        // scanf with whitespace specifier to allow spaces in filename
        scanf(" %255[^\n]", filename);

        //  trim high comma at beginning and end if present
        int move = 0;
        if (filename[0] == '"' || filename[0] == '\'' || filename[0] == '`')
            move = 1;
        if (filename[strlen(filename) - 1] == '"' || filename[strlen(filename) - 1] == '\'' || filename[strlen(filename) - 1] == '`')
            filename[strlen(filename) - 1] = '\0';
        // replace backslashes with forward slashes
        for (int i = 0; i < strlen(filename); i++)
        {
            if(move)
                filename[i] = filename[i + 1];
            if (filename[i] == '\\')
            {
                filename[i] = '/';
            }
        }

        saveMyHashTables(ht, filename);
    }

    printf("Press Any Key to Continue\n");
    getchar();
}

void loadHashTablesUI(MyHashTables* ht) {
    // ask if default path should be used
    char answer;
    printf("Do you want to use the default path for loading? (Y/n): ");
    scanf(" %c", &answer);
    if(answer == 'Y' || answer == 'y'){
        loadMyHashTablesDefault(ht);
    }
    else{
        char filename[256];
        printf("Enter path to load: ");
        // scanf with whitespace specifier to allow spaces in filename
        scanf(" %255[^\n]", filename);

        //  trim high comma at beginning and end if present
        int move = 0;
        if (filename[0] == '"' || filename[0] == '\'' || filename[0] == '`')
            move = 1;
        if (filename[strlen(filename) - 1] == '"' || filename[strlen(filename) - 1] == '\'' || filename[strlen(filename) - 1] == '`')
            filename[strlen(filename) - 1] = '\0';
        // replace backslashes with forward slashes
        for (int i = 0; i < strlen(filename); i++)
        {
            if(move)
                filename[i] = filename[i + 1];
            if (filename[i] == '\\')
            {
                filename[i] = '/';
            }
        }

        loadMyHashTables(ht, filename);
    }

    printf("Press Any Key to Continue\n");
    getchar();
}