/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:02:47 by rene              #+#    #+#             */
/*   Updated: 2023/06/02 12:56:00 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	ft_exec_cmd(t_data *pipex_data, char **cmd, char **envp)
{
	char	*cmd_path;
	char	*cmd_file;
	int		i;

	i = -1;
	if (cmd[0][0] == '/')
		cmd[0] = ft_strrchr(cmd[0], '/') + 1;
	while (pipex_data->envp[++i])
	{
		cmd_file = ft_strjoin("/", cmd[0]);
		cmd_path = ft_strjoin(pipex_data->envp[i], cmd_file);
		if (access(cmd_path, F_OK | X_OK) != -1)
		{
			if (ft_strncmp(cmd[0], pipex_data->cmd1[0], ft_strlen(cmd[0])) == 0)
				execve(cmd_path, pipex_data->cmd1, envp);
			else
				execve(cmd_path, pipex_data->cmd2, envp);
		}
		free(cmd_file);
		free(cmd_path);
	}
}

void	ft_first_child(t_data *pipex_data, char **envp)
{
	close(pipex_data->pipefd[0]);
	if (pipex_data->fd_infile > 0)
		dup2(pipex_data->fd_infile, STDIN_FILENO);
	dup2(pipex_data->pipefd[1], STDOUT_FILENO);
	ft_exec_cmd(pipex_data, pipex_data->cmd1, envp);
	ft_end_program(pipex_data, ERR_CMD, true);
}

void	ft_second_child(t_data *pipex_data, char **envp)
{
	close(pipex_data->pipefd[1]);
	dup2(pipex_data->fd_outfile, STDOUT_FILENO);
	dup2(pipex_data->pipefd[0], STDIN_FILENO);
	ft_exec_cmd(pipex_data, pipex_data->cmd2, envp);
	ft_end_program(pipex_data, ERR_CMD, true);
}
