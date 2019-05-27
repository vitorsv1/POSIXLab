#include "mintest/macros.h"

int testLoopInfinito() {
    while(1){

    }
    return 0;
}

int testMuitoTrab(){
    for(int i = 0; i <= 99999999999; i++){
        for(int j = 0; j <= 99999999999; j++){
            return 0;
        }    
    }
}

int testSegmentation(){
    raise(SIGSEGV);
    return 0;
}

int testDivision0(){
    raise(SIGFPE);
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
    for(int i = 0; i < 1321325; i++){
        printf("Print-");
    }
    return 0;
}

int testRapido(){
    return 0;
}

int testLento(){
    sleep(600);
    return 0;
}
test_list = { TEST(testLoopInfinito), TEST(testMuitoTrab), TEST(testDivision0), \
              TEST(testFalhaPassa), TEST(testLento), TEST(testPrints), \
              TEST(testSegmentation), TEST(testRapido)};

#include "mintest/runner.h"
