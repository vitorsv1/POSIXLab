static int timeout;

void alarm_handler(int sign){
    timeout = 1;
}


int main() {
    int size = sizeof(all_tests)/sizeof(test_data);

    printf("Running %d tests:\n", size);
    printf("=====================\n\n");
    
    int pass_count = 0;
    pid_t piaidi[size];

    for (int i = 0; i < size; i++){
        pid_t filho = fork();

        if (filho == 0){
            signal(SIGALRM, alarm_handler);
            alarm(5);

            int test = all_tests[i].function();

            return test;
        }
        else{
            piaidi[i] = filho;
        }
    }

    for (int j = 0; j < size; j++){
        int test;
        pid_t p = waitpid(piaidi[j],&test, WUNTRACED);
        if (p == -1){
            if (timeout){
                // alarm
            }
        }
        if (WEXITSTATUS(test) == 0){
            printf("%s: [PASS]\n", all_tests[j].name);
            pass_count++;
        }
        else if(WIFSIGNALED(test)){
            char buffer[50];
            psignal(WTERMSIG(test),buffer);
            printf("\nError -> %s\n", buffer);
        }

    }

    printf("\n\n=====================\n");
    printf("%d/%d tests passed\n", pass_count, size);
    return 0;
}
