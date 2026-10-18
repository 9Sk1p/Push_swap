/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 12:56:35 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/18 19:44:32 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_index_pos(t_stack *s, int target)
{
	t_node	*curr;
	int		pos;

	curr = s->top;
	pos = 0;
	while (curr)
	{
		if (curr->index == target)
			return (pos);
		pos++;
		curr = curr->next;
	}
	return (-1);
}

static void	bring_target_to_b(t_stack *a, t_stack *b, int target)
{
	int	pos;

	pos = get_index_pos(a, target);
	if (pos <= a->size / 2)
	{
		while (pos > 0)
		{
			exec_op("ra", a, b);
			pos--;
		}
	}
	else
	{
		while (pos < a->size)
		{
			exec_op("rra", a, b);
			pos++;
		}
	}
	exec_op("pb", a, b);
}

void	sort_simple(t_stack *a, t_stack *b)
{
	int	target;

	if (!a || a->size < 2)
		return ;
	if (a->size <= 3)
	{
		sort_three(a, b);
		return ;
	}
	target = 0;
	while (a->size > 3)
	{
		bring_target_to_b(a, b, target);
		target++;
	}
	sort_three(a, b);
	while (b->size > 0)
		exec_op("pa", a, b);
}
