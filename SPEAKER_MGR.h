#ifndef _SPEAKER_H_
#define _SPEAKER_H_

extern void Speaker_Mgr_Init();
extern void VB_Notify();
extern void Speaker_Cyclic_5ms();
extern void Ringer_Cyclic_1ms();

//#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (1<<ADLAR))

#endif 