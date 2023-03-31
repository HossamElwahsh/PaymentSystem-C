/*
 * @Title      	: Server Module
 * @Filename   	: server.c
 * @Author     	: Mahmoud Mowafey
 * @Origin Date	: Mar 30, 2023
 * @Version		: 1.0.0
 * @Compiler	: MinGW
 * @Target     	: General Purpose Processor / PCs
 * @Notes		: The code is written with ANSI_C Standard.
 *
 * THIS SOFTWARE IS PROVIDED BY HACKER KERMIT- TEAM_1 at Sprints_Automotiv_BC_W11.
 *
 *
 */
#include "server.h"

ST_accountsDB_t accountsDB[255] = {
        {2000.5f, RUNNING,"465802789866246"},
        {10000.0f, BLOCKED, "4523811971470463"},
        { 3000.5f, RUNNING,"3566250034860958"},
        {2000.5f, RUNNING,"5246473315044497"},
        {10000.7f, BLOCKED, "5224747772286501"},
        { 2000.5f, RUNNING,"5295132073042677"},
        {2000.5f, RUNNING,"5296594764212407"},
        {10000.0f, BLOCKED, "5235394910255721"},
        { 2000.5f, RUNNING,"5220871865596701"},
        {2000.5f, RUNNING,"5296594764212407"}
};


ST_transaction_t transactionsDB[255];

/***********************************************************************************************************************/

 /**
 * @author         : Tarek Gohry
 * @brief          : Take all transaction data and validate its data 
 * Description     :
    - It checks the account details and amount availability 
 * Return          :
    - FRAUD_CARD if the account does not exist 
    - DECLINED_INSUFFECIENT_FUND if the amount is not available
	- DECLINED_STOLEN_CARD if the account is blocked 
	- INTERNAL_SERVER_ERROR if a transaction can't be saved
	- APPROVED Otherwise
 */
 EN_transState_t recieveTransactionData(ST_transaction_t *transData)
 {
     ST_accountsDB_t * accountReference = calloc(1, sizeof(ST_accountsDB_t));

    if(isValidAccount(&transData->cardHolderData, accountReference) == ACCOUNT_NOT_FOUND)
	{
        free(accountReference);
		return FRAUD_CARD; 
	}

	if(isBlockedAccount(accountReference) == BLOCKED_ACCOUNT)
	{
        free(accountReference);
		return DECLINED_STOLEN_CARD;
	}

     if(isAmountAvailable(&transData->terminalData, accountReference) == LOW_BALANCE)
     {
         free(accountReference);
         return DECLINED_INSUFFECIENT_FUND;
     }
	
	if(saveTransaction(transData) != SERVER_OK)
	{
        free(accountReference);
		return INTERNAL_SERVER_ERROR;
	}

    free(accountReference);
	return APPROVED; 
 }
 
 /***********************************************************************************************************************/


/***********************************************************************************************************************/

/**
* @author         : Tarek Gohry
* @brief          : Store all transaction data in the transaction database
* Description     :
   - It gives a sequence number to a transaction
   - This number is incremented once a transaction is processed into the server
   - Must check the last sequence number in the server to give the new transaction a new sequence number
   - It saves ant type of a transaction. APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD,
     FRUAD_CARD, INTERNAL_SERVER_ERROR
   - List all saved transactions using the listSavedTransactions function
* Return          :
   - SERVER_OK, Assuming that the connection between the terminal and server is always connected
*/

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{

    transactionsDB[transData->transactionSequenceNumber].cardHolderData = transData->cardHolderData;
    transactionsDB[transData->transactionSequenceNumber].terminalData = transData->terminalData;
    transactionsDB[transData->transactionSequenceNumber].transState = transData->transState;
    transactionsDB[transData->transactionSequenceNumber].transactionSequenceNumber = transData->transactionSequenceNumber++;

    listSavedTransactions();

    return SERVER_OK;
}



/***********************************************************************************************************************/

 /************************************************************************************************************
  * Function : isBlockedAccount()
  *//**
  * Description:
  *
  * This function is used to check the user-account status, to validate if the account is blocked or running.
  *
  * PRE-CONDITION:  the Account_Data_Base should be exist.
  *
  * POST-CONDITION: the Account has been checked if it is blocked or running.
  *
  * @param [in]		accountRefrence is a pointer to the ST_accountsDB_t structure that holding data
  * 					about user-account.
  *
  * @return 			EN_serverError_t is a enumeration that contains server errors.
  * \b Example:
  * @code
  * EN_serverError_t var = isBlockedAccount();
  * @endcode
  *
  *
  ************************************************************************************************************/

EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	if (accountRefrence->state)
	{
		return BLOCKED_ACCOUNT;
	}
	else
	{
		return SERVER_OK;
	}

}

/***************************************************************************************************************/


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