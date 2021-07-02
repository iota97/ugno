#ifndef CARTAPESCADUE_H
#define CARTAPESCADUE_H

#include "CartaEffetto.h"
#include "CartaColore.h"

class CartaPescaDue : public CartaEffetto, public CartaColore {
public:
	// Costruttore con colore random
	CartaPescaDue();

	// Costruttore con colore fisso
	CartaPescaDue(int colore);

	// Clonazione polimorfa
	CartaPescaDue* clone() const override;
	
	// Controlla che la carta sia giocabile sopra la carta passata
	bool valida(const Carta& c) const override;
	
	// metodo viruale per applicare l'effetto
	void applicaEffetto(Partita* partita) const override;
};

#endif
