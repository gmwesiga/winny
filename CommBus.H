#ifndef __I_WSERVER_comBUS_H
#define __I_WSERVER_comBUS_H

#include <ServiceTypes.H>

namespace StdSystem{

    typedef int BusPort;

    const int UIO_PORT = 01;
    const int APP_PORT = 00;
    const int SVC_PORT = 02;

    class Bus {
        /*Bus is a shared communication medium   */
    public:

        struct Message {
            int sourcePort;
            int type;
            int opcode;
            Address message;
        };
       
        static int  sendRequest(Service::Request rqst);
        /*Dispaches rqst to Service controller thread and returns emmediately.*/

        static int sendResponse(Service::Response *rsp);
        /*Dispaches response to winny application thread*/

        static int echo(Service::Response *rsp);
        /*Ask bus to reecho this response later*/

        static Service::Request receiveRequest();
        /*Blocks and waits for applicaiton thread to send new request*/

        static Service::Response* receiveResponse();
        /*Blocks and waits for application to send response*/

        static int sendTo(BusPort port, Bus::Message msg);
        static Bus::Message receiveAt(BusPort port);

    };

};

#endif