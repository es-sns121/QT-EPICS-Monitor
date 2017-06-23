/*
 *	monitorWorker.cpp
 *
 *	Implementations for monitorRunnable and monitorWorker
 *	member functions.
 *
 */

#include "monitorWorker.h"

#include <sstream>

#define MONITOR_ERR "Null monitor ptr passed to thread."
#define NULLSTR_ERR "Null string ptr passed to thread."

using namespace std;
using namespace epics::pvaClient;
using namespace epics::monitorWorker;

MonitorRunnable::MonitorRunnable (PvaClientMonitorPtr monitor, string * recordData)
				: done(false), monitor(monitor), recordData(recordData)
{	
}

/* Update the runnable's copy of the record's data */
void MonitorRunnable::updateRecordData ()
{
	stringstream dumpStream;

	monitor->getData();
	
	monitorData->getPVStructure()->dumpValue(dumpStream);

	string dumpString = dumpStream.str();
	
/* Only update the data if its changed */
	if (*recordData != dumpString)
	*recordData = dumpString;
}

/* Monitor the record's data. Update if it changes. Poll to check if thread should exit.  */
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
	
	/* If an event occured it must be released before the thread exits */
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

/* Instantiate members and check if conditions to start the runnable are met.  */
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
 * 'done' is evaluated in MonitorRunnable::run().
 */
void MonitorWorker::exit()
{
	if (this != NULL) {
		runnable->setDone(true);
		thread->exitWait(.1);
	}
}
