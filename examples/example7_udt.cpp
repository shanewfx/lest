// C++11 - report a user-defined data type.

#include "lest.hpp"

namespace ns {

struct book
{
    using text = std::string;

    text author;
    text title;
    text isbn;

    book( text author, text title, text isbn_ )
    : author( author ), title( title ), isbn( isbn_ ) {}

    friend bool operator==( book const & lhs, book const & rhs )
    {
        return lhs.author == rhs.author
            && lhs.title == rhs.title
            && lhs.isbn == rhs.isbn;
    }

    friend bool operator!=( book const & lhs, book const & rhs )
    {
        return ! ( lhs == rhs );
    }
};

} // namespace ns

// provide stream operator for ns::book:

namespace lest {

std::ostream & operator<<( std::ostream & os, ::ns::book const & b )
{
    return os << "[book: " << to_string(b.author) << ", " << to_string(b.title) << ", " << to_string(b.isbn) << "]";
}

} // namespace ns

ns::book atocpp{ "Bjarne Stroustrup", "A Tour of C++.", "978-0-321-95831-0" };
ns::book tcpppl{ "Bjarne Stroustrup", "The C++ Programming Language.", "978-0-321-56384-2" };

const lest::test specification[] =
{
    TEST( "A book reports via the book-specific operator<<()" )
    {
        EXPECT( atocpp != tcpppl );
        EXPECT( atocpp == tcpppl );
    },

    TEST( "A collection of books reports via the book-specific operator<<()" )
    {
        std::vector<ns::book> less = { atocpp }, more = { tcpppl };

        EXPECT( less == more );
    },
};

int main( int argc, char * argv[] )
{
    return lest::run( specification, argc, argv );
}

// cl -nologo -W3 -EHsc -I.. example7_udt.cpp && example7_udt
// g++ -Wall -Wextra -Wmissing-include-dirs -std=c++11 -I.. -o example7_udt.exe example7_udt.cpp && example7_udt

// example7_udt.cpp:52: failed: A book reports via the book-specific operator<<(): atocpp == tcpppl for [book: "Bjarne Stroustrup", "A Tour of C++.", "978-0-321-95831-0"] == [book: "Bjarne Stroustrup", "The C++ Programming Language.", "978-0-321-56384-2"]
// example7_udt.cpp:59: failed: A collection of books reports via the book-specific operator<<(): less == more for { [book: "Bjarne Stroustrup", "A Tour of C++.", "978-0-321-95831-0"], } == { [book: "Bjarne Stroustrup", "The C++ Programming Language.", "978-0-321-56384-2"], }
// 2 out of 2 selected tests failed.