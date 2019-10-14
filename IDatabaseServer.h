// proposed database access interface
#ifndef WDS_DATASERVER_LINK_H
#define WDS_DATASERVER_LINK_H

#include <IApplication.h> //for *IApplication
#include <gmdataset.h> //for variable and dataset

namespace StdSystem {

    typedef void* Address;
    typedef long  RequestId;

    class IDatabaseService{
/*IDatabaseService defines an interface required by Application to service
 *(handle) requests that need retrieval of data. Application requires this 
 *IDtabaseService to have a process that takes a request command token and
 *optionally a argument list.
 *Application also requires that process() returns imediately and performs
 *long work in the background upon completion of which, it calls application's
 *handle and passes the results.*/

        
        public:
        enum Request{
            CONNECT,
            CLOSE,
            NEW_PRODT,
            NEW_CLIENT,
            NEW_TRANS,
            UPDT_TRANS,
            UPDT_PRODT,
            UPDT_CLIENT,
            GET_CASH_FROW,
            GET_STCKMOVT,
            GET_ACCT,
            GETL_CLIENTS,/*GETL for get list of*/
            GETL_PRODTS
        };

        struct RequestInfo {
            /*Application needs a way to match responses from database server
             *to clients that made a request. so each request has an id,
             *fore each response sent back, the server should quote the request id
             *the application uses a table to look up the client that made the request
             *originally**/
            RequestId id(){return _my_id_;};

            //the requested operation
            Request request; 

            //address of client app where to send response
            IApplication* client; 

            //address to additional data required to perform operation.
            Address data; 

            /*Id() needs to be unique for each request, so we implement it here*/
            RequestInfo(){
                _my_id_ = _nextid_++;/*NOt THEAD SAFE!!*/
            }
            
            private:
            /*this' id*/
            RequestId _my_id_;

            /*class shared global, next request object gets this id*/
            static RequestId _nextid_;//initally 0; 
        };//end of RequestInfo


        struct Response {
            /*Response from the server
             *To use less memory and avoid over copying especially
             *in cases where data has been returned, when server
             *calls application's handle, it shall pass a reference
             *to this response, the handler should copy out the data
             *response from the dataserver module layer to it's layer
             *or probably the interface. it should not assume its on
             *the free store
             */

            //tells if operaton was succefull
            int ok;

            //contains a message about the operation.
            variable message;

            //contains data for query operations
            dataset data;

            //the originating request's id
            RequestId requestId;

            //default constructor;
            Response():ok(1), data(0,0){};
        };
        
        /*Perform the requeste  d request */
        virtual int process( RequestInfo rqst)=0;
    };


};

#endif