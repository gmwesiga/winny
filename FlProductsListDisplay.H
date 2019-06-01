#ifndef FPRODUCTSLISTDISPLAY_H
#define FPRODUCTSLISTDISPLAY_H

#include <IProductsListDisplay.H>
#include <IExtEventSource.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Box.H>
#include <dataset_view.h>

/*Is both Input and Output Class as itImplements IProductsListDisplay -
 *an output class and IEXtEvents a command input class
 *Events / commands Inputs from this class are
 *  - CmdNavigateTo CreateProduct
 *  - CmdFilterProductsList...
 *  - CmdDeactivateProduct ...
 *  - CmdEditProductDetails ...
 *  - CmdsearchProduct ...
 * Inputs: filter of products to list
 * Outputs List of products matching filter
 * 
 * inputs: searchkey 
 * Outputs:List of all products with a property matching search Key
 * 
 * Inputs: (product selected from output list) and any command (edit 
 * deactivate) 
 * output: perform action and report action feedback
 * 
 * 
 */
class FlProductsListDisplay : public IProductsListDisplay , public Fl_Group{
    public:
    FlProductsListDisplay();
    void show();
    void hide();
    void update();
    void AddSortOption(string opt);
    void clearSortOptions();
    string sortOption();
    string searchKey();
    void addToshowList(Product); 
    void clearShowList();
    string selected();
    void readBuffer(void* buff);//filter to products list
    void writeBuffer(void* buff);//matches
    UIname id();
  //  void raiseEvent(StdSystem::sEvent e, void *eData=nullptr);
    void run(){return;};

    private:
    Fl_Group       *menuBar;
    Fl_Button      *btnNew, *btnActivateToggle, *btnEdit;
    Fl_Menu_Button *filter;
    Fl_Input       *searchToken;
    dataset_view   *prdList;
    
    Fl_Box         *menuBarResizer;
};

#endif