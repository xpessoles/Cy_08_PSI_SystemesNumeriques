/* Include files */

#include <stddef.h>
#include "blas.h"
#include "ascenseur_simplev2_sfun.h"
#include "c1_ascenseur_simplev2.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "ascenseur_simplev2_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c1_IN_NO_ACTIVE_CHILD          ((uint8_T)0U)
#define c1_IN_fonctionnement_normal    ((uint8_T)1U)
#define c1_IN_en_cours_fermeture       ((uint8_T)1U)
#define c1_IN_en_cours_ouverture       ((uint8_T)2U)
#define c1_IN_portes_fermees           ((uint8_T)3U)
#define c1_IN_portes_ouvertes          ((uint8_T)4U)
#define c1_IN_voyant_allume            ((uint8_T)1U)
#define c1_IN_voyant_eteint            ((uint8_T)2U)
#define c1_IN_effacement_etageDemande  ((uint8_T)1U)
#define c1_IN_initialisation           ((uint8_T)2U)
#define c1_IN_memorisation             ((uint8_T)3U)
#define c1_IN_arret_cabine             ((uint8_T)1U)
#define c1_IN_descente_cabine          ((uint8_T)2U)
#define c1_IN_montee_cabine            ((uint8_T)3U)

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
static void initialize_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance);
static void initialize_params_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance);
static void enable_c1_ascenseur_simplev2(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance);
static void disable_c1_ascenseur_simplev2(SFc1_ascenseur_simplev2InstanceStruct *
  chartInstance);
static void c1_update_debugger_state_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance);
static const mxArray *get_sim_state_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance);
static void set_sim_state_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance, const mxArray *c1_st);
static void c1_set_sim_state_side_effects_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance);
static void finalize_c1_ascenseur_simplev2(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance);
static void sf_c1_ascenseur_simplev2(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance);
static void initSimStructsc1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance);
static void registerMessagesc1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance);
static void c1_fonctionnement_normal(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance);
static void c1_gestion_portes(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance);
static void c1_controllerAscenseur(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static int32_T c1_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static uint8_T c1_b_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_b_tp_fonctionnement_normal, const char_T
  *c1_identifier);
static uint8_T c1_c_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_d_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_porte, const char_T *c1_identifier);
static real_T c1_e_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_f_emlrt_marshallIn
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance, const mxArray
   *c1_b_setSimStateSideEffectsInfo, const char_T *c1_identifier);
static const mxArray *c1_g_emlrt_marshallIn
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance, const mxArray *c1_u,
   const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance)
{
  real_T *c1_porte;
  real_T *c1_etage;
  real_T *c1_led;
  real_T *c1_afficheur;
  c1_afficheur = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_led = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_etage = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_porte = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_doSetSimStateSideEffects = 0U;
  chartInstance->c1_setSimStateSideEffectsInfo = NULL;
  chartInstance->c1_tp_fonctionnement_normal = 0U;
  chartInstance->c1_is_active_cabine = 0U;
  chartInstance->c1_is_cabine = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_cabine = 0U;
  chartInstance->c1_tp_arret_cabine = 0U;
  chartInstance->c1_tp_descente_cabine = 0U;
  chartInstance->c1_tp_montee_cabine = 0U;
  chartInstance->c1_is_active_controllerAscenseur = 0U;
  chartInstance->c1_is_controllerAscenseur = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_controllerAscenseur = 0U;
  chartInstance->c1_tp_effacement_etageDemande = 0U;
  chartInstance->c1_tp_initialisation = 0U;
  chartInstance->c1_tp_memorisation = 0U;
  chartInstance->c1_is_active_gestion_portes = 0U;
  chartInstance->c1_is_gestion_portes = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_gestion_portes = 0U;
  chartInstance->c1_tp_en_cours_fermeture = 0U;
  chartInstance->c1_temporalCounter_i1 = 0.0;
  chartInstance->c1_tp_en_cours_ouverture = 0U;
  chartInstance->c1_tp_portes_fermees = 0U;
  chartInstance->c1_tp_portes_ouvertes = 0U;
  chartInstance->c1_temporalCounter_i1 = 0.0;
  chartInstance->c1_is_active_voyant_lumineux = 0U;
  chartInstance->c1_is_voyant_lumineux = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_tp_voyant_lumineux = 0U;
  chartInstance->c1_tp_voyant_allume = 0U;
  chartInstance->c1_tp_voyant_eteint = 0U;
  chartInstance->c1_is_active_c1_ascenseur_simplev2 = 0U;
  chartInstance->c1_is_c1_ascenseur_simplev2 = c1_IN_NO_ACTIVE_CHILD;
  chartInstance->c1_etageDemande = 0.0;
  if (!(cdrGetOutputPortReusable(chartInstance->S, 1) != 0)) {
    *c1_porte = 0.0;
  }

  if (!(cdrGetOutputPortReusable(chartInstance->S, 2) != 0)) {
    *c1_etage = 0.0;
  }

  if (!(cdrGetOutputPortReusable(chartInstance->S, 3) != 0)) {
    *c1_led = 0.0;
  }

  if (!(cdrGetOutputPortReusable(chartInstance->S, 4) != 0)) {
    *c1_afficheur = 0.0;
  }

  chartInstance->c1_presentTime = 0.0;
  chartInstance->c1_elapsedTime = 0.0;
  chartInstance->c1_previousTime = 0.0;
}

static void initialize_params_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance)
{
}

static void enable_c1_ascenseur_simplev2(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_presentTime = _sfTime_;
  chartInstance->c1_previousTime = chartInstance->c1_presentTime;
}

static void disable_c1_ascenseur_simplev2(SFc1_ascenseur_simplev2InstanceStruct *
  chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_presentTime = _sfTime_;
  chartInstance->c1_elapsedTime = chartInstance->c1_presentTime -
    chartInstance->c1_previousTime;
  chartInstance->c1_previousTime = chartInstance->c1_presentTime;
  chartInstance->c1_temporalCounter_i1 += chartInstance->c1_elapsedTime;
}

static void c1_update_debugger_state_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance)
{
  uint32_T c1_prevAniVal;
  c1_prevAniVal = _SFD_GET_ANIMATION();
  _SFD_SET_ANIMATION(0U);
  _SFD_SET_HONOR_BREAKPOINTS(0U);
  if (chartInstance->c1_is_active_c1_ascenseur_simplev2 == 1U) {
    _SFD_CC_CALL(CHART_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_c1_ascenseur_simplev2 == c1_IN_fonctionnement_normal)
  {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_gestion_portes == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_gestion_portes == c1_IN_en_cours_ouverture) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_gestion_portes == c1_IN_portes_ouvertes) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_gestion_portes == c1_IN_portes_fermees) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_gestion_portes == c1_IN_en_cours_fermeture) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_voyant_lumineux == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 14U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_voyant_lumineux == c1_IN_voyant_allume) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_voyant_lumineux == c1_IN_voyant_eteint) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_controllerAscenseur == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_controllerAscenseur == c1_IN_initialisation) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_controllerAscenseur == c1_IN_effacement_etageDemande)
  {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_controllerAscenseur == c1_IN_memorisation) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_active_cabine == 1U) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_cabine == c1_IN_montee_cabine) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_cabine == c1_IN_arret_cabine) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
  }

  if (chartInstance->c1_is_cabine == c1_IN_descente_cabine) {
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  } else {
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
  }

  _SFD_SET_ANIMATION(c1_prevAniVal);
  _SFD_SET_HONOR_BREAKPOINTS(1U);
  _SFD_ANIMATE();
}

static const mxArray *get_sim_state_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_c_u;
  const mxArray *c1_d_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  uint8_T c1_f_hoistedGlobal;
  uint8_T c1_f_u;
  const mxArray *c1_g_y = NULL;
  uint8_T c1_g_hoistedGlobal;
  uint8_T c1_g_u;
  const mxArray *c1_h_y = NULL;
  uint8_T c1_h_hoistedGlobal;
  uint8_T c1_h_u;
  const mxArray *c1_i_y = NULL;
  uint8_T c1_i_hoistedGlobal;
  uint8_T c1_i_u;
  const mxArray *c1_j_y = NULL;
  uint8_T c1_j_hoistedGlobal;
  uint8_T c1_j_u;
  const mxArray *c1_k_y = NULL;
  uint8_T c1_k_hoistedGlobal;
  uint8_T c1_k_u;
  const mxArray *c1_l_y = NULL;
  uint8_T c1_l_hoistedGlobal;
  uint8_T c1_l_u;
  const mxArray *c1_m_y = NULL;
  uint8_T c1_m_hoistedGlobal;
  uint8_T c1_m_u;
  const mxArray *c1_n_y = NULL;
  uint8_T c1_n_hoistedGlobal;
  uint8_T c1_n_u;
  const mxArray *c1_o_y = NULL;
  uint8_T c1_o_hoistedGlobal;
  uint8_T c1_o_u;
  const mxArray *c1_p_y = NULL;
  real_T c1_p_hoistedGlobal;
  real_T c1_p_u;
  const mxArray *c1_q_y = NULL;
  real_T c1_q_hoistedGlobal;
  real_T c1_q_u;
  const mxArray *c1_r_y = NULL;
  real_T *c1_afficheur;
  real_T *c1_etage;
  real_T *c1_led;
  real_T *c1_porte;
  c1_afficheur = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_led = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_etage = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_porte = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(17), FALSE);
  c1_hoistedGlobal = *c1_afficheur;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_etage;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_c_hoistedGlobal = *c1_led;
  c1_c_u = c1_c_hoistedGlobal;
  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_c_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_d_hoistedGlobal = *c1_porte;
  c1_d_u = c1_d_hoistedGlobal;
  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_e_hoistedGlobal = chartInstance->c1_etageDemande;
  c1_e_u = c1_e_hoistedGlobal;
  c1_f_y = NULL;
  sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_f_hoistedGlobal = chartInstance->c1_is_active_c1_ascenseur_simplev2;
  c1_f_u = c1_f_hoistedGlobal;
  c1_g_y = NULL;
  sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_g_hoistedGlobal = chartInstance->c1_is_active_gestion_portes;
  c1_g_u = c1_g_hoistedGlobal;
  c1_h_y = NULL;
  sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_g_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_h_hoistedGlobal = chartInstance->c1_is_active_voyant_lumineux;
  c1_h_u = c1_h_hoistedGlobal;
  c1_i_y = NULL;
  sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_i_hoistedGlobal = chartInstance->c1_is_active_controllerAscenseur;
  c1_i_u = c1_i_hoistedGlobal;
  c1_j_y = NULL;
  sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_i_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_j_hoistedGlobal = chartInstance->c1_is_active_cabine;
  c1_j_u = c1_j_hoistedGlobal;
  c1_k_y = NULL;
  sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_k_hoistedGlobal = chartInstance->c1_is_c1_ascenseur_simplev2;
  c1_k_u = c1_k_hoistedGlobal;
  c1_l_y = NULL;
  sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_k_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 10, c1_l_y);
  c1_l_hoistedGlobal = chartInstance->c1_is_gestion_portes;
  c1_l_u = c1_l_hoistedGlobal;
  c1_m_y = NULL;
  sf_mex_assign(&c1_m_y, sf_mex_create("y", &c1_l_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 11, c1_m_y);
  c1_m_hoistedGlobal = chartInstance->c1_is_voyant_lumineux;
  c1_m_u = c1_m_hoistedGlobal;
  c1_n_y = NULL;
  sf_mex_assign(&c1_n_y, sf_mex_create("y", &c1_m_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 12, c1_n_y);
  c1_n_hoistedGlobal = chartInstance->c1_is_controllerAscenseur;
  c1_n_u = c1_n_hoistedGlobal;
  c1_o_y = NULL;
  sf_mex_assign(&c1_o_y, sf_mex_create("y", &c1_n_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 13, c1_o_y);
  c1_o_hoistedGlobal = chartInstance->c1_is_cabine;
  c1_o_u = c1_o_hoistedGlobal;
  c1_p_y = NULL;
  sf_mex_assign(&c1_p_y, sf_mex_create("y", &c1_o_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 14, c1_p_y);
  c1_p_hoistedGlobal = chartInstance->c1_temporalCounter_i1;
  c1_p_u = c1_p_hoistedGlobal;
  c1_q_y = NULL;
  sf_mex_assign(&c1_q_y, sf_mex_create("y", &c1_p_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 15, c1_q_y);
  c1_q_hoistedGlobal = chartInstance->c1_previousTime;
  c1_q_u = c1_q_hoistedGlobal;
  c1_r_y = NULL;
  sf_mex_assign(&c1_r_y, sf_mex_create("y", &c1_q_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 16, c1_r_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_afficheur;
  real_T *c1_etage;
  real_T *c1_led;
  real_T *c1_porte;
  c1_afficheur = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_led = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_etage = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_porte = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_u = sf_mex_dup(c1_st);
  *c1_afficheur = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 0)), "afficheur");
  *c1_etage = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 1)), "etage");
  *c1_led = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    2)), "led");
  *c1_porte = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 3)), "porte");
  chartInstance->c1_etageDemande = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 4)), "etageDemande");
  chartInstance->c1_is_active_c1_ascenseur_simplev2 = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 5)),
     "is_active_c1_ascenseur_simplev2");
  chartInstance->c1_is_active_gestion_portes = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 6)),
     "is_active_gestion_portes");
  chartInstance->c1_is_active_voyant_lumineux = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 7)),
     "is_active_voyant_lumineux");
  chartInstance->c1_is_active_controllerAscenseur = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 8)),
     "is_active_controllerAscenseur");
  chartInstance->c1_is_active_cabine = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 9)), "is_active_cabine");
  chartInstance->c1_is_c1_ascenseur_simplev2 = c1_b_emlrt_marshallIn
    (chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 10)),
     "is_c1_ascenseur_simplev2");
  chartInstance->c1_is_gestion_portes = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 11)), "is_gestion_portes");
  chartInstance->c1_is_voyant_lumineux = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 12)), "is_voyant_lumineux");
  chartInstance->c1_is_controllerAscenseur = c1_b_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 13)), "is_controllerAscenseur");
  chartInstance->c1_is_cabine = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 14)), "is_cabine");
  chartInstance->c1_temporalCounter_i1 = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 15)), "temporalCounter_i1");
  chartInstance->c1_previousTime = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 16)), "previousTime");
  sf_mex_assign(&chartInstance->c1_setSimStateSideEffectsInfo,
                c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell
    (c1_u, 17)), "setSimStateSideEffectsInfo"), TRUE);
  sf_mex_destroy(&c1_u);
  chartInstance->c1_doSetSimStateSideEffects = 1U;
  c1_update_debugger_state_c1_ascenseur_simplev2(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void c1_set_sim_state_side_effects_c1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance)
{
  if (chartInstance->c1_doSetSimStateSideEffects != 0) {
    if (chartInstance->c1_is_c1_ascenseur_simplev2 ==
        c1_IN_fonctionnement_normal) {
      chartInstance->c1_tp_fonctionnement_normal = 1U;
    } else {
      chartInstance->c1_tp_fonctionnement_normal = 0U;
    }

    if (chartInstance->c1_is_active_gestion_portes == 1U) {
      chartInstance->c1_tp_gestion_portes = 1U;
    } else {
      chartInstance->c1_tp_gestion_portes = 0U;
    }

    if (chartInstance->c1_is_gestion_portes == c1_IN_en_cours_fermeture) {
      chartInstance->c1_tp_en_cours_fermeture = 1U;
      if (sf_mex_sub(chartInstance->c1_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 4) == 0.0) {
        chartInstance->c1_temporalCounter_i1 = 0.0;
      }
    } else {
      chartInstance->c1_tp_en_cours_fermeture = 0U;
    }

    if (chartInstance->c1_is_gestion_portes == c1_IN_en_cours_ouverture) {
      chartInstance->c1_tp_en_cours_ouverture = 1U;
    } else {
      chartInstance->c1_tp_en_cours_ouverture = 0U;
    }

    if (chartInstance->c1_is_gestion_portes == c1_IN_portes_fermees) {
      chartInstance->c1_tp_portes_fermees = 1U;
    } else {
      chartInstance->c1_tp_portes_fermees = 0U;
    }

    if (chartInstance->c1_is_gestion_portes == c1_IN_portes_ouvertes) {
      chartInstance->c1_tp_portes_ouvertes = 1U;
      if (sf_mex_sub(chartInstance->c1_setSimStateSideEffectsInfo,
                     "setSimStateSideEffectsInfo", 1, 7) == 0.0) {
        chartInstance->c1_temporalCounter_i1 = 0.0;
      }
    } else {
      chartInstance->c1_tp_portes_ouvertes = 0U;
    }

    if (chartInstance->c1_is_active_voyant_lumineux == 1U) {
      chartInstance->c1_tp_voyant_lumineux = 1U;
    } else {
      chartInstance->c1_tp_voyant_lumineux = 0U;
    }

    if (chartInstance->c1_is_voyant_lumineux == c1_IN_voyant_allume) {
      chartInstance->c1_tp_voyant_allume = 1U;
    } else {
      chartInstance->c1_tp_voyant_allume = 0U;
    }

    if (chartInstance->c1_is_voyant_lumineux == c1_IN_voyant_eteint) {
      chartInstance->c1_tp_voyant_eteint = 1U;
    } else {
      chartInstance->c1_tp_voyant_eteint = 0U;
    }

    if (chartInstance->c1_is_active_controllerAscenseur == 1U) {
      chartInstance->c1_tp_controllerAscenseur = 1U;
    } else {
      chartInstance->c1_tp_controllerAscenseur = 0U;
    }

    if (chartInstance->c1_is_controllerAscenseur ==
        c1_IN_effacement_etageDemande) {
      chartInstance->c1_tp_effacement_etageDemande = 1U;
    } else {
      chartInstance->c1_tp_effacement_etageDemande = 0U;
    }

    if (chartInstance->c1_is_controllerAscenseur == c1_IN_initialisation) {
      chartInstance->c1_tp_initialisation = 1U;
    } else {
      chartInstance->c1_tp_initialisation = 0U;
    }

    if (chartInstance->c1_is_controllerAscenseur == c1_IN_memorisation) {
      chartInstance->c1_tp_memorisation = 1U;
    } else {
      chartInstance->c1_tp_memorisation = 0U;
    }

    if (chartInstance->c1_is_active_cabine == 1U) {
      chartInstance->c1_tp_cabine = 1U;
    } else {
      chartInstance->c1_tp_cabine = 0U;
    }

    if (chartInstance->c1_is_cabine == c1_IN_arret_cabine) {
      chartInstance->c1_tp_arret_cabine = 1U;
    } else {
      chartInstance->c1_tp_arret_cabine = 0U;
    }

    if (chartInstance->c1_is_cabine == c1_IN_descente_cabine) {
      chartInstance->c1_tp_descente_cabine = 1U;
    } else {
      chartInstance->c1_tp_descente_cabine = 0U;
    }

    if (chartInstance->c1_is_cabine == c1_IN_montee_cabine) {
      chartInstance->c1_tp_montee_cabine = 1U;
    } else {
      chartInstance->c1_tp_montee_cabine = 0U;
    }

    chartInstance->c1_doSetSimStateSideEffects = 0U;
  }
}

static void finalize_c1_ascenseur_simplev2(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance)
{
  sf_mex_destroy(&chartInstance->c1_setSimStateSideEffectsInfo);
}

static void sf_c1_ascenseur_simplev2(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance)
{
  real_T c1_d0;
  real_T c1_d1;
  real_T c1_d2;
  real_T *c1_porte;
  real_T *c1_led;
  c1_led = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_porte = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_set_sim_state_side_effects_c1_ascenseur_simplev2(chartInstance);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_presentTime = _sfTime_;
  chartInstance->c1_elapsedTime = chartInstance->c1_presentTime -
    chartInstance->c1_previousTime;
  chartInstance->c1_previousTime = chartInstance->c1_presentTime;
  chartInstance->c1_temporalCounter_i1 += chartInstance->c1_elapsedTime;
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  if (chartInstance->c1_is_active_c1_ascenseur_simplev2 == 0U) {
    _SFD_CC_CALL(CHART_ENTER_ENTRY_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_active_c1_ascenseur_simplev2 = 1U;
    _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_c1_ascenseur_simplev2 = c1_IN_fonctionnement_normal;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_fonctionnement_normal = 1U;
    chartInstance->c1_is_active_gestion_portes = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_gestion_portes = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_gestion_portes = c1_IN_en_cours_fermeture;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
    chartInstance->c1_temporalCounter_i1 = 0.0;
    chartInstance->c1_tp_en_cours_fermeture = 1U;
    *c1_porte = 0.0;
    c1_d0 = *c1_porte;
    sf_mex_printf("%s =\\n", "porte");
    sf_mex_call_debug("disp", 0U, 1U, 6, c1_d0);
    chartInstance->c1_is_active_voyant_lumineux = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 14U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_voyant_lumineux = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 24U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_voyant_lumineux = c1_IN_voyant_eteint;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_voyant_eteint = 1U;
    *c1_led = 0.0;
    c1_d1 = *c1_led;
    sf_mex_printf("%s =\\n", "led");
    sf_mex_call_debug("disp", 0U, 1U, 6, c1_d1);
    chartInstance->c1_is_active_controllerAscenseur = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_controllerAscenseur = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 31U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_controllerAscenseur = c1_IN_initialisation;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_initialisation = 1U;
    chartInstance->c1_etageDemande = 0.0;
    c1_d2 = chartInstance->c1_etageDemande;
    sf_mex_printf("%s =\\n", "etageDemande");
    sf_mex_call_debug("disp", 0U, 1U, 6, c1_d2);
    chartInstance->c1_is_active_cabine = 1U;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_cabine = 1U;
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 25U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_cabine = c1_IN_arret_cabine;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_arret_cabine = 1U;
  } else {
    c1_fonctionnement_normal(chartInstance);
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_ascenseur_simplev2MachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance)
{
}

static void registerMessagesc1_ascenseur_simplev2
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance)
{
}

static void c1_fonctionnement_normal(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance)
{
  boolean_T c1_out;
  real_T c1_d3;
  boolean_T c1_temp;
  boolean_T c1_b_temp;
  boolean_T c1_c_temp;
  boolean_T c1_d_temp;
  boolean_T c1_e_temp;
  boolean_T c1_f_temp;
  boolean_T c1_g_temp;
  boolean_T c1_b_out;
  real_T c1_d4;
  boolean_T c1_h_temp;
  boolean_T c1_i_temp;
  boolean_T c1_c_out;
  boolean_T c1_d_out;
  real_T c1_d5;
  boolean_T c1_j_temp;
  boolean_T c1_k_temp;
  boolean_T c1_e_out;
  real_T c1_d6;
  boolean_T c1_l_temp;
  boolean_T c1_f_out;
  real_T c1_d7;
  boolean_T c1_m_temp;
  boolean_T c1_g_out;
  real_T c1_d8;
  real_T *c1_etageCabine;
  real_T *c1_led;
  real_T *c1_C0;
  real_T *c1_B0;
  real_T *c1_C1;
  real_T *c1_B1;
  real_T *c1_C2;
  real_T *c1_B2;
  real_T *c1_C3;
  real_T *c1_B3;
  real_T *c1_etage;
  real_T *c1_afficheur;
  c1_etageCabine = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
  c1_C3 = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c1_C2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_C1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_C0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_B3 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_B2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_B1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_B0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c1_afficheur = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c1_led = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
  c1_etage = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_gestion_portes(chartInstance);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 14U, chartInstance->c1_sfEvent);
  switch (chartInstance->c1_is_voyant_lumineux) {
   case c1_IN_voyant_allume:
    CV_STATE_EVAL(14, 0, 1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 7U, chartInstance->c1_sfEvent);
    c1_out = (CV_TRANSITION_EVAL(7U, (int32_T)_SFD_CCP_CALL(7U, 0,
                chartInstance->c1_etageDemande == *c1_etageCabine != 0U,
                chartInstance->c1_sfEvent)) != 0);
    if (c1_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_voyant_allume = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_voyant_lumineux = c1_IN_voyant_eteint;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_voyant_eteint = 1U;
      *c1_led = 0.0;
      c1_d3 = *c1_led;
      sf_mex_printf("%s =\\n", "led");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d3);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 15U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 15U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_voyant_eteint:
    CV_STATE_EVAL(14, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 6U, chartInstance->c1_sfEvent);
    c1_temp = (_SFD_CCP_CALL(6U, 0, *c1_C0 != 0U, chartInstance->c1_sfEvent) !=
               0);
    if (!c1_temp) {
      c1_temp = (_SFD_CCP_CALL(6U, 1, *c1_B0 != 0U, chartInstance->c1_sfEvent)
                 != 0);
    }

    c1_b_temp = c1_temp;
    if (!c1_b_temp) {
      c1_b_temp = (_SFD_CCP_CALL(6U, 2, *c1_C1 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_c_temp = c1_b_temp;
    if (!c1_c_temp) {
      c1_c_temp = (_SFD_CCP_CALL(6U, 3, *c1_B1 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_d_temp = c1_c_temp;
    if (!c1_d_temp) {
      c1_d_temp = (_SFD_CCP_CALL(6U, 4, *c1_C2 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_e_temp = c1_d_temp;
    if (!c1_e_temp) {
      c1_e_temp = (_SFD_CCP_CALL(6U, 5, *c1_B2 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_f_temp = c1_e_temp;
    if (!c1_f_temp) {
      c1_f_temp = (_SFD_CCP_CALL(6U, 6, *c1_C3 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_g_temp = c1_f_temp;
    if (!c1_g_temp) {
      c1_g_temp = (_SFD_CCP_CALL(6U, 7, *c1_B3 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_b_out = (CV_TRANSITION_EVAL(6U, (int32_T)c1_g_temp) != 0);
    if (c1_b_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_voyant_eteint = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_voyant_lumineux = c1_IN_voyant_allume;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_voyant_allume = 1U;
      *c1_led = 1.0;
      c1_d4 = *c1_led;
      sf_mex_printf("%s =\\n", "led");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d4);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 16U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 16U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(14, 0, 0);
    chartInstance->c1_is_voyant_lumineux = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 14U, chartInstance->c1_sfEvent);
  c1_controllerAscenseur(chartInstance);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
  switch (chartInstance->c1_is_cabine) {
   case c1_IN_arret_cabine:
    CV_STATE_EVAL(1, 0, 1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 26U,
                 chartInstance->c1_sfEvent);
    c1_h_temp = (_SFD_CCP_CALL(26U, 0, chartInstance->c1_is_gestion_portes ==
      c1_IN_portes_fermees != 0U, chartInstance->c1_sfEvent) != 0);
    if (c1_h_temp) {
      c1_h_temp = (_SFD_CCP_CALL(26U, 1, chartInstance->c1_etageDemande >
        *c1_etageCabine != 0U, chartInstance->c1_sfEvent) != 0);
    }

    c1_i_temp = c1_h_temp;
    if (c1_i_temp) {
      c1_i_temp = (_SFD_CCP_CALL(26U, 2, chartInstance->c1_etageDemande != 100.0
        != 0U, chartInstance->c1_sfEvent) != 0);
    }

    c1_c_out = (CV_TRANSITION_EVAL(26U, (int32_T)c1_i_temp) != 0);
    if (c1_c_out) {
      if (_SFD_TRANSITION_CONFLICT_CHECK_ENABLED()) {
        unsigned int transitionList[2];
        unsigned int numTransitions = 1;
        transitionList[0] = 26;
        _SFD_TRANSITION_CONFLICT_CHECK_BEGIN();
        c1_d_out = ((chartInstance->c1_is_gestion_portes == c1_IN_portes_fermees)
                    && (chartInstance->c1_etageDemande < *c1_etageCabine) &&
                    (chartInstance->c1_etageDemande != 100.0));
        if (c1_d_out) {
          transitionList[numTransitions] = 28;
          numTransitions++;
        }

        _SFD_TRANSITION_CONFLICT_CHECK_END();
        if (numTransitions > 1) {
          _SFD_TRANSITION_CONFLICT(&(transitionList[0]),numTransitions);
        }
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 26U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_arret_cabine = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_cabine = c1_IN_montee_cabine;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_montee_cabine = 1U;
      *c1_etage = chartInstance->c1_etageDemande;
      c1_d5 = *c1_etage;
      sf_mex_printf("%s =\\n", "etage");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d5);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 28U,
                   chartInstance->c1_sfEvent);
      c1_j_temp = (_SFD_CCP_CALL(28U, 0, chartInstance->c1_is_gestion_portes ==
        c1_IN_portes_fermees != 0U, chartInstance->c1_sfEvent) != 0);
      if (c1_j_temp) {
        c1_j_temp = (_SFD_CCP_CALL(28U, 1, chartInstance->c1_etageDemande <
          *c1_etageCabine != 0U, chartInstance->c1_sfEvent) != 0);
      }

      c1_k_temp = c1_j_temp;
      if (c1_k_temp) {
        c1_k_temp = (_SFD_CCP_CALL(28U, 2, chartInstance->c1_etageDemande !=
          100.0 != 0U, chartInstance->c1_sfEvent) != 0);
      }

      c1_e_out = (CV_TRANSITION_EVAL(28U, (int32_T)c1_k_temp) != 0);
      if (c1_e_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 28U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_arret_cabine = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_cabine = c1_IN_descente_cabine;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_descente_cabine = 1U;
        *c1_etage = chartInstance->c1_etageDemande;
        c1_d6 = *c1_etage;
        sf_mex_printf("%s =\\n", "etage");
        sf_mex_call_debug("disp", 0U, 1U, 6, c1_d6);
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 2U,
                     chartInstance->c1_sfEvent);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 2U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_descente_cabine:
    CV_STATE_EVAL(1, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 29U,
                 chartInstance->c1_sfEvent);
    c1_l_temp = (_SFD_CCP_CALL(29U, 0, *c1_etageCabine ==
      chartInstance->c1_etageDemande != 0U, chartInstance->c1_sfEvent) != 0);
    if (!c1_l_temp) {
      c1_l_temp = (_SFD_CCP_CALL(29U, 1, chartInstance->c1_etageDemande == 100.0
        != 0U, chartInstance->c1_sfEvent) != 0);
    }

    c1_f_out = (CV_TRANSITION_EVAL(29U, (int32_T)c1_l_temp) != 0);
    if (c1_f_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 29U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_descente_cabine = 0U;
      _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 3U, chartInstance->c1_sfEvent);
      *c1_afficheur = *c1_etageCabine;
      c1_d7 = *c1_afficheur;
      sf_mex_printf("%s =\\n", "afficheur");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d7);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c1_sfEvent);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_cabine = c1_IN_arret_cabine;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_arret_cabine = 1U;
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 3U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 3U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_montee_cabine:
    CV_STATE_EVAL(1, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 27U,
                 chartInstance->c1_sfEvent);
    c1_m_temp = (_SFD_CCP_CALL(27U, 0, *c1_etageCabine ==
      chartInstance->c1_etageDemande != 0U, chartInstance->c1_sfEvent) != 0);
    if (!c1_m_temp) {
      c1_m_temp = (_SFD_CCP_CALL(27U, 1, chartInstance->c1_etageDemande == 100.0
        != 0U, chartInstance->c1_sfEvent) != 0);
    }

    c1_g_out = (CV_TRANSITION_EVAL(27U, (int32_T)c1_m_temp) != 0);
    if (c1_g_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 27U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_montee_cabine = 0U;
      _SFD_CS_CALL(STATE_ENTER_EXIT_FUNCTION_TAG, 4U, chartInstance->c1_sfEvent);
      *c1_afficheur = *c1_etageCabine;
      c1_d8 = *c1_afficheur;
      sf_mex_printf("%s =\\n", "afficheur");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d8);
      _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c1_sfEvent);
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 4U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_cabine = c1_IN_arret_cabine;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_arret_cabine = 1U;
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 4U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 4U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(1, 0, 0);
    chartInstance->c1_is_cabine = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c1_sfEvent);
  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void c1_gestion_portes(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance)
{
  boolean_T c1_out;
  real_T c1_d9;
  boolean_T c1_temp;
  boolean_T c1_b_out;
  boolean_T c1_c_out;
  boolean_T c1_d_out;
  real_T c1_d10;
  boolean_T c1_b_temp;
  boolean_T c1_e_out;
  real_T c1_d11;
  real_T *c1_B0;
  real_T *c1_porte;
  real_T *c1_fdc;
  real_T *c1_etageCabine;
  c1_fdc = (real_T *)ssGetInputPortSignal(chartInstance->S, 10);
  c1_etageCabine = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
  c1_B0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  c1_porte = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 9U, chartInstance->c1_sfEvent);
  switch (chartInstance->c1_is_gestion_portes) {
   case c1_IN_en_cours_fermeture:
    CV_STATE_EVAL(9, 0, 1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 2U, chartInstance->c1_sfEvent);
    c1_out = (CV_TRANSITION_EVAL(2U, (int32_T)_SFD_CCP_CALL(2U, 0, *c1_B0 != 0U,
                chartInstance->c1_sfEvent)) != 0);
    if (c1_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 2U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_en_cours_fermeture = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_gestion_portes = c1_IN_en_cours_ouverture;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_en_cours_ouverture = 1U;
      *c1_porte = 1.0;
      c1_d9 = *c1_porte;
      sf_mex_printf("%s =\\n", "porte");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d9);
    } else {
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 3U,
                   chartInstance->c1_sfEvent);
      c1_temp = (_SFD_CCP_CALL(3U, 0, 1 != 0U, chartInstance->c1_sfEvent) != 0);
      if (c1_temp) {
        c1_temp = (_SFD_CCP_CALL(3U, 1, chartInstance->c1_temporalCounter_i1 +
                    (_sfTime_ - chartInstance->c1_previousTime) >= 2.0 != 0U,
                    chartInstance->c1_sfEvent) != 0);
      }

      c1_b_out = (CV_TRANSITION_EVAL(3U, (int32_T)c1_temp) != 0);
      if (c1_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 3U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_en_cours_fermeture = 0U;
        _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
        chartInstance->c1_is_gestion_portes = c1_IN_portes_fermees;
        _SFD_CS_CALL(STATE_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
        chartInstance->c1_tp_portes_fermees = 1U;
      } else {
        _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 10U,
                     chartInstance->c1_sfEvent);
      }
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 10U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_en_cours_ouverture:
    CV_STATE_EVAL(9, 0, 2);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 0U, chartInstance->c1_sfEvent);
    c1_c_out = (CV_TRANSITION_EVAL(0U, (int32_T)_SFD_CCP_CALL(0U, 0, *c1_fdc ==
      1.0 != 0U, chartInstance->c1_sfEvent)) != 0);
    if (c1_c_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 0U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_en_cours_ouverture = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_gestion_portes = c1_IN_portes_ouvertes;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
      chartInstance->c1_temporalCounter_i1 = 0.0;
      chartInstance->c1_tp_portes_ouvertes = 1U;
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 11U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 11U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_portes_fermees:
    CV_STATE_EVAL(9, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 5U, chartInstance->c1_sfEvent);
    c1_d_out = (CV_TRANSITION_EVAL(5U, (int32_T)_SFD_CCP_CALL(5U, 0,
      chartInstance->c1_etageDemande == *c1_etageCabine != 0U,
      chartInstance->c1_sfEvent)) != 0);
    if (c1_d_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 5U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_portes_fermees = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_gestion_portes = c1_IN_en_cours_ouverture;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_en_cours_ouverture = 1U;
      *c1_porte = 1.0;
      c1_d10 = *c1_porte;
      sf_mex_printf("%s =\\n", "porte");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d10);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 12U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 12U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_portes_ouvertes:
    CV_STATE_EVAL(9, 0, 4);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 1U, chartInstance->c1_sfEvent);
    c1_b_temp = (_SFD_CCP_CALL(1U, 0, 1 != 0U, chartInstance->c1_sfEvent) != 0);
    if (c1_b_temp) {
      c1_b_temp = (_SFD_CCP_CALL(1U, 1, chartInstance->c1_temporalCounter_i1 +
        (_sfTime_ - chartInstance->c1_previousTime) >= 10.0 != 0U,
        chartInstance->c1_sfEvent) != 0);
    }

    c1_e_out = (CV_TRANSITION_EVAL(1U, (int32_T)c1_b_temp) != 0);
    if (c1_e_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 1U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_portes_ouvertes = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_gestion_portes = c1_IN_en_cours_fermeture;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
      chartInstance->c1_temporalCounter_i1 = 0.0;
      chartInstance->c1_tp_en_cours_fermeture = 1U;
      *c1_porte = 0.0;
      c1_d11 = *c1_porte;
      sf_mex_printf("%s =\\n", "porte");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d11);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 13U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 13U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(9, 0, 0);
    chartInstance->c1_is_gestion_portes = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 9U, chartInstance->c1_sfEvent);
}

static void c1_controllerAscenseur(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance)
{
  boolean_T c1_temp;
  boolean_T c1_b_temp;
  boolean_T c1_c_temp;
  boolean_T c1_d_temp;
  boolean_T c1_e_temp;
  boolean_T c1_f_temp;
  boolean_T c1_g_temp;
  boolean_T c1_out;
  boolean_T c1_h_temp;
  boolean_T c1_b_out;
  boolean_T c1_i_temp;
  boolean_T c1_c_out;
  boolean_T c1_j_temp;
  boolean_T c1_d_out;
  real_T c1_d12;
  real_T c1_d13;
  boolean_T c1_e_out;
  real_T c1_d14;
  real_T *c1_C0;
  real_T *c1_B0;
  real_T *c1_C1;
  real_T *c1_B1;
  real_T *c1_C2;
  real_T *c1_B2;
  real_T *c1_C3;
  real_T *c1_B3;
  real_T *c1_etageCabine;
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  c1_etageCabine = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
  c1_C3 = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
  c1_C2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c1_C1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c1_C0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
  c1_B3 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c1_B2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_B1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_B0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 5U, chartInstance->c1_sfEvent);
  switch (chartInstance->c1_is_controllerAscenseur) {
   case c1_IN_effacement_etageDemande:
    CV_STATE_EVAL(5, 0, 1);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 21U,
                 chartInstance->c1_sfEvent);
    c1_temp = (_SFD_CCP_CALL(21U, 0, *c1_C0 != 0U, chartInstance->c1_sfEvent) !=
               0);
    if (!c1_temp) {
      c1_temp = (_SFD_CCP_CALL(21U, 1, *c1_B0 != 0U, chartInstance->c1_sfEvent)
                 != 0);
    }

    c1_b_temp = c1_temp;
    if (!c1_b_temp) {
      c1_b_temp = (_SFD_CCP_CALL(21U, 2, *c1_C1 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_c_temp = c1_b_temp;
    if (!c1_c_temp) {
      c1_c_temp = (_SFD_CCP_CALL(21U, 3, *c1_B1 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_d_temp = c1_c_temp;
    if (!c1_d_temp) {
      c1_d_temp = (_SFD_CCP_CALL(21U, 4, *c1_C2 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_e_temp = c1_d_temp;
    if (!c1_e_temp) {
      c1_e_temp = (_SFD_CCP_CALL(21U, 5, *c1_B2 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_f_temp = c1_e_temp;
    if (!c1_f_temp) {
      c1_f_temp = (_SFD_CCP_CALL(21U, 6, *c1_C3 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_g_temp = c1_f_temp;
    if (!c1_g_temp) {
      c1_g_temp = (_SFD_CCP_CALL(21U, 7, *c1_B3 != 0U, chartInstance->c1_sfEvent)
                   != 0);
    }

    c1_out = (CV_TRANSITION_EVAL(21U, (int32_T)c1_g_temp) != 0);
    if (c1_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 21U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 9U,
                   chartInstance->c1_sfEvent);
      c1_h_temp = (_SFD_CCP_CALL(9U, 0, *c1_C0 != 0U, chartInstance->c1_sfEvent)
                   != 0);
      if (!c1_h_temp) {
        c1_h_temp = (_SFD_CCP_CALL(9U, 1, *c1_B0 != 0U,
          chartInstance->c1_sfEvent) != 0);
      }

      c1_b_out = (CV_TRANSITION_EVAL(9U, (int32_T)c1_h_temp) != 0);
      guard1 = FALSE;
      guard2 = FALSE;
      if (c1_b_out) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 9U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 14U, chartInstance->c1_sfEvent);
        chartInstance->c1_etageDemande = 0.0;
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 13U, chartInstance->c1_sfEvent);
        guard2 = TRUE;
      } else {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
        _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 16U,
                     chartInstance->c1_sfEvent);
        c1_i_temp = (_SFD_CCP_CALL(16U, 0, *c1_C1 != 0U,
          chartInstance->c1_sfEvent) != 0);
        if (!c1_i_temp) {
          c1_i_temp = (_SFD_CCP_CALL(16U, 1, *c1_B1 != 0U,
            chartInstance->c1_sfEvent) != 0);
        }

        c1_c_out = (CV_TRANSITION_EVAL(16U, (int32_T)c1_i_temp) != 0);
        if (c1_c_out) {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 16U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 15U, chartInstance->c1_sfEvent);
          chartInstance->c1_etageDemande = 1.0;
          guard2 = TRUE;
        } else {
          _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 11U, chartInstance->c1_sfEvent);
          _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 17U,
                       chartInstance->c1_sfEvent);
          c1_j_temp = (_SFD_CCP_CALL(17U, 0, *c1_C2 != 0U,
            chartInstance->c1_sfEvent) != 0);
          if (!c1_j_temp) {
            c1_j_temp = (_SFD_CCP_CALL(17U, 1, *c1_B2 != 0U,
              chartInstance->c1_sfEvent) != 0);
          }

          c1_d_out = (CV_TRANSITION_EVAL(17U, (int32_T)c1_j_temp) != 0);
          if (c1_d_out) {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 17U, chartInstance->c1_sfEvent);
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 18U, chartInstance->c1_sfEvent);
            chartInstance->c1_etageDemande = 2.0;
            guard1 = TRUE;
          } else {
            _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 20U, chartInstance->c1_sfEvent);
            chartInstance->c1_etageDemande = 3.0;
          }
        }
      }

      if (guard2 == TRUE) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 12U, chartInstance->c1_sfEvent);
        guard1 = TRUE;
      }

      if (guard1 == TRUE) {
        _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 19U, chartInstance->c1_sfEvent);
      }

      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 10U, chartInstance->c1_sfEvent);
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 22U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_effacement_etageDemande = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_controllerAscenseur = c1_IN_memorisation;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_memorisation = 1U;
      c1_d12 = chartInstance->c1_etageDemande;
      sf_mex_printf("%s =\\n", "etageDemande");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d12);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 6U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 6U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_initialisation:
    CV_STATE_EVAL(5, 0, 2);
    _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 30U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_initialisation = 0U;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 7U, chartInstance->c1_sfEvent);
    chartInstance->c1_is_controllerAscenseur = c1_IN_effacement_etageDemande;
    _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
    chartInstance->c1_tp_effacement_etageDemande = 1U;
    chartInstance->c1_etageDemande = 100.0;
    c1_d13 = chartInstance->c1_etageDemande;
    sf_mex_printf("%s =\\n", "etageDemande");
    sf_mex_call_debug("disp", 0U, 1U, 6, c1_d13);
    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 7U, chartInstance->c1_sfEvent);
    break;

   case c1_IN_memorisation:
    CV_STATE_EVAL(5, 0, 3);
    _SFD_CT_CALL(TRANSITION_BEFORE_PROCESSING_TAG, 23U,
                 chartInstance->c1_sfEvent);
    c1_e_out = (CV_TRANSITION_EVAL(23U, (int32_T)_SFD_CCP_CALL(23U, 0,
      *c1_etageCabine == chartInstance->c1_etageDemande != 0U,
      chartInstance->c1_sfEvent)) != 0);
    if (c1_e_out) {
      _SFD_CT_CALL(TRANSITION_ACTIVE_TAG, 23U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_memorisation = 0U;
      _SFD_CS_CALL(STATE_INACTIVE_TAG, 8U, chartInstance->c1_sfEvent);
      chartInstance->c1_is_controllerAscenseur = c1_IN_effacement_etageDemande;
      _SFD_CS_CALL(STATE_ACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
      chartInstance->c1_tp_effacement_etageDemande = 1U;
      chartInstance->c1_etageDemande = 100.0;
      c1_d14 = chartInstance->c1_etageDemande;
      sf_mex_printf("%s =\\n", "etageDemande");
      sf_mex_call_debug("disp", 0U, 1U, 6, c1_d14);
    } else {
      _SFD_CS_CALL(STATE_ENTER_DURING_FUNCTION_TAG, 8U,
                   chartInstance->c1_sfEvent);
    }

    _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 8U, chartInstance->c1_sfEvent);
    break;

   default:
    CV_STATE_EVAL(5, 0, 0);
    chartInstance->c1_is_controllerAscenseur = c1_IN_NO_ACTIVE_CHILD;
    _SFD_CS_CALL(STATE_INACTIVE_TAG, 6U, chartInstance->c1_sfEvent);
    break;
  }

  _SFD_CS_CALL(EXIT_OUT_OF_FUNCTION_TAG, 5U, chartInstance->c1_sfEvent);
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

const mxArray *sf_c1_ascenseur_simplev2_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c1_nameCaptureInfo;
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_ascenseur_simplev2InstanceStruct *chartInstance;
  chartInstance = (SFc1_ascenseur_simplev2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i0, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_ascenseur_simplev2InstanceStruct *chartInstance;
  chartInstance = (SFc1_ascenseur_simplev2InstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent), &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  uint8_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_ascenseur_simplev2InstanceStruct *chartInstance;
  chartInstance = (SFc1_ascenseur_simplev2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(uint8_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static uint8_T c1_b_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_b_tp_fonctionnement_normal, const char_T
  *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_tp_fonctionnement_normal), &c1_thisId);
  sf_mex_destroy(&c1_b_tp_fonctionnement_normal);
  return c1_y;
}

static uint8_T c1_c_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_tp_fonctionnement_normal;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  uint8_T c1_y;
  SFc1_ascenseur_simplev2InstanceStruct *chartInstance;
  chartInstance = (SFc1_ascenseur_simplev2InstanceStruct *)chartInstanceVoid;
  c1_b_tp_fonctionnement_normal = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_tp_fonctionnement_normal), &c1_thisId);
  sf_mex_destroy(&c1_b_tp_fonctionnement_normal);
  *(uint8_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_ascenseur_simplev2InstanceStruct *chartInstance;
  chartInstance = (SFc1_ascenseur_simplev2InstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_d_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_porte, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_porte), &c1_thisId);
  sf_mex_destroy(&c1_porte);
  return c1_y;
}

static real_T c1_e_emlrt_marshallIn(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance, const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d15;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d15, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d15;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_porte;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_ascenseur_simplev2InstanceStruct *chartInstance;
  chartInstance = (SFc1_ascenseur_simplev2InstanceStruct *)chartInstanceVoid;
  c1_porte = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_porte), &c1_thisId);
  sf_mex_destroy(&c1_porte);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_emlrt_marshallIn
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance, const mxArray
   *c1_b_setSimStateSideEffectsInfo, const char_T *c1_identifier)
{
  const mxArray *c1_y = NULL;
  emlrtMsgIdentifier c1_thisId;
  c1_y = NULL;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  sf_mex_assign(&c1_y, c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c1_b_setSimStateSideEffectsInfo), &c1_thisId), FALSE);
  sf_mex_destroy(&c1_b_setSimStateSideEffectsInfo);
  return c1_y;
}

static const mxArray *c1_g_emlrt_marshallIn
  (SFc1_ascenseur_simplev2InstanceStruct *chartInstance, const mxArray *c1_u,
   const emlrtMsgIdentifier *c1_parentId)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_duplicatearraysafe(&c1_u), FALSE);
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_ascenseur_simplev2InstanceStruct
  *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c1_ascenseur_simplev2_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1269528373U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3478998069U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2293594300U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3104247818U);
}

mxArray *sf_c1_ascenseur_simplev2_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("Cgfr1PJ6t9YSRcZ2hz4Wc");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,11,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,4,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_ascenseur_simplev2_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

static const mxArray *sf_get_sim_state_info_c1_ascenseur_simplev2(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[28],T\"afficheur\",},{M[1],M[14],T\"etage\",},{M[1],M[27],T\"led\",},{M[1],M[12],T\"porte\",},{M[3],M[64],T\"etageDemande\",},{M[8],M[0],T\"is_active_c1_ascenseur_simplev2\",},{M[8],M[43],T\"is_active_gestion_portes\",},{M[8],M[46],T\"is_active_voyant_lumineux\",},{M[8],M[63],T\"is_active_controllerAscenseur\",},{M[8],M[136],T\"is_active_cabine\",}}",
    "100 S1x7'type','srcId','name','auxInfo'{{M[9],M[0],T\"is_c1_ascenseur_simplev2\",},{M[9],M[43],T\"is_gestion_portes\",},{M[9],M[46],T\"is_voyant_lumineux\",},{M[9],M[63],T\"is_controllerAscenseur\",},{M[9],M[136],T\"is_cabine\",},{M[11],M[0],T\"temporalCounter_i1\",S'et','os','ct'{{T\"at\",M1x2[3 21],M[1]}}},{M[13],M[0],T\"previousTime\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 17, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_ascenseur_simplev2_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_ascenseur_simplev2InstanceStruct *chartInstance;
    chartInstance = (SFc1_ascenseur_simplev2InstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _ascenseur_simplev2MachineNumber_,
           1,
           17,
           32,
           16,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_ascenseur_simplev2MachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_ascenseur_simplev2MachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _ascenseur_simplev2MachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,2,0,1,"porte");
          _SFD_SET_DATA_PROPS(1,2,0,1,"etage");
          _SFD_SET_DATA_PROPS(2,2,0,1,"led");
          _SFD_SET_DATA_PROPS(3,2,0,1,"afficheur");
          _SFD_SET_DATA_PROPS(4,1,1,0,"B0");
          _SFD_SET_DATA_PROPS(5,1,1,0,"B1");
          _SFD_SET_DATA_PROPS(6,1,1,0,"B2");
          _SFD_SET_DATA_PROPS(7,1,1,0,"B3");
          _SFD_SET_DATA_PROPS(8,1,1,0,"C0");
          _SFD_SET_DATA_PROPS(9,1,1,0,"C1");
          _SFD_SET_DATA_PROPS(10,1,1,0,"C2");
          _SFD_SET_DATA_PROPS(11,1,1,0,"C3");
          _SFD_SET_DATA_PROPS(12,0,0,0,"etageDemande");
          _SFD_SET_DATA_PROPS(13,1,1,0,"etageCabine");
          _SFD_SET_DATA_PROPS(14,1,1,0,"arret");
          _SFD_SET_DATA_PROPS(15,1,1,0,"fdc");
          _SFD_STATE_INFO(0,1,0);
          _SFD_STATE_INFO(1,0,1);
          _SFD_STATE_INFO(2,0,0);
          _SFD_STATE_INFO(3,0,0);
          _SFD_STATE_INFO(4,0,0);
          _SFD_STATE_INFO(5,0,1);
          _SFD_STATE_INFO(6,0,0);
          _SFD_STATE_INFO(7,0,0);
          _SFD_STATE_INFO(8,0,0);
          _SFD_STATE_INFO(9,0,1);
          _SFD_STATE_INFO(10,0,0);
          _SFD_STATE_INFO(11,0,0);
          _SFD_STATE_INFO(12,0,0);
          _SFD_STATE_INFO(13,0,0);
          _SFD_STATE_INFO(14,0,1);
          _SFD_STATE_INFO(15,0,0);
          _SFD_STATE_INFO(16,0,0);
          _SFD_CH_SUBSTATE_COUNT(1);
          _SFD_CH_SUBSTATE_DECOMP(0);
          _SFD_CH_SUBSTATE_INDEX(0,0);
          _SFD_ST_SUBSTATE_COUNT(0,4);
          _SFD_ST_SUBSTATE_INDEX(0,0,9);
          _SFD_ST_SUBSTATE_INDEX(0,1,14);
          _SFD_ST_SUBSTATE_INDEX(0,2,5);
          _SFD_ST_SUBSTATE_INDEX(0,3,1);
          _SFD_ST_SUBSTATE_COUNT(9,4);
          _SFD_ST_SUBSTATE_INDEX(9,0,10);
          _SFD_ST_SUBSTATE_INDEX(9,1,11);
          _SFD_ST_SUBSTATE_INDEX(9,2,12);
          _SFD_ST_SUBSTATE_INDEX(9,3,13);
          _SFD_ST_SUBSTATE_COUNT(10,0);
          _SFD_ST_SUBSTATE_COUNT(11,0);
          _SFD_ST_SUBSTATE_COUNT(12,0);
          _SFD_ST_SUBSTATE_COUNT(13,0);
          _SFD_ST_SUBSTATE_COUNT(14,2);
          _SFD_ST_SUBSTATE_INDEX(14,0,15);
          _SFD_ST_SUBSTATE_INDEX(14,1,16);
          _SFD_ST_SUBSTATE_COUNT(15,0);
          _SFD_ST_SUBSTATE_COUNT(16,0);
          _SFD_ST_SUBSTATE_COUNT(5,3);
          _SFD_ST_SUBSTATE_INDEX(5,0,6);
          _SFD_ST_SUBSTATE_INDEX(5,1,7);
          _SFD_ST_SUBSTATE_INDEX(5,2,8);
          _SFD_ST_SUBSTATE_COUNT(6,0);
          _SFD_ST_SUBSTATE_COUNT(7,0);
          _SFD_ST_SUBSTATE_COUNT(8,0);
          _SFD_ST_SUBSTATE_COUNT(1,3);
          _SFD_ST_SUBSTATE_INDEX(1,0,2);
          _SFD_ST_SUBSTATE_INDEX(1,1,3);
          _SFD_ST_SUBSTATE_INDEX(1,2,4);
          _SFD_ST_SUBSTATE_COUNT(2,0);
          _SFD_ST_SUBSTATE_COUNT(3,0);
          _SFD_ST_SUBSTATE_COUNT(4,0);
        }

        _SFD_CV_INIT_CHART(1,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,4,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(1,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(2,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(3,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(4,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(5,3,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(6,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(7,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(8,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(9,4,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(10,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(11,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(12,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(13,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(14,2,1,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(15,0,0,0,0,0,NULL,NULL);
        }

        {
          _SFD_CV_INIT_STATE(16,0,0,0,0,0,NULL,NULL);
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(5,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 7 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(0,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 3 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(2,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 9, 0 };

          static unsigned int sEndGuardMap[] = { 12, 13 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(1,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 8, 0 };

          static unsigned int sEndGuardMap[] = { 11, 12 };

          static int sPostFixPredicateTree[] = { 0, 1, -3 };

          _SFD_CV_INIT_TRANS(3,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(4,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 5, 9, 13, 17, 21, 25, 29 };

          static unsigned int sEndGuardMap[] = { 3, 7, 11, 15, 19, 23, 27, 31 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2, 6, -2, 7, -2 };

          _SFD_CV_INIT_TRANS(6,8,&(sStartGuardMap[0]),&(sEndGuardMap[0]),15,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(7,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(24,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(31,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 5, 9, 13, 17, 21, 25, 29 };

          static unsigned int sEndGuardMap[] = { 3, 7, 11, 15, 19, 23, 27, 31 };

          static int sPostFixPredicateTree[] = { 0, 1, -2, 2, -2, 3, -2, 4, -2,
            5, -2, 6, -2, 7, -2 };

          _SFD_CV_INIT_TRANS(21,8,&(sStartGuardMap[0]),&(sEndGuardMap[0]),15,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(30,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          static int sPostFixPredicateTree[] = { 0 };

          _SFD_CV_INIT_TRANS(23,1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),1,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 5 };

          static unsigned int sEndGuardMap[] = { 3, 7 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(9,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(8,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(14,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 5 };

          static unsigned int sEndGuardMap[] = { 3, 7 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(16,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(11,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(15,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 1, 5 };

          static unsigned int sEndGuardMap[] = { 3, 7 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(17,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_CV_INIT_TRANS(20,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(18,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(19,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(12,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(13,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(10,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(22,0,NULL,NULL,0,NULL);
        _SFD_CV_INIT_TRANS(25,0,NULL,NULL,0,NULL);

        {
          static unsigned int sStartGuardMap[] = { 2, 31 };

          static unsigned int sEndGuardMap[] = { 27, 48 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(29,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 37, 65 };

          static unsigned int sEndGuardMap[] = { 34, 61, 82 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(26,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 1, 37, 65 };

          static unsigned int sEndGuardMap[] = { 34, 61, 82 };

          static int sPostFixPredicateTree[] = { 0, 1, -3, 2, -3 };

          _SFD_CV_INIT_TRANS(28,3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),5,
                             &(sPostFixPredicateTree[0]));
        }

        {
          static unsigned int sStartGuardMap[] = { 2, 31 };

          static unsigned int sEndGuardMap[] = { 27, 48 };

          static int sPostFixPredicateTree[] = { 0, 1, -2 };

          _SFD_CV_INIT_TRANS(27,2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),3,
                             &(sPostFixPredicateTree[0]));
        }

        _SFD_TRANS_COV_WTS(5,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          _SFD_TRANS_COV_MAPS(5,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(0,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 7 };

          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(2,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 3 };

          _SFD_TRANS_COV_MAPS(2,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(1,0,2,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 9, 0 };

          static unsigned int sEndGuardMap[] = { 12, 13 };

          _SFD_TRANS_COV_MAPS(1,
                              0,NULL,NULL,
                              2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(3,0,2,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 8, 0 };

          static unsigned int sEndGuardMap[] = { 11, 12 };

          _SFD_TRANS_COV_MAPS(3,
                              0,NULL,NULL,
                              2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(4,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(4,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(6,0,8,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1, 5, 9, 13, 17, 21, 25, 29 };

          static unsigned int sEndGuardMap[] = { 3, 7, 11, 15, 19, 23, 27, 31 };

          _SFD_TRANS_COV_MAPS(6,
                              0,NULL,NULL,
                              8,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(7,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          _SFD_TRANS_COV_MAPS(7,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(24,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(24,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(31,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(31,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(21,0,8,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1, 5, 9, 13, 17, 21, 25, 29 };

          static unsigned int sEndGuardMap[] = { 3, 7, 11, 15, 19, 23, 27, 31 };

          _SFD_TRANS_COV_MAPS(21,
                              0,NULL,NULL,
                              8,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(30,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(30,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(23,0,1,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1 };

          static unsigned int sEndGuardMap[] = { 26 };

          _SFD_TRANS_COV_MAPS(23,
                              0,NULL,NULL,
                              1,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(9,0,2,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1, 5 };

          static unsigned int sEndGuardMap[] = { 3, 7 };

          _SFD_TRANS_COV_MAPS(9,
                              0,NULL,NULL,
                              2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(8,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(8,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(14,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(14,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(16,0,2,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1, 5 };

          static unsigned int sEndGuardMap[] = { 3, 7 };

          _SFD_TRANS_COV_MAPS(16,
                              0,NULL,NULL,
                              2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(11,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(11,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(15,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(15,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(17,0,2,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1, 5 };

          static unsigned int sEndGuardMap[] = { 3, 7 };

          _SFD_TRANS_COV_MAPS(17,
                              0,NULL,NULL,
                              2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(20,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(20,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(18,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(18,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(19,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(19,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(12,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(12,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(13,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(13,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(10,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(10,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(22,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(22,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(25,0,0,0,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(25,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(29,0,2,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 2, 31 };

          static unsigned int sEndGuardMap[] = { 27, 48 };

          _SFD_TRANS_COV_MAPS(29,
                              0,NULL,NULL,
                              2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(26,0,3,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1, 37, 65 };

          static unsigned int sEndGuardMap[] = { 34, 61, 82 };

          _SFD_TRANS_COV_MAPS(26,
                              0,NULL,NULL,
                              3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(28,0,3,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 1, 37, 65 };

          static unsigned int sEndGuardMap[] = { 34, 61, 82 };

          _SFD_TRANS_COV_MAPS(28,
                              0,NULL,NULL,
                              3,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_TRANS_COV_WTS(27,0,2,0,0);
        if (chartAlreadyPresent==0) {
          static unsigned int sStartGuardMap[] = { 2, 31 };

          static unsigned int sEndGuardMap[] = { 27, 48 };

          _SFD_TRANS_COV_MAPS(27,
                              0,NULL,NULL,
                              2,&(sStartGuardMap[0]),&(sEndGuardMap[0]),
                              0,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c1_porte;
          real_T *c1_etage;
          real_T *c1_led;
          real_T *c1_afficheur;
          real_T *c1_B0;
          real_T *c1_B1;
          real_T *c1_B2;
          real_T *c1_B3;
          real_T *c1_C0;
          real_T *c1_C1;
          real_T *c1_C2;
          real_T *c1_C3;
          real_T *c1_etageCabine;
          real_T *c1_arret;
          real_T *c1_fdc;
          c1_fdc = (real_T *)ssGetInputPortSignal(chartInstance->S, 10);
          c1_arret = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
          c1_etageCabine = (real_T *)ssGetInputPortSignal(chartInstance->S, 8);
          c1_C3 = (real_T *)ssGetInputPortSignal(chartInstance->S, 7);
          c1_C2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c1_C1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c1_C0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 4);
          c1_B3 = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c1_B2 = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c1_B1 = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_B0 = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          c1_afficheur = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c1_led = (real_T *)ssGetOutputPortSignal(chartInstance->S, 3);
          c1_etage = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_porte = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_porte);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_etage);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_led);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_afficheur);
          _SFD_SET_DATA_VALUE_PTR(4U, c1_B0);
          _SFD_SET_DATA_VALUE_PTR(5U, c1_B1);
          _SFD_SET_DATA_VALUE_PTR(6U, c1_B2);
          _SFD_SET_DATA_VALUE_PTR(7U, c1_B3);
          _SFD_SET_DATA_VALUE_PTR(8U, c1_C0);
          _SFD_SET_DATA_VALUE_PTR(9U, c1_C1);
          _SFD_SET_DATA_VALUE_PTR(10U, c1_C2);
          _SFD_SET_DATA_VALUE_PTR(11U, c1_C3);
          _SFD_SET_DATA_VALUE_PTR(12U, &chartInstance->c1_etageDemande);
          _SFD_SET_DATA_VALUE_PTR(13U, c1_etageCabine);
          _SFD_SET_DATA_VALUE_PTR(14U, c1_arret);
          _SFD_SET_DATA_VALUE_PTR(15U, c1_fdc);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _ascenseur_simplev2MachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "cgjBNi2xTcDKxL8zZIBksD";
}

static void sf_opaque_initialize_c1_ascenseur_simplev2(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_ascenseur_simplev2InstanceStruct*)
    chartInstanceVar)->S,0);
  initialize_params_c1_ascenseur_simplev2((SFc1_ascenseur_simplev2InstanceStruct*)
    chartInstanceVar);
  initialize_c1_ascenseur_simplev2((SFc1_ascenseur_simplev2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_enable_c1_ascenseur_simplev2(void *chartInstanceVar)
{
  enable_c1_ascenseur_simplev2((SFc1_ascenseur_simplev2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_disable_c1_ascenseur_simplev2(void *chartInstanceVar)
{
  disable_c1_ascenseur_simplev2((SFc1_ascenseur_simplev2InstanceStruct*)
    chartInstanceVar);
}

static void sf_opaque_gateway_c1_ascenseur_simplev2(void *chartInstanceVar)
{
  sf_c1_ascenseur_simplev2((SFc1_ascenseur_simplev2InstanceStruct*)
    chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_ascenseur_simplev2(SimStruct*
  S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_ascenseur_simplev2
    ((SFc1_ascenseur_simplev2InstanceStruct*)chartInfo->chartInstance);/* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_ascenseur_simplev2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_ascenseur_simplev2(SimStruct* S, const
  mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_ascenseur_simplev2();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_ascenseur_simplev2((SFc1_ascenseur_simplev2InstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_ascenseur_simplev2(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_ascenseur_simplev2(S);
}

static void sf_opaque_set_sim_state_c1_ascenseur_simplev2(SimStruct* S, const
  mxArray *st)
{
  sf_internal_set_sim_state_c1_ascenseur_simplev2(S, st);
}

static void sf_opaque_terminate_c1_ascenseur_simplev2(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_ascenseur_simplev2InstanceStruct*) chartInstanceVar)
      ->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_ascenseur_simplev2_optimization_info();
    }

    finalize_c1_ascenseur_simplev2((SFc1_ascenseur_simplev2InstanceStruct*)
      chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_ascenseur_simplev2((SFc1_ascenseur_simplev2InstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_ascenseur_simplev2(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_ascenseur_simplev2
      ((SFc1_ascenseur_simplev2InstanceStruct*)(((ChartInfoStruct *)
         ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_ascenseur_simplev2(SimStruct *S)
{
  ssSetNeedAbsoluteTime(S,1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_ascenseur_simplev2_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,11);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,4);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=4; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 11; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(1234698423U));
  ssSetChecksum1(S,(3241681536U));
  ssSetChecksum2(S,(4019960677U));
  ssSetChecksum3(S,(2870035808U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_ascenseur_simplev2(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Stateflow");
  }
}

static void mdlStart_c1_ascenseur_simplev2(SimStruct *S)
{
  SFc1_ascenseur_simplev2InstanceStruct *chartInstance;
  chartInstance = (SFc1_ascenseur_simplev2InstanceStruct *)utMalloc(sizeof
    (SFc1_ascenseur_simplev2InstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_ascenseur_simplev2InstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 0;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway =
    sf_opaque_gateway_c1_ascenseur_simplev2;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c1_ascenseur_simplev2;
  chartInstance->chartInfo.terminateChart =
    sf_opaque_terminate_c1_ascenseur_simplev2;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_ascenseur_simplev2;
  chartInstance->chartInfo.disableChart =
    sf_opaque_disable_c1_ascenseur_simplev2;
  chartInstance->chartInfo.getSimState =
    sf_opaque_get_sim_state_c1_ascenseur_simplev2;
  chartInstance->chartInfo.setSimState =
    sf_opaque_set_sim_state_c1_ascenseur_simplev2;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c1_ascenseur_simplev2;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_ascenseur_simplev2;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_ascenseur_simplev2;
  chartInstance->chartInfo.mdlSetWorkWidths =
    mdlSetWorkWidths_c1_ascenseur_simplev2;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_ascenseur_simplev2_method_dispatcher(SimStruct *S, int_T method, void
  *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_ascenseur_simplev2(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_ascenseur_simplev2(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_ascenseur_simplev2(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_ascenseur_simplev2_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
