#include "IScreen.h"
#include "IExtEventSource.h"
#include "FlScreen.h"
//#include "FltkFactory.h"

IScreen* screen;
//IApplication winnyApp;
IExtEventSource* eventSource;

void initialiseSystem(){
//    screen      = new fltkFactory.createScreen();
    FlScreen* scrn = new FlScreen();
    screen =  scrn;
    eventSource = scrn;    
//    winnyApp    = new WinnyApplication;
    
//    eventSource->attach(winnyApp);
    screen->show();
    eventSource->run();
};

int main(){
    initialiseSystem();
    return 0;
};