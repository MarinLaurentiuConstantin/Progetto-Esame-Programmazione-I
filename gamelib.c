//MARIN LAURENTIU CONSTANTIN matricola:303422
#include <stdio.h>
#include <stdlib.h>
#include "gamelib.h"
#include <time.h>
static struct Giocatore chi_gioca;//usato per funzioni generiche al posto dei giocatori
static struct Zona* prima_zona=NULL;
static struct Zona* ultima_zona=NULL;
static struct Giocatore marzia;
static struct Giocatore giacomo;
int opzione=0;
int n_zone=0;//usato per contare le zone create
int s_zona=0;//usato per scanf zone
int adr_g=0;//adrenalina  utilizata giocatori
int adr_m=0;
int benza=0;//benzina utilizata
int visione_g=0;//usato per mostra oggetto
int visione_m=0;
int mp_creata=0;//usato per individuare creazione mappa
int g_prec=0;//giocatore che ha iniziato il turno
int g_turno=0;//individuare inizio e fine turno
static const short int probabilita[6][6]={  {30,50,90,0,0,100},
											{20,30,40,70,0,100},
											{20,10,60,0,90,100},
											{80,0,90,0,100,0},
											{70,0,80,0,100,0},
											{90,0,100,0,0,0}};
void termina_gioco(){
	if(prima_zona!=NULL){
		struct Zona* cor=prima_zona;
		struct Zona* suc=NULL;
		do{
			suc=cor->zona_successiva;
			free(cor);
			cor=suc;
		}while(cor!=NULL);
		free(suc);
	};
	printf("____________________\n");
	printf("\nGame Over\n");
	printf("____________________\n");
	exit(0);
};
static int ins_ogg(){
		int ogg=(rand()%100)+1;
		for (int i = 0; i < 6; ++i){
			if(probabilita[s_zona][i]!=0){
				if (ogg<=probabilita[s_zona][i]){
					return i;
				};
			};
		};
	return 0;
};

static void ins_zona(){
	n_zone++;
	printf("____________________\n");
	printf("1.     Cucina\n");
	printf("2.    Soggiorno\n");
	printf("3.     Rimessa\n");
	printf("4.     Strada\n");
	printf("5.   Lungo lago\n");
	printf("6. Uscita campeggio\n");
	printf("____________________\n");
	scanf("%d",&s_zona);
	system("clear");
	//printf("\n%d n_zone!!!",n_zone);
	
	
		if ((s_zona==1)||(s_zona==2)||(s_zona==3)||(s_zona==4)||(s_zona==5)||(s_zona==6)){
				if(prima_zona==NULL){
					ultima_zona=prima_zona=(struct Zona*) malloc(sizeof(struct Zona));
					prima_zona->zona_successiva=NULL;
					ultima_zona->zona=s_zona;
					ultima_zona->oggetto=ins_ogg();
				}	
				else{
					ultima_zona->zona_successiva=(struct Zona*) malloc(sizeof(struct Zona));
					ultima_zona=ultima_zona->zona_successiva;
					ultima_zona->zona_successiva=NULL;
					ultima_zona->zona=s_zona;
					ultima_zona->oggetto=ins_ogg();

				};
		}
		else{
			n_zone--;
			system("clear");
			printf("Input sbagliato\n");
			ins_zona();
		};
		//printf("%d\n",prima_zona->zona);
		crea_mappa();
	};


static void canc_zona(){
		if(n_zone==0){
			system("clear");
			printf("\nInserire Zona\n");
			crea_mappa();
		}
		else{
			printf("Ultima zona Cancellata\n");
			n_zone--;
			struct Zona* elemento=prima_zona;
			struct Zona* ultimo=NULL;
		 	if (elemento->zona_successiva==NULL){
		 		free(elemento);
		 		prima_zona=NULL;
		 	}
		 	else{
		 		do
		 		{
		 			if(elemento->zona_successiva==ultima_zona){
		 				ultimo=elemento;
		 				break;
		 			}
		 			else{
		 				elemento=elemento->zona_successiva;
		 			};
		 		} while (elemento->zona_successiva!=NULL);
		 		free(ultimo->zona_successiva);
		 		ultimo->zona_successiva=NULL;
		 		ultima_zona=ultimo;

		 	};

        };
            
        crea_mappa();
		};


static void stampa_mappa(){
		if(n_zone==0){
			system("clear");
			printf("\nInserire Zona\n");          
			crea_mappa();
		}
		else{
			printf("_____________________\n");
			struct Zona* nodo=prima_zona;
			do
			{
				//printf("%d\n",nodo->oggetto);
				switch (nodo->zona){
					case 1: 
						printf(" > Cucina \n");

						break;
					case 2: 
						printf(" > Soggiorno \n");
						break;
					case 3:
					 	printf(" > Rimessa \n");
						break;
					case 4:
						 printf(" > Strada \n");
						break;
					case 5:
						 printf(" > Lungo lago \n");
						break;
					case 6:
						 printf(" > Uscita Campeggio \n");
						break;
				};
				printf("     %p\n", nodo->zona_successiva);
				nodo=nodo->zona_successiva;
			} while (nodo!=NULL);
			printf("_____________________\n");
        crea_mappa();
		};
	};


static void chiudi_mappa(){
	if(n_zone<7) {
		printf("\nDevono essere almeno 8 zone\n");
		crea_mappa();
	};
	if ((ultima_zona->zona!=6)&&(n_zone>7)){
					system("clear");
					printf("L'ultima zona deve essere uscita campeggio.\n");
					crea_mappa();
				}
	system("clear");
	mp_creata=1;
	main();
	};

void crea_mappa(){
	struct Zona* pri=prima_zona;
	struct Zona* su=NULL;
	if(mp_creata>0){
		int risp=0;
		system("clear");
		printf("Mappa gia creata\n");
		printf("_____________________\n");
		printf("Vuoi eliminare la mappa attuale e crearne una nuova?\n");
		printf("1. Si\n");
		printf("2. No\n");
		printf("_____________________\n");
		scanf("%d",&risp);
		switch (risp){
			case 1:
				
				do{
					su=pri->zona_successiva;
					free(pri);
					pri=su;
				}while(pri!=NULL);
				free(su);
				n_zone=0;
				mp_creata=0;
				prima_zona=NULL;

				crea_mappa();
			break;
			case 2:
				system("clear");
				main();
			break;
			default:
				crea_mappa();
			break;
		};
	};
	printf("__________________\n");
	printf("1. Inserisci Zona \n");
	printf("2. Cancella Zona  \n");
	printf("3. Stampa Mappa   \n");
	printf("4. Chiudi Mappa   \n");
	printf("__________________\n");
	scanf("%d",&opzione);
	//printf("%d" ,opzione);
	
		switch (opzione){
			case 1:system("clear");
                ins_zona();
			break;
			case 2:system("clear");
                canc_zona();
			break;
			case 3:system("clear");
                stampa_mappa();
			break;
			case 4:system("clear");
                chiudi_mappa();
			break;
			default:
			system("clear");
			printf("\nInput sbagliato\n");
			crea_mappa();
			break;
			
		};
	
	};

static void gieson(int ini , int g){ //comparsa e combattimento con gieson
			int col=0;
			int pis=0;
			int arm=0;
			int ben=0;
			
	
			if (ini==0){
				chi_gioca=giacomo;
			}
			else{
				chi_gioca=marzia;
			};
				col=chi_gioca.zaino[coltello];
				pis=chi_gioca.zaino[pistola];
				ben=chi_gioca.zaino[benzina];

				if((g<75)&&(chi_gioca.posizione->zona==6)){//comparsa in uscita campeggio
					printf("E' apparso gieson!\n");
					printf("_______________________\n");
					if((col>0)||(pis>0)||(ben>0)){
						printf("Hai a disposizione:\n");
						printf("1. Coltello: %d\n", col);
						printf("2. Pistola: %d\n",pis );
						printf("3. Benzina:%d\n",ben );
						printf("Quale oggetto usare?\n");
						scanf("%d",&arm);

						switch (arm){
							case 1:
								if (col>0){
									if (chi_gioca.stato==vivo){
										chi_gioca.zaino[coltello]--;
										chi_gioca.stato=ferito;
										system("clear");
										printf("Hai usato coltello.\n");
										printf("Sei rimatoferito/a durante il combattimento\n");
									}
									else{
										system("clear");
										printf("Essendo gia ferito sei morto/a durante il combattimento\n");
										chi_gioca.stato=morto;
									
									};
								}
								else{
										system("clear");
										printf("Non hai : Coltello\n");
										printf("Scegliere un altro oggetto\n");
										gieson(ini , g);
								};
							break;

							case 2:
								if (pis>0)	{
									chi_gioca.zaino[pistola]--;
									system("clear");
									printf("Hai usato pistola e sei scappato/a da Gieson\n");
								}
								else{
										system("clear");
										printf("Non hai : Pistola\n");
										printf("Scegliere un altro oggetto\n");
										gieson(ini , g);
								};
							break;

							case 3:
								if(ben>0){
									chi_gioca.zaino[benzina]--;
									benza=4;
									system("clear");
									printf("Hai usato benzina.\n");
									printf("Gieson non apparira' per i prossimi %d turni\n",benza);
								}
								else{
										system("clear");
										printf("Non hai : Benzina\n");
										printf("Scegliere un altro oggetto\n");
										gieson(ini , g);
								};
							break;
							default:
								system("clear");
								printf("Input sbagliato\n");
								gieson(ini , g);
							break;

						};
					}
					else{
						printf("Non avevi niente per difenderti\n");
						printf("Giocatore morto.\n");
						chi_gioca.stato=morto;
					};
				}		
				else{
					if(  (g<30) || ( (g<50) && ( (giacomo.stato==morto) || (marzia.stato==morto) ) ) ) {//comparsa in altre zone
					system("clear");
					printf("E' apparso gieson!\n");
					printf("_______________________\n");
					if((col>0)||(pis>0)||(ben>0)){
						printf("Hai a disposizione:\n");
						printf("1. Coltello: %d\n", col);
						printf("2. Pistola: %d\n",pis );
						printf("3. Benzina:%d\n",ben );
						printf("Quale oggetto usare?\n");
						scanf("%d",&arm);

						switch (arm){
							case 1:
								if (col>0){
									if (chi_gioca.stato==vivo){
										chi_gioca.zaino[coltello]--;
										chi_gioca.stato=ferito;
										system("clear");
										printf("Hai usato coltello.\n");
										printf("Sei rimatoferito/a durante il combattimento\n");
									}
									else{
										system("clear");
										printf("Essendo gia ferito sei morto/a durante il combattimento\n");
										chi_gioca.stato=morto;
									
									};
								}
								else{
										system("clear");
										printf("Non hai : Coltello\n");
										printf("Scegliere un altro oggetto\n");
										gieson(ini , g);
								};
							break;

							case 2:
								if (pis>0)	{
									chi_gioca.zaino[pistola]--;
									system("clear");
									printf("Hai usato pistola e sei scappato/a da Gieson\n");
								}
								else{
										system("clear");
										printf("Non hai : Pistola\n");
										printf("Scegliere un altro oggetto\n");
										gieson(ini , g);
								};
							break;

							case 3:
								if(ben>0){
									chi_gioca.zaino[benzina]--;
									benza=4;
									system("clear");
									printf("Hai usato benzina.\n");
									printf("Gieson non apparira' per i prossimi %d turni\n",benza);
								}
								else{
										system("clear");
										printf("Non hai : Benzina\n");
										printf("Scegliere un altro oggetto\n");
										gieson(ini , g);
								};
							break;
							default:
								system("clear");
								printf("Input sbagliato\n");
								gieson(ini , g);
							break;

						};
					}
					else{
						printf("Non avevi niente per difenderti\n");
						printf("Giocatore morto.\n");
						chi_gioca.stato=morto;
					};

					}
					else{
						//system("clear");
						printf("Gieson non presente!\n");
					};

				
				};
	
			if (ini==0){
				giacomo=chi_gioca;
			}
			else{
				marzia=chi_gioca;
			};
};

	static void avanza(int ini, int g){
	 	system("clear");
	 	if(benza<=0){

			if (ini==0){
				if(giacomo.posizione->zona_successiva==NULL){
					system("clear");
					printf("\nGiacomo é uscito dal campeggio!\n");
					giacomo.stato=morto;
				}
				else{
				giacomo.posizione=giacomo.posizione->zona_successiva;
				gieson(ini , g);
				};

			}
			else{
				if(marzia.posizione->zona_successiva==NULL){
					system("clear");
					printf("\nMarzia é uscito dal campeggio!\n");
					marzia.stato=morto;
				}
				else{
				marzia.posizione=marzia.posizione->zona_successiva;
				gieson(ini , g);
				};
			
			};
		}
		else{
			benza--;
			system("clear");
			printf("Gieson non apparira' per i prossimi %d turni \n",benza);
			if (ini==0){
				if(giacomo.posizione->zona_successiva==NULL){
					system("clear");
					printf("\nGiacomo é uscito dal campeggio!\n");
					giacomo.stato=morto;
				}
				else{
				giacomo.posizione=giacomo.posizione->zona_successiva;
				};

			}
			else{
				if(marzia.posizione->zona_successiva==NULL){
					system("clear");
					printf("\nMarzia é uscito dal campeggio!\n");
					marzia.stato=morto;
				}
				else{
				marzia.posizione=marzia.posizione->zona_successiva;
				};
			
			};

		};

		
	gioca();
	
};
 static void mostra_oggetto(int ini, int g){
 	if(ini==0){
 		chi_gioca=giacomo;
 		visione_g++;
 	}
 	else{
 		chi_gioca=marzia;
 		visione_m++;
 	};
 	printf("\n Oggetto trovato:");
	switch (chi_gioca.posizione->oggetto){
					case 0: 
						system("clear");
						printf("cianfrusaglia\n\n");
						break;
					case 1: 
						system("clear");
						printf("bende\n\n");
						break;
					case 2:
						system("clear");
					 	printf("coltello\n\n");
						break;
					case 3:
						system("clear");
						 printf("pistola\n\n");
						break;
					case 4:
						system("clear");
						 printf("benzina\n\n");
						break;
					case 5:
						system("clear");
						 printf("adrenalina\n\n");
						break;
				};
				gieson(ini , g);
				gioca();
   
};

static void prendi_oggetto(int ini, int g){
 	int r;
 	if(ini==0){
 		if(visione_g>0){
 		visione_g=0;
 		chi_gioca=giacomo;
 		r=giacomo.posizione->oggetto;
 		giacomo.zaino[r]++;
		chi_gioca.zaino[r]=giacomo.zaino[r];
		system("clear");
		printf("Giacomo ha preso: ");
		switch(chi_gioca.posizione->oggetto){
		case 0:
		printf("cianfrusaglia\n\n");
		break;
		case 1:
		printf("bende\n\n");
		break;
		case 2:
		printf("coltello\n\n");
		break;
		case 3:
		printf("pistola\n\n");
		break;
		case 4:
		printf("benzina\n\n");
		break;
		case 5:
		printf("adrenalina\n\n");
		break;
		
	};
		}
		else{
			system("clear");
			printf("Bisogna prima fare Mostra Oggetto! \n");
		};
 	}
 	else{
 		if(visione_m>0){
 		chi_gioca=marzia;
 		r=marzia.posizione->oggetto;
		marzia.zaino[r]++;
		chi_gioca.zaino[r]=marzia.zaino[r];
		system("clear");
		printf("Marzia ha preso: ");
			switch(chi_gioca.posizione->oggetto){
		case 0:
		printf("cianfrusaglia\n");
		break;
		case 1:
		printf("bende\n");
		break;
		case 2:
		printf("coltello\n");
		break;
		case 3:
		printf("pistola\n");
		break;
		case 4:
		printf("benzina\n");
		break;
		case 5:
		printf("adrenalina\n");
		break;
		
	};
		}
		else{
			system("clear");
			printf("Bisogna prima fare Mostra Oggetto! \n");
		};

 	};
 	chi_gioca.posizione->oggetto=cianfrusaglia;
 	gieson(ini , g);
    gioca();
};

static void cura(int ini, int g){
	if(ini==0){
		if(giacomo.zaino[bende]>0){
		giacomo.zaino[bende]--;
    	giacomo.stato=vivo;
    	system("clear");
    	printf("Giacomo ha usato cura\n");
    
    	}
    else{
    	system("clear");
    	printf("\nNon hai bende\n");
    
    	};
	}
	else{
		if(marzia.zaino[bende]>0){
		marzia.zaino[bende]--;
    	marzia.stato=vivo;
    	system("clear");
    	printf("Marzia ha usato cura\n");
    
    	}
    else{
    	system("clear");
    	printf("\nNon hai bende\n");
    	
    	};
	};
 	gieson(ini , g);
 	gioca();
};

static void usa_adrenalina(int ini, int g){

   if(ini==0){
   		if(giacomo.zaino[adrenalina]>0){
		giacomo.zaino[adrenalina]--;
		adr_g=2;
		system("clear");
		printf("\nGiacomo ha usato adrenalina\n");
		

		}
		else{
			system("clear");
			printf("Non hai adrenalina\n");

		};
	}
	else{
		if(marzia.zaino[adrenalina]>0){
		marzia.zaino[adrenalina]--;
		adr_m=2;
		system("clear");
		printf("\nMarzia ha usato adrenalina\n");

		}
		else{
			system("clear");
			printf("Non hai adrenalina\n");

		};
	};
	gieson(ini , g);
	gioca();
};
int p_turno=0;//usato per identificare il primo turo
void gioca(){
	int g=rand()%100;
    int gio=0;//usato per scanf che fa avanzare nel gioco
    
    int ini;//usato per identificare a chi tocca giocare
  	
  	if(p_turno==0){//primo turno con inizializazione giocatori
    	p_turno++;
   		marzia.zaino[adrenalina]=2;
    	marzia.posizione=prima_zona;
    	marzia.stato=vivo;

    	giacomo.zaino[coltello]=1;
    	giacomo.posizione=prima_zona;
    	giacomo.stato=vivo;
	}

   	if(g_turno==0){//inizio turno
   		ini=rand()%2;
		g_prec=ini;
    	g_turno=1;
   	}
    else{//meta turno
    	g_turno=0;
    	if(g_prec==0){
   			ini=1;
  		}
   		else{
   			ini=0;
   		};
  	};
  	if(adr_g>0){//adrenalina
   		adr_g--;
   		ini=0;
   	};
   	if(adr_m>0){
   		ini=1;
   		adr_m--;
   	};

   	if((giacomo.stato==morto)&&((marzia.stato==vivo)||(marzia.stato==ferito))){
    	ini=1;
    };

    if((marzia.stato==morto)&&((giacomo.stato==vivo)||(giacomo.stato==ferito))){	
    	ini=0;
   	};	
   
	
	 

	if((marzia.stato==morto)&&(giacomo.stato==morto)){
		termina_gioco();
	};
   

	printf("\n\n\n_______________________\n");
	if (ini==0){
        printf("\n\nTurno di Giacomo");
        chi_gioca=giacomo;
    }
    else{
        printf("\n\nTurno di Marzia");
        chi_gioca=marzia;
    };
    printf("\nSi trova in:");
    switch(chi_gioca.posizione->zona){
    	case 1: 
						printf(" Cucina \n");

						break;
					case 2: 
						printf(" Soggiorno \n");
						break;
					case 3:
					 	printf(" Rimessa \n");
						break;
					case 4:
						 printf(" Strada \n");
						break;
					case 5:
						 printf(" Lungo lago \n");
						break;
					case 6:
						 printf(" Uscita Campeggio \n");
						break;
    };

    printf("\n_______________________");
    printf("\n Inserire:\n 1.Avanza\n 2.Mostra Oggetto\n 3.Prendi oggetto\n 4.Cura\n 5.Usa Adrenalina\n ");
    printf("_______________________\n");
	scanf("%d",&gio);
    switch(gio){
        case 1:
            avanza(ini , g);
            break;
        case 2:
            mostra_oggetto(ini , g);
            break;
        case 3:
            prendi_oggetto(ini , g);
            break;
        case 4:
            cura(ini , g);
            break;
        case 5:
            usa_adrenalina(ini , g);
            break;
        default:
        	system("clear");
            printf("Input Sbagliato");
            gioca();
            break;
    };
};

