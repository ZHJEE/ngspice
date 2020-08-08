
/**********
 * Copyright 2001 Regents of the University of California. All rights reserved.
 * Original File: b3ld.c of BSIM3v3.2.4
 * Author: 1991 JianHui Huang and Min-Chie Jeng.
 * Modified by Mansun Chan (1995).
 * Author: 1997-1999 Weidong Liu.
 * Author: 2001 Xuemei Xi
 * Modified by Xuemei Xi, 10/05, 12/21, 2001.
 * Modified by Paolo Nenzi 2002 and Dietmar Warning 2003
 * Modified by Florian Ballenegger 2020 for SIMD version generation
 **********/

 /**********
 * Modified 2020 by Florian Ballenegger, Anamosic Ballenegger Design
 * Distributed under the same license terms as the original code,
 * see file "B3TERMS_OF_USE"
 **********/
#ifdef USE_OMP
#pragma message "Warning: simd configured without USE_OMP but compiled with - ignored"
#endif
#ifdef NOBYPASS
#pragma message "Warning: simd configured without NOBYPASS but compiled with - ignored"
#endif
#ifdef PREDICTOR
#pragma message "Warning: simd configured without PREDICTOR but compiled with - ignored"
#endif
#ifndef NEWCONV
#pragma message "Warning: simd configured for NEWCONV but compiled without - use anyway"
#endif
#ifndef OMP_EFFMEM
#pragma message "Warning: simd configured for OMP_EFFMEM but compiled without - use anyway"
#endif

{
  Vec2d SourceSatCurrent;
  Vec2d DrainSatCurrent;
  double ag0;
  Vec2d qgd;
  Vec2d qgs;
  Vec2d qgb;
  Vec2d cbhat;
  Vec2d VgstNVt;
  Vec2d ExpVgst;
  Vec2d cdrain;
  Vec2d cdhat;
  Vec2d cdreq;
  Vec2d ceqbd;
  Vec2d ceqbs;
  Vec2d ceqqb;
  Vec2d ceqqd;
  Vec2d ceqqg;
  double ceq;
  double geq;
  Vec2d czbd;
  Vec2d czbdsw;
  Vec2d czbdswg;
  Vec2d czbs;
  Vec2d czbssw;
  Vec2d czbsswg;
  Vec2d evbd;
  Vec2d evbs;
  Vec2d arg;
  Vec2d sarg;
  Vec2d Vfbeff;
  Vec2d dVfbeff_dVg;
  Vec2d dVfbeff_dVd = (Vec2d ){0.0, 0.0};
  Vec2d dVfbeff_dVb;
  Vec2d V3;
  Vec2d V4;
  Vec2d gcbdb;
  Vec2d gcbgb;
  Vec2d gcbsb;
  Vec2d gcddb;
  Vec2d gcdgb;
  Vec2d gcdsb;
  Vec2d gcgdb;
  Vec2d gcggb;
  Vec2d gcgsb;
  Vec2d gcsdb;
  Vec2d gcsgb;
  Vec2d gcssb;
  double MJ;
  double MJSW;
  double MJSWG;
  Vec2d vbd;
  Vec2d vbs;
  Vec2d vds;
  Vec2d vgb;
  Vec2d vgd;
  Vec2d vgs;
  Vec2d qgate = (Vec2d ){0.0, 0.0};
  Vec2d qbulk = (Vec2d ){0.0, 0.0};
  Vec2d qdrn = (Vec2d ){0.0, 0.0};
  Vec2d qsrc;
  Vec2d qinoi;
  Vec2d cqgate;
  Vec2d cqbulk;
  Vec2d cqdrn;
  Vec2d Vds;
  Vec2d Vgs;
  Vec2d Vbs;
  Vec2d Gmbs;
  Vec2d FwdSum;
  Vec2d RevSum;
  Vec2d Vgs_eff;
  Vec2d Vfb;
  Vec2d dVfb_dVb = (Vec2d ){0.0, 0.0};
  Vec2d dVfb_dVd = (Vec2d ){0.0, 0.0};
  Vec2d Phis;
  Vec2d dPhis_dVb;
  Vec2d sqrtPhis;
  Vec2d dsqrtPhis_dVb;
  Vec2d Vth;
  Vec2d dVth_dVb;
  Vec2d dVth_dVd;
  Vec2d Vgst;
  Vec2d dVgst_dVg;
  Vec2d dVgst_dVb;
  Vec2d dVgs_eff_dVg;
  double Nvtm;
  double Vtm;
  Vec2d n;
  Vec2d dn_dVb;
  Vec2d dn_dVd;
  double voffcv;
  Vec2d noff;
  Vec2d dnoff_dVd;
  Vec2d dnoff_dVb;
  Vec2d ExpArg;
  double V0;
  Vec2d CoxWLcen;
  Vec2d QovCox;
  double LINK;
  Vec2d DeltaPhi;
  Vec2d dDeltaPhi_dVg;
  Vec2d dDeltaPhi_dVd;
  Vec2d dDeltaPhi_dVb;
  double Cox;
  double Tox;
  Vec2d Tcen;
  Vec2d dTcen_dVg;
  Vec2d dTcen_dVd;
  Vec2d dTcen_dVb;
  Vec2d Ccen;
  Vec2d Coxeff;
  Vec2d dCoxeff_dVg;
  Vec2d dCoxeff_dVd;
  Vec2d dCoxeff_dVb;
  Vec2d Denomi;
  Vec2d dDenomi_dVg;
  Vec2d dDenomi_dVd;
  Vec2d dDenomi_dVb;
  Vec2d ueff;
  Vec2d dueff_dVg;
  Vec2d dueff_dVd;
  Vec2d dueff_dVb;
  Vec2d Esat;
  Vec2d Vdsat;
  Vec2d EsatL;
  Vec2d dEsatL_dVg;
  Vec2d dEsatL_dVd;
  Vec2d dEsatL_dVb;
  Vec2d dVdsat_dVg;
  Vec2d dVdsat_dVb;
  Vec2d dVdsat_dVd;
  Vec2d Vasat;
  Vec2d dAlphaz_dVg;
  Vec2d dAlphaz_dVb;
  Vec2d dVasat_dVg;
  Vec2d dVasat_dVb;
  Vec2d dVasat_dVd;
  Vec2d Va;
  Vec2d dVa_dVd;
  Vec2d dVa_dVg;
  Vec2d dVa_dVb;
  Vec2d Vbseff;
  Vec2d dVbseff_dVb;
  Vec2d VbseffCV;
  Vec2d dVbseffCV_dVb;
  Vec2d Arg1;
  double One_Third_CoxWL;
  double Two_Third_CoxWL;
  Vec2d Alphaz;
  double CoxWL;
  Vec2d T0;
  Vec2d dT0_dVg;
  Vec2d dT0_dVd;
  Vec2d dT0_dVb;
  Vec2d T1;
  Vec2d dT1_dVg;
  Vec2d dT1_dVd;
  Vec2d dT1_dVb;
  Vec2d T2;
  Vec2d dT2_dVg;
  Vec2d dT2_dVd;
  Vec2d dT2_dVb;
  Vec2d T3;
  Vec2d dT3_dVg;
  Vec2d dT3_dVd;
  Vec2d dT3_dVb;
  Vec2d T4;
  Vec2d T5;
  Vec2d T6;
  Vec2d T7;
  Vec2d T8;
  Vec2d T9;
  Vec2d T10;
  Vec2d T11;
  Vec2d T12;
  Vec2d tmp;
  Vec2d Abulk;
  Vec2d dAbulk_dVb;
  Vec2d Abulk0;
  Vec2d dAbulk0_dVb;
  double tmpuni;
  Vec2d VACLM;
  Vec2d dVACLM_dVg;
  Vec2d dVACLM_dVd;
  Vec2d dVACLM_dVb;
  Vec2d VADIBL;
  Vec2d dVADIBL_dVg;
  Vec2d dVADIBL_dVd;
  Vec2d dVADIBL_dVb;
  Vec2d Xdep;
  Vec2d dXdep_dVb;
  Vec2d lt1;
  Vec2d dlt1_dVb;
  Vec2d ltw;
  Vec2d dltw_dVb;
  Vec2d Delt_vth;
  Vec2d dDelt_vth_dVb;
  Vec2d Theta0;
  Vec2d dTheta0_dVb;
  double TempRatio;
  Vec2d tmp1;
  Vec2d tmp2;
  Vec2d tmp3;
  Vec2d tmp4;
  Vec2d DIBL_Sft;
  Vec2d dDIBL_Sft_dVd;
  Vec2d Lambda;
  Vec2d dLambda_dVg;
  double a1;
  double ScalingFactor;
  Vec2d Vgsteff;
  Vec2d dVgsteff_dVg;
  Vec2d dVgsteff_dVd;
  Vec2d dVgsteff_dVb;
  Vec2d Vdseff;
  Vec2d dVdseff_dVg;
  Vec2d dVdseff_dVd;
  Vec2d dVdseff_dVb;
  Vec2d VdseffCV;
  Vec2d dVdseffCV_dVg;
  Vec2d dVdseffCV_dVd;
  Vec2d dVdseffCV_dVb;
  Vec2d diffVds;
  Vec2d dAbulk_dVg;
  Vec2d beta;
  Vec2d dbeta_dVg;
  Vec2d dbeta_dVd;
  Vec2d dbeta_dVb;
  Vec2d gche;
  Vec2d dgche_dVg;
  Vec2d dgche_dVd;
  Vec2d dgche_dVb;
  Vec2d fgche1;
  Vec2d dfgche1_dVg;
  Vec2d dfgche1_dVd;
  Vec2d dfgche1_dVb;
  Vec2d fgche2;
  Vec2d dfgche2_dVg;
  Vec2d dfgche2_dVd;
  Vec2d dfgche2_dVb;
  Vec2d Idl;
  Vec2d dIdl_dVg;
  Vec2d dIdl_dVd;
  Vec2d dIdl_dVb;
  Vec2d Idsa;
  Vec2d dIdsa_dVg;
  Vec2d dIdsa_dVd;
  Vec2d dIdsa_dVb;
  Vec2d Ids;
  Vec2d Gm;
  Vec2d Gds;
  Vec2d Gmb;
  Vec2d Isub;
  Vec2d Gbd;
  Vec2d Gbg;
  Vec2d Gbb;
  Vec2d VASCBE;
  Vec2d dVASCBE_dVg;
  Vec2d dVASCBE_dVd;
  Vec2d dVASCBE_dVb;
  Vec2d CoxWovL;
  Vec2d Rds;
  Vec2d dRds_dVg;
  Vec2d dRds_dVb;
  Vec2d WVCox;
  Vec2d WVCoxRds;
  Vec2d Vgst2Vtm;
  Vec2d VdsatCV;
  Vec2d dVdsatCV_dVg;
  Vec2d dVdsatCV_dVb;
  double Leff;
  Vec2d Weff;
  Vec2d dWeff_dVg;
  Vec2d dWeff_dVb;
  Vec2d AbulkCV;
  Vec2d dAbulkCV_dVb;
  Vec2d qgdo;
  Vec2d qgso;
  Vec2d cgdo;
  Vec2d cgso;
  Vec2d qcheq = (Vec2d ){0.0, 0.0};
  Vec2d qdef;
  Vec2d gqdef = (Vec2d ){0.0, 0.0};
  Vec2d cqdef;
  Vec2d cqcheq;
  Vec2d gtau_diff;
  Vec2d gtau_drift;
  Vec2d gcqdb = (Vec2d ){0.0, 0.0};
  Vec2d gcqsb = (Vec2d ){0.0, 0.0};
  Vec2d gcqgb = (Vec2d ){0.0, 0.0};
  Vec2d gcqbb = (Vec2d ){0.0, 0.0};
  Vec2d dxpart;
  Vec2d sxpart;
  Vec2d ggtg;
  Vec2d ggtd;
  Vec2d ggts;
  Vec2d ggtb;
  Vec2d ddxpart_dVd;
  Vec2d ddxpart_dVg;
  Vec2d ddxpart_dVb;
  Vec2d ddxpart_dVs;
  Vec2d dsxpart_dVd;
  Vec2d dsxpart_dVg;
  Vec2d dsxpart_dVb;
  Vec2d dsxpart_dVs;
  Vec2d gbspsp;
  Vec2d gbbdp;
  Vec2d gbbsp;
  Vec2d gbspg;
  Vec2d gbspb;
  Vec2d gbspdp;
  Vec2d gbdpdp;
  Vec2d gbdpg;
  Vec2d gbdpb;
  Vec2d gbdpsp;
  Vec2d Cgg;
  Vec2d Cgd;
  Vec2d Cgb;
  Vec2d Cdg;
  Vec2d Cdd;
  Vec2d Cds;
  Vec2d Csg;
  Vec2d Csd;
  Vec2d Css;
  Vec2d Csb;
  Vec2d Cbg;
  Vec2d Cbd;
  Vec2d Cbb;
  Vec2d Cgg1;
  Vec2d Cgb1;
  Vec2d Cgd1;
  Vec2d Cbg1;
  Vec2d Cbb1;
  Vec2d Cbd1;
  Vec2d Qac0;
  Vec2d Qsub0;
  Vec2d dQac0_dVg;
  Vec2d dQac0_dVd = (Vec2d ){0.0, 0.0};
  Vec2d dQac0_dVb;
  Vec2d dQsub0_dVg;
  Vec2d dQsub0_dVd;
  Vec2d dQsub0_dVb;
  Vec2d m;
  Vec2m BSIM3v32mode;
  Vec2m Check;
  int ChargeComputationNeeded;
  int error;
  ScalingFactor = 1.0e-9;
  ChargeComputationNeeded = ((ckt->CKTmode & (((MODEDCTRANCURVE | MODEAC) | MODETRAN) | MODEINITSMSIG)) || ((ckt->CKTmode & MODETRANOP) && (ckt->CKTmode & MODEUIC))) ? (1) : (0);
  vbs = vec2_SIMDLOADDATA(0, data);
  vgs = vec2_SIMDLOADDATA(1, data);
  vds = vec2_SIMDLOADDATA(2, data);
  qdef = vec2_SIMDLOADDATA(3, data);
  cdhat = vec2_SIMDLOADDATA(4, data);
  cbhat = vec2_SIMDLOADDATA(5, data);
  Check = vec2_SIMDLOADDATA(6, data) > 0.5;
  SIMDIFYCMD(start);
  vbd = vbs - vds;
  vgd = vgs - vds;
  vgb = vgs - vbs;
  Nvtm = model->BSIM3v32vtm * model->BSIM3v32jctEmissionCoeff;
  if (model->BSIM3v32acmMod == 0)
  {
    SourceSatCurrent = vec2_SIMDTOVECTOR(1.0e-14);
    if (1)
    {
      Vec2m condmask0 = (((Vec2d ){heres[0]->BSIM3v32sourceArea, heres[1]->BSIM3v32sourceArea}) <= 0.0) & (((Vec2d ){heres[0]->BSIM3v32sourcePerimeter, heres[1]->BSIM3v32sourcePerimeter}) <= 0.0);
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        ;
      }
      {
        SourceSatCurrent = vec2_blend(SourceSatCurrent, (((Vec2d ){heres[0]->BSIM3v32sourceArea, heres[1]->BSIM3v32sourceArea}) * model->BSIM3v32jctTempSatCurDensity) + (((Vec2d ){heres[0]->BSIM3v32sourcePerimeter, heres[1]->BSIM3v32sourcePerimeter}) * model->BSIM3v32jctSidewallTempSatCurDensity), condmask_false0);
      }
    }

    DrainSatCurrent = vec2_SIMDTOVECTOR(1.0e-14);
    if (1)
    {
      Vec2m condmask0 = (((Vec2d ){heres[0]->BSIM3v32drainArea, heres[1]->BSIM3v32drainArea}) <= 0.0) & (((Vec2d ){heres[0]->BSIM3v32drainPerimeter, heres[1]->BSIM3v32drainPerimeter}) <= 0.0);
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        ;
      }
      {
        DrainSatCurrent = vec2_blend(DrainSatCurrent, (((Vec2d ){heres[0]->BSIM3v32drainArea, heres[1]->BSIM3v32drainArea}) * model->BSIM3v32jctTempSatCurDensity) + (((Vec2d ){heres[0]->BSIM3v32drainPerimeter, heres[1]->BSIM3v32drainPerimeter}) * model->BSIM3v32jctSidewallTempSatCurDensity), condmask_false0);
      }
    }

  }
  else
  {
    error = vec2_BSIM3v32_ACM_saturationCurrents(model, heres, &DrainSatCurrent, &SourceSatCurrent);
    if (SIMDANY(error))
      return error;

  }

  if (1)
  {
    Vec2m condmask0 = SourceSatCurrent <= 0.0;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      {
        if (condmask_true0[0])
          heres[0]->BSIM3v32gbs = ckt->CKTgmin;

        if (condmask_true0[1])
          heres[1]->BSIM3v32gbs = ckt->CKTgmin;

      }
      {
        Vec2d val = ((Vec2d ){heres[0]->BSIM3v32gbs, heres[1]->BSIM3v32gbs}) * vbs;
        if (condmask_true0[0])
          heres[0]->BSIM3v32cbs = val[0];

        if (condmask_true0[1])
          heres[1]->BSIM3v32cbs = val[1];

      }
    }
    {
      if (model->BSIM3v32ijth == 0.0)
      {
        evbs = vec2_blend(evbs, vec2_exp(vbs / Nvtm), condmask_false0);
        {
          Vec2d val = ((SourceSatCurrent * evbs) / Nvtm) + ckt->CKTgmin;
          if (condmask_false0[0])
            heres[0]->BSIM3v32gbs = val[0];

          if (condmask_false0[1])
            heres[1]->BSIM3v32gbs = val[1];

        }
        {
          Vec2d val = (SourceSatCurrent * (evbs - 1.0)) + (ckt->CKTgmin * vbs);
          if (condmask_false0[0])
            heres[0]->BSIM3v32cbs = val[0];

          if (condmask_false0[1])
            heres[1]->BSIM3v32cbs = val[1];

        }
      }
      else
      {
        if (1)
        {
          Vec2m condmask1 = vbs < ((Vec2d ){heres[0]->BSIM3v32vjsm, heres[1]->BSIM3v32vjsm});
          Vec2m condmask_true1 = condmask_false0 & condmask1;
          Vec2m condmask_false1 = condmask_false0 & (~condmask1);
          {
            evbs = vec2_blend(evbs, vec2_exp(vbs / Nvtm), condmask_true1);
            {
              Vec2d val = ((SourceSatCurrent * evbs) / Nvtm) + ckt->CKTgmin;
              if (condmask_true1[0])
                heres[0]->BSIM3v32gbs = val[0];

              if (condmask_true1[1])
                heres[1]->BSIM3v32gbs = val[1];

            }
            {
              Vec2d val = (SourceSatCurrent * (evbs - 1.0)) + (ckt->CKTgmin * vbs);
              if (condmask_true1[0])
                heres[0]->BSIM3v32cbs = val[0];

              if (condmask_true1[1])
                heres[1]->BSIM3v32cbs = val[1];

            }
          }
          {
            switch (model->BSIM3v32intVersion)
            {
              case BSIM3v32V324:

              case BSIM3v32V323:

              case BSIM3v32V322:
                T0 = vec2_blend(T0, ((Vec2d ){heres[0]->BSIM3v32IsEvjsm, heres[1]->BSIM3v32IsEvjsm}) / Nvtm, condmask_false1);
              {
                Vec2d val = T0 + ckt->CKTgmin;
                if (condmask_false1[0])
                  heres[0]->BSIM3v32gbs = val[0];

                if (condmask_false1[1])
                  heres[1]->BSIM3v32gbs = val[1];

              }
              {
                Vec2d val = ((((Vec2d ){heres[0]->BSIM3v32IsEvjsm, heres[1]->BSIM3v32IsEvjsm}) - SourceSatCurrent) + (T0 * (vbs - ((Vec2d ){heres[0]->BSIM3v32vjsm, heres[1]->BSIM3v32vjsm})))) + (ckt->CKTgmin * vbs);
                if (condmask_false1[0])
                  heres[0]->BSIM3v32cbs = val[0];

                if (condmask_false1[1])
                  heres[1]->BSIM3v32cbs = val[1];

              }
                break;

              case BSIM3v32V32:

              default:
                T0 = vec2_blend(T0, (SourceSatCurrent + model->BSIM3v32ijth) / Nvtm, condmask_false1);
              {
                Vec2d val = T0 + ckt->CKTgmin;
                if (condmask_false1[0])
                  heres[0]->BSIM3v32gbs = val[0];

                if (condmask_false1[1])
                  heres[1]->BSIM3v32gbs = val[1];

              }
              {
                Vec2d val = (model->BSIM3v32ijth + (ckt->CKTgmin * vbs)) + (T0 * (vbs - ((Vec2d ){heres[0]->BSIM3v32vjsm, heres[1]->BSIM3v32vjsm})));
                if (condmask_false1[0])
                  heres[0]->BSIM3v32cbs = val[0];

                if (condmask_false1[1])
                  heres[1]->BSIM3v32cbs = val[1];

              }

            }

          }
        }

      }

    }
  }

  if (1)
  {
    Vec2m condmask0 = DrainSatCurrent <= 0.0;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      {
        if (condmask_true0[0])
          heres[0]->BSIM3v32gbd = ckt->CKTgmin;

        if (condmask_true0[1])
          heres[1]->BSIM3v32gbd = ckt->CKTgmin;

      }
      {
        Vec2d val = ((Vec2d ){heres[0]->BSIM3v32gbd, heres[1]->BSIM3v32gbd}) * vbd;
        if (condmask_true0[0])
          heres[0]->BSIM3v32cbd = val[0];

        if (condmask_true0[1])
          heres[1]->BSIM3v32cbd = val[1];

      }
    }
    {
      if (model->BSIM3v32ijth == 0.0)
      {
        evbd = vec2_blend(evbd, vec2_exp(vbd / Nvtm), condmask_false0);
        {
          Vec2d val = ((DrainSatCurrent * evbd) / Nvtm) + ckt->CKTgmin;
          if (condmask_false0[0])
            heres[0]->BSIM3v32gbd = val[0];

          if (condmask_false0[1])
            heres[1]->BSIM3v32gbd = val[1];

        }
        {
          Vec2d val = (DrainSatCurrent * (evbd - 1.0)) + (ckt->CKTgmin * vbd);
          if (condmask_false0[0])
            heres[0]->BSIM3v32cbd = val[0];

          if (condmask_false0[1])
            heres[1]->BSIM3v32cbd = val[1];

        }
      }
      else
      {
        if (1)
        {
          Vec2m condmask1 = vbd < ((Vec2d ){heres[0]->BSIM3v32vjdm, heres[1]->BSIM3v32vjdm});
          Vec2m condmask_true1 = condmask_false0 & condmask1;
          Vec2m condmask_false1 = condmask_false0 & (~condmask1);
          {
            evbd = vec2_blend(evbd, vec2_exp(vbd / Nvtm), condmask_true1);
            {
              Vec2d val = ((DrainSatCurrent * evbd) / Nvtm) + ckt->CKTgmin;
              if (condmask_true1[0])
                heres[0]->BSIM3v32gbd = val[0];

              if (condmask_true1[1])
                heres[1]->BSIM3v32gbd = val[1];

            }
            {
              Vec2d val = (DrainSatCurrent * (evbd - 1.0)) + (ckt->CKTgmin * vbd);
              if (condmask_true1[0])
                heres[0]->BSIM3v32cbd = val[0];

              if (condmask_true1[1])
                heres[1]->BSIM3v32cbd = val[1];

            }
          }
          {
            switch (model->BSIM3v32intVersion)
            {
              case BSIM3v32V324:

              case BSIM3v32V323:

              case BSIM3v32V322:
                T0 = vec2_blend(T0, ((Vec2d ){heres[0]->BSIM3v32IsEvjdm, heres[1]->BSIM3v32IsEvjdm}) / Nvtm, condmask_false1);
              {
                Vec2d val = T0 + ckt->CKTgmin;
                if (condmask_false1[0])
                  heres[0]->BSIM3v32gbd = val[0];

                if (condmask_false1[1])
                  heres[1]->BSIM3v32gbd = val[1];

              }
              {
                Vec2d val = ((((Vec2d ){heres[0]->BSIM3v32IsEvjdm, heres[1]->BSIM3v32IsEvjdm}) - DrainSatCurrent) + (T0 * (vbd - ((Vec2d ){heres[0]->BSIM3v32vjdm, heres[1]->BSIM3v32vjdm})))) + (ckt->CKTgmin * vbd);
                if (condmask_false1[0])
                  heres[0]->BSIM3v32cbd = val[0];

                if (condmask_false1[1])
                  heres[1]->BSIM3v32cbd = val[1];

              }
                break;

              case BSIM3v32V32:

              default:
                T0 = vec2_blend(T0, (DrainSatCurrent + model->BSIM3v32ijth) / Nvtm, condmask_false1);
              {
                Vec2d val = T0 + ckt->CKTgmin;
                if (condmask_false1[0])
                  heres[0]->BSIM3v32gbd = val[0];

                if (condmask_false1[1])
                  heres[1]->BSIM3v32gbd = val[1];

              }
              {
                Vec2d val = (model->BSIM3v32ijth + (ckt->CKTgmin * vbd)) + (T0 * (vbd - ((Vec2d ){heres[0]->BSIM3v32vjdm, heres[1]->BSIM3v32vjdm})));
                if (condmask_false1[0])
                  heres[0]->BSIM3v32cbd = val[0];

                if (condmask_false1[1])
                  heres[1]->BSIM3v32cbd = val[1];

              }

            }

          }
        }

      }

    }
  }

  BSIM3v32mode = vds >= 0.0;
  if (1)
  {
    Vec2m condmask0 = BSIM3v32mode;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      Vds = vec2_blend(Vds, vds, condmask_true0);
      Vgs = vec2_blend(Vgs, vgs, condmask_true0);
      Vbs = vec2_blend(Vbs, vbs, condmask_true0);
    }
    {
      Vds = vec2_blend(Vds, -vds, condmask_false0);
      Vgs = vec2_blend(Vgs, vgd, condmask_false0);
      Vbs = vec2_blend(Vbs, vbd, condmask_false0);
    }
  }

  {
    Vec2m modesym;
    modesym = (2 * (BSIM3v32mode & 0x1)) - 1;
    {
      heres[0]->BSIM3v32mode = modesym[0];
      heres[1]->BSIM3v32mode = modesym[1];
    }
  }
  T0 = (Vbs - pParam->BSIM3v32vbsc) - 0.001;
  T1 = vec2_sqrt((T0 * T0) - (0.004 * pParam->BSIM3v32vbsc));
  Vbseff = pParam->BSIM3v32vbsc + (0.5 * (T0 + T1));
  dVbseff_dVb = 0.5 * (1.0 + (T0 / T1));
  if (1)
  {
    Vec2m condmask0 = Vbseff < Vbs;
    Vec2m condmask_true0 = condmask0;
    {
      Vbseff = vec2_blend(Vbseff, Vbs, condmask_true0);
    }
  }

  if (1)
  {
    Vec2m condmask0 = Vbseff > 0.0;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T0 = vec2_blend(T0, pParam->BSIM3v32phi / (pParam->BSIM3v32phi + Vbseff), condmask_true0);
      Phis = vec2_blend(Phis, pParam->BSIM3v32phi * T0, condmask_true0);
      dPhis_dVb = vec2_blend(dPhis_dVb, (-T0) * T0, condmask_true0);
      sqrtPhis = vec2_blend(sqrtPhis, pParam->BSIM3v32phis3 / (pParam->BSIM3v32phi + (0.5 * Vbseff)), condmask_true0);
      dsqrtPhis_dVb = vec2_blend(dsqrtPhis_dVb, (((-0.5) * sqrtPhis) * sqrtPhis) / pParam->BSIM3v32phis3, condmask_true0);
    }
    {
      Phis = vec2_blend(Phis, pParam->BSIM3v32phi - Vbseff, condmask_false0);
      dPhis_dVb = vec2_blend(dPhis_dVb, vec2_SIMDTOVECTOR(-1.0), condmask_false0);
      sqrtPhis = vec2_blend(sqrtPhis, vec2_sqrt(Phis), condmask_false0);
      dsqrtPhis_dVb = vec2_blend(dsqrtPhis_dVb, (-0.5) / sqrtPhis, condmask_false0);
    }
  }

  Xdep = (pParam->BSIM3v32Xdep0 * sqrtPhis) / pParam->BSIM3v32sqrtPhi;
  dXdep_dVb = (pParam->BSIM3v32Xdep0 / pParam->BSIM3v32sqrtPhi) * dsqrtPhis_dVb;
  Leff = pParam->BSIM3v32leff;
  Vtm = model->BSIM3v32vtm;
  T3 = vec2_sqrt(Xdep);
  V0 = pParam->BSIM3v32vbi - pParam->BSIM3v32phi;
  T0 = pParam->BSIM3v32dvt2 * Vbseff;
  T2 = vec2_SIMDTOVECTOR(pParam->BSIM3v32dvt2);
  if (1)
  {
    Vec2m condmask0 = T0 >= (-0.5);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T1 = vec2_blend(T1, 1.0 + T0, condmask_true0);
    }
    {
      T4 = vec2_blend(T4, 1.0 / (3.0 + (8.0 * T0)), condmask_false0);
      T1 = vec2_blend(T1, (1.0 + (3.0 * T0)) * T4, condmask_false0);
      T2 = vec2_blend(T2, (T2 * T4) * T4, condmask_false0);
    }
  }

  lt1 = (model->BSIM3v32factor1 * T3) * T1;
  dlt1_dVb = model->BSIM3v32factor1 * ((((0.5 / T3) * T1) * dXdep_dVb) + (T3 * T2));
  T0 = pParam->BSIM3v32dvt2w * Vbseff;
  if (1)
  {
    Vec2m condmask0 = T0 >= (-0.5);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T1 = vec2_blend(T1, 1.0 + T0, condmask_true0);
      T2 = vec2_blend(T2, vec2_SIMDTOVECTOR(pParam->BSIM3v32dvt2w), condmask_true0);
    }
    {
      T4 = vec2_blend(T4, 1.0 / (3.0 + (8.0 * T0)), condmask_false0);
      T1 = vec2_blend(T1, (1.0 + (3.0 * T0)) * T4, condmask_false0);
      T2 = vec2_blend(T2, (pParam->BSIM3v32dvt2w * T4) * T4, condmask_false0);
    }
  }

  ltw = (model->BSIM3v32factor1 * T3) * T1;
  dltw_dVb = model->BSIM3v32factor1 * ((((0.5 / T3) * T1) * dXdep_dVb) + (T3 * T2));
  T0 = (((-0.5) * pParam->BSIM3v32dvt1) * Leff) / lt1;
  if (1)
  {
    Vec2m condmask0 = T0 > (-EXP_THRESHOLD);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T1 = vec2_blend(T1, vec2_exp(T0), condmask_true0);
      Theta0 = vec2_blend(Theta0, T1 * (1.0 + (2.0 * T1)), condmask_true0);
      dT1_dVb = vec2_blend(dT1_dVb, (((-T0) / lt1) * T1) * dlt1_dVb, condmask_true0);
      dTheta0_dVb = vec2_blend(dTheta0_dVb, (1.0 + (4.0 * T1)) * dT1_dVb, condmask_true0);
    }
    {
      T1 = vec2_blend(T1, vec2_SIMDTOVECTOR(MIN_EXP), condmask_false0);
      Theta0 = vec2_blend(Theta0, T1 * (1.0 + (2.0 * T1)), condmask_false0);
      dTheta0_dVb = vec2_blend(dTheta0_dVb, vec2_SIMDTOVECTOR(0.0), condmask_false0);
    }
  }

  Delt_vth = (pParam->BSIM3v32dvt0 * Theta0) * V0;
  dDelt_vth_dVb = (pParam->BSIM3v32dvt0 * dTheta0_dVb) * V0;
  T0 = ((((-0.5) * pParam->BSIM3v32dvt1w) * pParam->BSIM3v32weff) * Leff) / ltw;
  if (1)
  {
    Vec2m condmask0 = T0 > (-EXP_THRESHOLD);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T1 = vec2_blend(T1, vec2_exp(T0), condmask_true0);
      T2 = vec2_blend(T2, T1 * (1.0 + (2.0 * T1)), condmask_true0);
      dT1_dVb = vec2_blend(dT1_dVb, (((-T0) / ltw) * T1) * dltw_dVb, condmask_true0);
      dT2_dVb = vec2_blend(dT2_dVb, (1.0 + (4.0 * T1)) * dT1_dVb, condmask_true0);
    }
    {
      T1 = vec2_blend(T1, vec2_SIMDTOVECTOR(MIN_EXP), condmask_false0);
      T2 = vec2_blend(T2, T1 * (1.0 + (2.0 * T1)), condmask_false0);
      dT2_dVb = vec2_blend(dT2_dVb, vec2_SIMDTOVECTOR(0.0), condmask_false0);
    }
  }

  T0 = pParam->BSIM3v32dvt0w * T2;
  T2 = T0 * V0;
  dT2_dVb = (pParam->BSIM3v32dvt0w * dT2_dVb) * V0;
  TempRatio = (ckt->CKTtemp / model->BSIM3v32tnom) - 1.0;
  T0 = vec2_SIMDTOVECTOR(sqrt(1.0 + (pParam->BSIM3v32nlx / Leff)));
  T1 = ((pParam->BSIM3v32k1ox * (T0 - 1.0)) * pParam->BSIM3v32sqrtPhi) + (((pParam->BSIM3v32kt1 + (pParam->BSIM3v32kt1l / Leff)) + (pParam->BSIM3v32kt2 * Vbseff)) * TempRatio);
  tmp2 = vec2_SIMDTOVECTOR((model->BSIM3v32tox * pParam->BSIM3v32phi) / (pParam->BSIM3v32weff + pParam->BSIM3v32w0));
  T3 = pParam->BSIM3v32eta0 + (pParam->BSIM3v32etab * Vbseff);
  if (1)
  {
    Vec2m condmask0 = T3 < 1.0e-4;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T9 = vec2_blend(T9, 1.0 / (3.0 - (2.0e4 * T3)), condmask_true0);
      T3 = vec2_blend(T3, (2.0e-4 - T3) * T9, condmask_true0);
      T4 = vec2_blend(T4, T9 * T9, condmask_true0);
    }
    {
      T4 = vec2_blend(T4, vec2_SIMDTOVECTOR(1.0), condmask_false0);
    }
  }

  dDIBL_Sft_dVd = T3 * pParam->BSIM3v32theta0vb0;
  DIBL_Sft = dDIBL_Sft_dVd * Vds;
  Vth = ((((((((model->BSIM3v32type * ((Vec2d ){heres[0]->BSIM3v32vth0, heres[1]->BSIM3v32vth0})) - (pParam->BSIM3v32k1 * pParam->BSIM3v32sqrtPhi)) + (pParam->BSIM3v32k1ox * sqrtPhis)) - (pParam->BSIM3v32k2ox * Vbseff)) - Delt_vth) - T2) + ((pParam->BSIM3v32k3 + (pParam->BSIM3v32k3b * Vbseff)) * tmp2)) + T1) - DIBL_Sft;
  {
    heres[0]->BSIM3v32von = Vth[0];
    heres[1]->BSIM3v32von = Vth[1];
  }
  dVth_dVb = ((((((pParam->BSIM3v32k1ox * dsqrtPhis_dVb) - pParam->BSIM3v32k2ox) - dDelt_vth_dVb) - dT2_dVb) + (pParam->BSIM3v32k3b * tmp2)) - (((pParam->BSIM3v32etab * Vds) * pParam->BSIM3v32theta0vb0) * T4)) + (pParam->BSIM3v32kt2 * TempRatio);
  dVth_dVd = -dDIBL_Sft_dVd;
  tmp2 = (pParam->BSIM3v32nfactor * EPSSI) / Xdep;
  tmp3 = (pParam->BSIM3v32cdsc + (pParam->BSIM3v32cdscb * Vbseff)) + (pParam->BSIM3v32cdscd * Vds);
  tmp4 = ((tmp2 + (tmp3 * Theta0)) + pParam->BSIM3v32cit) / model->BSIM3v32cox;
  if (1)
  {
    Vec2m condmask0 = tmp4 >= (-0.5);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      n = vec2_blend(n, 1.0 + tmp4, condmask_true0);
      dn_dVb = vec2_blend(dn_dVb, (((((-tmp2) / Xdep) * dXdep_dVb) + (tmp3 * dTheta0_dVb)) + (pParam->BSIM3v32cdscb * Theta0)) / model->BSIM3v32cox, condmask_true0);
      dn_dVd = vec2_blend(dn_dVd, (pParam->BSIM3v32cdscd * Theta0) / model->BSIM3v32cox, condmask_true0);
    }
    {
      T0 = vec2_blend(T0, 1.0 / (3.0 + (8.0 * tmp4)), condmask_false0);
      n = vec2_blend(n, (1.0 + (3.0 * tmp4)) * T0, condmask_false0);
      T0 = vec2_blend(T0, T0 * T0, condmask_false0);
      dn_dVb = vec2_blend(dn_dVb, ((((((-tmp2) / Xdep) * dXdep_dVb) + (tmp3 * dTheta0_dVb)) + (pParam->BSIM3v32cdscb * Theta0)) / model->BSIM3v32cox) * T0, condmask_false0);
      dn_dVd = vec2_blend(dn_dVd, ((pParam->BSIM3v32cdscd * Theta0) / model->BSIM3v32cox) * T0, condmask_false0);
    }
  }

  T0 = ((Vec2d ){heres[0]->BSIM3v32vfb, heres[1]->BSIM3v32vfb}) + pParam->BSIM3v32phi;
  Vgs_eff = Vgs;
  dVgs_eff_dVg = vec2_SIMDTOVECTOR(1.0);
  if ((pParam->BSIM3v32ngate > 1.e18) && (pParam->BSIM3v32ngate < 1.e25))
    if (1)
  {
    Vec2m condmask0 = Vgs > T0;
    Vec2m condmask_true0 = condmask0;
    {
      T1 = vec2_blend(T1, vec2_SIMDTOVECTOR((((1.0e6 * Charge_q) * EPSSI) * pParam->BSIM3v32ngate) / (model->BSIM3v32cox * model->BSIM3v32cox)), condmask_true0);
      T4 = vec2_blend(T4, vec2_sqrt(1.0 + ((2.0 * (Vgs - T0)) / T1)), condmask_true0);
      T2 = vec2_blend(T2, T1 * (T4 - 1.0), condmask_true0);
      T3 = vec2_blend(T3, ((0.5 * T2) * T2) / T1, condmask_true0);
      T7 = vec2_blend(T7, (1.12 - T3) - 0.05, condmask_true0);
      T6 = vec2_blend(T6, vec2_sqrt((T7 * T7) + 0.224), condmask_true0);
      T5 = vec2_blend(T5, 1.12 - (0.5 * (T7 + T6)), condmask_true0);
      Vgs_eff = vec2_blend(Vgs_eff, Vgs - T5, condmask_true0);
      dVgs_eff_dVg = vec2_blend(dVgs_eff_dVg, 1.0 - ((0.5 - (0.5 / T4)) * (1.0 + (T7 / T6))), condmask_true0);
    }
  }


  Vgst = Vgs_eff - Vth;
  T10 = (2.0 * n) * Vtm;
  VgstNVt = Vgst / T10;
  ExpArg = ((2.0 * pParam->BSIM3v32voff) - Vgst) / T10;
  T0 = VgstNVt;
  if (1)
  {
    Vec2m condmask0 = ExpArg > EXP_THRESHOLD;
    Vec2m condmask_true0 = condmask0;
    T0 = vec2_blend(T0, (Vgst - pParam->BSIM3v32voff) / (n * Vtm), condmask_true0);
  }

  ExpVgst = vec2_exp(T0);
  if (1)
  {
    Vec2m condmask0 = VgstNVt > EXP_THRESHOLD;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      Vgsteff = vec2_blend(Vgsteff, Vgst, condmask_true0);
      dVgsteff_dVg = vec2_blend(dVgsteff_dVg, dVgs_eff_dVg, condmask_true0);
      dVgsteff_dVd = vec2_blend(dVgsteff_dVd, -dVth_dVd, condmask_true0);
      dVgsteff_dVb = vec2_blend(dVgsteff_dVb, -dVth_dVb, condmask_true0);
    }
    if (1)
    {
      Vec2m condmask1 = ExpArg > EXP_THRESHOLD;
      Vec2m condmask_true1 = condmask_false0 & condmask1;
      Vec2m condmask_false1 = condmask_false0 & (~condmask1);
      {
        Vgsteff = vec2_blend(Vgsteff, ((Vtm * pParam->BSIM3v32cdep0) / model->BSIM3v32cox) * ExpVgst, condmask_true1);
        dVgsteff_dVg = vec2_blend(dVgsteff_dVg, Vgsteff / (n * Vtm), condmask_true1);
        dVgsteff_dVd = vec2_blend(dVgsteff_dVd, (-dVgsteff_dVg) * (dVth_dVd + ((T0 * Vtm) * dn_dVd)), condmask_true1);
        dVgsteff_dVb = vec2_blend(dVgsteff_dVb, (-dVgsteff_dVg) * (dVth_dVb + ((T0 * Vtm) * dn_dVb)), condmask_true1);
        dVgsteff_dVg = vec2_blend(dVgsteff_dVg, dVgsteff_dVg * dVgs_eff_dVg, condmask_true1);
      }
      {
        T1 = vec2_blend(T1, T10 * vec2_log(1.0 + ExpVgst), condmask_false1);
        dT1_dVg = vec2_blend(dT1_dVg, ExpVgst / (1.0 + ExpVgst), condmask_false1);
        dT1_dVb = vec2_blend(dT1_dVb, ((-dT1_dVg) * (dVth_dVb + ((Vgst / n) * dn_dVb))) + ((T1 / n) * dn_dVb), condmask_false1);
        dT1_dVd = vec2_blend(dT1_dVd, ((-dT1_dVg) * (dVth_dVd + ((Vgst / n) * dn_dVd))) + ((T1 / n) * dn_dVd), condmask_false1);
        dT2_dVg = vec2_blend(dT2_dVg, ((-model->BSIM3v32cox) / (Vtm * pParam->BSIM3v32cdep0)) * vec2_exp(ExpArg), condmask_false1);
        T2 = vec2_blend(T2, 1.0 - (T10 * dT2_dVg), condmask_false1);
        dT2_dVd = vec2_blend(dT2_dVd, ((-dT2_dVg) * (dVth_dVd - (((2.0 * Vtm) * ExpArg) * dn_dVd))) + (((T2 - 1.0) / n) * dn_dVd), condmask_false1);
        dT2_dVb = vec2_blend(dT2_dVb, ((-dT2_dVg) * (dVth_dVb - (((2.0 * Vtm) * ExpArg) * dn_dVb))) + (((T2 - 1.0) / n) * dn_dVb), condmask_false1);
        Vgsteff = vec2_blend(Vgsteff, T1 / T2, condmask_false1);
        T3 = vec2_blend(T3, T2 * T2, condmask_false1);
        dVgsteff_dVg = vec2_blend(dVgsteff_dVg, (((T2 * dT1_dVg) - (T1 * dT2_dVg)) / T3) * dVgs_eff_dVg, condmask_false1);
        dVgsteff_dVd = vec2_blend(dVgsteff_dVd, ((T2 * dT1_dVd) - (T1 * dT2_dVd)) / T3, condmask_false1);
        dVgsteff_dVb = vec2_blend(dVgsteff_dVb, ((T2 * dT1_dVb) - (T1 * dT2_dVb)) / T3, condmask_false1);
      }
    }

  }

  if (model->BSIM3v32intVersion > BSIM3v32V323)
  {
    {
      heres[0]->BSIM3v32Vgsteff = Vgsteff[0];
      heres[1]->BSIM3v32Vgsteff = Vgsteff[1];
    }
  }

  T9 = sqrtPhis - pParam->BSIM3v32sqrtPhi;
  Weff = pParam->BSIM3v32weff - (2.0 * ((pParam->BSIM3v32dwg * Vgsteff) + (pParam->BSIM3v32dwb * T9)));
  dWeff_dVg = vec2_SIMDTOVECTOR((-2.0) * pParam->BSIM3v32dwg);
  dWeff_dVb = ((-2.0) * pParam->BSIM3v32dwb) * dsqrtPhis_dVb;
  if (1)
  {
    Vec2m condmask0 = Weff < 2.0e-8;
    Vec2m condmask_true0 = condmask0;
    {
      T0 = vec2_blend(T0, 1.0 / (6.0e-8 - (2.0 * Weff)), condmask_true0);
      Weff = vec2_blend(Weff, (2.0e-8 * (4.0e-8 - Weff)) * T0, condmask_true0);
      T0 = vec2_blend(T0, T0 * (T0 * 4.0e-16), condmask_true0);
      dWeff_dVg = vec2_blend(dWeff_dVg, dWeff_dVg * T0, condmask_true0);
      dWeff_dVb = vec2_blend(dWeff_dVb, dWeff_dVb * T0, condmask_true0);
    }
  }

  T0 = (pParam->BSIM3v32prwg * Vgsteff) + (pParam->BSIM3v32prwb * T9);
  if (1)
  {
    Vec2m condmask0 = T0 >= (-0.9);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      Rds = vec2_blend(Rds, pParam->BSIM3v32rds0 * (1.0 + T0), condmask_true0);
      dRds_dVg = vec2_blend(dRds_dVg, vec2_SIMDTOVECTOR(pParam->BSIM3v32rds0 * pParam->BSIM3v32prwg), condmask_true0);
      dRds_dVb = vec2_blend(dRds_dVb, (pParam->BSIM3v32rds0 * pParam->BSIM3v32prwb) * dsqrtPhis_dVb, condmask_true0);
    }
    {
      T1 = vec2_blend(T1, 1.0 / (17.0 + (20.0 * T0)), condmask_false0);
      Rds = vec2_blend(Rds, (pParam->BSIM3v32rds0 * (0.8 + T0)) * T1, condmask_false0);
      T1 = vec2_blend(T1, T1 * T1, condmask_false0);
      dRds_dVg = vec2_blend(dRds_dVg, (pParam->BSIM3v32rds0 * pParam->BSIM3v32prwg) * T1, condmask_false0);
      dRds_dVb = vec2_blend(dRds_dVb, ((pParam->BSIM3v32rds0 * pParam->BSIM3v32prwb) * dsqrtPhis_dVb) * T1, condmask_false0);
    }
  }

  if (model->BSIM3v32intVersion > BSIM3v32V323)
  {
    {
      heres[0]->BSIM3v32rds = Rds[0];
      heres[1]->BSIM3v32rds = Rds[1];
    }
  }

  T1 = (0.5 * pParam->BSIM3v32k1ox) / sqrtPhis;
  dT1_dVb = ((-T1) / sqrtPhis) * dsqrtPhis_dVb;
  T9 = vec2_sqrt(pParam->BSIM3v32xj * Xdep);
  tmp1 = Leff + (2.0 * T9);
  T5 = Leff / tmp1;
  tmp2 = pParam->BSIM3v32a0 * T5;
  tmp3 = vec2_SIMDTOVECTOR(pParam->BSIM3v32weff + pParam->BSIM3v32b1);
  tmp4 = pParam->BSIM3v32b0 / tmp3;
  T2 = tmp2 + tmp4;
  dT2_dVb = (((-T9) / tmp1) / Xdep) * dXdep_dVb;
  T6 = T5 * T5;
  T7 = T5 * T6;
  Abulk0 = 1.0 + (T1 * T2);
  dAbulk0_dVb = ((T1 * tmp2) * dT2_dVb) + (T2 * dT1_dVb);
  T8 = (pParam->BSIM3v32ags * pParam->BSIM3v32a0) * T7;
  dAbulk_dVg = (-T1) * T8;
  Abulk = Abulk0 + (dAbulk_dVg * Vgsteff);
  dAbulk_dVb = dAbulk0_dVb - ((T8 * Vgsteff) * (dT1_dVb + ((3.0 * T1) * dT2_dVb)));
  if (1)
  {
    Vec2m condmask0 = Abulk0 < 0.1;
    Vec2m condmask_true0 = condmask0;
    {
      T9 = vec2_blend(T9, 1.0 / (3.0 - (20.0 * Abulk0)), condmask_true0);
      Abulk0 = vec2_blend(Abulk0, (0.2 - Abulk0) * T9, condmask_true0);
      dAbulk0_dVb = vec2_blend(dAbulk0_dVb, dAbulk0_dVb * (T9 * T9), condmask_true0);
    }
  }

  if (1)
  {
    Vec2m condmask0 = Abulk < 0.1;
    Vec2m condmask_true0 = condmask0;
    {
      T9 = vec2_blend(T9, 1.0 / (3.0 - (20.0 * Abulk)), condmask_true0);
      Abulk = vec2_blend(Abulk, (0.2 - Abulk) * T9, condmask_true0);
      if (model->BSIM3v32intVersion > BSIM3v32V32)
      {
        T10 = vec2_blend(T10, T9 * T9, condmask_true0);
        dAbulk_dVb = vec2_blend(dAbulk_dVb, dAbulk_dVb * T10, condmask_true0);
        dAbulk_dVg = vec2_blend(dAbulk_dVg, dAbulk_dVg * T10, condmask_true0);
      }
      else
      {
        dAbulk_dVb = vec2_blend(dAbulk_dVb, dAbulk_dVb * (T9 * T9), condmask_true0);
      }

    }
  }

  if (model->BSIM3v32intVersion > BSIM3v32V323)
  {
    {
      heres[0]->BSIM3v32Abulk = Abulk[0];
      heres[1]->BSIM3v32Abulk = Abulk[1];
    }
  }

  T2 = pParam->BSIM3v32keta * Vbseff;
  if (1)
  {
    Vec2m condmask0 = T2 >= (-0.9);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T0 = vec2_blend(T0, 1.0 / (1.0 + T2), condmask_true0);
      dT0_dVb = vec2_blend(dT0_dVb, ((-pParam->BSIM3v32keta) * T0) * T0, condmask_true0);
    }
    {
      T1 = vec2_blend(T1, 1.0 / (0.8 + T2), condmask_false0);
      T0 = vec2_blend(T0, (17.0 + (20.0 * T2)) * T1, condmask_false0);
      dT0_dVb = vec2_blend(dT0_dVb, ((-pParam->BSIM3v32keta) * T1) * T1, condmask_false0);
    }
  }

  dAbulk_dVg *= T0;
  dAbulk_dVb = (dAbulk_dVb * T0) + (Abulk * dT0_dVb);
  dAbulk0_dVb = (dAbulk0_dVb * T0) + (Abulk0 * dT0_dVb);
  Abulk *= T0;
  Abulk0 *= T0;
  if (model->BSIM3v32mobMod == 1)
  {
    T0 = (Vgsteff + Vth) + Vth;
    T2 = pParam->BSIM3v32ua + (pParam->BSIM3v32uc * Vbseff);
    T3 = T0 / model->BSIM3v32tox;
    T5 = T3 * (T2 + (pParam->BSIM3v32ub * T3));
    dDenomi_dVg = (T2 + ((2.0 * pParam->BSIM3v32ub) * T3)) / model->BSIM3v32tox;
    dDenomi_dVd = (dDenomi_dVg * 2.0) * dVth_dVd;
    dDenomi_dVb = ((dDenomi_dVg * 2.0) * dVth_dVb) + (pParam->BSIM3v32uc * T3);
  }
  else
    if (model->BSIM3v32mobMod == 2)
  {
    T5 = (Vgsteff / model->BSIM3v32tox) * ((pParam->BSIM3v32ua + (pParam->BSIM3v32uc * Vbseff)) + ((pParam->BSIM3v32ub * Vgsteff) / model->BSIM3v32tox));
    dDenomi_dVg = ((pParam->BSIM3v32ua + (pParam->BSIM3v32uc * Vbseff)) + (((2.0 * pParam->BSIM3v32ub) * Vgsteff) / model->BSIM3v32tox)) / model->BSIM3v32tox;
    dDenomi_dVd = vec2_SIMDTOVECTOR(0.0);
    dDenomi_dVb = (Vgsteff * pParam->BSIM3v32uc) / model->BSIM3v32tox;
  }
  else
  {
    T0 = (Vgsteff + Vth) + Vth;
    T2 = 1.0 + (pParam->BSIM3v32uc * Vbseff);
    T3 = T0 / model->BSIM3v32tox;
    T4 = T3 * (pParam->BSIM3v32ua + (pParam->BSIM3v32ub * T3));
    T5 = T4 * T2;
    dDenomi_dVg = ((pParam->BSIM3v32ua + ((2.0 * pParam->BSIM3v32ub) * T3)) * T2) / model->BSIM3v32tox;
    dDenomi_dVd = (dDenomi_dVg * 2.0) * dVth_dVd;
    dDenomi_dVb = ((dDenomi_dVg * 2.0) * dVth_dVb) + (pParam->BSIM3v32uc * T4);
  }


  if (1)
  {
    Vec2m condmask0 = T5 >= (-0.8);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      Denomi = vec2_blend(Denomi, 1.0 + T5, condmask_true0);
    }
    {
      T9 = vec2_blend(T9, 1.0 / (7.0 + (10.0 * T5)), condmask_false0);
      Denomi = vec2_blend(Denomi, (0.6 + T5) * T9, condmask_false0);
      T9 = vec2_blend(T9, T9 * T9, condmask_false0);
      dDenomi_dVg = vec2_blend(dDenomi_dVg, dDenomi_dVg * T9, condmask_false0);
      dDenomi_dVd = vec2_blend(dDenomi_dVd, dDenomi_dVd * T9, condmask_false0);
      dDenomi_dVb = vec2_blend(dDenomi_dVb, dDenomi_dVb * T9, condmask_false0);
    }
  }

  {
    Vec2d val = ueff = ((Vec2d ){heres[0]->BSIM3v32u0temp, heres[1]->BSIM3v32u0temp}) / Denomi;
    heres[0]->BSIM3v32ueff = val[0];
    heres[1]->BSIM3v32ueff = val[1];
  }
  T9 = (-ueff) / Denomi;
  dueff_dVg = T9 * dDenomi_dVg;
  dueff_dVd = T9 * dDenomi_dVd;
  dueff_dVb = T9 * dDenomi_dVb;
  WVCox = (Weff * pParam->BSIM3v32vsattemp) * model->BSIM3v32cox;
  WVCoxRds = WVCox * Rds;
  Esat = (2.0 * pParam->BSIM3v32vsattemp) / ueff;
  EsatL = Esat * Leff;
  T0 = (-EsatL) / ueff;
  dEsatL_dVg = T0 * dueff_dVg;
  dEsatL_dVd = T0 * dueff_dVd;
  dEsatL_dVb = T0 * dueff_dVb;
  a1 = pParam->BSIM3v32a1;
  if (a1 == 0.0)
  {
    Lambda = vec2_SIMDTOVECTOR(pParam->BSIM3v32a2);
    dLambda_dVg = vec2_SIMDTOVECTOR(0.0);
  }
  else
    if (a1 > 0.0)
  {
    T0 = vec2_SIMDTOVECTOR(1.0 - pParam->BSIM3v32a2);
    T1 = (T0 - (pParam->BSIM3v32a1 * Vgsteff)) - 0.0001;
    T2 = vec2_sqrt((T1 * T1) + (0.0004 * T0));
    Lambda = (pParam->BSIM3v32a2 + T0) - (0.5 * (T1 + T2));
    dLambda_dVg = (0.5 * pParam->BSIM3v32a1) * (1.0 + (T1 / T2));
  }
  else
  {
    T1 = (pParam->BSIM3v32a2 + (pParam->BSIM3v32a1 * Vgsteff)) - 0.0001;
    T2 = vec2_sqrt((T1 * T1) + (0.0004 * pParam->BSIM3v32a2));
    Lambda = 0.5 * (T1 + T2);
    dLambda_dVg = (0.5 * pParam->BSIM3v32a1) * (1.0 + (T1 / T2));
  }


  Vgst2Vtm = Vgsteff + (2.0 * Vtm);
  if (model->BSIM3v32intVersion > BSIM3v32V323)
  {
    {
      Vec2d val = Abulk / Vgst2Vtm;
      heres[0]->BSIM3v32AbovVgst2Vtm = val[0];
      heres[1]->BSIM3v32AbovVgst2Vtm = val[1];
    }
  }

  if (1)
  {
    Vec2m condmask0 = Rds > 0;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      tmp2 = vec2_blend(tmp2, (dRds_dVg / Rds) + (dWeff_dVg / Weff), condmask_true0);
      tmp3 = vec2_blend(tmp3, (dRds_dVb / Rds) + (dWeff_dVb / Weff), condmask_true0);
    }
    {
      tmp2 = vec2_blend(tmp2, dWeff_dVg / Weff, condmask_false0);
      tmp3 = vec2_blend(tmp3, dWeff_dVb / Weff, condmask_false0);
    }
  }

  if (1)
  {
    Vec2m condmask0 = (Rds == 0.0) & (Lambda == 1.0);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T0 = vec2_blend(T0, 1.0 / ((Abulk * EsatL) + Vgst2Vtm), condmask_true0);
      tmp1 = vec2_blend(tmp1, vec2_SIMDTOVECTOR(0.0), condmask_true0);
      T1 = vec2_blend(T1, T0 * T0, condmask_true0);
      T2 = vec2_blend(T2, Vgst2Vtm * T0, condmask_true0);
      T3 = vec2_blend(T3, EsatL * Vgst2Vtm, condmask_true0);
      Vdsat = vec2_blend(Vdsat, T3 * T0, condmask_true0);
      dT0_dVg = vec2_blend(dT0_dVg, (-(((Abulk * dEsatL_dVg) + (EsatL * dAbulk_dVg)) + 1.0)) * T1, condmask_true0);
      dT0_dVd = vec2_blend(dT0_dVd, (-(Abulk * dEsatL_dVd)) * T1, condmask_true0);
      dT0_dVb = vec2_blend(dT0_dVb, (-((Abulk * dEsatL_dVb) + (dAbulk_dVb * EsatL))) * T1, condmask_true0);
      dVdsat_dVg = vec2_blend(dVdsat_dVg, ((T3 * dT0_dVg) + (T2 * dEsatL_dVg)) + (EsatL * T0), condmask_true0);
      dVdsat_dVd = vec2_blend(dVdsat_dVd, (T3 * dT0_dVd) + (T2 * dEsatL_dVd), condmask_true0);
      dVdsat_dVb = vec2_blend(dVdsat_dVb, (T3 * dT0_dVb) + (T2 * dEsatL_dVb), condmask_true0);
    }
    {
      tmp1 = vec2_blend(tmp1, dLambda_dVg / (Lambda * Lambda), condmask_false0);
      T9 = vec2_blend(T9, Abulk * WVCoxRds, condmask_false0);
      T8 = vec2_blend(T8, Abulk * T9, condmask_false0);
      T7 = vec2_blend(T7, Vgst2Vtm * T9, condmask_false0);
      T6 = vec2_blend(T6, Vgst2Vtm * WVCoxRds, condmask_false0);
      T0 = vec2_blend(T0, (2.0 * Abulk) * ((T9 - 1.0) + (1.0 / Lambda)), condmask_false0);
      dT0_dVg = vec2_blend(dT0_dVg, 2.0 * (((T8 * tmp2) - (Abulk * tmp1)) + ((((2.0 * T9) + (1.0 / Lambda)) - 1.0) * dAbulk_dVg)), condmask_false0);
      dT0_dVb = vec2_blend(dT0_dVb, 2.0 * ((T8 * (((2.0 / Abulk) * dAbulk_dVb) + tmp3)) + (((1.0 / Lambda) - 1.0) * dAbulk_dVb)), condmask_false0);
      dT0_dVd = vec2_blend(dT0_dVd, vec2_SIMDTOVECTOR(0.0), condmask_false0);
      T1 = vec2_blend(T1, ((Vgst2Vtm * ((2.0 / Lambda) - 1.0)) + (Abulk * EsatL)) + (3.0 * T7), condmask_false0);
      dT1_dVg = vec2_blend(dT1_dVg, (((((2.0 / Lambda) - 1.0) - ((2.0 * Vgst2Vtm) * tmp1)) + (Abulk * dEsatL_dVg)) + (EsatL * dAbulk_dVg)) + (3.0 * ((T9 + (T7 * tmp2)) + (T6 * dAbulk_dVg))), condmask_false0);
      dT1_dVb = vec2_blend(dT1_dVb, ((Abulk * dEsatL_dVb) + (EsatL * dAbulk_dVb)) + (3.0 * ((T6 * dAbulk_dVb) + (T7 * tmp3))), condmask_false0);
      dT1_dVd = vec2_blend(dT1_dVd, Abulk * dEsatL_dVd, condmask_false0);
      T2 = vec2_blend(T2, Vgst2Vtm * (EsatL + (2.0 * T6)), condmask_false0);
      dT2_dVg = vec2_blend(dT2_dVg, (EsatL + (Vgst2Vtm * dEsatL_dVg)) + (T6 * (4.0 + ((2.0 * Vgst2Vtm) * tmp2))), condmask_false0);
      dT2_dVb = vec2_blend(dT2_dVb, Vgst2Vtm * (dEsatL_dVb + ((2.0 * T6) * tmp3)), condmask_false0);
      dT2_dVd = vec2_blend(dT2_dVd, Vgst2Vtm * dEsatL_dVd, condmask_false0);
      T3 = vec2_blend(T3, vec2_sqrt((T1 * T1) - ((2.0 * T0) * T2)), condmask_false0);
      Vdsat = vec2_blend(Vdsat, (T1 - T3) / T0, condmask_false0);
      dT3_dVg = vec2_blend(dT3_dVg, ((T1 * dT1_dVg) - (2.0 * ((T0 * dT2_dVg) + (T2 * dT0_dVg)))) / T3, condmask_false0);
      dT3_dVd = vec2_blend(dT3_dVd, ((T1 * dT1_dVd) - (2.0 * ((T0 * dT2_dVd) + (T2 * dT0_dVd)))) / T3, condmask_false0);
      dT3_dVb = vec2_blend(dT3_dVb, ((T1 * dT1_dVb) - (2.0 * ((T0 * dT2_dVb) + (T2 * dT0_dVb)))) / T3, condmask_false0);
      dVdsat_dVg = vec2_blend(dVdsat_dVg, ((dT1_dVg - ((((T1 * dT1_dVg) - (dT0_dVg * T2)) - (T0 * dT2_dVg)) / T3)) - (Vdsat * dT0_dVg)) / T0, condmask_false0);
      dVdsat_dVb = vec2_blend(dVdsat_dVb, ((dT1_dVb - ((((T1 * dT1_dVb) - (dT0_dVb * T2)) - (T0 * dT2_dVb)) / T3)) - (Vdsat * dT0_dVb)) / T0, condmask_false0);
      dVdsat_dVd = vec2_blend(dVdsat_dVd, (dT1_dVd - (((T1 * dT1_dVd) - (T0 * dT2_dVd)) / T3)) / T0, condmask_false0);
    }
  }

  {
    heres[0]->BSIM3v32vdsat = Vdsat[0];
    heres[1]->BSIM3v32vdsat = Vdsat[1];
  }
  T1 = (Vdsat - Vds) - pParam->BSIM3v32delta;
  dT1_dVg = dVdsat_dVg;
  dT1_dVd = dVdsat_dVd - 1.0;
  dT1_dVb = dVdsat_dVb;
  T2 = vec2_sqrt((T1 * T1) + ((4.0 * pParam->BSIM3v32delta) * Vdsat));
  T0 = T1 / T2;
  T3 = (2.0 * pParam->BSIM3v32delta) / T2;
  dT2_dVg = (T0 * dT1_dVg) + (T3 * dVdsat_dVg);
  dT2_dVd = (T0 * dT1_dVd) + (T3 * dVdsat_dVd);
  dT2_dVb = (T0 * dT1_dVb) + (T3 * dVdsat_dVb);
  Vdseff = Vdsat - (0.5 * (T1 + T2));
  dVdseff_dVg = dVdsat_dVg - (0.5 * (dT1_dVg + dT2_dVg));
  dVdseff_dVd = dVdsat_dVd - (0.5 * (dT1_dVd + dT2_dVd));
  dVdseff_dVb = dVdsat_dVb - (0.5 * (dT1_dVb + dT2_dVb));
  switch (model->BSIM3v32intVersion)
  {
    case BSIM3v32V324:

    case BSIM3v32V323:

    case BSIM3v32V322:
      if (1)
    {
      Vec2m condmask0 = Vds == 0.0;
      Vec2m condmask_true0 = condmask0;
      {
        Vdseff = vec2_blend(Vdseff, vec2_SIMDTOVECTOR(0.0), condmask_true0);
        dVdseff_dVg = vec2_blend(dVdseff_dVg, vec2_SIMDTOVECTOR(0.0), condmask_true0);
        dVdseff_dVb = vec2_blend(dVdseff_dVb, vec2_SIMDTOVECTOR(0.0), condmask_true0);
      }
    }

      break;

    case BSIM3v32V32:

    default:
      break;

  }

  tmp4 = 1.0 - (((0.5 * Abulk) * Vdsat) / Vgst2Vtm);
  T9 = WVCoxRds * Vgsteff;
  T8 = T9 / Vgst2Vtm;
  T0 = (EsatL + Vdsat) + ((2.0 * T9) * tmp4);
  T7 = (2.0 * WVCoxRds) * tmp4;
  dT0_dVg = ((dEsatL_dVg + dVdsat_dVg) + (T7 * (1.0 + (tmp2 * Vgsteff)))) - (T8 * (((Abulk * dVdsat_dVg) - ((Abulk * Vdsat) / Vgst2Vtm)) + (Vdsat * dAbulk_dVg)));
  dT0_dVb = ((dEsatL_dVb + dVdsat_dVb) + ((T7 * tmp3) * Vgsteff)) - (T8 * ((dAbulk_dVb * Vdsat) + (Abulk * dVdsat_dVb)));
  dT0_dVd = (dEsatL_dVd + dVdsat_dVd) - ((T8 * Abulk) * dVdsat_dVd);
  T9 = WVCoxRds * Abulk;
  T1 = ((2.0 / Lambda) - 1.0) + T9;
  dT1_dVg = ((-2.0) * tmp1) + (WVCoxRds * ((Abulk * tmp2) + dAbulk_dVg));
  dT1_dVb = (dAbulk_dVb * WVCoxRds) + (T9 * tmp3);
  Vasat = T0 / T1;
  dVasat_dVg = (dT0_dVg - (Vasat * dT1_dVg)) / T1;
  dVasat_dVb = (dT0_dVb - (Vasat * dT1_dVb)) / T1;
  dVasat_dVd = dT0_dVd / T1;
  if (1)
  {
    Vec2m condmask0 = Vdseff > Vds;
    Vec2m condmask_true0 = condmask0;
    Vdseff = vec2_blend(Vdseff, Vds, condmask_true0);
  }

  diffVds = Vds - Vdseff;
  if (model->BSIM3v32intVersion > BSIM3v32V323)
  {
    {
      heres[0]->BSIM3v32Vdseff = Vdseff[0];
      heres[1]->BSIM3v32Vdseff = Vdseff[1];
    }
  }

  VACLM = vec2_SIMDTOVECTOR(MAX_EXP);
  dVACLM_dVd = (dVACLM_dVg = (dVACLM_dVb = vec2_SIMDTOVECTOR(0.0)));
  if (pParam->BSIM3v32pclm > 0.0)
    if (1)
  {
    Vec2m condmask0 = diffVds > 1.0e-10;
    Vec2m condmask_true0 = condmask0;
    {
      T0 = vec2_blend(T0, 1.0 / ((pParam->BSIM3v32pclm * Abulk) * pParam->BSIM3v32litl), condmask_true0);
      dT0_dVb = vec2_blend(dT0_dVb, ((-T0) / Abulk) * dAbulk_dVb, condmask_true0);
      dT0_dVg = vec2_blend(dT0_dVg, ((-T0) / Abulk) * dAbulk_dVg, condmask_true0);
      T2 = vec2_blend(T2, Vgsteff / EsatL, condmask_true0);
      T1 = vec2_blend(T1, Leff * (Abulk + T2), condmask_true0);
      dT1_dVg = vec2_blend(dT1_dVg, Leff * (((1.0 - (T2 * dEsatL_dVg)) / EsatL) + dAbulk_dVg), condmask_true0);
      dT1_dVb = vec2_blend(dT1_dVb, Leff * (dAbulk_dVb - ((T2 * dEsatL_dVb) / EsatL)), condmask_true0);
      dT1_dVd = vec2_blend(dT1_dVd, ((-T2) * dEsatL_dVd) / Esat, condmask_true0);
      T9 = vec2_blend(T9, T0 * T1, condmask_true0);
      VACLM = vec2_blend(VACLM, T9 * diffVds, condmask_true0);
      dVACLM_dVg = vec2_blend(dVACLM_dVg, (((T0 * dT1_dVg) * diffVds) - (T9 * dVdseff_dVg)) + ((T1 * diffVds) * dT0_dVg), condmask_true0);
      dVACLM_dVb = vec2_blend(dVACLM_dVb, (((dT0_dVb * T1) + (T0 * dT1_dVb)) * diffVds) - (T9 * dVdseff_dVb), condmask_true0);
      dVACLM_dVd = vec2_blend(dVACLM_dVd, ((T0 * dT1_dVd) * diffVds) + (T9 * (1.0 - dVdseff_dVd)), condmask_true0);
    }
  }


  if (pParam->BSIM3v32thetaRout > 0.0)
  {
    T8 = Abulk * Vdsat;
    T0 = Vgst2Vtm * T8;
    dT0_dVg = (((Vgst2Vtm * Abulk) * dVdsat_dVg) + T8) + ((Vgst2Vtm * Vdsat) * dAbulk_dVg);
    dT0_dVb = Vgst2Vtm * ((dAbulk_dVb * Vdsat) + (Abulk * dVdsat_dVb));
    dT0_dVd = (Vgst2Vtm * Abulk) * dVdsat_dVd;
    T1 = Vgst2Vtm + T8;
    dT1_dVg = (1.0 + (Abulk * dVdsat_dVg)) + (Vdsat * dAbulk_dVg);
    dT1_dVb = (Abulk * dVdsat_dVb) + (dAbulk_dVb * Vdsat);
    dT1_dVd = Abulk * dVdsat_dVd;
    T9 = T1 * T1;
    T2 = vec2_SIMDTOVECTOR(pParam->BSIM3v32thetaRout);
    VADIBL = (Vgst2Vtm - (T0 / T1)) / T2;
    dVADIBL_dVg = ((1.0 - (dT0_dVg / T1)) + ((T0 * dT1_dVg) / T9)) / T2;
    dVADIBL_dVb = (((-dT0_dVb) / T1) + ((T0 * dT1_dVb) / T9)) / T2;
    dVADIBL_dVd = (((-dT0_dVd) / T1) + ((T0 * dT1_dVd) / T9)) / T2;
    T7 = pParam->BSIM3v32pdiblb * Vbseff;
    if (1)
    {
      Vec2m condmask0 = T7 >= (-0.9);
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        T3 = vec2_blend(T3, 1.0 / (1.0 + T7), condmask_true0);
        VADIBL = vec2_blend(VADIBL, VADIBL * T3, condmask_true0);
        dVADIBL_dVg = vec2_blend(dVADIBL_dVg, dVADIBL_dVg * T3, condmask_true0);
        dVADIBL_dVb = vec2_blend(dVADIBL_dVb, (dVADIBL_dVb - (VADIBL * pParam->BSIM3v32pdiblb)) * T3, condmask_true0);
        dVADIBL_dVd = vec2_blend(dVADIBL_dVd, dVADIBL_dVd * T3, condmask_true0);
      }
      {
        T4 = vec2_blend(T4, 1.0 / (0.8 + T7), condmask_false0);
        T3 = vec2_blend(T3, (17.0 + (20.0 * T7)) * T4, condmask_false0);
        dVADIBL_dVg = vec2_blend(dVADIBL_dVg, dVADIBL_dVg * T3, condmask_false0);
        dVADIBL_dVb = vec2_blend(dVADIBL_dVb, (dVADIBL_dVb * T3) - (((VADIBL * pParam->BSIM3v32pdiblb) * T4) * T4), condmask_false0);
        dVADIBL_dVd = vec2_blend(dVADIBL_dVd, dVADIBL_dVd * T3, condmask_false0);
        VADIBL = vec2_blend(VADIBL, VADIBL * T3, condmask_false0);
      }
    }

  }
  else
  {
    VADIBL = vec2_SIMDTOVECTOR(MAX_EXP);
    dVADIBL_dVd = (dVADIBL_dVg = (dVADIBL_dVb = vec2_SIMDTOVECTOR(0.0)));
  }

  T8 = pParam->BSIM3v32pvag / EsatL;
  T9 = T8 * Vgsteff;
  if (1)
  {
    Vec2m condmask0 = T9 > (-0.9);
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      T0 = vec2_blend(T0, 1.0 + T9, condmask_true0);
      dT0_dVg = vec2_blend(dT0_dVg, T8 * (1.0 - ((Vgsteff * dEsatL_dVg) / EsatL)), condmask_true0);
      dT0_dVb = vec2_blend(dT0_dVb, ((-T9) * dEsatL_dVb) / EsatL, condmask_true0);
      dT0_dVd = vec2_blend(dT0_dVd, ((-T9) * dEsatL_dVd) / EsatL, condmask_true0);
    }
    {
      T1 = vec2_blend(T1, 1.0 / (17.0 + (20.0 * T9)), condmask_false0);
      T0 = vec2_blend(T0, (0.8 + T9) * T1, condmask_false0);
      T1 = vec2_blend(T1, T1 * T1, condmask_false0);
      dT0_dVg = vec2_blend(dT0_dVg, (T8 * (1.0 - ((Vgsteff * dEsatL_dVg) / EsatL))) * T1, condmask_false0);
      T9 = vec2_blend(T9, T9 * (T1 / EsatL), condmask_false0);
      dT0_dVb = vec2_blend(dT0_dVb, (-T9) * dEsatL_dVb, condmask_false0);
      dT0_dVd = vec2_blend(dT0_dVd, (-T9) * dEsatL_dVd, condmask_false0);
    }
  }

  tmp1 = VACLM * VACLM;
  tmp2 = VADIBL * VADIBL;
  tmp3 = VACLM + VADIBL;
  T1 = (VACLM * VADIBL) / tmp3;
  tmp3 *= tmp3;
  dT1_dVg = ((tmp1 * dVADIBL_dVg) + (tmp2 * dVACLM_dVg)) / tmp3;
  dT1_dVd = ((tmp1 * dVADIBL_dVd) + (tmp2 * dVACLM_dVd)) / tmp3;
  dT1_dVb = ((tmp1 * dVADIBL_dVb) + (tmp2 * dVACLM_dVb)) / tmp3;
  Va = Vasat + (T0 * T1);
  dVa_dVg = (dVasat_dVg + (T1 * dT0_dVg)) + (T0 * dT1_dVg);
  dVa_dVd = (dVasat_dVd + (T1 * dT0_dVd)) + (T0 * dT1_dVd);
  dVa_dVb = (dVasat_dVb + (T1 * dT0_dVb)) + (T0 * dT1_dVb);
  dVASCBE_dVg = (dVASCBE_dVd = (dVASCBE_dVb = vec2_SIMDTOVECTOR(0.0)));
  if (pParam->BSIM3v32pscbe2 > 0.0)
  {
    if (1)
    {
      Vec2m condmask0 = diffVds > ((pParam->BSIM3v32pscbe1 * pParam->BSIM3v32litl) / EXP_THRESHOLD);
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        T0 = vec2_blend(T0, (pParam->BSIM3v32pscbe1 * pParam->BSIM3v32litl) / diffVds, condmask_true0);
        VASCBE = vec2_blend(VASCBE, (Leff * vec2_exp(T0)) / pParam->BSIM3v32pscbe2, condmask_true0);
        T1 = vec2_blend(T1, (T0 * VASCBE) / diffVds, condmask_true0);
        dVASCBE_dVg = vec2_blend(dVASCBE_dVg, T1 * dVdseff_dVg, condmask_true0);
        dVASCBE_dVd = vec2_blend(dVASCBE_dVd, (-T1) * (1.0 - dVdseff_dVd), condmask_true0);
        dVASCBE_dVb = vec2_blend(dVASCBE_dVb, T1 * dVdseff_dVb, condmask_true0);
      }
      {
        VASCBE = vec2_blend(VASCBE, vec2_SIMDTOVECTOR((MAX_EXP * Leff) / pParam->BSIM3v32pscbe2), condmask_false0);
      }
    }

  }
  else
  {
    VASCBE = vec2_SIMDTOVECTOR(MAX_EXP);
  }

  CoxWovL = (model->BSIM3v32cox * Weff) / Leff;
  beta = ueff * CoxWovL;
  dbeta_dVg = (CoxWovL * dueff_dVg) + ((beta * dWeff_dVg) / Weff);
  dbeta_dVd = CoxWovL * dueff_dVd;
  dbeta_dVb = (CoxWovL * dueff_dVb) + ((beta * dWeff_dVb) / Weff);
  T0 = 1.0 - (((0.5 * Abulk) * Vdseff) / Vgst2Vtm);
  dT0_dVg = ((-0.5) * (((Abulk * dVdseff_dVg) - ((Abulk * Vdseff) / Vgst2Vtm)) + (Vdseff * dAbulk_dVg))) / Vgst2Vtm;
  dT0_dVd = (((-0.5) * Abulk) * dVdseff_dVd) / Vgst2Vtm;
  dT0_dVb = ((-0.5) * ((Abulk * dVdseff_dVb) + (dAbulk_dVb * Vdseff))) / Vgst2Vtm;
  fgche1 = Vgsteff * T0;
  dfgche1_dVg = (Vgsteff * dT0_dVg) + T0;
  dfgche1_dVd = Vgsteff * dT0_dVd;
  dfgche1_dVb = Vgsteff * dT0_dVb;
  T9 = Vdseff / EsatL;
  fgche2 = 1.0 + T9;
  dfgche2_dVg = (dVdseff_dVg - (T9 * dEsatL_dVg)) / EsatL;
  dfgche2_dVd = (dVdseff_dVd - (T9 * dEsatL_dVd)) / EsatL;
  dfgche2_dVb = (dVdseff_dVb - (T9 * dEsatL_dVb)) / EsatL;
  gche = (beta * fgche1) / fgche2;
  dgche_dVg = (((beta * dfgche1_dVg) + (fgche1 * dbeta_dVg)) - (gche * dfgche2_dVg)) / fgche2;
  dgche_dVd = (((beta * dfgche1_dVd) + (fgche1 * dbeta_dVd)) - (gche * dfgche2_dVd)) / fgche2;
  dgche_dVb = (((beta * dfgche1_dVb) + (fgche1 * dbeta_dVb)) - (gche * dfgche2_dVb)) / fgche2;
  T0 = 1.0 + (gche * Rds);
  T9 = Vdseff / T0;
  Idl = gche * T9;
  dIdl_dVg = (((gche * dVdseff_dVg) + (T9 * dgche_dVg)) / T0) - (((Idl * gche) / T0) * dRds_dVg);
  dIdl_dVd = ((gche * dVdseff_dVd) + (T9 * dgche_dVd)) / T0;
  dIdl_dVb = (((gche * dVdseff_dVb) + (T9 * dgche_dVb)) - ((Idl * dRds_dVb) * gche)) / T0;
  T9 = diffVds / Va;
  T0 = 1.0 + T9;
  Idsa = Idl * T0;
  dIdsa_dVg = (T0 * dIdl_dVg) - ((Idl * (dVdseff_dVg + (T9 * dVa_dVg))) / Va);
  dIdsa_dVd = (T0 * dIdl_dVd) + ((Idl * ((1.0 - dVdseff_dVd) - (T9 * dVa_dVd))) / Va);
  dIdsa_dVb = (T0 * dIdl_dVb) - ((Idl * (dVdseff_dVb + (T9 * dVa_dVb))) / Va);
  T9 = diffVds / VASCBE;
  T0 = 1.0 + T9;
  Ids = Idsa * T0;
  Gm = (T0 * dIdsa_dVg) - ((Idsa * (dVdseff_dVg + (T9 * dVASCBE_dVg))) / VASCBE);
  Gds = (T0 * dIdsa_dVd) + ((Idsa * ((1.0 - dVdseff_dVd) - (T9 * dVASCBE_dVd))) / VASCBE);
  Gmb = (T0 * dIdsa_dVb) - ((Idsa * (dVdseff_dVb + (T9 * dVASCBE_dVb))) / VASCBE);
  Gds += Gm * dVgsteff_dVd;
  Gmb += Gm * dVgsteff_dVb;
  Gm *= dVgsteff_dVg;
  Gmb *= dVbseff_dVb;
  tmpuni = pParam->BSIM3v32alpha0 + (pParam->BSIM3v32alpha1 * Leff);
  if ((tmpuni <= 0.0) || (pParam->BSIM3v32beta0 <= 0.0))
  {
    Isub = (Gbd = (Gbb = (Gbg = vec2_SIMDTOVECTOR(0.0))));
  }
  else
  {
    T2 = vec2_SIMDTOVECTOR(tmpuni / Leff);
    if (1)
    {
      Vec2m condmask0 = diffVds > (pParam->BSIM3v32beta0 / EXP_THRESHOLD);
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        T0 = vec2_blend(T0, (-pParam->BSIM3v32beta0) / diffVds, condmask_true0);
        T1 = vec2_blend(T1, (T2 * diffVds) * vec2_exp(T0), condmask_true0);
        T3 = vec2_blend(T3, (T1 / diffVds) * (T0 - 1.0), condmask_true0);
        dT1_dVg = vec2_blend(dT1_dVg, T3 * dVdseff_dVg, condmask_true0);
        dT1_dVd = vec2_blend(dT1_dVd, T3 * (dVdseff_dVd - 1.0), condmask_true0);
        dT1_dVb = vec2_blend(dT1_dVb, T3 * dVdseff_dVb, condmask_true0);
      }
      {
        T3 = vec2_blend(T3, T2 * MIN_EXP, condmask_false0);
        T1 = vec2_blend(T1, T3 * diffVds, condmask_false0);
        dT1_dVg = vec2_blend(dT1_dVg, (-T3) * dVdseff_dVg, condmask_false0);
        dT1_dVd = vec2_blend(dT1_dVd, T3 * (1.0 - dVdseff_dVd), condmask_false0);
        dT1_dVb = vec2_blend(dT1_dVb, (-T3) * dVdseff_dVb, condmask_false0);
      }
    }

    Isub = T1 * Idsa;
    Gbg = (T1 * dIdsa_dVg) + (Idsa * dT1_dVg);
    Gbd = (T1 * dIdsa_dVd) + (Idsa * dT1_dVd);
    Gbb = (T1 * dIdsa_dVb) + (Idsa * dT1_dVb);
    Gbd += Gbg * dVgsteff_dVd;
    Gbb += Gbg * dVgsteff_dVb;
    Gbg *= dVgsteff_dVg;
    Gbb *= dVbseff_dVb;
  }

  cdrain = Ids;
  {
    heres[0]->BSIM3v32gds = Gds[0];
    heres[1]->BSIM3v32gds = Gds[1];
  }
  {
    heres[0]->BSIM3v32gm = Gm[0];
    heres[1]->BSIM3v32gm = Gm[1];
  }
  {
    heres[0]->BSIM3v32gmbs = Gmb[0];
    heres[1]->BSIM3v32gmbs = Gmb[1];
  }
  {
    heres[0]->BSIM3v32gbbs = Gbb[0];
    heres[1]->BSIM3v32gbbs = Gbb[1];
  }
  {
    heres[0]->BSIM3v32gbgs = Gbg[0];
    heres[1]->BSIM3v32gbgs = Gbg[1];
  }
  {
    heres[0]->BSIM3v32gbds = Gbd[0];
    heres[1]->BSIM3v32gbds = Gbd[1];
  }
  {
    heres[0]->BSIM3v32csub = Isub[0];
    heres[1]->BSIM3v32csub = Isub[1];
  }
  CoxWL = (model->BSIM3v32cox * pParam->BSIM3v32weffCV) * pParam->BSIM3v32leffCV;
  One_Third_CoxWL = CoxWL / 3.0;
  Two_Third_CoxWL = 2.0 * One_Third_CoxWL;
  if ((model->BSIM3v32xpart < 0) | (!ChargeComputationNeeded))
  {
    qgate = vec2_SIMDTOVECTOR(0.0);
    qdrn = vec2_SIMDTOVECTOR(0.0);
    qsrc = vec2_SIMDTOVECTOR(0.0);
    qbulk = vec2_SIMDTOVECTOR(0.0);
    {
      heres[0]->BSIM3v32cggb = 0.0;
      heres[1]->BSIM3v32cggb = 0.0;
    }
    {
      heres[0]->BSIM3v32cgsb = 0.0;
      heres[1]->BSIM3v32cgsb = 0.0;
    }
    {
      heres[0]->BSIM3v32cgdb = 0.0;
      heres[1]->BSIM3v32cgdb = 0.0;
    }
    {
      heres[0]->BSIM3v32cdgb = 0.0;
      heres[1]->BSIM3v32cdgb = 0.0;
    }
    {
      heres[0]->BSIM3v32cdsb = 0.0;
      heres[1]->BSIM3v32cdsb = 0.0;
    }
    {
      heres[0]->BSIM3v32cddb = 0.0;
      heres[1]->BSIM3v32cddb = 0.0;
    }
    {
      heres[0]->BSIM3v32cbgb = 0.0;
      heres[1]->BSIM3v32cbgb = 0.0;
    }
    {
      heres[0]->BSIM3v32cbsb = 0.0;
      heres[1]->BSIM3v32cbsb = 0.0;
    }
    {
      heres[0]->BSIM3v32cbdb = 0.0;
      heres[1]->BSIM3v32cbdb = 0.0;
    }
    {
      heres[0]->BSIM3v32cqdb = 0.0;
      heres[1]->BSIM3v32cqdb = 0.0;
    }
    {
      heres[0]->BSIM3v32cqsb = 0.0;
      heres[1]->BSIM3v32cqsb = 0.0;
    }
    {
      heres[0]->BSIM3v32cqgb = 0.0;
      heres[1]->BSIM3v32cqgb = 0.0;
    }
    {
      heres[0]->BSIM3v32cqbb = 0.0;
      heres[1]->BSIM3v32cqbb = 0.0;
    }
    {
      heres[0]->BSIM3v32gtau = 0.0;
      heres[1]->BSIM3v32gtau = 0.0;
    }
    goto finished;
  }
  else
    if (model->BSIM3v32capMod == 0)
  {
    if (1)
    {
      Vec2m condmask0 = Vbseff < 0.0;
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        Vbseff = vec2_blend(Vbseff, Vbs, condmask_true0);
        dVbseff_dVb = vec2_blend(dVbseff_dVb, vec2_SIMDTOVECTOR(1.0), condmask_true0);
      }
      {
        Vbseff = vec2_blend(Vbseff, pParam->BSIM3v32phi - Phis, condmask_false0);
        dVbseff_dVb = vec2_blend(dVbseff_dVb, -dPhis_dVb, condmask_false0);
      }
    }

    Vfb = vec2_SIMDTOVECTOR(pParam->BSIM3v32vfbcv);
    Vth = (Vfb + pParam->BSIM3v32phi) + (pParam->BSIM3v32k1ox * sqrtPhis);
    Vgst = Vgs_eff - Vth;
    dVth_dVb = pParam->BSIM3v32k1ox * dsqrtPhis_dVb;
    dVgst_dVb = -dVth_dVb;
    dVgst_dVg = dVgs_eff_dVg;
    Arg1 = (Vgs_eff - Vbseff) - Vfb;
    if (1)
    {
      Vec2m condmask0 = Arg1 <= 0.0;
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        qgate = vec2_blend(qgate, CoxWL * Arg1, condmask_true0);
        qbulk = vec2_blend(qbulk, -qgate, condmask_true0);
        qdrn = vec2_blend(qdrn, vec2_SIMDTOVECTOR(0.0), condmask_true0);
        {
          Vec2d val = CoxWL * dVgs_eff_dVg;
          if (condmask_true0[0])
            heres[0]->BSIM3v32cggb = val[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32cggb = val[1];

        }
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32cgdb = 0.0;

          if (condmask_true0[1])
            heres[1]->BSIM3v32cgdb = 0.0;

        }
        {
          Vec2d val = CoxWL * (dVbseff_dVb - dVgs_eff_dVg);
          if (condmask_true0[0])
            heres[0]->BSIM3v32cgsb = val[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32cgsb = val[1];

        }
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32cdgb = 0.0;

          if (condmask_true0[1])
            heres[1]->BSIM3v32cdgb = 0.0;

        }
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32cddb = 0.0;

          if (condmask_true0[1])
            heres[1]->BSIM3v32cddb = 0.0;

        }
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32cdsb = 0.0;

          if (condmask_true0[1])
            heres[1]->BSIM3v32cdsb = 0.0;

        }
        {
          Vec2d val = (-CoxWL) * dVgs_eff_dVg;
          if (condmask_true0[0])
            heres[0]->BSIM3v32cbgb = val[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32cbgb = val[1];

        }
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32cbdb = 0.0;

          if (condmask_true0[1])
            heres[1]->BSIM3v32cbdb = 0.0;

        }
        {
          Vec2d val = -((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb});
          if (condmask_true0[0])
            heres[0]->BSIM3v32cbsb = val[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32cbsb = val[1];

        }
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32qinv = 0.0;

          if (condmask_true0[1])
            heres[1]->BSIM3v32qinv = 0.0;

        }
      }
      if (1)
      {
        Vec2m condmask1 = Vgst <= 0.0;
        Vec2m condmask_true1 = condmask_false0 & condmask1;
        Vec2m condmask_false1 = condmask_false0 & (~condmask1);
        {
          T1 = vec2_blend(T1, vec2_SIMDTOVECTOR(0.5 * pParam->BSIM3v32k1ox), condmask_true1);
          T2 = vec2_blend(T2, vec2_sqrt((T1 * T1) + Arg1), condmask_true1);
          qgate = vec2_blend(qgate, (CoxWL * pParam->BSIM3v32k1ox) * (T2 - T1), condmask_true1);
          qbulk = vec2_blend(qbulk, -qgate, condmask_true1);
          qdrn = vec2_blend(qdrn, vec2_SIMDTOVECTOR(0.0), condmask_true1);
          T0 = vec2_blend(T0, (CoxWL * T1) / T2, condmask_true1);
          {
            Vec2d val = T0 * dVgs_eff_dVg;
            if (condmask_true1[0])
              heres[0]->BSIM3v32cggb = val[0];

            if (condmask_true1[1])
              heres[1]->BSIM3v32cggb = val[1];

          }
          {
            if (condmask_true1[0])
              heres[0]->BSIM3v32cgdb = 0.0;

            if (condmask_true1[1])
              heres[1]->BSIM3v32cgdb = 0.0;

          }
          {
            Vec2d val = T0 * (dVbseff_dVb - dVgs_eff_dVg);
            if (condmask_true1[0])
              heres[0]->BSIM3v32cgsb = val[0];

            if (condmask_true1[1])
              heres[1]->BSIM3v32cgsb = val[1];

          }
          {
            if (condmask_true1[0])
              heres[0]->BSIM3v32cdgb = 0.0;

            if (condmask_true1[1])
              heres[1]->BSIM3v32cdgb = 0.0;

          }
          {
            if (condmask_true1[0])
              heres[0]->BSIM3v32cddb = 0.0;

            if (condmask_true1[1])
              heres[1]->BSIM3v32cddb = 0.0;

          }
          {
            if (condmask_true1[0])
              heres[0]->BSIM3v32cdsb = 0.0;

            if (condmask_true1[1])
              heres[1]->BSIM3v32cdsb = 0.0;

          }
          {
            Vec2d val = -((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb});
            if (condmask_true1[0])
              heres[0]->BSIM3v32cbgb = val[0];

            if (condmask_true1[1])
              heres[1]->BSIM3v32cbgb = val[1];

          }
          {
            if (condmask_true1[0])
              heres[0]->BSIM3v32cbdb = 0.0;

            if (condmask_true1[1])
              heres[1]->BSIM3v32cbdb = 0.0;

          }
          {
            Vec2d val = -((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb});
            if (condmask_true1[0])
              heres[0]->BSIM3v32cbsb = val[0];

            if (condmask_true1[1])
              heres[1]->BSIM3v32cbsb = val[1];

          }
          {
            if (condmask_true1[0])
              heres[0]->BSIM3v32qinv = 0.0;

            if (condmask_true1[1])
              heres[1]->BSIM3v32qinv = 0.0;

          }
        }
        {
          AbulkCV = vec2_blend(AbulkCV, Abulk0 * pParam->BSIM3v32abulkCVfactor, condmask_false1);
          dAbulkCV_dVb = vec2_blend(dAbulkCV_dVb, pParam->BSIM3v32abulkCVfactor * dAbulk0_dVb, condmask_false1);
          Vdsat = vec2_blend(Vdsat, Vgst / AbulkCV, condmask_false1);
          dVdsat_dVg = vec2_blend(dVdsat_dVg, dVgs_eff_dVg / AbulkCV, condmask_false1);
          dVdsat_dVb = vec2_blend(dVdsat_dVb, (-((Vdsat * dAbulkCV_dVb) + dVth_dVb)) / AbulkCV, condmask_false1);
          if (model->BSIM3v32xpart > 0.5)
          {
            if (1)
            {
              Vec2m condmask2 = Vdsat <= Vds;
              Vec2m condmask_true2 = condmask_false1 & condmask2;
              Vec2m condmask_false2 = condmask_false1 & (~condmask2);
              {
                T1 = vec2_blend(T1, Vdsat / 3.0, condmask_true2);
                qgate = vec2_blend(qgate, CoxWL * (((Vgs_eff - Vfb) - pParam->BSIM3v32phi) - T1), condmask_true2);
                T2 = vec2_blend(T2, (-Two_Third_CoxWL) * Vgst, condmask_true2);
                qbulk = vec2_blend(qbulk, -(qgate + T2), condmask_true2);
                qdrn = vec2_blend(qdrn, vec2_SIMDTOVECTOR(0.0), condmask_true2);
                {
                  Vec2d val = (One_Third_CoxWL * (3.0 - dVdsat_dVg)) * dVgs_eff_dVg;
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cggb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cggb = val[1];

                }
                T2 = vec2_blend(T2, (-One_Third_CoxWL) * dVdsat_dVb, condmask_true2);
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + T2);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cgsb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cgsb = val[1];

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cgdb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cgdb = 0.0;

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cdgb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cdgb = 0.0;

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cddb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cddb = 0.0;

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cdsb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cdsb = 0.0;

                }
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) - (Two_Third_CoxWL * dVgs_eff_dVg));
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbgb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbgb = val[1];

                }
                T3 = vec2_blend(T3, -(T2 + (Two_Third_CoxWL * dVth_dVb)), condmask_true2);
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb}) + T3);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbsb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbsb = val[1];

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbdb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbdb = 0.0;

                }
                {
                  Vec2d val = -(qgate + qbulk);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32qinv = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32qinv = val[1];

                }
              }
              {
                Alphaz = vec2_blend(Alphaz, Vgst / Vdsat, condmask_false2);
                T1 = vec2_blend(T1, (2.0 * Vdsat) - Vds, condmask_false2);
                T2 = vec2_blend(T2, Vds / (3.0 * T1), condmask_false2);
                T3 = vec2_blend(T3, T2 * Vds, condmask_false2);
                T9 = vec2_blend(T9, vec2_SIMDTOVECTOR(0.25 * CoxWL), condmask_false2);
                T4 = vec2_blend(T4, T9 * Alphaz, condmask_false2);
                T7 = vec2_blend(T7, ((2.0 * Vds) - T1) - (3.0 * T3), condmask_false2);
                T8 = vec2_blend(T8, (T3 - T1) - (2.0 * Vds), condmask_false2);
                qgate = vec2_blend(qgate, CoxWL * (((Vgs_eff - Vfb) - pParam->BSIM3v32phi) - (0.5 * (Vds - T3))), condmask_false2);
                T10 = vec2_blend(T10, T4 * T8, condmask_false2);
                qdrn = vec2_blend(qdrn, T4 * T7, condmask_false2);
                qbulk = vec2_blend(qbulk, -((qgate + qdrn) + T10), condmask_false2);
                T5 = vec2_blend(T5, T3 / T1, condmask_false2);
                {
                  Vec2d val = (CoxWL * (1.0 - (T5 * dVdsat_dVg))) * dVgs_eff_dVg;
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cggb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cggb = val[1];

                }
                T11 = vec2_blend(T11, ((-CoxWL) * T5) * dVdsat_dVb, condmask_false2);
                {
                  Vec2d val = CoxWL * ((T2 - 0.5) + (0.5 * T5));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cgdb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cgdb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + T11) + ((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cgsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cgsb = val[1];

                }
                T6 = vec2_blend(T6, 1.0 / Vdsat, condmask_false2);
                dAlphaz_dVg = vec2_blend(dAlphaz_dVg, T6 * (1.0 - (Alphaz * dVdsat_dVg)), condmask_false2);
                dAlphaz_dVb = vec2_blend(dAlphaz_dVb, (-T6) * (dVth_dVb + (Alphaz * dVdsat_dVb)), condmask_false2);
                T7 = vec2_blend(T7, T9 * T7, condmask_false2);
                T8 = vec2_blend(T8, T9 * T8, condmask_false2);
                T9 = vec2_blend(T9, (2.0 * T4) * (1.0 - (3.0 * T5)), condmask_false2);
                {
                  Vec2d val = ((T7 * dAlphaz_dVg) - (T9 * dVdsat_dVg)) * dVgs_eff_dVg;
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cdgb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cdgb = val[1];

                }
                T12 = vec2_blend(T12, (T7 * dAlphaz_dVb) - (T9 * dVdsat_dVb), condmask_false2);
                {
                  Vec2d val = T4 * ((3.0 - (6.0 * T2)) - (3.0 * T5));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cddb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cddb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}) + T12) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cdsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cdsb = val[1];

                }
                T9 = vec2_blend(T9, (2.0 * T4) * (1.0 + T5), condmask_false2);
                T10 = vec2_blend(T10, ((T8 * dAlphaz_dVg) - (T9 * dVdsat_dVg)) * dVgs_eff_dVg, condmask_false2);
                T11 = vec2_blend(T11, (T8 * dAlphaz_dVb) - (T9 * dVdsat_dVb), condmask_false2);
                T12 = vec2_blend(T12, T4 * (((2.0 * T2) + T5) - 1.0), condmask_false2);
                T0 = vec2_blend(T0, -((T10 + T11) + T12), condmask_false2);
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb})) + T10);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbgb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbgb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb})) + T12);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbdb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbdb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) + ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb})) + T0);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbsb = val[1];

                }
                {
                  Vec2d val = -(qgate + qbulk);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32qinv = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32qinv = val[1];

                }
              }
            }

          }
          else
            if (model->BSIM3v32xpart < 0.5)
          {
            if (1)
            {
              Vec2m condmask2 = Vds >= Vdsat;
              Vec2m condmask_true2 = condmask_false1 & condmask2;
              Vec2m condmask_false2 = condmask_false1 & (~condmask2);
              {
                T1 = vec2_blend(T1, Vdsat / 3.0, condmask_true2);
                qgate = vec2_blend(qgate, CoxWL * (((Vgs_eff - Vfb) - pParam->BSIM3v32phi) - T1), condmask_true2);
                T2 = vec2_blend(T2, (-Two_Third_CoxWL) * Vgst, condmask_true2);
                qbulk = vec2_blend(qbulk, -(qgate + T2), condmask_true2);
                qdrn = vec2_blend(qdrn, 0.4 * T2, condmask_true2);
                {
                  Vec2d val = (One_Third_CoxWL * (3.0 - dVdsat_dVg)) * dVgs_eff_dVg;
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cggb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cggb = val[1];

                }
                T2 = vec2_blend(T2, (-One_Third_CoxWL) * dVdsat_dVb, condmask_true2);
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + T2);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cgsb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cgsb = val[1];

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cgdb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cgdb = 0.0;

                }
                T3 = vec2_blend(T3, vec2_SIMDTOVECTOR(0.4 * Two_Third_CoxWL), condmask_true2);
                {
                  Vec2d val = (-T3) * dVgs_eff_dVg;
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cdgb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cdgb = val[1];

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cddb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cddb = 0.0;

                }
                T4 = vec2_blend(T4, T3 * dVth_dVb, condmask_true2);
                {
                  Vec2d val = -(T4 + ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}));
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cdsb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cdsb = val[1];

                }
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) - (Two_Third_CoxWL * dVgs_eff_dVg));
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbgb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbgb = val[1];

                }
                T3 = vec2_blend(T3, -(T2 + (Two_Third_CoxWL * dVth_dVb)), condmask_true2);
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb}) + T3);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbsb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbsb = val[1];

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbdb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbdb = 0.0;

                }
                {
                  Vec2d val = -(qgate + qbulk);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32qinv = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32qinv = val[1];

                }
              }
              {
                Alphaz = vec2_blend(Alphaz, Vgst / Vdsat, condmask_false2);
                T1 = vec2_blend(T1, (2.0 * Vdsat) - Vds, condmask_false2);
                T2 = vec2_blend(T2, Vds / (3.0 * T1), condmask_false2);
                T3 = vec2_blend(T3, T2 * Vds, condmask_false2);
                T9 = vec2_blend(T9, vec2_SIMDTOVECTOR(0.25 * CoxWL), condmask_false2);
                T4 = vec2_blend(T4, T9 * Alphaz, condmask_false2);
                qgate = vec2_blend(qgate, CoxWL * (((Vgs_eff - Vfb) - pParam->BSIM3v32phi) - (0.5 * (Vds - T3))), condmask_false2);
                T5 = vec2_blend(T5, T3 / T1, condmask_false2);
                {
                  Vec2d val = (CoxWL * (1.0 - (T5 * dVdsat_dVg))) * dVgs_eff_dVg;
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cggb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cggb = val[1];

                }
                tmp = vec2_blend(tmp, ((-CoxWL) * T5) * dVdsat_dVb, condmask_false2);
                {
                  Vec2d val = CoxWL * ((T2 - 0.5) + (0.5 * T5));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cgdb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cgdb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb})) + tmp);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cgsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cgsb = val[1];

                }
                T6 = vec2_blend(T6, 1.0 / Vdsat, condmask_false2);
                dAlphaz_dVg = vec2_blend(dAlphaz_dVg, T6 * (1.0 - (Alphaz * dVdsat_dVg)), condmask_false2);
                dAlphaz_dVb = vec2_blend(dAlphaz_dVb, (-T6) * (dVth_dVb + (Alphaz * dVdsat_dVb)), condmask_false2);
                T6 = vec2_blend(T6, (((8.0 * Vdsat) * Vdsat) - ((6.0 * Vdsat) * Vds)) + ((1.2 * Vds) * Vds), condmask_false2);
                T8 = vec2_blend(T8, T2 / T1, condmask_false2);
                T7 = vec2_blend(T7, (Vds - T1) - (T8 * T6), condmask_false2);
                qdrn = vec2_blend(qdrn, T4 * T7, condmask_false2);
                T7 = vec2_blend(T7, T7 * T9, condmask_false2);
                tmp = vec2_blend(tmp, T8 / T1, condmask_false2);
                tmp1 = vec2_blend(tmp1, T4 * ((2.0 - ((4.0 * tmp) * T6)) + (T8 * ((16.0 * Vdsat) - (6.0 * Vds)))), condmask_false2);
                {
                  Vec2d val = ((T7 * dAlphaz_dVg) - (tmp1 * dVdsat_dVg)) * dVgs_eff_dVg;
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cdgb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cdgb = val[1];

                }
                T10 = vec2_blend(T10, (T7 * dAlphaz_dVb) - (tmp1 * dVdsat_dVb), condmask_false2);
                {
                  Vec2d val = T4 * ((2.0 - (((1.0 / ((3.0 * T1) * T1)) + (2.0 * tmp)) * T6)) + (T8 * ((6.0 * Vdsat) - (2.4 * Vds))));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cddb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cddb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}) + T10) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cdsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cdsb = val[1];

                }
                T7 = vec2_blend(T7, 2.0 * (T1 + T3), condmask_false2);
                qbulk = vec2_blend(qbulk, -(qgate - (T4 * T7)), condmask_false2);
                T7 = vec2_blend(T7, T7 * T9, condmask_false2);
                T0 = vec2_blend(T0, (4.0 * T4) * (1.0 - T5), condmask_false2);
                T12 = vec2_blend(T12, ((((-T7) * dAlphaz_dVg) - ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb})) - (T0 * dVdsat_dVg)) * dVgs_eff_dVg, condmask_false2);
                T11 = vec2_blend(T11, (((-T7) * dAlphaz_dVb) - T10) - (T0 * dVdsat_dVb), condmask_false2);
                T10 = vec2_blend(T10, (((-4.0) * T4) * ((T2 - 0.5) + (0.5 * T5))) - ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}), condmask_false2);
                tmp = vec2_blend(tmp, -((T10 + T11) + T12), condmask_false2);
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb})) + T12);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbgb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbgb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb})) + T10);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbdb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbdb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) + ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb})) + tmp);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbsb = val[1];

                }
                {
                  Vec2d val = -(qgate + qbulk);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32qinv = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32qinv = val[1];

                }
              }
            }

          }
          else
          {
            if (1)
            {
              Vec2m condmask2 = Vds >= Vdsat;
              Vec2m condmask_true2 = condmask_false1 & condmask2;
              Vec2m condmask_false2 = condmask_false1 & (~condmask2);
              {
                T1 = vec2_blend(T1, Vdsat / 3.0, condmask_true2);
                qgate = vec2_blend(qgate, CoxWL * (((Vgs_eff - Vfb) - pParam->BSIM3v32phi) - T1), condmask_true2);
                T2 = vec2_blend(T2, (-Two_Third_CoxWL) * Vgst, condmask_true2);
                qbulk = vec2_blend(qbulk, -(qgate + T2), condmask_true2);
                qdrn = vec2_blend(qdrn, 0.5 * T2, condmask_true2);
                {
                  Vec2d val = (One_Third_CoxWL * (3.0 - dVdsat_dVg)) * dVgs_eff_dVg;
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cggb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cggb = val[1];

                }
                T2 = vec2_blend(T2, (-One_Third_CoxWL) * dVdsat_dVb, condmask_true2);
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + T2);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cgsb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cgsb = val[1];

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cgdb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cgdb = 0.0;

                }
                {
                  Vec2d val = (-One_Third_CoxWL) * dVgs_eff_dVg;
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cdgb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cdgb = val[1];

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cddb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cddb = 0.0;

                }
                T4 = vec2_blend(T4, One_Third_CoxWL * dVth_dVb, condmask_true2);
                {
                  Vec2d val = -(T4 + ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}));
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cdsb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cdsb = val[1];

                }
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) - (Two_Third_CoxWL * dVgs_eff_dVg));
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbgb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbgb = val[1];

                }
                T3 = vec2_blend(T3, -(T2 + (Two_Third_CoxWL * dVth_dVb)), condmask_true2);
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb}) + T3);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbsb = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbsb = val[1];

                }
                {
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32cbdb = 0.0;

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32cbdb = 0.0;

                }
                {
                  Vec2d val = -(qgate + qbulk);
                  if (condmask_true2[0])
                    heres[0]->BSIM3v32qinv = val[0];

                  if (condmask_true2[1])
                    heres[1]->BSIM3v32qinv = val[1];

                }
              }
              {
                Alphaz = vec2_blend(Alphaz, Vgst / Vdsat, condmask_false2);
                T1 = vec2_blend(T1, (2.0 * Vdsat) - Vds, condmask_false2);
                T2 = vec2_blend(T2, Vds / (3.0 * T1), condmask_false2);
                T3 = vec2_blend(T3, T2 * Vds, condmask_false2);
                T9 = vec2_blend(T9, vec2_SIMDTOVECTOR(0.25 * CoxWL), condmask_false2);
                T4 = vec2_blend(T4, T9 * Alphaz, condmask_false2);
                qgate = vec2_blend(qgate, CoxWL * (((Vgs_eff - Vfb) - pParam->BSIM3v32phi) - (0.5 * (Vds - T3))), condmask_false2);
                T5 = vec2_blend(T5, T3 / T1, condmask_false2);
                {
                  Vec2d val = (CoxWL * (1.0 - (T5 * dVdsat_dVg))) * dVgs_eff_dVg;
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cggb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cggb = val[1];

                }
                tmp = vec2_blend(tmp, ((-CoxWL) * T5) * dVdsat_dVb, condmask_false2);
                {
                  Vec2d val = CoxWL * ((T2 - 0.5) + (0.5 * T5));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cgdb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cgdb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb})) + tmp);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cgsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cgsb = val[1];

                }
                T6 = vec2_blend(T6, 1.0 / Vdsat, condmask_false2);
                dAlphaz_dVg = vec2_blend(dAlphaz_dVg, T6 * (1.0 - (Alphaz * dVdsat_dVg)), condmask_false2);
                dAlphaz_dVb = vec2_blend(dAlphaz_dVb, (-T6) * (dVth_dVb + (Alphaz * dVdsat_dVb)), condmask_false2);
                T7 = vec2_blend(T7, T1 + T3, condmask_false2);
                qdrn = vec2_blend(qdrn, (-T4) * T7, condmask_false2);
                qbulk = vec2_blend(qbulk, -((qgate + qdrn) + qdrn), condmask_false2);
                T7 = vec2_blend(T7, T7 * T9, condmask_false2);
                T0 = vec2_blend(T0, T4 * ((2.0 * T5) - 2.0), condmask_false2);
                {
                  Vec2d val = ((T0 * dVdsat_dVg) - (T7 * dAlphaz_dVg)) * dVgs_eff_dVg;
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cdgb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cdgb = val[1];

                }
                T12 = vec2_blend(T12, (T0 * dVdsat_dVb) - (T7 * dAlphaz_dVb), condmask_false2);
                {
                  Vec2d val = T4 * ((1.0 - (2.0 * T2)) - T5);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cddb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cddb = val[1];

                }
                {
                  Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}) + T12) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cdsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cdsb = val[1];

                }
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + (2.0 * ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb})));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbgb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbgb = val[1];

                }
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) + (2.0 * ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb})));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbdb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbdb = val[1];

                }
                {
                  Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) + (2.0 * ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb})));
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32cbsb = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32cbsb = val[1];

                }
                {
                  Vec2d val = -(qgate + qbulk);
                  if (condmask_false2[0])
                    heres[0]->BSIM3v32qinv = val[0];

                  if (condmask_false2[1])
                    heres[1]->BSIM3v32qinv = val[1];

                }
              }
            }

          }


        }
      }

    }

  }
  else
  {
    if (1)
    {
      Vec2m condmask0 = Vbseff < 0.0;
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        VbseffCV = vec2_blend(VbseffCV, Vbseff, condmask_true0);
        dVbseffCV_dVb = vec2_blend(dVbseffCV_dVb, vec2_SIMDTOVECTOR(1.0), condmask_true0);
      }
      {
        VbseffCV = vec2_blend(VbseffCV, pParam->BSIM3v32phi - Phis, condmask_false0);
        dVbseffCV_dVb = vec2_blend(dVbseffCV_dVb, -dPhis_dVb, condmask_false0);
      }
    }

    noff = n * pParam->BSIM3v32noff;
    dnoff_dVd = pParam->BSIM3v32noff * dn_dVd;
    dnoff_dVb = pParam->BSIM3v32noff * dn_dVb;
    T0 = Vtm * noff;
    voffcv = pParam->BSIM3v32voffcv;
    VgstNVt = (Vgst - voffcv) / T0;
    if (1)
    {
      Vec2m condmask0 = VgstNVt > EXP_THRESHOLD;
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        Vgsteff = vec2_blend(Vgsteff, Vgst - voffcv, condmask_true0);
        dVgsteff_dVg = vec2_blend(dVgsteff_dVg, dVgs_eff_dVg, condmask_true0);
        dVgsteff_dVd = vec2_blend(dVgsteff_dVd, -dVth_dVd, condmask_true0);
        dVgsteff_dVb = vec2_blend(dVgsteff_dVb, -dVth_dVb, condmask_true0);
      }
      if (1)
      {
        Vec2m condmask1 = VgstNVt < (-EXP_THRESHOLD);
        Vec2m condmask_true1 = condmask_false0 & condmask1;
        Vec2m condmask_false1 = condmask_false0 & (~condmask1);
        {
          Vgsteff = vec2_blend(Vgsteff, T0 * log(1.0 + MIN_EXP), condmask_true1);
          dVgsteff_dVg = vec2_blend(dVgsteff_dVg, vec2_SIMDTOVECTOR(0.0), condmask_true1);
          dVgsteff_dVd = vec2_blend(dVgsteff_dVd, Vgsteff / noff, condmask_true1);
          dVgsteff_dVb = vec2_blend(dVgsteff_dVb, dVgsteff_dVd * dnoff_dVb, condmask_true1);
          dVgsteff_dVd = vec2_blend(dVgsteff_dVd, dVgsteff_dVd * dnoff_dVd, condmask_true1);
        }
        {
          ExpVgst = vec2_blend(ExpVgst, vec2_exp(VgstNVt), condmask_false1);
          Vgsteff = vec2_blend(Vgsteff, T0 * vec2_log(1.0 + ExpVgst), condmask_false1);
          dVgsteff_dVg = vec2_blend(dVgsteff_dVg, ExpVgst / (1.0 + ExpVgst), condmask_false1);
          dVgsteff_dVd = vec2_blend(dVgsteff_dVd, ((-dVgsteff_dVg) * (dVth_dVd + (((Vgst - voffcv) / noff) * dnoff_dVd))) + ((Vgsteff / noff) * dnoff_dVd), condmask_false1);
          dVgsteff_dVb = vec2_blend(dVgsteff_dVb, ((-dVgsteff_dVg) * (dVth_dVb + (((Vgst - voffcv) / noff) * dnoff_dVb))) + ((Vgsteff / noff) * dnoff_dVb), condmask_false1);
          dVgsteff_dVg = vec2_blend(dVgsteff_dVg, dVgsteff_dVg * dVgs_eff_dVg, condmask_false1);
        }
      }

    }

    if (model->BSIM3v32capMod == 1)
    {
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          Vfb = (Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb};
          break;

        case BSIM3v32V32:
          Vfb = (Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb};
          dVfb_dVb = (dVfb_dVd = vec2_SIMDTOVECTOR(0.0));
          break;

        default:
          Vfb = (Vth - pParam->BSIM3v32phi) - (pParam->BSIM3v32k1ox * sqrtPhis);
          dVfb_dVb = dVth_dVb - (pParam->BSIM3v32k1ox * dsqrtPhis_dVb);
          dVfb_dVd = dVth_dVd;

      }

      Arg1 = ((Vgs_eff - VbseffCV) - Vfb) - Vgsteff;
      if (1)
      {
        Vec2m condmask0 = Arg1 <= 0.0;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          qgate = vec2_blend(qgate, CoxWL * Arg1, condmask_true0);
          Cgg = vec2_blend(Cgg, CoxWL * (dVgs_eff_dVg - dVgsteff_dVg), condmask_true0);
          switch (model->BSIM3v32intVersion)
          {
            case BSIM3v32V324:

            case BSIM3v32V323:

            case BSIM3v32V322:
              Cgd = vec2_blend(Cgd, (-CoxWL) * dVgsteff_dVd, condmask_true0);
              Cgb = vec2_blend(Cgb, (-CoxWL) * (dVbseffCV_dVb + dVgsteff_dVb), condmask_true0);
              break;

            case BSIM3v32V32:

            default:
              Cgd = vec2_blend(Cgd, (-CoxWL) * (dVfb_dVd + dVgsteff_dVd), condmask_true0);
              Cgb = vec2_blend(Cgb, (-CoxWL) * ((dVfb_dVb + dVbseffCV_dVb) + dVgsteff_dVb), condmask_true0);

          }

        }
        {
          T0 = vec2_blend(T0, vec2_SIMDTOVECTOR(0.5 * pParam->BSIM3v32k1ox), condmask_false0);
          T1 = vec2_blend(T1, vec2_sqrt((T0 * T0) + Arg1), condmask_false0);
          T2 = vec2_blend(T2, (CoxWL * T0) / T1, condmask_false0);
          qgate = vec2_blend(qgate, (CoxWL * pParam->BSIM3v32k1ox) * (T1 - T0), condmask_false0);
          Cgg = vec2_blend(Cgg, T2 * (dVgs_eff_dVg - dVgsteff_dVg), condmask_false0);
          switch (model->BSIM3v32intVersion)
          {
            case BSIM3v32V324:

            case BSIM3v32V323:

            case BSIM3v32V322:
              Cgd = vec2_blend(Cgd, (-T2) * dVgsteff_dVd, condmask_false0);
              Cgb = vec2_blend(Cgb, (-T2) * (dVbseffCV_dVb + dVgsteff_dVb), condmask_false0);
              break;

            case BSIM3v32V32:

            default:
              Cgd = vec2_blend(Cgd, (-T2) * (dVfb_dVd + dVgsteff_dVd), condmask_false0);
              Cgb = vec2_blend(Cgb, (-T2) * ((dVfb_dVb + dVbseffCV_dVb) + dVgsteff_dVb), condmask_false0);

          }

        }
      }

      qbulk = -qgate;
      Cbg = -Cgg;
      Cbd = -Cgd;
      Cbb = -Cgb;
      One_Third_CoxWL = CoxWL / 3.0;
      Two_Third_CoxWL = 2.0 * One_Third_CoxWL;
      AbulkCV = Abulk0 * pParam->BSIM3v32abulkCVfactor;
      dAbulkCV_dVb = pParam->BSIM3v32abulkCVfactor * dAbulk0_dVb;
      VdsatCV = Vgsteff / AbulkCV;
      if (1)
      {
        Vec2m condmask0 = VdsatCV < Vds;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          dVdsatCV_dVg = vec2_blend(dVdsatCV_dVg, 1.0 / AbulkCV, condmask_true0);
          dVdsatCV_dVb = vec2_blend(dVdsatCV_dVb, ((-VdsatCV) * dAbulkCV_dVb) / AbulkCV, condmask_true0);
          T0 = vec2_blend(T0, Vgsteff - (VdsatCV / 3.0), condmask_true0);
          dT0_dVg = vec2_blend(dT0_dVg, 1.0 - (dVdsatCV_dVg / 3.0), condmask_true0);
          dT0_dVb = vec2_blend(dT0_dVb, (-dVdsatCV_dVb) / 3.0, condmask_true0);
          qgate = vec2_blend(qgate, qgate + (CoxWL * T0), condmask_true0);
          Cgg1 = vec2_blend(Cgg1, CoxWL * dT0_dVg, condmask_true0);
          Cgb1 = vec2_blend(Cgb1, (CoxWL * dT0_dVb) + (Cgg1 * dVgsteff_dVb), condmask_true0);
          Cgd1 = vec2_blend(Cgd1, Cgg1 * dVgsteff_dVd, condmask_true0);
          Cgg1 = vec2_blend(Cgg1, Cgg1 * dVgsteff_dVg, condmask_true0);
          Cgg = vec2_blend(Cgg, Cgg + Cgg1, condmask_true0);
          Cgb = vec2_blend(Cgb, Cgb + Cgb1, condmask_true0);
          Cgd = vec2_blend(Cgd, Cgd + Cgd1, condmask_true0);
          T0 = vec2_blend(T0, VdsatCV - Vgsteff, condmask_true0);
          dT0_dVg = vec2_blend(dT0_dVg, dVdsatCV_dVg - 1.0, condmask_true0);
          dT0_dVb = vec2_blend(dT0_dVb, dVdsatCV_dVb, condmask_true0);
          qbulk = vec2_blend(qbulk, qbulk + (One_Third_CoxWL * T0), condmask_true0);
          Cbg1 = vec2_blend(Cbg1, One_Third_CoxWL * dT0_dVg, condmask_true0);
          Cbb1 = vec2_blend(Cbb1, (One_Third_CoxWL * dT0_dVb) + (Cbg1 * dVgsteff_dVb), condmask_true0);
          Cbd1 = vec2_blend(Cbd1, Cbg1 * dVgsteff_dVd, condmask_true0);
          Cbg1 = vec2_blend(Cbg1, Cbg1 * dVgsteff_dVg, condmask_true0);
          Cbg = vec2_blend(Cbg, Cbg + Cbg1, condmask_true0);
          Cbb = vec2_blend(Cbb, Cbb + Cbb1, condmask_true0);
          Cbd = vec2_blend(Cbd, Cbd + Cbd1, condmask_true0);
          if (model->BSIM3v32xpart > 0.5)
            T0 = vec2_blend(T0, vec2_SIMDTOVECTOR(-Two_Third_CoxWL), condmask_true0);
          else
            if (model->BSIM3v32xpart < 0.5)
            T0 = vec2_blend(T0, vec2_SIMDTOVECTOR((-0.4) * CoxWL), condmask_true0);
          else
            T0 = vec2_blend(T0, vec2_SIMDTOVECTOR(-One_Third_CoxWL), condmask_true0);


          qsrc = vec2_blend(qsrc, T0 * Vgsteff, condmask_true0);
          Csg = vec2_blend(Csg, T0 * dVgsteff_dVg, condmask_true0);
          Csb = vec2_blend(Csb, T0 * dVgsteff_dVb, condmask_true0);
          Csd = vec2_blend(Csd, T0 * dVgsteff_dVd, condmask_true0);
          Cgb = vec2_blend(Cgb, Cgb * dVbseff_dVb, condmask_true0);
          Cbb = vec2_blend(Cbb, Cbb * dVbseff_dVb, condmask_true0);
          Csb = vec2_blend(Csb, Csb * dVbseff_dVb, condmask_true0);
        }
        {
          T0 = vec2_blend(T0, AbulkCV * Vds, condmask_false0);
          T1 = vec2_blend(T1, 12.0 * ((Vgsteff - (0.5 * T0)) + 1.e-20), condmask_false0);
          T2 = vec2_blend(T2, Vds / T1, condmask_false0);
          T3 = vec2_blend(T3, T0 * T2, condmask_false0);
          dT3_dVg = vec2_blend(dT3_dVg, (((-12.0) * T2) * T2) * AbulkCV, condmask_false0);
          dT3_dVd = vec2_blend(dT3_dVd, ((((6.0 * T0) * ((4.0 * Vgsteff) - T0)) / T1) / T1) - 0.5, condmask_false0);
          dT3_dVb = vec2_blend(dT3_dVb, (((12.0 * T2) * T2) * dAbulkCV_dVb) * Vgsteff, condmask_false0);
          qgate = vec2_blend(qgate, qgate + (CoxWL * ((Vgsteff - (0.5 * Vds)) + T3)), condmask_false0);
          Cgg1 = vec2_blend(Cgg1, CoxWL * (1.0 + dT3_dVg), condmask_false0);
          Cgb1 = vec2_blend(Cgb1, (CoxWL * dT3_dVb) + (Cgg1 * dVgsteff_dVb), condmask_false0);
          Cgd1 = vec2_blend(Cgd1, (CoxWL * dT3_dVd) + (Cgg1 * dVgsteff_dVd), condmask_false0);
          Cgg1 = vec2_blend(Cgg1, Cgg1 * dVgsteff_dVg, condmask_false0);
          Cgg = vec2_blend(Cgg, Cgg + Cgg1, condmask_false0);
          Cgb = vec2_blend(Cgb, Cgb + Cgb1, condmask_false0);
          Cgd = vec2_blend(Cgd, Cgd + Cgd1, condmask_false0);
          qbulk = vec2_blend(qbulk, qbulk + ((CoxWL * (1.0 - AbulkCV)) * ((0.5 * Vds) - T3)), condmask_false0);
          Cbg1 = vec2_blend(Cbg1, (-CoxWL) * ((1.0 - AbulkCV) * dT3_dVg), condmask_false0);
          Cbb1 = vec2_blend(Cbb1, ((-CoxWL) * (((1.0 - AbulkCV) * dT3_dVb) + (((0.5 * Vds) - T3) * dAbulkCV_dVb))) + (Cbg1 * dVgsteff_dVb), condmask_false0);
          Cbd1 = vec2_blend(Cbd1, (((-CoxWL) * (1.0 - AbulkCV)) * dT3_dVd) + (Cbg1 * dVgsteff_dVd), condmask_false0);
          Cbg1 = vec2_blend(Cbg1, Cbg1 * dVgsteff_dVg, condmask_false0);
          Cbg = vec2_blend(Cbg, Cbg + Cbg1, condmask_false0);
          Cbb = vec2_blend(Cbb, Cbb + Cbb1, condmask_false0);
          Cbd = vec2_blend(Cbd, Cbd + Cbd1, condmask_false0);
          if (model->BSIM3v32xpart > 0.5)
          {
            T1 = vec2_blend(T1, T1 + T1, condmask_false0);
            qsrc = vec2_blend(qsrc, (-CoxWL) * (((0.5 * Vgsteff) + (0.25 * T0)) - ((T0 * T0) / T1)), condmask_false0);
            Csg = vec2_blend(Csg, (-CoxWL) * (0.5 + (((((24.0 * T0) * Vds) / T1) / T1) * AbulkCV)), condmask_false0);
            Csb = vec2_blend(Csb, ((-CoxWL) * (((0.25 * Vds) * dAbulkCV_dVb) - ((((((12.0 * T0) * Vds) / T1) / T1) * ((4.0 * Vgsteff) - T0)) * dAbulkCV_dVb))) + (Csg * dVgsteff_dVb), condmask_false0);
            Csd = vec2_blend(Csd, ((-CoxWL) * ((0.25 * AbulkCV) - (((((12.0 * AbulkCV) * T0) / T1) / T1) * ((4.0 * Vgsteff) - T0)))) + (Csg * dVgsteff_dVd), condmask_false0);
            Csg = vec2_blend(Csg, Csg * dVgsteff_dVg, condmask_false0);
          }
          else
            if (model->BSIM3v32xpart < 0.5)
          {
            T1 = vec2_blend(T1, T1 / 12.0, condmask_false0);
            T2 = vec2_blend(T2, (0.5 * CoxWL) / (T1 * T1), condmask_false0);
            T3 = vec2_blend(T3, (Vgsteff * ((((2.0 * T0) * T0) / 3.0) + (Vgsteff * (Vgsteff - ((4.0 * T0) / 3.0))))) - ((((2.0 * T0) * T0) * T0) / 15.0), condmask_false0);
            qsrc = vec2_blend(qsrc, (-T2) * T3, condmask_false0);
            T4 = vec2_blend(T4, (((4.0 / 3.0) * Vgsteff) * (Vgsteff - T0)) + ((0.4 * T0) * T0), condmask_false0);
            Csg = vec2_blend(Csg, (((-2.0) * qsrc) / T1) - (T2 * ((Vgsteff * ((3.0 * Vgsteff) - ((8.0 * T0) / 3.0))) + (((2.0 * T0) * T0) / 3.0))), condmask_false0);
            Csb = vec2_blend(Csb, ((((qsrc / T1) * Vds) + ((T2 * T4) * Vds)) * dAbulkCV_dVb) + (Csg * dVgsteff_dVb), condmask_false0);
            Csd = vec2_blend(Csd, (((qsrc / T1) + (T2 * T4)) * AbulkCV) + (Csg * dVgsteff_dVd), condmask_false0);
            Csg = vec2_blend(Csg, Csg * dVgsteff_dVg, condmask_false0);
          }
          else
          {
            qsrc = vec2_blend(qsrc, (-0.5) * (qgate + qbulk), condmask_false0);
            Csg = vec2_blend(Csg, (-0.5) * (Cgg1 + Cbg1), condmask_false0);
            Csb = vec2_blend(Csb, (-0.5) * (Cgb1 + Cbb1), condmask_false0);
            Csd = vec2_blend(Csd, (-0.5) * (Cgd1 + Cbd1), condmask_false0);
          }


          Cgb = vec2_blend(Cgb, Cgb * dVbseff_dVb, condmask_false0);
          Cbb = vec2_blend(Cbb, Cbb * dVbseff_dVb, condmask_false0);
          Csb = vec2_blend(Csb, Csb * dVbseff_dVb, condmask_false0);
        }
      }

      qdrn = -((qgate + qbulk) + qsrc);
      {
        heres[0]->BSIM3v32cggb = Cgg[0];
        heres[1]->BSIM3v32cggb = Cgg[1];
      }
      {
        Vec2d val = -((Cgg + Cgd) + Cgb);
        heres[0]->BSIM3v32cgsb = val[0];
        heres[1]->BSIM3v32cgsb = val[1];
      }
      {
        heres[0]->BSIM3v32cgdb = Cgd[0];
        heres[1]->BSIM3v32cgdb = Cgd[1];
      }
      {
        Vec2d val = -((Cgg + Cbg) + Csg);
        heres[0]->BSIM3v32cdgb = val[0];
        heres[1]->BSIM3v32cdgb = val[1];
      }
      {
        Vec2d val = (((((((Cgg + Cgd) + Cgb) + Cbg) + Cbd) + Cbb) + Csg) + Csd) + Csb;
        heres[0]->BSIM3v32cdsb = val[0];
        heres[1]->BSIM3v32cdsb = val[1];
      }
      {
        Vec2d val = -((Cgd + Cbd) + Csd);
        heres[0]->BSIM3v32cddb = val[0];
        heres[1]->BSIM3v32cddb = val[1];
      }
      {
        heres[0]->BSIM3v32cbgb = Cbg[0];
        heres[1]->BSIM3v32cbgb = Cbg[1];
      }
      {
        Vec2d val = -((Cbg + Cbd) + Cbb);
        heres[0]->BSIM3v32cbsb = val[0];
        heres[1]->BSIM3v32cbsb = val[1];
      }
      {
        heres[0]->BSIM3v32cbdb = Cbd[0];
        heres[1]->BSIM3v32cbdb = Cbd[1];
      }
      {
        Vec2d val = -(qgate + qbulk);
        heres[0]->BSIM3v32qinv = val[0];
        heres[1]->BSIM3v32qinv = val[1];
      }
    }
    else
      if (model->BSIM3v32capMod == 2)
    {
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          Vfb = (Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb};
          break;

        case BSIM3v32V32:
          Vfb = (Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb};
          dVfb_dVb = (dVfb_dVd = vec2_SIMDTOVECTOR(0.0));
          break;

        default:
          Vfb = (Vth - pParam->BSIM3v32phi) - (pParam->BSIM3v32k1ox * sqrtPhis);
          dVfb_dVb = dVth_dVb - (pParam->BSIM3v32k1ox * dsqrtPhis_dVb);
          dVfb_dVd = dVth_dVd;

      }

      V3 = ((Vfb - Vgs_eff) + VbseffCV) - DELTA_3;
      T0 = V3 * V3;
      T2 = (4.0 * DELTA_3) * Vfb;
      if (1)
      {
        Vec2m condmask0 = Vfb <= 0.0;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          T0 = vec2_blend(T0, T0 - T2, condmask_true0);
          T2 = vec2_blend(T2, vec2_SIMDTOVECTOR(-DELTA_3), condmask_true0);
        }
        {
          T0 = vec2_blend(T0, T0 + T2, condmask_false0);
          T2 = vec2_blend(T2, vec2_SIMDTOVECTOR(DELTA_3), condmask_false0);
        }
      }

      T0 = vec2_sqrt(T0);
      T2 = T2 / T0;
      T1 = 0.5 * (1.0 + (V3 / T0));
      Vfbeff = Vfb - (0.5 * (V3 + T0));
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          break;

        case BSIM3v32V32:

        default:
          dVfbeff_dVd = ((1.0 - T1) - T2) * dVfb_dVd;

      }

      dVfbeff_dVg = T1 * dVgs_eff_dVg;
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          dVfbeff_dVb = (-T1) * dVbseffCV_dVb;
          break;

        case BSIM3v32V32:

        default:
          dVfbeff_dVb = (((1.0 - T1) - T2) * dVfb_dVb) - (T1 * dVbseffCV_dVb);

      }

      Qac0 = CoxWL * (Vfbeff - Vfb);
      dQac0_dVg = CoxWL * dVfbeff_dVg;
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          break;

        case BSIM3v32V32:

        default:
          dQac0_dVd = CoxWL * (dVfbeff_dVd - dVfb_dVd);

      }

      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          dQac0_dVb = CoxWL * dVfbeff_dVb;
          break;

        case BSIM3v32V32:

        default:
          dQac0_dVb = CoxWL * (dVfbeff_dVb - dVfb_dVb);

      }

      T0 = vec2_SIMDTOVECTOR(0.5 * pParam->BSIM3v32k1ox);
      T3 = ((Vgs_eff - Vfbeff) - VbseffCV) - Vgsteff;
      if (pParam->BSIM3v32k1ox == 0.0)
      {
        T1 = vec2_SIMDTOVECTOR(0.0);
        T2 = vec2_SIMDTOVECTOR(0.0);
      }
      else
        if (1)
      {
        Vec2m condmask0 = T3 < 0.0;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          T1 = vec2_blend(T1, T0 + (T3 / pParam->BSIM3v32k1ox), condmask_true0);
          T2 = vec2_blend(T2, vec2_SIMDTOVECTOR(CoxWL), condmask_true0);
        }
        {
          T1 = vec2_blend(T1, vec2_sqrt((T0 * T0) + T3), condmask_false0);
          T2 = vec2_blend(T2, (CoxWL * T0) / T1, condmask_false0);
        }
      }


      Qsub0 = (CoxWL * pParam->BSIM3v32k1ox) * (T1 - T0);
      dQsub0_dVg = T2 * ((dVgs_eff_dVg - dVfbeff_dVg) - dVgsteff_dVg);
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          dQsub0_dVd = (-T2) * dVgsteff_dVd;
          break;

        case BSIM3v32V32:

        default:
          dQsub0_dVd = (-T2) * (dVfbeff_dVd + dVgsteff_dVd);

      }

      dQsub0_dVb = (-T2) * ((dVfbeff_dVb + dVbseffCV_dVb) + dVgsteff_dVb);
      AbulkCV = Abulk0 * pParam->BSIM3v32abulkCVfactor;
      dAbulkCV_dVb = pParam->BSIM3v32abulkCVfactor * dAbulk0_dVb;
      VdsatCV = Vgsteff / AbulkCV;
      V4 = (VdsatCV - Vds) - DELTA_4;
      T0 = vec2_sqrt((V4 * V4) + ((4.0 * DELTA_4) * VdsatCV));
      VdseffCV = VdsatCV - (0.5 * (V4 + T0));
      T1 = 0.5 * (1.0 + (V4 / T0));
      T2 = DELTA_4 / T0;
      T3 = ((1.0 - T1) - T2) / AbulkCV;
      dVdseffCV_dVg = T3;
      dVdseffCV_dVd = T1;
      dVdseffCV_dVb = ((-T3) * VdsatCV) * dAbulkCV_dVb;
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          if (1)
        {
          Vec2m condmask0 = Vds == 0.0;
          Vec2m condmask_true0 = condmask0;
          {
            VdseffCV = vec2_blend(VdseffCV, vec2_SIMDTOVECTOR(0.0), condmask_true0);
            dVdseffCV_dVg = vec2_blend(dVdseffCV_dVg, vec2_SIMDTOVECTOR(0.0), condmask_true0);
            dVdseffCV_dVb = vec2_blend(dVdseffCV_dVb, vec2_SIMDTOVECTOR(0.0), condmask_true0);
          }
        }

          break;

        case BSIM3v32V32:

        default:
          break;

      }

      T0 = AbulkCV * VdseffCV;
      T1 = 12.0 * ((Vgsteff - (0.5 * T0)) + 1e-20);
      T2 = VdseffCV / T1;
      T3 = T0 * T2;
      T4 = 1.0 - (((12.0 * T2) * T2) * AbulkCV);
      T5 = (((6.0 * T0) * ((4.0 * Vgsteff) - T0)) / (T1 * T1)) - 0.5;
      T6 = ((12.0 * T2) * T2) * Vgsteff;
      qinoi = (-CoxWL) * ((Vgsteff - (0.5 * T0)) + (AbulkCV * T3));
      qgate = CoxWL * ((Vgsteff - (0.5 * VdseffCV)) + T3);
      Cgg1 = CoxWL * (T4 + (T5 * dVdseffCV_dVg));
      Cgd1 = ((CoxWL * T5) * dVdseffCV_dVd) + (Cgg1 * dVgsteff_dVd);
      Cgb1 = (CoxWL * ((T5 * dVdseffCV_dVb) + (T6 * dAbulkCV_dVb))) + (Cgg1 * dVgsteff_dVb);
      Cgg1 *= dVgsteff_dVg;
      T7 = 1.0 - AbulkCV;
      qbulk = (CoxWL * T7) * ((0.5 * VdseffCV) - T3);
      T4 = (-T7) * (T4 - 1.0);
      T5 = (-T7) * T5;
      T6 = -((T7 * T6) + ((0.5 * VdseffCV) - T3));
      Cbg1 = CoxWL * (T4 + (T5 * dVdseffCV_dVg));
      Cbd1 = ((CoxWL * T5) * dVdseffCV_dVd) + (Cbg1 * dVgsteff_dVd);
      Cbb1 = (CoxWL * ((T5 * dVdseffCV_dVb) + (T6 * dAbulkCV_dVb))) + (Cbg1 * dVgsteff_dVb);
      Cbg1 *= dVgsteff_dVg;
      if (model->BSIM3v32xpart > 0.5)
      {
        T1 = T1 + T1;
        qsrc = (-CoxWL) * (((0.5 * Vgsteff) + (0.25 * T0)) - ((T0 * T0) / T1));
        T7 = ((4.0 * Vgsteff) - T0) / (T1 * T1);
        T4 = -(0.5 + (((24.0 * T0) * T0) / (T1 * T1)));
        T5 = -((0.25 * AbulkCV) - (((12.0 * AbulkCV) * T0) * T7));
        T6 = -((0.25 * VdseffCV) - (((12.0 * T0) * VdseffCV) * T7));
        Csg = CoxWL * (T4 + (T5 * dVdseffCV_dVg));
        Csd = ((CoxWL * T5) * dVdseffCV_dVd) + (Csg * dVgsteff_dVd);
        Csb = (CoxWL * ((T5 * dVdseffCV_dVb) + (T6 * dAbulkCV_dVb))) + (Csg * dVgsteff_dVb);
        Csg *= dVgsteff_dVg;
      }
      else
        if (model->BSIM3v32xpart < 0.5)
      {
        T1 = T1 / 12.0;
        T2 = (0.5 * CoxWL) / (T1 * T1);
        T3 = (Vgsteff * ((((2.0 * T0) * T0) / 3.0) + (Vgsteff * (Vgsteff - ((4.0 * T0) / 3.0))))) - ((((2.0 * T0) * T0) * T0) / 15.0);
        qsrc = (-T2) * T3;
        T7 = (((4.0 / 3.0) * Vgsteff) * (Vgsteff - T0)) + ((0.4 * T0) * T0);
        T4 = (((-2.0) * qsrc) / T1) - (T2 * ((Vgsteff * ((3.0 * Vgsteff) - ((8.0 * T0) / 3.0))) + (((2.0 * T0) * T0) / 3.0)));
        T5 = ((qsrc / T1) + (T2 * T7)) * AbulkCV;
        T6 = ((qsrc / T1) * VdseffCV) + ((T2 * T7) * VdseffCV);
        Csg = T4 + (T5 * dVdseffCV_dVg);
        Csd = (T5 * dVdseffCV_dVd) + (Csg * dVgsteff_dVd);
        Csb = ((T5 * dVdseffCV_dVb) + (T6 * dAbulkCV_dVb)) + (Csg * dVgsteff_dVb);
        Csg *= dVgsteff_dVg;
      }
      else
      {
        qsrc = (-0.5) * (qgate + qbulk);
        Csg = (-0.5) * (Cgg1 + Cbg1);
        Csb = (-0.5) * (Cgb1 + Cbb1);
        Csd = (-0.5) * (Cgd1 + Cbd1);
      }


      qgate += Qac0 + Qsub0;
      qbulk -= Qac0 + Qsub0;
      qdrn = -((qgate + qbulk) + qsrc);
      Cgg = (dQac0_dVg + dQsub0_dVg) + Cgg1;
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          Cgd = dQsub0_dVd + Cgd1;
          break;

        case BSIM3v32V32:

        default:
          Cgd = (dQac0_dVd + dQsub0_dVd) + Cgd1;

      }

      Cgb = (dQac0_dVb + dQsub0_dVb) + Cgb1;
      Cbg = (Cbg1 - dQac0_dVg) - dQsub0_dVg;
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          Cbd = Cbd1 - dQsub0_dVd;
          break;

        case BSIM3v32V32:

        default:
          Cbd = (Cbd1 - dQac0_dVd) - dQsub0_dVd;

      }

      Cbb = (Cbb1 - dQac0_dVb) - dQsub0_dVb;
      Cgb *= dVbseff_dVb;
      Cbb *= dVbseff_dVb;
      Csb *= dVbseff_dVb;
      {
        heres[0]->BSIM3v32cggb = Cgg[0];
        heres[1]->BSIM3v32cggb = Cgg[1];
      }
      {
        Vec2d val = -((Cgg + Cgd) + Cgb);
        heres[0]->BSIM3v32cgsb = val[0];
        heres[1]->BSIM3v32cgsb = val[1];
      }
      {
        heres[0]->BSIM3v32cgdb = Cgd[0];
        heres[1]->BSIM3v32cgdb = Cgd[1];
      }
      {
        Vec2d val = -((Cgg + Cbg) + Csg);
        heres[0]->BSIM3v32cdgb = val[0];
        heres[1]->BSIM3v32cdgb = val[1];
      }
      {
        Vec2d val = (((((((Cgg + Cgd) + Cgb) + Cbg) + Cbd) + Cbb) + Csg) + Csd) + Csb;
        heres[0]->BSIM3v32cdsb = val[0];
        heres[1]->BSIM3v32cdsb = val[1];
      }
      {
        Vec2d val = -((Cgd + Cbd) + Csd);
        heres[0]->BSIM3v32cddb = val[0];
        heres[1]->BSIM3v32cddb = val[1];
      }
      {
        heres[0]->BSIM3v32cbgb = Cbg[0];
        heres[1]->BSIM3v32cbgb = Cbg[1];
      }
      {
        Vec2d val = -((Cbg + Cbd) + Cbb);
        heres[0]->BSIM3v32cbsb = val[0];
        heres[1]->BSIM3v32cbsb = val[1];
      }
      {
        heres[0]->BSIM3v32cbdb = Cbd[0];
        heres[1]->BSIM3v32cbdb = Cbd[1];
      }
      {
        heres[0]->BSIM3v32qinv = qinoi[0];
        heres[1]->BSIM3v32qinv = qinoi[1];
      }
    }
    else
      if (model->BSIM3v32capMod == 3)
    {
      V3 = ((((Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb}) - Vgs_eff) + VbseffCV) - DELTA_3;
      T0 = V3 * V3;
      T2 = (4.0 * DELTA_3) * ((Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb});
      if (1)
      {
        Vec2m condmask0 = ((Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb}) <= 0.0;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          T0 = vec2_blend(T0, T0 - T2, condmask_true0);
          T2 = vec2_blend(T2, vec2_SIMDTOVECTOR(-DELTA_3), condmask_true0);
        }
        {
          T0 = vec2_blend(T0, T0 + T2, condmask_false0);
          T2 = vec2_blend(T2, vec2_SIMDTOVECTOR(DELTA_3), condmask_false0);
        }
      }

      T0 = vec2_sqrt(T0);
      T2 = T2 / T0;
      T1 = 0.5 * (1.0 + (V3 / T0));
      Vfbeff = ((Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb}) - (0.5 * (V3 + T0));
      dVfbeff_dVg = T1 * dVgs_eff_dVg;
      dVfbeff_dVb = (-T1) * dVbseffCV_dVb;
      Cox = model->BSIM3v32cox;
      Tox = 1.0e8 * model->BSIM3v32tox;
      T0 = ((Vgs_eff - VbseffCV) - ((Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb})) / Tox;
      dT0_dVg = dVgs_eff_dVg / Tox;
      dT0_dVb = (-dVbseffCV_dVb) / Tox;
      tmp = T0 * pParam->BSIM3v32acde;
      dTcen_dVg = (dTcen_dVb = vec2_SIMDTOVECTOR(0.0));
      if (1)
      {
        Vec2m condmask0 = ((-EXP_THRESHOLD) < tmp) & (tmp < EXP_THRESHOLD);
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          Tcen = vec2_blend(Tcen, pParam->BSIM3v32ldeb * vec2_exp(tmp), condmask_true0);
          dTcen_dVg = vec2_blend(dTcen_dVg, pParam->BSIM3v32acde * Tcen, condmask_true0);
          dTcen_dVb = vec2_blend(dTcen_dVb, dTcen_dVg * dT0_dVb, condmask_true0);
          dTcen_dVg = vec2_blend(dTcen_dVg, dTcen_dVg * dT0_dVg, condmask_true0);
        }
        if (1)
        {
          Vec2m condmask1 = tmp <= (-EXP_THRESHOLD);
          Vec2m condmask_true1 = condmask_false0 & condmask1;
          Vec2m condmask_false1 = condmask_false0 & (~condmask1);
          {
            Tcen = vec2_blend(Tcen, vec2_SIMDTOVECTOR(pParam->BSIM3v32ldeb * MIN_EXP), condmask_true1);
          }
          {
            Tcen = vec2_blend(Tcen, vec2_SIMDTOVECTOR(pParam->BSIM3v32ldeb * MAX_EXP), condmask_false1);
          }
        }

      }

      LINK = 1.0e-3 * model->BSIM3v32tox;
      V3 = (pParam->BSIM3v32ldeb - Tcen) - LINK;
      V4 = vec2_sqrt((V3 * V3) + ((4.0 * LINK) * pParam->BSIM3v32ldeb));
      Tcen = pParam->BSIM3v32ldeb - (0.5 * (V3 + V4));
      T1 = 0.5 * (1.0 + (V3 / V4));
      dTcen_dVg *= T1;
      dTcen_dVb *= T1;
      Ccen = EPSSI / Tcen;
      T2 = Cox / (Cox + Ccen);
      Coxeff = T2 * Ccen;
      T3 = (-Ccen) / Tcen;
      dCoxeff_dVg = (T2 * T2) * T3;
      dCoxeff_dVb = dCoxeff_dVg * dTcen_dVb;
      dCoxeff_dVg *= dTcen_dVg;
      CoxWLcen = (CoxWL * Coxeff) / Cox;
      Qac0 = CoxWLcen * (Vfbeff - ((Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb}));
      QovCox = Qac0 / Coxeff;
      dQac0_dVg = (CoxWLcen * dVfbeff_dVg) + (QovCox * dCoxeff_dVg);
      dQac0_dVb = (CoxWLcen * dVfbeff_dVb) + (QovCox * dCoxeff_dVb);
      T0 = vec2_SIMDTOVECTOR(0.5 * pParam->BSIM3v32k1ox);
      T3 = ((Vgs_eff - Vfbeff) - VbseffCV) - Vgsteff;
      if (pParam->BSIM3v32k1ox == 0.0)
      {
        T1 = vec2_SIMDTOVECTOR(0.0);
        T2 = vec2_SIMDTOVECTOR(0.0);
      }
      else
        if (1)
      {
        Vec2m condmask0 = T3 < 0.0;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          T1 = vec2_blend(T1, T0 + (T3 / pParam->BSIM3v32k1ox), condmask_true0);
          T2 = vec2_blend(T2, CoxWLcen, condmask_true0);
        }
        {
          T1 = vec2_blend(T1, vec2_sqrt((T0 * T0) + T3), condmask_false0);
          T2 = vec2_blend(T2, (CoxWLcen * T0) / T1, condmask_false0);
        }
      }


      Qsub0 = (CoxWLcen * pParam->BSIM3v32k1ox) * (T1 - T0);
      QovCox = Qsub0 / Coxeff;
      dQsub0_dVg = (T2 * ((dVgs_eff_dVg - dVfbeff_dVg) - dVgsteff_dVg)) + (QovCox * dCoxeff_dVg);
      dQsub0_dVd = (-T2) * dVgsteff_dVd;
      dQsub0_dVb = ((-T2) * ((dVfbeff_dVb + dVbseffCV_dVb) + dVgsteff_dVb)) + (QovCox * dCoxeff_dVb);
      if (pParam->BSIM3v32k1ox <= 0.0)
      {
        Denomi = vec2_SIMDTOVECTOR((0.25 * pParam->BSIM3v32moin) * Vtm);
        T0 = vec2_SIMDTOVECTOR(0.5 * pParam->BSIM3v32sqrtPhi);
      }
      else
      {
        Denomi = vec2_SIMDTOVECTOR(((pParam->BSIM3v32moin * Vtm) * pParam->BSIM3v32k1ox) * pParam->BSIM3v32k1ox);
        T0 = vec2_SIMDTOVECTOR(pParam->BSIM3v32k1ox * pParam->BSIM3v32sqrtPhi);
      }

      T1 = (2.0 * T0) + Vgsteff;
      DeltaPhi = Vtm * vec2_log(1.0 + ((T1 * Vgsteff) / Denomi));
      dDeltaPhi_dVg = ((2.0 * Vtm) * (T1 - T0)) / (Denomi + (T1 * Vgsteff));
      dDeltaPhi_dVd = dDeltaPhi_dVg * dVgsteff_dVd;
      dDeltaPhi_dVb = dDeltaPhi_dVg * dVgsteff_dVb;
      T3 = 4.0 * ((Vth - ((Vec2d ){heres[0]->BSIM3v32vfbzb, heres[1]->BSIM3v32vfbzb})) - pParam->BSIM3v32phi);
      Tox += Tox;
      if (1)
      {
        Vec2m condmask0 = T3 >= 0.0;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          switch (model->BSIM3v32intVersion)
          {
            case BSIM3v32V324:

            case BSIM3v32V323:

            case BSIM3v32V322:
              T0 = vec2_blend(T0, (Vgsteff + T3) / Tox, condmask_true0);
              dT0_dVd = vec2_blend(dT0_dVd, (dVgsteff_dVd + (4.0 * dVth_dVd)) / Tox, condmask_true0);
              dT0_dVb = vec2_blend(dT0_dVb, (dVgsteff_dVb + (4.0 * dVth_dVb)) / Tox, condmask_true0);
              break;

            case BSIM3v32V32:

            default:
              T0 = vec2_blend(T0, (Vgsteff + T3) / Tox, condmask_true0);

          }

        }
        {
          switch (model->BSIM3v32intVersion)
          {
            case BSIM3v32V324:

            case BSIM3v32V323:

            case BSIM3v32V322:
              T0 = vec2_blend(T0, (Vgsteff + 1.0e-20) / Tox, condmask_false0);
              dT0_dVd = vec2_blend(dT0_dVd, dVgsteff_dVd / Tox, condmask_false0);
              dT0_dVb = vec2_blend(dT0_dVb, dVgsteff_dVb / Tox, condmask_false0);
              break;

            case BSIM3v32V32:

            default:
              T0 = vec2_blend(T0, (Vgsteff + 1.0e-20) / Tox, condmask_false0);

          }

        }
      }

      tmp = vec2_pow0p7(T0, 0.7);
      T1 = 1.0 + tmp;
      T2 = (0.7 * tmp) / (T0 * Tox);
      Tcen = 1.9e-9 / T1;
      dTcen_dVg = (((-1.9e-9) * T2) / T1) / T1;
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          dTcen_dVd = Tox * dTcen_dVg;
          dTcen_dVb = dTcen_dVd * dT0_dVb;
          dTcen_dVd *= dT0_dVd;
          break;

        case BSIM3v32V32:

        default:
          dTcen_dVd = dTcen_dVg * ((4.0 * dVth_dVd) + dVgsteff_dVd);
          dTcen_dVb = dTcen_dVg * ((4.0 * dVth_dVb) + dVgsteff_dVb);

      }

      dTcen_dVg *= dVgsteff_dVg;
      Ccen = EPSSI / Tcen;
      T0 = Cox / (Cox + Ccen);
      Coxeff = T0 * Ccen;
      T1 = (-Ccen) / Tcen;
      dCoxeff_dVg = (T0 * T0) * T1;
      dCoxeff_dVd = dCoxeff_dVg * dTcen_dVd;
      dCoxeff_dVb = dCoxeff_dVg * dTcen_dVb;
      dCoxeff_dVg *= dTcen_dVg;
      CoxWLcen = (CoxWL * Coxeff) / Cox;
      AbulkCV = Abulk0 * pParam->BSIM3v32abulkCVfactor;
      dAbulkCV_dVb = pParam->BSIM3v32abulkCVfactor * dAbulk0_dVb;
      VdsatCV = (Vgsteff - DeltaPhi) / AbulkCV;
      V4 = (VdsatCV - Vds) - DELTA_4;
      T0 = vec2_sqrt((V4 * V4) + ((4.0 * DELTA_4) * VdsatCV));
      VdseffCV = VdsatCV - (0.5 * (V4 + T0));
      T1 = 0.5 * (1.0 + (V4 / T0));
      T2 = DELTA_4 / T0;
      T3 = ((1.0 - T1) - T2) / AbulkCV;
      T4 = T3 * (1.0 - dDeltaPhi_dVg);
      dVdseffCV_dVg = T4;
      dVdseffCV_dVd = T1;
      dVdseffCV_dVb = ((-T3) * VdsatCV) * dAbulkCV_dVb;
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:

        case BSIM3v32V322:
          if (1)
        {
          Vec2m condmask0 = Vds == 0.0;
          Vec2m condmask_true0 = condmask0;
          {
            VdseffCV = vec2_blend(VdseffCV, vec2_SIMDTOVECTOR(0.0), condmask_true0);
            dVdseffCV_dVg = vec2_blend(dVdseffCV_dVg, vec2_SIMDTOVECTOR(0.0), condmask_true0);
            dVdseffCV_dVb = vec2_blend(dVdseffCV_dVb, vec2_SIMDTOVECTOR(0.0), condmask_true0);
          }
        }

          break;

        case BSIM3v32V32:

        default:
          break;

      }

      T0 = AbulkCV * VdseffCV;
      T1 = Vgsteff - DeltaPhi;
      T2 = 12.0 * ((T1 - (0.5 * T0)) + 1.0e-20);
      T3 = T0 / T2;
      T4 = 1.0 - ((12.0 * T3) * T3);
      T5 = AbulkCV * ((((6.0 * T0) * ((4.0 * T1) - T0)) / (T2 * T2)) - 0.5);
      T6 = (T5 * VdseffCV) / AbulkCV;
      qgate = (qinoi = CoxWLcen * (T1 - (T0 * (0.5 - T3))));
      QovCox = qgate / Coxeff;
      Cgg1 = CoxWLcen * ((T4 * (1.0 - dDeltaPhi_dVg)) + (T5 * dVdseffCV_dVg));
      Cgd1 = (((CoxWLcen * T5) * dVdseffCV_dVd) + (Cgg1 * dVgsteff_dVd)) + (QovCox * dCoxeff_dVd);
      Cgb1 = ((CoxWLcen * ((T5 * dVdseffCV_dVb) + (T6 * dAbulkCV_dVb))) + (Cgg1 * dVgsteff_dVb)) + (QovCox * dCoxeff_dVb);
      Cgg1 = (Cgg1 * dVgsteff_dVg) + (QovCox * dCoxeff_dVg);
      T7 = 1.0 - AbulkCV;
      T8 = T2 * T2;
      T9 = (((12.0 * T7) * T0) * T0) / (T8 * AbulkCV);
      T10 = T9 * (1.0 - dDeltaPhi_dVg);
      T11 = ((-T7) * T5) / AbulkCV;
      T12 = -(((T9 * T1) / AbulkCV) + (VdseffCV * (0.5 - (T0 / T2))));
      qbulk = (CoxWLcen * T7) * ((0.5 * VdseffCV) - ((T0 * VdseffCV) / T2));
      QovCox = qbulk / Coxeff;
      Cbg1 = CoxWLcen * (T10 + (T11 * dVdseffCV_dVg));
      Cbd1 = (((CoxWLcen * T11) * dVdseffCV_dVd) + (Cbg1 * dVgsteff_dVd)) + (QovCox * dCoxeff_dVd);
      Cbb1 = ((CoxWLcen * ((T11 * dVdseffCV_dVb) + (T12 * dAbulkCV_dVb))) + (Cbg1 * dVgsteff_dVb)) + (QovCox * dCoxeff_dVb);
      Cbg1 = (Cbg1 * dVgsteff_dVg) + (QovCox * dCoxeff_dVg);
      if (model->BSIM3v32xpart > 0.5)
      {
        qsrc = (-CoxWLcen) * (((T1 / 2.0) + (T0 / 4.0)) - (((0.5 * T0) * T0) / T2));
        QovCox = qsrc / Coxeff;
        T2 += T2;
        T3 = T2 * T2;
        T7 = -(0.25 - (((12.0 * T0) * ((4.0 * T1) - T0)) / T3));
        T4 = (-(0.5 + (((24.0 * T0) * T0) / T3))) * (1.0 - dDeltaPhi_dVg);
        T5 = T7 * AbulkCV;
        T6 = T7 * VdseffCV;
        Csg = CoxWLcen * (T4 + (T5 * dVdseffCV_dVg));
        Csd = (((CoxWLcen * T5) * dVdseffCV_dVd) + (Csg * dVgsteff_dVd)) + (QovCox * dCoxeff_dVd);
        Csb = ((CoxWLcen * ((T5 * dVdseffCV_dVb) + (T6 * dAbulkCV_dVb))) + (Csg * dVgsteff_dVb)) + (QovCox * dCoxeff_dVb);
        Csg = (Csg * dVgsteff_dVg) + (QovCox * dCoxeff_dVg);
      }
      else
        if (model->BSIM3v32xpart < 0.5)
      {
        T2 = T2 / 12.0;
        T3 = (0.5 * CoxWLcen) / (T2 * T2);
        T4 = (T1 * ((((2.0 * T0) * T0) / 3.0) + (T1 * (T1 - ((4.0 * T0) / 3.0))))) - ((((2.0 * T0) * T0) * T0) / 15.0);
        qsrc = (-T3) * T4;
        QovCox = qsrc / Coxeff;
        T8 = (((4.0 / 3.0) * T1) * (T1 - T0)) + ((0.4 * T0) * T0);
        T5 = (((-2.0) * qsrc) / T2) - (T3 * ((T1 * ((3.0 * T1) - ((8.0 * T0) / 3.0))) + (((2.0 * T0) * T0) / 3.0)));
        T6 = AbulkCV * ((qsrc / T2) + (T3 * T8));
        T7 = (T6 * VdseffCV) / AbulkCV;
        Csg = (T5 * (1.0 - dDeltaPhi_dVg)) + (T6 * dVdseffCV_dVg);
        Csd = ((Csg * dVgsteff_dVd) + (T6 * dVdseffCV_dVd)) + (QovCox * dCoxeff_dVd);
        Csb = (((Csg * dVgsteff_dVb) + (T6 * dVdseffCV_dVb)) + (T7 * dAbulkCV_dVb)) + (QovCox * dCoxeff_dVb);
        Csg = (Csg * dVgsteff_dVg) + (QovCox * dCoxeff_dVg);
      }
      else
      {
        qsrc = (-0.5) * qgate;
        Csg = (-0.5) * Cgg1;
        Csd = (-0.5) * Cgd1;
        Csb = (-0.5) * Cgb1;
      }


      qgate += (Qac0 + Qsub0) - qbulk;
      qbulk -= Qac0 + Qsub0;
      qdrn = -((qgate + qbulk) + qsrc);
      Cbg = (Cbg1 - dQac0_dVg) - dQsub0_dVg;
      Cbd = Cbd1 - dQsub0_dVd;
      Cbb = (Cbb1 - dQac0_dVb) - dQsub0_dVb;
      Cgg = Cgg1 - Cbg;
      Cgd = Cgd1 - Cbd;
      Cgb = Cgb1 - Cbb;
      Cgb *= dVbseff_dVb;
      Cbb *= dVbseff_dVb;
      Csb *= dVbseff_dVb;
      {
        heres[0]->BSIM3v32cggb = Cgg[0];
        heres[1]->BSIM3v32cggb = Cgg[1];
      }
      {
        Vec2d val = -((Cgg + Cgd) + Cgb);
        heres[0]->BSIM3v32cgsb = val[0];
        heres[1]->BSIM3v32cgsb = val[1];
      }
      {
        heres[0]->BSIM3v32cgdb = Cgd[0];
        heres[1]->BSIM3v32cgdb = Cgd[1];
      }
      {
        Vec2d val = -((Cgg + Cbg) + Csg);
        heres[0]->BSIM3v32cdgb = val[0];
        heres[1]->BSIM3v32cdgb = val[1];
      }
      {
        Vec2d val = (((((((Cgg + Cgd) + Cgb) + Cbg) + Cbd) + Cbb) + Csg) + Csd) + Csb;
        heres[0]->BSIM3v32cdsb = val[0];
        heres[1]->BSIM3v32cdsb = val[1];
      }
      {
        Vec2d val = -((Cgd + Cbd) + Csd);
        heres[0]->BSIM3v32cddb = val[0];
        heres[1]->BSIM3v32cddb = val[1];
      }
      {
        heres[0]->BSIM3v32cbgb = Cbg[0];
        heres[1]->BSIM3v32cbgb = Cbg[1];
      }
      {
        Vec2d val = -((Cbg + Cbd) + Cbb);
        heres[0]->BSIM3v32cbsb = val[0];
        heres[1]->BSIM3v32cbsb = val[1];
      }
      {
        heres[0]->BSIM3v32cbdb = Cbd[0];
        heres[1]->BSIM3v32cbdb = Cbd[1];
      }
      {
        Vec2d val = -qinoi;
        heres[0]->BSIM3v32qinv = val[0];
        heres[1]->BSIM3v32qinv = val[1];
      }
    }



  }


  finished:
  {
    heres[0]->BSIM3v32qgate = qgate[0];
    heres[1]->BSIM3v32qgate = qgate[1];
  }

  {
    heres[0]->BSIM3v32qbulk = qbulk[0];
    heres[1]->BSIM3v32qbulk = qbulk[1];
  }
  {
    heres[0]->BSIM3v32qdrn = qdrn[0];
    heres[1]->BSIM3v32qdrn = qdrn[1];
  }
  {
    heres[0]->BSIM3v32cd = cdrain[0];
    heres[1]->BSIM3v32cd = cdrain[1];
  }
  if (ChargeComputationNeeded)
  {
    Vec2d nstate_qbs = vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qbs, heres[1]->BSIM3v32qbs});
    Vec2d nstate_qbd = vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qbd, heres[1]->BSIM3v32qbd});
    if (model->BSIM3v32acmMod == 0)
    {
      switch (model->BSIM3v32intVersion)
      {
        case BSIM3v32V324:

        case BSIM3v32V323:
          czbd = model->BSIM3v32unitAreaTempJctCap * ((Vec2d ){heres[0]->BSIM3v32drainArea, heres[1]->BSIM3v32drainArea});
          czbs = model->BSIM3v32unitAreaTempJctCap * ((Vec2d ){heres[0]->BSIM3v32sourceArea, heres[1]->BSIM3v32sourceArea});
          break;

        case BSIM3v32V322:

        case BSIM3v32V32:

        default:
          czbd = model->BSIM3v32unitAreaJctCap * ((Vec2d ){heres[0]->BSIM3v32drainArea, heres[1]->BSIM3v32drainArea});
          czbs = model->BSIM3v32unitAreaJctCap * ((Vec2d ){heres[0]->BSIM3v32sourceArea, heres[1]->BSIM3v32sourceArea});

      }

      if (1)
      {
        Vec2m condmask0 = ((Vec2d ){heres[0]->BSIM3v32drainPerimeter, heres[1]->BSIM3v32drainPerimeter}) < pParam->BSIM3v32weff;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          czbdsw = vec2_blend(czbdsw, vec2_SIMDTOVECTOR(0.0), condmask_true0);
          switch (model->BSIM3v32intVersion)
          {
            case BSIM3v32V324:

            case BSIM3v32V323:
              czbdswg = vec2_blend(czbdswg, model->BSIM3v32unitLengthGateSidewallTempJctCap * ((Vec2d ){heres[0]->BSIM3v32drainPerimeter, heres[1]->BSIM3v32drainPerimeter}), condmask_true0);
              break;

            case BSIM3v32V322:

            case BSIM3v32V32:

            default:
              czbdswg = vec2_blend(czbdswg, model->BSIM3v32unitLengthGateSidewallJctCap * ((Vec2d ){heres[0]->BSIM3v32drainPerimeter, heres[1]->BSIM3v32drainPerimeter}), condmask_true0);

          }

        }
        {
          switch (model->BSIM3v32intVersion)
          {
            case BSIM3v32V324:

            case BSIM3v32V323:
              czbdsw = vec2_blend(czbdsw, model->BSIM3v32unitLengthSidewallTempJctCap * (((Vec2d ){heres[0]->BSIM3v32drainPerimeter, heres[1]->BSIM3v32drainPerimeter}) - pParam->BSIM3v32weff), condmask_false0);
              czbdswg = vec2_blend(czbdswg, vec2_SIMDTOVECTOR(model->BSIM3v32unitLengthGateSidewallTempJctCap * pParam->BSIM3v32weff), condmask_false0);
              break;

            case BSIM3v32V322:

            case BSIM3v32V32:

            default:
              czbdsw = vec2_blend(czbdsw, model->BSIM3v32unitLengthSidewallJctCap * (((Vec2d ){heres[0]->BSIM3v32drainPerimeter, heres[1]->BSIM3v32drainPerimeter}) - pParam->BSIM3v32weff), condmask_false0);
              czbdswg = vec2_blend(czbdswg, vec2_SIMDTOVECTOR(model->BSIM3v32unitLengthGateSidewallJctCap * pParam->BSIM3v32weff), condmask_false0);

          }

        }
      }

      if (1)
      {
        Vec2m condmask0 = ((Vec2d ){heres[0]->BSIM3v32sourcePerimeter, heres[1]->BSIM3v32sourcePerimeter}) < pParam->BSIM3v32weff;
        Vec2m condmask_true0 = condmask0;
        Vec2m condmask_false0 = ~condmask0;
        {
          czbssw = vec2_blend(czbssw, vec2_SIMDTOVECTOR(0.0), condmask_true0);
          switch (model->BSIM3v32intVersion)
          {
            case BSIM3v32V324:

            case BSIM3v32V323:
              czbsswg = vec2_blend(czbsswg, model->BSIM3v32unitLengthGateSidewallTempJctCap * ((Vec2d ){heres[0]->BSIM3v32sourcePerimeter, heres[1]->BSIM3v32sourcePerimeter}), condmask_true0);
              break;

            case BSIM3v32V322:

            case BSIM3v32V32:

            default:
              czbsswg = vec2_blend(czbsswg, model->BSIM3v32unitLengthGateSidewallJctCap * ((Vec2d ){heres[0]->BSIM3v32sourcePerimeter, heres[1]->BSIM3v32sourcePerimeter}), condmask_true0);

          }

        }
        {
          switch (model->BSIM3v32intVersion)
          {
            case BSIM3v32V324:

            case BSIM3v32V323:
              czbssw = vec2_blend(czbssw, model->BSIM3v32unitLengthSidewallTempJctCap * (((Vec2d ){heres[0]->BSIM3v32sourcePerimeter, heres[1]->BSIM3v32sourcePerimeter}) - pParam->BSIM3v32weff), condmask_false0);
              czbsswg = vec2_blend(czbsswg, vec2_SIMDTOVECTOR(model->BSIM3v32unitLengthGateSidewallTempJctCap * pParam->BSIM3v32weff), condmask_false0);
              break;

            case BSIM3v32V322:

            case BSIM3v32V32:

            default:
              czbssw = vec2_blend(czbssw, model->BSIM3v32unitLengthSidewallJctCap * (((Vec2d ){heres[0]->BSIM3v32sourcePerimeter, heres[1]->BSIM3v32sourcePerimeter}) - pParam->BSIM3v32weff), condmask_false0);
              czbsswg = vec2_blend(czbsswg, vec2_SIMDTOVECTOR(model->BSIM3v32unitLengthGateSidewallJctCap * pParam->BSIM3v32weff), condmask_false0);

          }

        }
      }

    }
    else
    {
      error = vec2_BSIM3v32_ACM_junctionCapacitances(model, heres, &czbd, &czbdsw, &czbdswg, &czbs, &czbssw, &czbsswg);
      if (SIMDANY(error))
        return error;

    }

    MJ = model->BSIM3v32bulkJctBotGradingCoeff;
    MJSW = model->BSIM3v32bulkJctSideGradingCoeff;
    MJSWG = model->BSIM3v32bulkJctGateSideGradingCoeff;
    if (1)
    {
      Vec2m condmask0 = vbs == 0.0;
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        nstate_qbs = vec2_blend(nstate_qbs, vec2_SIMDTOVECTOR(0.0), condmask_true0);
        {
          Vec2d val = (czbs + czbssw) + czbsswg;
          if (condmask_true0[0])
            heres[0]->BSIM3v32capbs = val[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32capbs = val[1];

        }
      }
      if (1)
      {
        Vec2m condmask1 = vbs < 0.0;
        Vec2m condmask_true1 = condmask_false0 & condmask1;
        Vec2m condmask_false1 = condmask_false0 & (~condmask1);
        {
          if (1)
          {
            Vec2m condmask2 = czbs > 0.0;
            Vec2m condmask_true2 = condmask_true1 & condmask2;
            Vec2m condmask_false2 = condmask_true1 & (~condmask2);
            {
              arg = vec2_blend(arg, 1.0 - (vbs / model->BSIM3v32PhiB), condmask_true2);
              if (MJ == 0.5)
                sarg = vec2_blend(sarg, 1.0 / vec2_sqrt(arg), condmask_true2);
              else
                sarg = vec2_blend(sarg, vec2_powMJ(arg, -MJ), condmask_true2);

              nstate_qbs = vec2_blend(nstate_qbs, ((model->BSIM3v32PhiB * czbs) * (1.0 - (arg * sarg))) / (1.0 - MJ), condmask_true2);
              {
                Vec2d val = czbs * sarg;
                if (condmask_true2[0])
                  heres[0]->BSIM3v32capbs = val[0];

                if (condmask_true2[1])
                  heres[1]->BSIM3v32capbs = val[1];

              }
            }
            {
              nstate_qbs = vec2_blend(nstate_qbs, vec2_SIMDTOVECTOR(0.0), condmask_false2);
              {
                if (condmask_false2[0])
                  heres[0]->BSIM3v32capbs = 0.0;

                if (condmask_false2[1])
                  heres[1]->BSIM3v32capbs = 0.0;

              }
            }
          }

          if (1)
          {
            Vec2m condmask2 = czbssw > 0.0;
            Vec2m condmask_true2 = condmask_true1 & condmask2;
            {
              arg = vec2_blend(arg, 1.0 - (vbs / model->BSIM3v32PhiBSW), condmask_true2);
              if (MJSW == 0.5)
                sarg = vec2_blend(sarg, 1.0 / vec2_sqrt(arg), condmask_true2);
              else
                sarg = vec2_blend(sarg, vec2_powMJSW(arg, -MJSW), condmask_true2);

              nstate_qbs = vec2_blend(nstate_qbs, nstate_qbs + (((model->BSIM3v32PhiBSW * czbssw) * (1.0 - (arg * sarg))) / (1.0 - MJSW)), condmask_true2);
              {
                Vec2d val = czbssw * sarg;
                if (condmask_true2[0])
                  heres[0]->BSIM3v32capbs += val[0];

                if (condmask_true2[1])
                  heres[1]->BSIM3v32capbs += val[1];

              }
            }
          }

          if (1)
          {
            Vec2m condmask2 = czbsswg > 0.0;
            Vec2m condmask_true2 = condmask_true1 & condmask2;
            {
              arg = vec2_blend(arg, 1.0 - (vbs / model->BSIM3v32PhiBSWG), condmask_true2);
              if (MJSWG == 0.5)
                sarg = vec2_blend(sarg, 1.0 / vec2_sqrt(arg), condmask_true2);
              else
                sarg = vec2_blend(sarg, vec2_powMJSWG(arg, -MJSWG), condmask_true2);

              nstate_qbs = vec2_blend(nstate_qbs, nstate_qbs + (((model->BSIM3v32PhiBSWG * czbsswg) * (1.0 - (arg * sarg))) / (1.0 - MJSWG)), condmask_true2);
              {
                Vec2d val = czbsswg * sarg;
                if (condmask_true2[0])
                  heres[0]->BSIM3v32capbs += val[0];

                if (condmask_true2[1])
                  heres[1]->BSIM3v32capbs += val[1];

              }
            }
          }

        }
        {
          T0 = vec2_blend(T0, (czbs + czbssw) + czbsswg, condmask_false1);
          T1 = vec2_blend(T1, vbs * ((((czbs * MJ) / model->BSIM3v32PhiB) + ((czbssw * MJSW) / model->BSIM3v32PhiBSW)) + ((czbsswg * MJSWG) / model->BSIM3v32PhiBSWG)), condmask_false1);
          nstate_qbs = vec2_blend(nstate_qbs, vbs * (T0 + (0.5 * T1)), condmask_false1);
          {
            Vec2d val = T0 + T1;
            if (condmask_false1[0])
              heres[0]->BSIM3v32capbs = val[0];

            if (condmask_false1[1])
              heres[1]->BSIM3v32capbs = val[1];

          }
        }
      }

    }

    vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qbs, heres[1]->BSIM3v32qbs}, nstate_qbs);
    if (1)
    {
      Vec2m condmask0 = vbd == 0.0;
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        nstate_qbd = vec2_blend(nstate_qbd, vec2_SIMDTOVECTOR(0.0), condmask_true0);
        {
          Vec2d val = (czbd + czbdsw) + czbdswg;
          if (condmask_true0[0])
            heres[0]->BSIM3v32capbd = val[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32capbd = val[1];

        }
      }
      if (1)
      {
        Vec2m condmask1 = vbd < 0.0;
        Vec2m condmask_true1 = condmask_false0 & condmask1;
        Vec2m condmask_false1 = condmask_false0 & (~condmask1);
        {
          if (1)
          {
            Vec2m condmask2 = czbd > 0.0;
            Vec2m condmask_true2 = condmask_true1 & condmask2;
            Vec2m condmask_false2 = condmask_true1 & (~condmask2);
            {
              arg = vec2_blend(arg, 1.0 - (vbd / model->BSIM3v32PhiB), condmask_true2);
              if (MJ == 0.5)
                sarg = vec2_blend(sarg, 1.0 / vec2_sqrt(arg), condmask_true2);
              else
                sarg = vec2_blend(sarg, vec2_powMJ(arg, -MJ), condmask_true2);

              nstate_qbd = vec2_blend(nstate_qbd, ((model->BSIM3v32PhiB * czbd) * (1.0 - (arg * sarg))) / (1.0 - MJ), condmask_true2);
              {
                Vec2d val = czbd * sarg;
                if (condmask_true2[0])
                  heres[0]->BSIM3v32capbd = val[0];

                if (condmask_true2[1])
                  heres[1]->BSIM3v32capbd = val[1];

              }
            }
            {
              nstate_qbd = vec2_blend(nstate_qbd, vec2_SIMDTOVECTOR(0.0), condmask_false2);
              {
                if (condmask_false2[0])
                  heres[0]->BSIM3v32capbd = 0.0;

                if (condmask_false2[1])
                  heres[1]->BSIM3v32capbd = 0.0;

              }
            }
          }

          if (1)
          {
            Vec2m condmask2 = czbdsw > 0.0;
            Vec2m condmask_true2 = condmask_true1 & condmask2;
            {
              arg = vec2_blend(arg, 1.0 - (vbd / model->BSIM3v32PhiBSW), condmask_true2);
              if (MJSW == 0.5)
                sarg = vec2_blend(sarg, 1.0 / vec2_sqrt(arg), condmask_true2);
              else
                sarg = vec2_blend(sarg, vec2_powMJSW(arg, -MJSW), condmask_true2);

              nstate_qbd = vec2_blend(nstate_qbd, nstate_qbd + (((model->BSIM3v32PhiBSW * czbdsw) * (1.0 - (arg * sarg))) / (1.0 - MJSW)), condmask_true2);
              {
                Vec2d val = czbdsw * sarg;
                if (condmask_true2[0])
                  heres[0]->BSIM3v32capbd += val[0];

                if (condmask_true2[1])
                  heres[1]->BSIM3v32capbd += val[1];

              }
            }
          }

          if (1)
          {
            Vec2m condmask2 = czbdswg > 0.0;
            Vec2m condmask_true2 = condmask_true1 & condmask2;
            {
              arg = vec2_blend(arg, 1.0 - (vbd / model->BSIM3v32PhiBSWG), condmask_true2);
              if (MJSWG == 0.5)
                sarg = vec2_blend(sarg, 1.0 / vec2_sqrt(arg), condmask_true2);
              else
                sarg = vec2_blend(sarg, vec2_powMJSWG(arg, -MJSWG), condmask_true2);

              nstate_qbd = vec2_blend(nstate_qbd, nstate_qbd + (((model->BSIM3v32PhiBSWG * czbdswg) * (1.0 - (arg * sarg))) / (1.0 - MJSWG)), condmask_true2);
              {
                Vec2d val = czbdswg * sarg;
                if (condmask_true2[0])
                  heres[0]->BSIM3v32capbd += val[0];

                if (condmask_true2[1])
                  heres[1]->BSIM3v32capbd += val[1];

              }
            }
          }

        }
        {
          T0 = vec2_blend(T0, (czbd + czbdsw) + czbdswg, condmask_false1);
          T1 = vec2_blend(T1, vbd * ((((czbd * MJ) / model->BSIM3v32PhiB) + ((czbdsw * MJSW) / model->BSIM3v32PhiBSW)) + ((czbdswg * MJSWG) / model->BSIM3v32PhiBSWG)), condmask_false1);
          nstate_qbd = vec2_blend(nstate_qbd, vbd * (T0 + (0.5 * T1)), condmask_false1);
          {
            Vec2d val = T0 + T1;
            if (condmask_false1[0])
              heres[0]->BSIM3v32capbd = val[0];

            if (condmask_false1[1])
              heres[1]->BSIM3v32capbd = val[1];

          }
        }
      }

    }

    vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qbd, heres[1]->BSIM3v32qbd}, nstate_qbd);
  }

  if ((heres[0]->BSIM3v32off == 0) || (!(ckt->CKTmode & MODEINITFIX)))
  {
    Vec2m nonconcount;
    nonconcount = Check;
    ckt->CKTnoncon += vec2_SIMDCOUNT(nonconcount);
  }

  vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32vbs, heres[1]->BSIM3v32vbs}, vbs);
  vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32vbd, heres[1]->BSIM3v32vbd}, vbd);
  vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32vgs, heres[1]->BSIM3v32vgs}, vgs);
  vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32vds, heres[1]->BSIM3v32vds}, vds);
  vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qdef, heres[1]->BSIM3v32qdef}, qdef);
  if (!ChargeComputationNeeded)
    goto line850;

  line755:
  if (heres[0]->BSIM3v32nqsMod)
  {
    qcheq = -(qbulk + qgate);
    {
      Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb}));
      heres[0]->BSIM3v32cqgb = val[0];
      heres[1]->BSIM3v32cqgb = val[1];
    }
    {
      Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) + ((Vec2d ){heres[0]->BSIM3v32cbdb, heres[1]->BSIM3v32cbdb}));
      heres[0]->BSIM3v32cqdb = val[0];
      heres[1]->BSIM3v32cqdb = val[1];
    }
    {
      Vec2d val = -(((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) + ((Vec2d ){heres[0]->BSIM3v32cbsb, heres[1]->BSIM3v32cbsb}));
      heres[0]->BSIM3v32cqsb = val[0];
      heres[1]->BSIM3v32cqsb = val[1];
    }
    {
      Vec2d val = -((((Vec2d ){heres[0]->BSIM3v32cqgb, heres[1]->BSIM3v32cqgb}) + ((Vec2d ){heres[0]->BSIM3v32cqdb, heres[1]->BSIM3v32cqdb})) + ((Vec2d ){heres[0]->BSIM3v32cqsb, heres[1]->BSIM3v32cqsb}));
      heres[0]->BSIM3v32cqbb = val[0];
      heres[1]->BSIM3v32cqbb = val[1];
    }
    gtau_drift = vec2_fabs(((Vec2d ){heres[0]->BSIM3v32tconst, heres[1]->BSIM3v32tconst}) * qcheq) * ScalingFactor;
    T0 = vec2_SIMDTOVECTOR(pParam->BSIM3v32leffCV * pParam->BSIM3v32leffCV);
    gtau_diff = (((16.0 * ((Vec2d ){heres[0]->BSIM3v32u0temp, heres[1]->BSIM3v32u0temp})) * model->BSIM3v32vtm) / T0) * ScalingFactor;
    {
      Vec2d val = gtau_drift + gtau_diff;
      heres[0]->BSIM3v32gtau = val[0];
      heres[1]->BSIM3v32gtau = val[1];
    }
  }


  if (model->BSIM3v32capMod == 0)
  {
    cgdo = vec2_SIMDTOVECTOR(pParam->BSIM3v32cgdo);
    qgdo = pParam->BSIM3v32cgdo * vgd;
    cgso = vec2_SIMDTOVECTOR(pParam->BSIM3v32cgso);
    qgso = pParam->BSIM3v32cgso * vgs;
  }
  else
    if (model->BSIM3v32capMod == 1)
  {
    if (1)
    {
      Vec2m condmask0 = vgd < 0.0;
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        T1 = vec2_blend(T1, vec2_sqrt(1.0 - ((4.0 * vgd) / pParam->BSIM3v32ckappa)), condmask_true0);
        cgdo = vec2_blend(cgdo, pParam->BSIM3v32cgdo + ((pParam->BSIM3v32weffCV * pParam->BSIM3v32cgdl) / T1), condmask_true0);
        qgdo = vec2_blend(qgdo, (pParam->BSIM3v32cgdo * vgd) - ((((pParam->BSIM3v32weffCV * 0.5) * pParam->BSIM3v32cgdl) * pParam->BSIM3v32ckappa) * (T1 - 1.0)), condmask_true0);
      }
      {
        cgdo = vec2_blend(cgdo, vec2_SIMDTOVECTOR(pParam->BSIM3v32cgdo + (pParam->BSIM3v32weffCV * pParam->BSIM3v32cgdl)), condmask_false0);
        qgdo = vec2_blend(qgdo, ((pParam->BSIM3v32weffCV * pParam->BSIM3v32cgdl) + pParam->BSIM3v32cgdo) * vgd, condmask_false0);
      }
    }

    if (1)
    {
      Vec2m condmask0 = vgs < 0.0;
      Vec2m condmask_true0 = condmask0;
      Vec2m condmask_false0 = ~condmask0;
      {
        T1 = vec2_blend(T1, vec2_sqrt(1.0 - ((4.0 * vgs) / pParam->BSIM3v32ckappa)), condmask_true0);
        cgso = vec2_blend(cgso, pParam->BSIM3v32cgso + ((pParam->BSIM3v32weffCV * pParam->BSIM3v32cgsl) / T1), condmask_true0);
        qgso = vec2_blend(qgso, (pParam->BSIM3v32cgso * vgs) - ((((pParam->BSIM3v32weffCV * 0.5) * pParam->BSIM3v32cgsl) * pParam->BSIM3v32ckappa) * (T1 - 1.0)), condmask_true0);
      }
      {
        cgso = vec2_blend(cgso, vec2_SIMDTOVECTOR(pParam->BSIM3v32cgso + (pParam->BSIM3v32weffCV * pParam->BSIM3v32cgsl)), condmask_false0);
        qgso = vec2_blend(qgso, ((pParam->BSIM3v32weffCV * pParam->BSIM3v32cgsl) + pParam->BSIM3v32cgso) * vgs, condmask_false0);
      }
    }

  }
  else
  {
    T0 = vgd + DELTA_1;
    T1 = vec2_sqrt((T0 * T0) + (4.0 * DELTA_1));
    T2 = 0.5 * (T0 - T1);
    T3 = vec2_SIMDTOVECTOR(pParam->BSIM3v32weffCV * pParam->BSIM3v32cgdl);
    T4 = vec2_sqrt(1.0 - ((4.0 * T2) / pParam->BSIM3v32ckappa));
    cgdo = (pParam->BSIM3v32cgdo + T3) - ((T3 * (1.0 - (1.0 / T4))) * (0.5 - ((0.5 * T0) / T1)));
    qgdo = ((pParam->BSIM3v32cgdo + T3) * vgd) - (T3 * (T2 + ((0.5 * pParam->BSIM3v32ckappa) * (T4 - 1.0))));
    T0 = vgs + DELTA_1;
    T1 = vec2_sqrt((T0 * T0) + (4.0 * DELTA_1));
    T2 = 0.5 * (T0 - T1);
    T3 = vec2_SIMDTOVECTOR(pParam->BSIM3v32weffCV * pParam->BSIM3v32cgsl);
    T4 = vec2_sqrt(1.0 - ((4.0 * T2) / pParam->BSIM3v32ckappa));
    cgso = (pParam->BSIM3v32cgso + T3) - ((T3 * (1.0 - (1.0 / T4))) * (0.5 - ((0.5 * T0) / T1)));
    qgso = ((pParam->BSIM3v32cgso + T3) * vgs) - (T3 * (T2 + ((0.5 * pParam->BSIM3v32ckappa) * (T4 - 1.0))));
  }


  {
    heres[0]->BSIM3v32cgdo = cgdo[0];
    heres[1]->BSIM3v32cgdo = cgdo[1];
  }
  {
    heres[0]->BSIM3v32cgso = cgso[0];
    heres[1]->BSIM3v32cgso = cgso[1];
  }
  ag0 = ckt->CKTag[0];
  ddxpart_dVd = (ddxpart_dVg = (ddxpart_dVb = (ddxpart_dVs = vec2_SIMDTOVECTOR(0.0))));
  dsxpart_dVd = (dsxpart_dVg = (dsxpart_dVb = (dsxpart_dVs = vec2_SIMDTOVECTOR(0.0))));
  ggtg = (ggtd = (ggtb = (ggts = vec2_SIMDTOVECTOR(0.0))));
  if (1)
  {
    Vec2m condmask0 = BSIM3v32mode;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      if (heres[0]->BSIM3v32nqsMod == 0)
      {
        gcggb = vec2_blend(gcggb, (((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + cgdo) + cgso) + pParam->BSIM3v32cgbo) * ag0, condmask_true0);
        gcgdb = vec2_blend(gcgdb, (((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) - cgdo) * ag0, condmask_true0);
        gcgsb = vec2_blend(gcgsb, (((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) - cgso) * ag0, condmask_true0);
        gcdgb = vec2_blend(gcdgb, (((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}) - cgdo) * ag0, condmask_true0);
        gcddb = vec2_blend(gcddb, ((((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}) + ((Vec2d ){heres[0]->BSIM3v32capbd, heres[1]->BSIM3v32capbd})) + cgdo) * ag0, condmask_true0);
        gcdsb = vec2_blend(gcdsb, ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb}) * ag0, condmask_true0);
        gcsgb = vec2_blend(gcsgb, (-(((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb})) + ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb})) + cgso)) * ag0, condmask_true0);
        gcsdb = vec2_blend(gcsdb, (-((((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) + ((Vec2d ){heres[0]->BSIM3v32cbdb, heres[1]->BSIM3v32cbdb})) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}))) * ag0, condmask_true0);
        gcssb = vec2_blend(gcssb, ((((Vec2d ){heres[0]->BSIM3v32capbs, heres[1]->BSIM3v32capbs}) + cgso) - ((((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) + ((Vec2d ){heres[0]->BSIM3v32cbsb, heres[1]->BSIM3v32cbsb})) + ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb}))) * ag0, condmask_true0);
        gcbgb = vec2_blend(gcbgb, (((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb}) - pParam->BSIM3v32cgbo) * ag0, condmask_true0);
        gcbdb = vec2_blend(gcbdb, (((Vec2d ){heres[0]->BSIM3v32cbdb, heres[1]->BSIM3v32cbdb}) - ((Vec2d ){heres[0]->BSIM3v32capbd, heres[1]->BSIM3v32capbd})) * ag0, condmask_true0);
        gcbsb = vec2_blend(gcbsb, (((Vec2d ){heres[0]->BSIM3v32cbsb, heres[1]->BSIM3v32cbsb}) - ((Vec2d ){heres[0]->BSIM3v32capbs, heres[1]->BSIM3v32capbs})) * ag0, condmask_true0);
        qgd = vec2_blend(qgd, qgdo, condmask_true0);
        qgs = vec2_blend(qgs, qgso, condmask_true0);
        qgb = vec2_blend(qgb, pParam->BSIM3v32cgbo * vgb, condmask_true0);
        qgate = vec2_blend(qgate, qgate + ((qgd + qgs) + qgb), condmask_true0);
        qbulk = vec2_blend(qbulk, qbulk - qgb, condmask_true0);
        qdrn = vec2_blend(qdrn, qdrn - qgd, condmask_true0);
        qsrc = vec2_blend(qsrc, -((qgate + qbulk) + qdrn), condmask_true0);
        sxpart = vec2_blend(sxpart, vec2_SIMDTOVECTOR(0.6), condmask_true0);
        dxpart = vec2_blend(dxpart, vec2_SIMDTOVECTOR(0.4), condmask_true0);
      }
      else
      {
        if (1)
        {
          Vec2m condmask1 = qcheq > 0.0;
          Vec2m condmask_true1 = condmask_true0 & condmask1;
          Vec2m condmask_false1 = condmask_true0 & (~condmask1);
          T0 = vec2_blend(T0, (((Vec2d ){heres[0]->BSIM3v32tconst, heres[1]->BSIM3v32tconst}) * qdef) * ScalingFactor, condmask_true1);
          T0 = vec2_blend(T0, ((-((Vec2d ){heres[0]->BSIM3v32tconst, heres[1]->BSIM3v32tconst})) * qdef) * ScalingFactor, condmask_false1);
        }

        ggtg = vec2_blend(ggtg, T0 * ((Vec2d ){heres[0]->BSIM3v32cqgb, heres[1]->BSIM3v32cqgb}), condmask_true0);
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32gtg = ggtg[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32gtg = ggtg[1];

        }
        ggtd = vec2_blend(ggtd, T0 * ((Vec2d ){heres[0]->BSIM3v32cqdb, heres[1]->BSIM3v32cqdb}), condmask_true0);
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32gtd = ggtd[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32gtd = ggtd[1];

        }
        ggts = vec2_blend(ggts, T0 * ((Vec2d ){heres[0]->BSIM3v32cqsb, heres[1]->BSIM3v32cqsb}), condmask_true0);
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32gts = ggts[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32gts = ggts[1];

        }
        ggtb = vec2_blend(ggtb, T0 * ((Vec2d ){heres[0]->BSIM3v32cqbb, heres[1]->BSIM3v32cqbb}), condmask_true0);
        {
          if (condmask_true0[0])
            heres[0]->BSIM3v32gtb = ggtb[0];

          if (condmask_true0[1])
            heres[1]->BSIM3v32gtb = ggtb[1];

        }
        gqdef = vec2_blend(gqdef, vec2_SIMDTOVECTOR(ScalingFactor * ag0), condmask_true0);
        gcqgb = vec2_blend(gcqgb, ((Vec2d ){heres[0]->BSIM3v32cqgb, heres[1]->BSIM3v32cqgb}) * ag0, condmask_true0);
        gcqdb = vec2_blend(gcqdb, ((Vec2d ){heres[0]->BSIM3v32cqdb, heres[1]->BSIM3v32cqdb}) * ag0, condmask_true0);
        gcqsb = vec2_blend(gcqsb, ((Vec2d ){heres[0]->BSIM3v32cqsb, heres[1]->BSIM3v32cqsb}) * ag0, condmask_true0);
        gcqbb = vec2_blend(gcqbb, ((Vec2d ){heres[0]->BSIM3v32cqbb, heres[1]->BSIM3v32cqbb}) * ag0, condmask_true0);
        gcggb = vec2_blend(gcggb, ((cgdo + cgso) + pParam->BSIM3v32cgbo) * ag0, condmask_true0);
        gcgdb = vec2_blend(gcgdb, (-cgdo) * ag0, condmask_true0);
        gcgsb = vec2_blend(gcgsb, (-cgso) * ag0, condmask_true0);
        gcdgb = vec2_blend(gcdgb, (-cgdo) * ag0, condmask_true0);
        gcddb = vec2_blend(gcddb, (((Vec2d ){heres[0]->BSIM3v32capbd, heres[1]->BSIM3v32capbd}) + cgdo) * ag0, condmask_true0);
        gcdsb = vec2_blend(gcdsb, vec2_SIMDTOVECTOR(0.0), condmask_true0);
        gcsgb = vec2_blend(gcsgb, (-cgso) * ag0, condmask_true0);
        gcsdb = vec2_blend(gcsdb, vec2_SIMDTOVECTOR(0.0), condmask_true0);
        gcssb = vec2_blend(gcssb, (((Vec2d ){heres[0]->BSIM3v32capbs, heres[1]->BSIM3v32capbs}) + cgso) * ag0, condmask_true0);
        gcbgb = vec2_blend(gcbgb, vec2_SIMDTOVECTOR((-pParam->BSIM3v32cgbo) * ag0), condmask_true0);
        gcbdb = vec2_blend(gcbdb, (-((Vec2d ){heres[0]->BSIM3v32capbd, heres[1]->BSIM3v32capbd})) * ag0, condmask_true0);
        gcbsb = vec2_blend(gcbsb, (-((Vec2d ){heres[0]->BSIM3v32capbs, heres[1]->BSIM3v32capbs})) * ag0, condmask_true0);
        if (1)
        {
          Vec2m condmask1 = vec2_fabs(qcheq) <= (1.0e-5 * CoxWL);
          Vec2m condmask_true1 = condmask_true0 & condmask1;
          Vec2m condmask_false1 = condmask_true0 & (~condmask1);
          {
            if (model->BSIM3v32xpart < 0.5)
            {
              dxpart = vec2_blend(dxpart, vec2_SIMDTOVECTOR(0.4), condmask_true1);
            }
            else
              if (model->BSIM3v32xpart > 0.5)
            {
              dxpart = vec2_blend(dxpart, vec2_SIMDTOVECTOR(0.0), condmask_true1);
            }
            else
            {
              dxpart = vec2_blend(dxpart, vec2_SIMDTOVECTOR(0.5), condmask_true1);
            }


          }
          {
            dxpart = vec2_blend(dxpart, qdrn / qcheq, condmask_false1);
            Cdd = vec2_blend(Cdd, (Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}, condmask_false1);
            Csd = vec2_blend(Csd, -((((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb})) + ((Vec2d ){heres[0]->BSIM3v32cbdb, heres[1]->BSIM3v32cbdb})), condmask_false1);
            ddxpart_dVd = vec2_blend(ddxpart_dVd, (Cdd - (dxpart * (Cdd + Csd))) / qcheq, condmask_false1);
            Cdg = vec2_blend(Cdg, (Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}, condmask_false1);
            Csg = vec2_blend(Csg, -((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb})) + ((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb})), condmask_false1);
            ddxpart_dVg = vec2_blend(ddxpart_dVg, (Cdg - (dxpart * (Cdg + Csg))) / qcheq, condmask_false1);
            Cds = vec2_blend(Cds, (Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb}, condmask_false1);
            Css = vec2_blend(Css, -((((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) + ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb})) + ((Vec2d ){heres[0]->BSIM3v32cbsb, heres[1]->BSIM3v32cbsb})), condmask_false1);
            ddxpart_dVs = vec2_blend(ddxpart_dVs, (Cds - (dxpart * (Cds + Css))) / qcheq, condmask_false1);
            ddxpart_dVb = vec2_blend(ddxpart_dVb, -((ddxpart_dVd + ddxpart_dVg) + ddxpart_dVs), condmask_false1);
          }
        }

        sxpart = vec2_blend(sxpart, 1.0 - dxpart, condmask_true0);
        dsxpart_dVd = vec2_blend(dsxpart_dVd, -ddxpart_dVd, condmask_true0);
        dsxpart_dVg = vec2_blend(dsxpart_dVg, -ddxpart_dVg, condmask_true0);
        dsxpart_dVs = vec2_blend(dsxpart_dVs, -ddxpart_dVs, condmask_true0);
        dsxpart_dVb = vec2_blend(dsxpart_dVb, -((dsxpart_dVd + dsxpart_dVg) + dsxpart_dVs), condmask_true0);
        qgd = vec2_blend(qgd, qgdo, condmask_true0);
        qgs = vec2_blend(qgs, qgso, condmask_true0);
        qgb = vec2_blend(qgb, pParam->BSIM3v32cgbo * vgb, condmask_true0);
        qgate = vec2_blend(qgate, (qgd + qgs) + qgb, condmask_true0);
        qbulk = vec2_blend(qbulk, -qgb, condmask_true0);
        qdrn = vec2_blend(qdrn, -qgd, condmask_true0);
        qsrc = vec2_blend(qsrc, -((qgate + qbulk) + qdrn), condmask_true0);
      }

    }
    {
      if (heres[0]->BSIM3v32nqsMod == 0)
      {
        gcggb = vec2_blend(gcggb, (((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + cgdo) + cgso) + pParam->BSIM3v32cgbo) * ag0, condmask_false0);
        gcgdb = vec2_blend(gcgdb, (((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) - cgdo) * ag0, condmask_false0);
        gcgsb = vec2_blend(gcgsb, (((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) - cgso) * ag0, condmask_false0);
        gcdgb = vec2_blend(gcdgb, (-(((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb})) + ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb})) + cgdo)) * ag0, condmask_false0);
        gcddb = vec2_blend(gcddb, ((((Vec2d ){heres[0]->BSIM3v32capbd, heres[1]->BSIM3v32capbd}) + cgdo) - ((((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) + ((Vec2d ){heres[0]->BSIM3v32cbsb, heres[1]->BSIM3v32cbsb})) + ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb}))) * ag0, condmask_false0);
        gcdsb = vec2_blend(gcdsb, (-((((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) + ((Vec2d ){heres[0]->BSIM3v32cbdb, heres[1]->BSIM3v32cbdb})) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}))) * ag0, condmask_false0);
        gcsgb = vec2_blend(gcsgb, (((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}) - cgso) * ag0, condmask_false0);
        gcsdb = vec2_blend(gcsdb, ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb}) * ag0, condmask_false0);
        gcssb = vec2_blend(gcssb, ((((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}) + ((Vec2d ){heres[0]->BSIM3v32capbs, heres[1]->BSIM3v32capbs})) + cgso) * ag0, condmask_false0);
        gcbgb = vec2_blend(gcbgb, (((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb}) - pParam->BSIM3v32cgbo) * ag0, condmask_false0);
        gcbdb = vec2_blend(gcbdb, (((Vec2d ){heres[0]->BSIM3v32cbsb, heres[1]->BSIM3v32cbsb}) - ((Vec2d ){heres[0]->BSIM3v32capbd, heres[1]->BSIM3v32capbd})) * ag0, condmask_false0);
        gcbsb = vec2_blend(gcbsb, (((Vec2d ){heres[0]->BSIM3v32cbdb, heres[1]->BSIM3v32cbdb}) - ((Vec2d ){heres[0]->BSIM3v32capbs, heres[1]->BSIM3v32capbs})) * ag0, condmask_false0);
        qgd = vec2_blend(qgd, qgdo, condmask_false0);
        qgs = vec2_blend(qgs, qgso, condmask_false0);
        qgb = vec2_blend(qgb, pParam->BSIM3v32cgbo * vgb, condmask_false0);
        qgate = vec2_blend(qgate, qgate + ((qgd + qgs) + qgb), condmask_false0);
        qbulk = vec2_blend(qbulk, qbulk - qgb, condmask_false0);
        qsrc = vec2_blend(qsrc, qdrn - qgs, condmask_false0);
        qdrn = vec2_blend(qdrn, -((qgate + qbulk) + qsrc), condmask_false0);
        sxpart = vec2_blend(sxpart, vec2_SIMDTOVECTOR(0.4), condmask_false0);
        dxpart = vec2_blend(dxpart, vec2_SIMDTOVECTOR(0.6), condmask_false0);
      }
      else
      {
        if (1)
        {
          Vec2m condmask1 = qcheq > 0.0;
          Vec2m condmask_true1 = condmask_false0 & condmask1;
          Vec2m condmask_false1 = condmask_false0 & (~condmask1);
          T0 = vec2_blend(T0, (((Vec2d ){heres[0]->BSIM3v32tconst, heres[1]->BSIM3v32tconst}) * qdef) * ScalingFactor, condmask_true1);
          T0 = vec2_blend(T0, ((-((Vec2d ){heres[0]->BSIM3v32tconst, heres[1]->BSIM3v32tconst})) * qdef) * ScalingFactor, condmask_false1);
        }

        ggtg = vec2_blend(ggtg, T0 * ((Vec2d ){heres[0]->BSIM3v32cqgb, heres[1]->BSIM3v32cqgb}), condmask_false0);
        {
          if (condmask_false0[0])
            heres[0]->BSIM3v32gtg = ggtg[0];

          if (condmask_false0[1])
            heres[1]->BSIM3v32gtg = ggtg[1];

        }
        ggts = vec2_blend(ggts, T0 * ((Vec2d ){heres[0]->BSIM3v32cqdb, heres[1]->BSIM3v32cqdb}), condmask_false0);
        {
          if (condmask_false0[0])
            heres[0]->BSIM3v32gtd = ggts[0];

          if (condmask_false0[1])
            heres[1]->BSIM3v32gtd = ggts[1];

        }
        ggtd = vec2_blend(ggtd, T0 * ((Vec2d ){heres[0]->BSIM3v32cqsb, heres[1]->BSIM3v32cqsb}), condmask_false0);
        {
          if (condmask_false0[0])
            heres[0]->BSIM3v32gts = ggtd[0];

          if (condmask_false0[1])
            heres[1]->BSIM3v32gts = ggtd[1];

        }
        ggtb = vec2_blend(ggtb, T0 * ((Vec2d ){heres[0]->BSIM3v32cqbb, heres[1]->BSIM3v32cqbb}), condmask_false0);
        {
          if (condmask_false0[0])
            heres[0]->BSIM3v32gtb = ggtb[0];

          if (condmask_false0[1])
            heres[1]->BSIM3v32gtb = ggtb[1];

        }
        gqdef = vec2_blend(gqdef, vec2_SIMDTOVECTOR(ScalingFactor * ag0), condmask_false0);
        gcqgb = vec2_blend(gcqgb, ((Vec2d ){heres[0]->BSIM3v32cqgb, heres[1]->BSIM3v32cqgb}) * ag0, condmask_false0);
        gcqdb = vec2_blend(gcqdb, ((Vec2d ){heres[0]->BSIM3v32cqsb, heres[1]->BSIM3v32cqsb}) * ag0, condmask_false0);
        gcqsb = vec2_blend(gcqsb, ((Vec2d ){heres[0]->BSIM3v32cqdb, heres[1]->BSIM3v32cqdb}) * ag0, condmask_false0);
        gcqbb = vec2_blend(gcqbb, ((Vec2d ){heres[0]->BSIM3v32cqbb, heres[1]->BSIM3v32cqbb}) * ag0, condmask_false0);
        gcggb = vec2_blend(gcggb, ((cgdo + cgso) + pParam->BSIM3v32cgbo) * ag0, condmask_false0);
        gcgdb = vec2_blend(gcgdb, (-cgdo) * ag0, condmask_false0);
        gcgsb = vec2_blend(gcgsb, (-cgso) * ag0, condmask_false0);
        gcdgb = vec2_blend(gcdgb, (-cgdo) * ag0, condmask_false0);
        gcddb = vec2_blend(gcddb, (((Vec2d ){heres[0]->BSIM3v32capbd, heres[1]->BSIM3v32capbd}) + cgdo) * ag0, condmask_false0);
        gcdsb = vec2_blend(gcdsb, vec2_SIMDTOVECTOR(0.0), condmask_false0);
        gcsgb = vec2_blend(gcsgb, (-cgso) * ag0, condmask_false0);
        gcsdb = vec2_blend(gcsdb, vec2_SIMDTOVECTOR(0.0), condmask_false0);
        gcssb = vec2_blend(gcssb, (((Vec2d ){heres[0]->BSIM3v32capbs, heres[1]->BSIM3v32capbs}) + cgso) * ag0, condmask_false0);
        gcbgb = vec2_blend(gcbgb, vec2_SIMDTOVECTOR((-pParam->BSIM3v32cgbo) * ag0), condmask_false0);
        gcbdb = vec2_blend(gcbdb, (-((Vec2d ){heres[0]->BSIM3v32capbd, heres[1]->BSIM3v32capbd})) * ag0, condmask_false0);
        gcbsb = vec2_blend(gcbsb, (-((Vec2d ){heres[0]->BSIM3v32capbs, heres[1]->BSIM3v32capbs})) * ag0, condmask_false0);
        if (1)
        {
          Vec2m condmask1 = vec2_fabs(qcheq) <= (1.0e-5 * CoxWL);
          Vec2m condmask_true1 = condmask_false0 & condmask1;
          Vec2m condmask_false1 = condmask_false0 & (~condmask1);
          {
            if (model->BSIM3v32xpart < 0.5)
            {
              sxpart = vec2_blend(sxpart, vec2_SIMDTOVECTOR(0.4), condmask_true1);
            }
            else
              if (model->BSIM3v32xpart > 0.5)
            {
              sxpart = vec2_blend(sxpart, vec2_SIMDTOVECTOR(0.0), condmask_true1);
            }
            else
            {
              sxpart = vec2_blend(sxpart, vec2_SIMDTOVECTOR(0.5), condmask_true1);
            }


          }
          {
            sxpart = vec2_blend(sxpart, qdrn / qcheq, condmask_false1);
            Css = vec2_blend(Css, (Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb}, condmask_false1);
            Cds = vec2_blend(Cds, -((((Vec2d ){heres[0]->BSIM3v32cgdb, heres[1]->BSIM3v32cgdb}) + ((Vec2d ){heres[0]->BSIM3v32cddb, heres[1]->BSIM3v32cddb})) + ((Vec2d ){heres[0]->BSIM3v32cbdb, heres[1]->BSIM3v32cbdb})), condmask_false1);
            dsxpart_dVs = vec2_blend(dsxpart_dVs, (Css - (sxpart * (Css + Cds))) / qcheq, condmask_false1);
            Csg = vec2_blend(Csg, (Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb}, condmask_false1);
            Cdg = vec2_blend(Cdg, -((((Vec2d ){heres[0]->BSIM3v32cggb, heres[1]->BSIM3v32cggb}) + ((Vec2d ){heres[0]->BSIM3v32cdgb, heres[1]->BSIM3v32cdgb})) + ((Vec2d ){heres[0]->BSIM3v32cbgb, heres[1]->BSIM3v32cbgb})), condmask_false1);
            dsxpart_dVg = vec2_blend(dsxpart_dVg, (Csg - (sxpart * (Csg + Cdg))) / qcheq, condmask_false1);
            Csd = vec2_blend(Csd, (Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb}, condmask_false1);
            Cdd = vec2_blend(Cdd, -((((Vec2d ){heres[0]->BSIM3v32cgsb, heres[1]->BSIM3v32cgsb}) + ((Vec2d ){heres[0]->BSIM3v32cdsb, heres[1]->BSIM3v32cdsb})) + ((Vec2d ){heres[0]->BSIM3v32cbsb, heres[1]->BSIM3v32cbsb})), condmask_false1);
            dsxpart_dVd = vec2_blend(dsxpart_dVd, (Csd - (sxpart * (Csd + Cdd))) / qcheq, condmask_false1);
            dsxpart_dVb = vec2_blend(dsxpart_dVb, -((dsxpart_dVd + dsxpart_dVg) + dsxpart_dVs), condmask_false1);
          }
        }

        dxpart = vec2_blend(dxpart, 1.0 - sxpart, condmask_false0);
        ddxpart_dVd = vec2_blend(ddxpart_dVd, -dsxpart_dVd, condmask_false0);
        ddxpart_dVg = vec2_blend(ddxpart_dVg, -dsxpart_dVg, condmask_false0);
        ddxpart_dVs = vec2_blend(ddxpart_dVs, -dsxpart_dVs, condmask_false0);
        ddxpart_dVb = vec2_blend(ddxpart_dVb, -((ddxpart_dVd + ddxpart_dVg) + ddxpart_dVs), condmask_false0);
        qgd = vec2_blend(qgd, qgdo, condmask_false0);
        qgs = vec2_blend(qgs, qgso, condmask_false0);
        qgb = vec2_blend(qgb, pParam->BSIM3v32cgbo * vgb, condmask_false0);
        qgate = vec2_blend(qgate, (qgd + qgs) + qgb, condmask_false0);
        qbulk = vec2_blend(qbulk, -qgb, condmask_false0);
        qsrc = vec2_blend(qsrc, -qgs, condmask_false0);
        qdrn = vec2_blend(qdrn, -((qgate + qbulk) + qsrc), condmask_false0);
      }

    }
  }

  cqdef = (cqcheq = vec2_SIMDTOVECTOR(0.0));
  vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qg, heres[1]->BSIM3v32qg}, qgate);
  vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qd, heres[1]->BSIM3v32qd}, qdrn - vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qbd, heres[1]->BSIM3v32qbd}));
  vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qb, heres[1]->BSIM3v32qb}, (qbulk + vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qbd, heres[1]->BSIM3v32qbd})) + vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qbs, heres[1]->BSIM3v32qbs}));
  if (heres[0]->BSIM3v32nqsMod)
  {
    vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qcdump, heres[1]->BSIM3v32qcdump}, qdef * ScalingFactor);
    vec2_BSIM3v32_StateStore(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qcheq, heres[1]->BSIM3v32qcheq}, qcheq);
  }

  if (ckt->CKTmode & MODEINITSMSIG)
  {
    goto line1000;
  }

  if (!ChargeComputationNeeded)
    goto line850;

  if (ckt->CKTmode & MODEINITTRAN)
  {
    vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32qb, heres[1]->BSIM3v32qb}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qb, heres[1]->BSIM3v32qb}));
    vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32qg, heres[1]->BSIM3v32qg}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qg, heres[1]->BSIM3v32qg}));
    vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32qd, heres[1]->BSIM3v32qd}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qd, heres[1]->BSIM3v32qd}));
    if (heres[0]->BSIM3v32nqsMod)
    {
      vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32qcheq, heres[1]->BSIM3v32qcheq}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qcheq, heres[1]->BSIM3v32qcheq}));
      vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32qcdump, heres[1]->BSIM3v32qcdump}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32qcdump, heres[1]->BSIM3v32qcdump}));
    }

  }

  error = vec2_NIintegrate(ckt, &geq, &ceq, 0.0, (Vec2m ){heres[0]->BSIM3v32qb, heres[1]->BSIM3v32qb});
  if (SIMDANY(error))
    return error;

  error = vec2_NIintegrate(ckt, &geq, &ceq, 0.0, (Vec2m ){heres[0]->BSIM3v32qg, heres[1]->BSIM3v32qg});
  if (SIMDANY(error))
    return error;

  error = vec2_NIintegrate(ckt, &geq, &ceq, 0.0, (Vec2m ){heres[0]->BSIM3v32qd, heres[1]->BSIM3v32qd});
  if (SIMDANY(error))
    return error;

  if (heres[0]->BSIM3v32nqsMod)
  {
    error = vec2_NIintegrate(ckt, &geq, &ceq, 0.0, (Vec2m ){heres[0]->BSIM3v32qcdump, heres[1]->BSIM3v32qcdump});
    if (SIMDANY(error))
      return error;

    error = vec2_NIintegrate(ckt, &geq, &ceq, 0.0, (Vec2m ){heres[0]->BSIM3v32qcheq, heres[1]->BSIM3v32qcheq});
    if (SIMDANY(error))
      return error;

  }

  goto line860;
  line850:
  ceqqg = (ceqqb = (ceqqd = vec2_SIMDTOVECTOR(0.0)));

  cqcheq = (cqdef = vec2_SIMDTOVECTOR(0.0));
  gcdgb = (gcddb = (gcdsb = vec2_SIMDTOVECTOR(0.0)));
  gcsgb = (gcsdb = (gcssb = vec2_SIMDTOVECTOR(0.0)));
  gcggb = (gcgdb = (gcgsb = vec2_SIMDTOVECTOR(0.0)));
  gcbgb = (gcbdb = (gcbsb = vec2_SIMDTOVECTOR(0.0)));
  gqdef = (gcqgb = (gcqdb = (gcqsb = (gcqbb = vec2_SIMDTOVECTOR(0.0)))));
  ggtg = (ggtd = (ggtb = (ggts = vec2_SIMDTOVECTOR(0.0))));
  dxpart = vec2_SIMDTOVECTOR(0.6);
  if (1)
  {
    Vec2m condmask0 = BSIM3v32mode;
    Vec2m condmask_true0 = condmask0;
    dxpart = vec2_blend(dxpart, vec2_SIMDTOVECTOR(0.4), condmask_true0);
  }

  sxpart = 1.0 - dxpart;
  ddxpart_dVd = (ddxpart_dVg = (ddxpart_dVb = (ddxpart_dVs = vec2_SIMDTOVECTOR(0.0))));
  dsxpart_dVd = (dsxpart_dVg = (dsxpart_dVb = (dsxpart_dVs = vec2_SIMDTOVECTOR(0.0))));
  if (heres[0]->BSIM3v32nqsMod)
  {
    Vec2d val = ((((16.0 * ((Vec2d ){heres[0]->BSIM3v32u0temp, heres[1]->BSIM3v32u0temp})) * model->BSIM3v32vtm) / pParam->BSIM3v32leffCV) / pParam->BSIM3v32leffCV) * ScalingFactor;
    heres[0]->BSIM3v32gtau = val[0];
    heres[1]->BSIM3v32gtau = val[1];
  }
  else
  {
    heres[0]->BSIM3v32gtau = 0.0;
    heres[1]->BSIM3v32gtau = 0.0;
  }

  goto line900;
  line860:
  cqgate = vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqg, heres[1]->BSIM3v32cqg});

  cqbulk = vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqb, heres[1]->BSIM3v32cqb});
  cqdrn = vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqd, heres[1]->BSIM3v32cqd});
  ceqqg = ((cqgate - (gcggb * vgb)) + (gcgdb * vbd)) + (gcgsb * vbs);
  ceqqb = ((cqbulk - (gcbgb * vgb)) + (gcbdb * vbd)) + (gcbsb * vbs);
  ceqqd = ((cqdrn - (gcdgb * vgb)) + (gcddb * vbd)) + (gcdsb * vbs);
  if (heres[0]->BSIM3v32nqsMod)
  {
    T0 = ((ggtg * vgb) - (ggtd * vbd)) - (ggts * vbs);
    ceqqg += T0;
    T1 = qdef * ((Vec2d ){heres[0]->BSIM3v32gtau, heres[1]->BSIM3v32gtau});
    ceqqd -= (dxpart * T0) + (T1 * (((ddxpart_dVg * vgb) - (ddxpart_dVd * vbd)) - (ddxpart_dVs * vbs)));
    cqdef = vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqcdump, heres[1]->BSIM3v32cqcdump}) - (gqdef * qdef);
    cqcheq = (vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqcheq, heres[1]->BSIM3v32cqcheq}) - (((gcqgb * vgb) - (gcqdb * vbd)) - (gcqsb * vbs))) + T0;
  }

  if (ckt->CKTmode & MODEINITTRAN)
  {
    vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32cqb, heres[1]->BSIM3v32cqb}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqb, heres[1]->BSIM3v32cqb}));
    vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32cqg, heres[1]->BSIM3v32cqg}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqg, heres[1]->BSIM3v32cqg}));
    vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32cqd, heres[1]->BSIM3v32cqd}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqd, heres[1]->BSIM3v32cqd}));
    if (heres[0]->BSIM3v32nqsMod)
    {
      vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32cqcheq, heres[1]->BSIM3v32cqcheq}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqcheq, heres[1]->BSIM3v32cqcheq}));
      vec2_BSIM3v32_StateStore(ckt->CKTstate1, (Vec2m ){heres[0]->BSIM3v32cqcdump, heres[1]->BSIM3v32cqcdump}, vec2_BSIM3v32_StateAccess(ckt->CKTstate0, (Vec2m ){heres[0]->BSIM3v32cqcdump, heres[1]->BSIM3v32cqcdump}));
    }

  }

  line900:
  ;

  if (1)
  {
    Vec2m condmask0 = BSIM3v32mode;
    Vec2m condmask_true0 = condmask0;
    Vec2m condmask_false0 = ~condmask0;
    {
      Gm = vec2_blend(Gm, (Vec2d ){heres[0]->BSIM3v32gm, heres[1]->BSIM3v32gm}, condmask_true0);
      Gmbs = vec2_blend(Gmbs, (Vec2d ){heres[0]->BSIM3v32gmbs, heres[1]->BSIM3v32gmbs}, condmask_true0);
      FwdSum = vec2_blend(FwdSum, Gm + Gmbs, condmask_true0);
      RevSum = vec2_blend(RevSum, vec2_SIMDTOVECTOR(0.0), condmask_true0);
      cdreq = vec2_blend(cdreq, model->BSIM3v32type * (((cdrain - (((Vec2d ){heres[0]->BSIM3v32gds, heres[1]->BSIM3v32gds}) * vds)) - (Gm * vgs)) - (Gmbs * vbs)), condmask_true0);
      ceqbd = vec2_blend(ceqbd, (-model->BSIM3v32type) * (((((Vec2d ){heres[0]->BSIM3v32csub, heres[1]->BSIM3v32csub}) - (((Vec2d ){heres[0]->BSIM3v32gbds, heres[1]->BSIM3v32gbds}) * vds)) - (((Vec2d ){heres[0]->BSIM3v32gbgs, heres[1]->BSIM3v32gbgs}) * vgs)) - (((Vec2d ){heres[0]->BSIM3v32gbbs, heres[1]->BSIM3v32gbbs}) * vbs)), condmask_true0);
      ceqbs = vec2_blend(ceqbs, vec2_SIMDTOVECTOR(0.0), condmask_true0);
      gbbdp = vec2_blend(gbbdp, -((Vec2d ){heres[0]->BSIM3v32gbds, heres[1]->BSIM3v32gbds}), condmask_true0);
      gbbsp = vec2_blend(gbbsp, (((Vec2d ){heres[0]->BSIM3v32gbds, heres[1]->BSIM3v32gbds}) + ((Vec2d ){heres[0]->BSIM3v32gbgs, heres[1]->BSIM3v32gbgs})) + ((Vec2d ){heres[0]->BSIM3v32gbbs, heres[1]->BSIM3v32gbbs}), condmask_true0);
      gbdpg = vec2_blend(gbdpg, (Vec2d ){heres[0]->BSIM3v32gbgs, heres[1]->BSIM3v32gbgs}, condmask_true0);
      gbdpdp = vec2_blend(gbdpdp, (Vec2d ){heres[0]->BSIM3v32gbds, heres[1]->BSIM3v32gbds}, condmask_true0);
      gbdpb = vec2_blend(gbdpb, (Vec2d ){heres[0]->BSIM3v32gbbs, heres[1]->BSIM3v32gbbs}, condmask_true0);
      gbdpsp = vec2_blend(gbdpsp, -((gbdpg + gbdpdp) + gbdpb), condmask_true0);
      gbspg = vec2_blend(gbspg, vec2_SIMDTOVECTOR(0.0), condmask_true0);
      gbspdp = vec2_blend(gbspdp, vec2_SIMDTOVECTOR(0.0), condmask_true0);
      gbspb = vec2_blend(gbspb, vec2_SIMDTOVECTOR(0.0), condmask_true0);
      gbspsp = vec2_blend(gbspsp, vec2_SIMDTOVECTOR(0.0), condmask_true0);
    }
    {
      Gm = vec2_blend(Gm, -((Vec2d ){heres[0]->BSIM3v32gm, heres[1]->BSIM3v32gm}), condmask_false0);
      Gmbs = vec2_blend(Gmbs, -((Vec2d ){heres[0]->BSIM3v32gmbs, heres[1]->BSIM3v32gmbs}), condmask_false0);
      FwdSum = vec2_blend(FwdSum, vec2_SIMDTOVECTOR(0.0), condmask_false0);
      RevSum = vec2_blend(RevSum, -(Gm + Gmbs), condmask_false0);
      cdreq = vec2_blend(cdreq, (-model->BSIM3v32type) * (((cdrain + (((Vec2d ){heres[0]->BSIM3v32gds, heres[1]->BSIM3v32gds}) * vds)) + (Gm * vgd)) + (Gmbs * vbd)), condmask_false0);
      ceqbs = vec2_blend(ceqbs, (-model->BSIM3v32type) * (((((Vec2d ){heres[0]->BSIM3v32csub, heres[1]->BSIM3v32csub}) + (((Vec2d ){heres[0]->BSIM3v32gbds, heres[1]->BSIM3v32gbds}) * vds)) - (((Vec2d ){heres[0]->BSIM3v32gbgs, heres[1]->BSIM3v32gbgs}) * vgd)) - (((Vec2d ){heres[0]->BSIM3v32gbbs, heres[1]->BSIM3v32gbbs}) * vbd)), condmask_false0);
      ceqbd = vec2_blend(ceqbd, vec2_SIMDTOVECTOR(0.0), condmask_false0);
      gbbsp = vec2_blend(gbbsp, -((Vec2d ){heres[0]->BSIM3v32gbds, heres[1]->BSIM3v32gbds}), condmask_false0);
      gbbdp = vec2_blend(gbbdp, (((Vec2d ){heres[0]->BSIM3v32gbds, heres[1]->BSIM3v32gbds}) + ((Vec2d ){heres[0]->BSIM3v32gbgs, heres[1]->BSIM3v32gbgs})) + ((Vec2d ){heres[0]->BSIM3v32gbbs, heres[1]->BSIM3v32gbbs}), condmask_false0);
      gbdpg = vec2_blend(gbdpg, vec2_SIMDTOVECTOR(0.0), condmask_false0);
      gbdpsp = vec2_blend(gbdpsp, vec2_SIMDTOVECTOR(0.0), condmask_false0);
      gbdpb = vec2_blend(gbdpb, vec2_SIMDTOVECTOR(0.0), condmask_false0);
      gbdpdp = vec2_blend(gbdpdp, vec2_SIMDTOVECTOR(0.0), condmask_false0);
      gbspg = vec2_blend(gbspg, (Vec2d ){heres[0]->BSIM3v32gbgs, heres[1]->BSIM3v32gbgs}, condmask_false0);
      gbspsp = vec2_blend(gbspsp, (Vec2d ){heres[0]->BSIM3v32gbds, heres[1]->BSIM3v32gbds}, condmask_false0);
      gbspb = vec2_blend(gbspb, (Vec2d ){heres[0]->BSIM3v32gbbs, heres[1]->BSIM3v32gbbs}, condmask_false0);
      gbspdp = vec2_blend(gbspdp, -((gbspg + gbspsp) + gbspb), condmask_false0);
    }
  }

  if (model->BSIM3v32type > 0)
  {
    ceqbs += ((Vec2d ){heres[0]->BSIM3v32cbs, heres[1]->BSIM3v32cbs}) - (((Vec2d ){heres[0]->BSIM3v32gbs, heres[1]->BSIM3v32gbs}) * vbs);
    ceqbd += ((Vec2d ){heres[0]->BSIM3v32cbd, heres[1]->BSIM3v32cbd}) - (((Vec2d ){heres[0]->BSIM3v32gbd, heres[1]->BSIM3v32gbd}) * vbd);
  }
  else
  {
    ceqbs -= ((Vec2d ){heres[0]->BSIM3v32cbs, heres[1]->BSIM3v32cbs}) - (((Vec2d ){heres[0]->BSIM3v32gbs, heres[1]->BSIM3v32gbs}) * vbs);
    ceqbd -= ((Vec2d ){heres[0]->BSIM3v32cbd, heres[1]->BSIM3v32cbd}) - (((Vec2d ){heres[0]->BSIM3v32gbd, heres[1]->BSIM3v32gbd}) * vbd);
    ceqqg = -ceqqg;
    ceqqb = -ceqqb;
    ceqqd = -ceqqd;
    cqdef = -cqdef;
    cqcheq = -cqcheq;
  }

  m = (Vec2d ){heres[0]->BSIM3v32m, heres[1]->BSIM3v32m};
  vec2_BSIM3v32_StateSub(ckt->CKTrhs, (Vec2m ){heres[0]->BSIM3v32gNode, heres[1]->BSIM3v32gNode}, m * ceqqg);
  vec2_BSIM3v32_StateSub(ckt->CKTrhs, (Vec2m ){heres[0]->BSIM3v32bNode, heres[1]->BSIM3v32bNode}, m * ((ceqbs + ceqbd) + ceqqb));
  vec2_BSIM3v32_StateAdd(ckt->CKTrhs, (Vec2m ){heres[0]->BSIM3v32dNodePrime, heres[1]->BSIM3v32dNodePrime}, m * ((ceqbd - cdreq) - ceqqd));
  vec2_BSIM3v32_StateAdd(ckt->CKTrhs, (Vec2m ){heres[0]->BSIM3v32sNodePrime, heres[1]->BSIM3v32sNodePrime}, m * ((((cdreq + ceqbs) + ceqqg) + ceqqb) + ceqqd));
  if (heres[0]->BSIM3v32nqsMod)
    vec2_BSIM3v32_StateAdd(ckt->CKTrhs, (Vec2m ){heres[0]->BSIM3v32qNode, heres[1]->BSIM3v32qNode}, m * (cqcheq - cqdef));

  T1 = qdef * ((Vec2d ){heres[0]->BSIM3v32gtau, heres[1]->BSIM3v32gtau});
  {
    Vec2d val = m * ((Vec2d ){heres[0]->BSIM3v32drainConductance, heres[1]->BSIM3v32drainConductance});
    *heres[0]->BSIM3v32DdPtr += val[0];
    *heres[1]->BSIM3v32DdPtr += val[1];
  }
  {
    Vec2d val = m * (gcggb - ggtg);
    *heres[0]->BSIM3v32GgPtr += val[0];
    *heres[1]->BSIM3v32GgPtr += val[1];
  }
  {
    Vec2d val = m * ((Vec2d ){heres[0]->BSIM3v32sourceConductance, heres[1]->BSIM3v32sourceConductance});
    *heres[0]->BSIM3v32SsPtr += val[0];
    *heres[1]->BSIM3v32SsPtr += val[1];
  }
  {
    Vec2d val = m * (((((((Vec2d ){heres[0]->BSIM3v32gbd, heres[1]->BSIM3v32gbd}) + ((Vec2d ){heres[0]->BSIM3v32gbs, heres[1]->BSIM3v32gbs})) - gcbgb) - gcbdb) - gcbsb) - ((Vec2d ){heres[0]->BSIM3v32gbbs, heres[1]->BSIM3v32gbbs}));
    *heres[0]->BSIM3v32BbPtr += val[0];
    *heres[1]->BSIM3v32BbPtr += val[1];
  }
  {
    Vec2d val = m * (((((((((Vec2d ){heres[0]->BSIM3v32drainConductance, heres[1]->BSIM3v32drainConductance}) + ((Vec2d ){heres[0]->BSIM3v32gds, heres[1]->BSIM3v32gds})) + ((Vec2d ){heres[0]->BSIM3v32gbd, heres[1]->BSIM3v32gbd})) + RevSum) + gcddb) + (dxpart * ggtd)) + (T1 * ddxpart_dVd)) + gbdpdp);
    *heres[0]->BSIM3v32DPdpPtr += val[0];
    *heres[1]->BSIM3v32DPdpPtr += val[1];
  }
  {
    Vec2d val = m * (((((((((Vec2d ){heres[0]->BSIM3v32sourceConductance, heres[1]->BSIM3v32sourceConductance}) + ((Vec2d ){heres[0]->BSIM3v32gds, heres[1]->BSIM3v32gds})) + ((Vec2d ){heres[0]->BSIM3v32gbs, heres[1]->BSIM3v32gbs})) + FwdSum) + gcssb) + (sxpart * ggts)) + (T1 * dsxpart_dVs)) + gbspsp);
    *heres[0]->BSIM3v32SPspPtr += val[0];
    *heres[1]->BSIM3v32SPspPtr += val[1];
  }
  {
    Vec2d val = m * ((Vec2d ){heres[0]->BSIM3v32drainConductance, heres[1]->BSIM3v32drainConductance});
    *heres[0]->BSIM3v32DdpPtr -= val[0];
    *heres[1]->BSIM3v32DdpPtr -= val[1];
  }
  {
    Vec2d val = m * (((gcggb + gcgdb) + gcgsb) + ggtb);
    *heres[0]->BSIM3v32GbPtr -= val[0];
    *heres[1]->BSIM3v32GbPtr -= val[1];
  }
  {
    Vec2d val = m * (gcgdb - ggtd);
    *heres[0]->BSIM3v32GdpPtr += val[0];
    *heres[1]->BSIM3v32GdpPtr += val[1];
  }
  {
    Vec2d val = m * (gcgsb - ggts);
    *heres[0]->BSIM3v32GspPtr += val[0];
    *heres[1]->BSIM3v32GspPtr += val[1];
  }
  {
    Vec2d val = m * ((Vec2d ){heres[0]->BSIM3v32sourceConductance, heres[1]->BSIM3v32sourceConductance});
    *heres[0]->BSIM3v32SspPtr -= val[0];
    *heres[1]->BSIM3v32SspPtr -= val[1];
  }
  {
    Vec2d val = m * (gcbgb - ((Vec2d ){heres[0]->BSIM3v32gbgs, heres[1]->BSIM3v32gbgs}));
    *heres[0]->BSIM3v32BgPtr += val[0];
    *heres[1]->BSIM3v32BgPtr += val[1];
  }
  {
    Vec2d val = m * ((gcbdb - ((Vec2d ){heres[0]->BSIM3v32gbd, heres[1]->BSIM3v32gbd})) + gbbdp);
    *heres[0]->BSIM3v32BdpPtr += val[0];
    *heres[1]->BSIM3v32BdpPtr += val[1];
  }
  {
    Vec2d val = m * ((gcbsb - ((Vec2d ){heres[0]->BSIM3v32gbs, heres[1]->BSIM3v32gbs})) + gbbsp);
    *heres[0]->BSIM3v32BspPtr += val[0];
    *heres[1]->BSIM3v32BspPtr += val[1];
  }
  {
    Vec2d val = m * ((Vec2d ){heres[0]->BSIM3v32drainConductance, heres[1]->BSIM3v32drainConductance});
    *heres[0]->BSIM3v32DPdPtr -= val[0];
    *heres[1]->BSIM3v32DPdPtr -= val[1];
  }
  {
    Vec2d val = m * ((((Gm + gcdgb) + (dxpart * ggtg)) + (T1 * ddxpart_dVg)) + gbdpg);
    *heres[0]->BSIM3v32DPgPtr += val[0];
    *heres[1]->BSIM3v32DPgPtr += val[1];
  }
  {
    Vec2d val = m * (((((((((Vec2d ){heres[0]->BSIM3v32gbd, heres[1]->BSIM3v32gbd}) - Gmbs) + gcdgb) + gcddb) + gcdsb) - (dxpart * ggtb)) - (T1 * ddxpart_dVb)) - gbdpb);
    *heres[0]->BSIM3v32DPbPtr -= val[0];
    *heres[1]->BSIM3v32DPbPtr -= val[1];
  }
  {
    Vec2d val = m * (((((((Vec2d ){heres[0]->BSIM3v32gds, heres[1]->BSIM3v32gds}) + FwdSum) - gcdsb) - (dxpart * ggts)) - (T1 * ddxpart_dVs)) - gbdpsp);
    *heres[0]->BSIM3v32DPspPtr -= val[0];
    *heres[1]->BSIM3v32DPspPtr -= val[1];
  }
  {
    Vec2d val = m * ((((gcsgb - Gm) + (sxpart * ggtg)) + (T1 * dsxpart_dVg)) + gbspg);
    *heres[0]->BSIM3v32SPgPtr += val[0];
    *heres[1]->BSIM3v32SPgPtr += val[1];
  }
  {
    Vec2d val = m * ((Vec2d ){heres[0]->BSIM3v32sourceConductance, heres[1]->BSIM3v32sourceConductance});
    *heres[0]->BSIM3v32SPsPtr -= val[0];
    *heres[1]->BSIM3v32SPsPtr -= val[1];
  }
  {
    Vec2d val = m * (((((((((Vec2d ){heres[0]->BSIM3v32gbs, heres[1]->BSIM3v32gbs}) + Gmbs) + gcsgb) + gcsdb) + gcssb) - (sxpart * ggtb)) - (T1 * dsxpart_dVb)) - gbspb);
    *heres[0]->BSIM3v32SPbPtr -= val[0];
    *heres[1]->BSIM3v32SPbPtr -= val[1];
  }
  {
    Vec2d val = m * (((((((Vec2d ){heres[0]->BSIM3v32gds, heres[1]->BSIM3v32gds}) + RevSum) - gcsdb) - (sxpart * ggtd)) - (T1 * dsxpart_dVd)) - gbspdp);
    *heres[0]->BSIM3v32SPdpPtr -= val[0];
    *heres[1]->BSIM3v32SPdpPtr -= val[1];
  }
  if (heres[0]->BSIM3v32nqsMod)
  {
    {
      Vec2d val = m * (gqdef + ((Vec2d ){heres[0]->BSIM3v32gtau, heres[1]->BSIM3v32gtau}));
      *heres[0]->BSIM3v32QqPtr += val[0];
      *heres[1]->BSIM3v32QqPtr += val[1];
    }
    {
      Vec2d val = m * (dxpart * ((Vec2d ){heres[0]->BSIM3v32gtau, heres[1]->BSIM3v32gtau}));
      *heres[0]->BSIM3v32DPqPtr += val[0];
      *heres[1]->BSIM3v32DPqPtr += val[1];
    }
    {
      Vec2d val = m * (sxpart * ((Vec2d ){heres[0]->BSIM3v32gtau, heres[1]->BSIM3v32gtau}));
      *heres[0]->BSIM3v32SPqPtr += val[0];
      *heres[1]->BSIM3v32SPqPtr += val[1];
    }
    {
      Vec2d val = m * ((Vec2d ){heres[0]->BSIM3v32gtau, heres[1]->BSIM3v32gtau});
      *heres[0]->BSIM3v32GqPtr -= val[0];
      *heres[1]->BSIM3v32GqPtr -= val[1];
    }
    {
      Vec2d val = m * (ggtg - gcqgb);
      *heres[0]->BSIM3v32QgPtr += val[0];
      *heres[1]->BSIM3v32QgPtr += val[1];
    }
    {
      Vec2d val = m * (ggtd - gcqdb);
      *heres[0]->BSIM3v32QdpPtr += val[0];
      *heres[1]->BSIM3v32QdpPtr += val[1];
    }
    {
      Vec2d val = m * (ggts - gcqsb);
      *heres[0]->BSIM3v32QspPtr += val[0];
      *heres[1]->BSIM3v32QspPtr += val[1];
    }
    {
      Vec2d val = m * (ggtb - gcqbb);
      *heres[0]->BSIM3v32QbPtr += val[0];
      *heres[1]->BSIM3v32QbPtr += val[1];
    }
  }

  line1000:
  ;

  return OK;
}
