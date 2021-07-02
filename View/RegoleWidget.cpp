#include "RegoleWidget.h"

RegoleWidget::RegoleWidget(QWidget *parent) : QWidget(parent) {
	setWindowTitle("Regole");
	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->setSpacing(0);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setAlignment(Qt::AlignCenter);
	QLabel* ugno = new QLabel("UGNO");
	QFont font = ugno->font();
	font.setPointSize(32);
	font.setBold(true);
	ugno->setFont(font);
	ugno->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(ugno);
	mainLayout->addSpacing(20);
	addRegole(mainLayout);
	setLayout(mainLayout);
	resize(QSize(640, 480));
}

void RegoleWidget::addRegole(QVBoxLayout* mainLayout) {
	QTextEdit* text = new QTextEdit();
	text->setReadOnly(true);
	text->setText(
		"<b>Giocatori</b><br>"
		"Il numero di giocatori è configurabile in un numero compreso tra 2 e 8. All'inizio "
		"della partita ogni giocatore ha in mano un numero di carte configurabile compreso tra 1 e 16.<br><br>"

		"<b>Turni</b><br>"
		"Il giocatore umano inizia per primo e si prosegue in senso orario, ad ogni turno un giocatore può gettare"
		"sul tavolo ogni carta compatibile con l'ultima gettata, a inizio partita è già presente una carta sul tavolo."
		"Se un giocatore non getta alcuna carta a fine turno pesca automaticamente una carta dal mazzo.<br><br>"

		"<b>Vittoria</b><br>"
		"Vince il giocatore che getta tutte le carte nella sua mano e rimane senza.<br><br>"

		"<b>Carte</b><br>"
		"Ci sono 2 tipi di carte: quelle numero e quelle effetto.<br><br>"

		"<b>Carte numero</b><br>"
		"Sono indicate da un numero compreso tra 1 e 9 colorato di rosso, giallo, blu o verde.<br>"
		"Sono giocabili sopra qualunque carta abbia lo stesso numero oppure lo stesso colore.<br><br>"

		"<b>Carta salta turno</b><br>"
		"Sono indicate dal simbolo S (salta) colorato di rosso, giallo, blu o verde.<br>"
		"Sono giocabili sopra una carta salta turno oppure qualunque carta abbia lo stesso colore.<br>"
		"<i>Effetto</i>: il giocatore successivo salta il turno, se ne vengono giocate più in un turno l'effetto si estende ai "
		"giocatori successivi al primo.<br><br>"

		"<b>Carta pesca due</b><br>"
		"Sono indicate dal simbolo D (due) colorato di rosso, giallo, blu o verde.<br>"
		"Sono giocabili sopra una carta pesca due oppure qualunque carta abbia lo stesso colore.<br>"
		"<i>Effetto</i>: il giocatore successivo pesca 2 carte dal mazzo.<br><br>"

		"<b>Carta pesca quattro</b><br>"
		"Sono indicate dal simbolo Q (quattro) di colore nero.<br>"
		"Sono giocabili sopra qualunque carta e qualunque carta è giocabile sopra di esse.<br>"
		"<i>Effetto</i>: il giocatore successivo pesca 4 carte dal mazzo.<br><br>"
	);
	mainLayout->addWidget(text);
}
