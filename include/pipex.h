/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:12:59 by rene              #+#    #+#             */
/*   Updated: 2023/05/21 00:53:42 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// to write, read, close, access, pipe, fork, dup2, execve
# include <unistd.h>
# include <sys/types.h>

// to open, unlink
# include <fcntl.h>

// to waitpid
# include <sys/wait.h>

// to malloc, free, exit
# include <stdlib.h>

# include "../libft/include/libft.h"

# define ERR_INPUT "Invalid number of arguments: ./pipex infile cmd1 cmd2 outfile"
# define ERR_INFILE "Infile: No such file or directory"
# define ERR_OUTFILE "Outfile: Cannot create file"
# define ERR_PIPE "Pipe: Pipe initialization failed"
# define ERR_FORK "Fork: Child process creation failed"
# define ERR_CMD "Command not found"
# define ERR_MALLOC "Dynamic memory allocation failed"

typedef struct s_data
{
    pid_t   child1;
    pid_t   child2;
    int     fd_infile;
    int     fd_outfile;
    int     pipefd[2];
    int     status;
    char    **cmd1;
    char    **cmd2;
    char    **envp;
}            t_data;

void ft_testing(t_data *pipex_data);
void ft_end_program(t_data *pipex_data, char *error_message);

#endif