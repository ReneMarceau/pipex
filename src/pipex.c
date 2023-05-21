/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:11:29 by rene              #+#    #+#             */
/*   Updated: 2023/05/21 10:13:16 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void ft_init_pipex(t_data *pipex_data, int argc, char **argv, char **envp)
{
    if (argc != 5)
        ft_end_program(pipex_data, ERR_INPUT);
    if (pipe(pipex_data->pipefd) == -1)
        ft_end_program(pipex_data, ERR_PIPE);
    pipex_data->fd_infile = open(argv[1], O_RDONLY);
    if (pipex_data->fd_infile < 0)
        ft_end_program(pipex_data, ERR_INFILE);
    pipex_data->fd_outfile = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (pipex_data->fd_outfile < 0)
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
    ft_init(pipex_data);
    if (!pipex_data)
        ft_end_program(pipex_data, ERR_MALLOC);
    ft_init_pipex(pipex_data, argc, argv, envp);
    pipex_data->child1 = fork();
    if (pipex_data->child1 == -1)
        ft_end_program(pipex_data, ERR_FORK);
    else if (pipex_data->child1 == 0)
        ft_first_child(pipex_data, envp);
    else
    {
        waitpid(pipex_data->child1, &pipex_data->status, 0);
        pipex_data->child2 = fork();
        if (pipex_data->child2 == -1)
            ft_end_program(pipex_data, ERR_FORK);
        else if (pipex_data->child2 == 0)
            ft_second_child(pipex_data, envp);
    }
    ft_close_pipes(pipex_data);
    ft_end_program(pipex_data, NULL);
    return (EXIT_SUCCESS);
}
