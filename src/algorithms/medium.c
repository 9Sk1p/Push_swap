/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 12:56:32 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/18 14:34:58 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	chunk_size(int size)
{
	int	chunk;

	chunk = 1;
	while (chunk * chunk < size)
		chunk++;
	return (chunk);
}

static int	get_index_pos(t_stack *stack, int index)
{
	t_node	*node;
	int		position;

	node = stack->top;
	position = 0;
	while (node)
	{
		if (node->index == index)
			return (position);
		node = node->next;
		position++;
	}
	return (-1);
}

static void	move_max_to_top(t_stack *b)
{
	int	max_index;
	int	position;

	max_index = b->size - 1;
	position = get_index_pos(b, max_index);
	if (position <= b->size / 2)
	{
		while (position-- > 0)
			exec_op("rb", NULL, b);
	}
	else
	{
		while (position++ < b->size)
			exec_op("rrb", NULL, b);
	}
}

static void	distribute_chunks(t_stack *a, t_stack *b, int chunk)
{
	int	pushed;

	pushed = 0;
	while (a->size > 0)
	{
		if (a->top->index <= pushed + chunk)
		{
			exec_op("pb", a, b);
			if (b->top->index <= pushed)
				exec_op("rb", a, b);
			pushed++;
		}
		else
			exec_op("ra", a, b);
	}
}

void	sort_medium(t_stack *a, t_stack *b)
{
	int	chunk;

	if (!a || a->size < 2)
		return ;
	chunk = chunk_size(a->size);
	distribute_chunks(a, b, chunk);
	while (b->size > 0)
	{
		move_max_to_top(b);
		exec_op("pa", a, b);
	}
}
