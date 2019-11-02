#ifndef __I_PHONE_H__
#define __I_PHONE_H__

#include <mega328p.h>
#include <delay.h>

typedef enum {False=0,True} boolean;
extern void I_Phone_RTOS_Conf(void);
extern void Set_SPK_LVL(char);
extern char Get_VB_Status(void);
extern void Set_Luminance_LVL(char);
extern char Get_LS_Status(void);
extern boolean Get_RSS_Status(void);
extern void Set_Rng_Value(boolean);
extern void Set_Screen_Value(boolean);
typedef enum {OFF=0,ON} SWITCH;

#define VB  4
#define END_CALL 1
#define ACCEPT_CALL 0
#define CALL_COME 2
#define HB_OR_SWB 3
#define Luminous_low 5
#define Luminous_high 6
#define Ringer 7
#define Screen 5
#define RSS 2

// Voltage Reference: AREF pin
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (1<<ADLAR))

#endif 