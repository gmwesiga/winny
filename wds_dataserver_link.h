// proposed database access interface
#ifndef WDS_DATASERVER_LINK_H
#define WDS_DATASERVER_LINK_H

namespace StdSystem {

    typedef void* Address;

    class IDatabaseService{
        
        public:
        enum Requests{
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


        /*Perform the requested request */
        virtual int process( IDatabaseService::Requests rqst, StdSystem::Address rqstData = 0 )=0;
    };


};

#endif