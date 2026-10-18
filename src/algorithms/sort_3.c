/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 12:56:38 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/18 14:36:09 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3(t_stack *a, t_stack *b)
{
	int	top;
	int	mid;
	int	bot;

	if (!a || a->size < 2)
		return ;
	if (a->size == 2)
	{
		if (a->top->value > a->bottom->value)
			exec_op("sa", a, b);
		return ;
	}
	top = a->top->value;
	mid = a->top->next->value;
	bot = a->bottom->value;
	if (top > mid && top > bot)
		exec_op("ra", a, b);
	else if (mid > top && mid > bot)
		exec_op("rra", a, b);
	if (a->top->value > a->top->next->value)
		exec_op("sa", a, b);
}
