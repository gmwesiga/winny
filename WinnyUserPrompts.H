#ifndef WinnyUserPrompts_H
#define WinnyUserPrompts_H
#include <gmtime.h>
#include <gmdataset.h>//to get varialbe
#include <IApplication.h>
#include <string>
//using utils::Time;
using StdSystem::IApplication;
using std::string;

class PromptUser{
    public:
    void setApplication(IApplication* app);
    /*Sets app as the application to service
     *some dialogs that need to access winny API */
    static void getDate(utils::Time* out);
    /*Prompts user to select a date using a date picker
     *blocks until user dismisses prompt after entering 
     *date. */
    static void getClientId(variable *out);
    static void getProductId(variable *out);
};

#endif