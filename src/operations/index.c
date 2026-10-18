/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 19:42:43 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/18 19:42:45 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	index_stack(t_stack *a)
{
	t_node	*curr;
	t_node	*cmp;
	int		count;

	curr = a->top;
	while (curr)
	{
		count = 0;
		cmp = a->top;
		while (cmp)
		{
			if (cmp->value < curr->value)
				count++;
			cmp = cmp->next;
		}
		curr->index = count;
		curr = curr->next;
	}
}
