/* See LICENSE file for copyright and license details. */

#include <string.h>

int optind = 1;
int optopt;
char *optarg;

int mgetopt(int argc, char *argv[], const char *optstr)
{
    char *p;
    int c;

    if (optind >= argc || argv[optind][0] != '-' 
        || strcmp(argv[optind], "-") == 0)
	return -1;
    if (strcmp(argv[optind], "--") == 0) {
        optind++;
        return -1;
    }
    if ((p = strchr(optstr, argv[optind][1])) == NULL) {
	optopt = argv[optind][1];
	return '?';
    }
    c = argv[optind][1];
    if (*++p == ':') {
        if (argv[optind][2] == '\0') {
            optarg = argv[++optind];
            if (++optind > argc) {
                optopt = c;
                c = '?';
            }
        } else {
	    optarg = &argv[optind][2];
	    optind++;
	}
    } else {
	if (argv[optind][2] != '\0') {
	    argv[optind][1] = '-';
            argv[optind]++;
	} else {
            optind++;
        }
    }
    return c;
}

#ifdef TEST

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int aflag = 0, bflag = 0;
    char *cval = NULL;
    int i, c;

    while ((c = mgetopt(argc, argv, "abc:")) != -1) {
	switch (c) {
	case 'a':
	    aflag = 1;
	    break;
	case 'b':
	    bflag = 1;
	    break;
	case 'c':
	    cval = optarg;
	    break;
	case '?':
	    if (optopt == 'c')
		fprintf(stderr, "Option -%c requires an argument.\n",
			optopt);
	    else if (isprint(optopt))
		fprintf(stderr, "Unknown option -%c.\n", optopt);
	    else
		fprintf(stderr, "Unknown option character \\x%x.\n",
			optopt);
	    return 1;
	default:
	    abort();
	}
    }

    printf("aflag = %d, bflag = %d, cval=%s\n", aflag, bflag, cval);

    for (i = optind; i < argc; i++) {
	printf("Non-option argument %s\n", argv[i]);
    }
    return 0;
}

#endif
