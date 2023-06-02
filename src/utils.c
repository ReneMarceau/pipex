/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 00:49:49 by rene              #+#    #+#             */
/*   Updated: 2023/06/02 12:53:31 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_init(t_data *pipex_data)
{
	pipex_data->child1 = 0;
	pipex_data->child2 = 0;
	pipex_data->pipefd[0] = 0;
	pipex_data->pipefd[1] = 0;
	pipex_data->status = 1;
	pipex_data->fd_infile = 0;
	pipex_data->fd_outfile = 0;
	pipex_data->infile = NULL;
	pipex_data->outfile = NULL;
	pipex_data->cmd1 = NULL;
	pipex_data->cmd2 = NULL;
	pipex_data->envp = NULL;
}

char	**ft_get_envp(char **envp)
{
	char	**enviroment;
	char	*path_trimmed;
	char	*path;
	int		i;

	enviroment = NULL;
	path_trimmed = NULL;
	path = NULL;
	i = -1;
	while (envp[++i])
	{
		path = ft_strnstr(envp[i], "PATH=", 5);
		if (path)
		{
			path_trimmed = ft_strtrim(envp[i], "PATH=");
			enviroment = ft_split(path_trimmed, ':');
			break ;
		}
		free(path);
	}
	free(path_trimmed);
	return (enviroment);
}
