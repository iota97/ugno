#include "CartaNumero.h"
#include "Random.h"
#include <typeinfo>

CartaNumero::CartaNumero() : numero_(generaRandom() % 9+1) {}

CartaNumero::CartaNumero(int numero, int colore) : CartaColore(colore), numero_(numero) {
	if (numero < 1 || numero > 9) {
		throw numero_fuori_range();
	}
}

CartaNumero* CartaNumero::clone() const {
	return new CartaNumero(*this);
}

bool CartaNumero::valida(const Carta& c) const {
	auto aux = dynamic_cast<const CartaNumero*>(&c);
	if (aux) {
		return aux->getColore() == getColore() || aux->getNumero() == getNumero();
	}
	auto aux2 = dynamic_cast<const CartaColore*>(&c);
	if (aux2) {
		return aux2->getColore() == getColore();
	}
	return true;
}

int CartaNumero::getNumero() const {
	return numero_;
}
