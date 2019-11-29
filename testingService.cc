#include <CommBus.H>
#include <ServiceTypes.H>
using namespace StdSystem;
using StdSystem::Service::Request;
using StdSystem::Service::Response;
using StdSystem::Service::Operation;

void testingService (Service::Request& rqt){
    //Performs required operation and writes response in request.responseBuffer

    Response* response = (Response*)rqt.responseBuffer;
    
    //std::cout<<"processing request in db trigger event sent here is"<<request.triggerEvent<<"\n";
    switch (rqt.operation){

        case Operation::GETL_PRODTS:
        {
            //sizes of our dataset response //lets use response and request terms
            int rc = 50; int cc = 10; 

            //resize response
            response->data.set_rows(rc);
            response->data.set_cols(cc);

            //populate it with some garbage data for now
            for (int r=0; r<rc; r++){
                for (int c=0; c<cc; c++){
                    response->data.data(r,c,(c+r)*rand());
                    if(response->data.data(r,c).number()>300000){
                        response->data.data(r,c).style().forecolor = wcolor(0,125,12);   
                    }
                    response->data.data(r,c).style().borders = Borders::LEFT_RIGHT_BORDER;
                    
                }
            }   
            response->ok = 1;
            response->requestId = rqt.id();
            response->message= variable("Search executed successfully");
            response->request = rqt;

        }
        break;
        
        default:
            break;
        }
        //Bus::sendResponse(response);
        Bus::Message msg;
        msg.message = response;
        msg.sourcePort = StdSystem::SVC_PORT;
        Bus::sendTo(StdSystem::APP_PORT,msg);
};