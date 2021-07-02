#include "PartitaWidget.h"

void PartitaWidget::addMenu(QVBoxLayout* mainLayout) {
	QMenuBar* menuBar = new QMenuBar(this);

	// Menu File (Nuova, Carica, Salva, Esci)
	QMenu* file = new QMenu("File", menuBar);
	menuBar->addMenu(file);
	QAction* nuova = new QAction("Nuova Partita", file);
	QAction* carica = new QAction("Carica Partita", file);
	salva_ = new QAction("Salva Partita", file);
	QAction* esci = new QAction("Esci", file);
	file->addAction(nuova);
	file->addAction(carica);
	file->addAction(salva_);
	file->addAction(esci);
	menuBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	mainLayout->addWidget(menuBar);

	connect(nuova, &QAction::triggered, [=]() {
		NuovaPartitaWidget* win = new NuovaPartitaWidget(this);
		win->setAttribute(Qt::WA_DeleteOnClose);
		win->show();
	});

	connect(carica, &QAction::triggered, [=]() {
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

	connect(salva_, &QAction::triggered, [=]() {
		QString fileName = QFileDialog::getSaveFileName(this, "Salva Partita", "./", "Partite Salvate (*.xml)");
		if (fileName.isEmpty()) return;
		if (!fileName.endsWith(".xml", Qt::CaseInsensitive)) {
			fileName.append(".xml");
		}
		QFile file(fileName);
		salvaXml(file);
	});

	connect(esci, &QAction::triggered, [=]() {
		close();
	});

	// Menu Aiuto (Regole, Crediti)
	QMenu* aiuto = new QMenu("Aiuto", menuBar);
	menuBar->addMenu(aiuto);
	QAction* regole = new QAction("Regole", aiuto);
	QAction* crediti = new QAction("Crediti", aiuto);
	aiuto->addAction(regole);
	aiuto->addAction(crediti);
	
	connect(regole, &QAction::triggered, [=]() {
		RegoleWidget* win = new RegoleWidget();
		win->setAttribute(Qt::WA_DeleteOnClose);
		win->show();
	});
	connect(crediti, &QAction::triggered, [=]() {
		CreditiWidget* win = new CreditiWidget();
		win->setAttribute(Qt::WA_DeleteOnClose);
		win->show();
	});
}

void PartitaWidget::addMano(QVBoxLayout* mainLayout) {
	QWidget* scrollAreaWidget = new QWidget;
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(scrollAreaWidget);
	manoLayout_ = new QHBoxLayout(scrollAreaWidget);
	mainLayout->addWidget(scrollArea);
}

void PartitaWidget::addGiocatoriCPU(QVBoxLayout* mainLayout) {
	QWidget* scrollAreaWidget = new QWidget;
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(scrollAreaWidget);
	QHBoxLayout* screenLayout = new QHBoxLayout(scrollAreaWidget);
    	for (int i = 1; i < controller_->getNumeroGiocatori(); ++i) {
		giocatoriCPU_.push_back(new GiocatoreCPUWidget(i));
		screenLayout->addWidget(giocatoriCPU_[i-1]);
	}
	screenLayout->setSpacing(0);
	mainLayout->addWidget(scrollArea);
}

void PartitaWidget::addTavolo(QVBoxLayout* mainLayout) {
	QHBoxLayout* screenLayout = new QHBoxLayout;
	screenLayout->setAlignment(Qt::AlignCenter);
	cartaSulTavolo_ = new CartaWidget();
	cartaSulTavolo_->setEnabled(false);
	screenLayout->addWidget(cartaSulTavolo_);
	mainLayout->addLayout(screenLayout);
}

void PartitaWidget::addControlli(QVBoxLayout* mainLayout) {
	QVBoxLayout* controlsLayout = new QVBoxLayout;
	controlsLayout->setAlignment(Qt::AlignVCenter);
	controlsLayout->setContentsMargins(50, 10, 50, 10);
	controlsLayout->setSpacing(15);
	fineTurnoButton_ = new QPushButton("Fine turno");
	fineTurnoButton_->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	controlsLayout->addWidget(fineTurnoButton_);
	controlsLayout->setAlignment(fineTurnoButton_, Qt::AlignCenter);
	QLabel* label = new QLabel("Velocità partita");
	controlsLayout->addWidget(label);
	controlsLayout->setAlignment(label, Qt::AlignCenter);
	QSlider* slider = new QSlider();
	slider->setOrientation(Qt::Horizontal);
	slider->setMinimum(1);
	slider->setMaximum(100);
	slider->setValue(30);
	controlsLayout->addWidget(slider);
	mainLayout->addLayout(controlsLayout);
	connect(fineTurnoButton_, SIGNAL(pressed()), controller_, SLOT(fineTurno()));
	connect(slider, &QSlider::valueChanged, [=]() {
		controller_->setGameSpeed(slider->value());
	});
}

void PartitaWidget::buildLayout() {
	setWindowTitle("Ugno");

	QVBoxLayout* mainLayout = new QVBoxLayout;
	
	QWidget* scrollAreaWidget = new QWidget;
	QScrollArea* scrollArea = new QScrollArea;
	scrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	scrollArea->setWidgetResizable(true);
	scrollArea->setWidget(scrollAreaWidget);
	QVBoxLayout* scrollLayout = new QVBoxLayout(scrollAreaWidget);

	addMenu(mainLayout);
	addGiocatoriCPU(scrollLayout);
	addTavolo(scrollLayout);
	addMano(scrollLayout);
	addControlli(scrollLayout);

	mainLayout->addWidget(scrollArea);
	mainLayout->setSpacing(0);
	mainLayout->setContentsMargins(0, 0, 0, 0);
	scrollLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(mainLayout);
	resize(QSize(1024, 720));
	updateView();
}

PartitaWidget::PartitaWidget(int numeroGiocatori, int numeroCarte, QWidget* parent) : QWidget(parent), controller_(new Controller(this, numeroGiocatori, numeroCarte)) {
	buildLayout();
}

PartitaWidget::PartitaWidget(QFile& file, bool* success, QWidget* parent) : QWidget(parent), controller_(new Controller(this)) {
	// Parsing del file XML, se da errore chiude tutto
	try {
		caricaXml(file);
	} catch (...) {
		if (success) {
			*success = false;
		}
		QMessageBox messageBox;
		messageBox.critical(0, "Errore", "File di salvataggio corrotto!");
		messageBox.setFixedSize(500, 200);
		setAttribute(Qt::WA_DeleteOnClose);
		close();
		return;
	}
	if (success) {
		*success = true;
	}
	buildLayout();
}

PartitaWidget::~PartitaWidget() {
	delete controller_;
}

void PartitaWidget::updateView() {
	// Disabilita le azioni quando non è il turno corretto
	fineTurnoButton_->setEnabled(controller_->getTurno() == 0);
	salva_->setEnabled(controller_->getTurno() == 0);
	
	// Carta sul Tavolo
	cartaSulTavolo_->setText(QChar(controller_->cartaSulTavoloChar()));
	cartaSulTavolo_->setColore(controller_->cartaSulTavoloColore());

	// Aggiorna i giocatori CPU
	for (int i = 1; i < controller_->getNumeroGiocatori(); ++i) {
		if (!controller_->haVinto(i)) {
			giocatoriCPU_[i-1]->setNumeroCarte(controller_->getNumeroCarte(i));
			giocatoriCPU_[i-1]->setTurno(controller_->getTurno() == i);
		} else {
			giocatoriCPU_[i-1]->out();
		}
	}

	// Numero carte in mano al giocatore
	int carteInManoOld = carteInMano_.size();
	if (carteInManoOld < controller_->getNumeroCarte(0)) {
		for (int i = 0; i < controller_->getNumeroCarte(0)-carteInManoOld; ++i) {
			carteInMano_.push_back(new CartaWidget(carteInManoOld+i, controller_));
			manoLayout_->addWidget(carteInMano_[carteInManoOld+i]);
			connect(carteInMano_[carteInManoOld+i], SIGNAL(pressed()), carteInMano_[carteInManoOld+i], SLOT(gioca()));
		}
	} else if (carteInManoOld > controller_->getNumeroCarte(0)) {
		for (int i = 0; i < carteInManoOld-controller_->getNumeroCarte(0); ++i) {
			delete carteInMano_[carteInManoOld-1-i];
			carteInMano_.pop_back();
		}
	}

	// Carte in mano
	for (int i = 0; i < controller_->getNumeroCarte(0); ++i) {
		carteInMano_[i]->setText(QChar(controller_->cartaInManoChar(0, i)));
		carteInMano_[i]->setColore(controller_->cartaInManoColore(0, i));
		carteInMano_[i]->setEnabled(controller_->getTurno() == 0 && controller_->cartaInManoValida(0, i));
	}

	// Fine partita check
	int count = 1;
	for (int i = 1; i < controller_->getNumeroGiocatori(); ++i) {
		if (controller_->haVinto(i))
			++count;
	}
	if (count == controller_->getNumeroGiocatori() || controller_->haVinto(0)) {
		MainMenuWidget* win = new MainMenuWidget(count);
		win->setAttribute(Qt::WA_DeleteOnClose);
		win->show();
		close();
	}
}

void PartitaWidget::caricaXml(QFile& file) {
	file.open(QIODevice::ReadOnly);
	QXmlStreamReader r(&file);
	int idGiocatore = 0;
	if (r.readNextStartElement() && r.name() == "partita") {
		while (r.readNextStartElement()) {
			if (r.name() == "giocatore") {
				controller_->aggiungiGiocatore();
	   			while (r.readNextStartElement()) {
					if (r.name() == "carta") {
						char tipo = 'x';
						int colore = -2;
						while (r.readNextStartElement()) {
							if (r.name() == "tipo") {
					    			tipo = r.readElementText().toStdString().c_str()[0];
							} else if (r.name() == "colore") {
								char tmp = r.readElementText().toStdString().c_str()[0];
								switch (tmp) {
								case 'N':
									colore = -1;
									break;
								case '0':
								case '1':
								case '2':
								case '3':
									colore = tmp-'0';
									break;
								default:
									throw file_corrotto();
								}
							} else {
								throw file_corrotto();
							}
						}
						controller_->aggiungiCartaAllaMano(tipo, colore, idGiocatore);
					} else {
						throw file_corrotto();
					}
				}
				idGiocatore++;
			} else if (r.name() == "tavolo") {
				char tipo = 'x';
				int colore = -2;
				while (r.readNextStartElement()) {
					if (r.name() == "tipo") {
				    		tipo = r.readElementText().toStdString().c_str()[0];
					} else if (r.name() == "colore") {
						char tmp = r.readElementText().toStdString().c_str()[0];
						switch (tmp) {
						case 'N':
							colore = -1;
							break;
						case '0':
						case '1':
						case '2':
						case '3':
							colore = tmp-'0';
							break;
						default:
							throw file_corrotto();
						}
					} else {
						throw file_corrotto();
					}
				}
				controller_->setCartaSulTavolo(tipo, colore);
			} else if (r.name() == "seed") {
				Controller::setSeed(r.readElementText().toInt());
			} else {
				throw file_corrotto();
			}
		}
	} else {
		throw file_corrotto();
	}
}

void PartitaWidget::salvaXml(QFile& file) const {
	file.open(QIODevice::WriteOnly);
	QXmlStreamWriter w(&file);
	w.writeStartDocument();
	w.writeStartElement("partita");
	w.writeTextElement("seed", QString::number(Controller::getSeed()));
	w.writeStartElement("tavolo");
	w.writeTextElement("tipo", QString(QChar(controller_->cartaSulTavoloChar())));
	if (controller_->cartaSulTavoloColore() != -1) {
		w.writeTextElement("colore", QString::number(controller_->cartaSulTavoloColore()));
	} else {
		w.writeTextElement("colore", "N");
	}
	w.writeEndElement();
	for (int i = 0; i < controller_->getNumeroGiocatori(); ++i) {
		w.writeStartElement("giocatore");
		for (int j = 0; j < controller_->getNumeroCarte(i); ++j) {
			w.writeStartElement("carta");
			w.writeTextElement("tipo", QString(QChar(controller_->cartaInManoChar(i, j))));
			if (controller_->cartaInManoColore(i, j) != -1) {
				w.writeTextElement("colore", QString::number(controller_->cartaInManoColore(i, j)));
			} else {
				w.writeTextElement("colore", "N");
			}
			w.writeEndElement();
		}
		w.writeEndElement();
	}
	w.writeEndElement();
	w.writeEndDocument();
}
