
clock_t begin;   


void CHandler (int sig){
    char  c;

    signal(sig, SIG_IGN);
    printf("\nDid you hit Ctrl-C!\n"
    "Do you really want to quit? [y/n]: ");
    c = getchar();
    if (c == 'y' || c == 'Y')
        kill(0,SIGKILL);
}


int main() {
    int size = sizeof(all_tests)/sizeof(test_data);

    printf("Running %d tests:\n", size);
    printf("==============================================\n\n");
    
    //Contador e lista de forks e pids
    int pass_count = 0;
    pid_t piaidi[size];
    pid_t forqui[size];

    //Pipe e buffer
    char buffer;
    int fds[size];


    //Loop para criar filhos e wait
    for (int i = 0; i < size; i++){
        
        //Arquivo temporario
        fds[i] = open("/tmp", __O_TMPFILE | O_RDWR, 0600);
        forqui[i] = fork();

        if (forqui[i] == 0){
            //Setar o alarm
            alarm(7);
            //Setar o dup 
            dup2(fds[i], 1);
            
            //ignorar o ctrl-c no filho
            signal(SIGINT, SIG_IGN);

            clock_t end;
            begin = clock();
            int test = all_tests[i].function();
            end = clock();
            double time_taken = (double) (end - begin) / CLOCKS_PER_SEC;
            
            // Teste passou
            if (test >= 0){
                printf(KNORMAL "%s: " KGRN "[PASS]\n" KNORMAL, all_tests[i].name);
                printf("%s demorou " KBLU "%lf sec\n" KNORMAL, all_tests[i].name, time_taken);
                return test;
            }

            printf("%s demorou " KBLU "%lf sec\n" KNORMAL, all_tests[i].name, time_taken);

            return -1;
        }
    }

    struct sigaction s;
    s.sa_handler = CHandler;
    sigemptyset(&s.sa_mask);
    sigaction(SIGINT,&s,NULL);
    s.sa_flags = 0;

    for (int j = 0; j < size; j++){
        int test;
        piaidi[j] = waitpid(forqui[j],&test, WUNTRACED);

        //Recebendo saida 
        if (WIFEXITED(test)){
            printf(KNORMAL "\n%s exit status = " KBLU "%d\n" KNORMAL, all_tests[j].name, WEXITSTATUS(test));
            if (WEXITSTATUS(test) == 0){
                pass_count++;
            }
        }
        
        // Falha e print do erro
        if(WIFSIGNALED(test)){
            clock_t end = clock();
            double time_taken = (double) (end - begin) / CLOCKS_PER_SEC;
            printf(KNORMAL"\n%s : " KRED "[FAIL] " KNORMAL "com sinal: %s\n", all_tests[j].name, strsignal(WTERMSIG(test)));
            printf("%s demorou " KBLU "%lf sec\n" KNORMAL , all_tests[j].name, time_taken);
        }

        //Setar o cursor
        lseek(fds[j], 0, SEEK_SET);

        //Ler o dup 
        while(read(fds[j],&buffer,1)>0){
            printf("%c",buffer);
        }
    } 

    printf("\n\n==============================================\n");
    printf(KGRN "%d" KNORMAL "/%d tests " KGRN "passed\n" KNORMAL, pass_count, size);
    return 0;
}
