#include "GiocatoreCPU.h"

GiocatoreCPU::GiocatoreCPU(int numCarte) : Giocatore(numCarte) {}

bool GiocatoreCPU::stepMossa(DeepPtr<Carta>& tavolo, Partita* partita) {
	for (auto i = mano_.begin(); i != mano_.end(); ++i) {
		if ((*i)->valida(*tavolo)) {
			giocaCarta(i, partita);
			return true;
		}
	}
	fineTurno();
	return false;
}
