/*************************************************************************
    > File Name: AssertMsg.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Wed 05 Nov 2014 04:13:47 PM CST
 ************************************************************************/

#ifndef LIMBO_PREPROCESSOR_ASSERTMSG_H
#define LIMBO_PREPROCESSOR_ASSERTMSG_H

/// =======================================================
///      macro: assert_msg (deprecated)
///      attribute: assertion with message 
///                 if defined NO_LIMBO_ASSERTION, call assert in stl
///                 else call custom assertion
///       
///      macro: limboAssertMsg, limboAssert
///      attribute: assertion with or without message 
/// =======================================================
#include <iostream>
#include <limbo/preprocessor/Msg.h>

/// deprecated
/// I leave it here for backward compatibility
/// custom assertion with message 
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

/// custom assertion with message 
/// example usage: limboAssertMsg(condition, "this is %s", name);
#define limboAssertMsg(condition, args...) do {\
    if (!(condition)) \
    {\
        ::limbo::limboPrintAssertMsg(#condition, __FILE__, __LINE__, __PRETTY_FUNCTION__, args); \
        abort(); \
    }\
} while (false)

#define limboAssert(condition) do {\
    if (!(condition)) \
    {\
        ::limbo::limboPrintAssertMsg(#condition, __FILE__, __LINE__, __PRETTY_FUNCTION__); \
        abort(); \
    }\
} while (false)

#endif 
