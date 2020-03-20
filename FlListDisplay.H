/** \file
 * A ListDisplay is an abstract communication medium between an scoperator
 * module and a user.
 * 
 * To the scoperator module, a listDisplay takes a dataset object specified
 * located at a mem address and outputs it to a user's display in a pre-
 * agreed diplay layout. This is it's output operation. for its input operation
 * it takes a query object-sized memory where it writes out a query object
 * specified by a user in its input textboxs
 */

#ifndef FLISTDISPLAY_H
#define FLISTDISPLAY_H

#include <IUserInterface.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include <dataset_view.h>
#include <IApplicationTypes.H>
#include <IApplication.h>

using StdSystem::IApplication;

typedef void (*typeHandler)(IUserInterface *a, int event, Winny::UserInputArg*);


class FlListDisplay : public IUserInterface , public Fl_Group{
    public:
    enum Query
    {SEARCH, DEACTIVATE, ACTIVATE,CREATE,EDIT,REFRESH};//generic events that query handlers should specialise

    FlListDisplay();
    void show();
    void hide();
    void update();
    void readBuff(MemAddress buff){buff=&queryCond;};//filter to Values list
    void writeBuff(MemAddress buff);//matches
    
    void sethandler(typeHandler o){cb = o;};
    /*Sets a handler that specialises the queries made by the display*/
    
    void extEventsHandler(Fl_Widget* o);
    /*Processes Raw Events from Lower layer of FL Library*/

    void run(){return;};

    private:
    Fl_Group       *menuBar;
    Fl_Button      *btnNew, *btnActivateToggle, *btnEdit;
    Fl_Menu_Button *filter;
    Fl_Input       *searchToken;
    dataset_view   *itemsList;
    dataset        output;
    Fl_Box         *menuBarResizer;
    typeHandler cb;
    Winny::QueryCond queryCond;
};

void productListCb(IUserInterface *o, int e, Winny::UserInputArg* argz);
//this handler must compose the output args to send to the user

#endif