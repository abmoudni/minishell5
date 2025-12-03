/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_free_and_errs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:11:03 by mtawil            #+#    #+#             */
/*   Updated: 2025/12/03 18:30:09 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_all_pipes(int **pipes, int num_cmds)
{
	int	j;

	j = 0;
	while (j < num_cmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}

void	handle_fork_error(t_cmd *cmd, char *path, t_pipeline_data *data)
{
	perror("fork");
	if (path)
		free(path);
	free_cmd(cmd);
	free_pipes_array(data->pipes, data->num_cmds);
	free(data->pids);
}

int	handle_cmd_not_found(t_cmd *cmd, int i, pid_t *pids)
{
	ft_perror("minishell: ");
	ft_perror(cmd->args[0]);
	ft_perror(": command not found\n");
	free_cmd(cmd);
	pids[i] = fork();
	if (pids[i] == 0)
		exit(127);
	return (1);
}
