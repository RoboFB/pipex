/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:17:46 by rgohrig           #+#    #+#             */
/*   Updated: 2025/07/08 11:47:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdbool.h>

# include <stdio.h>

# include "libft.h"
# include "printf.h"



// auto
t_element		*el_new(int input_value, int goal);
void		el_add_front(t_element **start, t_element *new_el);
void		el_add_end(t_element **start, t_element *new_el);
int			el_get_size(t_element **start);
int			el_fill_goals(t_element **start);
t_element		*el_pop_one(t_element **start, t_element *remove);
void		el_remove_one(t_element **start, t_element *remove);
void		el_remove_all(t_element **start);
void		ps_error_exit(t_all *all);
void		ps_free_all(t_all *all);
int			ps_get_goal(t_all *all);
bool		ps_is_solved(t_all *all);
void		ps_move_goal(t_all *all, int goal);
int			ps_count_a(t_all *all, int goal);
int			ps_count_b(t_all *all, int goal);
void		ps_pa(t_all *all);
void		ps_pb(t_all *all);
void		ps_remove_last_op(t_all *all);
void		ps_rra(t_all *all);
void		ps_rrb(t_all *all);
void		ps_rrr(t_all *all);
void		ps_ra(t_all *all);
void		ps_rb(t_all *all);
void		ps_rr(t_all *all);
void		ps_init_ops(t_all *all);
void		ps_resize_ops(t_all *all);
void		ps_add_op(t_all *all, t_operation op);
void		ps_add_multi_ops(t_all *all, t_operation op, int count);
void		ps_sa(t_all *all);
void		ps_sb(t_all *all);
void		ps_ss(t_all *all);
int			ps_parser(int argc, char const *argv[], t_element **start_a);
void		ps_print_results(t_all *all);
int			main(int argc, char const *argv[]);
void		ps_sort(t_all *all);
bool		ps_sort_backtracking(t_all *all, int max_depth, int try_size);

#endif
