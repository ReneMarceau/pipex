/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:12:59 by rene              #+#    #+#             */
/*   Updated: 2023/05/20 20:32:22 by rene             ###   ########.fr       */
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

// to strerror
# include <string.h>

typedef struct s_pipex
{
    pid_t   child1;
    pid_t   child2;
    int     status;
    int     pipefd[2];
    int     fd_infile;
    int     fd_outfile;
    char    **cmd1;
    char    **cmd2;
    char    **envp;
}            t_pipex;

#endif