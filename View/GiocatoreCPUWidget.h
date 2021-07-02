#ifndef GIOCATORECPUWIDGET_H
#define GIOCATORECPUWIDGET_H

#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>

class GiocatoreCPUWidget : public QWidget {
	Q_OBJECT
private:
	QLabel* id_;
	QLabel* numeroCarte_;
public:
	explicit GiocatoreCPUWidget(int id, QWidget *parent = nullptr);
	void setNumeroCarte(int num);
	void setTurno(bool turno);
	void out();
};

#endif
