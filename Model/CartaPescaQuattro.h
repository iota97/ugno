#ifndef CARTAPESCAQUATTRO_H
#define CARTAPESCAQUATTRO_H

#include "CartaEffetto.h"

class CartaPescaQuattro : public CartaEffetto {
public:
	CartaPescaQuattro();
	
	// Clonazione polimorfa
	CartaPescaQuattro* clone() const override;
	
	// Controlla che la carta sia giocabile sopra la carta passata
	bool valida(const Carta& c) const override;
	
	// metodo viruale per applicare l'effetto
	void applicaEffetto(Partita* partita) const override;
};

#endif
