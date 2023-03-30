#include <io.h>
#include <fcntl.h>
#include "test.h"

/**
 * Retrieves full file name for test case (input data / expected result) depending on fileType
 * @param fileType [in] 1 return input data file, 0 return expected result file
 * @param i [in] test case number (0 indexed)
 * @param test_dir [in] main test dir
 * @param testFilename [out] full filename for the file requested
 */
void getTestFileName(int i, char * test_dir, char * testFilename, uint8_t fileType)
{
    if(fileType)
    {
        sprintf(testFilename, "%s%d_in", test_dir, i+1);
    }else{
        sprintf(testFilename, "%s%d_ex", test_dir, i+1);
    }
//    printf("filename: %s\n", testFilename);
}

/***
 * Runs test cases for getCardPan
 */
void getCardPANTest(void)
{
    // test init
    int testCasesCount = 3;
    char test_input_data_filename[50];
    char test_expected_result_filename[50];
    char * test_dir = CONCAT(TEST_DIR, "getCardPan_");

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

        getTestFileName(i, test_dir, test_input_data_filename, 1);

        // redirect test case inputData to stdin
        fp_input_data = freopen(test_input_data_filename, "r", stdin);

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

        fclose(fp_input_data);
    }
}

/*
int main()
{
    getCardPANTest();
}*/
