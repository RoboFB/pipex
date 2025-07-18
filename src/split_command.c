/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 21:06:55 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/18 21:14:22 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	h_end_seperator(
	const char *start, const char *separator, const char **end_out)
{
	*end_out = ft_strnstr(start, separator, ft_strlen(start));
	if (*end_out == NULL)
		*end_out = start + ft_strlen(start);
	return (*end_out != start);
}

static bool	h_check_space(const char *start, const char **end_out)
{
	*end_out = ft_strnstr(start, " ", ft_strlen(start));
	if (*end_out == NULL)
		*end_out = start + ft_strlen(start);
	return (*end_out != start);
}

const char	*h_check_seperator(const char **start, const char **end_out)
{
	static const char	*separator[5] = {"'", "\"", "\\'", "\\\"", NULL};
	int					idx;
	int					len;

	len = ft_strlen(*start);
	idx = 0;
	*end_out = *start + len;
	while (separator[idx])
	{
		if (!ft_strncmp(*start, separator[idx], ft_strlen(separator[idx])))
		{
			*start += ft_strlen(separator[idx]);
			h_end_seperator(*start, separator[idx], end_out);
			return (separator[idx]);
		}
		idx++;
	}
	return (NULL);
}

static char	**add_split(char **all_pp, char *str)
{
	int			idx;
	char		**tmp_all;

	idx = 0;
	if (!str)
		return (free_split(all_pp), NULL);
	while (all_pp && all_pp[idx])
		idx++;
	tmp_all = ft_realloc(all_pp,
			idx * sizeof(char *), (idx + 2) * sizeof(char *));
	if (!tmp_all)
		return (free_split(all_pp), NULL);
	all_pp = tmp_all;
	all_pp[idx] = str;
	all_pp[idx + 1] = NULL;
	return (all_pp);
}

char	**split_command(const char *start)
{
	const char		*end;
	const char		*sep;
	char			**all_pp;

	all_pp = NULL;
	while (*start)
	{

		end = NULL;
		sep = h_check_seperator(&start, &end);
		if ((sep == NULL && h_check_space(start, &end) != true)
			|| start == end)
			break ;
		all_pp = add_split(all_pp, ft_substr(start, 0, end - start));
		if (!all_pp)
			return (NULL);
		start = end;
		if (sep != NULL)
			start += ft_strlen(sep);
		if (*start == ' ')
			start++;
	}
	return (all_pp);
}
