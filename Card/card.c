/*
 * @Title      	: Card Module
 * @Filename   	: card.c
 * @Author     	: Mahmoud Mowafey
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

#include"card.h"


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

