/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:09:30 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/21 17:48:44 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	h_read_line(t_fd	pipe_end, const char *limiter)
{
	char	*line;

	while (true)
	{
		ft_putchar_fd('>', STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL
			|| (!ft_strncmp(line, limiter, ft_strlen(limiter))
				&& line[ft_strlen(limiter)] == '\n'))
			break ;
		ft_putstr_fd(line, pipe_end);
		free(line);
	}
	free(line);
	return ;
}

void	first_child_here_doc(
						const char *limiter, t_fd *curr,
						const char *command_in, const char *envp[])
{
	pid_t	pid;
	t_fd	tmp[2];

	pid = fork();
	if (pid > 0)
		return ;
	else if (pid == -1)
		error_exit_errno("fork first child process");
	if (close(curr[0]) < 0)
		error_exit_errno("close");
	create_pipe(tmp);
	h_read_line(tmp[1], limiter);
	if (close(tmp[1]) < 0)
		error_exit_errno("close");
	if (set_std_in_out(tmp[0], curr[1]) < 0)
		error_exit_errno("dup2 or close");
	exe_command(command_in, envp);
	return ;
}

pid_t	last_child_here_doc(
						t_fd *curr, const char *output_file,
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
	write_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (write_fd < 0)
		error_exit_errno("output");
	if (set_std_in_out(curr[0], write_fd) < 0)
		error_exit_errno("dup2 or close");
	exe_command(command_in, envp);
	return (pid);
}
