/*
 *	view.cpp
 *
 *	Implementations of RecordTab and Window
 *	member functions.
 *
 */

#include <sstream>

/* Class definitions */
#include "view.h"

/* Qt includes */
#include <QBoxLayout>
#include <QFuture>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTextEdit>
#include <QTimer>

/* Instantiate and format application's main window  */
Window::Window(QWidget * parent) 
	: QWidget(parent) 
{
/* Adds a record tab to the tab widget */
	addRecordButton = new QPushButton("Add Record");	
	addRecordButton->setFixedSize(100, 35);

/* Connects button to its action */
	connect(addRecordButton, SIGNAL (released()), this, SLOT (addRecord()));

	tabWidget = new QTabWidget;
	
	tabWidget->addTab(new RecordTab(this), tr("PV Record"));

/* Formatting */
	
	QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::LeftToRight); 
	
	mainLayout->addWidget(addRecordButton);
	mainLayout->setAlignment(addRecordButton, Qt::AlignLeft | Qt::AlignTop);
	
	mainLayout->addWidget(tabWidget);

	setLayout(mainLayout);

	setWindowTitle(tr("Record Tabs"));
}

/* Instantiates and formats a record tab */
RecordTab::RecordTab(QWidget * parent)
	: QWidget(parent)
{
	model = new MonitorModel;
	
	recordLabel = new QLabel(tr("Record Name:"));

/* Text box to type record name */
	recordLine = new QLineEdit;
		
	recordLine->setMaximumWidth(750);
	recordLine->setMinimumWidth(150);
	recordLine->setMaxLength(500);

/* Connect text box to its actions */
	connect(recordLine, SIGNAL (textEdited(QString)), this, SLOT (updateRecordName(QString)));
	connect(recordLine, SIGNAL (returnPressed()), this, SLOT (connectToRecord()));

/* Text box that record data will be displayed in */
	recordText = new QTextEdit;

	recordText->setReadOnly(true);
	recordText->setMaximumWidth(750);
	recordText->setMinimumWidth(150);

/* Button that removes the current record tab */
	QPushButton * removeRecordButton = new QPushButton("Remove Record");
	
	removeRecordButton->setFixedSize(130, 35);

/* Connect button to its action */
	connect(removeRecordButton, SIGNAL (released()), parent, SLOT (removeRecord()));

	QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);

/* Formatting */

	mainLayout->addWidget(recordLabel);
	mainLayout->addWidget(recordLine);
	mainLayout->addWidget(recordText);
	
	mainLayout->addWidget(removeRecordButton);
	mainLayout->setAlignment(removeRecordButton, Qt::AlignRight);

	setLayout(mainLayout);

/* To take advantage of the model's monitoring functionality the view is asked to
 * update the record data at a set polling rate of 250 milliseconds. */
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL (timeout()), this, SLOT (updateRecordData()));
	timer->start(250);
	
}

/* Adds a record tab to the tab widget */
void Window::addRecord()
{
	tabWidget->addTab(new RecordTab(this), tr("PV Record"));
}

/* Removes a record tab from the tab widget */
void Window::removeRecord()
{
	stopTab();
	tabWidget->removeTab(tabWidget->currentIndex());
}

/* Kills the thread currently running in the tab's model */
void Window::stopTab()
{
	RecordTab * currentTab = (RecordTab *)(tabWidget->currentWidget());
	
	currentTab->stop();
}

/* Update the tabs data with the requested record data. 'setText()' forces
 * a widget redraw. */
void RecordTab::updateRecordData() 
{
	std::string ret;
	ret = model->getRecordData();
	
	recordData = QString(ret.c_str());
	
	recordText->setText(recordData);
}

/* When any text is changed in the text box, update the record name to match */
void RecordTab::updateRecordName(const QString & recordName)
{
	this->recordName = recordName;
}

/* When return is pressed, connect to a record through the model */
void RecordTab::connectToRecord()
{
	if (!recordName.isEmpty()) {
		model->connect(recordName.toStdString());
	}

	updateRecordData();
}
