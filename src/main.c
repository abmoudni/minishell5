#include "../include/minishell.h"

int main(int ac, char **av, char **env)
{
    char *input;
    (void) av;
    (void) ac;
    

    while(1){
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n"); // readline retrn the NULL  if the the user ENTERD
            break;
        }
        if (*input == '\0')
        {
            free(input);
            continue;
        }
        execute_command(input, env);
        add_history(input);
        free(input);
    }

    return 0;
}