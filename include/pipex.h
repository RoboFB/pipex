/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:17:46 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/14 17:18:02 by rgohrig          ###   ########.fr       */
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
# include "printf.h"


typedef	int t_fd;

// auto
void		exe_command(char *comand_in, char **envp);
void		error_exit_msg(char *msg);
void		error_exit_errno(char *msg);
void		error_exit_input(void);
void		free_all(void);
void		free_split(char **split);
char		*get_path_comand(char *cmd_name, char **envp);
int			main(int argc, char const *argv[], char const *envp[]);
int			parser_check(int argc, char const *argv[]);
pid_t		split_processes(int argc, char const *argv[], char const *envp[]);
void		h_middle_child(t_fd *curr, t_fd *next);
void		h_first_child(const char *input_file, t_fd *curr);
void		h_last_child(const char *output_file, t_fd *curr);
int			h_set_std_in_out(int in_fd, int out_fd);
void		close_one_pip(t_fd *pipe);
void		swap_ptrs(int **a, int **b);

#endif
