#ifndef CARTACOLORE_H
#define CARTACOLORE_H

#include "Carta.h"

class CartaColore : virtual public Carta {
public:
	// Costruttore random
	CartaColore();
	
	// Costruttore fisso
	CartaColore(int colore);

	// Getter publico
	int getColore() const;

	class colore_fuori_range {};

protected:
	int colore_;
};

#endif
