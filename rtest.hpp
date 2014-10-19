// Copyright (C) 2011 by Kristian Rumberg <kristianrumberg@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef RTEST_HPP
#define RTEST_HPP

#include <stdlib.h>

#include <iostream>
#include <sstream>
#include <vector>

namespace RTest {

/*************************
          View
*************************/

void dieWithError(const std::string& expect, int line);
void dispAssertEqFailed(const char* expr, const std::string& expect, const std::string& value, int line);
void dispAssertNeFailed(const char* expr, const std::string& expect, const std::string& value, int line);

/*************************
   Model and controller
*************************/

class ASingleTest;

typedef std::vector<ASingleTest*> SingleTestList;

SingleTestList& getTestList();

class ASingleTest {
public:
    ASingleTest() {
        getTestList().push_back(this);
    }

    virtual const char* name() const = 0;
    virtual void run() = 0;
};

template <typename A>
std::string toStr(const A& a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
}

template <typename A, typename B>
void assertEq(const char* expr, const A& expect, const B& value, int line)
{
    if (expect != value) {
        dispAssertEqFailed(expr, toStr(expect), toStr(value), line);
    }
}

template <typename A, typename B>
void assertNe(const char* expr, const A& expect, const B& value, int line)
{
    if (expect == value) {
        dispAssertNeFailed(expr, toStr(expect), toStr(value), line);
    }
}

inline void assertTrue(const char* expr, bool value, int line)
{
    if (!value) {
        dispAssertEqFailed(expr, "true", "false", line);
    }
}

inline void assertFalse(const char* expr, bool value, int line)
{
    if (value) {
        dispAssertEqFailed(expr, "false", "true", line);
    }
}

void runAllTests();

} // RTest

/*************************
         Macros
*************************/

#define RTEST_TYPE2STR(a) #a

#define RTEST_TEST(groupname, testname)                            \
    class groupname##testname : public RTest::ASingleTest {        \
        const char* name() const;                                  \
        void start();                                              \
        void initTestDir();                                        \
        void run();                                                \
                                                                   \
        std::string TMP_PATH;                                       \
    };                                                             \
                                                                   \
    groupname##testname groupname##testname##_instance;            \
                                                                   \
    const char* groupname##testname::name() const {                \
        return RTEST_TYPE2STR(groupname) "_" RTEST_TYPE2STR(testname); \
    }                                                              \
                                                                   \
    void groupname##testname::run() {                              \
        initTestDir();                                             \
        start();                                                   \
    }                                                              \
                                                                   \
    void groupname##testname::initTestDir() {                      \
        TMP_PATH = std::string("tests/tmp/") + name();            \
                                                                   \
        ::system(("rm -rf " + TMP_PATH).c_str());                  \
        ::system(("mkdir -p " + TMP_PATH).c_str());                \
    }                                                              \
                                                                   \
    void groupname##testname::start()

#define RTEST_TEST_F(groupname, testname)			\
    class groupname##testname : public groupname {		\
        const char* name() const;                                  \
        void run();                                               \
        void internalRun();                                       \
    };                                                             \
                                                                   \
    groupname##testname groupname##testname##_instance;            \
                                                                   \
    const char* groupname##testname::name() const {                \
        return RTEST_TYPE2STR(groupname) "_" RTEST_TYPE2STR(testname); \
    }                                                              \
                                                                   \
    void groupname##testname::run() {                              \
        groupname::SetUp();                                       \
        internalRun();                                             \
        groupname::TearDown();                                    \
    }                                                              \
                                                                   \
    void groupname##testname::internalRun()

#ifdef RTEST_SKIP_PREFIX
	#define TEST         RTEST_TEST
	#define TEST_F       RTEST_TEST_F

	#define ASSERT_EQ    RTEST_ASSERT_EQ
	#define ASSERT_NE    RTEST_ASSERT_NE
	#define ASSERT_TRUE  RTEST_ASSERT_TRUE
	#define ASSERT_FALSE RTEST_ASSERT_FALSE
	#define ASSERT_FAIL  RTEST_ASSERT_FAIL
#endif

#define RTEST_ASSERT_EQ(expect, value) RTest::assertEq(#value, expect, value, __LINE__)
#define RTEST_ASSERT_NE(expect, value) RTest::assertNe(#value, expect, value, __LINE__)
#define RTEST_ASSERT_TRUE(value) RTest::assertTrue(#value, value, __LINE__)
#define RTEST_ASSERT_FALSE(value) RTest::assertFalse(#value, value, __LINE__)

#endif /* RTEST_HPP */
