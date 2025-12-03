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

void	free_split_all(char ***result, int count)
{
	while (--count >= 0)
		free(result[count]);
	free(result);
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

void	free_all_pipes(char ***cmds)
{
	int	i;
	int	j;

	if (!cmds)
		return ;
	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (ft_strncmp(cmds[i][j], "/tmp/.heredoc_temp_", 19) == 0)
			{
				free(cmds[i][j]);
			}
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}
