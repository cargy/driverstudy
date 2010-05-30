FLTK2CONFIG=fltk2-config

# flags for compiler:
CFLAGS   = -Wall -O3 -I. $(shell $(FLTK2CONFIG) --cflags) -DFLTK2
CXXFLAGS = -g -Wall -O2 -I. $(shell $(FLTK2CONFIG) -g --cxxflags) -DFLTK2

# Possible steps after linking...
STRIP      = strip
POSTBUILD  = $(FLTK2CONFIG) --post

# libraries to link with:
LDLIBS   = -lm
LINKFLTK = $(shell $(FLTK2CONFIG) --ldstaticflags)
IMGLIB   = $(shell $(FLTK2CONFIG) --use-images --ldstaticflags)
GL_LIB   = $(shell $(FLTK2CONFIG) --use-gl --ldstaticflags)

# Other general settings
CXX     =  g++ #$(shell $(FLTK2CONFIG) --cxx)
CC      = $(shell $(FLTK2CONFIG) --cc)

# get version
MAJOR_VERSION	= $(shell grep "DRIVERSTUDY_MAJOR_VERSION.*[0-9]" version.h | cut -f3)
MINOR_VERSION	= $(shell grep "DRIVERSTUDY_MINOR_VERSION.*[0-9]" version.h | cut -f3)
MICRO_VERSION	= $(shell grep "DRIVERSTUDY_MICRO_VERSION.*[0-9]" version.h | cut -f3)
VERSION			= $(MAJOR_VERSION).$(MINOR_VERSION).$(MICRO_VERSION)

.SILENT: # Make the build run quietly

#########################################################
# make sure the basic rules are in place, just in case...
# Build commands and filename extensions...
.SUFFIXES: .cxx .h .fl .o

# Rule to build an object file from a C++ source file
%.o : %.cxx
	@echo Compile $@...
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	

#########################################################

all:  driverstudy

run: driverstudy
	bash -c "cd ../build;./QuestionWindow"&

ui: cleanui QuestionUIAbstract.cxx

QuestionUIAbstract.cxx MainMenuUIAbstract.cxx: 
	@echo === Generate UI... ===
	fluid2 -c ui/QuestionUIAbstract.fl
	fluid2 -c ui/MainMenuUIAbstract.fl
	mv ui/QuestionUIAbstract.h ./
	mv ui/QuestionUIAbstract.cxx ./
	mv ui/MainMenuUIAbstract.h ./
	mv ui/MainMenuUIAbstract.cxx ./
	# gettex fix for not being supported by Fluid2
	# strings with "_string" raplced by _("string")
	sed -i  's/"_\([^"]*\)"/_("\1") /g' QuestionUIAbstract.cxx
	sed -i  's/"_\([^"]*\)"/_("\1") /g' MainMenuUIAbstract.cxx
	
driverstudy: answer.o question.o test.o sqlite3.o \
			 DictationSystem.o TimerProgressBar.o dlg.o \
			 MainMenuUIAbstract.o MainMenuUI.o  \
			 QuestionUIAbstract.o QuestionUI.o driverstudy.o 
	@echo === Linking $@... ===
	$(CXX) answer.o question.o test.o \
	sqlite3.o DictationSystem.o TimerProgressBar.o dlg.o \
	QuestionUIAbstract.o QuestionUI.o MainMenuUIAbstract.o MainMenuUI.o  \
	driverstudy.o \
	$(IMGLIB) $(LDLIBS) -lsqlite3 -laudiere -o ../build/driverstudy	
	@echo version:$(VERSION)
	#@echo Strip $@...
	#$(STRIP) ../build/$@
	#$(POSTBUILD) ../build/QuestionViewMain

QuestionViewMain: answer.o question.o test.o sqlite3.o \
				  QuestionViewUI.o QuestionView.o QuestionViewMain.o 
	@echo === Linking $@... ===
	$(CXX) answer.o question.o test.o \
	sqlite3.o QuestionViewUI.o QuestionView.o QuestionViewMain.o \
	$(IMGLIB) $(LDLIBS) -lsqlite3 -o ../build/QuestionViewMain	
	#@echo Strip $@...
	#$(STRIP) build/$@
	#$(POSTBUILD) build/QuestionViewMain
	
MainMenu: MainMenuUIAbstract.o MainMenuUI.o MainMenu.o
	@echo === Linking $@... ===
	$(CXX) MainMenuUIAbstract.o MainMenuUI.o MainMenu.o \
	$(IMGLIB) $(LDLIBS) -lsqlite3 -o ../build/MainMenu	
	#@echo Strip $@...
	#$(STRIP) ../build/$@
	#$(POSTBUILD) ../build/MainMenu

QuestionWindow: Question.o sqliteExerBase.o QuestionWindow.o 
	@echo === Linking $@... ===
	$(CXX) QuestionWindow.o -Wall -o build/QuestionWindow \
	$(IMGLIB) $(LDLIBS) -lsqlite3
	#@echo Strip $@...
	#$(STRIP) ../build/$@
	#$(POSTBUILD) ../build/QuestionViewMain


debug: QuestionViewMain.cxx QuestionWindow.cpp
	g++ QuestionViewMain.cxx -Wall -W -g3 -o ../build/QuestionWindow `fltk2-config --libs --ldflags --cxxflags --use-images` -lsqlite3
	#g++ QuestionWindow.cpp -Wall -W -g3 -o ../build/QuestionWindow `fltk2-config --libs --ldflags --cxxflags --use-images` -lsqlite3

# configure below the path to fltk2-config of cross-buildable FLTK 2 lib
allwin: QuestionWindow.exe QuestionViewMain.exe

wrun: QuestionWindow.exe
	bash -c "cd ../build;wine ./QuestionWindow.exe"&
	
driver_res.o: driverstudy.rc
	@echo === Compiling $@... ===
	i586-mingw32msvc-windres -i driverstudy.rc -o driver_res.o
	
driverstudy.exe: driver_res.o MainMenuUIAbstract.cxx QuestionUIAbstract.cxx
	@echo === Compiling $@... ===
	i586-mingw32msvc-g++ -static -O2 -Wall driverstudy.cxx MainMenuUIAbstract.cxx MainMenuUI.cxx QuestionUI.cxx QuestionUIAbstract.cxx \
	DictationSystem.cxx dlg.cxx TimerProgressBar.cxx test.cxx question.cxx answer.cxx driver_res.o \
	-o ../build/DriverStudy.exe \
	-L/home/krizz/src/cross_win32/lib \
	-laudiere -ldsound -lole32 -lrpcrt4 -lspeex -lwinmm -lvorbisfile -lvorbis -logg -lpthread -lws2_32 \
	-I/home/krizz/src/cross_win32/include -DPTW32_STATIC_LIB=1 -D_WIN32_WINNT=0x0501 \
	`/home/krizz/src/cross_win32/bin/fltk2-config --cxxflags` \
	`/home/krizz/src/cross_win32/bin/fltk2-config --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/krizz/src/cross_win32/include -I./ \
	/home/krizz/src/cross_win32/lib/libintl.a  \
	/home/krizz/src/cross_win32/lib/libsqlite3.a 
	@echo version:$(VERSION)
	#@echo Strip $@...
	#$(STRIP) ../build/$@
	#$(POSTBUILD) ../build/DriverStudy.exe

QuestionWindow.exe: QuestionWindow.cpp
	i586-mingw32msvc-g++ QuestionWindow.cpp -o ../build/QuestionWindow.exe \
	`/home/krizz/src/cross_win32/bin/fltk2-config --cxxflags` \
	`/home/krizz/src/cross_win32/bin/fltk2-config --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/krizz/src/sqlite-3.6.22/cross_win32/include -L/home/krizz/src/sqlite-3.6.22/cross_win32/lib/ /home/krizz/src/sqlite-3.6.22/cross_win32/lib/libsqlite3.a

QuestionViewMain.exe: QuestionViewUI.cxx
	@echo === Compiling $@... ===
	i586-mingw32msvc-g++ QuestionViewMain.cxx QuestionView.cxx QuestionViewUI.cxx test.cxx question.cxx answer.cxx \
	-o ../build/QuestionViewMain.exe \
	`/home/krizz/src/cross_win32/bin/fltk2-config --cxxflags` \
	`/home/krizz/src/cross_win32/bin/fltk2-config --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/krizz/src/cross_win32/include -I./ \
	/home/krizz/src/cross_win32/lib/libintl.a  \
	/home/krizz/src/cross_win32/lib/libsqlite3.a
	#@echo Strip $@...
	#$(STRIP) ../build/$@
	#$(POSTBUILD) ../build/QuestionViewMain.exe
	
MainMenu.exe: MainMenuUIAbstract.cxx
	@echo === Compiling $@... ===
	i586-mingw32msvc-g++ MainMenuUIAbstract.cxx MainMenuUI.cxx MainMenu.cxx \
	-o ../build/MainMenu.exe \
	`/home/krizz/src/cross_win32/bin/fltk2-config --cxxflags` \
	`/home/krizz/src/cross_win32/bin/fltk2-config --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/krizz/src/cross_win32/include -I./ \
	/home/krizz/src/cross_win32/lib/libintl.a 
	#@echo Strip $@...
	#$(STRIP) ../build/$@
	#$(POSTBUILD) ../build/QuestionViewMain.exe

clean:
	rm -f *.o
	rm -f ../build/QuestionWindow ../build/QuestionViewMain ../build/MainMenu ../build/driverstudy
	rm -f ../build/QuestionWindow.exe ../build/QuestionViewMain.exe ../build/MainMenu.exe ../build/DriverStudy.exe

cleanui:
	rm -f QuestionUIAbstract.cxx QuestionUIAbstract.h
	rm -f MainMenuUIAbstract.cxx MainMenuUIAbstract.h
	
deepclean: clean cleanui


