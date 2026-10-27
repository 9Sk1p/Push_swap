/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strategy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 21:00:00 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/27 21:00:00 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_stack *a, t_stack *b)
{
	double	disorder;

	if (!a || a->size < 2)
		return ;
	if (a->size <= 3)
	{
		sort_three(a, b);
		return ;
	}
	disorder = calculate_disorder(a);
	if (a->size <= 5 || disorder < 0.20)
		sort_simple(a, b);
	else if (disorder < 0.50)
		sort_medium(a, b);
	else
		sort_complex(a, b);
}

void	run_strategy(t_strategy strategy, t_stack *a, t_stack *b)
{
	if (strategy == STRATEGY_SIMPLE)
		sort_simple(a, b);
	else if (strategy == STRATEGY_MEDIUM)
		sort_medium(a, b);
	else if (strategy == STRATEGY_COMPLEX)
		sort_complex(a, b);
	else
		sort_adaptive(a, b);
}
