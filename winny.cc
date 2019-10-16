#include "IScreen.h"
#include "IExtEventSource.h"
#include "FlScreen.h"
#include <Application.H>
#include <DatabaseServer.h>

//#include "FltkFactory.h"


void initialiseSystem(){
    Fl::lock();

   //step one Initilise Module objects;

    //allocate UserIO module
    FlScreen* screen = new FlScreen();
   
    //allocate DatabaserverIO Object to work as database module
    DatabaseServer* DB = new DatabaseServer();

    //Allocate Application object to work as Application module
    //and connect the modules together
    Application* APP = new Application(screen,DB);

    //begin user IO lop
    screen->show(); //show after completing setup
    screen->run();
};

int main(){
    initialiseSystem();
    return 0;
};