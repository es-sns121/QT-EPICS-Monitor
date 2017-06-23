/*
 *	model.cpp
 *
 *	Implementation of model class's
 *	connect() member function.
 *
 */

#include "model.h"

#include <pv/pvaClient.h>
#include <sstream>
#include <string>

using namespace std;
using namespace epics::pvaClient;
using namespace epics::monitorWorker;

/*
 *	Gets pvaClient singleton and creates a pvAccess channel to the record.
 *	Dumps value of record to a stream and stores the value as a standard string.
 *	Returns true on success, false on failure. Upon failure the 'recordData'
 *	string of the parent class will contain an error message.
 *
 */
bool MonitorModel::connect(const string & recordName)
{
	try {
	
		pvaClient = PvaClient::get();
		channel = pvaClient->channel(recordName);
	
		get = channel->createGet("");
		getData = get->getData();

		stringstream recordStream;

		getData->getPVStructure()->dumpValue(recordStream);

		*recordData = recordStream.str();
	
		if (monitorWorker != NULL)
			monitorWorker->exit();

		monitorWorker = new MonitorWorker(channel->monitor(""), recordData);
		monitorWorker->start();
	
	} catch (std::runtime_error e) {
		
		*recordData = string("Error: ") + string(e.what());	
		
		return false;

	}

	return true;
}
