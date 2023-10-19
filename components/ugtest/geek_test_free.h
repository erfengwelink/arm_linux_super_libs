#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)
#define RED(a) COLOR(a, 31)

//链表实现
int test_run_flag;
#define EXPECT(a, b, comp) { \
    __typeof(a) val_a = (a), val_b = (b); \
    if (!(val_a comp val_b)) { \
        printf("%s:%d: Failure\n", __FILE__, __LINE__); \
        printf("Expected (%s %s %s):\n", #a, #comp, #b); \
        printf("    Which is: (%d %s %d)\n", val_a, #comp, val_b); \
        test_run_flag = 0; \
    } \
}
#define EXPECT_EQ(a, b) EXPECT(a, b, ==)//Defining a macro called EXPECT_EQ that takes two arguments, a and b. It then calls the macro EXPECT with the arguments a, b, and ==.

#define EXPECT_LT(a, b) EXPECT(a, b, <)
#define EXPECT_GT(a, b) EXPECT(a, b, >)
#define EXPECT_NE(a, b) EXPECT(a, b, !=)

typedef void (*test_function_t)();

struct test_function_info_t {
    test_function_t func;  // 测试用例函数指针，指向测试用例函数
    const char *name; // 指向测试用例名称
    struct test_function_info_t *next;
};
struct test_function_info_t head, *tail = &head;

void add_test_function(const char *name, test_function_t func) {
    struct test_function_info_t *node;
    node = (struct test_function_info_t *)malloc(sizeof(struct test_function_info_t));
    node->func = func;
    node->name = name;
    node->next = NULL;
    tail->next = node;
    tail = node;
    return ;
}

void clear_node(struct test_function_info_t *node) {
    if (node == NULL) {
        return ;
    }
    free(node);
    return ;
}
void clear(struct test_function_info_t *head) {
    if (head == NULL) return ;
    struct test_function_info_t *p = head->next, *q;
    while (p != NULL) {
        q = p->next;
        clear_node(p);
        p = q;
    }
    free(p);
    return ;
}





#define TEST(test_name, func_name) void test_name##_##func_name(); __attribute__((constructor)) void register_##test_name##_##func_name() {  add_test_function(#func_name "." #test_name,      test_name##_##func_name); } void test_name##_##func_name()

int RUN_ALL_TESTS() {
    struct test_function_info_t *p = head.next;
    for (; p; p = p->next) {
        //printf("[ RUN      ] %s\n", p->name);
        printf(GREEN("[ RUN      ]"));
        printf("%s\n", p->name);
        test_run_flag = 1;
        long long t1 = clock();
        p->func();
        long long t2 = clock();
        if (test_run_flag) {
            printf(GREEN("[       OK ] "));
        } else {
            printf(RED("[  FAILED  ] "));
        }
        printf("%s", p->name);
        printf(" (%.0lf μs)\n\n", 1.0 * (t2 - t1) / CLOCKS_PER_SEC * 1000 * 1000);//加一个* 1000，单位改成微秒
    }
    clear(&head);
    return 0;
}