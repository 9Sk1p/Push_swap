/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 21:00:00 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/27 21:00:00 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init_stack(t_stack *stack)
{
	stack->top = NULL;
	stack->bottom = NULL;
	stack->size = 0;
	stack->bench = NULL;
}

static void	init_bench(t_bench *bench)
{
	int	i;

	bench->enabled = 0;
	bench->total = 0;
	i = 0;
	while (i < 11)
		bench->counts[i++] = 0;
}

static int	run_program(t_stack *a, t_stack *b, t_bench *bench,
		t_options options)
{
	double	disorder;

	if (a->size == 0)
		ft_error(a, NULL);
	disorder = calculate_disorder(a);
	if (is_sorted(a))
	{
		if (bench->enabled)
			print_benchmark(bench, disorder, options.strategy, a->size);
		return (0);
	}
	index_stack(a);
	run_strategy(options.strategy, a, b);
	if (bench->enabled)
		print_benchmark(bench, disorder, options.strategy, a->size);
	return (0);
}

int	main(int argc, char **argv)
{
	t_stack		a;
	t_stack		b;
	t_bench		bench;
	t_options	options;

	if (argc < 2)
		return (0);
	init_stack(&a);
	init_stack(&b);
	init_bench(&bench);
	options = parse_options(argc, argv);
	if (options.strategy == STRATEGY_INVALID)
		ft_error(&a, NULL);
	bench.enabled = options.bench;
	a.bench = &bench;
	b.bench = &bench;
	parse_args(&a, argc, argv);
	run_program(&a, &b, &bench, options);
	ft_free_stack(&a);
	ft_free_stack(&b);
	return (0);
}
