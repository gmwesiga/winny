#include "winny_Window.h"
#include "records_lib.h"
#include <ctime>
typedef Fl_Widget wWidget;

//dialog windows
static winny_window      *app_window  = 0;
static loadlist_dialog   *load_window = 0;
static compsale_dialog   *rs_window   = 0;
static product_dialog   *product_window = 0;

//app wide shared data
static Product_Table     *product_table=0;
static dataset  *productTable_ds=0;
static dataset *stockMovt_report=0;

//other
static vector<source_document*>  active_csale; 
static load_list    * active_load =0;

//application interface
void create_new_product(Product& p);
void ui_create_new_product();

//callbacks
void btnok_create_new_product(wWidget*w,void* o);
void menu_create_new_product(wWidget*w,void*o);
void sidebar_cb(wWidget* w, void* o);

void position_dialog(Fl_Widget* dialog, winny_window* window)
{
 // return;
  int posx,posy;
    posx = window->x()+(window->w()/2-dialog->w()/2);
    posy = window->y()+(window->h()/2-dialog->h()/2);
    dialog->position(posx,posy);
}

void createload_cb  (Fl_Widget* w, void*o)
{
  if(!load_window)return;
  if(load_window->shown())
  {return; }
  else
  {
    position_dialog(load_window,app_window);
    load_window->show();
  }  
};

void show_dialog  (Fl_Window* w)
{
  if(!w)return;
  if(w->shown())
  {return; }
  else
  {
    position_dialog(w,app_window);
    w->show();
  }  
}


void createproduct_cb  (Fl_Widget* w, void*o)
{
  if(!product_window)return;
  if(product_window->shown())
  {return; }
  else
  {
    position_dialog(product_window,app_window);
    product_window->show();
  }  
}

void display_load(load_list& l)
{
	load_window->client_name->value(l.client_name().c_str());
	load_window->doc_num->value("xxxx");
	//load_window->date->value()
	//value
	load_window->list->value(l.list());
	createload_cb(load_window,0);
}

load_list get_load(){
	vector<load_item>temp;
	temp = load_window->list->value();
	//printf("\n..before sizeof Del:%d\n",temp.size() ); //test
	load_list l;
	l.client_name(load_window->client_name->value());
	l.list(temp);
	return l;
}

void add_receipt_cb ( Fl_Widget* w, void* o)
{
  winny_window* window = ((winny_window*)o);
  if(window->receipt_view->shown())
  {return; }
  else
  {
    position_dialog(window->receipt_view,window);
    //deactivate save and ok buttons;
    window->receipt_view->save_changes->deactivate();
    window->receipt_view->ok->deactivate();
    window->receipt_view->show();
    window->receipt_view->copy_label("Create New Receipt");   //update label
    
    std::time_t now = std::time(0);   // time now as timestamp
    std::tm  *calendar_now = std::localtime(&now);
    char dd[3], mm[2], yy[5];
    sprintf(dd, "%d", calendar_now->tm_mday);
    sprintf(mm, "%d", calendar_now->tm_mon+1);
    sprintf(yy, "%d", calendar_now->tm_year+1900);
    
    window->receipt_view->day->value(dd);
    window->receipt_view->month->value(mm);
    window->receipt_view->year->value(yy);
  }
  return;
}

void create_routesale_cb(Fl_Widget* w, void* o)
{
  winny_window* window = (winny_window*)o;
  position_dialog(window->routesale_window, window);
  window->routesale_window->copy_label("Create New Route Sale");   //update label
  window->routesale_window->show();
}


void rs_edit_load(Fl_Widget* w, void* o)
{
	printf("%d",*((int*)o) );
	*(active_csale[*((int*)o)]) = get_load(); //*(int*(o))] => dereference int pointer
	rs_window->documents->refresh();
	load_window->hide();
}



void rs_createDel_ok(Fl_Widget* w, void* o);
static int rs_index = 0; //index of selected document

void sourceDocWgt_cb(Fl_Widget* w, void* o)
{
	source_doc_list* _list = ((source_doc_list*)w);
  
  //if double click && in varied region
  if(Fl::event_clicks()&& _list->callback_context()==Fl_Table::CONTEXT_CELL){ 
	//reset so other widgets don't handle. //see Fl documentation 
	Fl::event_clicks(0); 
	//if list not empty
	  if( _list->data_source()->size()) 
	  {
		  rs_index = _list->callback_row();
		  source_document* selected_doc = (*(_list->data_source()))[rs_index];
		  
		  switch(selected_doc->type_code()) //document selected
		  {
			case LOAD_IN:
			case LOAD_OUT:
			case GENERIC_LOAD:
				display_load(*((load_list*)selected_doc));
				//load_window->data((load_list*)selected_doc);
				load_window->ok->callback(&rs_edit_load,(void*)&rs_index);
			    //createload_cb(load_window,0);   //display
				
				break;
		  }
		  
	  }
  }
}


void balance_rsale(vector<source_document*> rs);

void rs_createDel_ok(Fl_Widget* w, void* o)
{
	//coppy load in dialog into current route sale record
		//get handle to load in dialog and copy
		load_out* lo = new load_out(get_load());
		//insert it into current route sale record
		active_csale.push_back((source_document*)lo);
		//close dialog and refresh rs_window to update display
		rs_window->documents->refresh();
		load_window->hide();	
}

void rs_createGR_ok(Fl_Widget* w, void* o)
{
	//coppy load in dialog into current route sale record
		//get handle to load in dialog and copy
		load_in* lo = new load_in(get_load());
		// insert into route_sale record
		active_csale.push_back((source_document*)lo);
		balance_rsale(active_csale);
		//close dialog and refresh rs_window to update display
		rs_window->documents->refresh();
		load_window->hide();
}

void rs_createDel_cb(Fl_Widget* w, void* o)
{
	load_window->ok->callback(& rs_createDel_ok);
	createload_cb(w,o);	
}



void rs_createGR_cb(Fl_Widget* w, void* o)
{
	//set handler when user clicks ok
	load_window->ok->callback(& rs_createGR_ok);
	//display dialog
	createload_cb(w,o);	
}

vector<load_item> get_rsLoadOut(vector<source_document*> rs)
{
	//just get the first record for now.
	for (int i=0; i<rs.size(); i++)
	{
		if(rs[i]->type_code()==LOAD_OUT) return ((load_list*)(rs[i]))->list();
	}
	
	//just return a blank 
	vector<load_item> i;
	return i;
}

vector<load_item> get_rsLoadIn(vector<source_document*>rs)
{
	//just get the first record for now.
	for (int i=0; i<rs.size(); i++)
	{
		if(rs[i]->type_code()==LOAD_IN) return ((load_list*)(rs[i]))->list();
	}
	
	//just return a blank 
	vector<load_item> i;
	return i;
}


void balance_rsale(vector<source_document*> rs)
{
	//get loadout, convert it: algoritnm knows component, a variation of load_list
	vector<Component> loadOut = loadItems_to_components(get_rsLoadOut(rs));
	printf("in balance\n");
	
	//get in, convert it: algoritnm knows component, a variation of load_list
	vector<Component> loadIn = loadItems_to_components(get_rsLoadIn(rs));

	//compute sale
	vector<load_item> sales = components_to_loadItems(
	  difference(*product_table,loadOut,loadIn )
	  );
	  
	//insert sales record in rs
	load_list* sales_rec = new load_list();
	sales_rec->list(sales);
	active_csale.push_back((source_document*)sales_rec);
	rs_window->documents->refresh();
}


void exit_cb(Fl_Widget* w, void* o)
{
  winny_window* window = (winny_window*)o;
  window->routesale_window->hide();
  window->receipt_view->hide();
  window->hide();

}

const int MENUE_NUM = 10;  
struct{char item[30];  
       void (*callback)(Fl_Widget*, void*);
       } menu_options[MENUE_NUM] = 
  {{"Create/Product",menu_create_new_product},
	{"Create/Receipt",add_receipt_cb},  
   {"Create/Delivery Note",createload_cb},   
   {"Create/Goods Recieved Note",createload_cb},
   {"Create/Invoice",createload_cb},  
   {"Create/Cheque",0}, 
   {"Create/Route Sale",create_routesale_cb}, 
   {"Create/Cash Sale",createload_cb},
   {"Performance Tools",0},   
   {"Options",0} 
  };  
  
   
int main(void)
{
  init_ui();
  winny_window* window;
  window = new winny_window(10,10,800,600,"winny");
  window->callback(exit_cb,window);
  
  //initialise our global app data
  app_window  = window;         
  load_window = window->load_window;
  product_window = window->product_window;
  printf("in main..pv(%p)\n",product_window->product);
  
  //routesale dialog initialisation
  rs_window  = window->routesale_window;
  rs_window->documents->data_source(&active_csale);
  rs_window->create_menu->add("Load Out",0,&rs_createDel_cb);
  rs_window->create_menu->add("Load In",0,&rs_createGR_cb);
  
  rs_window->documents->callback(&sourceDocWgt_cb);
  rs_window->documents->when(FL_WHEN_RELEASE_ALWAYS);

  window->browser_bar->callback(& sidebar_cb);
  window->browser_bar->when(FL_WHEN_RELEASE_ALWAYS);
  
  product_table = open_ftable("productsTable.txt");
  if(product_table)
  {
    //printf("loaded");
    load_window->list->product_list(product_table->data());
  }
  
  
  //set up menues
    //window->main_menu->add(menu_options[0],0,&add_receipt_cb,window);
     for(int i=0; i<MENUE_NUM-1; ++i ) 
       window->main_menu->add(menu_options[i].item,0,menu_options[i].callback, window);  //main_menu->copy(menu_options) is buggy
   
   
   //Initialise dataset view_
   dataset ds(100,20);
   stockMovt_report = &ds;
   for(int row=0;row<ds.rows();++row){
   	//ds.set_col_header(row, table_data("column"));
   	for(int col=0;col<ds.cols();++col){
	   int t= row+col;
	   ds.data(row,col,table_data(row*col));
	}
   }	

   productTable_ds = new dataset(0,0);
   product_table->sort_size();
   productTable_to_dataset(*product_table,*productTable_ds);
   window->documents_list->attach_dataset(productTable_ds);
  window->documents_list->take_focus();
  
  window->show();
  return Fl::run();
}



void smr_cb(wWidget*,void*);
void prdts_cb(wWidget*,void*);

void sidebar_cb(wWidget* w, void* o)
{
 //we handle clicks only
 if(!(Fl::event()==FL_PUSH)) return;
  Fl_Tree * tree = (Fl_Tree*)w;
  Fl_Tree_Item *item = tree->callback_item();
  if(tree->callback_reason()==FL_TREE_REASON_SELECTED){
	  if(item==tree->find_item("DashBoard/Products")){
		  if(app_window->documents_list->get_dataset()==productTable_ds)return;
		  app_window->documents_list->attach_dataset(productTable_ds);
		  app_window->documents_list->callback(&prdts_cb);
		  app_window->documents_list->when(app_window->documents_list->when()&FL_WHEN_CHANGED );
		  return;
	  }else if(item==tree->find_item("DashBoard/Stock Movement Report")){
		  if(app_window->documents_list->get_dataset()==stockMovt_report)return;
		  app_window->documents_list->attach_dataset(stockMovt_report);
		  app_window->documents_list->callback(&smr_cb);
		  app_window->documents_list->when(FL_WHEN_RELEASE);
		  return;
	  }
  }

}


void smr_cb(wWidget *w, void* o){
	dataset_view * dsv = (dataset_view*) w;
	dataset * ds = dsv->get_dataset();
	for(int r=0; r<ds->rows(); ++r){
		for(int c=0; c<ds->cols(); ++c){
			if(ds->data(r,c).type()==NUMBER){
				double num = rand()*c*r;
				ds->data(r,c).number(num);
				if(num>99999)ds->data(r,c).style().forecolor = {254,0,0};
			}
		}
	}
	ds->resume_events();
	ds->data(0,0,table_data(rand()));
	//printf("updated smr_cb\n");
}


/**callback: runs if ui-dataset_view is displaying product list
 **and user changes selected entry 
 **/
void prdts_cb(wWidget* w,void*){
	dataset* ds = ((dataset_view*)w)->get_dataset();
	int row = ((dataset_view*)w)->selected();
	Product p = product_table->find_product(ds->data(row,0).cstring());
	product_window->product->attach_product(&p);
	product_window->product->attach_product_table(product_table);
	show_dialog(product_window);
};

void create_new_product(Product& p){
	product_table->add(p);
	productTable_ds->resume_events();
	productTable_to_dataset(*product_table,*productTable_ds);
	//maybe insert into database
	product_window->hide();
};

void ui_create_new_product(){
	Product p;
	product_window->product->attach_product(&p);
	product_window->product->attach_product_table(product_table);
	product_window->ok->callback(&btnok_create_new_product,product_window->product);
	product_window->ok->copy_label("create");
	show_dialog(product_window);

};

void btnok_create_new_product(wWidget*w,void* o){
	create_new_product(*(((product_view*)o)->get_product()));
};

void menu_create_new_product(wWidget*w, void* o){
	ui_create_new_product();
}