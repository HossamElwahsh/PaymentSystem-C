#ifndef PAYMENTSYSTEM_TEST_H
#define PAYMENTSYSTEM_TEST_H

#include <stdlib.h>
#include "card.h"
#define TEST_DIR "../Test/TestCases/"
#define CONCAT(STR1, STR2) STR1 STR2

/**
 * Retrieves full file name for test case (input data / expected result) depending on fileType
 * @param fileType [in] 1 return input data file, 0 return expected result file
 * @param i [in] test case number (0 indexed)
 * @param test_dir [in] main test dir
 * @param testFilename [out] full filename for the file requested
 */
void getTestFileName(int i, char * test_dir, char * testFilename, uint8_t fileType);

/**
 * Test function for @see ../Card/card.c:getCardPan()
 * */
void getCardPANTest(void);

#endif //PAYMENTSYSTEM_TEST_H
