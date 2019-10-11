// proposed database access interface
#ifndef WDS_DATASERVER_LINK_H
#define WDS_DATASERVER_LINK_H

#include <IApplication.h> //for *IApplication

namespace StdSystem {

    typedef void* Address;

    class IDatabaseService{
        
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
            Request request; //the requested operation
            IApplication* client; //address of client app where to send response
            Address data; //address to additional data required to perform operation. 
        };

        /*Perform the requested request */
        virtual int process( RequestInfo rqst)=0;
    };


};

#endif