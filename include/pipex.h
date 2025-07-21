/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:17:46 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/21 14:04:28 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> // for malloc, free
# include <unistd.h> // for read, write, close
# include <fcntl.h> // for open
# include <limits.h> // for INT_MAX
# include <stdbool.h> // for bool type
# include <sys/wait.h> // for wait
# include <errno.h> // for errno

# include <string.h> // for strerror
# include <stdio.h> // for printf, perror

# include "libft.h"
# include "get_next_line.h"

typedef int	t_fd;

// error functions

void		error_exit_msg(char *msg);
void		error_exit_errno(char *msg);
void		error_exit_input(void);

// Parent functions

int			main(int argc, char const *argv[], char const *envp[]);
void		parser_check(int argc, char const *argv[]);

// Child functions

pid_t		split_processes(int argc, const char **argv, const char *envp[]);

void		first_child( const char *input_file, t_fd *curr,
				const char *command_in, const char *envp[]);
void		middle_child(t_fd *curr, t_fd *next,
				const char *command_in, const char *envp[]);
pid_t		last_child(t_fd *curr, const char *output_file,
				const char *command_in, const char *envp[]);

void		exe_command(const char *comand_in, const char **envp);
char		**split_command(const char *start);
char		*get_path_comand(const char *cmd_name, const char *envp[]);

// util functions

void		swap_ptrs(int **a, int **b);
void		create_pipe(t_fd *one_pipe);
void		close_one_pip(t_fd *pipe);
int			set_std_in_out(int in_fd, int out_fd);
void		*ft_realloc(void *ptr, size_t old, size_t new);
void		free_split(char **split);

#endif
