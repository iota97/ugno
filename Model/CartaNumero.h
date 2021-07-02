#ifndef CARTANUMERO_H
#define CARTANUMERO_H

#include "CartaColore.h"

class CartaNumero : public CartaColore {
public:

	// Costruttore di carta random
	CartaNumero();

	// Costruttore fisso
	CartaNumero(int numero, int colore);

	// Clonazione polimorfa
	CartaNumero* clone() const override;
	
	// Controlla che la carta sia giocabile sopra la carta passata
	bool valida(const Carta& c) const override;
	
	// Getter publici
	virtual int getNumero() const;

	class numero_fuori_range {};

protected:
	int numero_;
};

#endif
