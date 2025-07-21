/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:17:46 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/21 14:07:42 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

// here_doc bonus part

bool		is_here_doc(
				int argc, char const *argv[]);

pid_t		split_processes_here_doc(
				int argc, const char **argv, const char *envp[]);

void		first_child_here_doc(
				const char *limiter, t_fd *curr,
				const char *command_in, const char *envp[]);

pid_t		last_child_here_doc(
				t_fd *curr, const char *output_file,
				const char *command_in, const char *envp[]);


#endif
