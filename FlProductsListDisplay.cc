#include <FlProductsListDisplay.H>
#include <FWidgetSizes.H>
#include <winny_theme.h>

    FlProductsListDisplay::FlProductsListDisplay()
        :Fl_Group(CONTENT_AREA.X,CONTENT_AREA.Y,CONTENT_AREA.W,CONTENT_AREA.H), 
        IExtEventSource(){
            begin();
            menuBar = new Fl_Group(MENUBAR_AREA.X,MENUBAR_AREA.Y,MENUBAR_AREA.W,MENUBAR_AREA.H,
            "Product Managment");
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

            searchToken = new Fl_Input(805,96,206,19,"Search Products");
            searchToken->color(FL_WHITE);
            searchToken->box(WINNY_THIN_BORDERBOX);

            menuBarResizer = new Fl_Box(649,100,10,2);
            menuBarResizer->box(WINNY_NO_BORDERBOX);
            menuBar->resizable(menuBarResizer);

            menuBar->end();
            menuBar->box(WINNY_TOP_BORDERBOX);
            prdList = new dataset_view(233,123,776,
            (int)(((double)384/DESIGNSH)*SCRN_HEIGHT));
            prdList->box(WINNY_BOTTOM_BORDERBOX);
            prdList->table_box(WINNY_BOTTOM_BORDERBOX);
            prdList->box(WINNY_TOP_BORDERBOX);
            resizable((Fl_Widget*)prdList);
            end();
        return;
    };

    void FlProductsListDisplay::show(){
        return;
    };
    void FlProductsListDisplay::hide(){
        Fl_Group::hide();
        return;
    };

    void FlProductsListDisplay::update(){
        redraw();
    }

    void FlProductsListDisplay::AddSortOption(string opt){
        return;
    };
    void FlProductsListDisplay::clearSortOptions(){
        return;
    };
    string FlProductsListDisplay::sortOption(){
        return "";
    };
    string FlProductsListDisplay::searchKey(){
        return "";
    };
    void FlProductsListDisplay::addToshowList(Product){
        return;
    }; 
    void FlProductsListDisplay::clearShowList(){
        return;
    };
    string FlProductsListDisplay::selected(){
        return "";
    };