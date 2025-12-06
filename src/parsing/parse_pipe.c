/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:24:37 by mtawil            #+#    #+#             */
/*   Updated: 2025/12/03 17:41:24 by mtawil           ###   ########.fr       */
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

char	**alloc_one_command(char **args, int *start)
{
	int		j;
	int		k;
	char	**cmd;

	j = *start;
	while (args[j] && ft_strcmp(args[j], "|") != 0)
		j++;
	cmd = malloc(sizeof(char *) * (j - *start + 1));
	if (!cmd)
		return (NULL);
	k = 0;
	while (*start < j)
	{
		cmd[k] = args[*start];
		k++;
		(*start)++;
	}
	cmd[k] = NULL;
	if (args[*start])
		(*start)++;
	return (cmd);
}

char	***split_all_pipes(char **args)
{
	char	***result;
	int		num_cmds;
	int		i;
	int		start;

	num_cmds = count_pipes(args) + 1;
	result = malloc(sizeof(char **) * (num_cmds + 1));
	if (!result)
		return (NULL);
	i = 0;
	start = 0;
	while (i < num_cmds)
	{
		result[i] = alloc_one_command(args, &start);
		if (!result[i])
		{
			free_split_all(result, i);
			return (NULL);
		}
		i++;
	}
	result[num_cmds] = NULL;
	return (result);
}
