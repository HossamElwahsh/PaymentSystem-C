#include "server.h"#include <string.h>
/* Standard Library */
#include <string.h>

/* Card Module */
#include "../Card/card.h"
/* Terminal Module */
#include "../Terminal/terminal.h"
/* Server Module */
#include "server.h"

/* Accounts Database */
ST_accountsDB_t  accountsDB[255] =               /* Visa */                               /* MasterCard */
                                    /* Balance |  State |        PAN       */  /* Balance |  State |        PAN       */
                                   {{  12000   , BLOCKED, "4728459258966333"}, {  68600.3 , RUNNING, "5183150660610263"},
                                    {  5805.5  , RUNNING, "4946084897338284"}, {  5000.3  , RUNNING, "5400829062340903"},
                                    {  90360.12, RUNNING, "4728451059691228"}, {  1800000 , RUNNING, "5191786640828580"},
                                    {  16800.58, RUNNING, "4573762093153876"}, {  40800   , RUNNING, "5367052744350494"},
                                    {  520.9   , RUNNING, "4127856791257426"}, {  18900.45, RUNNING, "5248692364161088"},
                                    {  6900.33 , RUNNING, "4946099660091878"}, {  1047751 , RUNNING, "5419558003040483"},
                                    {  200000  , RUNNING, "4834699064563433"}, {  3026239 , RUNNING, "5116136307216426"},
                                    {  5000000 , RUNNING, "4946069587908256"}, {  9362076 , RUNNING, "5335847432506029"},
                                    {  25600   , RUNNING, "4946085117749481"}, {  10662670, RUNNING, "5424438206113309"},
                                    {  895000  , RUNNING, "4946099683908835"}, {  1824    , RUNNING, "5264166325336492"}};
/* Accounts Database Index */
uint8_t Glb_AccountsDBIndex = 0;

/* Transactions Database */
ST_transaction_t transactionsDB[255] = {0};
/* Transactions Database Index */
static uint8_t Glb_TransactionsDBIndex = 0;

/* ********************** Includes Section End   ********************** */


/* ********************** Main Terminal Functions Start ******************************************** */


/*
 Name: isValidAccount
 Input: Pointer to Card Data structure, 
 Input: Pointer to Card Data structure, Pointer to AccountsDB structure
 Output: EN_sreverError_t Error or No Error
 Description: 1. This function will take card data and validate if the account related to this card exists or not.
              2. It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
              3. If the PAN doesn't exist will return ACCOUNT_NOT_FOUND, else will return SERVER_OK and return a reference 
                 to this account in the DB.
*/
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    /* Define local variable to set the error state, No Error */
    EN_serverError_t Loc_ErrorState = SERVER_OK;
    /* Define local variable to set the flag state, Flag Down */
    EN_flagState_t Loc_Flag = FLAG_DOWN;
    
    /* Loop: Until Account is found or until the end of accountsDB */
    for (uint8_t Loc_Index = 0; Loc_Index < 255; Loc_Index++)
    {
        /* Check 1: Account is found */
        if (!strcmp(cardData->primaryAccountNumber, accountsDB[Loc_Index].primaryAccountNumber))
        {
            /* Copy Account details from accountsDB to passed pointer */
            *accountRefrence = accountsDB[Loc_Index];
            /* Update accountsDB Index */
            Glb_AccountsDBIndex = Loc_Index;

            /* Update flag state, Account is Found! */
            Loc_Flag = FLAG_UP;            
            break;
        }
    }

    /* Check 2: Account is not found */
    if (Loc_Flag == FLAG_DOWN)
    {
        /* Update error state, Account Not Found! */
        Loc_ErrorState = ACCOUNT_NOT_FOUND;
    }    

    return Loc_ErrorState;
}

/*
 Name: listSavedTransactions
 Input: void
 Output: void
 Description: 
*/
void listSavedTransactions(void)
{
    for(uint8_t Loc_u8Index = 0; Loc_Index <= Glb_TransactionsDBIndex; Loc_Index++)
    {
        printf("\n");

        printf(" ##########################\n");
        printf(" Transaction Sequence Number: %d\n", transactionsDB[Loc_u8Index].transactionSequenceNumber);
        printf(" Transaction Date: %s\n", transactionsDB[Loc_u8Index].terminalData.transactionDate);
        printf(" Transaction Amount: %.3f\n", transactionsDB[Loc_u8Index].terminalData.transAmount);
        printf(" Transaction State: %c\n", transactionsDB[Loc_u8Index].transState);
        printf(" Terminal Max Amount: %.3f\n", transactionsDB[Loc_u8Index].terminalData.maxTransAmount);
        printf(" Cardholder Name: %s\n", transactionsDB[Loc_u8Index].cardHolderData.cardHolderName);
        printf(" PAN: %s\n", transactionsDB[Loc_u8Index].cardHolderData.primaryAccountNumber);
        printf(" Card Expiration Date: %s\n", transactionsDB[Loc_u8Index].cardHolderData.cardExpirationDate);
        printf(" ##########################\n");

        printf("\n");
    }
}

/* ********************** Main Terminal Functions End ********************************************** */

/* ********************** TEST Functions Start ***************************************************** */

void isValidAccountTest(void)
{
    printf("\n");
	printf("Tester name     : Abdelrhman Walaa\n");
	printf("Function name   : isValidAccount\n\n");

	printf("Test Case 1:\n");
	printf("Input Data      : \n");
	printf("Expected Result : ACCOUNT_NOT_FOUND\n");
	printf("Actual Result   : ");
}

void listSavedTransactionsTest(void)
{
    printf("\n");
	printf("Tester name     : Abdelrhman Walaa\n");
	printf("Function name   : listSavedTransactions\n\n");

	printf("Test Case 1:\n");
	printf("Input Data      : \n");
	printf("Expected Result : ACCOUNT_NOT_FOUND\n");
	printf("Actual Result   : ");
}

/* ********************** TEST Functions End  ***************************************************** */


int main()
{
    
}