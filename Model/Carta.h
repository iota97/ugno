#ifndef CARTA_H
#define CARTA_H

class Carta {
public:
	// Distruzione polimorfa
	virtual ~Carta();
	
	// Clonazione polimorfa virtuale
	virtual Carta* clone() const = 0;
	
	// Controlla che la carta sia giocabile sopra la carta passata
	virtual bool valida(const Carta& c) const = 0;
};

#endif
