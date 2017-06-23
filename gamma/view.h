#ifndef VIEW_H
#define VIEW_H

/*
 *	view.h
 *
 * 	Class definitions for the application's view.
 * 	The view consists of a 'Window' which has a
 * 	TabWidget. This TabWidget is populated with
 * 	RecordTabs, each of which is capable of 
 * 	connecting to a pvRecord that is hosted on 
 * 	an EPICS v4 database. The application lacks 
 * 	a monolithic model as the data retrieved is 
 * 	relevant to the that tab alone. The connection 
 * 	is handled by the tab's model. Each tab has its 
 * 	own model.
 *
 */

#include "model.h"

#include <QWidget>

class QLabel;
class QLineEdit;
class QPushButton;
class QTabWidget;
class QTextEdit;

class RecordTab;
class Window;

class RecordTab : public QWidget {
	
	Q_OBJECT

	public :
		explicit RecordTab(QWidget * parent = 0);
	/* Stops the model's thread */
		void stop() { model->stop(); }
	
	private slots :
		void updateRecordName(const QString & recordName);
		void connectToRecord();
		void updateRecordData();

	private :
		QString recordName;
		QString recordData;
		QLabel * recordLabel;
	/* Text box that record name is entered in */
		QLineEdit * recordLine;
	/* Text box that record data is displayed in */
		QTextEdit * recordText;

		MonitorModel * model;

	friend class Window;
};

/* Application's main window. */
class Window : public QWidget {

	Q_OBJECT

	public : 
		explicit Window(QWidget * parent = 0);

/* Add and remove record tabs */
	private slots :
		void addRecord();
		void removeRecord();
	
	private :
	/* Hosts the RecordTabs */
		QTabWidget * tabWidget;
	/* Calls RecordTab::stop() to stop the thread running in the tab */
		void stopTab();
		QPushButton * addRecordButton;
};

#endif /* VIEW_H */
