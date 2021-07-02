#include "Giocatore.h"
#include "Partita.h"
#include "CartaEffetto.h"

Giocatore::Giocatore(int numCarte) : haGettato_(false) {
	for (int i = 0; i < numCarte; ++i) {
		mano_.push_back(Partita::generaCarta());
	}
}

Giocatore::~Giocatore() {}

const Carta& Giocatore::getCarta(int id) const {
	if (id < 0 || id >= getNumeroCarteInMano()) {
		throw id_carta_out_of_range();
	}
	return *mano_[id];
}
	
int Giocatore::getNumeroCarteInMano() const {
	return mano_.size();
}

bool Giocatore::haVinto() const {
	return mano_.size() == 0;
}

void Giocatore::giocaCarta(int id, Partita* partita) {
	haGettato_ = true;	
	partita->setCartaSulTavolo(mano_[id]);
	mano_.erase(id);
	partita->applicaCartaSulTavolo();
}

void Giocatore::giocaCarta(const Lista<DeepPtr<Carta>>::iterator& it, Partita* partita) {
	haGettato_ = true;	
	partita->setCartaSulTavolo(*it);
	mano_.erase(it);
	partita->applicaCartaSulTavolo();
}

void Giocatore::pesca(int numCarte) {
	for (int i = 0; i < numCarte; ++i) {
		mano_.push_back(Partita::generaCarta());
	}
}

void Giocatore::fineTurno() {
	if (mano_.size() != 0 && !haGettato_) {
		pesca();
	}
	haGettato_ = false;
}

void Giocatore::aggiungiCartaAllaMano(const DeepPtr<Carta>& carta) {
	mano_.push_back(carta);
}
