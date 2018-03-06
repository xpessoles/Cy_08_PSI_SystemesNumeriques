#include "__cf_ascenseur_simplev2.h"
#ifndef RTW_HEADER_ascenseur_simplev2_acc_h_
#define RTW_HEADER_ascenseur_simplev2_acc_h_
#ifndef ascenseur_simplev2_acc_COMMON_INCLUDES_
#define ascenseur_simplev2_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "ascenseur_simplev2_acc_types.h"
typedef struct { real_T B_1_0_0 [ 6 ] ; real_T B_1_3_0 ; real_T B_1_4_0 ;
real_T B_1_8_0 ; real_T B_1_9_0 ; real_T B_1_10_0 ; real_T B_1_11_0 ; real_T
B_1_12_0 ; real_T B_1_13_0 ; real_T B_1_14_0 ; real_T B_1_15_0 ; real_T
B_1_16_0 ; real_T B_1_20_0 ; real_T B_1_22_0 ; real_T B_1_23_0 [ 4 ] ; real_T
B_1_25_0 ; real_T B_1_27_0 ; real_T B_1_28_0 [ 4 ] ; real_T B_1_30_0 ; real_T
B_1_32_0 ; real_T B_1_33_0 [ 4 ] ; real_T B_0_0_1 ; real_T B_0_0_2 ; real_T
B_0_0_3 ; real_T B_0_0_4 ; real_T B_1_1_0 [ 3 ] ; real_T B_1_6_0 ; real_T
B_1_7_0 ; } B_ascenseur_simplev2_T ; typedef struct { real_T
EXEC_INPUT_1_DSTATE ; real_T EXEC_INPUT_1_DSTATE_l ; real_T
EXEC_INPUT_1_DSTATE_i ; real_T EXEC_STATE_1_RWORK ; real_T
EXEC_OUTPUT_3_RWORK ; real_T EXEC_INPUT_1_RWORK ; real_T EXEC_INPUT_1_RWORK_k
; real_T EXEC_INPUT_1_RWORK_c ; real_T EXEC_SINK_2_RWORK ; void *
EXEC_STATE_1_PWORK [ 5 ] ; void * EXEC_OUTPUT_3_PWORK [ 5 ] ; void *
EXEC_INPUT_1_PWORK [ 5 ] ; void * EXEC_INPUT_1_PWORK_d [ 5 ] ; void *
EXEC_INPUT_1_PWORK_n [ 5 ] ; void * EXEC_SINK_2_PWORK [ 5 ] ; int_T Abs_MODE
; char pad_Abs_MODE [ 4 ] ; } DW_ascenseur_simplev2_T ; typedef struct {
real_T EXEC_STATE_1_CSTATE [ 6 ] ; } X_ascenseur_simplev2_T ; typedef struct
{ real_T EXEC_STATE_1_CSTATE [ 6 ] ; } XDot_ascenseur_simplev2_T ; typedef
struct { boolean_T EXEC_STATE_1_CSTATE [ 6 ] ; } XDis_ascenseur_simplev2_T ;
typedef struct { real_T EXEC_STATE_1_CSTATE [ 6 ] ; }
CStateAbsTol_ascenseur_simplev2_T ; typedef struct { real_T Abs_AbsZc_ZC ; }
ZCV_ascenseur_simplev2_T ; typedef struct { ZCSigState Abs_AbsZc_ZCE ; }
PrevZCX_ascenseur_simplev2_T ; struct P_ascenseur_simplev2_T_ { real_T P_0 ;
real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ;
real_T P_7 ; real_T P_8 ; uint8_T P_9 ; uint8_T P_10 ; uint8_T P_11 ; uint8_T
P_12 ; uint8_T P_13 ; uint8_T P_14 ; uint8_T P_15 ; uint8_T P_16 ; uint8_T
P_17 ; char pad_P_17 [ 7 ] ; } ; extern P_ascenseur_simplev2_T
ascenseur_simplev2_rtDefaultP ;
#endif
