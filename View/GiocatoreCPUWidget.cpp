#include "GiocatoreCPUWidget.h"

GiocatoreCPUWidget::GiocatoreCPUWidget(int id, QWidget* parent) : QWidget(parent), id_(new QLabel()), numeroCarte_(new QLabel()) {
	QVBoxLayout* mainLayout = new QVBoxLayout;
	setLayout(mainLayout);
	mainLayout->addSpacing(20);
	QFont font = id_->font();
	font.setPointSize(12);
	font.setBold(true);
	id_->setFont(font);
	id_->setAlignment(Qt::AlignCenter);
	font = numeroCarte_->font();
	font.setPointSize(8);
	numeroCarte_->setFont(font);
	numeroCarte_->setAlignment(Qt::AlignCenter);
	mainLayout->addWidget(id_);
	mainLayout->addSpacing(10);
	mainLayout->addWidget(numeroCarte_);
	resize(QSize(210,130));
	setFixedSize(size());
	id_->setText(QString("Giocatore CPU # ") + QString::number(id));
}

void GiocatoreCPUWidget::setNumeroCarte(int num) {
	numeroCarte_->setText(QString("Carte in mano: ") + QString::number(num));
}

void GiocatoreCPUWidget::setTurno(bool turno) {
	id_->setStyleSheet(turno ? "color: rgb(200, 0, 0)" : "color: rgb(0, 0, 0)");
}

void GiocatoreCPUWidget::out() {
	delete id_;
	delete numeroCarte_;
	id_ = nullptr;
	numeroCarte_ = nullptr;
}
