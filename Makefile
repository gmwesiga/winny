objects ::= winny.o FlScreen.o IExtEventSource.o FlSessionInfoDisplay.o \
            winny_theme.o FlNavDisplay.o FlProductsListDisplay.o FlLocalNavDisplay.o \
			FlCreateProductDisplay.o FlContactsListDisplay.o\
			dataset.o dataset_view.o table_data.o color.o FlCreateContactDisplay.o \
			Application.o FlNotificationDisplay.o FlOffPremiseSaleUserIO.o
commonUIHeaders = FWidgetSizes.H winny_theme.h

FLDLIBS ::= -lfltk_images -lfltk_png -lfltk_z -lfltk -lpthread -ldl -lm -lX11
FLDFLAGS ::= -L/usr/local/lib
FLCXXFLAGS ::= -I. -I/usr/local/include -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE \
              -D_THREAD_SAFE -D_REENTRANT #FLCXXFLAGS = FLTK CXX FLAGS

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
FlSessionInfoDisplay.o : FlSessionInfoDisplay.h $(commonUIHeaders)
FlNavDisplay.o         : FlNavDisplay.h $(commonUIHeaders)
FlProductsListDisplay.o : FlProductsListDisplay.H $(commonUIHeaders)
FlLocalNavDisplay.o    : FlLocalNavDisplay.H $(commonUIHeaders)
FlCreateProductDisplay.o    : FlCreateProductDisplay.H $(commonUIHeaders)
FlContactsListDisplay.o: FlContactsListDisplay.H $(commonUIHeaders)
FlCreateContactDisplay.o: FlCreateContactDisplay.H $(commonUIHeaders)
FlNotificationDisplay.o: FlNotificationDisplay.H $(commonUIHeaders)
FlOffPremiseSaleUserIO.o: FlOffPremiseSaleUserIO.H $(commonUIHeaders)

dataset.o      : gmdataset.h
dataset_view.o : dataset_view.h
table_data.o   : gmdataset.h
color.o        : gmdataset.h

clean :
	rm *o

#appending text to variables  use +=