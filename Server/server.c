#include "server.h"












/***********************************************************************************************************************/

 /*
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
	if(isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence) == ACCOUNT_NOT_FOUND)
	{
		return FRAUD_CARD; 
	}
	
	if(isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence) == LOW_BALANCE)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}
	
	if(isBlockedAccount(ST_accountsDB_t *accountRefrence) == BLOCKED_ACCOUNT)
	{
		return DECLINED_STOLEN_CARD;
	}
	
	if(saveTransaction(ST_transaction_t *transData) != SERVER_OK)
	{
		return INTERNAL_SERVER_ERROR;
	}
	
	return APPROVED; 
 }
 
 /***********************************************************************************************************************/
 
 