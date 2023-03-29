/*
 * @Title      	: Terminal Module
 * @Filename   	: terminal.c
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


#include"terminal.h"

ST_terminalData_t MyTerminalData;


/************************************************************************************************************
 * Function : getTransactionAmount()
 *//**
 * Description:
 *
 * This function is used to test the getTransactionAmount(ST_terminalData_t *termData) function, to validate the terminal data.
 *
 * PRE-CONDITION:
 * PRE-CONDITION:
 * PRE-CONDITION:
 * PRE-CONDITION:
 * POST-CONDITION:
 *
 * @param [in]		termData is a pointer to the ST_terminalData_t structure that holding data
 * 					about the terminal such as transAmount, maxTransAmount, transactionGate.
 *
 * @return 			EN_terminalError_t is a enumeration that contains terminal module errors.
 *
 * \b Example:
 * @code
 *
 * EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
 *
 * @endcode
 *
 * @see getCardHolderNameTest()
 *
 *************************************************************************************************************************************/


EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
	printf("\nEnter the amount for transaction: \t");
	fflush(stdin);
	fflush(stdout);
	scanf("%f",&(termData->maxTransAmount));
	if( ( termData->maxTransAmount ) <= 0.0  )
		return INVALID_AMOUNT;
	else
		return TERMINAL_OK;
}

void getTransactionAmountTest(void)
{
	uint8_t i, WrongName=0, WrongString[] = "INVALID_AMOUNT, Please check your transaction amount!\n";
	printf("Tester Name: Mahmoud_Mowafey\n");
	printf("Function Name: getTransactionAmount\n\n\n");
	for ( i=0 ; i<5 ; i++ )
	{
		WrongName = getTransactionAmount(&MyTerminalData);
		printf("\nTest Case_%d: \n",i);
		printf("Input Data: %f\n",MyTerminalData.maxTransAmount);
		printf("Expected Result: Your transaction amount should be greater than Zero\n");
		if( WrongName == INVALID_AMOUNT )
		{
			printf("Actual Result: %s\n",WrongString);
		}
		else
			printf("Actual Result: Your operation is done\n");
	}
}
