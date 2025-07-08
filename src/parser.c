/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:23:52 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/08 12:13:20 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// R: num of converted chars or -1 on error | converts str to number
static int	h_strict_atoi(const char *nptr, int *result)
{
	long int	num;
	int			len;
	int			negative;

	num = 0;
	len = 0;
	negative = 1;
	if (!nptr || !result)
		return (-1);
	if (*nptr == '-')
	{
		negative = -1;
		nptr++;
		len++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - '0') * negative;
		if (num < INT_MIN || num > INT_MAX)
			return (-1);
		nptr++;
		len++;
	}
	*result = (int)num;
	return (len);
}

// F: free | free split strs and split
static void	h_free_split(char **split)
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

static int	h_one_arg(char const *input, t_element **start_a)
{
	t_element	*new;
	int			result;
	char		**strs;
	int			idx;

	idx = 0;
	result = 0;
	strs = ft_split(input, ' ');
	if (strs == NULL || strs[0] == NULL)
		return (-1);
	while (strs[idx])
	{
		if (strs[idx][0] == '\0')
			return (h_free_split(strs), -1);
		if (strs[idx][0] == '-' && strs[idx][1] == '\0')
			return (h_free_split(strs), -1);
		if (h_strict_atoi(strs[idx], &result) != (int)ft_strlen(strs[idx]))
			return (h_free_split(strs), -1);
		new = el_new(result, -1);
		if (new == NULL)
			return (h_free_split(strs), -1);
		el_add_end(start_a, new);
		idx++;
	}
	return (h_free_split(strs), 0);
}

// R: 0 ok | -1 error | parses argc and argv
int	parser(int argc, char const *argv[], t_element **start_a)
{
	int			idx;

	idx = 1;
	if (argc <= 1)
		return (0);
	while (idx < argc)
	{
		if (argv[idx][0] == '\0')
			return (-1);
		if (h_one_arg(argv[idx], start_a) < 0)
			return (-1);
		idx++;
	}
	if (start_a == NULL)
		return (-1);
	return (0);
}
