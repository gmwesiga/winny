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
    screen->show();
    APP = new Application();
    screen->Attach(APP);
    //screen->productsListDisplay()->Attach(APP);

    APP->uiScreen(scrn);
    eventSource->run();
};

int main(){
    initialiseSystem();
    return 0;
};