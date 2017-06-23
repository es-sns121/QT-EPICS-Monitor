#ifndef MODEL_H
#define MODEL_H

/*
 *	model.h
 *
 *	Class definition of the application's
 *	model.
 *
 */

#include "monitorWorker.h"
#include <pv/pvaClient.h>

class MonitorModel {

	public:
		MonitorModel () : recordData(new std::string), monitorWorker(NULL) {}
		
		bool connect(const std::string & recordName);
		std::string getRecordData() { return *recordData; }
		void stop() { monitorWorker->exit(); }
	
	private:
	/* Data retrieved from record */
		std::string * recordData;
	/* pvaClient objects used for data retrieval */
		epics::pvaClient::PvaClientPtr         pvaClient;
		epics::pvaClient::PvaClientChannelPtr  channel;
		epics::pvaClient::PvaClientGetPtr 	   get;
		epics::pvaClient::PvaClientGetDataPtr  getData;
	/* Worker thread to monitor server side record data */
	    epics::monitorWorker::MonitorWorker  * monitorWorker;
};

#endif /* MODEL_H */
