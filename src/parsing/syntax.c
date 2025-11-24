#include "../../include/minishell.h"

int check_simple_command(t_tokens *tokens) {
    t_tokens *last = tokens;

    if (!tokens) {
        printf("Empty command.\n");
        return 0; //? exit-status
    }
    if (tokens->type == TOKEN_PIPE) {
        printf("Syntax error: command cannot start with '|'\n");
        return 0;
    }
    int i = 0;
    while (tokens) {
        
        if ((tokens->type >= 0 && tokens->type <= 3) && i == 0)
        {
            write(2, "-bash: syntax error near unexpected token ", 42);
            write(2, tokens->value, 1);
            write(2, "\n", 1);
            return (0);
        }
        last = tokens;
        tokens = tokens->next;
        i++;
    }
    if (last && last->type == TOKEN_PIPE) {
        printf("Syntax error: command cannot end with '|'\n");
        return 0;
    }
    return 1;
}
