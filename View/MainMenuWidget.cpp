#include "MainMenuWidget.h"

MainMenuWidget::MainMenuWidget(int posizione, QWidget *parent) : QWidget(parent) {
	setWindowTitle("Ugno");

	QVBoxLayout* controlsLayout = new QVBoxLayout;
	controlsLayout->setSpacing(10);
	controlsLayout->setContentsMargins(50, 50, 50, 50);
	controlsLayout->setAlignment(Qt::AlignCenter);

	if (posizione > 0) {
		QLabel* over = new QLabel("GAME OVER");
		QFont font = over->font();
		font.setPointSize(20);
		font.setBold(true);
		over->setFont(font);
		over->setAlignment(Qt::AlignCenter);
		over->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		controlsLayout->addWidget(over);

		QLabel* pos = new QLabel("Sei arrivato #"+QString::number(posizione));
		font = pos->font();
		font.setPointSize(16);
		pos->setFont(font);
		pos->setAlignment(Qt::AlignCenter);
		pos->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		controlsLayout->addWidget(pos);
	} else {
		QLabel* title = new QLabel("UGNO");
		QFont font = title->font();
		font.setPointSize(56);
		font.setBold(true);
		title->setFont(font);
		title->setAlignment(Qt::AlignCenter);
		title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		controlsLayout->addWidget(title);
	}	

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
	QPushButton* ok = new QPushButton("Nuova");
	buttonLayout->addWidget(ok);

	QPushButton* carica = new QPushButton("Carica");
	buttonLayout->addWidget(carica);

	QPushButton* cancel = new QPushButton("Esci");
	buttonLayout->addWidget(cancel);
	controlsLayout->addLayout(buttonLayout);

	setLayout(controlsLayout);
	resize(QSize(500, 400));
	setFixedSize(size());

	connect(ok, &QPushButton::pressed, [=]() {
		PartitaWidget* win = new PartitaWidget(numGiocatori->value(), numCarte->value());
		win->setAttribute(Qt::WA_DeleteOnClose);
		win->show();
		close();
	});

	connect(carica, &QPushButton::pressed, [=]() {
		QString fileName = QFileDialog::getOpenFileName(this, "Carica Partita", "./", "Partite Salvate (*.xml)");
		if (fileName.isEmpty()) return;
	    	QFile file(fileName);
		bool success;
		PartitaWidget* win = new PartitaWidget(file, &success);
		if (success) {
			win->setAttribute(Qt::WA_DeleteOnClose);
			win->show();
			close();
		}
	});

	connect(cancel, &QPushButton::pressed, [=]() {
		close();
	});
}
