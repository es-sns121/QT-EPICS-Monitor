#ifndef MONITORWORKER_H
#define MONITORWORKER_H

/*
 *	monitorWorker.h
 *
 *	Class definitions of the application's
 *	worker thread and the runnable that the
 *	thread executes.
 *
 */

#include <pv/pvaClient.h>
#include <epicsThread.h>

namespace epics { namespace monitorWorker {

/* Runnable that the thread will execute */
class MonitorRunnable : public epicsThreadRunable {
	public:
		MonitorRunnable(epics::pvaClient::PvaClientMonitorPtr monitor,
					    std::string * recordData);
	/* Code thread will execute */
		void run();
		void setDone(const bool & b) { done = b; }
	
	private:
		void updateRecordData();
	/* Status of whether the runnable should stop or not. */
		bool done;
	
		epics::pvaClient::PvaClientMonitorPtr     monitor;
		epics::pvaClient::PvaClientMonitorDataPtr monitorData;
	
		std::string * recordData;
};

/* Wrapper around the thread and runnable */
class MonitorWorker {
	public:
		MonitorWorker(epics::pvaClient::PvaClientMonitorPtr monitor,
					  std::string * recordData);
	/* Starts the thread */
		int start();
	/* Stops the thread */
		void exit();
		
		std::string getErrMsg () { return errorMsg; }	
	
	private:
	/* Status of whether the thread should start */
		bool isSafe;
	
		std::string errorMsg;
	
		MonitorRunnable * runnable;
		epicsThread * thread;
};

}} /* namespace epics, monitorWorker */

#endif /* MONITORWORKER_H */
