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

#include <iostream>
#include <sstream>
#include <vector>

namespace RTest {

/*************************
          View
*************************/

void dieWithError(const std::string& expect);
void dispAssertEqFailed(const std::string& expect, const std::string& value);
void dispAssertNeFailed(const std::string& expect, const std::string& value);

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
std::string toStr(A a)
{
    std::stringstream ss;
    ss << a;
    return ss.str();
}

template <typename A>
void assertEq(const A& expect, const A& value)
{
    if (expect != value) {
        dispAssertEqFailed(toStr(expect), toStr(value));
    }
}

template <typename A>
void assertNe(const A& expect, const A& value)
{
    if (expect == value) {
        dispAssertNeFailed(toStr(expect), toStr(value));
    }
}

inline void assertTrue(bool value)
{
    if (!value) {
        dispAssertEqFailed("true", "false");
    }
}

inline void assertFalse(bool value)
{
    if (value) {
        dispAssertEqFailed("false", "true");
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
        void run();                                                \
    };                                                             \
                                                                   \
    groupname##testname groupname##testname##_instance;            \
                                                                   \
    const char* groupname##testname::name() const {                \
        return RTEST_TYPE2STR(groupname) RTEST_TYPE2STR(testname); \
    }                                                              \
                                                                   \
    void groupname##testname::run()

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
        return RTEST_TYPE2STR(groupname) RTEST_TYPE2STR(testname); \
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

#define RTEST_ASSERT_EQ(expect, value) RTest::assertEq(expect, value)
#define RTEST_ASSERT_NE(expect, value) RTest::assertNe(expect, value)
#define RTEST_ASSERT_TRUE(value) RTest::assertTrue(value)
#define RTEST_ASSERT_FALSE(value) RTest::assertFalse(value)
#define RTEST_ASSERT_FAIL(value)

#endif /* RTEST_HPP */
