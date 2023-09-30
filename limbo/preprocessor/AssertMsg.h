/**
 * @file   AssertMsg.h
 * @brief  assertion with message 
 *
 * macro: limboAssertMsg, limboAssert
 *
 * attribute: assertion with or without message. 
 *            compared with assert in STL, it provides detailed information on the failures and positions 
 *
 * @author Yibo Lin
 * @date   Nov 2014
 */

#ifndef LIMBO_PREPROCESSOR_ASSERTMSG_H
#define LIMBO_PREPROCESSOR_ASSERTMSG_H

#include <iostream>
#include <limbo/preprocessor/Msg.h>

/// @def limboAssertMsg(condition, args...)
/// @brief custom assertion with message 
/// 
/// example usage: limboAssertMsg(a == 1, "this is %s", name);
#define limboAssertMsg(condition, args...) do {\
    if (!(condition)) \
    {\
        ::limbo::limboPrintAssertMsg(#condition, __FILE__, __LINE__, __PRETTY_FUNCTION__, args); \
        abort(); \
    }\
} while (false)

/// @def limboAssert(condition)
/// @brief custom assertion without message 
///
/// example usage: limboAssert(a == 1);
#define limboAssert(condition) do {\
    if (!(condition)) \
    {\
        ::limbo::limboPrintAssertMsg(#condition, __FILE__, __LINE__, __PRETTY_FUNCTION__); \
        abort(); \
    }\
} while (false)

/// namespace for Limbo
namespace limbo 
{

/// @brief static assertion 
template <bool>
struct StaticAssert;
/// @brief template specialization 
template <>
struct StaticAssert<true> {};

} // namespace limbo

/// @def limboStaticAssert(condition)
/// @brief compile time assertion 
#define limboStaticAssert(condition) {\
    limbo::StaticAssert<(condition) != 0>(); \
}

#endif 
