/**
 @file   BookshelfDataBase.cc
 @author Yibo Lin
 @date   Jul 2019
 @brief  Implementation of @ref BookshelfParser::BookshelfDataBase
 */

#include <limbo/parsers/bookshelf/bison/BookshelfDataBase.h>
#include <cstring>
#include <cstdlib>

namespace BookshelfParser {

void BookshelfDataBase::bookshelf_user_cbk_reminder(const char* str) const 
{
    cerr << "A corresponding user-defined callback is necessary: " << str << endl;
    exit(0);
}

} // namespace BookshelfParser
