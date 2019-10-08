objects = winny.o FlScreen.o IExtEventSource.o \
            winny_theme.o \
			FlCreateProductDisplay.o FlListDisplay.o\
			dataset.o dataset_view.o table_data.o color.o FlCreateContactDisplay.o \
			Application.o FlNotificationDisplay.o FlOffPremiseSaleUserIO.o \
			FlCashFlowDisplay.o WinnyUserPrompts.o time.o FlStockTransactionDisplay.o \
			w_transaction.o
commonUIHeaders = FWidgetSizes.H winny_theme.h WinnyUserPrompts.H

FLDLIBS = -mwindows -lfltk_images -lfltk_png -lfltk_z -lfltk -lole32 -luuid -lcomctl32
#FLDLIBS = -lfltk_images -lfltk_png -lfltk_z -lfltk -lpthread -ldl -lm -lX11

FLDFLAGS = -L/usr/local/lib
FLCXXFLAGS = -g -I. -I/usr/local/include -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE \
              -D_THREAD_SAFE -D_REENTRANT  -std=gnu++11 #FLCXXFLAGS = FLTK CXX FLAGS
#remember to remove -g option in production
CXXFLAGS += $(FLCXXFLAGS)
LDLIBS += $(FLDLIBS)
LDFLAGS += $(FLDFLAGS)

winny : $(objects)
	g++ -owinny $(objects) $(LDFLAGS) $(LDLIBS)
#	rm *o

winny.o           : IScreen.h  IExtEventSource.h FlScreen.h
winny_theme.o     : winny_theme.cc winny_theme.h
Application.o     : Application.H
IExtEventSource.o : IExtEventSource.h IApplication.h
FlScreen.o        : FlScreen.h IExtEventSource.h IScreen.h $(commonUIHeaders)
#FlSessionInfoDisplay.o : FlSessionInfoDisplay.h $(commonUIHeaders)
#FlNavDisplay.o         : FlNavDisplay.h $(commonUIHeaders)
#FlProductsListDisplay.o : FlProductsListDisplay.H $(commonUIHeaders)
#FlLocalNavDisplay.o    : FlLocalNavDisplay.H $(commonUIHeaders)
FlCreateProductDisplay.o    : FlCreateProductDisplay.H $(commonUIHeaders)
FlListDisplay.o: FlListDisplay.H $(commonUIHeaders)
FlCreateContactDisplay.o: FlCreateContactDisplay.H $(commonUIHeaders)
FlNotificationDisplay.o: FlNotificationDisplay.H $(commonUIHeaders)
FlOffPremiseSaleUserIO.o: FlOffPremiseSaleUserIO.H $(commonUIHeaders)
FlCashFlowDisplay.o: FlCashFlowDisplay.H $(commonUIHeaders)
FlStockTransactionDisplay.o: FlStockTransactionDisplay.H $(commonUIHeaders)
w_transaction.o: transaction.H

dataset.o      : gmdataset.h
dataset_view.o : dataset_view.h
table_data.o   : gmdataset.h
color.o        : gmdataset.h
time.o         :gmtime.h
WinnyUserPrompts.o  : WinnyUserPrompts.H

clean :
	rm *o

#appending text to variables  use +=