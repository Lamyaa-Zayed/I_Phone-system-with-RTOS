/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
© Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : I_Phone
Version : 1
Date    : 23/10/2019
Author  : Lamyaa Zayed
Company : Just_Dream
Comments: 


Chip type               : ATmega328P
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include "I_Phone_RTOS.h"
#include "SPEAKER_MGR.h"
#include "SCREEN_MGR.h"
#include "CALL_MGR.h"

// Declare your global variables here
#define MAJOR_CYCLE 20U
#define TASK_1MS 1U
#define TASK_2MS 2U
#define TASK_4MS 4U
#define TASK_5MS 5U
static void I_Phone_Scheduler_1ms();
static unsigned char VB_Status;         //ADC1
static unsigned char LS_Status;         //ADC0

static void I_Phone_Scheduler_1ms()
{
   static unsigned char Cycle_Counter;
   if((Cycle_Counter%TASK_1MS)==0)
   {
     Ringer_Cyclic_1ms();   
   }
   if((Cycle_Counter%TASK_2MS)==0)
   {
     Screen_Cyclic_2ms();   
   }
   if((Cycle_Counter%TASK_4MS)==0)
   {
     LS_Cyclic_4ms();   
   }
   if((Cycle_Counter%TASK_5MS)==0)
   {
     Speaker_Cyclic_5ms();   
   }
   
   Cycle_Counter++;
   Cycle_Counter=Cycle_Counter%MAJOR_CYCLE;
} 

 // Timer 0 overflow interrupt service routine
interrupt [TIM0_OVF] void timer0_ovf_isr(void)
  { 
   // Reinitialize Timer 0 value
    TCNT0=0x83;   
    I_Phone_Scheduler_1ms();
    // Place your code here

  }

// Pin change 16-23 interrupt service routine
interrupt [PC_INT2] void pin_change_isr2(void)
    {
    // Place your code here
   static char Port_Value;
   Port_Value^=PIND;
   
   //VB_Come
   if(Port_Value & (1<<VB))
   {
     if(!(PIND&(1<<VB)))
    {
      VB_Notify();     
    }
   }  
   
   //END_CALL
   else if (Port_Value & (1<<END_CALL))
   {
    if((!(PIND&(1<<END_CALL))) )
    {
        End_Call_Notify();
    }
   } 
    
   //Accept_CALL                         
    else if (Port_Value & (1<<ACCEPT_CALL))
   {
    if(!(PIND&(1<<ACCEPT_CALL)))
    {
        Accept_Call_Notify();
    }
   }   
   Port_Value=PIND;
 }

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
  {
    // Place your code here
    Income_Call_Notify();
  }

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
  {
    // Place your code here
    //HB_OR_SWB
    HB_Notify(); 
  }

// ADC interrupt service routine
interrupt [ADC_INT] void adc_isr(void)
  {
    unsigned char adc_data;   // Read the 8 most significant bits
    adc_data=ADCH;            // of the AD conversion result
    // Place your code here
    
    if( (ADMUX &(1<<MUX0)) != 0x01)//this is channel 0
    {           
        LS_Status=adc_data ;                                                 
        ADMUX |= (1<<MUX0);//select channel 1
    }
    else  
    {
        VB_Status=adc_data ; 
        ADMUX &=~ (1<<MUX0);//select channel 0           
    }   
    ADCSRA |= (1<<ADSC);

  }

void main(void)
  {
    // Declare your local variables here

    I_Phone_RTOS_Conf();
    //I_Phone_init();
    Call_Mgr_Init();
    Speaker_Mgr_Init();
    Screen_Mgr_Init();
    // Global enable interrupts
    #asm("sei")

    while (1)
      {
        SMCR=(1<<SE);
        SMCR&=~((1<<SM0)|(1<<SM1)|(1<<SM2));
      }   
  }


boolean Get_RSS_Status()
{
  return (PINC&(1<<RSS)? 0x01:0x00 );
}

void Set_SPK_LVL(char SPK_Level)
{
   unsigned char Unit_Digit,Tenth_Digit; 
   if( SPK_Level<100)
    {
    Unit_Digit=SPK_Level%10u;
    Tenth_Digit=SPK_Level/10u;
    PORTB=((Tenth_Digit<<4)|Unit_Digit);
    }
}

char Get_LS_Status()
{
  return LS_Status;
}

void Set_Rng_Value(boolean Rng_Value)
{
   if(Rng_Value)
   {
    PORTD |=(1<<Ringer);
   }
   else
   {
     PORTD&=~(1<<Ringer);
   }
}

 void Set_Screen_Value(boolean Screen_Value)
{
    if(Screen_Value==0)
   {
    PORTC&=~(1<<Screen);  
   }
   else
   {
     PORTC|=(1<<Screen);
   }    
}

 void Set_Luminance_LVL(char Luminance_Lvl) 
 { 
    if (Luminance_Lvl<128) 
            {
                PORTD&=~(1<< Luminous_high);
                PORTD|=(1<< Luminous_low);
            }
    else if (Luminance_Lvl==128)
            {
               PORTD&=~(1<< Luminous_low);
               PORTD&=~(1<< Luminous_high);
            }
    else if (Luminance_Lvl>128)
            {  
                PORTD&=~(1<< Luminous_low);
                PORTD|=(1<< Luminous_high);
            } 
 }
 
 char Get_VB_Status()
 {
    return VB_Status;
 }