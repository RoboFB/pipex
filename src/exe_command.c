/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:25:15 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/18 21:14:57 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exe_command(const char *comand_in, const char **envp)
{
	char	*path_comand;
	char	**comand_with_args;

	comand_with_args = split_command(comand_in);
	if (comand_with_args == NULL || comand_with_args[0] == NULL)
		error_exit_errno("ft_split in exe_command failed");
	path_comand = get_path_comand(*comand_with_args, envp);
	if (path_comand == NULL)
	{
		ft_putstr_fd("pipex: ", STDERR_FILENO);
		ft_putstr_fd(*comand_with_args, STDERR_FILENO);
		free_split(comand_with_args);
		error_exit_msg(": command not found");
	}
	if (execve(path_comand, comand_with_args, (char *const *)envp) < 0)
	{
		free(path_comand);
		free_split(comand_with_args);
		error_exit_errno("execve failed");
	}
	return ;
}
