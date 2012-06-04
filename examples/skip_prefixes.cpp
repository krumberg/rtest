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

#define RTEST_SKIP_PREFIX

#include "rtest.hpp"

#include <stdio.h>

class SkipPrefixTest : public RTest::ASingleTest {
public:
    void SetUp() {
        puts("SetUp");
    }

    void TearDown() {
        puts("TearDown");
    }
};

TEST_F(SkipPrefixTest, test1) {
    puts("test1");
    ASSERT_TRUE(false);
}

TEST_F(SkipPrefixTest, test2) {
    puts("test1");
    ASSERT_TRUE(true);
}

TEST_F(SkipPrefixTest, test3) {
    puts("test2");
    ASSERT_EQ(3, 3);
}

TEST(SkipPrefixTestNoFixture, test4) {
    puts("test3");
    ASSERT_EQ(3, 4);
}

int main()
{
    RTest::runAllTests();

    return 0;
}
