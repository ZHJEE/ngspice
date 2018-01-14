/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

/*
 * This routine deletes a BJT instance from the circuit and frees
 * the storage it was using.
 */

#include "ngspice/ngspice.h"
#include "bjtdefs.h"
#include "ngspice/sperror.h"
#include "ngspice/suffix.h"


int
BJTdelete(GENinstance *inst)
{
    BJTinstance *here = (BJTinstance*) inst;
    FREE(here->BJTsens);
    GENinstanceFree(inst);
    return OK;
}
