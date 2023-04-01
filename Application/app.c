#include "app.h"



static uint32_t sequenceNumber;
static uint8_t setMaxAmount_counter;
static float max_amount = 0;

void appStart(void) {
	//ST_cardData_t cardData;
	//ST_terminalData_t termData;
	ST_transaction_t transData = { 0 };

 	uint8_t state = INVALID_MAX_AMOUNT;

	// Set Max Amount 
	if (setMaxAmount_counter == 0)
	{
		while (state == INVALID_MAX_AMOUNT)
		{
			printf("Enter system Max Amount\n");
			fflush(stdin);
			scanf("%f\n", &max_amount);
			state = setMaxAmount(&transData.terminalData, max_amount);
			setMaxAmount_counter++;
		}
	}

	// Get all card data
	state = WRONG_NAME;
	while(state == WRONG_NAME)
		state = getCardHolderName(&transData.cardHolderData);
	state = WRONG_EXP_DATE;
	while (state == WRONG_EXP_DATE)
		state = getCardExpiryDate(&transData.cardHolderData);
	state = WRONG_PAN;
	while (state == WRONG_PAN)
		state = getCardPAN(&transData.cardHolderData);

	// Get all transaction date
	state = WRONG_DATE;
	while (state == WRONG_DATE)
		state = getTransactionDate(&transData.terminalData);

	// Check is expired card
	/*
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
	}*/


	state = isCardExpired(&transData.cardHolderData, &transData.terminalData);

	// If card is not Expired Continue
	if (state == TERMINAL_OK)
	{
		uint8_t  status = INVALID_AMOUNT;

		// Get transaction amount
		while (status == INVALID_AMOUNT)
		{
			status = getTransactionAmount(&transData.terminalData);
		}

		// Check is below max amount
		status = isBelowMaxAmount(&transData.terminalData);
		if (status == EXCEED_MAX_AMOUNT)
		{
            printf("Declined Amount Exceeding ATM Limit\n");
		}
		else
		{
			/*state = 0;


			// Check if the account is valid
			state = isValidAccount(&transData.cardHolderData,&accountRefrence);

			// Not valid
			if (state == ACCOUNT_NOT_FOUND)
			{
				transData.transState = EXCEED_MAX_AMOUNT;
				sequenceNumber++;
				transData.transactionSequenceNumber = sequenceNumber;
				printf("Declined Account is not valid\n");
				saveTransaction(&transData);
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
					transData.transState = DECLINED_INSUFFECIENT_FUND;
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
			}*/
			state = recieveTransactionData(&transData);
			if (state == APPROVED)
			{
				printf("Transaction Approved.\n");
			}
			else
			{
				transData.transState = state;
				saveTransaction(&transData);
				switch (state)
				{
				case FRAUD_CARD:
                        printf("Fraud card!");
					break;
				case DECLINED_STOLEN_CARD :
					printf("Trx #%u refused, Blocked card\n", transData.transactionSequenceNumber);
					break;
				case DECLINED_INSUFFECIENT_FUND :
					printf("Declined insufficient fund in account\n");
					break;
                case INTERNAL_SERVER_ERROR:
                default:
                        printf("Failed to save Trx. #%u, internal server error. \n",
                               transData.transactionSequenceNumber);
                        break;
				}
			}
		}

	}
	else
	{
		printf("Transaction declined, Reason: Expired card\n");
	}

}

int main()
{
    appStart();
}