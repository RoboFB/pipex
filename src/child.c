/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/10 14:52:41 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char *comand_in, char **envp)
{
	char	*path_comand;
	char	**comand_with_args;

	comand_with_args = ft_split(comand_in, ' ');
	if (comand_with_args == NULL || comand_with_args[0] == NULL)
		error_exit_msg("Memory full: ft_split failed");
	path_comand = get_path_comand(*comand_with_args, envp);
	if (path_comand == NULL)
	{
		free_split(comand_with_args);
		error_exit_msg("Command not found");
	}
	// printf("exe:%s|%s\n", path_comand, *comand_with_args);//debuging
	if (execve(path_comand, comand_with_args, envp) < 0)
	{
		free_split(comand_with_args);
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}
	return ;
}
