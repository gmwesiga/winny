#include "IScreen.h"
#include "IExtEventSource.h"
#include "FlScreen.h"
#include <Application.H>

//#include "FltkFactory.h"

FlScreen* screen;
Application* APP;
IExtEventSource* eventSource;

void initialiseSystem(){
    FlScreen* scrn = new FlScreen();
    screen =  scrn;

    eventSource = screen;    
    APP = new Application();
    screen->Attach(APP);
    APP->uiScreen(scrn);

    screen->show(); //show after completing setup
    eventSource->run();
};

int main(){
    initialiseSystem();
    return 0;
};