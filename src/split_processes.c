/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:01:25 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/14 23:17:38 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t	split_processes(int argc, char const *argv[], char const *envp[])
{
	int			count;
	t_fd		pipes[2][2];
	pid_t		pid;
	t_fd		*curr_pip;
	t_fd		*new_pip;

	count = 0;
	curr_pip = pipes[0];
	new_pip = pipes[1];
	if (pipe(curr_pip) < 0)
		error_exit_errno("1");
	pid = fork();

	if (pid == 0)
	{
		h_first_child(argv[1], curr_pip);
		exe_command((char *)argv[2], (char **)envp); // execute command no return
	}
	else if (pid < 0)
		error_exit_errno("15");
	while (count < argc - 5)
	{
		if (pipe(new_pip) < 0)
			error_exit_errno("2");
		pid = fork();
		if (pid == 0)
		{
			h_middle_child(curr_pip, new_pip);
			exe_command((char *)argv[count + 3], (char **)envp);
		}
		else if (pid < 0)
			error_exit_errno("3");
		close_one_pip(curr_pip);
		swap_ptrs(&new_pip, &curr_pip);
		count++;
	}
	pid = fork();
	if (pid == 0)
	{
		h_last_child(argv[argc - 1], curr_pip);
		exe_command((char *)argv[argc - 2], (char **)envp);
	}
	else if (pid < 0)
		error_exit_errno("16");
	close_one_pip(curr_pip);
	while(wait(NULL) >= 0 && errno != ECHILD);
	return (pid);
}




void	h_middle_child(t_fd *curr, t_fd *next)
{
	if (close(curr[1]) < 0
		|| close(next[0]) < 0)
		error_exit_errno("4");
	if (h_set_std_in_out(curr[0], next[1]) < 0)
		error_exit_errno("5");
	return ;
}


void	h_first_child(const char *input_file, t_fd *curr)
{
	int		read_fd;

	if (close(curr[0]) < 0)
		error_exit_errno("6");
	read_fd = open(input_file, O_RDONLY);
	if (read_fd < 0)
		error_exit_errno("7");
	if (h_set_std_in_out(read_fd, curr[1]) < 0)
		error_exit_errno("8");
	return ;
}

void	h_last_child(const char *output_file, t_fd *curr)
{
	int		write_fd;

	if (close(curr[1]) < 0)
		error_exit_errno("9");
	write_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (write_fd < 0)
		error_exit_errno("10");
	if (h_set_std_in_out(curr[0], write_fd) < 0)
		error_exit_errno("11");
	return ;
}

int	h_set_std_in_out(int in_fd, int out_fd)
{
	if (dup2(in_fd, STDIN_FILENO) < 0
		|| close(in_fd) < 0
		|| dup2(out_fd, STDOUT_FILENO) < 0
		|| close(out_fd) < 0)
		return (-1);
	else
		return (0);
}

void close_one_pip(t_fd *pipe)
{
	if (close(pipe[0]) < 0
		|| close(pipe[1]) < 0)
		error_exit_errno("13");
	return ;
}



void swap_ptrs(int **a, int **b)
{
    int *temp = *a;
    *a = *b;
    *b = temp;
}