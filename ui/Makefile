all: QuestionViewMain

QuestionViewUI.cxx: QuestionViewUI.fl
	fluid2 -c QuestionViewUI.fl

QuestionViewUI.h: QuestionViewUI.cxx
	patch -p1 -i fluid_test_missinclude.patch QuestionViewUI.h

QuestionViewMain: QuestionViewUI.h QuestionViewUI.cxx
	cp ../test.h ../test.cxx ./
	cp ../question.cxx ../question.h ./
	cp ../answer.cxx ../answer.h ./
	g++ QuestionViewMain.cxx QuestionViewUI.cxx test.cxx question.cxx answer.cxx -Wall \
	`fltk2-config --libs --ldflags --cxxflags --use-images` -o QuestionViewMain

QuestionViewMain.exe: QuestionViewUI.h QuestionViewUI.cxx
	cp ../test.h ../test.cxx ./
	cp ../question.cxx ../question.h ./
	cp ../answer.cxx ../answer.h ./
	i586-mingw32msvc-g++ QuestionViewMain.cxx QuestionViewUI.cxx test.cxx question.cxx answer.cxx \
	-o QuestionWindow.exe \
	`/home/src/fltk-2.0.x-r6970/cross_win32/bin/fltk2-config --cxxflags` \
	`/home/src/fltk-2.0.x-r6970/cross_win32/bin/fltk2-config --libs --use-images --ldstaticflags` \
	-lgdi32 -lws2_32 -lole32 -luuid -lmsimg32 -mwindows -lgdi32  \
	-I/home/krizz/src/sqlite-3.6.22/cross_win32/include -L/home/krizz/src/sqlite-3.6.22/cross_win32/lib/ /home/krizz/src/sqlite-3.6.22/cross_win32/lib/libsqlite3.a

clean:
	rm -f QuestionViewUI.h QuestionViewUI.cxx
	rm -f test.* question.* answer.*
	rm -f ./QuestionViewMain

