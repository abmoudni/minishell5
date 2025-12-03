/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:03:16 by mtawil            #+#    #+#             */
/*   Updated: 2025/12/03 14:04:16 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	count_pipes(char **args)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			count++;
		i++;
	}
	return (count);
}

int	has_pipe(char **args, t_env_and_exit *shell)
{
	int		flag;
	char	***pipe_cmds;

	flag = count_pipes(args);
	if (flag > 0)
	{
		pipe_cmds = split_all_pipes(args);
		if (pipe_cmds)
		{
			execute_pipeline(pipe_cmds, shell);
			free_all_pipes(pipe_cmds);
		}
	}
	return (flag > 0);
}

int	find_pipe(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			return (i);
		i++;
	}
	return (-1);
}
