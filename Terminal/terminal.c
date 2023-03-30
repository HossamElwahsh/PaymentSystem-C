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


/* ********************** structs and Enums Start *********************************************************** */


/* ********************** Main Terminal Functions Start ******************************************** */

 /*
 * @author         : Tarek Gohry
 * @brief          : Get transaction date and store it in terminal data
 * Description     :
    - This function takes a reference to a structure or terminal data
    - Get transaction date
 * Return          :
    - WRONG_DATE ERROR if transaction date is NULL or < 10 characters or Wrong format
    - TERMINAL_OK otherwise
 */

 EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
 {
     uint8_t i = 0;
     uint8_t day = 0;
     uint8_t month = 0;
     uint16_t year = 0;

     /* Read Date */
     printf("Please enter transaction date: ");
     gets(termData->transactionDate);

     /* Validate Date Length*/
     if(strlen(termData->transactionDate) != 10)
     {
         return WRONG_DATE;
     }

     /* Validate Date Format */
     if(termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/')
     {
         return WRONG_DATE;
     }

     /* Validate Day */
     day = termData->transactionDate[0] - '0';
     day = (day*10) + (termData->transactionDate[1] - '0');

     if(day<1 || day>31)
     {
         return WRONG_DATE;
     }

     /* Validate Month */
     month = termData->transactionDate[3] - '0';
     month = (month*10) + (termData->transactionDate[4] - '0');

     if(month<1 || month>12)
     {
         return WRONG_DATE;
     }

     if(month==2 && day>29)
     {
         return WRONG_DATE;
     }

     /* Validate Year */
     year = termData->transactionDate[6] - '0';
     year = (year*10) + (termData->transactionDate[7] - '0');
     year = (year*10) + (termData->transactionDate[8] - '0');
     year = (year*10) + (termData->transactionDate[9] - '0');

     if(year<1900 || year>2100)
     {
         return WRONG_DATE;
     }

     return TERMINAL_OK;
 }

/**
 * This function takes the maximum allowed amount and stores it into terminal data
 * Note:
 * - Transaction max amount is a float number
 * @param termData [in,out] terminal data
 * @param maxAmount [in] max transaction amount
 * @return INVALID_MAX_AMOUNT if max amount is less than or equal zero
 * @return TERMINAL_OK otherwise
 */
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    if(maxAmount > 0) {
        termData->maxTransAmount = maxAmount;
        return TERMINAL_OK;
    }
    else
    {
        return INVALID_MAX_AMOUNT;
    }

}

/* ********************** Main Terminal Functions End ********************************************** */