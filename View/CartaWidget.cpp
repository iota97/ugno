#include "CartaWidget.h"

CartaWidget::CartaWidget(int idCarta, Controller* controller, QWidget* parent) : QPushButton(parent), idCarta_(idCarta), controller_(controller) {
	QVBoxLayout* mainLayout = new QVBoxLayout;
	setLayout(mainLayout);
	mainLayout->addSpacing(20);
	label_ = new QLabel();
	QFont font = label_->font();
	font.setPointSize(38);
	font.setBold(true);
	label_->setFont(font);
	label_->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(label_);
	mainLayout->addSpacing(20);
	resize(QSize(115,160));
	setFixedSize(size());
}

void CartaWidget::setColore(int colore) {
	switch(colore) {
	case 0:
		label_->setStyleSheet("color: rgb(200, 0, 0)");
		break;
	case 1:
		label_->setStyleSheet("color: rgb(200, 200, 0)");
		break;
	case 2:
		label_->setStyleSheet("color: rgb(0, 0, 200)");
		break;
	case 3:
		label_->setStyleSheet("color: rgb(0, 200, 0)");
		break;
	default:
		label_->setStyleSheet("color: rgb(0, 0, 0)");
		break;
	}
}

void CartaWidget::setText(const QString& text) {
	label_->setText(text);
}

void CartaWidget::gioca() const {
	controller_->giocaCarta(idCarta_);
}
