#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../Model/Partita.h"
#include "../Model/CartaNumero.h"
#include "../Model/CartaPescaDue.h"
#include "../Model/CartaPescaQuattro.h"
#include "../Model/CartaSaltaTurno.h"
#include "../View/PartitaWidget.h"

class PartitaWidget;

class Controller : public QObject {
	Q_OBJECT
private:
	PartitaWidget* qt_;
	Partita partita_;
	int speed_;
public:
	Controller(PartitaWidget* qt);
	Controller(PartitaWidget* qt, int numGiocatori, int numCarte);
	int getNumeroCarte(int giocatore) const;
	int getNumeroGiocatori() const;
	int getTurno() const;
	char cartaSulTavoloChar() const;
	int cartaSulTavoloColore() const;
	char cartaInManoChar(int idGiocatore, int idCarta) const;
	int cartaInManoColore(int idGiocatore, int idCarta) const;
	bool cartaInManoValida(int idGiocatore, int idCarta) const;
	void giocaCarta(int idCarta);
	bool haVinto(int id) const;
	void setCartaSulTavolo(char id, int colore);
	void aggiungiCartaAllaMano(char id, int colore, int idGiocatore);
	void aggiungiGiocatore();
	void setGameSpeed(int speed);
	static void setSeed(unsigned int seed);
	static unsigned int getSeed();

	class id_carta_sconosciuto {};

public slots:
	void fineTurno();
	void doAIStep();
};

#endif
