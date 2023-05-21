/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:49:49 by rene              #+#    #+#             */
/*   Updated: 2023/05/21 10:13:48 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* void ft_testing(t_data *pipex_data)
{
    int i;

    ft_printf("child1: %d\n", pipex_data->child1);
    ft_printf("child2: %d\n", pipex_data->child2);
    ft_printf("fd_infile: %d\n", pipex_data->fd_infile);
    ft_printf("fd_outfile: %d\n", pipex_data->fd_outfile);
    ft_printf("pipefd[0]: %d\n", pipex_data->pipefd[0]);
    ft_printf("pipefd[1]: %d\n", pipex_data->pipefd[1]);
    ft_printf("status: %d\n", pipex_data->status);
    i = -1;
    while (pipex_data->cmd1[++i])
        ft_printf("cmd1[%d]: %s\n", i, pipex_data->cmd1[i]);
    i = -1;
    while (pipex_data->cmd2[++i])
        ft_printf("cmd2[%d]: %s\n", i, pipex_data->cmd2[i]);
    i = -1;
    while (pipex_data->envp[++i])
        ft_printf("envp[%d]: %s\n", i, pipex_data->envp[i]);
} */

void    ft_init(t_data *pipex_data)
{
    pipex_data->child1 = 0;
    pipex_data->child2 = 0;
    pipex_data->fd_infile = 0;
    pipex_data->fd_outfile = 0;
    pipex_data->pipefd[0] = 0;
    pipex_data->pipefd[1] = 0;
    pipex_data->status = 0;
    pipex_data->cmd1 = NULL;
    pipex_data->cmd2 = NULL;
    pipex_data->envp = NULL;
}

char **ft_get_envp(char **envp)
{
    char **enviroment;
    int i;

    i = -1;
    while (envp[++i])
    {
        if (ft_strnstr(envp[i], "PATH=", 5))
        {
            enviroment = ft_split(ft_strtrim(envp[i], "PATH="), ':');
            break ;
        }
    }
    return (enviroment);
}
