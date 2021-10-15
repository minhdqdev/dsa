/*
Reference:
- https://ourcodeworld.com/articles/read/249/implementation-of-the-soundex-algorithm-function-in-different-programming-languages
*/

#include <stdio.h>
#include <string.h>

static char code[128] = { 0 };

const char* soundex(const char *s)
{
	static char out[5];
	int c, prev, i;
 
	out[0] = out[4] = 0;
	if (!s || !*s) return out;
 
	out[0] = *s++;
 
	/* first letter, though not coded, can still affect next letter: Pfister */
	prev = code[(int)out[0]];
	for (i = 1; *s && i < 4; s++) {
		if ((c = code[(int)*s]) == prev) continue;
 
		if (c == -1) prev = 0;	/* vowel as separator */
		else if (c > 0) {
			out[i++] = c + '0';
			prev = c;
		}
	}
	while (i < 4) out[i++] = '0';
	return out;
}

void add_code(const char *s, int c)
{
	while (*s) {
		code[(int)*s] = code[0x20 ^ (int)*s] = c;
		s++;
	}
}
 
void init()
{
	static const char *cls[] =
		{ "AEIOU", "", "BFPV", "CGJKQSXZ", "DT", "L", "MN", "R", 0};
	int i;
	for (i = 0; cls[i]; i++)
		add_code(cls[i], i - 1);
}