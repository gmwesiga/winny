objects ::= winny.o FlScreen.o IExtEventSource.o FlSessionInfoDisplay.o \
            winny_theme.o FlNavDisplay.o FlProductsListDisplay.o FlLocalNavDisplay.o \
			FlCreateProductDisplay.o FlContactsListDisplay.o\
			dataset.o dataset_view.o table_data.o color.o FlCreateContactDisplay.o

FLDLIBS ::= -lfltk_images -lfltk_png -lfltk_z -lfltk -lpthread -ldl -lm -lX11
FLDFLAGS ::= -L/usr/local/lib
FLCXXFLAGS ::= -I. -I/usr/local/include -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE \
              -D_THREAD_SAFE -D_REENTRANT #FLCXXFLAGS = FLTK CXX FLAGS

CXXFLAGS += $(FLCXXFLAGS)
LDLIBS += $(FLDLIBS)
LDFLAGS += $(FLDFLAGS)

winny : $(objects)
	g++ -owinny $(objects) $(LDFLAGS) $(LDLIBS)

winny.o           : IScreen.h  IExtEventSource.h FlScreen.h
winny_theme.o     : winny_theme.cc winny_theme.h

IExtEventSource.o : IExtEventSource.h IApplication.h
FlScreen.o        : FlScreen.h IExtEventSource.h IScreen.h FWidgetSizes.H
FlSessionInfoDisplay.o : FlSessionInfoDisplay.h
FlNavDisplay.o         : FlNavDisplay.h
FlProductsListDisplay.o : FlProductsListDisplay.H
FlLocalNavDisplay.o    : FlLocalNavDisplay.H
FlCreateProductDisplay.o    : FlCreateProductDisplay.H
FlContactsListDisplay.o: FlContactsListDisplay.H
FlCreateContactDisplay.o: FlCreateContactDisplay.H

dataset.o      : gmdataset.h
dataset_view.o : dataset_view.h
table_data.o   : gmdataset.h
color.o        : gmdataset.h

#appending text to variables  use +=