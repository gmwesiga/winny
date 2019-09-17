#include<WinnyUserPrompts.H>
#include<FL\Fl_Window.H>
#include<FL\Fl_Choice.H>
#include<FL\Fl_Button.H>
#include<FL\Fl_Input.H>
#include<FL\Fl.H>
#include<dataset_view.h>
#include<IUserInterface.h>
#include <WinnyNames.H>
#include <stdio.h>

static IApplication* app = 0;
void PromptUser::setApplication(IApplication* a){
    app = a;
};



/*\\\\\\Get Date Implementation \\\\\\*/

#define MINYEAR 1960
#define MAXYEAR 2059

#define MONTHS 12
char tempString[] = {'\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'};
/*tempstring acts as an internal buffer used by datechangedcb. and others. date changed
 *uses it as an argument to sprintf while converting numbers to strings */

const char* MONTHSNAMES[] = {
    "JAN","FEB","MAR","APR","MAY","JUN","JUL","AUG","SEP","OCT","NOV","DEC"
};
/*MONTHSNAMES is a table used by datechangedhandler to map from numeric month
 *values of the widget to the string  */

struct getDateDialog {
    /*data shared/modified by all date dialog handlers */
    Fl_Window *Dialog;
    Fl_Choice *year;
    Fl_Choice *month;
    Fl_Choice *day;
    Fl_Button *btnOk;
    Fl_Button *btnCancel;
    Time      *oDate;
    int done;
}dateDialog={
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    0
    };


void getDateOkcb(Fl_Widget*o, void* d );
void getDateCancelcb(Fl_Widget*o, void* d );
void dateChangedcb(Fl_Widget*o, void* d );
void createDateDialog();



void PromptUser::getDate(Time* out){
    if(!dateDialog.Dialog)
        createDateDialog();
    dateDialog.oDate = out;
    dateDialog.Dialog->position(Fl::event_x_root(), Fl::event_y_root());
    dateDialog.Dialog->show();
    do{
        Fl::wait();
    }while(!dateDialog.done);
    dateDialog.done = 0;
    //Fl::delete_widget(dateDialog.Dialog);
}


using std::sprintf;
void createDateDialog(){
    /*Dialog should not be child of any other window 
     *fills the dateDialog Global with references to
     *dialog widgets so that they can easily be found
     *later by the callbacks*/

    Fl_Group *t = Fl_Group::current(); 
    Fl_Group::current(nullptr);
    Time today;//today
    dateDialog.Dialog = new Fl_Window(193,70,"Please Choose A Date");
    dateDialog.Dialog->begin();
        
        dateDialog.year = new Fl_Choice(10,16,57,20);
        dateDialog.year->callback(dateChangedcb,&dateDialog);
        for(int i = MINYEAR; i<=MAXYEAR; i++){
            sprintf(tempString,"%d",i);
            dateDialog.year->add(tempString);
            if(i==today.year())
                    dateDialog.year->value(i-MINYEAR);//select current year
        }

        dateDialog.month = new Fl_Choice(67,16,57,20);
        dateDialog.month->callback(dateChangedcb,&dateDialog);
        for(int i = 1; i<=MONTHS; i++){
            dateDialog.month->add(MONTHSNAMES[i-1]);
            if(i==today.month())
                    dateDialog.month->value(i-1);//select current month
                    //do callback after creating day widget
        }
        dateDialog.month->when(FL_WHEN_CHANGED);

        dateDialog.day = new Fl_Choice(124,16,57,20);
        dateDialog.month->do_callback();

        dateDialog.btnCancel = new Fl_Button(10,45,48,14,"Cancel");
        dateDialog.btnCancel->callback(getDateCancelcb,&dateDialog);

        dateDialog.btnOk = new Fl_Button(133,45,48,14,"Ok");
        dateDialog.btnOk->callback(getDateOkcb,&dateDialog);

    dateDialog.Dialog->end();
    set_winny_window_theme(dateDialog.Dialog);
    dateDialog.Dialog->set_modal();
    /*Restore previous Grouping widget as you found */
    Fl_Group::current(t);
    return;
}

void getDateCancelcb(Fl_Widget*o, void* d){
    dateDialog.done = 1;
    dateDialog.Dialog->hide();

}

//Helper Function to dateChangedcb to return numofDays in month
//given month and year
int daysInMonth(int month, int year){
    switch (month)
    {
    case 9:/*Sept */
    case 4:/*April */
    case 6:/*June */
    case 11:/*Nov */
        return 30;
    case 2:
        return !(year%100)&&!(year%400)?29:28; 
        //leap year definition of gregorian calender is that a year is leap
        //if its divisiable by 100 and 400. read more on wikipidea, leap year entry
    default:/*All the rest */
        return 31;
    };
}


/*Whenever the values of the Year or Month are changed, this callback
* is called to recalculate the num of days in the new year and month 
* combination and update the days in month widget accordingly 
* its necesary as the number of days in feb change with changes in years*/
void dateChangedcb(Fl_Widget*o, void* d){
//fill day combo
    Time dateInput;//what has been selected sorfar
    Time today;

    dateInput.year(dateDialog.year->value()+MINYEAR);
    dateInput.month(dateDialog.month->value()+1);
    dateInput.day(daysInMonth(dateInput.month(), dateInput.year()));//clamp if wrong
    dateDialog.day->clear();//reset
    dateDialog.day->value(0); //preselect first value;

    for(int i = 1; i<=dateInput.day(); i++){
        sprintf(tempString,"%d",i);
        dateDialog.day->add(tempString);

        /*If its not moth that was changed, ie year widget
         *don't do anything */
        if(o!=dateDialog.month)continue;
        /*Else, it was month that was changed, we can now
        /*set today as default day */
        if(i==today.day())//set doday's date  as default
            dateDialog.day->value(i-1);
        }
};


/*Close the dialog and return date entered by user */
void getDateOkcb(Fl_Widget*o, void* d ){
    if(dateDialog.oDate){
        dateDialog.oDate->year(dateDialog.year->value()+MINYEAR);
        dateDialog.oDate->month(dateDialog.month->value()+1);
        dateDialog.oDate->day(dateDialog.day->value()+1);
    }
    getDateCancelcb(nullptr, nullptr);
};





/*/////////////////GET STRING DIALOG/////////////////// */





/*Since the getClientId dialog and getContactId dialog are structurally
**the same, I have realised they should share the structral code... which
**we can just pass the variable functional code as arguments. 
**/

void getValueOkcb(Fl_Widget*o, void* d );
void getValueCancelcb(Fl_Widget*o, void* d );
void searchKeyChangedcb(Fl_Widget*o, void* d );
void createvalueDialog();
void _createSearchDialog(
    Fl_Window** dialog,
    Fl_Input**  searchKey,
    dataset_view** results,
    Fl_Button** btnOk,
    Fl_Button** btnCancel);
typedef void (*QueryChangedHandler)(IApplication* app); //should raise the right event to app
void runDialog();

struct GetValueDialog :IUserInterface{
    Fl_Window* dialog;
    Fl_Input*  searchKey;
    dataset_view* results;
    Fl_Button* btnOk;
    Fl_Button* btnCancel;
    string title;
    void* value;
    QueryChangedHandler handler;
    int column;
    int done;

    void show(){return;};
    void hide(){return;};
    void update(){return;};
    void readBuff(MemAddress buff){buff = (void*)(searchKey?searchKey->value():"");};//buff gets searchfilter
    void writeBuff(MemAddress buff){buff=nullptr ;};//matches
    UIname id(){return "GetValueDialog";};
    void run(){return;};
};

GetValueDialog valueDialog;
//  {
//     nullptr,/*dialog*/
//     nullptr,/*searchKey*/
//     nullptr,/*results*/
//     nullptr,/*btnOk*/
//     nullptr,/*btnCancel*/
//     "",/*title*/
//     nullptr,/*value*/
//     nullptr,/*handler*/
//     0, /*Column*/
//     0 /*done*/
// };

//TEXT/CODE REG



//Create the dialog if not exists and run it.
void runDialog(){
    if(!(valueDialog.dialog))
        createvalueDialog();
    valueDialog.dialog->label(valueDialog.title.c_str());
    valueDialog.dialog->position(Fl::event_x_root(), Fl::event_y_root());
    valueDialog.dialog->show();
    //return;
    do{
        Fl::wait();
    }while(!valueDialog.done);
    valueDialog.done = 0;

}

/*Calls _createSearchDialog to construct the dialog*/
void createvalueDialog(){
    _createSearchDialog(
        &(valueDialog.dialog),
        &(valueDialog.searchKey),
        &(valueDialog.results),
        &(valueDialog.btnOk),
        &(valueDialog.btnCancel));
    //set callbacks
    valueDialog.btnCancel->callback(getValueCancelcb);
}


void getValueCancelcb(Fl_Widget*o, void* d ){
    if(!valueDialog.dialog)
        return;
    valueDialog.dialog->hide();
    valueDialog.done= 1;
    
};





/*Constructs a generic search dialog window
//with a text input for the search key
//and a list display of matches.*/
void _createSearchDialog(
    Fl_Window** dialog,
    Fl_Input**  searchKey,
    dataset_view** results,
    Fl_Button** btnOk,
    Fl_Button** btnCancel)
{

    Fl_Group* o = Fl_Window::current(); //Grouping group widget
    Fl_Group::current(nullptr);//Our Window will not be nested in any other window, 
    (*dialog) = new Fl_Window(387,384);
    (*dialog)->begin();
    (*searchKey) = new Fl_Input(14,29,354,25,"Enter Search Key");
    (*results) = new dataset_view(14,77,356,258,"Matching Results");
    (*btnOk) = new Fl_Button(277,347,47,21, "Select");
    (*btnCancel) = new Fl_Button(324,347,47,21,"Cancel");
    (*dialog)->end();
    (*dialog)->set_modal(); //make it a model dialog
    Fl_Group::current(o); //leave every thing as you found
}




void PromptUser::getClientId(string* out){
    valueDialog.title = "Select A contact.";
    runDialog();
};


void PromptUser::getProductId(string* out){
    valueDialog.title = "Select A Product";
    runDialog();
}