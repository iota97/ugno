#include "CartaSaltaTurno.h"
#include <typeinfo>

CartaSaltaTurno::CartaSaltaTurno() {}

CartaSaltaTurno::CartaSaltaTurno(int colore) : CartaColore(colore) {}

CartaSaltaTurno* CartaSaltaTurno::clone() const {
	return new CartaSaltaTurno(*this);
}

bool CartaSaltaTurno::valida(const Carta& c) const {
	auto aux = dynamic_cast<const CartaSaltaTurno*>(&c);
	if (aux) {
		return true;
	}
	auto aux2 = dynamic_cast<const CartaColore*>(&c);
	if (aux2) {
		return aux2->getColore() == getColore();
	}
	return true;
}

void CartaSaltaTurno::applicaEffetto(Partita* partita) const {
	partita->aumentaTurniDaPassare();
}
