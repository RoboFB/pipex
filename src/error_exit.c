/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:50:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/09 18:23:08 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// prints errno if check is not 0
void	error_exit_errno(int check)
{
	if (check != 0)
	{
		perror(strerror(errno));
	}
	exit(EXIT_FAILURE);
}

// Exit the program as failure.
void	error_exit_msg(char *msg)
{
	ft_putstr_fd("Error : ", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
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