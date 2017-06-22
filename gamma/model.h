#ifndef MODEL_H
#define MODEL_H

#include <pv/pvaClient.h>

class Model {

	public:
		bool connect(const std::string & recordName);
		std::string getRecordData() { return recordData; }
	
	private:
	/* Data retrieved from record */
		std::string recordData;
	/* pvaClient objects used for data retrieval */
		epics::pvaClient::PvaClientPtr         pvaClient;
		epics::pvaClient::PvaClientChannelPtr  channel;
		epics::pvaClient::PvaClientGetPtr 	   get;
		epics::pvaClient::PvaClientGetDataPtr  getData;

};

#endif /* MODEL_H */
