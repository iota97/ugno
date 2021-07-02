#include "CartaPescaDue.h"
#include <typeinfo>

CartaPescaDue::CartaPescaDue() {}

CartaPescaDue::CartaPescaDue(int colore) : CartaColore(colore) {}

CartaPescaDue* CartaPescaDue::clone() const {
	return new CartaPescaDue(*this);
}

bool CartaPescaDue::valida(const Carta& c) const {
	auto aux = dynamic_cast<const CartaPescaDue*>(&c);
	if (aux) {
		return true;
	}
	auto aux2 = dynamic_cast<const CartaColore*>(&c);
	if (aux2) {
		return aux2->getColore() == getColore();
	}
	return true;
}

void CartaPescaDue::applicaEffetto(Partita* partita) const {
	partita->pescaGiocatore((partita->getTurno()+1) % partita->getNumeroGiocatori(), 2);
}
