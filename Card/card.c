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


ST_cardData_t MyCard;


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
	printf("\nEnter Your Name: \t");
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

    // PAN integer array
    uint8_t primaryAccountNumber[20] = {0};

    // prompt user to enter PAN
    printf("Enter card's primary account number (PAN):\n");
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

        // convert string digits to integers and save in `primaryAccountNumber` array
        primaryAccountNumber[i] = (uint8_t)(panStr[i] - '0');

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


/************************************************************************************************************
 * Function : getCardHolderNameTest()
 *//**
 * Description:
 *
 * This function is used to test the getHolderName() function, to validate the card data.
 *
 * PRE-CONDITION:     the Card_Data exist and struct should be created, so that we can store/validate the card name.
 * POST-CONDITION:    the cardName passed the listed test cases. 
 *
 * @param [in]		void
 *
 * @return 			void
 * \b Example:
 * @code
 * getCardHolderNameTest();
 * @endcode
 *
 * @see getCardHolderName()
 * Check the four cases:
 * 1- if the entered name is pure alphabetic and number of characters is >= 20 and <=24 or not.
 * 2- if the entered name contains an alphabetic characters or not.
 * 3- if the entered name is Null or not.
 * 4- if the entered name contains a non alphabetic characters or not.
 *
 ****************************************************************************************************************************************/

void getCardHolderNameTest(void)
{
	uint8_t i, WrongString[] = "Wrong Name, Please check your entered name!\n";
	printf("Tester Name: Mahmoud_Mowafey\n");
	printf("Function Name: cardHolderName\n\n\n");
	uint8_t WrongName = 0;
	for ( i=0 ; i<5 ; i++ )
	{
		WrongName = getCardHolderName(&MyCard);
		printf("\nTest Case_%d: \n",i);
		printf("Input Data: %s\n",MyCard.cardHolderName);
		printf("Expected Result: Your name's characters must be without non alphabetic and must be >20 && <24\n");
		if( WrongName == WRONG_NAME )
		{
			printf("Actual Result: %s\n",WrongString);
		}
		else
			printf("Actual Result: Your name is good\n");
	}
}

