/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 14:01:25 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/11 17:00:25 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	split_processes(int argc, char const *argv[], char const *envp[])
{
	int		pid;
	int		count;
	int		fds[2];

	pipe(fds);

	count = 0;
	while (count < argc - 3)
	{
		pid = fork();
		if (pid == 0) //child
		{
			
			if (count == 0)
			{
				close(fds[0]);
				int fd_test = open(argv[1], O_RDONLY);
				if (fd_test < 0)
				{
					ft_putendl_fd("Error opening input file", 2);
					exit(EXIT_FAILURE);
				}
				if (dup2(fd_test, 0) < 0)
				{
					ft_putendl_fd("E: 1", 2);
					exit(EXIT_FAILURE);
				}

				if (dup2(fds[1], 1) < 0)
				{
					ft_putendl_fd("E: 2", 2);
					exit(EXIT_FAILURE);
				}
				
				close(fd_test);
				close(fds[1]);
			}
			if (count == 1)
			{
				close(fds[1]);
				int fd_test_2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 777);
				if (fd_test_2 < 0)
				{
					perror("Error opening output file");
					exit(EXIT_FAILURE);
				}
				if (dup2(fds[0], 0) < 0)
				{
					ft_putendl_fd("E: 3", 2);
					exit(EXIT_FAILURE);
				}
				if (dup2(fd_test_2, 1) < 0)
				{
					ft_putendl_fd("E: 4", 2);
					exit(EXIT_FAILURE);
				}
				close(fd_test_2);
				close(fds[0]);
			}
			// ft_putendl_fd("_test_333", 2);
			child((char *)argv[count + 2], (char **)envp); // execute command
			ft_putendl_fd("E: 5", 2);
			break ; // shout be never reached, but just in case
		}
		count++;
	}
	if (pid != 0)
	{
		close(fds[0]); // close read end of pipe
		close(fds[1]); // close write end of pipe
		while(wait(NULL) >= 0 && errno != ECHILD);
			// ft_putendl_fd("1 c fished", 2);; // wait for child to finish
		// printf("Parent: All children finished\n");
	}
	return ;
}
