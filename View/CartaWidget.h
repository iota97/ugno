#ifndef CARTAWIDGET_H
#define CARTAWIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QString>

#include "../Controller/Controller.h"

class Controller;
class CartaWidget : public QPushButton {
	Q_OBJECT
private:
	QLabel* label_;	
	int idCarta_;
	Controller* controller_;
public:
	explicit CartaWidget(int idCarta = -1, Controller* controller = nullptr, QWidget *parent = nullptr);
	void setColore(int colore);
	void setText(const QString& text);

public slots:
	void gioca() const;
};

#endif
