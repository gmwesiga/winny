#include "FlSessionInfoDisplay.h"
#include <FL/Fl.H>
#include "winny_theme.h"
#include <FWidgetSizes.H>

static const UIname PAGENAME("Session Info"); 

//return name of this function page
UIname FlSessionInfoDisplay::id(){return PAGENAME;};

FlSessionInfoDisplay::FlSessionInfoDisplay(string sessionId)
:Fl_Group(0,0,SCRN_WIDTH,33,"WINNY"){
    begin();
    Fl_Color col  = fl_rgb_color(147,147,255);
    color(col);
    _id = new Fl_Output(831,5,176,23);
    _id->color(col);
    _id->label(sessionId.c_str());
    _id->align(FL_ALIGN_INSIDE);
    col = fl_rgb_color(236,236,255);
    _id->labelcolor(col);
    end();

};
void FlSessionInfoDisplay::sessionId(string txt){
    _id->label(txt.c_str());
};

void FlSessionInfoDisplay::show(){
    show();
};

void FlSessionInfoDisplay::hide(){
    hide();
};

void FlSessionInfoDisplay::update(){
    redraw();
};
