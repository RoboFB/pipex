/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:53:10 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/14 18:29:54 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Main function, starts the program
int	main(int argc, char const *argv[], char const *envp[])
{
	(void)argc; // temporary
	(void)argv; // temporary
	// test();
	// parsing
	pid_t pid;

	parser_check(argc, argv);

	pid = split_processes(argc, argv, envp);


	if (pid != 0)
		while(wait(NULL) >= 0 && errno != ECHILD);

	// work

	// free on exit

	return (0);
}
