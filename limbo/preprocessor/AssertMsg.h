/*************************************************************************
    > File Name: AssertMsg.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 05 Nov 2014 04:13:47 PM CST
 ************************************************************************/

#ifndef _LIMBO_PREPROCESSOR_ASSERTMSG_H
#define _LIMBO_PREPROCESSOR_ASSERTMSG_H

/// =======================================================
///      macro: assert_msg
///      attribute: assertion with message 
///                 if defined NO_LIMBO_ASSERTION, call assert in stl
///                 else call custom assertion
/// =======================================================
#include <iostream>
#include <cstdlib>
#include <cassert>

/// custom asssertion with message 
/// example usage: assert_msg(condition, "this is " << value << " for test");
#ifndef NO_LIMBO_ASSERTION
#define assert_msg(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << __FILE__ << ":" << __LINE__ << ": " << __PRETTY_FUNCTION__ << ": Assertion `" << #condition << "' failed: " << message << std::endl; \
            abort(); \
        } \
    } while (false)
#else
#define assert_msg(condition, message) \
	do { \
		assert(condition); \
	} while (false)
#endif

#endif 
