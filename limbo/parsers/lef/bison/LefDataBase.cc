/*************************************************************************
    > File Name: LefDataBase.cpp
    > Author: Yibo Lin
    > Mail: yibolin@utexas.edu
    > Created Time: Thu 11 Dec 2014 04:28:14 PM CST
 ************************************************************************/

#include "LefDataBase.h"
#include <cstring>
#include <cstdlib>

namespace LefParser {

LefDataBase::LefDataBase()
{
	m_current_version = 5.6;
}
double LefDataBase::current_version() const 
{return m_current_version;}
void LefDataBase::current_version(double cv)
{m_current_version = cv;}

int LefDataBase::lefNamesCaseSensitive = TRUE;
int LefDataBase::lefrShiftCase = FALSE;

} // namespace LefParser

namespace LefParser {

void * lefMalloc(int lef_size) 
{
	void * mallocVar;
/*
	if (lefiMallocFunction)
		return (*lefiMallocFunction)(lef_size);
	else */
	{
		mallocVar = (void*)malloc(lef_size);
		if (!mallocVar) {
			fprintf(stderr, "ERROR (LEFPARS-1009): Not enough memory, stop parsing!\n");
			exit (1);
		}
		return mallocVar;
	}
}
void * lefRealloc(void *name, int lef_size) 
{
/*	if (lefiReallocFunction)
		return (*lefiReallocFunction)(name, lef_size);
	else*/
		return (void*)realloc(name, lef_size);
}
void lefFree(void *name) 
{
/*	if (lefiFreeFunction)
		(*lefiFreeFunction)(name);
	else*/
		free(name);
}

} // namespace LefParser
