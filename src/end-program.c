/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end-program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:34:37 by rene              #+#    #+#             */
/*   Updated: 2023/06/02 12:37:53 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static void	ft_print_error(t_data *pipex_data, char *error_message)
{
	if (ft_strncmp(error_message, ERR_INPUT, ft_strlen(error_message)) == 0
		|| ft_strncmp(error_message, ERR_MALLOC, ft_strlen(error_message)) == 0)
		ft_putendl_fd(error_message, STDERR_FILENO);
	else if (ft_strncmp(error_message, ERR_INFILE,
			ft_strlen(error_message)) == 0)
		perror(pipex_data->infile);
	else if (ft_strncmp(error_message, ERR_OUTFILE,
			ft_strlen(error_message)) == 0)
		perror(pipex_data->outfile);
	else if (ft_strncmp(error_message, ERR_CMD, ft_strlen(error_message)) == 0
		&& pipex_data->child1 == 0)
	{
		ft_putstr_fd(pipex_data->cmd1[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else if (ft_strncmp(error_message, ERR_CMD, ft_strlen(error_message)) == 0
		&& pipex_data->child1 != 0)
	{
		ft_putstr_fd(pipex_data->cmd2[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
	}
	else
		perror(error_message);
}

void	ft_close_pipes(t_data *pipex_data)
{
	if (pipex_data->pipefd[0] != 0)
		close(pipex_data->pipefd[0]);
	if (pipex_data->pipefd[1] != 0)
		close(pipex_data->pipefd[1]);
}

void	ft_end_program(t_data *pipex_data, char *error_message,
		bool end_program)
{
	if (error_message)
		ft_print_error(pipex_data, error_message);
	if (end_program)
	{
		if (pipex_data->fd_infile != 0)
			close(pipex_data->fd_infile);
		if (pipex_data->fd_outfile != 0)
			close(pipex_data->fd_outfile);
		if (pipex_data->cmd1)
			free_2d_array(pipex_data->cmd1);
		if (pipex_data->cmd2)
			free_2d_array(pipex_data->cmd2);
		if (pipex_data->envp)
			free_2d_array(pipex_data->envp);
		if (pipex_data->infile)
			free(pipex_data->infile);
		if (pipex_data->outfile)
			free(pipex_data->outfile);
		if (error_message)
			exit(pipex_data->status);
		free(pipex_data);
	}
}
