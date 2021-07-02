#ifndef PARTITA_H
#define PARTITA_H

#include "DeepPtr.h"
#include "Giocatore.h"
#include "GiocatoreCPU.h"

#include <vector>

// Classe partita, tutti i giocatori escluso il primo di indice 0 sono controllati dal computer
class Partita {
public:
	// Costruttore di default, da usare insieme alle funzioni per caricare una partita
	Partita();

	// Costruttore a 2 parametri, numero di giocatori totali e carte in mano a ogni giocatore all'inizio
	Partita(int numGiocatori, int numCarteIniziali);
	
	// Distruttore
	virtual ~Partita();

	// Giocata la carta di indice idCarta nella mano del giocatore umano, ritorna false se la carta non è giocabile
	// con quella correntemente sul tavolo
	virtual bool playerGiocaCarta(int idCarta);

	// Finisce il turno del giocatore umano, pesca automaticamente una carta se in questo turno non ha buttato alcuna carta
	virtual void playerFineTurno();

	// Avanza di una mossa i giocatori controllati dal computer
	virtual void eseguiStepGiocatoreCPU();

	// Getter publici
	virtual const Giocatore& getGiocatore(int id) const;
	virtual const Carta& getCartaSulTavolo() const;
	virtual int getNumeroGiocatori() const;
	virtual int getTurno() const;
	
	// Funzioni per ausiliari per carte effetto
	virtual void applicaCartaSulTavolo();
	virtual void setTurno(int turno);
	virtual void pescaGiocatore(int id, int numCarte) const;
	virtual void aumentaTurniDaPassare();
	virtual void avanzaTurni(int turni);
	
	// Funzione statica che genera una carta, al fine di pescare e per non permettere di contare le carte
	// si genera random una carta al posto di avere un mazzo
	static DeepPtr<Carta> generaCarta();

	// Helper per caricare una partita e giocare le carte
	virtual void setCartaSulTavolo(const DeepPtr<Carta>& carta);
	virtual void aggiungiCartaAllaMano(const DeepPtr<Carta>& carta, int idGiocatore) const;
	virtual void aggiungiGiocatore();
	
	// Eccezioni
	class turno_giocatore_non_controllato_dalla_cpu {};
	class non_e_il_turno_del_giocatore {};

protected:
	// std::vector risulta piu' efficace della Lista dato che permette accesso casuale e il numero dei giocatori
	// rimane invariato durante la partita
	std::vector<Giocatore*> giocatori_;
	DeepPtr<Carta> cartaSulTavolo_;
	int turno_;
	int turniDaPassare_;
};

#endif
