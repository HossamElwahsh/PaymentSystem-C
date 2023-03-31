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
