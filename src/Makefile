CC=gcc
AFLAGS= -std=c++17 -lm -Wall -Werror -Wextra -lstdc++ -fsanitize=address -lmuparser
BFLAGS = -lgtest
GCOV = -fprofile-arcs -ftest-coverage -lgcov
SRCS = $(wildcard *.cpp)
CALCNAME = -o SmartCalculation
DIRCALC = develop/view/*.cpp develop/controller/controller.cpp develop/model/*.cpp
GTK = `pkg-config --cflags gtk+-3.0`
PREFIX = ../build
TARGET = SmartCalc_v2.0
GCOVFLAGS = -fprofile-arcs -ftest-coverage --coverage


all: clean
	mkdir -p ../build
	$(CC) $(GTK) $(AFLAGS) -Wno-unused-parameter `pkg-config --cflags gtk+-3.0` $(CALCNAME) $(DIRCALC) `pkg-config --libs gtk+-3.0` -o $(PREFIX)/SmartCalculation
	./$(PREFIX)/SmartCalculation
	rm $(PREFIX)/SmartCalculation

install: uninstall
	mkdir -p ../build
	$(CC) $(GTK) $(AFLAGS) -Wno-unused-parameter `pkg-config --cflags gtk+-3.0` $(CALCNAME) $(DIRCALC) `pkg-config --libs gtk+-3.0` -o $(PREFIX)/SmartCalc_v2.0.app

uninstall:
	rm -rf $(PREFIX)

dvi:
	mkdir -p doxygen
	@doxygen Doxyfile
	open doxygen/html/index.html || xdg-open doxygen/html/index.html || sensible-browser doxygen/html/index.html || x-www-browser doxygen/html/index.html || gnome-open doxygen/html/index.html

dist: install
	mkdir -p ../dist
	cp -R $(PREFIX)/$(TARGET).app ../dist
	cp -R . ../dist/src
	cd ../dist && tar cvzf $(TARGET).tgz *
	cd ../dist && rm -rf $(TARGET).app
	rm -rf ../dist/src
	echo "Archive creation completed successfully!"


tests:
	$(CC) $(GTK) $(AFLAGS) $(BFLAGS) $(GCOVFLAGS) develop/tests/tests.cpp develop/model/*.cpp -o tests
	./tests
	rm tests


rep_list:
	lcov -t "tests" -o tests.info -c -d . --rc geninfo_unexecuted_blocks=1 \
		--ignore-errors 'mismatch,unused' \
		--exclude c++/13/ \
		--exclude gtest/ \
		--exclude /usr/include \
		--exclude '*tests*.cpp'
	genhtml -o report tests.info
	open report/index.html || xdg-open report/index.html || sensible-browser report/index.html || x-www-browser report/index.html || gnome-open report/index.html

gcov_report: clean tests rep_list
	lcov -t "s21_smartcalc" -o s21_smartcalc.info -c -d .
	genhtml -o report s21_smartcalc.info
	open report/index.html || xdg-open report/index.html || sensible-browser report/index.html || x-www-browser report/index.html || gnome-open report/index.html



clean:
	rm -rf coverage_report *.o *.a s21_matrix_oop *.gcda *.gcno *.info ./out tests
	rm -rf report tests.dSYM SmartCalculation t html latex doxygen
	rm -rf ../build ../dist

c:
	cp ../materials/linters/.clang-format ../src/
	clang-format -i develop/view/*.cpp develop/tests/*cpp develop/view/*.h develop/model/*.cpp develop/model/*.h develop/controller/*.cpp develop/controller/*.h develop/tests/*.cpp
	rm .clang-format
cl:
	sed -i 's|//.*||' develop/view/*.cpp
	sed -i 's|//.*||' develop/model/*.cpp
	sed -i 's|//.*||' develop/controller/*.cpp
	sed -i 's|//.*||' develop/tests/*cpp

