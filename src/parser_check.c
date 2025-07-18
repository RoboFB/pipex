/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:23:52 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/18 18:35:34 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_cmd(char const *input)
{
	if (input[0] == '\0')
		error_exit_input();
	return ;
}

static void	check_path(char const *input)
{
	if (input[0] == '\0')
		error_exit_input();
	return ;
}

// R: 0 ok | -1 error | parses argc and argv
int	parser_check(int argc, char const *argv[])
{
	int			idx;

	if (argc <= 4)
		error_exit_input();
	check_path(argv[1]); // in file
	check_path(argv[argc - 1]); // out file
	idx = 2;
	while (idx < argc - 1)
	{
		check_cmd(argv[idx]);
		idx++;
	}
	return (0);
}
