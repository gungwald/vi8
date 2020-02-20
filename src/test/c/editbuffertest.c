#include <stdio.h>

#include "editbuffertest.h"

struct EditBuffer b;
const char *line = "nonsense";
const char *line2 = "silliness";

int test_ebInit(const char *testName)
{
	TINYTEST_EQUAL_MSG(0, ebInit(&b)->length, testName);
}

int test_ebAppendLineCopy(const char *testName)
{
	ebAppendLineCopy(ebAppendLineCopy(ebInit(&b), line), line2);
	TINYTEST_STR_EQUAL_MSG(ebToString(&b, 0), line, testName);
	TINYTEST_STR_EQUAL_MSG(ebToString(&b, 1), line2, testName);
}

int test_ebIsFull(const char *testName)
{
	TINYTEST_FALSE_MSG(ebIsFull(ebInit(&b)), testName);
	TINYTEST_FALSE_MSG(ebIsFull(ebAppendLineCopy(&b, line)), testName);
}

int test_ebToString(const char *testName)
{
	TINYTEST_EQUAL_MSG(0, ebInit(&b)->length, testName);
}

TINYTEST_START_SUITE(EditBuffer);
  TINYTEST_ADD_TEST(test_ebInit,NULL,NULL);
  TINYTEST_ADD_TEST(test_ebAppendLineCopy,NULL,NULL);
  TINYTEST_ADD_TEST(test_ebIsFull,NULL,NULL);
  TINYTEST_ADD_TEST(test_ebToString,NULL,NULL);
TINYTEST_END_SUITE();
