/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:09:30 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/18 22:14:12 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(
	const char *input_file, t_fd *curr,
	const char *command_in, const char *envp[])
{
	int		read_fd;
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		return ;
	else if (pid == -1)
		error_exit_errno("fork first child process");
	if (close(curr[0]) < 0)
		error_exit_errno("close");
	read_fd = open(input_file, O_RDONLY);
	if (read_fd < 0)
		error_exit_errno("input");
	if (set_std_in_out(read_fd, curr[1]) < 0)
		error_exit_errno("dup2 or close");
	exe_command(command_in, envp);
	return ;
}

void	middle_child(
	t_fd *curr, t_fd *next,
	const char *command_in, const char *envp[])
{
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		return ;
	else if (pid == -1)
		error_exit_errno("fork middle child process");
	if (close(curr[1]) < 0
		|| close(next[0]) < 0)
		error_exit_errno("close");
	if (set_std_in_out(curr[0], next[1]) < 0)
		error_exit_errno("dup2 or close");
	exe_command(command_in, envp);
	return ;
}

pid_t	last_child(
	const char *output_file, t_fd *curr,
	const char *command_in, const char *envp[])
{
	int		write_fd;
	pid_t	pid;

	pid = fork();
	if (pid > 0)
		return (pid);
	else if (pid == -1)
		error_exit_errno("fork last child process");
	if (close(curr[1]) < 0)
		error_exit_errno("close");
	write_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (write_fd < 0)
		error_exit_errno("output");
	if (set_std_in_out(curr[0], write_fd) < 0)
		error_exit_errno("dup2 or close");
	exe_command(command_in, envp);
	return (pid);
}
