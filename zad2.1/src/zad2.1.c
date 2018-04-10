/*
 ============================================================================
 Name        : 1.c
 Author      : mc
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 Zadanie 1. Tworzenie biblioteki dynamicznej
 Zadanie ma na celu utrwalenie sposobu tworzenia bibliotek dynamicznych.
 1. Utworzyć nowy projekt dla języka C w IDE Eclipse typu "Empty Project" o nazwie biblioteka.
 2. Wewnątrz utworzonego projektu stworzyć katalog źródłowy o nazwie „src”
 3. W katalogu „src” stworzyć plik nagłówkowy bilblioteka.h i źródłowy biblioteka.c.
 4. Zaimplementować funkcje odejmowanie() i iloczyn() realizujące odpowiednie
 operacje matematyczne, przyjmujące dwa argumenty typu całkowietego i zwracające wynik.
 5. Wykorzystując terminal (konsolę) na podstawie utworzonych plików stworzyć bibliotekę dynamiczną.

 */
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
int main(void) {
	//puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */

	int status_wyjscia;
	void * biblioteka;
	int (*odejmowanie)(int, int);
	int (*iloczyn)(int, int);
	biblioteka = dlopen("./biblioteka.so", RTLD_LAZY);

	if (!biblioteka) {

		printf("blad otwarcia %s\n", dlerror());
		return 1;
	}

	odejmowanie = dlsym(biblioteka, "odejmowanie");

	printf("odejmowanie: %d \n", odejmowanie(4, 2));

	iloczyn = dlsym(biblioteka, "iloczyn");

	printf("\n iloczyn: %d \n", iloczyn(4, 2));

	/*char cwd[1024];
	 if (getcwd(cwd, sizeof(cwd)) != NULL)
	 fprintf(stdout, "Current working dir: %s\n", cwd);
	 else
	 perror("getcwd() error");*/

	status_wyjscia = dlclose(biblioteka);

	if (status_wyjscia) {
		printf("Blad %s \n", dlerror());
	}else{printf("Poprawnie zamknieto RTLD_LAZY \n");}

	biblioteka = dlopen("./biblioteka.so", RTLD_NOW);

	odejmowanie = dlsym(biblioteka, "odejmowanie");

	printf("odejmowanie RTLD_NOW: %d \n", odejmowanie(4, 2));

	iloczyn = dlsym(biblioteka, "iloczyn");

	printf("\n iloczyn RTLD_NOW: %d \n", iloczyn(4, 2));

	status_wyjscia = dlclose(biblioteka);

	if (status_wyjscia) {
		printf("Blad %s \n", dlerror());
	}else{printf("Poprawnie zamknieto RTLD_NOW  \n");}

	return EXIT_SUCCESS;
}
int odejmowanie(int a, int b) {
	return a - b;
}
int iloczyn(int a, int b) {
	return a * b;
}
;

