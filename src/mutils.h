/* See LICENSE file for copyright and license details. */

#ifndef MUTILS_H
#define MUTILS_H

extern int optopt;
extern int optind;
extern char *optarg;

int mgetopt(int argc, char *argv[], const char *optstr);

char *mgets(FILE * fp);

#endif
