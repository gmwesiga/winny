#ifndef __I_WSERVER_THREAD_H
#define __I_WSERVER_THREAD_H

#include <ServiceTypes.H>
#include <CommBus.H>
#include <string>

namespace StdSystem {

    namespace Service {

        using std::string;
        typedef void (*ServiceImp)(Service::Request& rqt);

        struct ServiceManager{
        
            struct ServiceConfig{
                /*Defines configuration information used/required
                 *to configure(find and initialize) the srv implementers*/
                string address;
                ServiceImp svr;
            };

            static int start(ServiceConfig* LocalService);
        };

    };
};

#endif