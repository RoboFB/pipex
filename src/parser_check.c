/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:23:52 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/19 03:05:42 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parser_check(int argc, char const *argv[])
{
	int			idx;

	if (argc <= 4)
		error_exit_input();
	idx = 1;
	while (idx < argc - 1)
	{
		if (argv[idx][0] == '\0')
			error_exit_input();
		idx++;
	}
	return ;
}

bool	is_her_doc(int argc, char const *argv[])
{
	if (ft_strncmp(argv[1], "here_doc", 8))
		return (false);
	if (argc <= 5)
		error_exit_input();
	return (true);
}

// const char	*get_limiter(int argc, char const *argv[])
// {
// 	return (argv[2]);
// }
