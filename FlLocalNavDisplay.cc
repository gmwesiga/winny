#include <FlLocalNavDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <FL/fl_ask.H>

#define WBUFSIZE 125

static void cbGoToPage ( Fl_Widget* w, void* o);

FlLocalNavDisplay::FlLocalNavDisplay():
    Fl_Tree(LCLNAV_AREA2.X,LCLNAV_AREA2.Y,LCLNAV_AREA2.W,LCLNAV_AREA2.H,"Administrator")
{
    align(FL_ALIGN_TOP_LEFT);
    labelcolor(FL_WHITE);
    labelsize(WINNY_TITLETEXT_FONTSIZE);
    labelfont(WINNY_BOLDFONT);
    showroot(0); //remove it
    usericon(nullptr);
    connectorstyle(FL_TREE_CONNECTOR_NONE);
    connectorwidth(0);
    linespacing(5);
    selection_color(SELECTION_BACKCOLOR());
    marginleft(10);
    selectbox(WINNY_THIN_BORDERBOX);
    item_labelfgcolor(WINNY_LINKTEXT_COLOR);
    item_labelsize(WINNY_NORMALTEXT_FONTSIZE);
    callback(cbGoToPage,(void*)this);
    //when(when()&FL_WHEN_CHANGED);

    //box(WINNY_TOP_BORDERBOX);

};

//dynamically adds a link text to the navigation
//links 
void FlLocalNavDisplay::addLink(UIname pageName){
    add(pageName.c_str());
};

void FlLocalNavDisplay::show(){
    Fl_Tree::show();
};

void FlLocalNavDisplay::hide(){
    Fl_Tree::hide();
};

void FlLocalNavDisplay::update(){
    Fl_Tree::redraw();
};

//cbGoToPage is called whenever a user selects a local menu function.
//its evect is to raise a navigation event to the application
//the application uses the string of the page name to find and display
//the page.
static void cbGoToPage ( Fl_Widget* w, void* o){
    Fl_Tree* tree = (Fl_Tree *)w;
    Fl_Tree_Item* itm = tree->callback_item();
    char path[WBUFSIZE];
    UIname pageName;

    int r = tree->item_pathname(path,WBUFSIZE,itm); //get item absolute path
    if(r)return;                                   //-1 or -2 means error getting path;
    pageName=path;

    //fl_alert(pageName.c_str());
    switch (tree->callback_reason())
    {
        case FL_TREE_REASON_SELECTED:
            //fl_alert(itm->label());
            ((FlLocalNavDisplay*)o)->raiseEvent(CmdNavigateTo,(void*)pageName.c_str());
            break;
    
        default:
            break;
    }
};