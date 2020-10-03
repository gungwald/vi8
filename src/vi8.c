#include <stdint.h>

#define TEXT_LINE_1 0x0400
 
/*
Table 7-2. Text screen video RAM addresses.
Line Number
0
1
2
3
4
5
6
7
8
9
10
11
Base Address
$400
$480
$500
$580
$600
$680
$700
$780
$428
$4A8
$528
$5A8
Line Number
12
13
14
15
16
17
18
19
20
21
22
23
Base Address
$628
$6A8
$728
$7A8
$450
$400
$550
$500
$650
$600
$750
$700
*/

void main(void)
{
	uint8_t *p;

	for (p = (uint8_t *) 0x0400; 
			p < (uint8_t *) 0x0440; ++p)
		*p = 'A';
}
