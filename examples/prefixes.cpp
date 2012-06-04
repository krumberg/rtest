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

#include "rtest.hpp"

#include <stdio.h>

class PrefixTest : public RTest::ASingleTest {
public:
    void SetUp() {
        puts("SetUp");
    }

    void TearDown() {
        puts("TearDown");
    }
};

RTEST_TEST_F(PrefixTest, test1) {
    puts("test1");
    RTEST_ASSERT_TRUE(false);
}

RTEST_TEST_F(PrefixTest, test2) {
    puts("test1");
    RTEST_ASSERT_TRUE(true);
}

RTEST_TEST_F(PrefixTest, test3) {
    puts("test2");
    RTEST_ASSERT_EQ(3, 3);
}

RTEST_TEST(PrefixTestNoFixture, test4) {
    puts("test3");
    RTEST_ASSERT_EQ(3, 4);
}

int main()
{
    RTest::runAllTests();

    return 0;
}
