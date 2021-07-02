#ifndef GIOCATORE_H
#define GIOCATORE_H

#include "Lista.h"
#include "Carta.h"
#include "DeepPtr.h"

class Partita;
class Giocatore {
public:
	// Costruttore a 1 parametro col numero di carte iniziali
	Giocatore(int numCarte);
	
	// Distruttore virtuale per poliformismo
	virtual ~Giocatore();
	
	// Getter publici
	virtual const Carta& getCarta(int id) const;
	virtual int getNumeroCarteInMano() const;
	virtual bool haVinto() const;

	// Gioca la carta
	virtual void giocaCarta(int id, Partita* partita);
	virtual void giocaCarta(const Lista<DeepPtr<Carta>>::iterator& it, Partita* partita);
	
	// Finisce il turno pescando se non ha gettato carte in questo turno
	virtual void fineTurno();
	
	// Pesca n carte, default una
	virtual void pesca(int numCarte = 1);
	
	// Eccezioni
	class id_carta_out_of_range {};

	// Setter per caricare una partita
	virtual void aggiungiCartaAllaMano(const DeepPtr<Carta>& carta);

protected:
	// Una lista permette la rimozione in posizione arbitraria piu'
	// efficentemente di un vettore, il che utile dato che un giocatore puo'
	// giocare una carta da una qualsiasi "posizione" della sua mano
	Lista<DeepPtr<Carta>> mano_;
	bool haGettato_;
};

#endif
