/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:11:29 by rene              #+#    #+#             */
/*   Updated: 2023/05/21 00:51:07 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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


static void ft_init_pipex(t_data *pipex_data, int argc, char **argv, char **envp)
{
    if (argc != 5)
        ft_end_program(pipex_data, ERR_INPUT);
    pipex_data->child1 = 0;
    pipex_data->child2 = 0;
    pipex_data->status = 0;
    if (pipe(pipex_data->pipefd) == -1)
        ft_end_program(pipex_data, ERR_PIPE);
    pipex_data->fd_infile = open(argv[1], O_RDONLY);
    if (pipex_data->fd_infile == -1)
        ft_end_program(pipex_data, ERR_INFILE);
    pipex_data->fd_outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (pipex_data->fd_outfile == -1)
        ft_end_program(pipex_data, ERR_OUTFILE);
    pipex_data->cmd1 = ft_split(argv[2], ' ');
    pipex_data->cmd2 = ft_split(argv[3], ' ');
    pipex_data->envp = ft_get_envp(envp);
    if (!pipex_data->cmd1 || !pipex_data->cmd2 || !pipex_data->envp)
        ft_end_program(pipex_data, ERR_MALLOC);
}

int main(int argc, char **argv, char **envp)
{
    t_data *pipex_data;

    pipex_data = malloc(sizeof(t_data));
    ft_init_pipex(pipex_data, argc, argv, envp);
    ft_testing(pipex_data);
    ft_printf("init done\n");
    return (EXIT_SUCCESS);
}