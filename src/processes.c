/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 01:02:47 by rene              #+#    #+#             */
/*   Updated: 2023/05/21 10:54:21 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void   ft_exec_cmd(t_data *pipex_data, char **cmd, char **envp)
{
    char *cmd_path;
    char *cmd_file;
    int i;

    i = -1;
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

void    ft_first_child(t_data *pipex_data, char **envp)
{
    int original_fd_outfile;

    original_fd_outfile = dup(STDOUT_FILENO);
    dup2(pipex_data->fd_infile, STDIN_FILENO);
    dup2(pipex_data->pipefd[1], STDOUT_FILENO);
    ft_exec_cmd(pipex_data, pipex_data->cmd1, envp);
    dup2(original_fd_outfile, STDOUT_FILENO);
    close(original_fd_outfile);
    ft_end_program(pipex_data, ERR_CMD);
}

void    ft_second_child(t_data *pipex_data, char **envp)
{
    int original_fd_outfile;

    original_fd_outfile = dup(STDOUT_FILENO);
    dup2(pipex_data->fd_outfile, STDOUT_FILENO);
    dup2(pipex_data->pipefd[0], STDIN_FILENO);
    ft_exec_cmd(pipex_data, pipex_data->cmd2, envp);
    dup2(original_fd_outfile, STDOUT_FILENO);
    close(original_fd_outfile);
    ft_end_program(pipex_data, ERR_CMD);
}