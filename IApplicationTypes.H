/*Winny is currently separated into 3 broad functional modules
 * 1. the userIO module: provides input output to winny users
 * 2. the application module: which is the centrol controllor, and owner of all modules
 * 3. the databaseServer module: which provides storage of data.
 * these modules work as follows.
 * Users interact with the UserIO module to issue commands to winny. and optionally pass
 * data. the UserIO module thread seats in a tight loop waiting for user's requests
 * which it passes to the application module for processing. the application module 
 * processes the command optionally calling the databaseServer module for additional
 * data. and when results are ready, passes them to the userIO module . the user reads
 * the results off the userIO module.
 * 
 * This file defines the argument datatypes for all of the command arguments as exchanged between
 * these modules.*/

#ifndef _WINNYAPPLICATION_TYPES_H
#define _WINNYAPPLICATION_TYPES_H
#include <string>
#include <vector>
#include <gmdataset.h>

namespace Winny {
  using std::string;

    /*****ARGUMENT TYPES********/

    struct UserInputArg{
        /*Adress of the IODevice that generated the Input Request*/
        IUserInterface* interface;

        /*The Event name*/
        int event;

        /*The Event specific output data. */
        MemAddress args; 
    };



    struct UserOutputArg{
        /*The Input Event that requested the output*/
        int event;

        /*If input event was an operation request, this 
         *flag tells if it completed successfully */
        int ok;

        /*If input event was an operation request, this 
         * variable contains a message an optional message of
         * for example how operation succeded eg rows returned */
        variable message;

        /*The Event specific output data. Each IInterface knows 
         *interpletes this differently*/
        MemAddress args;
    };



   
    enum State {
        //A State variable holds a flag of possible states of application
        CLOSED,CONNECTING,CONNECTED,AUTHENTICATING,ESTABLISHED,CLOSING
        };
    
    enum UserIODevName {
        UIO_MAIN=100,
        UIOQ_CASH_FLOW,
        UIOQ_STOCK_MVT,
        UIOQ_SEARCH_PRODUCTS,
        UIOQ_SEARCH_CONTACTS,
        UIOQ_SEARCH_TRANSACTIONS,
        UIOQ_CREATE_PRODUCT,
        UIOQ_CREATE_CONTACT,
        UIOQ_CREATE_ROLE,
        UI0Q_CREATE_TRANS_SALES_CASH,
        UIOQ_CREATE_TRANS_SALES_REP,
        UIOQ_CREATE_TRANS_SALES_CREDIT,
        UIOQ_CREATE_TRANS_GOODS_DELIVERY,
        UIOQ_CREATE_TRANS_GOODS_RECIEVED,
    };
    //A serverName is used to locate the Winny Server
    typedef std::string ServerName;

    //generic and dynamic Storage type used by application to get datasets
    //from server and output them to UIs cliets should not assume vector, but 
    //instead assume a generic stl container and use iterators only for 
    //input and output
    typedef dataset Dataset;
    //typedef vector<vector<Data> > Dataset;

    struct ProductsListFilter{
        bool isComposite;
        char* searchKey;//IO to enforce this limit...
    };

    struct ProductsListParams{
        ProductsListFilter inPut;   
        Dataset* outPut;
    };

    /*Modified ProductListFilter and ProductListParams,Generalised them 
     *as follows*/

    struct QueryCond{/*Query Conditions*/
        bool isComposite;
        char* searchKey;//IO to enforce this limit...
    };

    struct Query{
        QueryCond inPut;   
        Dataset* outPut;
    };

    struct OpUnitInfo{
        char *name;
        char *code;
    };

    typedef string FuncScreenName; //will change in future

    struct Role{
        /*A role names a set of related operations*/
        std::string name;
        vector<FuncScreenName> operations;
    };

    struct UserSessionInfo{
        string userId;
        string password;//don't keep it here
        int serverSessionId;
        vector<OpUnitInfo> operatingUnits;
        OpUnitInfo currentOpgUnit; //selected Unit
        vector<Role> currentRoles;
        Role role; //selected role
    };

    //Global winny client Application Info
    struct AppInfo{
        State state;
        char name[50]; /*App name shouldn't be more than 50 chars*?*/
        ServerName serverName;
        UserSessionInfo sessionInfo;
    };
}
#endif