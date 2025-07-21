/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:23:52 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/21 13:22:12 by rgohrig          ###   ########.fr       */
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
