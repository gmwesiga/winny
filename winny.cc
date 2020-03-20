/** \file 
 * This file contains main. Main expresses the overall 
 * goal of the program. ie to return  a system response 
 * back to user for each command they enter on the input.
 */ 

#include <Winny.H>
#include <list>

using Winny::Link;
using Winny::UI;
using Winny::ID;
using Winny::Request;
using Winny::Response;
using Winny::REQID;
using Winny::OK;
using Winny::NO_WAIT;
using Winny::TIMEOUT;
using Winny::ERROR;

/**
 * Construct, configure and operate components.(discription 
 * that took me longest to define)
 * 
 * Operate UI and for each
 * command read, return and print its system Response  
 * Exit if command received is shutdown
 */ 
int main();


/**
 * Removes this id form the running Requests table
 * see addToExecReqsTable
 * remFromPendingRequestsIs a helper procedure for main.
 * 
 * @param reqid the request id to remove from the requests table
 */
void eraseFromExecReqsTable(REQID rID);


/**
 * Add this request id into the running Requests table (ExcReqsTable)
 * The execReqsTable (Executing Requests Table) records the ids of 
 * requests whose responses are yet to arrive from the remote server
 * 
 * @param reqid the request id to add
 */
void addToExecReqsTable(REQID rID);


/**
 * Gets the lengths of the ExecReqsTable which is equal to the number of
 * all Pending Requests
 */
int execReqsTableSize();


/**
 * Try local (not server side) processing of this request, if 
 * request can not be processed, return error code
 * 
 * @param reqAddr contains address of the request object to process
 * @param respAddr contains address of memory reserved where the
 * response should be written
 * @param returnvalue contains an OCC of the operation
 */
int tryInternalProc(Request* reqAddr, Response* respAddr);



/// An Urgent Request is assigned the value 1 in its priority
/// field.
#define PRIORITY_URGENT 1
#define MAX_WAIT_TIME 2.0

/**
 * shutdown_self is a flag indicating whether to terminate the synchronisation
 * cycle or to continue it. When a shutdown signal is sent by the user, tryInternalProc
 * sets this value to true. At the end of each operating cycle, master checks this value
 * if its true, it exits the operation cycle loop executes the exit routine
 */
bool SHUTDOWN_SELF = false;


int main(){
    /*construct the UI*/
    ID id = UI::newInstance();

    /*Configure Link*/
    Link::setRemoteNodeAddress();
    
    /// a single request and a single response are handled at a time
    /// mem to contain the request object that is readin by io
    Request request;
    Response response;

    /// OCC stands for Operation Completion Code
    /// linkOCC shall be used to store an OCC code of last Link operation
    int linkOCC = Winny::OK;
    
    /// for containing OCC code of last UI operation
    int uiOCC = Winny::OK;
    

    /// coordinate and synchronise the modules     
    while(!SHUTDOWN_SELF){

        /// if we have no pending background requests, lets
        /// wait for a new request from UI, else, wait only
        /// for TIMEOUT, so that you can have a chance to check
        /// link if it has received a new response 
        if(execReqsTableSize() == 0)
            uiOCC = UI::run(id,&request,NO_WAIT);
        
        else
            uiOCC = UI::run(id,&request,MAX_WAIT_TIME);

        /// if we got a new request,
        if(uiOCC==OK){
            
            /// record this request in table
            addToExecReqsTable(request.id());    
            
            if(tryInternalProc(&request,&response)==ERROR)
                Link::sendCommand(&request);
        }

        /// if this was a priority request, then no need to receive
        /// another request before giving a response for this one
        if (request.priority==PRIORITY_URGENT){
            
            /// Receive and output all responses that arrive on the link
            /// untill we get a response of this particular request.
            do{
                linkOCC = Link::receiveSystemResponse(&response,0);
                if(linkOCC==OK)
                    eraseFromExecReqsTable(response.requestId);
                
                UI::writeSystemResponse(id,&response);
            }while(response.requestId!=request.id());
  
        }else { /// PRIORITY_NORMAL

            /// Receieve Whatever Responses arrived on link while we waited
            /// on usermodule timeout
            while(Link::receiveSystemResponse(&response,MAX_WAIT_TIME)!=TIMEOUT){
                eraseFromExecReqsTable(response.requestId);
                UI::writeSystemResponse(id,&response);
            }
        
        }
                    
    }//end of synchronisation cycle     

    return 0;
};



int tryInternalProc(Request* reqAddr, Response* respAddr){
    switch (reqAddr->operation){
        case SigSHUTDOWN:
            SHUTDOWN_SELF = true;
            break;
    }
};


  
/** 
 * storage container of all received Requests that are pending
 * server Responses if a response comes in, update the list
 * by removing its matching request fromt the list
 * 
 * currently implemented from an std::vector
 */
static std::list<REQID> PendingRequests;


void eraseFromExecReqsTable(REQID rID){
    auto elem = PendingRequests.begin();
    
    while (elem != PendingRequests.end()){
        if(*elem == rID){
            PendingRequests.erase(elem);
        }
    }    
};



void addToExecReqsTable(REQID rID){
    PendingRequests.push_front(rID);
};


int execReqsTableSize(){
    return PendingRequests.size();
};