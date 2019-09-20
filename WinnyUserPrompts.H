#ifndef WinnyUserPrompts_H
#define WinnyUserPrompts_H
#include <gmtime.h>
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
    static void getClientId(string *out);
    static void getProductId(string *out);
};

#endif