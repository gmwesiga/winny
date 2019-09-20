#include<WinnyUserPrompts.H>
#include<FL/Fl_Window.H>
#include<FL/Fl_Choice.H>
#include<FL/Fl_Button.H>
#include<FL/Fl_Input.H>
#include<FL/Fl.H>
#include<dataset_view.h>
#include<IUserInterface.h>
#include <WinnyNames.H>
#include <stdio.h>
#include <FL/fl_ask.H>

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
    utils::Time      *oDate;
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



void PromptUser::getDate(utils::Time* out){
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
    utils::Time today;//today
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
    utils::Time dateInput;//what has been selected sorfar
    utils::Time today;

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

void getValueLibAdptcb(Fl_Widget*o, void* d );//library API adpater. lib requires subscribers to implement this interface
typedef void (*QueryChangedHandler)(IApplication* app); //should raise the right event to app
void runDialog();

struct GetValueDialog :IUserInterface{
    struct Query {
        /*This is a record containing info of the query and the result*/
        /*To allow for future changes eg passing more parameters, without
         *breaking exisiting code, we have but it in its own struct 
         *To Allow for clients to specify which column to return, a col
         *Interface is provided*/
        char* text;
        void* result; /*To allow clients flexibility of datatypes, we use a void pointer*/
    };

    GetValueDialog():results_(3,1),done(0){
        Fl_Group* o = Fl_Window::current(); //Grouping group widget
        Fl_Group::current(nullptr);//Our Window will not be nested in any other window, 
        
        dialog = new Fl_Window(387,384);
        dialog->begin();
        
        searchKey = new Fl_Input(14,29,354,25,"Enter Search Key");
        searchKey->callback(getValueLibAdptcb,this);
        set_winny_input_theme(searchKey);

        results = new dataset_view(14,77,356,258,"Matching Results");
        results->align(FL_ALIGN_TOP_LEFT);
        results->table_box(WINNY_THIN_BORDERFRAME);

        btnOk = new Fl_Button(277,347,47,21, "Select");
        set_winny_button_theme(btnOk);
        btnOk->color(WINNY_BACKGROUND_ACCCOLOR);
        btnOk->callback(getValueLibAdptcb,this);

        btnCancel = new Fl_Button(324,347,47,21,"Cancel");
        set_winny_button_theme(btnCancel);
        btnCancel->callback(getValueLibAdptcb,this);

        dialog->end();
        dialog->set_modal(); //make it a model dialog
        Fl_Group::current(o); //leave every thing as you found
        set_winny_window_theme(dialog);

        value.result = value.text = nullptr;
    };

    void show(){
        dialog->label(id().c_str());
        dialog->position(Fl::event_x_root(), Fl::event_y_root());
        dialog->show();
    };


    void hide(){
        dialog->hide();
    };


    void update(){return;};
    
    void readBuff(MemAddress buff){
        //will write into buff, contents of value
        //assumes buff is of Query* type and points to valid memory
        ((Query*)buff)->result = value.result;
        ((Query*)buff)->text = value.text;
    };

    
    
    void writeBuff(MemAddress buff){
    /*Assumes Buff is a pointer to a dataset. 
     *Copies it to internal buffer
     */
        results_ = *((dataset*)buff); //copy
    };//matches
    


    void run()
    {
        show();
        do{
            Fl::wait();
        }while(!done);
        hide();
    };
    
    
    void setQueryHandler(QueryChangedHandler hnd){
        handler = hnd;
    };

    private:
    Fl_Window* dialog;
    Fl_Input*  searchKey;
    dataset_view* results;
    dataset results_;
    Fl_Button* btnOk;
    Fl_Button* btnCancel;
    Query value;
    QueryChangedHandler handler;
    int column;
    int done;

    public:
    ~GetValueDialog(){
        Fl::delete_widget( dialog); //dialog deletes the rest
    }

    void handleLib(Fl_Widget* o){
        if(o==btnCancel){
            done = 1;
        };
    }
};


//TEXT/CODE REG




void getValueLibAdptcb(Fl_Widget*o, void* d ){
    fl_alert("Begin..");
    ((GetValueDialog*)d)->handleLib(o);
    fl_alert("End...");
    
};


GetValueDialog dlg;
void PromptUser::getClientId(string* out){
  
    dlg.id("Choose A Client");
    GetValueDialog::Query qry;
    dlg.show();
    dlg.run();
    //dlg.readBuff(&qry);
    dlg.hide();
}
  
  


void PromptUser::getProductId(string* out){
    dlg.id("Choose A Product");
    GetValueDialog::Query *qry;
    dlg.show();
    dlg.run();
    dlg.readBuff(qry);
    //get qry result
    *out = qry? string((char*)(qry->result)):nullptr;
    dlg.hide();
}