
#include "I_Phone_RTOS.h"
#include "CALL_MGR.h"

SWITCH CALL_COME_FLAG,END_CALL_FLAG,ACCEPT_CALL_FLAG;

void Call_Mgr_Init()
  {
    ACCEPT_CALL_FLAG=OFF;
    END_CALL_FLAG=OFF;
    CALL_COME_FLAG=OFF;   
  }

void Income_Call_Notify(void)
  {
    CALL_COME_FLAG=ON;
    ACCEPT_CALL_FLAG=OFF;
    END_CALL_FLAG=OFF;
  } 
  
void Accept_Call_Notify(void)
  {
    if (CALL_COME_FLAG==ON) 
    {
        ACCEPT_CALL_FLAG=ON;
        CALL_COME_FLAG=OFF;
   }
  }
   
  
void End_Call_Notify(void)
  {
    if (CALL_COME_FLAG==ON || ACCEPT_CALL_FLAG==ON) 
    {
     END_CALL_FLAG=ON;
     ACCEPT_CALL_FLAG=OFF;
     CALL_COME_FLAG=OFF;
    } 
   } 
  
  boolean Get_Income_Call_Status() 
  {
    return (CALL_COME_FLAG==ON); 
  } 
  
  boolean Get_Accept_Call_Status()
  {
    return (ACCEPT_CALL_FLAG==ON);
  }
  
  boolean Get_End_Call_Status()
  {
    return (END_CALL_FLAG==ON);
  }