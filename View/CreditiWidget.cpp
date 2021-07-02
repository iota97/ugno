#include "CreditiWidget.h"

CreditiWidget::CreditiWidget(QWidget *parent) : QWidget(parent) {
	setWindowTitle("Crediti");

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

	QLabel* creato = new QLabel("Creato da:");
	font.setPointSize(12);
	font.setBold(false);
	creato->setFont(font);
	creato->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(creato);
	mainLayout->addSpacing(10);


	QLabel* autori = new QLabel("Giovanni Cocco\nMatteo Noro");
	font.setPointSize(10);
	font.setItalic(true);
	autori->setFont(font);
	autori->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(autori);	

	setLayout(mainLayout);
	resize(QSize(320, 240));
	setFixedSize(size());
}
