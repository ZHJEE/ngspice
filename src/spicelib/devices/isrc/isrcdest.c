/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
**********/

#include "ngspice/ngspice.h"
#include "isrcdefs.h"
#include "ngspice/suffix.h"


void
ISRCdestroy(GENmodel **inModel)
{
    ISRCmodel *mod = *(ISRCmodel**) inModel;

    while (mod) {
        ISRCmodel *next_mod = ISRCnextModel(mod);
        ISRCinstance *inst = ISRCinstances(mod);
        while (inst) {
            ISRCinstance *next_inst = ISRCnextInstance(inst);
            ISRCdelete(GENinstanceOf(inst));
            inst = next_inst;
        }
        ISRCmDelete(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}
