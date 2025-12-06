/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 18:08:39 by mtawil            #+#    #+#             */
/*   Updated: 2025/12/06 17:28:21 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	setup_pipe_redirection(int i, int num_cmds, int **pipes)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < num_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
}

static void	child_execute_builtin(t_cmd *cmd, t_env_and_exit *shell)
{
	int	exit_code;

	exit_code = run_builtin(cmd->args, shell);
	exit(exit_code);
}

static void	child_execute_command(t_cmd *cmd, char *path, t_env_and_exit *shell)
{
	execve(path, cmd->args, shell->env);
	perror("minishell");
	exit(1);
}

void	child_process(t_cmd *cmd, char *path, t_pipeline_data *data)
{
	reset_signals();
	setup_pipe_redirection(data->i, data->num_cmds, data->pipes);
	close_all_pipes(data->pipes, data->num_cmds);
	if (cmd->redirs)
	{
		if (execute_redirections(cmd->redirs) == -1)
			exit(1);
	}
	if (data->is_builtin)
		child_execute_builtin(cmd, data->shell);
	child_execute_command(cmd, path, data->shell);
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
