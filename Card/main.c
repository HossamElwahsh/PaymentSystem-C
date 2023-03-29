/*
 * @Title      	: Card Module
 * @Filename   	: main.c
 * @Author     	: Mahmoud Mowafey
 * @Origin Date	: Mar 28, 2023
 * @Version		: 1.0.0
 * @Compiler	: MinGW
 * @Target     	: General Purpose Processor / PCs
 * @Notes		: The code is written with ANSI_C Standard.
 * THIS SOFTWARE IS PROVIDED BY HACKER KERMIT- TEAM_1
 *
 *
 */


 /**************************************************************************************************************************************/
 /*
 *						Include the required header files
 */
 /**************************************************************************************************************************************/

#include"main.h"

 /**************************************************************************************************************************************/
 /*
 *						Defines/Declare the global variables.
 */
 /**************************************************************************************************************************************/

extern ST_cardData_t MyCard;
extern ST_terminalData_t MyTerminalData;

/**************************************************************************************************************************************/
/*
*						The main_flow for the module, test the correctness of the module
*/
/**************************************************************************************************************************************/

int main(void)
{
	getCardHolderNameTest();
	//getTransactionAmountTest();
}

