#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"

/* Questo file contiene solo la stampa del menu principale e poi richiama una delle
 tre funzioni possibili: crea_mappa(), gioca(), termina_gioco(). */

int creata=0;
int main () {
	int a=0;
	do{
	system("clear");
	printf("\n (>Usare sempre i numeri<)\n");
	printf("\n  ________________________\n"
		   " |Campeggio Lake Trasymeno|\n"
		   " |________________________|\n"
		      "        Inserire:\n"  
		     "\n 1.    Crea mappa"
		     "\n 2.      Gioca"
		     "\n 3.   Termina gioco\n "
		        "______________________\n");
	
	scanf("%d",&a);
		switch(a){
			case 1:	
				creata=1;
				system("clear");
				crea_mappa();
				break;
			case 2:
				if(creata==1){
				system("clear");
				gioca();
				}
				else{
					system("clear");
					printf("Creare mappa\n");
				main();
				};
				break;
			case 3:
				termina_gioco();
				break;
			};	
	}while((a!=1)||(a!=2)||(a!=3));

};
