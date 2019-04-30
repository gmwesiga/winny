//winny interface 
//this file defines the main window and all 
//its dialogs. it defines the UI of the application
//g++ -oWINNY winny.cxx  winny_ui.cxx records_lib.cxx -I/usr/local/include/ -L/usr/local/lib/ -lfltk -lole32 -luuid -lcomctl32 -lgdi32 -std=gnu++11 -static-libgcc -static-libstdc++
//12:11pm 19/january/2016
//Author: © Gilbert Mwesiga. gilbert dot mwesiga at gmail dot com

#pragma once
#ifndef id8976154A_2450_42FA_B209B025FE9E2148
#define id8976154A_2450_42FA_B209B025FE9E2148

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Tree.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include "dataset_view.h"
#include "wgt_source_doc_list.h"
#include "loadlist_input.h"
#include "product_view.h"
#include "winny_theme.h"
#include <FL/fl_draw.H>

//main window constants;    
const int
BROWSER_BAR_TMARGIN =20;


void add_delivery_cb(Fl_Widget* w, void* o);
void add_gr_cb(Fl_Widget* w, void* o); //gr =>goods recieved note
void add_reciept_cb(Fl_Widget* w, void*o);

struct compsale_dialog: public Fl_Double_Window  //comp==composite eg route sale
{
  private:
  Fl_Group  *box ;
  Fl_Box    *surface;
  //Fl_Box    *surface2;
  //Fl_Box    *surface3;
  
  public:
  Fl_Choice *client_name;
  Fl_Output *status;
  Fl_Output *doc_num;
  Fl_Input  *date;
  
  //output here.
  Fl_Output *sales;
  Fl_Output *cash;
  Fl_Output *invoice;
  Fl_Output *commission;
  
  source_doc_list *documents;
  
  //buttons
  Fl_Button    *create;
  Fl_Button    *save_changes;
  Fl_Button    *ok;
  Fl_Button    *cancel;
  Fl_Menu_Button  *create_menu;
  Fl_Button    *remove;

  
  //const
  compsale_dialog(int X=0, int Y=0, int W=0, int H=0, const char *L=0):Fl_Double_Window(X,Y,675,430,L)
  {
    color(WINDOW_COLOR());
    labelcolor(DOMFONT_COLOR()); 
    labelsize(DOMFONT_SIZE());
    
    surface = new Fl_Box(7,5,655,357);
    surface->box(WINNY_THIN_BORDERFRAME);
    //surface->color(DOMWGT_COLOR());
    //surface2 = new Fl_Box(7,5,655,357);
    //surface2->box(FL_BORDER_FRAME);
    //surface2->color(DOMWGT_COLOR());
    //surface3 = new Fl_Box(19,71,630,248);
    //surface3->box(FL_BORDER_FRAME);
    
    client_name = new Fl_Choice(20,33,293,22,"Sales Rep");
    client_name->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
    client_name->color(WINDOW_COLOR());
    client_name->labelcolor(DOMFONT_COLOR()); 
    client_name->textcolor(DOMFONT_COLOR()); //text color;
    client_name->labelsize(DOMFONT_SIZE()); 
    client_name->textsize(DOMFONT_SIZE());   //text size
    client_name->box(FL_FLAT_BOX);
    //...
    date = new Fl_Input(332,35,98,22,"Date");
    date->align(FL_ALIGN_LEFT|FL_ALIGN_TOP);
    date->color(DOMWGT_COLOR());
    date->labelcolor(DOMFONT_COLOR()); 
    date->textcolor(DOMFONT_COLOR()); //text color;
    date->labelsize(DOMFONT_SIZE()); 
    date->textsize(DOMFONT_SIZE());   //text size
    //...
    status = new Fl_Output(519,35,60,22,"Status");
    status->align(FL_ALIGN_LEFT|FL_ALIGN_TOP);
    status->color(DOMWGT_COLOR());
    status->labelcolor(DOMFONT_COLOR()); 
    status->textcolor(DOMFONT_COLOR()); //text color;
    status->labelsize(DOMFONT_SIZE()); 
    status->textsize(DOMFONT_SIZE());   //text size
    status->box(WINNY_THIN_BORDERBOX);
    //...
    doc_num = new Fl_Output(585,35,64,22,"No.");
    doc_num->align(FL_ALIGN_LEFT|FL_ALIGN_TOP);
    doc_num->color(DOMWGT_COLOR());
    doc_num->labelcolor(DOMFONT_COLOR()); 
    doc_num->textcolor(DOMFONT_COLOR()); //text color;
    doc_num->labelsize(DOMFONT_SIZE()); 
    doc_num->textsize(DOMFONT_SIZE());   //text size
    doc_num->box(WINNY_THIN_BORDERBOX);
    
    box = new Fl_Group(20,89,628,230);
    //box->align(FL_ALIGN_LEFT|FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    box->box(FL_BORDER_FRAME);
    //....
    box->begin();
      documents = new source_doc_list(21,90,628,200,"Transactions");
      documents->align(FL_ALIGN_LEFT|FL_ALIGN_TOP);
      documents->box(WINNY_THIN_BORDERFRAME);
      documents->labelcolor(DOMFONT_COLOR()); 
      documents->labelsize(DOMFONT_SIZE()); 
      
      create_menu = new Fl_Menu_Button(21,293,103,21,"Add New");
      create_menu->color(DOMWGT_COLOR());
      create_menu->labelcolor(DOMFONT_COLOR()); 
      create_menu->textcolor(DOMFONT_COLOR()); //text color;
      create_menu->labelsize(DOMFONT_SIZE()); 
      create_menu->textsize(DOMFONT_SIZE());   //text size
	  
    box->end();
    //...
    sales = new Fl_Output(64,324,88,22,"Sales");
    sales->color(DOMWGT_COLOR());
    sales->labelcolor(DOMFONT_COLOR()); 
    sales->textcolor(DOMFONT_COLOR()); //text color;
    sales->labelsize(DOMFONT_SIZE()); 
    sales->textsize(DOMFONT_SIZE());   //text size
    sales->box(WINNY_THIN_BORDERBOX);
    //...
    cash  = new Fl_Output(198,324,88,22,"Cash");
    cash->color(DOMWGT_COLOR());
    cash->labelcolor(DOMFONT_COLOR()); 
    cash->textcolor(DOMFONT_COLOR()); //text color;
    cash->labelsize(DOMFONT_SIZE()); 
    cash->textsize(DOMFONT_SIZE());   //text size
    cash->box(WINNY_THIN_BORDERBOX);
    //..
    invoice = new Fl_Output(352,324,88,22,"Invoice");
    invoice->color(DOMWGT_COLOR());
    invoice->labelcolor(DOMFONT_COLOR()); 
    invoice->textcolor(DOMFONT_COLOR()); //text color;
    invoice->labelsize(DOMFONT_SIZE()); 
    invoice->textsize(DOMFONT_SIZE());   //text size 
    invoice->box(WINNY_THIN_BORDERBOX);
    //...
    commission = new Fl_Output(525,324,88,22,"Commission");
    commission->color(DOMWGT_COLOR());
    commission->labelcolor(DOMFONT_COLOR()); 
    commission->textcolor(DOMFONT_COLOR()); //text color;
    commission->labelsize(DOMFONT_SIZE()); 
    commission->textsize(DOMFONT_SIZE());   //text size 
    commission->box(WINNY_THIN_BORDERBOX);
    
    //buttons
    create = new Fl_Button(19,385,80,25,"create");
    save_changes = new Fl_Button(103,385,80,25,"save changes");
    ok = new Fl_Button(527,385,60,25, "ok");
    cancel = new Fl_Button(590,385,60,25,"cancel");
    set_non_modal();
    end();
    
  }
};



struct loadlist_dialog: Fl_Double_Window
{
  private:
  Fl_Box  *box ;
  //Fl_Box    *surface;
  //Fl_Box    *surface2;
  //Fl_Box    *surface3;
  
  public:
  Fl_Input *client_name;
  Fl_Output *doc_num;
  Fl_Input  *date;  
  Fl_Int_Input *cash_received;
  Fl_Output *value;
  
  loadlist_input *list;
  
  //buttons
  Fl_Button    *create;
  Fl_Button    *save_changes;
  Fl_Button    *ok;
  Fl_Button    *cancel;
  Fl_Menu_Button  *create_menu;
  Fl_Button    *remove;
  
  loadlist_dialog(int x=0, int y=0, int w=0, int h=0, const char* l=0):Fl_Double_Window(x,y,415,445,l)
  {
    color(WINDOW_COLOR());
    labelcolor(DOMFONT_COLOR()); 
    labelsize(DOMFONT_SIZE());
    
    client_name = new Fl_Input(13,61,383,22,"Client");
    client_name->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
    client_name->color(WINDOW_COLOR());
    client_name->labelcolor(DOMFONT_COLOR()); 
    client_name->textcolor(DOMFONT_COLOR()); //text color;
    client_name->labelsize(DOMFONT_SIZE()); 
    client_name->textsize(DOMFONT_SIZE());   //text size
    client_name->box(WINNY_THIN_BORDERBOX);;
    //...
    date = new Fl_Input(209,17,98,22,"Date");
    date->align(FL_ALIGN_LEFT);
    date->color(DOMWGT_COLOR());
    date->labelcolor(DOMFONT_COLOR()); 
    date->textcolor(DOMFONT_COLOR()); //text color;
    date->labelsize(DOMFONT_SIZE()); 
    date->textsize(DOMFONT_SIZE());   //text size
    date->box(WINNY_THIN_BORDERBOX);
    //...
    doc_num = new Fl_Output(332,17,64,22,"No.");
    doc_num->align(FL_ALIGN_LEFT);
    doc_num->color(FL_WHITE);
    doc_num->labelcolor(DOMFONT_COLOR()); 
    doc_num->textcolor(DOMFONT_COLOR()); //text color;
    doc_num->labelsize(DOMFONT_SIZE()); 
    doc_num->textsize(DOMFONT_SIZE());   //text size
    doc_num->box(WINNY_THIN_BORDERBOX);
    
    box = new Fl_Box(13,107,383,260);
    //box->align(FL_ALIGN_LEFT|FL_ALIGN_TOP|FL_ALIGN_INSIDE);
    box->box(FL_BORDER_FRAME);
    //....
    //box->begin();
      list = new loadlist_input(13,107,383,230,"Particulars");
      list->align(FL_ALIGN_LEFT|FL_ALIGN_TOP);
      
      list->box(WINNY_THIN_BORDERFRAME);
      //Watch the box type you put here!
      //After 2 days of confusion, i found out setting this box to a none
      //frame box cases table not to show child widgets! i don't know why
      //but to reproduce the problem, set box here to a Box type, things 
      //will go bazzack but if you ignore setting this figure, or set 
      //it to a frame box, everthing works fine
      //digging further, i found that the fl_table widget team seems to be 
      //aware of this, and that is why they provided this api
      //list->table_box(WINNY_THIN_BORDERBOX);
      //trying it out instead, could actually give you a view about where you
      //thought the table dimesions are. 24/jan/2016 11:27pm
      list->labelcolor(DOMFONT_COLOR()); 
      list->labelsize(DOMFONT_SIZE()); 
      list->color(DOMWGT_COLOR());
      
      value = new Fl_Output(52,341,74,22,"Total");
      value->color(DOMWGT_COLOR());
      value->labelcolor(DOMFONT_COLOR()); 
      value->textcolor(DOMFONT_COLOR()); //text color;
      value->labelsize(DOMFONT_SIZE()); 
      value->textsize(DOMFONT_SIZE());   //text size
      value->box(WINNY_THIN_BORDERBOX);
      
      cash_received = new Fl_Int_Input(311,340,74,22,"Cash Paid");
      cash_received->color(DOMWGT_COLOR());
      cash_received->labelcolor(DOMFONT_COLOR()); 
      cash_received->textcolor(DOMFONT_COLOR()); //text color;
      cash_received->labelsize(DOMFONT_SIZE()); 
      cash_received->textsize(DOMFONT_SIZE());   //text size
      cash_received->box(WINNY_THIN_BORDERBOX);     
    //box->end();
    
    create       = new Fl_Button(12,408,59,25,"create");
    save_changes = new Fl_Button(75,408,80,25,"save changes");
    ok           = new Fl_Button(276,408,60,25, "ok");
    cancel       = new Fl_Button(339,408,60,25,"cancel");
  
    { //buttons
      
      Fl_Button * pbutton[]={create,save_changes,ok, cancel};
      for (int i=0; i<4; ++i)
      {
        pbutton[i]->color(WINDOW_COLOR());
        pbutton[i]->labelcolor(DOMFONT_COLOR()); 
        pbutton[i]->labelsize(DOMFONT_SIZE());
        pbutton[i]->box(WINNY_THICK_BORDERBOX);
      }
    }  
    end();
    set_non_modal();
  }
  
  void data(load_list* w)
  {
	client_name->value( w->client_name().c_str());
	vector<load_item> temp = w->list();
	list->value(temp);
  }
};



//RECEIPT DIALOG BOX;
struct receipt_dialog: Fl_Double_Window
{
  Fl_Int_Input *cash_received;
  Fl_Input     *client_name;
  Fl_Group     *date;
  Fl_Int_Input *day;    
  Fl_Int_Input *month;
  Fl_Int_Input *year;
  
  Fl_Button    *create;
  Fl_Button    *save_changes;
  Fl_Button    *ok;
  Fl_Button    *cancel;
  
  receipt_dialog(int X, int Y, int W, int H,const char* L):Fl_Double_Window(X,Y,W,H)
  {
    w(350); h(260);
    W=w(); H=h();
    color(WINDOW_COLOR());
    surface = new Fl_Box(4,4, W-8,H-50);
    surface2 = new Fl_Box(surface->x()-1, surface->y()-1, surface->w()+1, surface->h()+1);
    surface2->box(FL_BORDER_FRAME);
    surface->color(DOMWGT_COLOR());
    surface->box(FL_FLAT_BOX);
    
    char label[50];
    strcat(label,L);
    strcat(label," Receipt");
    copy_label(label);        //label 
   
    int xpos{20}, width{200}, height{30}, sector;   //all controlls share these.
    sector=height+height/2 +10;
    
    int bottom_margin = 25;
  
    int margin_top=35;
    
    //client_name
    client_name = new Fl_Input(xpos,(margin_top),width,height,"Reieved from ");
    client_name->box(FL_THIN_DOWN_BOX);
    client_name->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
    client_name->labelcolor(DOMFONT_COLOR()); client_name->textcolor(DOMFONT_COLOR()); //text color;
    client_name->labelsize(DOMFONT_SIZE()); client_name->textsize(DOMFONT_SIZE());   //text size
    
    cash_received = new Fl_Int_Input(xpos,(client_name->y()+sector), width, height, "the sum of ");
    cash_received->box(FL_THIN_DOWN_BOX);
    cash_received->align(FL_ALIGN_TOP|FL_ALIGN_LEFT);
    cash_received->labelcolor(DOMFONT_COLOR()); 
    cash_received->textcolor(DOMFONT_COLOR()); //text color;
    cash_received->labelsize(DOMFONT_SIZE()); 
    cash_received->textsize(DOMFONT_SIZE());   //text size
    
    { //date 
    int datex(xpos);                            //Positions of date widgets;   //remember to factor out this class;
    date = new Fl_Group(xpos,cash_received->y()+sector+10,width,height,"date");
    date->box(FL_BORDER_FRAME);
    date->labelcolor(DOMFONT_COLOR()); date->labelsize(DOMFONT_SIZE());
    date->align(FL_ALIGN_LEFT|FL_ALIGN_TOP);
    date->begin();
      int labelw, inputw, space, x1, x2, x3, y, yearw, h;
      labelw =28; 
      inputw =20; 
      space  =4;
      x1     =datex+labelw+space;   
      x2     =datex+(labelw+space)*2 +inputw;   
      x3     =datex+(labelw+space)*3 +(2*inputw); 
      y      =date->y()+4;  
      yearw  =(3/width)-labelw;
      h      =height-6;
        
      day = new Fl_Int_Input(x1,y,inputw,h,"dd");
      day->box(FL_THIN_DOWN_BOX);
      day->labelcolor(DOMFONT_COLOR()); day->textcolor(DOMFONT_COLOR()); //text color;
      day->labelsize(DOMFONT_SIZE()); day->textsize(DOMFONT_SIZE());   //text size

      day->align(FL_ALIGN_LEFT);
      month = new Fl_Int_Input(x2,y,inputw,h,"mm");
      month->labelcolor(DOMFONT_COLOR()); month->textcolor(DOMFONT_COLOR()); //text color;
      month->labelsize(DOMFONT_SIZE()); month->textsize(DOMFONT_SIZE());   //text size
      
      
      month->align(FL_ALIGN_LEFT);
      year= new Fl_Int_Input(x3,y,inputw*2,h,"yyyy");
      year->labelcolor(DOMFONT_COLOR()); year->textcolor(DOMFONT_COLOR()); //text color;
      year->labelsize(DOMFONT_SIZE()); year->textsize(DOMFONT_SIZE());   //text size
    date->end();
    }
    
    { //buttons
      int height, width, y, cx, sx, ox, csx;
      height = 25;
      width  = W/5;
      y      = H-height -10;
      cx     = 20;
      sx     = width+cx+4;
      ox     = width+sx +4;
      csx    = width+ox +4;
      create       = new Fl_Button(cx, y, width, height, "create");
      save_changes = new Fl_Button(sx, y, width, height, "save");
      ok           = new Fl_Button(ox, y, width, height, "ok");
      cancel       = new Fl_Button(csx, y, width, height, "cancel");
      
      Fl_Button * pbutton[]={create,save_changes,ok, cancel};
      for (int i=0; i<4; ++i)
      {
        pbutton[i]->color(WINDOW_COLOR());
        pbutton[i]->labelcolor(DOMFONT_COLOR()); 
        pbutton[i]->labelsize(DOMFONT_SIZE());
      }
    }
    set_non_modal();
    end(); //end dialog
  }
    
  private:
  //ui widgets
  Fl_Box     *surface;
  Fl_Box     *surface2;
};
  
struct product_dialog: Fl_Double_Window
{
  product_view *product;
  Fl_Button   * ok;
  Fl_Button    *cancel;

  product_dialog(int x=0, int y=0, int w=0, int h=0, char* l=0)
  :Fl_Double_Window(x,y,300,410,l) {
    product = new product_view(2,2,250,400);
    ok = new Fl_Button(21,389,53,25);
    set_winny_button_theme(ok);
    cancel = new Fl_Button(193,389,45,25);
    set_winny_button_theme(cancel);
    
    end();
    set_non_modal();
  }
};
  
  
//THE APPLICATION MAIN WINDOW INTERFACE;
//CREATES A HIERACHY OF ALL ITS COMPONENTS  
struct  winny_window: Fl_Double_Window
{
  public:
    Fl_Menu_Bar     *main_menu;
    Fl_Tree         *browser_bar;
    dataset_view *documents_list;
    receipt_dialog  *receipt_view;
    compsale_dialog *routesale_window;
    loadlist_dialog *load_window;
    product_dialog  *product_window;

    winny_window(int X, int Y, int W, int H, const char *L=0)
  :Fl_Double_Window(X,Y,W,H,L)
  {
    //main window
      color(WINDOW_COLOR());
    //menue bar
      int menu_bar_height = 25;
      main_menu = new Fl_Menu_Bar(0,0,W,menu_bar_height);
      main_menu->box(WINNY_THIN_BORDERBOX);                                            //remove around bar default box 
      main_menu->color(MENUBAR_COLOR());
      main_menu->selection_color(SELECTION_BACKCOLOR());
      main_menu->textsize(DOMFONT_SIZE());
      main_menu->textcolor(DOMFONT_COLOR());
      
     // browser side bar
      int browser_bar_y = menu_bar_height;
      browser_bar       = new Fl_Tree(0, browser_bar_y,150,H-browser_bar_y); //width is 30%
      browser_bar->showroot(false); //dont show root icon
      browser_bar->connectorstyle(FL_TREE_CONNECTOR_NONE); //dont show connection lines
      browser_bar->selection_color(SELECTION_BACKCOLOR());
      browser_bar->item_labelsize(DOMFONT_SIZE());
      browser_bar->item_labelfgcolor(DOMFONT_COLOR());
     
     //the following code should be removed from here, and put in the main program since it varries and would
      //need callbacks;
      browser_bar->begin(); //this
        browser_bar->add("DashBoard/Products");
        browser_bar->add("DashBoard/Stock Movement Report");
      browser_bar->end();  //upto here
      
      documents_list = new dataset_view(148,browser_bar_y,W-150,H-browser_bar_y);//new source_doc_list()
      resizable(documents_list);
      end();
      //dialogs
      receipt_view = new receipt_dialog(50, 50, 350, 500, "New");
      routesale_window = new compsale_dialog(); //we can ignore all arguments;
      load_window      = new loadlist_dialog(); 
      product_window  = new product_dialog();
      receipt_view->hide();
      
      //end()
      //..
  }
  
};

#endif // header
