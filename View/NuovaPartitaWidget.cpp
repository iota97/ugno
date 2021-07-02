#include "NuovaPartitaWidget.h"

NuovaPartitaWidget::NuovaPartitaWidget(PartitaWidget* old, QWidget *parent) : QWidget(parent) {
	setWindowTitle("Nuova Partita");
	QVBoxLayout* controlsLayout = new QVBoxLayout;
	controlsLayout->setSpacing(10);
	controlsLayout->setContentsMargins(30, 30, 30, 30);
	controlsLayout->setAlignment(Qt::AlignCenter);

	controlsLayout->addWidget(new QLabel("Numero giocatori: "));
	QSpinBox* numGiocatori = new QSpinBox();
	numGiocatori->setRange(2, 8);
	numGiocatori->setValue(4);
	controlsLayout->addWidget(numGiocatori);

	controlsLayout->addWidget(new QLabel("Numero carte iniziali: "));
	QSpinBox* numCarte = new QSpinBox();
	numCarte->setRange(1, 16);
	numCarte->setValue(7);
	controlsLayout->addWidget(numCarte);

	QHBoxLayout* buttonLayout = new QHBoxLayout;
	QPushButton* ok = new QPushButton("OK");
	buttonLayout->addWidget(ok);
	QPushButton* cancel = new QPushButton("Annulla");
	buttonLayout->addWidget(cancel);
	controlsLayout->addLayout(buttonLayout);

	setLayout(controlsLayout);
	resize(QSize(300, 220));
	setFixedSize(size());

	connect(ok, &QPushButton::pressed, [=]() {
		PartitaWidget* win = new PartitaWidget(numGiocatori->value(), numCarte->value());
		win->setAttribute(Qt::WA_DeleteOnClose);
		win->show();
		if (old) {
			old->close();
		}
		close();
	});
	connect(cancel, &QPushButton::pressed, [=]() {
		close();
	});
}
