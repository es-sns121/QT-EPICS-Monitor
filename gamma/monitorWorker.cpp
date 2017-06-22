#include "monitorWorker.h"

#include <sstream>

#define MONITOR_ERR "Null monitor ptr passed to thread."
#define NULLSTR_ERR "Null string ptr passed to thread."

using namespace std;
using namespace epics::pvaClient;
using namespace epics::monitorWorker;

MonitorRunnable::MonitorRunnable (PvaClientMonitorPtr monitor, string * recordData)
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

	string dumpString = dumpStream.str();
	
/* Only update the data if its changed */
	if (*recordData != dumpString)
	*recordData = dumpStream.str();
}

void MonitorRunnable::run () 
{
	monitorData = monitor->getData();
	
	bool result(false);
/* return if 'done' is set. otherwise poll for new data. */
	while (true) {
		if (done)
			return; 
		
	/* Release every half second so the thread has a chance to quit without
	 * being updated */
		result = monitor->waitEvent(.5);
		
		if (done) {
			if (result)
				monitor->releaseEvent();
			return;
		}
		
		updateRecordData();
		
		if (result)
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

/* If safe, start the thread. */
int MonitorWorker::start() 
{
	if (isSafe) {
		thread->start();
		return 0;
	}

	return -1;
}

/* If the thread is allocated, set done to true. Give the 
 * thread a chance to exit. This is unlikely and the thread
 * will usually exit when the waitEvent times out and then
 * 'done' is evaluated."
 */
void MonitorWorker::exit()
{
	if (thread) {
		runnable->setDone(true);
		thread->exitWait(.1);
	}
}
