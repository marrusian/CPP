#include <QApplication>
#include "gtcd.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	GTCD *dialog = new GTCD;
	dialog->show();

	return app.exec();
}