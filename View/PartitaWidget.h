#ifndef PARTITAWIDGET_H
#define PARTITAWIDGET_H

#include <QAction>
#include <QFrame>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QXmlStreamWriter>
#include <QFile>
#include <QFileDialog>
#include <QSlider>
#include <QMessageBox>

#include "../Controller/Controller.h"
#include "CartaWidget.h"
#include "GiocatoreCPUWidget.h"
#include "NuovaPartitaWidget.h"
#include "MainMenuWidget.h"
#include "RegoleWidget.h"
#include "CreditiWidget.h"

class Controller;
class CartaWidget;
class PartitaWidget : public QWidget {
	Q_OBJECT
private:
	Controller* controller_;
	std::vector<GiocatoreCPUWidget*> giocatoriCPU_;
	std::vector<CartaWidget*> carteInMano_;
	QHBoxLayout* manoLayout_;
	CartaWidget* cartaSulTavolo_;
	QPushButton* fineTurnoButton_;
	QAction* salva_;

	void addMenu(QVBoxLayout* mainLayout);
    	void addGiocatoriCPU(QVBoxLayout* mainLayout);
    	void addTavolo(QVBoxLayout* mainLayout);
	void addMano(QVBoxLayout* mainLayout);
	void addControlli(QVBoxLayout* mainLayout);
	void buildLayout();
	void caricaXml(QFile& file);
	void salvaXml(QFile& file) const;

public:
	explicit PartitaWidget(QFile& file, bool* success = nullptr, QWidget *parent = nullptr);
	explicit PartitaWidget(int numeroGiocatori, int numeroCarte, QWidget *parent = nullptr);
	~PartitaWidget();
	void updateView();

	class file_corrotto {};
};

#endif
