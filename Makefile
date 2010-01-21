all: QuestionWindow

run: QuestionWindow
	./QuestionWindow

QuestionWindow: QuestionWindow.cpp
	g++ QuestionWindow.cpp -Wall -o QuestionWindow `fltk2-config --libs --ldflags --cxxflags --use-images` -lsqlite3
	mv QuestionWindow build/QuestionWindow


# configure below the path to fltk2-config of cross-buildable FLTK 2 lib

QuestionWindow.exe: QuestionWindow.cpp
	i586-mingw32msvc-g++ QuestionWindow.cpp -o QuestionWindow.exe \
	`/home/src/fltk-2.0.x-r6970/cross_win32/bin/fltk2-config --cxxflags` \
	`/home/src/fltk-2.0.x-r6970/cross_win32/bin/fltk2-config --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/krizz/src/sqlite-3.6.22/cross_win32/include -L/home/krizz/src/sqlite-3.6.22/cross_win32/lib/ /home/krizz/src/sqlite-3.6.22/cross_win32/lib/libsqlite3.a

wrun: QuestionWindow.exe
	wine ./QuestionWindow.exe

clean:
	rm -f *.o
	rm -f QuestionWindow
	rm -f *.exe

