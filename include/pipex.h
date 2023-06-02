/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarceau <rmarceau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:12:59 by rene              #+#    #+#             */
/*   Updated: 2023/05/30 17:22:49 by rmarceau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// to write, read, close, access, pipe, fork, dup2, execve
# include <sys/types.h>
# include <unistd.h>

// to open
# include <fcntl.h>
# include <sys/stat.h>

// to waitpid
# include <sys/wait.h>

// to malloc, free, exit
# include <stdlib.h>

// to perror
# include "../libft/include/libft.h"
# include <stdbool.h>
# include <stdio.h>

// error messages
# define ERR_INPUT "Invalid arguments: ./pipex infile cmd1 cmd2 outfile"
# define ERR_INFILE "Infile"
# define ERR_OUTFILE "Outfile"
# define ERR_PIPE "Pipe"
# define ERR_FORK "Fork"
# define ERR_CMD "Command"
# define ERR_MALLOC "Dynamic memory allocation failed"

// structure to store data
typedef struct s_data
{
	pid_t	child1;
	pid_t	child2;
	int		pipefd[2];
	int		status;
	int		fd_infile;
	int		fd_outfile;
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	**envp;
}			t_data;

// functions
void		ft_first_child(t_data *pipex_data, char **envp);
void		ft_second_child(t_data *pipex_data, char **envp);

void		ft_init(t_data *pipex_data);
char		**ft_get_envp(char **envp);
void		ft_testing(t_data *pipex_data);

void		ft_close_pipes(t_data *pipex_data);
void		ft_end_program(t_data *pipex_data, char *error_message,
				bool end_program);

#endif