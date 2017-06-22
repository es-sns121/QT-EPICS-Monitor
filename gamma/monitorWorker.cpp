#include "monitorWorker.h"

#include <sstream>

#define MONITOR_ERR "Null monitor ptr passed to thread."
#define NULLSTR_ERR "Null string ptr passed to thread."

using namespace std;
using namespace epics::pvaClient;
using namespace epics::monitorWorker;

MonitorRunnable::MonitorRunnable (PvaClientMonitorPtr monitor,
								  string * recordData)
				: done(false), isDone(new epicsEvent), monitor(monitor), recordData(recordData)
{	
}

MonitorRunnable::~MonitorRunnable ()
{
	delete isDone;	
}

void MonitorRunnable::updateRecordData ()
{
	stringstream dumpStream;

	monitor->getData();
	
	monitorData->getPVStructure()->dumpValue(dumpStream);

	*recordData = dumpStream.str();
}

void MonitorRunnable::run () 
{
	monitorData = monitor->getData();
	while (true) {
		if (done)
			return; 
		
		monitor->waitEvent();
		
		if (done)
			return; 
		updateRecordData();

		monitor->releaseEvent();
	}
}

MonitorWorker::MonitorWorker (PvaClientMonitorPtr monitor, string * recordData)
			  : isSafe(true),
			    runnable(new MonitorRunnable(monitor, recordData)), 
			    thread(new epicsThread(*runnable, "MonitorWorkerThread", epicsThreadGetStackSize(epicsThreadStackSmall)))
{
	if (monitor == NULL) {
		isSafe = false;
		errorMsg.assign(MONITOR_ERR);
	}
	
	if (recordData == NULL) {
		isSafe = false;
		errorMsg.assign(NULLSTR_ERR);
	}
}

int MonitorWorker::start() 
{
	if (isSafe) {
		thread->start();
		return 0;
	}

	return -1;
}

void MonitorWorker::exit()
{
	if (thread) {
		runnable->setDone(true);
		thread->exitWait(.1);
	}
}
