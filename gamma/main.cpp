/*
 *	main.cpp
 *
 *	Main entry point of application. Starts a QApplication
 *	and instantiates a Window class. The app is then
 *	executed.
 */

#include <iostream>
#include <QApplication>

#include "view.h"

int main (int argc, char **argv) {
	
	QApplication app(argc, argv);

	Window window;
	window.show();

	return app.exec();
}
