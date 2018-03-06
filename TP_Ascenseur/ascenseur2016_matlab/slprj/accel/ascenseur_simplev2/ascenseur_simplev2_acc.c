#include "__cf_ascenseur_simplev2.h"
#include <math.h>
#include "ascenseur_simplev2_acc.h"
#include "ascenseur_simplev2_acc_private.h"
#include <stdio.h>
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
static void mdlOutputs ( SimStruct * S , int_T tid ) { B_ascenseur_simplev2_T
* _rtB ; P_ascenseur_simplev2_T * _rtP ; DW_ascenseur_simplev2_T * _rtDW ;
_rtDW = ( ( DW_ascenseur_simplev2_T * ) ssGetRootDWork ( S ) ) ; _rtP = ( (
P_ascenseur_simplev2_T * ) ssGetDefaultParam ( S ) ) ; _rtB = ( (
B_ascenseur_simplev2_T * ) _ssGetBlockIO ( S ) ) ; ssCallAccelRunBlock ( S ,
1 , 0 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 1 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_1_3_0 = muDoubleScalarRound ( _rtP -> P_0 *
_rtB -> B_1_1_0 [ 2 ] ) ; if ( ssIsMajorTimeStep ( S ) ) { _rtDW -> Abs_MODE
= _rtB -> B_1_3_0 >= 0.0 ? 1 : 0 ; } _rtB -> B_1_4_0 = _rtDW -> Abs_MODE > 0
? _rtB -> B_1_3_0 : - _rtB -> B_1_3_0 ; ssCallAccelRunBlock ( S , 1 , 5 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_1_6_0
= _rtP -> P_1 ; _rtB -> B_1_7_0 = _rtP -> P_2 ; ssCallAccelRunBlock ( S , 1 ,
8 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 9 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 10 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 11 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 12 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 13 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 14 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 15 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 16 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 0 , 0 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 1 , 18 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 1 , 19 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_1_20_0 =
_rtP -> P_3 * _rtB -> B_0_0_2 ; } _rtB -> B_1_22_0 = ( _rtB -> B_1_20_0 -
_rtB -> B_1_1_0 [ 2 ] ) * _rtP -> P_4 ; ssCallAccelRunBlock ( S , 1 , 23 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_1_25_0
= _rtP -> P_5 * _rtB -> B_0_0_1 ; } _rtB -> B_1_27_0 = ( _rtB -> B_1_25_0 -
_rtB -> B_1_1_0 [ 0 ] ) * _rtP -> P_6 ; ssCallAccelRunBlock ( S , 1 , 28 ,
SS_CALL_MDL_OUTPUTS ) ; if ( ssIsSampleHit ( S , 1 , 0 ) ) { _rtB -> B_1_30_0
= _rtP -> P_7 * _rtB -> B_0_0_1 ; } _rtB -> B_1_32_0 = ( _rtB -> B_1_30_0 -
_rtB -> B_1_1_0 [ 1 ] ) * _rtP -> P_8 ; ssCallAccelRunBlock ( S , 1 , 33 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 38 ,
SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER ( tid
) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { ssCallAccelRunBlock ( S , 1 ,
0 , SS_CALL_MDL_DERIVATIVES ) ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { ssCallAccelRunBlock ( S , 1 , 0
, SS_CALL_MDL_PROJECTION ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) { ( ( ZCV_ascenseur_simplev2_T
* ) ssGetSolverZcSignalVector ( S ) ) -> Abs_AbsZc_ZC = ( (
B_ascenseur_simplev2_T * ) _ssGetBlockIO ( S ) ) -> B_1_3_0 ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 986193519U
) ; ssSetChecksumVal ( S , 1 , 2721620881U ) ; ssSetChecksumVal ( S , 2 ,
3472265743U ) ; ssSetChecksumVal ( S , 3 , 179137624U ) ; { mxArray *
slVerStructMat = NULL ; mxArray * slStrMat = mxCreateString ( "simulink" ) ;
char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat , 1
, & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat = mxGetField
( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == NULL ) { status = 1 ; }
else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; } }
mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "8.1" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != sizeof ( DW_ascenseur_simplev2_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_ascenseur_simplev2_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_ascenseur_simplev2_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetDefaultParam ( S , (
real_T * ) & ascenseur_simplev2_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof (
real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S ) { {
SimStruct * childS ; SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S
, 0 ) ; callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [
3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; } } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
