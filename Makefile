FLTK2CONFIG=fltk2-config

# flags for compiler:
CFLAGS   = -Wall -O3 -I. $(shell $(FLTK2CONFIG) --cflags) -DFLTK2
CXXFLAGS = -Wall -O3 -I. $(shell $(FLTK2CONFIG) --cxxflags) -DFLTK2

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

.SILENT: # Make the build run quietly

#########################################################
# make sure the basic rules are in place, just in case...
# Build commands and filename extensions...
.SUFFIXES: .c .cxx .cpp .cc .h .fl .o

# Rule to build an object file from a C++ source file
%.o : %.cxx 
	@echo Compile $@...
	$(CXX) -c -o $@ $< $(CXXFLAGS)

# Rule to build an object file from a C++ source file
%.o : %.cpp
	@echo Compile $@...
	$(CXX) -c -o $@ $< $(CXXFLAGS)

#########################################################

all: QuestionWindow QuestionViewMain

run: QuestionWindow
	bash -c "cd build;./QuestionWindow"&

ui: QuestionViewUI.cxx

QuestionViewUI.cxx: 
	@echo Generate UI...
	fluid2 -c ui/QuestionViewUI.fl
	mv ui/QuestionViewUI.h ./
	mv ui/QuestionViewUI.cxx ./
	@echo Patch UI classes...
	patch -p1 -i ui/fluid_test_missinclude.patch QuestionViewUI.h

QuestionViewMain: answer.o question.o test.o  QuestionViewUI.o QuestionViewMain.o
	@echo Build $@...
	$(CXX) answer.o question.o test.o  QuestionViewUI.o QuestionViewMain.o -Wall \
	$(IMGLIB) $(LDLIBS) -o build/QuestionViewMain	
	@echo Strip $@...
	$(STRIP) build/$@
	$(POSTBUILD) build/QuestionViewMain

QuestionWindow: Question.o sqliteExerBase.o QuestionWindow.o 
	@echo Build $@...
	$(CXX) QuestionWindow.o -Wall -o build/QuestionWindow \
	$(IMGLIB) $(LDLIBS) -lsqlite3
	@echo Strip $@...
	#$(STRIP) build/$@
	#$(POSTBUILD) build/QuestionViewMain


debug: QuestionWindow.cpp
	g++ QuestionWindow.cpp -Wall -W -g3 -o build/QuestionWindow `fltk2-config --libs --ldflags --cxxflags --use-images` -lsqlite3

# configure below the path to fltk2-config of cross-buildable FLTK 2 lib
allwin: QuestionWindow.exe QuestionViewMain.exe

wrun: QuestionWindow.exe
	bash -c "cd build;wine ./QuestionWindow.exe"&

QuestionWindow.exe: QuestionWindow.cpp
	i586-mingw32msvc-g++ QuestionWindow.cpp -o build/QuestionWindow.exe \
	`/home/src/fltk-2.0.x-r6970/cross_win32/bin/fltk2-config --cxxflags` \
	`/home/src/fltk-2.0.x-r6970/cross_win32/bin/fltk2-config --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/krizz/src/sqlite-3.6.22/cross_win32/include -L/home/krizz/src/sqlite-3.6.22/cross_win32/lib/ /home/krizz/src/sqlite-3.6.22/cross_win32/lib/libsqlite3.a

QuestionViewMain.exe: QuestionViewUI.h QuestionViewUI.cxx
	i586-mingw32msvc-g++ QuestionViewMain.cxx QuestionViewUI.cxx test.cxx question.cxx answer.cxx \
	-o build/QuestionViewMain.exe \
	`/home/src/fltk-2.0.x-r6970/cross_win32/bin/fltk2-config --cxxflags` \
	`/home/src/fltk-2.0.x-r6970/cross_win32/bin/fltk2-config --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/krizz/src/sqlite-3.6.22/cross_win32/include -L/home/krizz/src/sqlite-3.6.22/cross_win32/lib/ /home/krizz/src/sqlite-3.6.22/cross_win32/lib/libsqlite3.a

clean:
	rm -f *.o
	rm -f build/QuestionWindow build/QuestionViewMain
	rm -f build/QuestionWindow.exe build/QuestionViewMain.exe

deepclean: clean
	rm -f QuestionViewUI.cxx QuestionViewUI.h

