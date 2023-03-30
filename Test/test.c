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
/*
void getCardPANTest(void)
{
    // test init
    int testCasesCount = 3;
    char test_expected_result_filename[50];
    char * test_dir = CONCAT(TEST_DIR, "getCardPan.csv");

    // test case data
    char inputData[25];
    char expectedResult[100];

    ST_cardData_t * cardData = calloc(1, sizeof(ST_cardData_t));

    // Print Test Header
    printf("===============================\n");
    printf("Tester Name:\tHossam Elwahsh\n");
    printf("Function Name:\tgetCardPan\n");
    printf("===============================\n");

    // running test cases
    for (int i = 0; i < testCasesCount; ++i) {
        printf("\n-----------------------\n");
        printf("Test Case %d\n", i+1);
        printf("-----------------------\n");
        FILE *fp_input_data;
        FILE *fp_expected_result;


        // redirect test case inputData to stdin
        fp_input_data = freopen(test_dir, "r", stdin);

        // read test case inputData
        fgets(inputData, sizeof(inputData), fp_input_data);
        rewind(fp_input_data);

        // print inputData data
        printf("Input Data: %s\n", inputData);

        // read and print expected result
        getTestFileName(i, test_dir, test_expected_result_filename, 0);
        fp_expected_result = fopen(test_expected_result_filename, "r");
        fgets(expectedResult, sizeof(expectedResult), fp_expected_result);
        printf("Expected Result: %s\n", expectedResult);
        fclose(fp_expected_result);

        */
/************* Execute test case ***************//*

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

        fclose(fp_input_data);
    }
}
*/

void getCardPANTest_Fix(void)
{
    // test cases init
    char * test_cases_filename = CONCAT(TEST_DIR, "getCardPan.csv");
    const char testCaseDelimiter[2] = ",";

    // test case data
    char testCase[256];

    ST_cardData_t * cardData = calloc(1, sizeof(ST_cardData_t));

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
            char * inputData;
            char * expectedResult;

            printf("\n-----------------------\n");
            printf("Test Case %d\n", i+1);
            printf("-----------------------\n");

            inputData = strtok(testCase, testCaseDelimiter);
            expectedResult = strtok(NULL, testCaseDelimiter);

            printf("Input Data: %s\n", inputData);
            printf("Expected: %s\n", expectedResult);

            /************* push input data to stdin ***************/
//            fputs(inputData, stdin);
//            fprintf(stdin, "%s\n", inputData);
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

    fclose(fp_test_cases);

        // print inputData data


        // read and print expected result
        /*getTestFileName(i, test_dir, test_expected_result_filename, 0);
        fp_expected_result = fopen(test_expected_result_filename, "r");
        fgets(expectedResult, sizeof(expectedResult), fp_expected_result);
        printf("Expected Result: %s\n", expectedResult);
        fclose(fp_expected_result);

        *//*


        fclose(fp_test_cases);*/
//    }
}

int main()
{
    getCardPANTest_Fix();
}


/** *******************************************************
    ******************* TERMINAL MODULE *******************
    *******************************************************/

void getTransactionAmountTest(void)
{
    ST_terminalData_t MyTerminalData;

    uint8_t i, WrongName=0, WrongString[] = "INVALID_AMOUNT, Please check your transaction amount!\n";
    printf("Tester Name: Mahmoud_Mowafey\n");
    printf("Function Name: getTransactionAmount\n\n\n");
    for ( i=0 ; i<5 ; i++ )
    {
        WrongName = getTransactionAmount(&MyTerminalData);
        printf("\nTest Case_%d: \n",i);
        printf("Input Data: %f\n",MyTerminalData.maxTransAmount);
        printf("Expected Result: Your transaction amount should be greater than Zero\n");
        if( WrongName == INVALID_AMOUNT )
        {
            printf("Actual Result: %s\n",WrongString);
        }
        else
            printf("Actual Result: Your operation is done\n");
    }

}


void getTransactionDateTest(void)
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

    if(termError == WRONG_DATE)
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

    if(termError == WRONG_DATE)
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

    if(termError == WRONG_DATE)
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

    if(termError == WRONG_DATE)
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

    if(termError == WRONG_DATE)
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

    if(termError == WRONG_DATE)
    {
        printf("WRONG_DATE\n");
    }
    else
    {
        printf("TERMINAL_OK\n");
    }
}

/**
 * Call this from main.c to test all project modules
 */
void testAll()
{
    /** CARD MODULE */
    // todo print card module testing
//    getCardPANTest();

    /** TERMINAL MODULE */
//     todo print terminal module testing
//    getTransactionDateTest();
//    getTransactionAmountTest();
}
