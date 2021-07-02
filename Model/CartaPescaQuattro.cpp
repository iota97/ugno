#include "CartaPescaQuattro.h"
#include <typeinfo>

CartaPescaQuattro::CartaPescaQuattro() {}

CartaPescaQuattro* CartaPescaQuattro::clone() const {
	return new CartaPescaQuattro(*this);
}

bool CartaPescaQuattro::valida(const Carta& c) const {
	(void)c; // Silence unused parameter warning
	return true;
}

void CartaPescaQuattro::applicaEffetto(Partita* partita) const {
	partita->pescaGiocatore((partita->getTurno()+1) % partita->getNumeroGiocatori(), 4);
}
