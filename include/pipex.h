/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:17:46 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/09 21:53:07 by rgohrig          ###   ########.fr       */
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



// auto
void		child(char *comand_in, char **envp);
void		error_exit_errno(int check);
void		error_exit_msg(char *msg);
void		error_exit_input(void);
void		free_all(void);
char		*get_path_comand(char *cmd_name, char **envp);
int			main(int argc, char const *argv[], char const *envp[]);
int			parser_check(int argc, char const *argv[]);
void		split_processes(int argc, char const *argv[], char const *envp[]);
void		free_split(char **split);

#endif
