#include "FlNavDisplay.h"
#include "winny_theme.h"
#include <FWidgetSizes.H>

FlNavDisplay::FlNavDisplay():Fl_Group(0,33,SCRN_WIDTH,33,"Unkown Entity"){
    begin();
    align(FL_ALIGN_LEFT|FL_ALIGN_INSIDE);
    _menuicon_ = new Fl_PNG_Image("menuicon.png");
    menuicon =  new Fl_Box(993,38,22,18);
    menuicon->image(_menuicon_);
    menuicon->align(FL_ALIGN_INSIDE|FL_ALIGN_RIGHT);
    menuicon->box(WINNY_NO_BORDERBOX);
    end();
};

void FlNavDisplay::show(){
     show();
    };

void FlNavDisplay::hide(){
    hide();
};

void FlNavDisplay::update(){
    redraw();
};

void FlNavDisplay::entityName(string id){
    return;
};

void FlNavDisplay::addNotification(string text, int type){
    return;
};

void FlNavDisplay::clearNotifications(){
    return;
};

void FlNavDisplay::addResponsibility(string desc){
    return;
};

void FlNavDisplay::clearResponsibilities(){
    return;
};

void FlNavDisplay::setRoleName(string desc){
    return;
};

FlNavDisplay::~FlNavDisplay(){
    delete _menuicon_;
    delete menuicon;
};

/*Standardising Panel x,y w,h*/