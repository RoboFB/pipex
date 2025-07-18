/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 11:32:37 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/18 20:13:25 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// F: Mallocs joined_path and split intern
static char	*h_test_path(const char *cmd_name, const char *path)
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
		if (access(joined_path, F_OK) == 0)
			return (free(back_part), free_split(path_all), joined_path);
		else
			free(joined_path);
		idx++;
	}
	return (free(back_part), free_split(path_all), NULL);
}

// Mallocs joined_path
char	*get_path_comand(const char *cmd_name, const char *envp[])
{
	int					idx;
	static const char	*fallback_path
		= "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";

	idx = 0;
	if (access(cmd_name, F_OK) == 0)
		return (ft_strdup(cmd_name));
	if (envp == NULL || *envp == NULL)
		return (h_test_path(cmd_name, fallback_path));
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
