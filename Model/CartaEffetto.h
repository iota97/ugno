#ifndef CARTAEFFETTO_H
#define CARTAEFFETTO_H

#include "Carta.h"
#include "Partita.h"

class CartaEffetto : virtual public Carta {
public:
	// Metodo virtuale pure come inferfaccia per l'effetto
	virtual void applicaEffetto(Partita* partita) const = 0;
};

#endif
