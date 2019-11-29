objects = winny.o FlScreen.o IExtEventSource.o \
            winny_theme.o \
			FlCreateProductDisplay.o FlListDisplay.o\
			dataset.o dataset_view.o table_data.o color.o FlCreateContactDisplay.o \
			FlNotificationDisplay.o FlOffPremiseSaleUserIO.o \
			FlCashFlowDisplay.o WinnyUserPrompts.o time.o FlStockTransactionDisplay.o \
			w_transaction.o CommBus.o ServiceManager.o testingService.o
commonUIHeaders = FWidgetSizes.H winny_theme.h WinnyUserPrompts.H IApplicationTypes.H

FLDLIBS = -mwindows -lfltk_images -lfltk_png -lfltk_z -lfltk -lole32 -luuid -lcomctl32
#FLDLIBS = -mwindows -lfltk_images  -lfltk -lole32 -luuid -lcomctl32 #cygwin windows version
FLDLIBS = -lfltk_images -lfltk_png -lfltk_z -lfltk -lpthread -ldl -lm -lX11 
#FLDLIBS = -lfltk_images -lfltk -lpthread -ldl -lm -lX11 #cygwin version

FLDFLAGS = -L/usr/local/lib -static-libgcc -static-libstdc++ #-static-libgcc and -static-libstdc++ are to 
														#solve no libstdc found error.
#CXX = x86_64-w64-mingw32-g++ #cross compiler while on linux
CXX = g++

FLCXXFLAGS = -g -I. -I/usr/local/include -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE \
              -D_THREAD_SAFE -D_REENTRANT -std=c++11 -std=gnu++11 #FLCXXFLAGS = FLTK CXX FLAGS
#remember to remove -g option in production
CXXFLAGS += $(FLCXXFLAGS)
LDLIBS += $(FLDLIBS)
LDFLAGS += $(FLDFLAGS)

winny : $(objects)
	$(CXX) -owinny $(objects) $(LDFLAGS) $(LDLIBS)
#	rm *o g++-mingw-w64 

winny.o           : IScreen.h  IExtEventSource.h FlScreen.h
winny_theme.o     : winny_theme.cc winny_theme.h
#Application.o     : Application.H
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
DatabaseServer.o : DatabaseServer.h
Globals_DatabaseServer.o :IDatabaseServer.h
CommBus.o : CommBus.H ServiceTypes.H
ServiceManager.o : ServiceManager.H ServiceTypes.H
testingService.o :ServiceManager.H ServiceTypes.H

dataset.o      : gmdataset.h
dataset_view.o : dataset_view.h
table_data.o   : gmdataset.h
color.o        : gmdataset.h
time.o         :gmtime.h
WinnyUserPrompts.o  : WinnyUserPrompts.H

clean :
	rm *o

#appending text to variables  use +=