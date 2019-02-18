#include "snipertool.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SniperTool w;
	w.show();
	return a.exec();
}
