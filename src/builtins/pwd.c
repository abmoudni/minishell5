/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 02:46:03 by mtawil            #+#    #+#             */
/*   Updated: 2025/11/16 02:46:04 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int builtin_pwd()
{
    char *path = getcwd(NULL, 0);
    if (!path)
    {
        perror("pwd");
        return (1);
    }
    printf("%s\n", path);
    free(path);
    return (0);
}