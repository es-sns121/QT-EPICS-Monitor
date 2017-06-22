#ifndef MONITORWORKER_H
#define MONITORWORKER_H

#include <pv/pvaClient.h>
#include <epicsEvent.h>
#include <epicsThread.h>

namespace epics { namespace monitorWorker {

class MonitorRunnable : public epicsThreadRunable {
	public:
		MonitorRunnable(epics::pvaClient::PvaClientMonitorPtr monitor,
					    std::string * recordData);
		
		~MonitorRunnable();

		void run();
		void wait() { isDone->wait(); }
		void setDone(const bool & b) { done = b; }
	private:
		void updateRecordData();
	
		bool done;
		epicsEvent * isDone;
		epics::pvaClient::PvaClientMonitorPtr     monitor;
		epics::pvaClient::PvaClientMonitorDataPtr monitorData;
		std::string * recordData;
};

class MonitorWorker {
	public:
		MonitorWorker(epics::pvaClient::PvaClientMonitorPtr monitor,
					  std::string * recordData);
		
		int start();
		void exit();
		std::string getErrMsg () { return errorMsg; }	
	
	private:
		bool isSafe;
		std::string errorMsg;
		MonitorRunnable * runnable;
		epicsThread * thread;
};

}} /* namespace epics, monitorWorker */

#endif /* MONITORWORKER_H */
