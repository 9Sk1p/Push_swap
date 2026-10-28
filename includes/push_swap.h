/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 13:12:55 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/18 14:47:51 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "libft.h"

typedef struct s_node
{
	int				value;
	int				index;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_bench
{
	int		enabled;
	int		total;
	int		counts[11];
}	t_bench;

typedef struct s_stack
{
	t_node	*top;
	t_node	*bottom;
	int		size;
	t_bench	*bench;
}	t_stack;

typedef enum e_strategy
{
	STRATEGY_ADAPTIVE,
	STRATEGY_SIMPLE,
	STRATEGY_MEDIUM,
	STRATEGY_COMPLEX,
	STRATEGY_INVALID
}	t_strategy;

typedef struct s_options
{
	t_strategy	strategy;
	int			bench;
}	t_options;

void		parse_args(t_stack *a, int argc, char **argv);
t_options	parse_options(int argc, char **argv);
int			is_valid_number(char *str);
long		ft_atol(const char *str);
int			check_duplicate(t_node *a, long num);
t_node		*ft_node_new(int val);
void		ft_stack_add_back(t_stack *stack, t_node *new_node);

int			is_sorted(t_stack *stack);
double		calculate_disorder(t_stack *stack);
void		index_stack(t_stack *a);

void		op_swap(t_stack *stack);
void		op_push(t_stack *dst, t_stack *src);
void		op_rotate(t_stack *stack);
void		op_rev_rotate(t_stack *stack);
void		exec_op(char *cmd, t_stack *a, t_stack *b);
void		print_benchmark(t_bench *bench, double disorder,
				t_strategy strategy, int size);

void		sort_three(t_stack *a, t_stack *b);
void		sort_simple(t_stack *a, t_stack *b);
void		sort_medium(t_stack *a, t_stack *b);
void		sort_complex(t_stack *a, t_stack *b);
void		sort_adaptive(t_stack *a, t_stack *b);
void		run_strategy(t_strategy strategy, t_stack *a, t_stack *b);

void		ft_free_stack(t_stack *stack);
void		ft_free_split(char **arr);
void		ft_error(t_stack *stack, char **split_arr);

#endif
