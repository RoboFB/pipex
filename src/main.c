/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:53:10 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/21 14:39:28 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Main function with only normal part accepting
int	main(int argc, char const *argv[], char const *envp[])
{
	pid_t		last_child_pid;
	int			exit_num;
	int			status;

	exit_num = 0;
	parser_check(argc, argv);
	if (argc != 5)
		error_exit_input();
	last_child_pid = split_processes(argc, argv, envp);
	waitpid(last_child_pid, &status, 0);
	if (WIFEXITED(status))
		exit_num = WEXITSTATUS(status);
	if (exit_num == 1)
		exit_num += 126;
	while (wait(NULL) >= 0 && errno != ECHILD)
		;
	return (exit_num);
}
