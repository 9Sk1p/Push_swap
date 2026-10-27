/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disorder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhubaren <yhubaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:48:58 by yhubaren          #+#    #+#             */
/*   Updated: 2026/10/17 11:48:59 by yhubaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	t_node	*curr;

	if (!stack || !stack->top)
		return (1);
	curr = stack->top;
	while (curr->next)
	{
		if (curr->value > curr->next->value)
			return (0);
		curr = curr->next;
	}
	return (1);
}

double	calculate_disorder(t_stack *stack)
{
	t_node		*current;
	t_node		*following;
	long long	inversions;
	long long	pairs;

	if (!stack || stack->size < 2)
		return (0.0);
	inversions = 0;
	current = stack->top;
	while (current)
	{
		following = current->next;
		while (following)
		{
			if (current->value > following->value)
				inversions++;
			following = following->next;
		}
		current = current->next;
	}
	pairs = (long long)stack->size * (stack->size - 1) / 2;
	return ((double)inversions / (double)pairs);
}
