#include "server.h"

/*****************************************************************************************/
/*    Function Description    : This function will take terminal data and a reference to the account in the database 
*								and check if the account has a sufficient amount to withdraw or not.*/
/*    Parameter in            : ST_terminalData_t* termData
*								ST_accountsDB_t* accountRefrence	*/
/*    Parameter inout         : None */
/*    Parameter out           : None */
/*    Return value            : return LOW_BALANCE If the transaction amount is greater than the balance in the database
*								return SERVER_OK otherwise */
/*    Requirment              : None */
/*****************************************************************************************/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	if (termData->transAmount > accountRefrence->balance)
		return LOW_BALANCE;
	return SERVER_OK;
}


/*****************************************************************************************/
 /*    Function Description    : test all possible scenarios, happy-case, and worst-case scenarios. on isAmountAvailable function*/
 /*    Parameter in            : None */
 /*    Parameter inout         : None */
 /*    Parameter out           : None */
 /*    Return value            : None */
 /*    Requirment              : None */
 /*
 * Test casese 1000 , 1500 , 2000 , 2500 ,3000 , 3500 , 4000 , 4500 , 5000 , 5500 , 6000 , 6500 , 7000 , 7500 , 8000 , 8500 , 9000
 *             9500 , 10000 , 10500 
 * balance set to 8000
 */
 /*****************************************************************************************/
void isAmountAvailableTest(void)
{
    static char counter;
    ST_terminalData_t termData[20];
    ST_accountsDB_t accountRefrence;
    accountRefrence.balance = 8000.0;
    EN_terminalError_t error = TERMINAL_OK;
    termData[counter].maxTransAmount = 8000.0;
    termData[counter].transAmount = 1000.0 + (500.0 * counter);
    error = isAmountAvailable(&termData[counter], &accountRefrence);
    printf("Tester Name: Matarawy\n");
    printf("Test case : %d\n", counter + 1);
    printf("Input Data: maxTransAmount = %2.f and transAmount = %2.f\n", accountRefrence.balance, termData[counter].transAmount);
    if (error == LOW_BALANCE)
        printf("Expected Result: Your amount is more than your acount balance\n");
    else
        printf("Expected Result: Server is OK\n");
    if (error == SERVER_OK)
        printf("Actual Result: Server is OK\n\n\n\n");
    else
        printf("Actual Result:  amount is more than the max amount \n\n\n\n");

    counter++;
}