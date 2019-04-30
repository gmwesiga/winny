#include "FlSessionInfoDisplay.h"
#include <FL/Fl.H>
#include "winny_theme.h"
#include <FWidgetSizes.H>

FlSessionInfoDisplay::FlSessionInfoDisplay(string sessionId)
:Fl_Group(0,0,SCRN_WIDTH,33,"WINNY"){
    begin();
    Fl_Color col  = fl_rgb_color(147,147,255);
    color(col);
    id = new Fl_Output(831,5,176,23);
    id->color(col);
    id->label(sessionId.c_str());
    id->align(FL_ALIGN_INSIDE);
    col = fl_rgb_color(236,236,255);
    id->labelcolor(col);
    end();

};
void FlSessionInfoDisplay::sessionId(string txt){
    id->label(txt.c_str());
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