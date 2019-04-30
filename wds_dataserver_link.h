// proposed database access interface
#ifndef WDS_DATASERVER_LINK_H
#define WDS_DATASERVER_LINK_H

#include <string>
#include "account.h" //for Account
#include "wds_ledger_server.h"
#include "wds_store_server.h"

namespace winny_DataServer_link
{
    class DataServer_link : public ledger_server, public store_server
    {
        public:
        virtual bool connect_to(string server_name, string username, string password);
        virtual bool connect_as(string username, string password);
        virtual bool disconnect();
        virtual bool is_good();
        virtual bool is_bad();
    };
};

#endif