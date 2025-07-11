/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 17:18:33 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/11 15:46:39 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// free all mallocs in all R: void
void	free_all(void)
{
	// if (all == NULL)
	// 	return ;
	// if (all->ops != NULL)
	// 	free(all->ops);
	return ;
}

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