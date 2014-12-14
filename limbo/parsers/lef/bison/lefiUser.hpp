/*
 *     This  file  is  part  of  the  Cadence  LEF/DEF  Open   Source
 *  Distribution,  Product Version 5.7, and is subject to the Cadence
 *  LEF/DEF Open Source License Agreement.   Your  continued  use  of
 *  this file constitutes your acceptance of the terms of the LEF/DEF
 *  Open Source License and an agreement to abide by its  terms.   If
 *  you  don't  agree  with  this, you must remove this and any other
 *  files which are part of the distribution and  destroy any  copies
 *  made.
 *
 *     For updates, support, or to become part of the LEF/DEF Community,
 *  check www.openeda.org for details.
 */

/*
 * User header file for the LEF Interface.  This includes
 * all of the header files which are relevant to both the
 * reader and the writer.
 *
 * lefrReader.h and lefwWriter.h include this file, so that
 * an application only needs to include either lefrReader.h(pp)
 * or lefwWriter.h(pp).
 */

#ifndef LEFI_USER_H
#define LEFI_USER_H

/* General utilities. */
/* #include "lefiMalloc.hpp" */
/* #include "lefiUtils.hpp" */

/*
 * API objects
 */
//#include "lefiDebug.hpp"
#include "lefiUnits.hpp"
#include "lefiLayer.hpp"
#include "lefiVia.hpp"
#include "lefiViaRule.hpp"
#include "lefiMisc.hpp"
#include "lefiNonDefault.hpp"
#include "lefiMacro.hpp"
#include "lefiArray.hpp"
#include "lefiCrossTalk.hpp"
#include "lefiProp.hpp"
#include "lefiPropType.hpp"

/* NEW CALLBACK add the reference here */

#endif
