/**
 * @Title      	: Card Module
 * @Filename   	: card.c
 * @Authors     : Mahmoud Mowafey, Hossam Elwahsh
 * @Origin Date	: Mar 28, 2023
 * @Version		: 1.0.0
 * @Compiler	: MinGW
 * @Target     	: General Purpose Processor / PCs
 * @Notes		: The code is written with ANSI_C Standard.
 *
 * THIS SOFTWARE IS PROVIDED BY HACKER KERMIT- TEAM_1 at Sprints_Automotiv_BC_W11.
 *
 *
 */

#include "card.h"


/************************************************************************************************************
 * Function : getCardHolderName()
 *//**
 * Description:
 *
 * This function is used to test the getHolderName() function, to validate the card data.
 *
 * PRE-CONDITION:  the Card_Data exist and struct should be created, so that we can store/validate the card name.
 * 
 * POST-CONDITION: the cardName has been stored at the proper field of the argument item.
 *
 * @param [in]		cardData is a pointer to the ST_cardData_t structure that holding data
 * 					about the card, such as cardHolderName, primaryAccountNumber, cardExpirationDate.
 *
 * @return 			EN_cardError_t is a enumeration that contains module errors.
 * \b Example:
 * @code
 * uint8_t var = getCardHolderName();
 * @endcode
 *
 * @see getCardHolderNameTest()
 *
 ************************************************************************************************************/



EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
	printf("Enter Your Name: \t");
	fflush(stdin);
	fflush(stdout);
	gets(cardData->cardHolderName);
	uint8_t i=0, NonAlphabetic = 0;
	while(cardData->cardHolderName[i] !=0)
	{
		/*
		* if the entered name has a non alphabetic characters assign the NonAlphabetic variable.
		*/
		if ( ( ( cardData->cardHolderName[i] >= 65 ) && ( cardData->cardHolderName[i] <= 90 ) ) ||
			 ( ( cardData->cardHolderName[i] >= 97 ) && ( cardData->cardHolderName[i] <= 122 ) )||
			 ( ( cardData->cardHolderName[i] == ' ' ) )
		    )
		{
			NonAlphabetic = 0;
		}
		else
		{
			NonAlphabetic = 1;
			break;
		}
		i++;
	}
	/*
	 * Check if the entered name is greater than 20 and less than 24 characters or not.
	 * Check if the entered name is empty or not.
	 * Check if the entered name is greater than 20 and less than 24 characters.
	 * Check if the entered name has a non alphabetic characters or not.
	 * */
	if( ( strlen(cardData->cardHolderName) == 0 ) ||
			( strlen(cardData->cardHolderName) < 20 ) ||
			( strlen(cardData->cardHolderName) > 24 ) ||
			( NonAlphabetic == 1)
	)
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}
}

/**
 * @author Hossam Elwahsh
 * Description:
 *  This function will ask for the card's Primary Account Number (PAN) and store it in card data
 *  PAN is 20 numeric characters string, 19 chars max. and 16 chars min.
 *
 * @param cardData [out] card data
 * @return WRONG_PAN if PAN is less than 16 or more than 19
 * @return CARD_OK otherwise
 */
EN_cardError_t getCardPAN(ST_cardData_t *cardData){

    // temp variable for user input
    char panStr[25] = {'\0'};

    // prompt user to enter PAN
    printf("Enter card's primary account number (PAN):\t");
    fgets(panStr, sizeof(panStr), stdin);

    // remove trailing newline from string
    char* ptr = strchr(panStr, '\n');
    if (ptr) *ptr = '\0';
    //    panStr[strlen(panStr)] = '\0';

    // Format Check
    // less than 16 or more than 19
//    printf("Card length: %llu\n", strlen(panStr));
//    printf("Card number: %s\n", panStr);
    if(strlen(panStr) < 16 || strlen(panStr) > 19)
    {
//        printf("WRONG_PAN length\n");
        return WRONG_PAN;
    }

    // loop over all characters
    for (int i = 0; i < strlen(panStr); i++) {

        // clear data if any
        for (int j = 0; j < sizeof (cardData->primaryAccountNumber); ++j) {
            cardData->primaryAccountNumber[j] = 0;
        }

        // store PAN in `cardData`
        cardData->primaryAccountNumber[i] = (uint8_t)(panStr[i]);

        // check if any character isn't a digit
        if(!isdigit(panStr[i]))
        {
            return WRONG_PAN;
        }
    }

    return CARD_OK;
}


#include <stdlib.h>
int main2()
{
    ST_cardData_t * cardData = calloc(1, sizeof (ST_cardData_t));
    getCardPAN(cardData);

    return 0;
}


/*****************************************************************************************/
/*    Function Description    : This function will ask for the card expiry date and store it in card data.
*								Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".*/
/*    Parameter in            : None */
/*    Parameter inout         : None */
/*    Parameter out           :	ST_cardData_t* cardData */
/*    Return value            : return the WRONG_EXP_DATE If the card expiry date is NULL, 
*								less or more than 5 characters, or has the wrong format.
*								return CARD_OK otherwise */
/*    Requirment              : */
/*****************************************************************************************/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    uint8_t expiry_date[10];

	uint8_t month = 0;
	uint8_t yearIsNotNumber = 0;
	for (char counter = 0; counter <= EXPIRY_DATE_MAX_SIZE; counter++)
	{
		expiry_date[counter] = 0;
	}
	printf("Enter card expiry date:\t");
	fflush(stdin);
	fflush(stdout);
	gets(expiry_date);

	// Check the length of the date entered
	if ((strlen(expiry_date) > EXPIRY_DATE_MAX_SIZE) || (strlen(expiry_date) == 0) || (strlen(expiry_date) < EXPIRY_DATE_MAX_SIZE))
		return WRONG_EXP_DATE;
	else
	{
		// Calculate the value of months entered in the date
		month = ((expiry_date[0] - 48) * 10) + (expiry_date[1] - 48);


		// Check all indexes of year entered is numbers only
		if (expiry_date[3] >= '0' && expiry_date[3] <= '9')
			yearIsNotNumber = 0;
		else
			yearIsNotNumber = 1;
		if (expiry_date[4] >= '0' && expiry_date[4] <= '9')
			yearIsNotNumber = 0;
		else
			yearIsNotNumber = 1;


		// Check if the month number is valid and year num is only number and there is '/' in the entered date
		if (month == 0 || month > 12 || yearIsNotNumber || expiry_date[2] != '/')
			return WRONG_EXP_DATE;
		else
		{
			for (char counter = 0; counter < EXPIRY_DATE_MAX_SIZE; counter++)
			{
				cardData->cardExpirationDate[counter] = expiry_date[counter];
			}
		}
	}
	return CARD_OK;
}
