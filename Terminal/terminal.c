/**
 ******************************************************************************************************
 * @file           : terminal.c
 * @author         : Team 1
 * @brief          : Contains the functionality of terminal
 ******************************************************************************************************
 */

/* ********************** Includes Section Start ********************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terminal.h"
/* ********************** Includes Section End   ********************** */


/* ********************** structs and Enums Start *********************************************************** */

 struct ST_terminalData_t
 {
     float transAmount;
     float maxTransAmount;
     uint8_t transactionDate[11];

 };

enum EN_terminalError_t
 {
     TERMINAL_OK,
     WRONG_DATE,
     EXPIRED_CARD,
     INVALID_CARD,
     INVALID_AMOUNT,
     EXCEED_MAX_AMOUNT,
     INVALID_MAX_AMOUNT

 };

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

/* ********************** Main Terminal Functions End ********************************************** */


/* ********************** TEST Functions Start ***************************************************** */

 void getTransactionDateTest(void)
 {
    ST_terminalData_t termData;
    EN_terminalError_t termError;

	printf("\n");
	printf("Tester name     : Tarek Gohry\n");
	printf("Function name   : getTransactionDate\n");
	
	/* Test Date Format Length */
	printf("\nTest Case 1:\n");
	printf("Input Data      : 01/02\n");
	printf("Expected Result : WRONG_DATE\n");
	termError = getTransactionDate(&termData);
	printf("Actual Result   : ");
	
    if(termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }
	
	/* Test Year Format */
	printf("\nTest Case 2:\n");
	printf("Input Data      : 01/12/2022222\n");
	printf("Expected Result : WRONG_DATE\n");
	termError = getTransactionDate(&termData);
	printf("Actual Result   : ");
	
    if(termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }
	
	/* Test Day Format */
	printf("\nTest Case 3:\n");
	printf("Input Data      : 33/02/2022\n");
	printf("Expected Result : WRONG_DATE\n");
	termError = getTransactionDate(&termData);
	printf("Actual Result   : ");
	
    if(termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }
	
	/* Test Month Format */
	printf("\nTest Case 4:\n");
	printf("Input Data      : 02/15/2022\n");
	printf("Expected Result : WRONG_DATE\n");
	termError = getTransactionDate(&termData);
	printf("Actual Result   : ");
	
    if(termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }
	
	/* Test Year Format */
	printf("\nTest Case 5:\n");
	printf("Input Data      : 02/12/20az\n");
	printf("Expected Result : WRONG_DATE\n");
	termError = getTransactionDate(&termData);
	printf("Actual Result   : ");
	
    if(termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }
	
	/* Test Correct Date Format*/
	printf("\nTest Case 6:\n");
	printf("Input Data      : 01/02/2022\n");
	printf("Expected Result : TERMINAL_OK\n");
	termError = getTransactionDate(&termData);
	printf("Actual Result   : ");
	
    if(termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }
 }

/* ********************** TEST Functions SEnd  ***************************************************** */


int main()
{
    getTransactionDateTest();
}

/**
 *******************************************************************************************************
 User                Date                 Brief
 *******************************************************************************************************
 Tarek Gohry         29MARCH2023          Task-1 implement getTransactionDate Function

*/
