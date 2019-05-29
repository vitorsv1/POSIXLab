#include "mintest/macros.h"

int testLoopInfinito() {
    while(1){

    }
    return 0;
}

int testMuitoTrab(){
    for(int i = 0; i <= 99999; i++){
        for(int j = 0; j <= 9999; j++){
            
        }    
    }
    return 0;
}

int testSegmentation(){
    //raise(SIGSEGV);
    int *p = NULL;
    *p = 9;

    return 0;
}

int testDivision0(){
    //raise(SIGFPE);
    int a = 6/0;
    return 0;
}

int testFalhaPassa(){
    test_assert(1 == 1, "This always succeeds");
    test_assert(2 == 2, "This always succeeds");
    test_assert(0 == 1, "This always fails");
    test_assert(1 == 2, "This always fails");
    return 0;
}

int testPrints(){
    test_printf("Print\n");
    test_printf("Print\n");
    test_printf("Print\n");
    test_printf("Print\n");
    test_printf("Print\n");
    test_printf("Print\n");
    test_assert(3 == 3, "This succeeds");
    return 0;
}

int testRapido(){
    return 0;
}

int testLento(){
    sleep(5);
    return 0;
}
test_list = { TEST(testLoopInfinito), TEST(testMuitoTrab), TEST(testDivision0), \
              TEST(testFalhaPassa), TEST(testLento), TEST(testPrints), \
              TEST(testSegmentation), TEST(testRapido)};



#include "mintest/runner.h"
