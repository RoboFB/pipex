/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:53:10 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/21 14:25:58 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Main function, starts the program
int	main(int argc, char const *argv[], char const *envp[])
{
	pid_t		last_child_pid;
	int			exit_num;
	int			status;

	exit_num = 0;
	parser_check(argc, argv);
	if (is_here_doc(argc, argv))
	{
		last_child_pid = split_processes_here_doc(argc, argv, envp);
	}
	else
	{
		last_child_pid = split_processes(argc, argv, envp);
	}
	waitpid(last_child_pid, &status, 0);
	if (WIFEXITED(status))
		exit_num = WEXITSTATUS(status);
	if (exit_num != 0)
		exit_num += 126;
	while (wait(NULL) >= 0 && errno != ECHILD)
		;
	return (exit_num);
}

bool	is_here_doc(int argc, char const *argv[])
{
	if (ft_strncmp(argv[1], "here_doc", 8))
		return (false);
	if (argc <= 5)
		error_exit_input();
	return (true);
}