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







 /*****************************************************************************************/
 /*    Function Description    : This function compares the transaction amount with the terminal max allowed amount. */
 /*    Parameter in            : ST_terminalData_t* termData */
 /*    Parameter inout         : None */
 /*    Parameter out           : None */
 /*    Return value            : return EXCEED_MAX_AMOUNT If the transaction amount is larger than the terminal max allowed amount
 *                               return TERMINAL_OK otherwise;
 /*    Requirment              : None */
 /*****************************************************************************************/
 EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
 {
     if (termData->transAmount > termData->maxTransAmount)
         return EXCEED_MAX_AMOUNT;
     return TERMINAL_OK;
 }




/* ********************** Main Terminal Functions End ********************************************** */


/* ********************** TEST Functions Start ***************************************************** */
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


 /*****************************************************************************************/
 /*    Function Description    : test all possible scenarios, happy-case, and worst-case scenarios. on isBelowMaxAmount function*/
 /*    Parameter in            : None */
 /*    Parameter inout         : None */
 /*    Parameter out           : None */
 /*    Return value            : None */
 /*    Requirment              : None */
 /*
 * Test casese 1000 , 1500 , 2000 , 2500 ,3000 , 3500 , 4000 , 4500 , 5000 , 5500 , 6000 , 6500 , 7000 , 7500 , 8000 , 8500 , 9000
 *             9500 , 10000 , 10500 
 * max_amount set to 8000 
 */
 /*****************************************************************************************/
void isBelowMaxAmountTest(void)
{
    static char counter;
    ST_terminalData_t termData[20];
    EN_terminalError_t error = TERMINAL_OK;
    termData[counter].maxTransAmount = 8000.0;
    termData[counter].transAmount = 1000.0 + (500.0 * counter);
    error = isBelowMaxAmount(&termData[counter]);
    printf("Tester Name: Matarawy\n");
    printf("Test case : %d\n", counter + 1);
    printf("Input Data: maxTransAmount = 8000 and transAmount = %2.f\n", termData[counter].transAmount);
    if (error == EXCEED_MAX_AMOUNT)
        printf("Expected Result: Your amount is more than the max amount\n");
    else
        printf("Expected Result: Your amount is OK\n");
    if (error == TERMINAL_OK)
        printf("Actual Result: Your amount is OK\n\n\n\n");
    else
        printf("Actual Result:  amount is more than the max amount \n\n\n\n");

    counter++;
}

/* ********************** TEST Functions SEnd  ***************************************************** */


int main()
{
    getTransactionDateTest();
}
