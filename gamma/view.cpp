
#include <sstream>

// Class definitions
#include "view.h"

// Qt includes
#include <QLabel>
#include <QBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTextEdit>

Window::Window(QWidget * parent) 
	: QWidget(parent) 
{
	addRecordButton = new QPushButton("Add Record");	
	addRecordButton->setFixedSize(100, 35);

	connect(addRecordButton, SIGNAL (released()), this, SLOT (addRecord()));

	tabWidget = new QTabWidget;
	
	tabWidget->addTab(new RecordTab(this), tr("PV Record"));

	QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::LeftToRight); 
	
	mainLayout->addWidget(addRecordButton);
	mainLayout->setAlignment(addRecordButton, Qt::AlignLeft | Qt::AlignTop);
	
	mainLayout->addWidget(tabWidget);

	setLayout(mainLayout);

	setWindowTitle(tr("Record Tabs"));
}

RecordTab::RecordTab(QWidget * parent)
	: QWidget(parent)
{
	model = new MonitorModel;
	
	recordLabel = new QLabel(tr("Record Name:"));
	
	recordLine = new QLineEdit;
		
	recordLine->setMaximumWidth(750);
	recordLine->setMinimumWidth(150);
	recordLine->setMaxLength(500);

	connect(recordLine, SIGNAL (textEdited(QString)), this, SLOT (updateRecordName(QString)));
	connect(recordLine, SIGNAL (returnPressed()), this, SLOT (connectToRecord()));

	recordText = new QTextEdit;

	recordText->setReadOnly(true);
	recordText->setMaximumWidth(750);
	recordText->setMinimumWidth(150);
	
	QPushButton * removeRecordButton = new QPushButton("Remove Record");
	
	removeRecordButton->setFixedSize(130, 35);

	connect(removeRecordButton, SIGNAL (released()), parent, SLOT (removeRecord()));

	QBoxLayout *mainLayout = new QBoxLayout(QBoxLayout::TopToBottom);

	mainLayout->addWidget(recordLabel);
	mainLayout->addWidget(recordLine);
	mainLayout->addWidget(recordText);
	
	mainLayout->addWidget(removeRecordButton);
	mainLayout->setAlignment(removeRecordButton, Qt::AlignRight);

	setLayout(mainLayout);

}

void Window::addRecord()
{
	tabWidget->addTab(new RecordTab(this), tr("PV Record"));
}

void Window::removeRecord()
{
	tabWidget->removeTab(tabWidget->currentIndex());
}

void RecordTab::updateRecordName(const QString & recordName)
{
	this->recordName = recordName;
}

void RecordTab::connectToRecord()
{
	std::string ret;
	
	if (!recordName.isEmpty()) {
		model->connect(recordName.toStdString());
		ret = model->getRecordData();
	}
	
	recordData = QString(ret.c_str());

	recordText->setText(recordData);
}
