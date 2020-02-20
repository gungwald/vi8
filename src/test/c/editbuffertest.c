#include <stdio.h>

#include "editbuffertest.h"

struct EditBuffer b;

int test_ebInit(const char *unusedButRequired)
{
	TINYTEST_EQUAL_MSG(0, ebInit(&b)->length, unusedButRequired);
}

TINYTEST_START_SUITE(EditBuffer);
  TINYTEST_ADD_TEST(test_ebInit,NULL,NULL);
TINYTEST_END_SUITE();


/*
static void test_no_vowels_present()
{
    sput_fail_unless(count_vowels("GCC") == 0, "GCC == 0v");
    sput_fail_unless(count_vowels("BBC") == 0, "BBC == 0v");
    sput_fail_unless(count_vowels("CNN") == 0, "CNN == 0v");
    sput_fail_unless(count_vowels("GPS") == 0, "GPS == 0v");
    sput_fail_unless(count_vowels("Ltd") == 0, "Ltd == 0v");
}
*/
