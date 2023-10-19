#include <stdio.h>

#include <stdint.h>
#include "../ugtest/geek_test_free.h"
// #include "../stack/list.h"
#include "../stack/stack.h"

#define logDebug printf

void p_func(void)
{
    int i = 5, j = 6, k = 7;
	int *ip1 = &i, *ip2 = &j;

    int **ipp;

    ipp = &ip1;

    printf("**ipp = %x\n", **ipp);

    printf("*ipp = %x\n", *ipp);
    printf("*ip1 = %x\n", *ip1);
    printf("*ip2 = %x\n", *ip2);

    *ipp = ip2;
    printf(" *ipp = ip2; \r\n=======================\r\n\n");

    printf("**ipp = %x\n", **ipp);
    printf("*ipp = %x\n", *ipp);
    printf("*ip1 = %x\n", *ip1);
    printf("*ip2 = %x\n", *ip2);

    *ipp = &k;

    printf(" *ipp = &k; \r\n=======================\r\n\n");

    printf("**ipp = %x\n", **ipp);
    printf("*ipp = %x\n", *ipp);
    printf("*ip1 = %x\n", *ip1);
    printf("*ip2 = %x\n", *ip2);


}


int is_prime(int x) {
    for (int i = 2; i * i < x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}

// TEST(test1, test_is_prime) {
//     EXPECT_EQ(is_prime(3), 1);
//     EXPECT_EQ(is_prime(5), 1);
//     EXPECT_EQ(is_prime(7), 1);
// }

// List glist = {0};
// void gdestroy(void *data)
// {
//     printf("gdestroy %x\n", (int)data);
//     free(data);
// }

// int gstack_test0(void)
// {
//     stack_init(&glist, gdestroy);

//     return stack_size(&glist);
// }

// int gstack_push(int val)
// {
//     stack_push(&glist, (void *)val);
//     return stack_size(&glist);
// }

// TEST(test2, test_stack) {
//     EXPECT_EQ(gstack_test0(), 0);
//     EXPECT_EQ(gstack_push(5), 1);
//     EXPECT_EQ(gstack_push(4), 2);
//     EXPECT_EQ(gstack_push(3), 3);
//     EXPECT_EQ(gstack_push(2), 4);
//     EXPECT_EQ(gstack_push(1), 5);

// }


#include "../cson/cson.h"


struct subtest
{
    int id;
    char *test;
};

struct test
{
    char id;
    short num;
    int max;
    double value;
    char *name;
    struct subtest *sub;
    CsonList *list;
    char *str[2];
    CsonList *charList;
    CsonList *strList;
    char *subjson;
};

CsonModel subModel[] = 
{
    CSON_MODEL_OBJ(struct subtest),
    CSON_MODEL_INT(struct subtest, id),
    CSON_MODEL_STRING(struct subtest, test)
};


CsonModel model[] = 
{
    CSON_MODEL_OBJ(struct test),
    CSON_MODEL_CHAR(struct test, id),
    CSON_MODEL_SHORT(struct test, num),
    CSON_MODEL_INT(struct test, max),
    CSON_MODEL_DOUBLE(struct test, value),
    CSON_MODEL_STRING(struct test, name),
    CSON_MODEL_STRUCT(struct test, sub, subModel, sizeof(subModel)/sizeof(CsonModel)),
    CSON_MODEL_LIST(struct test, list, subModel, sizeof(subModel)/sizeof(CsonModel)),
    CSON_MODEL_ARRAY(struct test, str, CSON_TYPE_STRING, 2),
    CSON_MODEL_LIST(struct test, charList, CSON_MODEL_INT_LIST, CSON_BASIC_LIST_MODEL_SIZE),
    CSON_MODEL_LIST(struct test, strList, CSON_MODEL_STRING_LIST, CSON_BASIC_LIST_MODEL_SIZE),
    CSON_MODEL_JSON(struct test, subjson)
};



TEST(test3, test_cson) {

    char *jsonStr = "{\"id\": 1, \"num\": 300, \"max\": 1000, \"value\": 10.3, \"name\": \"letter\", "
    "\"sub\": {\"id\": 20, \"test\": \"hello world\"},"
    " \"list\": [{\"id\": 21, \"test\": \"hello cson\"}, {\"id\": 22, \"test\": \"hello letter\"}],"
    "\"str\": [\"array1\", \"array2\"],"
    "\"charList\": [1, 12, 52], "
    "\"strList\": [\"str1\", \"str2\"],"
    "\"subjson\":{\"test\": \"hello\"}}";

    struct test *st = csonDecode(jsonStr, model, sizeof(model)/sizeof(CsonModel));
    logDebug("json 0x%08x, id: %d, num: %d, max: %d, value: %f, name: %s\r\nsub: id: %d, test: %s",
        st, st->id, st->num, st->max, st->value, st->name, st->sub ? st->sub->id : 0, st->sub ? st->sub->test : "null");
    logDebug("str: %s %s", st->str[0], st->str[1]);
    CsonList *p = st->list;
    while (p)
    {
        struct subtest *sst = p->obj;
        if (p->obj)
        {
            logDebug("list: id: %d, test: %s", sst->id, sst->test);
        }
        else
        {
            logDebug("list: null");
        }
        p = p->next;
    }
    p = st->charList;
    while (p)
    {
        int sst = (int)(p->obj);
        if (p->obj)
        {
            logDebug("list: int: %d", sst);
        }
        p = p->next;
    }
    p = st->strList;
    while (p)
    {
        char *sst = p->obj;
        if (p->obj)
        {
            logDebug("list: str: %s", sst);
        }
        p = p->next;
    }
    logDebug("subjson: %s", st->subjson);

    char *root = csonEncode(st, model, sizeof(model)/sizeof(CsonModel), 512, 0);
    printf("encode: %s", root);

    csonFreeJson(root);
    csonFree(st, model, sizeof(model)/sizeof(CsonModel));
}

int main(int argc, char *argv[])
{
    // p_func();
    RUN_ALL_TESTS();
    return 0;
}