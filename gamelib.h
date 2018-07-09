/* Questo file contiene le dichiarazioni delle funzioni crea_mappa(), gioca(), termina_gioco().
 Continene anche le definizioni dei tipi utilizzati in gamelib.c:
 struct Giocatore, struct Zona, enum Stato_giocatore, enum Tipo_zona, enum Tipo_oggetto. */
void gioca();
void termina_gioco();
void crea_mappa();
int main();
enum Tipo_zona{
	cucina=1,
	soggiorno,
	rimessa,
	strada,
	lungo_lago,
	uscita_campeggio
	};

enum Tipo_oggetto{
	 cianfrusaglia,
	 bende,
	 coltello,
	 pistola,
	 benzina,
	 adrenalina
	};
enum Stato_giocatore{
	morto,
	ferito,
	vivo
	};

struct Zona{
	enum Tipo_zona zona;
	enum Tipo_oggetto oggetto;
	struct Zona* zona_successiva;
	};
struct Giocatore{
	enum Stato_giocatore stato;
	struct Zona* posizione;
	short zaino[6];
	};

