/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:49:49 by rene              #+#    #+#             */
/*   Updated: 2023/05/21 00:57:53 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void ft_testing(t_data *pipex_data)
{
    int i;

    ft_printf("fd_infile: %d\n", pipex_data->fd_infile);
    ft_printf("fd_outfile: %d\n", pipex_data->fd_outfile);
    ft_printf("pipefd[0]: %d\n", pipex_data->pipefd[0]);
    ft_printf("pipefd[1]: %d\n", pipex_data->pipefd[1]);
    i = -1;
    while (pipex_data->cmd1[++i])
        ft_printf("cmd1[%d]: %s\n", i, pipex_data->cmd1[i]);
    i = -1;
    while (pipex_data->cmd2[++i])
        ft_printf("cmd2[%d]: %s\n", i, pipex_data->cmd2[i]);
    i = -1;
    while (pipex_data->envp[++i])
        ft_printf("envp[%d]: %s\n", i, pipex_data->envp[i]);
}
