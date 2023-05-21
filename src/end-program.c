/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end-program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:34:37 by rene              #+#    #+#             */
/*   Updated: 2023/05/21 00:45:11 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void    free_2d_array(char **array)
{
    int i;

    i = 0;
    while (array[i])
        free(array[i++]);
    free(array);
}

void ft_end_program(t_data *pipex_data, char *error_message)
{
    if (pipex_data->fd_infile != 0)
        close(pipex_data->fd_infile);
    if (pipex_data->fd_outfile != 0)
        close(pipex_data->fd_outfile);
    if (pipex_data->pipefd[0] != 0)
        close(pipex_data->pipefd[0]);
    if (pipex_data->pipefd[1] != 0)
        close(pipex_data->pipefd[1]);
    if (pipex_data->cmd1)
        free_2d_array(pipex_data->cmd1);
    if (pipex_data->cmd2)
        free_2d_array(pipex_data->cmd2);
    if (pipex_data->envp)
        free_2d_array(pipex_data->envp);
    free(pipex_data);
    if (error_message)
    {
        ft_putendl_fd(error_message, STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
