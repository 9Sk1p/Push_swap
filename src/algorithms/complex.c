/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 12:56:30 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/18 14:35:02 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	max_index_bits(t_stack *a)
{
	int	max_index;
	int	bits;

	max_index = a->size - 1;
	bits = 0;
	while (max_index > 0)
	{
		max_index >>= 1;
		bits++;
	}
	return (bits);
}

static void	sort_bit(t_stack *a, t_stack *b, int bit)
{
	int	count;

	count = a->size;
	while (count-- > 0)
	{
		if (((a->top->index >> bit) & 1) == 0)
			exec_op("pb", a, b);
		else
			exec_op("ra", a, b);
	}
	while (b->size > 0)
		exec_op("pa", a, b);
}

void	sort_complex(t_stack *a, t_stack *b)
{
	int	bit;
	int	bits;

	if (!a || a->size < 2)
		return ;
	bits = max_index_bits(a);
	bit = 0;
	while (bit < bits)
	{
		sort_bit(a, b, bit);
		bit++;
	}
}
