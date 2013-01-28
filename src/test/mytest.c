#include <stdlib.h>
#include <stdio.h>

#include "ctest.h"
#include "../mutils.h"

CTEST_DATA(mgetopt1){
    char *arg_v[3];
    char *optstr; 
};

CTEST_SETUP(mgetopt1){
    data->optstr = "ab:";
    data->arg_v[0] = "test";
    data->arg_v[1] = malloc(10);
    data->arg_v[2] = malloc(10);
}

CTEST_TEARDOWN(mgetopt1){
    int i;

    for (i = 0; i < 3; i++) free(data->arg_v[i]);
}

CTEST2(mgetopt1, option_wo_arg){
    data->arg_v[1] = "-a";
    optind = 1;

    ASSERT_EQUAL('a', mgetopt(2, data->arg_v, data->optstr));
}

CTEST2(mgetopt1, option_required_arg_missing){
    data->arg_v[1] = "-b";
    optind = 1;

    ASSERT_EQUAL('?', mgetopt(2, data->arg_v, data->optstr));
}

CTEST2(mgetopt1, option_with_required_arg){
    data->arg_v[1] = "-b";
    data->arg_v[2] = "testarg";
    optind = 1;

    ASSERT_EQUAL('b', mgetopt(3, data->arg_v, data->optstr));
    ASSERT_STR(data->arg_v[2], optarg);

}

CTEST2(mgetopt1, invalid_option){
    data->arg_v[1] = "-c";
    optind = 1;

    ASSERT_EQUAL('?', mgetopt(2, data->arg_v, data->optstr));
}

CTEST_DATA(mgets){
    FILE *fp;
    char *s;
};

CTEST_SETUP(mgets){
}

CTEST_TEARDOWN(mgets){
}

//CTEST2(mgets, empty_file){
//    char *s;
//
//    s = mgets(data->f_empty);
//    ASSERT_STR("", s);
//    free(s);
//}

CTEST2(mgets, line1){
    data->fp = fopen("mgets_test2.txt", "r");
    data->s = mgets(data->fp);
    ASSERT_STR("string number 1.", data->s);
    free(data->s);
    fclose(data->fp);
}

CTEST2(mgets, line2){
    data->fp = fopen("mgets_test2.txt", "r");
    data->s = mgets(data->fp);
    free(data->s);
    data->s = mgets(data->fp);
    ASSERT_STR("string number 2.", data->s);
    free(data->s);
    fclose(data->fp);
}

CTEST2(mgets, eof){
    data->fp = fopen("mgets_test2.txt", "r");
    data->s = mgets(data->fp);
    free(data->s);
    data->s = mgets(data->fp);
    free(data->s);
    data->s = mgets(data->fp);
    ASSERT_STR(NULL, data->s);
    free(data->s);
    fclose(data->fp);
}

CTEST2(mgets, emptyfile){
    data->fp = fopen("mgets_test1.txt", "r");
    data->s = mgets(data->fp);
    ASSERT_STR(NULL, data->s);
    free(data->s);
    fclose(data->fp);
}
