/**** BSIM3v3.2.4, Released by Xuemei Xi 12/14/2001 ****/

/**********
 * Copyright 2001 Regents of the University of California. All rights reserved.
 * File: b3dest.c of BSIM3v3.2.4
 * Author: 1995 Min-Chie Jeng and Mansun Chan.
 * Author: 1997-1999 Weidong Liu.
 * Author: 2001  Xuemei Xi
 * Modified by Paolo Nenzi 2002
 **********/

#include "ngspice/ngspice.h"
#include "bsim3v32def.h"
#include "ngspice/suffix.h"


void
BSIM3v32destroy (GENmodel **inModel)
{
    BSIM3v32model *mod = *(BSIM3v32model**) inModel;

    while (mod) {
        BSIM3v32model *next_mod = BSIM3v32nextModel(mod);
        BSIM3v32instance *inst = BSIM3v32instances(mod);
        while (inst) {
            BSIM3v32instance *next_inst = BSIM3v32nextInstance(inst);
            BSIM3v32delete(GENinstanceOf(inst));
            inst = next_inst;
        }

        BSIM3v32mDelete(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}
