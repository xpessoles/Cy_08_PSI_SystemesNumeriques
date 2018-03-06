#ifndef __c1_ascenseur_simplev2_h__
#define __c1_ascenseur_simplev2_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_SFc1_ascenseur_simplev2InstanceStruct
#define typedef_SFc1_ascenseur_simplev2InstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  uint8_T c1_tp_fonctionnement_normal;
  uint8_T c1_tp_gestion_portes;
  uint8_T c1_tp_en_cours_ouverture;
  uint8_T c1_tp_portes_ouvertes;
  uint8_T c1_tp_portes_fermees;
  uint8_T c1_tp_en_cours_fermeture;
  uint8_T c1_tp_voyant_lumineux;
  uint8_T c1_tp_voyant_allume;
  uint8_T c1_tp_voyant_eteint;
  uint8_T c1_tp_controllerAscenseur;
  uint8_T c1_tp_initialisation;
  uint8_T c1_tp_effacement_etageDemande;
  uint8_T c1_tp_memorisation;
  uint8_T c1_tp_cabine;
  uint8_T c1_tp_montee_cabine;
  uint8_T c1_tp_arret_cabine;
  uint8_T c1_tp_descente_cabine;
  boolean_T c1_isStable;
  uint8_T c1_is_active_c1_ascenseur_simplev2;
  uint8_T c1_is_c1_ascenseur_simplev2;
  uint8_T c1_is_gestion_portes;
  uint8_T c1_is_active_gestion_portes;
  uint8_T c1_is_voyant_lumineux;
  uint8_T c1_is_active_voyant_lumineux;
  uint8_T c1_is_controllerAscenseur;
  uint8_T c1_is_active_controllerAscenseur;
  uint8_T c1_is_cabine;
  uint8_T c1_is_active_cabine;
  real_T c1_etageDemande;
  real_T c1_temporalCounter_i1;
  real_T c1_presentTime;
  real_T c1_elapsedTime;
  real_T c1_previousTime;
  uint8_T c1_doSetSimStateSideEffects;
  const mxArray *c1_setSimStateSideEffectsInfo;
} SFc1_ascenseur_simplev2InstanceStruct;

#endif                                 /*typedef_SFc1_ascenseur_simplev2InstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_ascenseur_simplev2_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c1_ascenseur_simplev2_get_check_sum(mxArray *plhs[]);
extern void c1_ascenseur_simplev2_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
