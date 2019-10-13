#ifndef WDS_DATASERVER__H
#define WDS_DATASERVER__H

#include <IDatabaseServer.h>
#include <stack>//for implementing the stack
#include <mutex> //for locking
#include <condition_variable> //for locking


using StdSystem::IDatabaseService;
using StdSystem::Address;
//using StdSystem::IDatabaseService::Requests;

class DatabaseServer : public IDatabaseService{
    /*DatabaseServer processes data access requests on behalf of the
      StdSytem::IApplication. 
      Usage:
      To issue a data request, users/clients, specify the required operation
      in a RequestInfo data struct and passes it to the process routine.
      latter when the response is ready, the server will notify the client
      by calling it's handle(). 
      
      Actual request processing  is done by server(). server() and process()
      communicate using a queue. process recieves client requests on behalf of
      server and adds them to queue. if server is asleep, it wakes it up
      Server() continually processes requests in 
      queue until its empty then it sleeps until process awakes it   
      */
    public:
    int process(RequestInfo rqst);

    private:
    /*list of Pending requests*/
    static std::stack <RequestInfo> RequestQueue;
    static std::condition_variable notEmpty;
    static std::mutex queueLock;


    /**/
    static void server(); 
};


#endif