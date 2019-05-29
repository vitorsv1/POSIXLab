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
            
            time_t begin,end;
            begin = time(NULL);
            int test = all_tests[i].function();
            end = time(NULL);
            float time_taken = difftime(end,begin);
            
            // Teste passou
            if (test >= 0){
                printf(KNORMAL "%s: " KGRN "[PASS]\n" KNORMAL, all_tests[i].name);
                printf("%s demorou " KBLU "%f" KNORMAL " sec\n", all_tests[i].name, time_taken);
                return test;
            }
            
            printf("%s demorou " KBLU "%f" KNORMAL" sec\n"  , all_tests[i].name, time_taken);

            return -1;
        }
    }

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
            printf(KNORMAL"\n%s : " KRED "[FAIL] " KNORMAL "com sinal: %s\n", all_tests[j].name, strsignal(WTERMSIG(test)));
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
