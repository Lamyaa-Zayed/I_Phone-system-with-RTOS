
#include "I_Phone_RTOS.h"
#include "SPEAKER_MGR.h"
#include "CALL_MGR.h"

static SWITCH Ringer_Flag,Speaker_Flag,VB_Notify_FLAG;

static unsigned char Speaker;       //PORTB
//unsigned char VB_Status=0;         //ADC1

void Speaker_Mgr_Init(void)
{
    Set_Rng_Value(0);
    Ringer_Flag=OFF;
    Set_SPK_LVL(0);
    Speaker_Flag=OFF; 
    VB_Notify_FLAG=OFF;
    Speaker=0;
}

void VB_Notify()
  {
   VB_Notify_FLAG=ON; 
  }   
  
  
void Speaker_Cyclic_5ms(void)
  {
   if(Get_Accept_Call_Status()==1)
   {
    if(Speaker_Flag==OFF)
    {
     Speaker=50;
     Speaker_Flag=ON;
    }
    if(VB_Notify_FLAG==ON )
    {
        if(Get_VB_Status()<128)
        {
        if( Speaker>0)
        Speaker--;   
        } 
        else 
        {
        if( Speaker<99)
        Speaker++;    
        }
       VB_Notify_FLAG=OFF; 
    } 
   }
   else
   {
     Speaker=0;
     Speaker_Flag=OFF;
   } 
   Set_SPK_LVL(Speaker);
  }
  
void Ringer_Cyclic_1ms()
  {  
     if(Get_RSS_Status()==1) 
         {
            Set_Rng_Value(0);
            Ringer_Flag=OFF;   
         } 
     else
         {
            if (Get_Income_Call_Status()==1)
            {
            Set_Rng_Value(1);
            Ringer_Flag=ON;
            }
            else
            {
            Set_Rng_Value(0);
            Ringer_Flag=OFF;
            }
         }   
  }   
  

   
