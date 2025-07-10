/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:20:57 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/09 18:35:34 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// F: free | free split strs and split
void	free_split(char **split)
{
	int	idx;

	if (!split)
		return ;
	idx = 0;
	while (split[idx])
	{
		free(split[idx]);
		idx++;
	}
	free(split);
	return ;
}
