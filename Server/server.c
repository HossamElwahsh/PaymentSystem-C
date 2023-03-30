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
    
}


/***********************************************************************************************************************/