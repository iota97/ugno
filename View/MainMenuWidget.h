#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>

#include "PartitaWidget.h"
class MainMenuWidget : public QWidget {
	Q_OBJECT
public:
	explicit MainMenuWidget(int posizione = 0, QWidget *parent = nullptr);
};

#endif
