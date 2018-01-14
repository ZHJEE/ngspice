/**********
Permit to use it as your wish.
Author: 2007 Gong Ding, gdiso@ustc.edu
University of Science and Technology of China
**********/

#include "ngspice/ngspice.h"
#include "ndevdefs.h"
#include "ngspice/suffix.h"


void
NDEVdestroy(GENmodel **inModel)
{
    NDEVmodel *mod = *(NDEVmodel **) inModel;

    while (mod) {
        NDEVmodel *next_mod = NDEVnextModel(mod);
        NDEVinstance *inst = NDEVinstances(mod);
        while (inst) {
            NDEVinstance *next_inst = NDEVnextInstance(inst);
            NDEVdelete(GENinstanceOf(inst));
            inst = next_inst;
        }
        NDEVmDelete(GENmodelOf(mod));
        mod = next_mod;
    }

    *inModel = NULL;
}
