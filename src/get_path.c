/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:37 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/15 18:28:14 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// F: Mallocs
static char	*h_test_path(char *cmd_name, const char *path)
{
	char	**path_all;
	int		idx;
	char	*joined_path;
	char	*back_part;

	idx = 0;
	path_all = ft_split(path + 5, ':');
	if (path_all == NULL || path_all[0] == NULL)
		return (NULL);
	back_part = ft_strjoin("/", cmd_name);
	if (back_part == NULL)
		return (free_split(path_all), NULL);
	while (path_all[idx])
	{
		joined_path = ft_strjoin(path_all[idx], back_part);
		if (joined_path == NULL)
			return (free(back_part), free_split(path_all), NULL);
		if (access(joined_path, F_OK) == 0)// it can be that i need to check the errnum on error
			return (free(back_part), free_split(path_all), joined_path);
		else
			free(joined_path);
		idx++;
	}
	return (free(back_part), free_split(path_all), NULL);
}

// Mallocs
char	*get_path_comand(char *cmd_name, const char *envp[])
{
	int		idx;

	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], "PATH=", 5) == 0)
		{
			return (h_test_path(cmd_name, envp[idx]));
		}
		idx++;
	}
	return (NULL);
}
