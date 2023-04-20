#include <gtest/gtest.h>
#include "Life.hpp"
#include "ConwayCell.hpp"
#include "FredkinCell.hpp"
#include "Cell.hpp"
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;

// ************** Conway Tests **************

// constructor and write
TEST(ConwayFixture, ConwayTest0) {
    ConwayCell c;
    stringstream ss;
    ss << c;
    ASSERT_EQ(".", ss.str());
}

TEST(ConwayFixture, ConwayTest1) {
    ConwayCell c(false);
    stringstream ss;
    ss << c;
    ASSERT_EQ(".", ss.str());
}

TEST(ConwayFixture, ConwayTest2) {
    ConwayCell c(true);
    stringstream ss;
    ss << c;
    ASSERT_EQ("*", ss.str());
}

// update, starting with dead
TEST(ConwayFixture, ConwayTest3) {
    ConwayCell c;
    stringstream ss;
    c.update(1, 1);
    ss << c;
    ASSERT_EQ(".", ss.str());
}

TEST(ConwayFixture, ConwayTest4) {
    ConwayCell c;
    stringstream ss;
    c.update(1, 3);
    ss << c;
    ASSERT_EQ(".", ss.str());
}

TEST(ConwayFixture, ConwayTest5) {
    ConwayCell c;
    stringstream ss;
    c.update(1, 2);
    ss << c;
    ASSERT_EQ("*", ss.str());
}

// update, starting with alive
TEST(ConwayFixture, ConwayTest6) {
    ConwayCell c(true);
    stringstream ss;
    c.update(1, 2);
    ss << c;
    ASSERT_EQ("*", ss.str());
}

TEST(ConwayFixture, ConwayTest7) {
    ConwayCell c(true);
    stringstream ss;
    c.update(1, 1);
    ss << c;
    ASSERT_EQ("*", ss.str());
}

TEST(ConwayFixture, ConwayTest8) {
    ConwayCell c(true);
    stringstream ss;
    c.update(0, 1);
    ss << c;
    ASSERT_EQ(".", ss.str());
}

TEST(ConwayFixture, ConwayTest9) {
    ConwayCell c(true);
    stringstream ss;
    c.update(1, 3);
    ss << c;
    ASSERT_EQ(".", ss.str());
}

// clone
TEST(ConwayFixture, ConwayTest10) {
    ConwayCell c(true);
    stringstream ss;
    ConwayCell* c_ptr = &c;
    ConwayCell* clone_ptr = c.clone();
    ASSERT_NE(c_ptr, clone_ptr);
    ss << (*clone_ptr);
    ASSERT_EQ(ss.str(), "*");
    delete clone_ptr;
}

// ************** Fredkin Tests **************
TEST(FredkinFixture, FredkinDefaultConstructor0) {
    FredkinCell f;
    stringstream ss;
    ss << f;
    ASSERT_EQ("-", ss.str());
};

TEST(FredkinFixture, FredkinBoolConstructor0) {
    stringstream ss;

    FredkinCell f1(false);
    ss << f1;
    ASSERT_EQ("-", ss.str());
    ss.clear();
    ss.str("");

    FredkinCell f2(true);
    ss << f2;
    ASSERT_EQ("0", ss.str());
};

TEST(FredkinFixture, FredkinUpdate0) {
    stringstream ss;
    FredkinCell f(false);
    ASSERT_EQ(f.update(0, 3), 0);
    ss << f;
    ASSERT_EQ("-", ss.str());
}

TEST(FredkinFixture, FredkinUpdate1) {
    stringstream ss;
    FredkinCell f(false);
    ASSERT_EQ(f.update(1, 3), 1);
    ss << f;
    ASSERT_EQ("0", ss.str());
    ss.clear();
    ss.str("");

    ASSERT_EQ(f.update(1, 3), 0);
    ss << f;
    ASSERT_EQ("1", ss.str());
    ss.clear();
    ss.str("");

    ASSERT_EQ(f.update(1, 3), 2);
    ss << f;
    ASSERT_EQ("2", ss.str());
    ss.clear();
    ss.str("");

    for (int i = 0; i < 10; i++) {
        ASSERT_EQ(f.update(1, 3), 0);
    }
    ss << f;
    ASSERT_EQ("+", ss.str());
    ss.clear();
    ss.str("");

    ASSERT_EQ(f.update(0, 1), -1);
    ss << f;
    ASSERT_EQ("-", ss.str());
}

TEST(FredkinFixture, FredkinClone0) {
    stringstream ss;
    FredkinCell f1(false);
    f1.update(1, 3);
    f1.update(1, 3);
    f1.update(1, 3);
    ss << f1;
    ASSERT_EQ("2", ss.str());
    ss.clear();
    ss.str("");

    FredkinCell f2(false);
    FredkinCell *ptr = f1.clone();
    f2 = *ptr;
    ss << f2;
    ASSERT_EQ("2", ss.str());
    delete ptr;
}

// ************** Cell Tests **************
TEST(CellFixture, CellDefaultConstructor0) {
    stringstream ss;
    Cell c;
    ss << c;
    ASSERT_EQ("-", ss.str());
}

TEST(CellFixture, CellBoolConstructor0) {
    stringstream ss;
    Cell c(true);
    ss << c;
    ASSERT_EQ("0", ss.str());
}

TEST(CellFixture, CellCopyConstructor0) {
    stringstream ss;
    Cell c1(true);

    Cell c2(c1);
    ss << c2;
    ASSERT_EQ("0", ss.str());
}

TEST(CellFixture, CellCopyAssignment0) {
    stringstream ss;
    Cell c1(true);

    Cell c2;
    ss << c2;
    ASSERT_EQ("-", ss.str());
    ss.clear();
    ss.str("");
    c2 = c1;
    ss << c2;
    ASSERT_EQ("0", ss.str());
}

TEST(CellFixture, CellUpdate0) {
    stringstream ss;
    Cell c;
    ASSERT_EQ(c.update(1,3), 1);
    ss << c;
    ASSERT_EQ("0", ss.str());
    ss.clear();
    ss.str("");
    ASSERT_EQ(c.update(1,3), 0);
    ss << c;
    ASSERT_EQ("1", ss.str());
    ss.clear();
    ss.str("");
    ASSERT_EQ(c.update(1,3), 0);
    ss << c;
    ASSERT_EQ("*", ss.str());
    ss.clear();
    ss.str("");
    ASSERT_EQ(c.update(1,3), -1);
    ss << c;
    ASSERT_EQ(".", ss.str());
}

TEST(CellFixture, CellClone0) {
    stringstream ss;
    Cell c1;
    c1.update(1,3);
    c1.update(1,3);
    c1.update(1,3);
    c1.update(1,3);
    ss << c1;
    ASSERT_EQ(".", ss.str());
    ss.clear();
    ss.str("");
    Cell c2;
    c2.clone(c1);
    ss << c2;
    ASSERT_EQ(".", ss.str());
}

// ************** Life Tests **************
TEST(LifeFixture, LifeTest0) {
    stringstream redirect_stream;
    streambuf* old_buf = cout.rdbuf(redirect_stream.rdbuf());
    vector<pair<int, int>> live_cells;
    live_cells.push_back(pair<int, int>(0, 1));
    live_cells.push_back(pair<int, int>(0, 1));
    Life<ConwayCell> life(
        2,
        2,
        live_cells
    );
    life.print(0);
    string exp_str = "Generation = 0, Population = 1."
                     "\n.*\n..\n";

    ASSERT_EQ(exp_str, redirect_stream.str());

    redirect_stream.clear();
    redirect_stream.str("");
    life.do_round();
    life.print(1);
    exp_str = "Generation = 1, Population = 0."
              "\n..\n..\n";

    ASSERT_EQ(exp_str, redirect_stream.str());
    cout.rdbuf(old_buf);
}
