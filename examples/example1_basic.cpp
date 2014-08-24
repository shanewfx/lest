#include "lest_basic.hpp"

using namespace std;

const lest::test specification[] =
{
    "Empty string has length zero (succeed)", []
    {
        EXPECT( 0 == string(  ).length() );
        EXPECT( 0 == string("").length() );
    },

    "Text compares lexically (fail)", []
    {
        EXPECT( string("hello") > string("world") );
    },

    "Unexpected exception is reported", []
    {
        EXPECT( (throw std::runtime_error("surprise!"), true) );
    },

    "Unspecified expected exception is captured", []
    {
        EXPECT_THROWS( (throw std::runtime_error("surprise!"), true) );
    },

    "Specified expected exception is captured", []
    {
        EXPECT_THROWS_AS( (throw std::bad_alloc(), true), std::bad_alloc );
    },

    "Expected exception is reported missing", []
    {
        EXPECT_THROWS( true );
    },

    "Specific expected exception is reported missing", []
    {
        EXPECT_THROWS_AS( true, std::runtime_error );
    },
};

int main()
{
    return lest::run( specification );
}

// cl -nologo -Wall -EHsc -I.. example1_basic.cpp && example1_basic
// g++ -Wall -Wextra -Weffc++ -std=c++11 -I.. -o example1_basic.exe example1_basic.cpp && example1_basic

// example1_basic.cpp:15: failed: Text compares lexically (fail): string("hello") > string("world")
// example1_basic.cpp:20: failed: got unexpected exception with message "surprise!": Unexpected exception is reported: (throw std::runtime_error("surprise!"), true)
// example1_basic.cpp:35: failed: didn't get exception: Expected exception is reported missing: true
// example1_basic.cpp:40: failed: didn't get exception of type std::runtime_error: Specific expected exception is reported missing: true
// 4 out of 7 tests failed.