#ifndef REGOLEWIDGET_H
#define REGOLEWIDGET_H

#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QTextEdit>
#include <QWidget>

#include "RegoleWidget.h"

class RegoleWidget : public QWidget {
	Q_OBJECT
private:
	void addRegole(QVBoxLayout* mainLayout);
public:
	explicit RegoleWidget(QWidget *parent = nullptr);
};

#endif
