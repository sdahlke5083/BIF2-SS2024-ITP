// system includes
#include <stdio.h>
#include <stdlib.h>
// my includes
#include "hash_table.h"
#include "menu.h"

int main() {
    MyHashTables myHT;
    initMyHashTables(&myHT);

    int option;
    do {
      displayMenu();
      scanf("%d", &option);
      processMenuOption(option, &myHT);
		  //clear input if anything got mixed up like enter a char or string instead of a number
		  scanf("%*[^\n]");
      //clear buffer
      scanf("%*c");
    } while (option != 8); // 8 is the option to quit

    // free memory	
    freeMyHashTables(&myHT);

    return 0;
}
