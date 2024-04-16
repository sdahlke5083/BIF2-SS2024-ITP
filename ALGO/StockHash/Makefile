run: StockHash
	bin\Debug\StockHash.exe

debug: StockHashDebug
	bin\Debug\StockHash.exe

StockHashDebug: mainDebug.o hash_tableDebug.o import_dataDebug.o menuDebug.o cJSON.o save_loadDebug.o
	gcc -o bin\Debug\StockHash.exe obj\Debug\main.o obj\Debug\src\hash_table.o obj\Debug\src\import_data.o obj\Debug\src\menu.o obj\Debug\src\cJSON.o obj\Debug\src\save_load.o  

mainDebug.o: main.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -DDEBUG -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\main.c" -o obj\Debug\main.o

hash_tableDebug.o: src\hash_table.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -DDEBUG -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\hash_table.c" -o obj\Debug\src\hash_table.o

import_dataDebug.o: src\import_data.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -DDEBUG -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\import_data.c" -o obj\Debug\src\import_data.o

menuDebug.o: src\menu.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -DDEBUG -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\menu.c" -o obj\Debug\src\menu.o

save_loadDebug.o: src\save_load.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -DDEBUG -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\save_load.c" -o obj\Debug\src\save_load.o

StockHash: main.o hash_table.o import_data.o menu.o cJSON.o save_load.o
	gcc -o bin\Debug\StockHash.exe obj\Debug\main.o obj\Debug\src\hash_table.o obj\Debug\src\import_data.o obj\Debug\src\menu.o obj\Debug\src\cJSON.o obj\Debug\src\save_load.o  

main.o: main.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\main.c" -o obj\Debug\main.o

hash_table.o: src\hash_table.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\hash_table.c" -o obj\Debug\src\hash_table.o

import_data.o: src\import_data.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\import_data.c" -o obj\Debug\src\import_data.o

menu.o: src\menu.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\menu.c" -o obj\Debug\src\menu.o

save_load.o: src\save_load.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\save_load.c" -o obj\Debug\src\save_load.o

cJSON.o: src\cJSON.c
	gcc -Wall -g -std=c99 -Werror -ggdb -D__USE_MINGW_ANSI_STDIO -Iinclude -c "C:\Users\dase\MyDrive\Documents\FH\Semester 2\ALGODAT\Programm1\StockHash\src\cJSON.c" -o obj\Debug\src\cJSON.o