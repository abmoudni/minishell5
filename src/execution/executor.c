#include "../../include/minishell.h"

void    execute_command(char *input, char **env){
    pid_t pid;
    char **args;
    char *cmd_path;

    args = parse_command(input);
    if (!args || !args[0])
    {
        free_array(args);
        return;
    }
    cmd_path = find_command_path(args[0]);
    if (!cmd_path)
    {
        printf("minishell: %s: command not found\n", args[0]);
        free_array(args);
        return;
    }

    pid = fork();

    if (pid == -1){
        perror("fork");
        free(cmd_path);
        free_array(args);
        return;
    }
    if (pid == 0){
        if (execve(cmd_path, args, env) == -1){
            perror("execve");
            exit(1);
        }

    }else{
        wait(NULL);
    }
    free(cmd_path);
    free_array(args);
}