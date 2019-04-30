#ifndef IPRODUCTSLISTDISPLAY_H
#define IPRODUCTSLISTDISPLAY_H

#include "SystemTypes.h"
#include "IUserInterface.h"
#include "Product.h"

class IProductsListDisplay : public IUserInterface {
    public:
    virtual void show()=0;
    virtual void hide()=0;
    virtual void update()=0;
    virtual void AddSortOption(string opt)=0;
    virtual void clearSortOptions()=0;
    virtual string sortOption()=0;
    virtual string searchKey()=0;
    virtual void addToshowList(Product)=0; 
    virtual void clearShowList()=0;
    virtual string selected()=0;
};

#endif
/*Notes:
 *AddToShowList();
 *getting right name for this interface
 *was not easy... initial proposals were addProduct(), writeProduct(), but these
 *didn't capture the UI screen abstraction which "shows"  not storage semantics
 */
/*AddSortOption()
 *First proposal of AddSortOption() interface was AddSortOption(vector<string>)
 *But We realised that was going to make our interface tied to an implementation
 *detail ie std::vector, so we would rather stick to a generic add(string)*/

 /*Class naming issues:
  Wanted a class name that captures the fact that this screen is used to manage 
  product records. my first try was productManager. Droped it because it seems to
  mean the abstraction manages (does some computing). yet actually it only displays
  (outputs). so i came up with productsBrowser. i felt browser brings a meaning i want
  ... the abstraction is used to browse! but later on, when i started thinking about what
  name to give to the window used to view a single product, i realised browser could still
  pass. i mean, a products browser should be used to also view the products. i figured
  this name was not ok. As i thought about it, i realised something! that actually this interface
  is a search interface... its only used to choose a product... and is part of the bigger 
  products browswer interface. so probally it should be called IProductSearch
  ....after more thought i now feel that productsearch would also crash with product selection
  dialogs.. now i feel that this should be productslistDisplay, then the single products page becames
  productsDetailsDisplay while the dialog becames productsSearch*/