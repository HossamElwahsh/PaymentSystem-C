#include "app.h"



static uint32_t sequenceNumber;

void appStart(void)
{
	//ST_cardData_t cardData;
	//ST_terminalData_t termData;
	ST_accountsDB_t accountRefrence;
	ST_transaction_t transData = { 0 };

 	uint8_t state = WRONG_NAME;

	// Get all card data
	while(state == WRONG_NAME)
		state = getCardHolderName(&transData.cardHolderData);
	state = WRONG_EXP_DATE;
	while (state == WRONG_EXP_DATE)
		state = getCardExpiryDate(&transData.cardHolderData);
	state = WRONG_PAN;
	while (state == WRONG_PAN)
		state = getCardPAN(&transData.cardHolderData);

	// Get all transaction data
	state = WRONG_DATE;
	while (state == WRONG_DATE)
		state = getTransactionDate(&transData.terminalData);
	
	/*
	// Get current time
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	int month = tm.tm_mon + 1;
	int year = tm.tm_year + 1900;
	*/

	// Check is expired card
	uint8_t ex_yr = ((transData.cardHolderData.cardExpirationDate[3] - 48) * 10) + (transData.cardHolderData.cardExpirationDate[4] - 48);
	uint8_t tr_yr = ((transData.terminalData.transactionDate[3] - 48) * 10) + (transData.terminalData.transactionDate[4] - 48);
	if (tr_yr <= ex_yr)
	{
		if (tr_yr == ex_yr)
		{
			uint8_t ex_mo = ((transData.cardHolderData.cardExpirationDate[0] - 48) * 10) + (transData.cardHolderData.cardExpirationDate[1] - 48);
			uint8_t tr_mo = ((transData.terminalData.transactionDate[0] - 48) * 10) + (transData.terminalData.transactionDate[1] - 48);
			if (tr_mo <= ex_mo)
			{
				state = CARD_OK;
			}
			else {
				state = EXPIRED_CARD;
				transData.transState = EXPIRED_CARD;
				sequenceNumber++;
				transData.transactionSequenceNumber = sequenceNumber;
				printf("Declined Expired card\n");
				saveTransaction(&transData);
			}
		}
		else {
			state = CARD_OK;
		}
	}
	else {
		state = EXPIRED_CARD;
		transData.transState = EXPIRED_CARD;
		sequenceNumber++;
		transData.transactionSequenceNumber = sequenceNumber;
		printf("Declined Expired card\n");
		saveTransaction(&transData);
	}


	// If card is not Expired Continue
	if (state == CARD_OK)
	{
		uint8_t  status = INVALID_AMOUNT;
		

		// Get transaction amount
		while (status == INVALID_AMOUNT)
		{
			status = getTransactionAmount(&transData.terminalData);
		}

		// Check is below max account 
		status = isBelowMaxAmount(&transData.terminalData);
		if (status == EXCEED_MAX_AMOUNT)
		{
			transData.transState = EXCEED_MAX_AMOUNT;
			sequenceNumber++;
			transData.transactionSequenceNumber = sequenceNumber;
			printf("Declined Amount Exceeding Limit\n");
			saveTransaction(&transData);
		}
		else
		{
			state = 0;


			// Check if the account is valid
			state = isValidAccount(&transData.cardHolderData,&accountRefrence);

			// Not valid
			if (state == ACCOUNT_NOT_FOUND)
			{
				transData.transState = EXCEED_MAX_AMOUNT;
				sequenceNumber++;
				transData.transactionSequenceNumber = sequenceNumber;
				printf("Declined Account is not valid\n");
			}
			else {
				// Valid
				status = 0 ;

				// Check if the amount is available
				status = isAmountAvailable(&transData.terminalData, &accountRefrence);
				if (status == LOW_BALANCE)
				{
					// Low balance 
					sequenceNumber++;
					transData.transactionSequenceNumber = sequenceNumber;
					transData.transState = LOW_BALANCE;
					printf("Declined Insuffecient Funds\n");
					saveTransaction(&transData);
				}
				else {
					// Available amount
					state = 0;
					accountRefrence.balance -= transData.terminalData.transAmount;
					sequenceNumber++;
					transData.transactionSequenceNumber = sequenceNumber;
					transData.transState = APPROVED;
					saveTransaction(&transData);
				}
			}
		}

		
		 

	}

}