#include <stdio.h>
#include <sput.h>

#include "editbuffer.h"

static void test_ebInit()
{
	
    sput_fail_unless(count_vowels("book")  == 2, "book == 2v");
    sput_fail_unless(count_vowels("hand")  == 1, "hand == 1v");
    sput_fail_unless(count_vowels("test")  == 1, "test == 1v");
    sput_fail_unless(count_vowels("Peter") == 2, "Peter == 2v");
    sput_fail_unless(count_vowels("Apu")   == 2, "Apu == 2v");
}


static void test_no_vowels_present()
{
    sput_fail_unless(count_vowels("GCC") == 0, "GCC == 0v");
    sput_fail_unless(count_vowels("BBC") == 0, "BBC == 0v");
    sput_fail_unless(count_vowels("CNN") == 0, "CNN == 0v");
    sput_fail_unless(count_vowels("GPS") == 0, "GPS == 0v");
    sput_fail_unless(count_vowels("Ltd") == 0, "Ltd == 0v");
}


int main(int argc, char *argv[])
{
    sput_start_testing();

    sput_enter_suite("count_vowels(): Vowels Present");
    sput_run_test(test_vowels_present);

    sput_enter_suite("count_vowels(): No Vowels Present");
    sput_run_test(test_no_vowels_present);

    sput_finish_testing();

    return sput_get_return_value();
}
