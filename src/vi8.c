/*
Table 7-2. Text screen video RAM addresses.
Base Address
 0 $400
 1 $480
 2 $500
 3 $580
 4 $600
 5 $680
 6 $700
 7 $780
 8 $428
 9 $4A8
10 $528
11 $5A8
12 $628
13 $6A8
14 $728
15 $7A8
16 $450
17 $400
18 $550
19 $500
20 $650
21 $600
22 $750
23 $700
*/

#define TXTPG1 ((char *) 0x0400)
#define NORMAL(ch) (ch | 0x80)

void main(void)
{
	char *p, *endp;
	char c;

	endp = TXTPG1 + 40;
	c = NORMAL('A');
	for (p = TXTPG1; p < endp; ++p)
		*p = c;
}
