#ifndef _CALL_MGR_H_
#define _CALL_MGR_H_

extern boolean Get_Income_Call_Status();
extern boolean Get_Accept_Call_Status();
extern boolean Get_End_Call_Status();
extern void Call_Mgr_Init();
extern void Income_Call_Notify(void); 
extern void Accept_Call_Notify(void);
extern void End_Call_Notify(void);



#endif 