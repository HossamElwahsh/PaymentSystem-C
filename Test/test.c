#include <io.h>
#include "test.h"

/**
 * Retrieves full file name for test case (input data / expected result) depending on fileType
 * @param fileType [in] 1 return input data file, 0 return expected result file
 * @param i [in] test case number (0 indexed)
 * @param test_dir [in] main test dir
 * @param testFilename [out] full filename for the file requested
 *//*
void getTestFileName(int i, char * test_dir, char * testFilename, uint8_t fileType)
{
    if(fileType)
    {
        sprintf(testFilename, "%s%d_in", test_dir, i+1);
    }else{
        sprintf(testFilename, "%s%d_ex", test_dir, i+1);
    }
//    printf("filename: %s\n", testFilename);
}*/

/***
 * Runs test cases for getCardPan
 */


//region Card Module
/** *******************************************************
    ******************* CARD MODULE *******************
    *******************************************************/


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
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "getCardHolderName.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    char testCase[256];

    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));
//    ST_cardData_t MyCard;

    // Print Test Header
    printf("==================================\n");
    printf("Tester Name:\tMahmoud Mowafey\n");
    printf("Function Name:\tgetCardHolderName\n");
    printf("==================================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE *fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE *fp_fake_stdin;
        char *inputData;
        char *expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data: %s\n", inputData);
        printf("Expected: %s\n", expectedResult);

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_cardError_t ret = getCardHolderName(cardData);
        // turn on console logs

        printf("Actual Result:\t");
        switch (ret) {
            case CARD_OK:
                printf("CARD_OK\n");
                break;
            case WRONG_NAME:
                printf("WRONG_NAME\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(cardData);
    fclose(fp_test_cases);
}


/*****************************************************************************************/
/**    Function Description    : This function to test getCardExpiryDate
*								Check for the following cases
*								- if the entered date is NULL
*								- if the entered date containing numbers only
*								- if the entered month is valid (Not equal 0 or more than 12)
*								- if the entered date length is 5
*    Parameter in            : None
*    Parameter inout         : None
*    Parameter out           : None
*    Return value            : None
*    Requirment              : None
*
* Test cases @see "Test/TestCases/getCardExpireDate.csv"
*****************************************************************************************/
void getCardExpiryDateTest(void)
{
/*    uint8_t expiry_date[10];

    ST_cardData_t cardData;
    EN_cardError_t error = CARD_OK;
    static char counter1;
    for (char counter = 0; counter <= EXPIRY_DATE_MAX_SIZE; counter++)
    {
        cardData.cardExpirationDate[counter] = 0;
    }
    error = getCardExpiryDate(&cardData);
    printf("Tester name : Matarawy\n");
    printf("Function Name: getCardExpiryDate\n");
    printf("Test Case %d:\n", counter1 + 1);
    counter1++;
    printf("Input Data: %s\n", expiry_date);
    if (error == WRONG_EXP_DATE)
    {
        printf("Expected Result: there is an error in your date please check it again\n");
    }
    else
        printf("Expected Result: %s\n", cardData.cardExpirationDate);
    printf("Actual Result: %s\n", cardData.cardExpirationDate);*/

    /** =============================================*/
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "getCardExpiryDate.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    char testCase[256];

    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tMatarawy\n");
    printf("Function Name:\tgetCardExpiryDate\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE *fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE *fp_fake_stdin;
        char *inputData;
        char *expectedResult;

        printf("\n-------------------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-------------------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data:\t%s\n", inputData);
        printf("Expected:\t%s\n", expectedResult);

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_cardError_t ret = getCardExpiryDate(&cardData);
        // turn on console logs

        printf("\nActual Result: ");
        switch (ret) {
            case WRONG_EXP_DATE:
                printf("\tWRONG_EXP_DATE\n");
                break;
            case CARD_OK:
                printf("\tCARD_OK\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(cardData);
    fclose(fp_test_cases);

}


/***
 * Runs test cases for getCardPan
 */
void getCardPANTest(void) {
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "getCardPan.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    char testCase[256];

    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tHossam Elwahsh\n");
    printf("Function Name:\tgetCardPan\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE *fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE *fp_fake_stdin;
        char *inputData;
        char *expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data: %s\n", inputData);
        printf("Expected: %s\n", expectedResult);

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_cardError_t ret = getCardPAN(cardData);
        // turn on console logs

        printf("Actual Result: ");
        switch (ret) {
            case CARD_OK:
                printf("CARD OK\n");
                break;
            case WRONG_PAN:
                printf("WRONG_PAN\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(cardData);
    fclose(fp_test_cases);
}

//endregion

/** ***************************************************
******************* TERMINAL MODULE *******************
*******************************************************/

void getTransactionDateTest(void) {
    // Print Test Header
    printf("====================================\n");
    printf("Tester Name:\tTarek Gohary\n");
    printf("Function Name:\tgetTransactionDate()\n");
    printf("====================================\n");
    printf("Test Case 1\n");
    printf("Input Data:\tPC's current date programmatically\n");
    printf("Expected Result:\tTERMINAL_OK\n");

    // allocate memory for terminalData
    ST_terminalData_t * terminalData = calloc(1, sizeof(ST_terminalData_t));

    // fetch and validate PC date
    EN_terminalError_t ret = getTransactionDate(terminalData);

    switch (ret) {

        case TERMINAL_OK:
            printf("Actual Result:\tTERMINAL_OK\n");
            break;
        case WRONG_DATE:
            printf("Actual Result:\tWRONG_DATE\n");
            break;
    }

    // free terminalData
    free(terminalData);
}

        /************* push input data to stdin ***************//*
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        *//************* Execute test case ***************//*
        EN_terminalError_t ret = getTransactionDate(terminalData);
        // turn on console logs

        printf("Actual Result: ");
        switch (ret) {
            case WRONG_DATE:
                printf("WRONG_DATE OK\n");
                break;
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(terminalData);
    fclose(fp_test_cases);
}*/


void isCardExpiredTest(void)
{
    /* Variables to be used */
    ST_cardData_t     cardData;
    ST_terminalData_t terminalData;

    printf("\n");
    printf("Tester name     : Abdelrhman Walaa\n");
    printf("Function name   : isCardExpired\n\n");

    printf("Test Case 1:\n");
    printf("Input Data      : \n");
    printf("Expected Result : EXPIRED_CARD\n");
    printf("Actual Result   : ");

    //
}

void getTransactionAmountTest(void)
{
    ST_terminalData_t MyTerminalData;

    uint8_t i, WrongName = 0, WrongString[] = "INVALID_AMOUNT, Please check your transaction amount!\n";
    printf("Tester Name: Mahmoud_Mowafey\n");
    printf("Function Name: getTransactionAmount\n\n\n");
    for (i = 0; i < 5; i++)
    {
        WrongName = getTransactionAmount(&MyTerminalData);
        printf("\nTest Case_%d: \n", i);
        printf("Input Data: %f\n", MyTerminalData.maxTransAmount);
        printf("Expected Result: Your transaction amount should be greater than Zero\n");
        if (WrongName == INVALID_AMOUNT)
        {
            printf("Actual Result: %s\n", WrongString);
        }
        else
            printf("Actual Result: Your operation is done\n");
    }

}

/*****************************************************************************************/
/*    Function Description    : test all possible scenarios, happy-case, and worst-case scenarios. on isBelowMaxAmount function*/
/*    Parameter in            : None */
/*    Parameter inout         : None */
/*    Parameter out           : None */
/*    Return value            : None */
/*    Requirment              : None */
/*
* Test casese 1000 , 1500 , 2000 , 2500 ,3000 , 3500 , 4000 , 4500 , 5000 , 5500 , 6000 , 6500 , 7000 , 7500 , 8000 , 8500 , 9000
*             9500 , 10000 , 10500
* max_amount set to 8000
*/
/*****************************************************************************************/
void isBelowMaxAmountTest(void)
{
    static char counter;
    ST_terminalData_t termData[20];
    EN_terminalError_t error = TERMINAL_OK;
    termData[counter].maxTransAmount = 8000.0f;
    termData[counter].transAmount = 1000.0f + (500.0 * counter);
    error = isBelowMaxAmount(&termData[counter]);
    printf("Tester Name: Matarawy\n");
    printf("Test case : %d\n", counter + 1);
    printf("Input Data: maxTransAmount = 8000 and transAmount = %2.f\n", termData[counter].transAmount);
    if (error == EXCEED_MAX_AMOUNT)
        printf("Expected Result: Your amount is more than the max amount\n");
    else
        printf("Expected Result: Your amount is OK\n");
    if (error == TERMINAL_OK)
        printf("Actual Result: Your amount is OK\n\n\n\n");
    else
        printf("Actual Result:  amount is more than the max amount \n\n\n\n");

    counter++;
}


/**
 * Runs test cases for setMaxAmount()
 */
void setMaxAmountTest(void) {
    // test cases init
    char* test_cases_filename = CONCAT(TEST_DIR, "setMaxAmount.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    char testCase[256];
    ST_terminalData_t* terminalData = calloc(1, sizeof(ST_terminalData_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tHossam Elwahsh\n");
    printf("Function Name:\tsetMaxAmount\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE* fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        char* inputData;
        char* expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data: %s\n", inputData);
        printf("Expected: %s\n", expectedResult);

        /************* Execute test case ***************/
        EN_terminalError_t ret = setMaxAmount(terminalData, atof(inputData));
        // turn on console logs

        printf("Actual Result: ");
        switch (ret) {
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
            case INVALID_MAX_AMOUNT:
                printf("INVALID_MAX_AMOUNT\n");
                break;
        }

        i++; // next test case
    }

    free(terminalData);
    fclose(fp_test_cases);
}


/**
 * Runs test cases for isValidCardPAN()
 */
void isValidCardPANTest(void) {
    // test cases init
    char *test_cases_filename = CONCAT(TEST_DIR, "isValidCardPAN.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    ST_cardData_t *cardData = calloc(1, sizeof(ST_cardData_t));
    char testCase[256];

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tHossam Elwahsh\n");
    printf("Function Name:\tisValidCardPAN\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE *fp_test_cases;
    int i = 0;

    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        char *inputData;
        char *expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data: %s\n", inputData);
        printf("Expected: %s\n", expectedResult);

        // clear data
        for (int j = 0; j < sizeof (cardData->primaryAccountNumber); ++j) {
            cardData->primaryAccountNumber[j] = 0;
        }

        // set test case input
        for (int j = 0; j < strlen(inputData); ++j) {
            cardData->primaryAccountNumber[j] = inputData[j];
        }

        /************* Execute test case ***************/
        EN_terminalError_t ret = isValidCardPAN(cardData);

        printf("Actual Result: ");
        switch (ret) {
            case TERMINAL_OK:
                printf("TERMINAL_OK\n");
                break;
            case INVALID_CARD:
                printf("INVALID_CARD\n");
                break;
        }

        i++; // next test case
    }

    free(cardData);
    fclose(fp_test_cases);
}

/** ***************************************************
******************* SERVER MODULE *******************
*******************************************************/

    /**
     * Runs test cases for isBlockedAccount()
     */
void isBlockedAccountTest(void)
{
    // test cases init
    char* test_cases_filename = CONCAT(TEST_DIR, "isBlockedAccount.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    char testCase[256];

    ST_accountsDB_t* accountState = calloc(1, sizeof(ST_accountsDB_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tMahmoud Mowafey\n");
    printf("Function Name:\tisBlokedAccount\n");
    printf("===============================\n");

    // running test cases
//    for (int i = 0; i < testCasesCount; ++i) {

    FILE* fp_test_cases;
    int i = 0;


    // redirect test case inputData to stdin
    fp_test_cases = fopen(test_cases_filename, "r");

    // read test case inputData
//        fgets(testCase, sizeof(testCase), fp_test_cases);
    while (fgets(testCase, sizeof(testCase), fp_test_cases)) {
        // split test case into tokens of input data & expected result (which was delimited by comma)

        FILE* fp_fake_stdin;
        char* inputData;
        char* expectedResult;

        printf("\n-----------------------\n");
        printf("Test Case %d\n", i + 1);
        printf("-----------------------\n");

        inputData = strtok(testCase, testCaseDelimiter);
        expectedResult = strtok(NULL, testCaseDelimiter);

        printf("Input Data: %s\n", inputData);
        printf("Expected: %s\n", expectedResult);

        /************* push input data to stdin ***************/
        fp_fake_stdin = freopen(CONCAT(TEST_DIR, "temp_stdin.txt"), "w+", stdin);
        fprintf(fp_fake_stdin, "%s\n", inputData);
        rewind(fp_fake_stdin);

        /************* Execute test case ***************/
        EN_serverError_t ret = isBlockedAccount(accountState);
        // turn on console logs

        printf("Actual Result: ");
        switch (ret) {
        case SERVER_OK:
            printf("Account is unblocked\n");
            break;
        case BLOCKED_ACCOUNT:
            printf("Account is blocked\n");
            break;
        }

        fclose(fp_fake_stdin);
        i++; // next test case
    }

    free(accountState);
    fclose(fp_test_cases);

}

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


/*****************************************************************************************/
/*    Function Description    : test all possible scenarios, happy-case, and worst-case scenarios. on isAmountAvailable function*/
/*    Parameter in            : None */
/*    Parameter inout         : None */
/*    Parameter out           : None */
/*    Return value            : None */
/*    Requirment              : None */
/*
* Test casese 1000 , 1500 , 2000 , 2500 ,3000 , 3500 , 4000 , 4500 , 5000 , 5500 , 6000 , 6500 , 7000 , 7500 , 8000 , 8500 , 9000
*             9500 , 10000 , 10500
* balance set to 8000
*/
/*****************************************************************************************/
void isAmountAvailableTest(void) {
    static char counter;
    ST_terminalData_t termData[20];
    ST_accountsDB_t accountRefrence;
    accountRefrence.balance = 8000.0f;
    EN_terminalError_t error = TERMINAL_OK;
    termData[counter].maxTransAmount = 8000.0f;
    termData[counter].transAmount = 1000.0f + (500.0f * counter);
    error = isAmountAvailable(&termData[counter], &accountRefrence);
    printf("Tester Name: Matarawy\n");
    printf("Test case : %d\n", counter + 1);
    printf("Input Data: maxTransAmount = %2.f and transAmount = %2.f\n", accountRefrence.balance,
           termData[counter].transAmount);
    if (error == LOW_BALANCE)
        printf("Expected Result: Your amount is more than your acount balance\n");
    else
        printf("Expected Result: Server is OK\n");
    if (error == SERVER_OK)
        printf("Actual Result: Server is OK\n\n\n\n");
    else
        printf("Actual Result:  amount is more than the max amount \n\n\n\n");

    counter++;

    // todo fix missing code
}


/**
 * Call this from main.c to test all project modules
 */
void testAll()
{
    /** CARD MODULE */
    getCardExpiryDateTest();
    getCardHolderNameTest();
//    getCardPANTest();
//    isBlockedAccountTest();
    /** TERMINAL MODULE */
//     todo print terminal module testing
//    getTransactionDateTest();
//    getTransactionAmountTest();
//    setMaxAmountTest();
}
