#ifndef GIOCATORECPU_H
#define GIOCATORECPU_H

#include "Giocatore.h"

class GiocatoreCPU : public Giocatore {
public:
	// Costruttore che costruisce la classe base
	GiocatoreCPU(int numCarte);
	
	// Avanza di una mossa, ritorna false se ha finito le mosse per questo turno
	bool stepMossa(DeepPtr<Carta>& tavolo, Partita* partita);
};

#endif
