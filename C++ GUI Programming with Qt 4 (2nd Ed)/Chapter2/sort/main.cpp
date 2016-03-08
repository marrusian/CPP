#include <QApplication>
#include "sortdialog.h"

int main(int argc, char *argv[])
{
	QApplication arg(argc, argv);

	SortDialog *dialog = new SortDialog;
	dialog->show();

	return arg.exec();
}