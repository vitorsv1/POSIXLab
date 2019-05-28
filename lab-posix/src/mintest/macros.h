#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h> 
#include <fcntl.h>
#include <string.h> 

#define KGRN  "\x1B[32m"
#define KRED  "\x1B[31m"
#define KNORMAL "\x1B[0m"
#define KBLU  "\x1B[34m"

typedef int (*test_func)();

typedef struct {
    char name[50];
    test_func function;
} test_data;

#define test_printf (printf("%s: ", __func__));printf

#define test_assert(expr, str) { if(!(expr)) { printf("%s: " KRED"[FAIL]" KNORMAL" %s in %s:%d\n", __func__, str, __FILE__, __LINE__); return -1; } }

#define TEST(f) {.name=#f, .function=f}

#define test_list test_data all_tests[]

