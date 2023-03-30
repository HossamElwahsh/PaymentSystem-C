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
