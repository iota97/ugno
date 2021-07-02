#include "Partita.h"

#include "CartaPescaDue.h"
#include "CartaPescaQuattro.h"
#include "CartaNumero.h"
#include "CartaSaltaTurno.h"
#include "Random.h"
#include <time.h> 

Partita::Partita(int numGiocatori, int numCarteIniziali) : turno_(0), turniDaPassare_(1) {
	setRandomSeed(time(NULL));
	cartaSulTavolo_ = generaCarta();
	giocatori_.push_back(new Giocatore(numCarteIniziali));
	for (int i = 1; i < numGiocatori; ++i) {
		giocatori_.push_back(new GiocatoreCPU(numCarteIniziali));
	}
}

Partita::Partita() : turno_(0), turniDaPassare_(1) {
	setRandomSeed(time(NULL));
}

Partita::~Partita() {
	for (auto it : giocatori_) {
		delete it;
	}
}

void Partita::eseguiStepGiocatoreCPU() {
	if (giocatori_[turno_]->haVinto()) {
		avanzaTurni(1);
		if (turno_ != 0 || giocatori_[0]->haVinto()) eseguiStepGiocatoreCPU();
		return;
	}
	auto ptr = dynamic_cast<GiocatoreCPU*>(giocatori_[turno_]);
	if (!ptr) {
		throw turno_giocatore_non_controllato_dalla_cpu();
	}
	if (!ptr->stepMossa(cartaSulTavolo_, this)) {
		avanzaTurni(turniDaPassare_);
		turniDaPassare_ = 1;
	}
}

bool Partita::playerGiocaCarta(int idCarta) {
	if (turno_ != 0) {
		throw non_e_il_turno_del_giocatore();
	}

	if (!giocatori_[0]->getCarta(idCarta).valida(*cartaSulTavolo_))
		return false;

	giocatori_[0]->giocaCarta(idCarta, this);
	return true;
}

void Partita::playerFineTurno() {
	if (turno_ != 0) {
		throw non_e_il_turno_del_giocatore();
	}
	giocatori_[0]->fineTurno();
	avanzaTurni(turniDaPassare_);
	turniDaPassare_ = 1;
}

void Partita::setTurno(int turno) {
	turno_ = turno;
}

int Partita::getNumeroGiocatori() const {
	return giocatori_.size();
}

const Giocatore& Partita::getGiocatore(int id) const {
	return *giocatori_[id];
}

void Partita::avanzaTurni(int turni) {
	for (int i = 0; i < turni; ++i) {
		do {
			turno_ = (turno_+1) % getNumeroGiocatori();
		} while (giocatori_[turno_]->haVinto());
	}
}

void Partita::pescaGiocatore(int id, int numCarte) const {
	if (giocatori_[id]->haVinto()) {
		pescaGiocatore((id+1) % getNumeroGiocatori(), numCarte);
		return;
	}
	giocatori_[id]->pesca(numCarte);
}

void Partita::aumentaTurniDaPassare() {
	turniDaPassare_++;
	int giocatoriAttivi = 0;
	for (int i = 0; i < getNumeroGiocatori(); ++i) {
		if (!giocatori_[i]->haVinto())
			giocatoriAttivi++;
	}
	turniDaPassare_ += turniDaPassare_/giocatoriAttivi;
}

const Carta& Partita::getCartaSulTavolo() const {
	return *cartaSulTavolo_;
}

void Partita::applicaCartaSulTavolo() {
	const CartaEffetto* ptr = dynamic_cast<const CartaEffetto*>(&(*cartaSulTavolo_));
	if (ptr) {
		ptr->applicaEffetto(this);
	}
}

int Partita::getTurno() const {
	return turno_;
}

DeepPtr<Carta> Partita::generaCarta() {
	if (generaRandom() % 10 == 0) {
		return DeepPtr<Carta>(new CartaSaltaTurno());
	}
	if (generaRandom() % 20 == 0) {
		return DeepPtr<Carta>(new CartaPescaDue());
	}
	if (generaRandom() % 30 == 0) {
		return DeepPtr<Carta>(new CartaPescaQuattro());
	}
	return DeepPtr<Carta>(new CartaNumero());
}

void Partita::aggiungiGiocatore() {
	if (giocatori_.empty()) {
		giocatori_.push_back(new Giocatore(0));
	} else {
		giocatori_.push_back(new GiocatoreCPU(0));
	}
}

void Partita::aggiungiCartaAllaMano(const DeepPtr<Carta>& carta, int idGiocatore) const {
	giocatori_[idGiocatore]->aggiungiCartaAllaMano(carta);
}

void Partita::setCartaSulTavolo(const DeepPtr<Carta>& carta) {
	cartaSulTavolo_ = carta;
}
