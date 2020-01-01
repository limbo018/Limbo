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

void BookshelfDataBase::resize_bookshelf_shapes(int n)
{
    cerr << "Bookshelf has " << n << " shapes" << endl; 
    bookshelf_user_cbk_reminder(__func__); 
}

void BookshelfDataBase::resize_bookshelf_niterminal_layers(int n)
{
    cerr << "Bookshelf route has " << n << " NI terminals with layers" << endl; 
    bookshelf_user_cbk_reminder(__func__); 
}

void BookshelfDataBase::resize_bookshelf_blockage_layers(int n)
{
    cerr << "Bookshelf route has " << n << " blockages with layers" << endl; 
    bookshelf_user_cbk_reminder(__func__); 
}

void BookshelfDataBase::add_bookshelf_terminal_NI(string& n, int, int)
{
    cerr << "Bookshelf has terminal_NI " << n << endl; 
    bookshelf_user_cbk_reminder(__func__);
}

void BookshelfDataBase::set_bookshelf_net_weight(string const& name, double w)
{
    cerr << "Bookshelf net weight: " << name << " " << w << endl;
    bookshelf_user_cbk_reminder(__func__);
}

void BookshelfDataBase::set_bookshelf_shape(NodeShape const& shape) 
{
    cerr << "Bookshelf shape: " << shape.node_name << endl; 
    bookshelf_user_cbk_reminder(__func__); 
}

void BookshelfDataBase::set_bookshelf_route_info(RouteInfo const&)
{
    cerr << "Bookshelf route: RouteInfo" << endl; 
    bookshelf_user_cbk_reminder(__func__); 
}

void BookshelfDataBase::add_bookshelf_niterminal_layer(string const& name, string const& layer)
{
    cerr << "Bookshelf route: " << name << ", " << layer << endl; 
    bookshelf_user_cbk_reminder(__func__); 
}

void BookshelfDataBase::add_bookshelf_blockage_layers(string const& name, vector<string> const&)
{
    cerr << "Bookshelf route: " << name << endl; 
    bookshelf_user_cbk_reminder(__func__); 
}

void BookshelfDataBase::bookshelf_user_cbk_reminder(const char* str) const 
{
    cerr << "A corresponding user-defined callback is necessary: " << str << endl;
    exit(0);
}

} // namespace BookshelfParser
