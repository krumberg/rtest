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

#include <iostream>

#include "rtest.hpp"

namespace {

/*************************
          View
*************************/

const char* COLOR_RESET       = "\033[0m";
const char* COLOR_RED         = "\033[31m";
const char* COLOR_GREEN       = "\033[32m";

void greenColor()
{
    printf("%s", COLOR_GREEN);
}

void redColor()
{
    printf("%s", COLOR_RED);
}

void resetColor()
{
    printf("%s", COLOR_RESET);
}

void dispTestsRunning()
{
    greenColor();
    std::cout << "Running tests" << std::endl;
}

void dispTestRunning(const char* name)
{
    greenColor();
    std::cout << "Running  " << name << std::endl;
}

void dispTestRan(const char* name)
{
    greenColor();
    std::cout << "\t" << "(OK)" << std::endl;
}

} // namespace

namespace RTest {

void dispAssertEqFailed(const std::string& expect, const std::string& value)
{
    redColor();
    std::cerr << "\t" << "Expected <" << expect << ">, got <" << value << ">" << std::endl;
}

void dispAssertNeFailed(const std::string& expect, const std::string& value)
{
    redColor();
    std::cerr << "\t" << "Expected <" << expect << ">, got a different value than <" << value << ">" << std::endl;
}

class ColorResetter {
public:
    ~ColorResetter() {
        resetColor();
    }
};

ColorResetter colorResetter;

/*************************
   Model and controller
*************************/

SingleTestList& getTestList() {
    static SingleTestList singleTestList;
    return singleTestList;
}

void runAllTests() {
    dispTestsRunning();

    SingleTestList::iterator it(
        getTestList().begin()
    );

    for (; it != getTestList().end(); ++it) {
        dispTestRunning((*it)->name());
        (*it)->run();
        dispTestRan((*it)->name());
    }
}

} // RTest
