#include "IScreen.h"
#include "IExtEventSource.h"
#include "FlScreen.h"
#include <Application.H>
#include <ServiceManager.H>
#include <ServiceTypes.H>
#include <iostream>
                       
//#include "FltkFactory.h"
using namespace StdSystem;
using Service::ServiceManager;
using Service::Request;
using Service::Response;
using Service::Operation;

void testingService(StdSystem::Service::Request& rqst);
void handleUI(StdSystem::Bus::Message);
void handleSvc(StdSystem::Address);
void WINNY();

static FlScreen *ui = nullptr;
static Winny::AppInfo curStatus;
int SHUTDOWN_WINNY = 0;


void initialiseSystem(){

   //step one Initilise Module objects;

    //allocate UserIO module
    FlScreen* screen =ui= new FlScreen();
    screen->run();
    
    //allocate DatabaserverIO Object to work as database module
    Service::ServiceManager::ServiceConfig s = {"",testingService};
    ServiceManager::start(&s);    

    //Allocate Application object to work as Application module
    //and connect the modules together
    //Application* APP = new Application(screen);
    WINNY();

    //begin user IO lop
    //screen->show(); //show after completing setup
    //screen->run();
};

int main(){
    initialiseSystem();
    return 0;
};



void WINNY(){
    do{
        Bus::Message m = Bus::receiveAt(APP_PORT);

        switch (m.sourcePort)
        {
        case UIO_PORT:
            handleUI(m);
            break;
        case SVC_PORT:
            handleSvc(m.message);
        default:
            break;
        };

    }while (!SHUTDOWN_WINNY);
};



//this is a helper to handleUI it helps dispatch UI navigation requests 
//back to the UI module
void navigate (Winny::UserIODevName* n){
    if(ui){
        Fl::lock();
        ui->switchToDisplay(*n);
        Fl::unlock();
    }
};

//this routine services all UI module requests
void handleUI(StdSystem::Bus::Message msg){
        //Winny::UserInputArg *arg= (Winny::UserInputArg*)msg;
        switch (msg.opcode) {

            case SigUserIOready:
                curStatus.sessionInfo.currentOpgUnit.name = (char*)"Premium Distributors";//cast constness
                curStatus.sessionInfo.operatingUnits.push_back({(char*)"Global Distributors",(char*)"Gors"});
                curStatus.sessionInfo.operatingUnits.push_back({(char*)"Scan Distributors",(char*)"Scrs"});
                curStatus.sessionInfo.operatingUnits.push_back({(char*)"Scan Distributors",(char*)"Scrs"});
                curStatus.sessionInfo.role.name = (char*)"Admin";
                Fl::lock();
                ui->writeBuff(&curStatus);
                Fl::unlock();
            break;


            case SigSHUTDOWN:
            {
                SHUTDOWN_WINNY = 1;
                break;
            }
            case CmdUpdateProductsList:
            {
                //std::cout<<"preparing request \n";
                Request rqst;
                Winny::UserInputArg *e_arg = (Winny::UserInputArg*)msg.message;//for client
                rqst.client =(IUserInterface*)(e_arg->sourceInterface);
                rqst.operation = Operation::GETL_PRODTS;
                rqst.triggerEvent = msg.opcode;
                //std::cout<<"client add sent "<<rqst.client<<"\n";
                rqst.responseBuffer = new Response();
                //saveRequest(rqst);
                StdSystem::Bus::sendRequest(rqst);
            }
                break;

            case CmdEditProductDetails:
                Fl::lock();
                ui->log("CmdEditProductDetails...Delivered");
                Fl::unlock();
                break;
            case CmdNavigateTo:
                //break;
                /**By convention, event data is not the source UI, but address to the name of the target UI**/
                navigate((Winny::UserIODevName*)msg.message);
                break;
    /*         case CmdUpdateProductsList:
                userIO->log("***CmdUpdateProductsList...Delivered");
                productListUpdate(eData); */
            break;
            default:
                Fl::lock();
                ui->log("@@@@unkown Command ...Delivered");
                Fl::unlock();
        }
};

void handleSvc(StdSystem::Address msg){
       // return;
        
        Response* rsp = (Response*)msg;
        
        int triggerEvent = rsp->request.triggerEvent;
        //std::cout<<"trigger Event returned is "<<rsp->request.client<<"\n";
        
        IUserInterface *userIO = rsp->request.client;
       // std::cout<<"client add returned is "<<rsp->request.client<<"\n";
        
        Winny::UserOutputArg output;

        if(triggerEvent == CmdUpdateProductsList){
            //prepare search results output
            output.ok = rsp->ok; 
            output.message = rsp->message;
            output.event = triggerEvent;
            output.args = & (rsp->data);

            //send them to output
            //std::cout<<"Process response ready, locking interface \n";
            //return;
            Fl::lock();

            userIO->writeBuff(&output);

            Fl::unlock();
            //std::cout<<"processDB done refreshing inteface, unlocked\n";

        }else{
            //std::cout<<"ProcessDB couldn't match this response to a known event \n";
        }

        //ALWAYS REMEMBER TO CLEAN MEMORY
        delete rsp;

};