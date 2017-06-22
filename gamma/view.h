#ifndef WINDOW_H
#define WINDOW_H

#include "model.h"

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;
class QTextEdit;

class RecordTab : public QWidget {
	
	Q_OBJECT

	public :
		explicit RecordTab(QWidget * parent = 0);

	private slots :
		void updateRecordName(const QString & recordName);
		void connectToRecord();

	private :
		QString recordName;
		QString recordData;
		QLabel * recordLabel;
		QLineEdit * recordLine;
		QTextEdit * recordText;

		MonitorModel * model;
};

class Window : public QWidget {

	Q_OBJECT

	public : 
		explicit Window(QWidget * parent = 0);

	private slots :
		void addRecord();
		void removeRecord();
		
	private :
		QTabWidget * tabWidget;
		QPushButton * addRecordButton;
};

#endif /* WINDOW_H */
