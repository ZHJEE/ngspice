/**********
Copyright 1990 Regents of the University of California.  All rights reserved.
Author: 1985 Thomas L. Quarles
Modified: Alan Gillespie
**********/

#include "ngspice/ngspice.h"
#include "mos9defs.h"
#include "ngspice/suffix.h"


void
MOS9destroy(GENmodel **inModel)
{
    MOS9model *mod = *(MOS9model **) inModel;

    while (mod) {
        MOS9model *next_mod = MOS9nextModel(mod);
        MOS9instance *inst = MOS9instances(mod);
        while (inst) {
            MOS9instance *next_inst = MOS9nextInstance(inst);
            MOS9delete(GENinstanceOf(inst));
            inst = next_inst;
        }
        MOS9mDelete(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}
