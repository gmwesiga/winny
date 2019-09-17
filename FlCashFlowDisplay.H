#ifndef FLCASHFLOWDISPLAY_H
#define FLCASHFLOWDISPLAY_H

#include <IUserInterface.H>
#include <IExtEventSource.h>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Output.H>
#include <dataset_view.h>
#include <IApplicationTypes.H>

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
class FlCashFlowDisplay : public IUserInterface , public Fl_Group{
    public:
    FlCashFlowDisplay();
    void show();
    void hide();
    void update();
    void readBuff(MemAddress buff){buff=0;};//filter to products list
    void writeBuff(MemAddress buff);//matches
    UIname id();
  //  void raiseEvent(StdSystem::sEvent e, void *eData=nullptr);
    void run(){return;};

    private:
    Fl_Button      *btnRefresh, *btnPrint, *btnShare;
    Fl_Choice *optCashFlowType;
    Fl_Output       *txtBeginDate, *txtEndDate;
    dataset_view   *vwCashFlow;
    dataset        *output;
    //Winny::ProductsListFilter fltrParams;
    Fl_Box         *resizer;
};

#endif