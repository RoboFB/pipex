/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:53:10 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/15 18:50:39 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Main function, starts the program
int	main(int argc, char const *argv[], char const *envp[])
{
	parser_check(argc, argv);

	split_processes(argc, argv, envp);
	// free on exit

	return (0);
}
