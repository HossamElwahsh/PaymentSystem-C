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


 /** *******************************************************
     ******************* TERMINAL MODULE *******************
     *******************************************************/

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

void getTransactionDateTest_old(void)
{
    ST_terminalData_t termData;
    EN_terminalError_t termError;

    printf("\n");
    printf("Tester name     : Tarek Gohry\n");
    printf("Function name   : getTransactionDate\n");

    /* Test Date Format Length */
    printf("\nTest Case 1:\n");
    printf("Input Data      : 01/02\n");
    printf("Expected Result : WRONG_DATE\n");
    termError = getTransactionDate(&termData);
    printf("Actual Result   : ");

    if (termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }

    /* Test Year Format */
    printf("\nTest Case 2:\n");
    printf("Input Data      : 01/12/2022222\n");
    printf("Expected Result : WRONG_DATE\n");
    termError = getTransactionDate(&termData);
    printf("Actual Result   : ");

    if (termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }

    /* Test Day Format */
    printf("\nTest Case 3:\n");
    printf("Input Data      : 33/02/2022\n");
    printf("Expected Result : WRONG_DATE\n");
    termError = getTransactionDate(&termData);
    printf("Actual Result   : ");

    if (termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }

    /* Test Month Format */
    printf("\nTest Case 4:\n");
    printf("Input Data      : 02/15/2022\n");
    printf("Expected Result : WRONG_DATE\n");
    termError = getTransactionDate(&termData);
    printf("Actual Result   : ");

    if (termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }

    /* Test Year Format */
    printf("\nTest Case 5:\n");
    printf("Input Data      : 02/12/20az\n");
    printf("Expected Result : WRONG_DATE\n");
    termError = getTransactionDate(&termData);
    printf("Actual Result   : ");

    if (termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }

    /* Test Correct Date Format*/
    printf("\nTest Case 6:\n");
    printf("Input Data      : 01/02/2022\n");
    printf("Expected Result : TERMINAL_OK\n");
    termError = getTransactionDate(&termData);
    printf("Actual Result   : ");

    if (termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }
}

/***
 * Runs test cases for getCardPan
 */
void getTransactionDateTest(void) {
    // test cases init
    char* test_cases_filename = CONCAT(TEST_DIR, "getTransactionDate.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    char testCase[256];

    ST_terminalData_t* terminalData = calloc(1, sizeof(ST_terminalData_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tTarek Gohary\n");
    printf("Function Name:\tgetTransactionDate\n");
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
    char* test_cases_filename = CONCAT(TEST_DIR, "isValidCardPAN.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    ST_cardData_t* cardData = calloc(1, sizeof(ST_cardData_t));
    char testCase[256];

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tHossam Elwahsh\n");
    printf("Function Name:\tisValidCardPAN\n");
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

        // clear data
        for (int j = 0; j < sizeof(cardData->primaryAccountNumber); ++j) {
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


/** *******************************************************
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

/**
 * Call this from main.c to test all project modules
 */
void testAll()
{
    /** CARD MODULE */
    // todo print card module testing
   // getCardPANTest();
    isBlockedAccountTest();
    /** TERMINAL MODULE */
//     todo print terminal module testing
//    getTransactionDateTest();
//    getTransactionAmountTest();
//    setMaxAmountTest();
}
