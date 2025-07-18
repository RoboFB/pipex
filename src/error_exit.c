/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/18 18:48:56 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Exit the program as failure.
void	error_exit_msg(char *msg)
{
	ft_putendl_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

// prints errno
void	error_exit_errno(char *msg)
{
	ft_putstr_fd("pipex: ", STDERR_FILENO);
	if (msg[0])
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
	exit(errno);
}

void	error_exit_input(void)
{
	const char	*msg
		= "3 Wrong User Input\n\n"
		"_____________________Example Table_______________________\n"
		"Program name | file in | comand 1  |  comand 2  | file out\n"
		"   ./pipex   |  in.txt | \"ls -l\" | \"cat -e\" | out.txt\n"
		"   ./pipex   |  in.txt | \"ls -l\" | \"cat -e\" | out.txt\n"
		"\n"
		"in bash example: < in.txt ls -l | cat -e > out.txt\n"
		"\n\n";

	error_exit_msg((char *)msg);
}

