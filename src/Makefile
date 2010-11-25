FLTK2CONFIG=/home/argy/usr/local/bin/fltk2-config
FLTK2CONFIGW32=/home/argy/usr/w32/bin/fltk2-config

# flags for compiler:
CFLAGS   = -Wall -O3 -I. $(shell $(FLTK2CONFIG) --cflags) -DFLTK2
CXXFLAGS = -g -Wall -O0 -I. $(shell $(FLTK2CONFIG) -g --cxxflags) -DFLTK2

# Possible steps after linking...
STRIP      = strip
POSTBUILD  = $(FLTK2CONFIG) --post
STRIPW32	= i586-mingw32msvc-strip -s

# libraries to link with:
LDLIBS   = -lm
LINKFLTK = $(shell $(FLTK2CONFIG) --ldstaticflags)
IMGLIB   = $(shell $(FLTK2CONFIG) --use-images --ldstaticflags)
GL_LIB   = $(shell $(FLTK2CONFIG) --use-gl --ldstaticflags)

# Other general settings
CXX     =  g++
CC      = $(shell $(FLTK2CONFIG) --cc)

EXEC = driverstudy

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

# list of source files
CXXSOURCES = \
	log.h MV.cxx Facade.cxx answer.cxx LanguageModel.cxx CategoryModel.cxx SectionModel.cxx TestPropertiesModel.cxx QuestionModel.cxx TestModel.cxx AppModel.cxx sqlite3.cxx \
	LanguageSelectView.cxx ToolbarView.cxx AppView.cxx ContainerView.cxx CategoryBtnView.cxx MainMenuView.cxx TestView.cxx QuestionView.cxx AnswersView.cxx TestResultsView.cxx \
	TimerProgressBar.cxx \
	mvmain.cxx

OBJDIR	   = Debug
CXXOBJECTS = $(CXXSOURCES:%.cxx=$(OBJDIR)/%.o)  # expands to list of object files


# Rule to build an object file from a C++ source file
$(OBJDIR)/%.o : %.cxx
	@echo Compile $@...
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	

#########################################################

all: $(EXEC)
	
$(EXEC): $(CXXOBJECTS)
	@echo === Linking $@... ===
	$(CXX) $(CXXOBJECTS) \
	$(IMGLIB) $(LDLIBS) -lsqlite3 -o ../build/$(EXEC)	
	@echo compiled version:$(VERSION)
	#@echo Strip $@...
	#$(STRIP) ../build/$@
	#$(POSTBUILD) ../build/QuestionViewMain
	
strip: $(EXEC)
	@echo Striping $(EXEC)...
	$(STRIP) ../build/$(EXEC)

# configure below the path to fltk2-config of cross-buildable FLTK 2 lib	
driver_res.o: driverstudy.rc
	@echo === Compiling $@... ===
	i586-mingw32msvc-windres -i driverstudy.rc -o driver_res.o
	
driverstudy.exe: driver_res.o 
	@echo === Compiling $@... ===
	i586-mingw32msvc-g++ -static -O2 -Wall $(CXXSOURCES) driver_res.o \
	-o ../build/DriverStudy.exe \
	-L/home/argy/usr/w32/lib -lws2_32 \
	-I/home/argy/usr/w32/include -DPTW32_STATIC_LIB=1 -D_WIN32_WINNT=0x0501 \
	`$(FLTK2CONFIGW32) --cxxflags` \
	`$(FLTK2CONFIGW32) --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/argy/usr/w32/include -I./ /home/argy/usr/w32/lib/libsqlite3.a 
	@echo build version:$(VERSION)
	#@echo Strip $@...
	#$(STRIP) ../build/$@
	#$(POSTBUILD) ../build/DriverStudy.exe
	
strip-w32: driverstudy.exe
	@echo Striping DriverStudy.exe...
	$(STRIP) ../build/DriverStudy.exe

clean:
	@echo Cleaning object and executable files...
	rm -f $(OBJDIR)/*.o
	rm -f ../build/driverstudy
	rm -f ../build/DriverStudy.exe
	
deepclean: clean

deploy-src: clean
	bzr export --root=driverstudy-$(VERSION)-src ../deploy/src/driverstudy-$(VERSION)-src.tar.bz2
	@echo exported: driverstudy-$(VERSION)-src.tar.bz2
	
deploy-w32: deepclean strip-w32
	@echo === Assembling $(VERSION) release... ===
	rm -rf ../deploy/win32/driverstudy-$(VERSION)
	cp -r ../build/ ../deploy/win32/driverstudy-$(VERSION)
	cp -r ../../sounds/speex-uwb/ ../deploy/win32/driverstudy-$(VERSION)/voice
	@echo === Archiving full release... ===
	rm -f ../deploy/win32/driverstudy-$(VERSION)-full.7z
	7z a -mx=9 -ms=on ../deploy/win32/driverstudy-$(VERSION)-full.7z ../deploy/win32/driverstudy-$(VERSION)/ | grep -v "Compressing"
	@echo === Archiving no-voice files release... ===
	rm -f ../deploy/win32/driverstudy-$(VERSION)-no-voice.7z
	7z a  -mx=9 -ms=on -x\!driverstudy-$(VERSION)/voice/ ../deploy/win32/driverstudy-$(VERSION)-no-voice.7z ../deploy/win32/driverstudy-$(VERSION)/ | grep -v "Compressing"
	@echo === Archiving no-voice files sfx release... ===
	rm -f ../deploy/win32/driverstudy-$(VERSION)-no-voice.exe
	7z a  -sfx7z.sfx -mx=9 -ms=on -x\!driverstudy-$(VERSION)/voice/ ../deploy/win32/driverstudy-$(VERSION)-no-voice.exe ../deploy/win32/driverstudy-$(VERSION)/ | grep -v "Compressing"
	@echo === Archiving voice files... ===
	rm -f ../deploy/win32/driverstudy-voice-files-spx.7z
	7z a -mx=9 -ms=on ../deploy/win32/driverstudy-voice-files-spx.7z ../deploy/win32/driverstudy-$(VERSION)/voice/ | grep -v "Compressing"
	@echo deployment of $(VERSION) release completed!

deploy: deploy-src deploy-w32

