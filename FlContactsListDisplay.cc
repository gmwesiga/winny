#include <FlContactsListDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>
#include <WinnyNames.H>

static const UIname PAGENAME(NAME_SEARCH_CONTACT_SCREEN); 

//return name of this function page
UIname FlContactsListDisplay::id()
{return PAGENAME;};

FlContactsListDisplay::FlContactsListDisplay()
    :Fl_Group(CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H){
        begin();
        menuBar = new Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y,MENUBAR_AREA.W,MENUBAR_AREA.H,
        PAGENAME.c_str());
        menuBar->align(FL_ALIGN_TOP_LEFT);
        menuBar->labelcolor(ACCFONTCOLOR);
        menuBar->labelsize(14);

        btnNew = new Fl_Button(233,95,57,19,"New");
        btnNew->color(ACCCOLOR);
        btnNew->labelcolor(FL_WHITE);
        btnNew->box(WINNY_THICK_BORDERBOX);

        filter = new Fl_Menu_Button(341,95,147,19,"Filter by");
        set_winny_button_theme(filter);

        btnActivateToggle = new Fl_Button(494,96,68,19,"Activate");
        set_winny_button_theme(btnActivateToggle);

        btnEdit = new Fl_Button(567,96,68,19,"Edit");
        set_winny_button_theme(btnEdit);

        searchToken = new Fl_Input(805,96,206,19,"Search Contacts");
        set_winny_input_theme(searchToken);
        searchToken->align(FL_ALIGN_LEFT);

        menuBarResizer = new Fl_Box(649,100,10,2);
        menuBarResizer->box(WINNY_NO_BORDERBOX);
        menuBar->resizable(menuBarResizer);

        menuBar->end();
        menuBar->box(WINNY_TOP_BORDERBOX);
        wList = new dataset_view(233,123,776,
        (int)(((double)384/DESIGNSH)*SCRN_HEIGHT));
        wList->box(WINNY_BOTTOM_BORDERBOX);
        wList->table_box(WINNY_BOTTOM_BORDERBOX);
        wList->box(WINNY_TOP_BORDERBOX);
        resizable((Fl_Widget*)wList);
        end();
    return;
};

void FlContactsListDisplay::show(){
    Fl_Group::show();
};
void FlContactsListDisplay::hide(){
    Fl_Group::hide();
};
void FlContactsListDisplay::update(){
    Fl_Group::redraw();
};