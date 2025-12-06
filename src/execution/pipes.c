/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtawil <mtawil@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 02:46:10 by mtawil            #+#    #+#             */
/*   Updated: 2025/12/06 17:21:45 by mtawil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_command_path(t_cmd *cmd, t_env_and_exit *shell, int *is_built)
{
	char	*path;

	if (is_builtin(cmd->args[0]))
	{
		*is_built = 1;
		return (NULL);
	}
	path = find_command_path(cmd->args[0], shell);
	return (path);
}

static void	wait_all_children(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;
	int	last_status;
	int	sigint_received;

	i = 0;
	last_status = 0;
	sigint_received = 0;
	while (i < num_cmds)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT && !sigint_received++)
				write(1, "\n", 1);
			last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	if (last_status != 0)
		get_and_set_value(NULL, last_status);
}

int	prepare_command(char **cmd_args, t_env_and_exit *shell, t_cmd **cmd,
		char **path)
{
	int	builtin_flag;

	builtin_flag = 0;
	*cmd = parse_cmd_with_redir(cmd_args);
	if (!*cmd || ((*cmd)->args && !(*cmd)->args[0]))
	{
		if (*cmd)
			free_cmd(*cmd);
		return (-1);
	}
	*path = get_command_path(*cmd, shell, &builtin_flag);
	if (!*path && !builtin_flag)
		return (0);
	return (builtin_flag);
}

int	process_single_command(t_pipeline_data *data, char ***cmds)
{
	t_cmd	*cmd;
	char	*path;
	int		builtin_flag;

	builtin_flag = prepare_command(cmds[data->i], data->shell, &cmd, &path);
	if (builtin_flag == -1)
		return (0);
	if (builtin_flag == 0 && !path)
		return (handle_cmd_not_found(cmd, data->i, data->pids));
	data->is_builtin = builtin_flag;
	data->pids[data->i] = fork();
	if (data->pids[data->i] == -1)
		return (handle_fork_error(cmd, path, data), -1);
	if (data->pids[data->i] == 0)
		child_process(cmd, path, data);
	if (path)
		free(path);
	free_cmd(cmd);
	return (0);
}

void	execute_pipeline(char ***cmds, t_env_and_exit *shell)
{
	t_pipeline_data	data;

	if (init_pipeline(&data, cmds, shell) == -1)
		return ;
	data.i = 0;
	while (data.i < data.num_cmds)
	{
		if (process_single_command(&data, cmds) == -1)
			return ;
		data.i++;
	}
	close_all_pipes(data.pipes, data.num_cmds);
	init_signals_child_exec();
	wait_all_children(data.pids, data.num_cmds);
	init_signals();
	free_pipes_array(data.pipes, data.num_cmds);
	free(data.pids);
}
