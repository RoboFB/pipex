/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:12:30 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/15 18:20:47 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	swap_ptrs(int **a, int **b)
{
	int		*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	create_pipe(t_fd *one_pipe)
{
	if (pipe(one_pipe) < 0)
		error_exit_errno("create_pipe failed");
	return ;
}

void	close_one_pip(t_fd *pipe)
{
	if (close(pipe[0]) < 0
		|| close(pipe[1]) < 0)
		error_exit_errno("close pipe fds failed");
	return ;
}

int	set_std_in_out(int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) < 0
		|| close(in_fd) < 0
		|| dup2(out_fd, STDOUT_FILENO) < 0
		|| close(out_fd) < 0)
		return (-1);
	else
		return (0);
}
