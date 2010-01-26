all: QuestionWindow QuestionViewMain

run: QuestionWindow
	bash -c "cd build;./QuestionWindow"&

QuestionViewUI.cxx: 
	fluid2 -c ui/QuestionViewUI.fl
	mv ui/QuestionViewUI.h ./
	mv ui/QuestionViewUI.cxx ./

QuestionViewUI.h: QuestionViewUI.cxx
	patch -p1 -i ui/fluid_test_missinclude.patch QuestionViewUI.h

QuestionViewMain: QuestionViewUI.h QuestionViewUI.cxx
	g++ QuestionViewMain.cxx QuestionViewUI.cxx test.cxx question.cxx answer.cxx -Wall \
	`fltk2-config --libs --ldflags --cxxflags --use-images` -o build/QuestionViewMain

QuestionWindow: QuestionWindow.cpp
	g++ QuestionWindow.cpp -Wall -o build/QuestionWindow \
	`fltk2-config --libs --ldflags --cxxflags --use-images` -lsqlite3



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

