/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:01:25 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/22 15:34:39 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

pid_t	split_processes_here_doc(
	int argc, const char **argv, const char *envp[])
{
	int			count;
	t_fd		pipes[2][2];
	t_fd		*curr_pipe;
	t_fd		*new_pipe;
	pid_t		last_child_pid;

	curr_pipe = pipes[0];
	new_pipe = pipes[1];
	create_pipe(curr_pipe);
	first_child_here_doc(argv[2], curr_pipe, argv[3], envp);
	count = 4;
	while (count < argc - 2)
	{
		create_pipe(new_pipe);
		middle_child(curr_pipe, new_pipe, argv[count], envp);
		close_one_pip(curr_pipe);
		swap_ptrs(&new_pipe, &curr_pipe);
		count++;
	}
	last_child_pid = last_child_here_doc(
			curr_pipe, argv[argc - 1], argv[argc - 2], envp);
	close_one_pip(curr_pipe);
	return (last_child_pid);
}

// ./pipex here_doc LIMITER cmd cmd1 outfile    6
//    0       1        2     3   4      5

// ./pipex here_doc LIMITER cmd cmd1 cmd2 outfile     7
//    0       1        2     3   4    5      6
