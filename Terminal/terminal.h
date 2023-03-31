/*
 * @Title      	: Terminal Module
 * @Filename   	: terminal.h
 * @Author     	: Mahmoud Mowafey
 * @Origin Date	: Mar 29, 2023
 * @Version		: 1.0.0
 * @Compiler	: MinGW
 * @Target     	: General Purpose Processor / PCs
 * @Notes		: The code is written with ANSI_C Standard.
 *
 * THIS SOFTWARE IS PROVIDED BY HACKER KERMIT- TEAM_1 at Sprints_Automotiv_BC_W11.
 *
 *
 */


#ifndef TERMINAL_H_
#define TERMINAL_H_



typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
#ifndef TERMINAL_H_
#define TERMINAL_H_

/* Library Module */
#include "../Library/standard_types.h"

#define TERMINAL_MAX_AMOUNT		5000

typedef struct ST_terminalData_t
{
	float32_t transAmount;
	float32_t maxTransAmount;
	uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;


	TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/* Functions' Prototypes */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional

#endif /* TERMINAL_H_ */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float32_t maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);             // Optional

void getTransactionDateTest(void);
void isCardExpired(void);

#endif /* TERMINAL_H_ */
