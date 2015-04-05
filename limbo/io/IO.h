/*************************************************************************
    > File Name: IO.h
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Sat 04 Apr 2015 04:26:46 PM CDT
 ************************************************************************/

#ifndef _LIMBO_IO
#define _LIMBO_IO

#include <cstdio>
#include <cstdarg>

namespace limbo {

void print(const char * format, ...)
{
	va_list args;
	va_start(args, format);

	char buf[1024];
	char* itBgn = format;
	char* itEnd = itBgn+strlen(format);
	char* itBuf = buf;

	for (char *itCur = itBgn, *itPrev = NULL; itCur != itEnd; )
	{
		if (*itCur == '%')
		{
			switch (*itCur)
			{
				case 'd': break;
				case 'u': break;
				case 'o': break;
				case 'x': break;
				case 'X': break;
				case 'f': break;
				case 'F': break;
				case 'e': break;
				case 'E': break;
				case 'g': break;
				case 'G': break;
				case 'a': break;
				case 'A': break;
				case 'c': break;
				case 's': break;
				case 'p': break;
				case 'n': break;
				case '%': break;
			}
		}
		else 
		{
			*itBuf = *itCur;
			++itBuf;
		}
		itPrev = itCur, ++itCur
	}

	va_end(args);
}

} // namespace limbo 

#endif
