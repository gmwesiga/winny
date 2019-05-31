#ifndef _WINNYAPPLICATION_TYPES_H
#define _WINNYAPPLICATION_TYPES_H
#include <string>
#include <vector>

namespace Winny {
  using namespace std;
   
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
        UIOQ_CREATE_ROLE,
        UI0Q_CREATE_TRANS_SALES_CASH,
        UIOQ_CREATE_TRANS_SALES_REP,
        UIOQ_CREATE_TRANS_SALES_CREDIT,
        UIOQ_CREATE_TRANS_GOODS_DELIVERY,
        UIOQ_CREATE_TRANS_GOODS_RECIEVED,
    };
    //A serverName is used to locate the Winny Server
    typedef std::string ServerName;

    //A Flag representing the data type of typeSafe dataObject 
    //returned By the winny Server
    enum ObjType {STRING,BOOL,INT,IMAGE};

    struct Data{
        void* object;
        ObjType type;    
    };

    //generic and dynamic Storage type used by application to get datasets
    //from server and output them to UIs 
    typedef vector<vector<Data> > Dataset;

    struct ProductsListFilter{
        bool isComposite;
        char searchKey[100];//IO to enforce this limit...
    };

    struct ProductsListParams{
        ProductsListFilter inPut;   
        Dataset outPut;
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