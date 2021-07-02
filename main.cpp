#include "View/PartitaWidget.h"
#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	MainMenuWidget* win = new MainMenuWidget();
	win->setAttribute(Qt::WA_DeleteOnClose);
	win->show();
	return app.exec();
}
