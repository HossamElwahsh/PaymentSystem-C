#ifndef TERMINAL_H
#define TERMINAL_H

 typedef unsigned char uint8_t;
 typedef unsigned short uint16_t;
 
 typedef struct ST_terminalData_t ST_terminalData_t;
 
 typedef enum EN_terminalError_t EN_terminalError_t;
 
 EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
 void getTransactionDateTest(void);

#endif