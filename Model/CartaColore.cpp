#include "CartaColore.h"
#include "Random.h"

CartaColore::CartaColore() : colore_(generaRandom() % 4) {}

CartaColore::CartaColore(int colore) : colore_(colore) {
	if (colore < 0 || colore > 3) {
		throw colore_fuori_range();
	}
}

int CartaColore::getColore() const {
	return colore_;
}
