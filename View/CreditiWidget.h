#ifndef CREDITIWIDGET_H
#define CREDITIWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include <QSpacerItem>
#include <QWidget>

#include "CreditiWidget.h"

class CreditiWidget : public QWidget {
	Q_OBJECT
public:
	explicit CreditiWidget(QWidget *parent = nullptr);
};

#endif
