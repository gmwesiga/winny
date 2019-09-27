#include<FlNotificationDisplay.H>
#include <winny_theme.h>
#include <FWidgetSizes.H>
#include <FL/Fl.H>
#include <FL/fl_ask.H>

static void closeSelf(void* data);
static void showSelf(void* data);
static void cb ( Fl_Widget* w, void* o);
static const int MINHGHT = 7/*23*/;

#define MAXLINES 10
static const char LABEL[] = "";

FlNotificationDisplay::FlNotificationDisplay()
:Fl_Group(NOTFCN_AREA.X,NOTFCN_AREA.Y,NOTFCN_AREA.W,MINHGHT){
    begin();
    box(WINNY_THIN_BORDERBOX);
    color(WINNY_BUTTON_COLOR);
    int xoffset =1;
    int yoffset =xoffset; //normally equal to MINHGHT
    view = new Fl_Hold_Browser(NOTFCN_AREA.X+xoffset,NOTFCN_AREA.Y+xoffset,
        NOTFCN_AREA.W-xoffset*2,MINHGHT,LABEL);
    view->box(WINNY_THIN_BORDERBOX);
    view->color(FL_WHITE);
    //view->scrollbar.type(FL_VERT_NICE_SLIDER);
    //view->scrollbar.slider(WINNY_THICK_BORDERBOX);
    //view->scrollbar.color(color());
    //view->textcolor(WINNY_NORMALTEXT_COLOR);
    //view->callback(cb,(void*)this);
    view->align(FL_ALIGN_TOP_LEFT);
    view->textsize(WINNY_NORMALTEXT_FONTSIZE);
    
    /*No scroll bar*/
    view->has_scrollbar(0);
    view->selection_color(SELECTION_BACKCOLOR());
    minimise();
    end();
};

int FlNotificationDisplay::handle(int e){
    int ret = Fl_Group::handle(e);
    //we want to capture the mouse move events
    switch (e)
    {
        case FL_ENTER:
            restore();
            break;
        case FL_LEAVE:
            minimise();
        default:
            break;
    }
    return ret;
}

static int CLOSED = 1;//initially OPEN (see constructor);


void FlNotificationDisplay::add(std::string message){
    if(view->size()>=MAXLINES)view->clear();
    view->add(message.c_str());
    view->topline(view->size());
    //view->select(view->size());
    
};


void FlNotificationDisplay::restore(){
    if(!CLOSED)return;
    Fl::remove_timeout(showSelf); //we are resetting
    Fl::repeat_timeout(0.005,showSelf,(void*)this); //emmediately restore
}

void FlNotificationDisplay::minimise(){
    if(CLOSED)return;
    Fl::remove_timeout(closeSelf);//we are resetting
    Fl::repeat_timeout(2.0,closeSelf, (void*)this);
}

//progressively hide
static void closeSelf(void* data){
    Fl_Group* vw = (Fl_Group*)data;
    if(vw->h()<=MINHGHT){
        CLOSED = 1;
        Fl::remove_timeout(closeSelf);
         return;
    };
    vw->resize(
        vw->x(),vw->y()+1,
        vw->w(),vw->h()-1);
    vw->parent()->damage(FL_DAMAGE_CHILD);
    //vw->damage(FL_DAMAGE_ALL,NOTFCN_AREA.X,NOTFCN_AREA.Y, NOTFCN_AREA.W,NOTFCN_AREA.H);
    vw->parent()->redraw();
    Fl::repeat_timeout(0.005,closeSelf,(void*)vw);
};

//progressively show
static void showSelf(void* data){
    Fl_Group* vw = (Fl_Group*)data;
    if(vw->h()>=NOTFCN_AREA.H){
        CLOSED=0;
        Fl::remove_timeout(showSelf);
        Fl::repeat_timeout(10,closeSelf,data);
        return;
    };
    vw->resize(
        vw->x(),vw->y()-1,
        vw->w(),
        vw->h()+1);
    vw->parent()->damage(FL_DAMAGE_CHILD);
    //vw->damage(FL_DAMAGE_ALL,NOTFCN_AREA.X,NOTFCN_AREA.Y, NOTFCN_AREA.W,NOTFCN_AREA.H);
    vw->parent()->redraw();
    Fl::repeat_timeout(0.005,showSelf,(void*)vw);
};



static void cb( Fl_Widget* w, void* o){
    //Fl_Group* vw = (Fl_Group*)o; //caution we are checking our group, not the child
    //fl_alert("in callback");
    switch(CLOSED){
        case 1:
            Fl::remove_timeout(showSelf); //we are resetting
            showSelf(o);
            break;
        case 0:
            Fl::remove_timeout(closeSelf); //we are resetting
            closeSelf(o);
        break;
    }
};

