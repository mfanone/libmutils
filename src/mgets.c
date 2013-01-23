/* See LICENSE file for copyright and license details. */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mgets(FILE * fp)
{
    size_t i = 0, buf = BUFSIZ;
    int c;
    char *s = NULL, *t = NULL;

    assert(fp != NULL);

    if ((s = malloc(buf)) == NULL)
	return s;

    while ((c = fgetc(fp)) != '\n' && c != EOF) {
	if (buf <= i + 2) {
	    buf += i;
	    if ((s = realloc(s, buf)) == NULL)
		return s;
	}
	s[i++] = c;
    }
    if (c == EOF && i == 0)
	return NULL;
    s[i] = '\0';
    buf = strlen(s) + 1;
    t = realloc(s, buf);
    if (t != NULL)
	s = t;

    if (ferror(fp))
	return NULL;

    return s;
}


#ifdef TEST
int main(void)
{
    char *s;

    while (s = mgets(stdin)) {
	printf("\"%s\"\n", s);
    }
    free(s);

    return 0;
}
#endif
