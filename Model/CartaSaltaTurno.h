#ifndef CARTASALTATURNO_H
#define CARTASALTATURNO_H

#include "CartaEffetto.h"
#include "CartaColore.h"

class CartaSaltaTurno : public CartaEffetto, public CartaColore {
public:
	// Costruttore con colore random
	CartaSaltaTurno();
	CartaSaltaTurno(int colore);
	
	// Clonazione polimorfa
	CartaSaltaTurno* clone() const override;
	
	// Controlla che la carta sia giocabile sopra la carta passata
	bool valida(const Carta& c) const override;
	
	// metodo viruale per applicare l'effetto
	void applicaEffetto(Partita* partita) const override;
};

#endif
