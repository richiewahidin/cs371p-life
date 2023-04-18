.DEFAULT_GOAL := all

ASTYLE        := astyle
CHECKTESTDATA := checktestdata
CPPCHECK      := cppcheck
DOXYGEN       := doxygen
SHELL         := bash
VALGRIND      := valgrind

ifeq ($(shell uname -s), Life)
    BOOST    := /usr/local/include/boost
    CXX      := clang++
    CXXFLAGS := --coverage -g -std=c++20 -I$(INCLUDE_PATH) -Wall -Wextra -Wpedantic
    GCOV     := llvm-cov gcov
    GTEST    := /usr/local/include/gtest
    LDFLAGS  := -lgtest -lgtest_main
    LIB      := $(LIBRARY_PATH)
    VALGRIND :=
else ifeq ($(shell uname -p), unknown)
    BOOST    := /usr/include/boost
    CXX      := g++
    CXXFLAGS := --coverage -g -std=c++20 -Wall -Wextra -Wpedantic
    GCOV     := gcov
    GTEST    := /usr/include/gtest
    LDFLAGS  := -lgtest -lgtest_main -pthread
    LIB      := /usr/lib
    VALGRIND := valgrind
else ifeq ($(shell uname -p), Linux)
    BOOST    := /usr/include/boost
    CXX      := g++
    CXXFLAGS := --coverage -g -std=c++20 -Wall -Wextra -Wpedantic
    GCOV     := gcov
    GTEST    := /usr/include/gtest
    LDFLAGS  := -lgtest -lgtest_main -pthread
    LIB      := /usr/lib/x86_64-linux-gnu
    VALGRIND := valgrind
else
    BOOST    := /usr/local/opt/boost-1.67/include/boost
    CXX      := g++-11
    CXXFLAGS := --coverage -g -std=c++20 -Wall -Wextra -Wpedantic
    GCOV     := gcov-11
    GTEST    := /usr/local/include/gtest
    LDFLAGS  := -L/usr/local/opt/boost-1.77/lib/ -lgtest -lgtest_main -pthread
    LIB      := /usr/local/lib
    VALGRIND := valgrind
endif

# run docker
docker:
	docker run --rm -it -v $(PWD):/usr/gcc -w /usr/gcc gpdowning/gcc

# get git config
config:
	git config -l

# get git log
Life.log.txt:
	git log > Life.log.txt

# get git status
status:
	make clean
	@echo
	git branch
	git remote -v
	git status

# download files from the Life code repo
pull:
	make clean
	@echo
	git pull
	git status

# upload files to the Life code repo
push:
	make clean
	@echo
	git add .gitignore
	git add .gitlab-ci.yml
	git add Life.hpp
	-git add Life.log.txt
	-git add html
	git add Makefile
	git add README.md
	git add Runlife.hpp
	-git add RunLife.ctd.txt
	git add Testlife.cpp
	git commit -m "another commit"
	git push
	git status

CLASS_FILES := \
	AbstractCell.cpp \
	ConwayCell.cpp \
	FredkinCell.cpp \
	Cell.cpp \
	Life.hpp

# compile run harness for Conway
RunLifeConway: AbstractCell.cpp ConwayCell.cpp Cell.cpp Life.hpp RunLifeConway.cpp
	-$(CPPCHECK) RunLifeConway.cpp
	$(CXX) $(CXXFLAGS) $(CLASS_FILES) RunLifeConway.cpp -o RunLifeConway

# compile run harness for Fredkin
RunLifeFredkin: AbstractCell.cpp FredkinCell.cpp Cell.cpp Life.hpp RunLifeFredkin.cpp
	-$(CPPCHECK) RunLifeFredkin.cpp
	$(CXX) $(CXXFLAGS) $(CLASS_FILES) RunLifeFredkin.cpp -o RunLifeFredkin

# compile run harness for Cell
RunLifeCell: AbstractCell.cpp Cell.cpp Life.hpp RunLifeCell.cpp
	-$(CPPCHECK) RunLifeCell.cpp
	$(CXX) $(CXXFLAGS) $(CLASS_FILES) RunLifeCell.cpp -o RunLifeCell

# compile test harness
TestLife: 	AbstractCell.cpp ConwayCell.cpp FredkinCell.cpp Cell.cpp Life.hpp TestLife.cpp
	-$(CPPCHECK) TestLife.cpp
	$(CXX) $(CXXFLAGS) $(CLASS_FILES) TestLife.cpp -o TestLife $(LDFLAGS)

# run/test files, compile with make all
FILES :=          \
    RunLifeConway \
	RunLifeFredkin \
	RunLifeCell \
    TestLife

# compile all
all: $(FILES)

# execute test harness with coverage
test: TestLife
	$(VALGRIND) ./TestLife
ifeq ($(shell uname -s), Life)
	$(GCOV) TestLife.cpp | grep -B 2 "hpp.gcov"
else
	gcc -c --coverage Life.hpp
	$(GCOV) -b TestLife-TestLife.cpp | grep -B 4 "cpp.gcov"
endif

# clone the Life test repo
../cs371p-life-tests:
	git clone https://gitlab.com/gpdowning/cs371p-life-tests.git ../cs371p-Life-tests

# test files in the Life test repo
T_FILES := `ls ../cs371p-Life-tests/*.in.txt`

# generate a random input file
ctd-generate:
	$(CHECKTESTDATA) -g RunLife.ctd.txt >> richiewahidin-RunLife.in.txt

# execute the run harness against a test file in the Life test repo and diff
# with the expected output for Conway
../cs371p-life-tests/%Conway: RunLifeConway
	$(CHECKTESTDATA) RunLife.ctd.txt $@.in.txt
	./RunLifeConway < $@.in.txt > RunLifeConway.tmp.txt
	diff RunLifeConway.tmp.txt $@.out.txt

# execute the run harness against a test file in the Life test repo and diff
# with the expected output for Fredkin
../cs371p-life-tests/%Fredkin: RunLifeFredkin
	$(CHECKTESTDATA) RunLife.ctd.txt $@.in.txt
	./RunLifeFredkin < $@.in.txt > RunLifeFredkin.tmp.txt
	diff RunLifeFredkin.tmp.txt $@.out.txt

# execute the run harness against a test file in the Life test repo and diff
# with the expected output for Cell
../cs371p-life-tests/%Cell: RunLifeCell
	$(CHECKTESTDATA) RunLife.ctd.txt $@.in.txt
	./RunLifeCell < $@.in.txt > RunLifeCell.tmp.txt
	diff RunLifeCell.tmp.txt $@.out.txt

# execute the run harness against your test files in the Life test repo and diff with the expected output
run: ../cs371p-life-tests
	-make run-conway
	-make run-fredkin
	-make run-cell

run-conway: ../cs371p-life-tests
	-make ../cs371p-life-tests/gpdowning-RunLifeConway # change gpdowning to your GitLab-ID

run-fredkin: ../cs371p-life-tests
	-make ../cs371p-life-tests/gpdowning-RunLifeFredkin # change gpdowning to your GitLab-ID

run-cell: ../cs371p-life-tests
	-make ../cs371p-life-tests/gpdowning-RunLifeCell # change gpdowning to your GitLab-ID

# execute the run harness against all of the test files in the Life test repo and diff with the expected output
run-all: ../cs371p-life-tests
	-for v in $(T_FILES); do make $${v/.in.txt/}; done

# auto format the code
format:
	$(ASTYLE) AbstractCell.cpp
	$(ASTYLE) AbstractCell.hpp
	$(ASTYLE) Cell.cpp
	$(ASTYLE) Cell.hpp
	$(ASTYLE) ConwayCell.cpp
	$(ASTYLE) ConwayCell.hpp
	$(ASTYLE) FredkinCell.cpp
	$(ASTYLE) FredkinCell.hpp
	$(ASTYLE) Life.hpp
	$(ASTYLE) RunLifeCell.cpp
	$(ASTYLE) RunLifeConway.cpp
	$(ASTYLE) RunLifeFredkin.cpp
	$(ASTYLE) TestLife.cpp

# you must edit Doxyfile and
# set EXTRACT_ALL     to YES
# set EXTRACT_PRIVATE to YES
# set EXTRACT_STATIC  to YES
# create Doxfile
Doxyfile:
	$(DOXYGEN) -g

# create html directory
html: Doxyfile
	$(DOXYGEN) Doxyfile

# check files, check their existence with make check
C_FILES :=            \
    .gitignore        \
    .gitlab-ci.yml    \
    Life.log.txt \
    html

# check the existence of check files
check: $(C_FILES)

# remove executables and temporary files
clean:
	rm -f  *.gcda
	rm -f  *.gcno
	rm -f  *.gcov
	rm -f  *.hpp.gch
	rm -f  *.gen.txt
	rm -f  *.tmp.txt
	rm -f  RunLifeCell
	rm -f  RunLifeConway
	rm -f  RunLifeFredkin
	rm -f  TestLife
	rm -rf *.dSYM

# remove executables, temporary files, and generated files
scrub:
	make clean
	rm -f  Life.log.txt
	rm -f  Doxyfile
	rm -rf html
	rm -rf latex

# output versions of all tools
versions:
	uname -p

	@echo
	uname -s

	@echo
	which $(ASTYLE)
	@echo
	$(ASTYLE) --version

	@echo
	which $(CHECKTESTDATA)
	@echo
	$(CHECKTESTDATA) --version | head -n 1

	@echo
	which $(CPPCHECK)
	@echo
	$(CPPCHECK) --version

	@echo
	which $(DOXYGEN)
	@echo
	$(DOXYGEN) --version

	@echo
	which $(CXX)
	@echo
	$(CXX) --version | head -n 1

	@echo
	which $(GCOV)
	@echo
	$(GCOV) --version | head -n 1

	@echo
	which git
	@echo
	git --version

	@echo
	which make
	@echo
	make --version | head -n 1

ifneq ($(VALGRIND),)
	@echo
	which $(VALGRIND)
	@echo
	$(VALGRIND) --version
endif

	@echo
	which vim
	@echo
	vim --version | head -n 1

	@echo
	grep "#define BOOST_LIB_VERSION " $(BOOST)/version.hpp

	@echo
	ls -al $(GTEST)/gtest.h
	@echo
	pkg-config --modversion gtest
	@echo
	ls -al $(LIB)/libgtest*.a
