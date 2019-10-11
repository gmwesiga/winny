#ifndef WDS_DATASERVER__H
#define WDS_DATASERVER__H

#include <IDatabaseServer.h>

using StdSystem::IDatabaseService;
using StdSystem::Address;
//using StdSystem::IDatabaseService::Requests;

class DatabaseServer : public IDatabaseService{
    public:
    int process(RequestInfo rqst);
};


#endif