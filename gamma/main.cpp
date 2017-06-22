
#include <iostream>
#include <QApplication>

#include "view.h"

int main (int argc, char **argv) {
	
	QApplication app(argc, argv);

	Window window;
	window.show();

	return app.exec();
}
