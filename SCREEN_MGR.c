
#include "I_Phone_RTOS.h"
#include "SCREEN_MGR.h"
#include "CALL_MGR.h"

SWITCH Screen_Flag,HB_Notify_FLAG;


void Screen_Mgr_Init()
{
    Set_Screen_Value(0);
    Screen_Flag=OFF;
    Set_Luminance_LVL(0);
}

void LS_Cyclic_4ms()
{
   if(Screen_Flag==ON)
         {
            Set_Luminance_LVL(Get_LS_Status());
         }  
}

void Screen_Cyclic_2ms()
{
   if(Get_Income_Call_Status()==1 || HB_Notify_FLAG==ON)
   {
    Set_Screen_Value(1);
    Screen_Flag=ON;
   }               
   //if(Get_Accept_Call_Status()==1 || Get_End_Call_Status()==1 || HB_Notify_FLAG==OFF )
   else
   {
    Set_Screen_Value(0);
    Screen_Flag=OFF; 
   }
}

void HB_Notify()
{
   if(HB_Notify_FLAG==ON)
   {
    HB_Notify_FLAG=OFF;
   } 
   else
   {
    HB_Notify_FLAG=ON;
   }
}

