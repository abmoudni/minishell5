/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 02:46:01 by mtawil            #+#    #+#             */
/*   Updated: 2025/11/24 14:41:50 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int builtin_export(char **args, t_env_and_exit *shell)
{
    char *equal_sign;
    char *name;
    char *value;
    char *clean_value;
    int i;
    
    if (!args[1])
    {
        i = 0;
        while (shell->env[i])
        {
            printf("declare -x %s\n", shell->env[i]);
            i++;
        }
        return (0);
    }
    
    i = 1;
    while (args[i])
    {
        equal_sign = ft_strchr(args[i], '=');
        if (!equal_sign)
        {
            i++;
            continue;
        }
        
        name = ft_substr(args[i], 0, equal_sign - args[i]);
        value = ft_strdup(equal_sign + 1);
        
        if (!name || !value)
        {
            if (name) free(name);  // Free both!
            if (value) free(value);
            return (1);
        }
        
        clean_value = remove_quotes(value);
        free(value);
        
        if (!clean_value)  // Check for NULL!
        {
            free(name);
            return (1);
        }
        
        set_env_value(name, clean_value, shell);
        
        free(name);
        free(clean_value);
        i++;
    }
    
    return (0);
}