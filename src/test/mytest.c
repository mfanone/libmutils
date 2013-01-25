#include <stdlib.h>
#include <stdio.h>

#include "ctest.h"
#include "../mutils.h"

CTEST_DATA(onearg){
    char *arg_v[3];
    char *optstr; 
};

CTEST_SETUP(onearg){
    data->optstr = "ab:";
    data->arg_v[0] = "test";
    data->arg_v[1] = malloc(10);
    data->arg_v[2] = malloc(10);
}

CTEST_TEARDOWN(onearg){
    int i;

    for (i = 0; i < 3; i++) free(data->arg_v[i]);
}

CTEST2(onearg, test1){
    data->arg_v[1] = "-a";
    optind = 1;

    ASSERT_EQUAL('a', mgetopt(2, data->arg_v, data->optstr));
}

CTEST2(onearg, test2){
    data->arg_v[1] = "-b";
    optind = 1;

    ASSERT_EQUAL('?', mgetopt(2, data->arg_v, data->optstr));
}

CTEST2(onearg, test3){
    data->arg_v[1] = "-b";
    data->arg_v[2] = "testarg";
    optind = 1;

    ASSERT_EQUAL('b', mgetopt(3, data->arg_v, data->optstr));
    ASSERT_STR(data->arg_v[2], optarg);

}

CTEST2(onearg, test4){
    data->arg_v[1] = "-c";
    optind = 1;

    ASSERT_EQUAL('?', mgetopt(2, data->arg_v, data->optstr));
}
