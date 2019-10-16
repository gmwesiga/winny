#ifndef WDS_DATASERVER__H
#define WDS_DATASERVER__H

#include <IDatabaseServer.h>
#include <queue>//for implementing the stack
#include <stack>
#include <mutex> //for locking
#include <condition_variable> //for locking
#include <thread> //a local thread


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

    /*Construct and start thread*/
    DatabaseServer();


    int process(IDatabaseService::RequestInfo rqst);

//////////////request queue and locks///////////////////////////////
    /*list of Pending requests*/
    static std::queue <RequestInfo> RequestQueue;
    /*server() waits on this*/
    static std::condition_variable notEmpty;

    /*synchronise process() and server() access to RequestQueue*/
    static std::mutex queueLock;

    /*allocates thread object to contain server thread*/
    std::thread svr;

    /*the actual server doing the work
     Server should do any*/
    static void server(); 

    /*helper function to server to actually do the work*/
    static void doit(RequestInfo request);

//////////////response queue and locks////////////////////////////////
  /*list of ready responses*/
    static std::queue <Response*> ResponseQueue;
    static std::mutex ResponseQueueLock;
    static std::condition_variable resQueNotEmpty;
    static Response* popResponse();
};


#endif