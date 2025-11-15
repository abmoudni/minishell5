#include "../../include/minishell.h"

char    **parse_command(char *input)
{
    char    **token;
    token = ft_split(input, ' ');
    return (token);
}

void    free_array(char **arr)
{
    int i;
    
    if (!arr)
        return;
    
    i = 0;
    while (arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}