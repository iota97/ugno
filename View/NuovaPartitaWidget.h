#ifndef NUOVAPARTITAWIDGET_H
#define NUOVAPARTITAWIDGET_H

#include <QPushButton>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QWidget>

#include "PartitaWidget.h"

class PartitaWidget;
class NuovaPartitaWidget : public QWidget {
	Q_OBJECT
public:
	explicit NuovaPartitaWidget(PartitaWidget *old = nullptr, QWidget *parent = nullptr);
};

#endif
