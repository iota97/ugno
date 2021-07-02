#include "Controller.h"
#include "../Model/Random.h"
#include <QTimer>
#include <typeinfo>

Controller::Controller(PartitaWidget* qt, int numGiocatori, int numCarte) : qt_(qt), partita_(numGiocatori, numCarte), speed_(30) {}

Controller::Controller(PartitaWidget* qt) : qt_(qt), speed_(30) {}

void Controller::fineTurno() {
	partita_.playerFineTurno();
	qt_->updateView();
	doAIStep();
}

int Controller::getTurno() const {
	return partita_.getTurno();
}

bool Controller::haVinto(int id) const {
	return partita_.getGiocatore(id).haVinto();
}

void Controller::setGameSpeed(int speed) {
	speed_ = speed;
}

void Controller::doAIStep() {
	if (partita_.getTurno() != 0) {
		partita_.eseguiStepGiocatoreCPU();
		qt_->updateView();
		QTimer::singleShot(30000/(speed_+10), this, SLOT(doAIStep()));
	}
}

int Controller::getNumeroCarte(int giocatore) const {
	return partita_.getGiocatore(giocatore).getNumeroCarteInMano();
}

int Controller::getNumeroGiocatori() const {
	return partita_.getNumeroGiocatori();
}

char Controller::cartaSulTavoloChar() const {
	const Carta& c = partita_.getCartaSulTavolo();	
	if (typeid(c) == typeid(CartaNumero)) {
		auto aux = dynamic_cast<const CartaNumero&>(c);
		return aux.getNumero()+'0';
	} else if (typeid(c) == typeid(CartaSaltaTurno)) {
		return 'S';
	} else if (typeid(c) == typeid(CartaPescaDue)) {
		return 'D';
	} else if (typeid(c) == typeid(CartaPescaQuattro)) {
		return 'Q';
	}
	return 'x';
}

int Controller::cartaSulTavoloColore() const {
	const Carta& c = partita_.getCartaSulTavolo();
	auto aux = dynamic_cast<const CartaColore*>(&c);
	if (aux) {
		return aux->getColore();
	}
	return -1;
}

char Controller::cartaInManoChar(int idGiocatore, int idCarta) const {
	const Carta& c = partita_.getGiocatore(idGiocatore).getCarta(idCarta);
	if (typeid(c) == typeid(CartaNumero)) {
		auto aux = dynamic_cast<const CartaNumero&>(c);
		return aux.getNumero()+'0';
	} else if (typeid(c) == typeid(CartaSaltaTurno)) {
		return 'S';
	} else if (typeid(c) == typeid(CartaPescaDue)) {
		return 'D';
	} else if (typeid(c) == typeid(CartaPescaQuattro)) {
		return 'Q';
	}
	return 'x';
}

int Controller::cartaInManoColore(int idGiocatore, int idCarta) const {
	const Carta& c = partita_.getGiocatore(idGiocatore).getCarta(idCarta);
	auto aux = dynamic_cast<const CartaColore*>(&c);
	if (aux) {
		return aux->getColore();
	}
	return -1;
}

void Controller::setCartaSulTavolo(char id, int colore) {
	switch (id) {
	case 'S':
		partita_.setCartaSulTavolo(DeepPtr<Carta>(new CartaSaltaTurno(colore)));
		break;
	case 'D':
		partita_.setCartaSulTavolo(DeepPtr<Carta>(new CartaPescaDue(colore)));
		break;
	case 'Q':
		partita_.setCartaSulTavolo(DeepPtr<Carta>(new CartaPescaQuattro()));
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		partita_.setCartaSulTavolo(DeepPtr<Carta>(new CartaNumero(id-'0', colore)));
		break;
	default:
		throw id_carta_sconosciuto();
	}
}

void Controller::aggiungiCartaAllaMano(char id, int colore, int idGiocatore) {
	switch (id) {
	case 'S':
		partita_.aggiungiCartaAllaMano(DeepPtr<Carta>(new CartaSaltaTurno(colore)), idGiocatore);
		break;
	case 'D':
		partita_.aggiungiCartaAllaMano(DeepPtr<Carta>(new CartaPescaDue(colore)), idGiocatore);
		break;
	case 'Q':
		partita_.aggiungiCartaAllaMano(DeepPtr<Carta>(new CartaPescaQuattro()), idGiocatore);
		break;
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		partita_.aggiungiCartaAllaMano(DeepPtr<Carta>(new CartaNumero(id-'0', colore)), idGiocatore);
		break;
	default:
		throw id_carta_sconosciuto();
	}
}

void Controller::aggiungiGiocatore() {
	partita_.aggiungiGiocatore();
}

bool Controller::cartaInManoValida(int idGiocatore, int idCarta) const {
	return partita_.getGiocatore(idGiocatore).getCarta(idCarta).valida(partita_.getCartaSulTavolo());
}

void Controller::giocaCarta(int idCarta) {
	partita_.playerGiocaCarta(idCarta);
	qt_->updateView();
}

void Controller::setSeed(unsigned int seed) {
	setRandomSeed(seed);
}

unsigned int Controller::getSeed() {
	return getRandomSeed();
}
