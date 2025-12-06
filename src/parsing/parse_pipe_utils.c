/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 17:59:24 by mtawil            #+#    #+#             */
/*   Updated: 2025/12/06 17:29:01 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_split_all(char ***result, int count)
{
	while (--count >= 0)
		free(result[count]);
	free(result);
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
