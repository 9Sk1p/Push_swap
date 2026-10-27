/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mx-vdv <mx-vdv@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 20:55:16 by mx-vdv            #+#    #+#             */
/*   Updated: 2026/10/27 20:56:08 by mx-vdv           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_percent(double disorder)
{
	int	percent;

	percent = (int)(disorder * 10000.0 + 0.5);
	ft_putnbr_fd(percent / 100, 2);
	ft_putchar_fd('.', 2);
	if (percent % 100 < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd(percent % 100, 2);
	ft_putstr_fd("%", 2);
}

static char	*strategy_name(t_strategy strategy)
{
	if (strategy == STRATEGY_SIMPLE)
		return ("Simple / O(n2)");
	if (strategy == STRATEGY_MEDIUM)
		return ("Medium / O(n sqrt(n))");
	if (strategy == STRATEGY_COMPLEX)
		return ("Complex / O(n log n)");
	return ("Adaptive");
}

static void	print_swap_counts(t_bench *bench)
{
	ft_putstr_fd("[bench] sa: ", 2);
	ft_putnbr_fd(bench->counts[0], 2);
	ft_putstr_fd(" sb: ", 2);
	ft_putnbr_fd(bench->counts[1], 2);
	ft_putstr_fd(" ss: ", 2);
	ft_putnbr_fd(bench->counts[2], 2);
	ft_putstr_fd(" pa: ", 2);
	ft_putnbr_fd(bench->counts[3], 2);
	ft_putstr_fd(" pb: ", 2);
	ft_putnbr_fd(bench->counts[4], 2);
	ft_putchar_fd('\n', 2);
}

static void	print_rotate_counts(t_bench *bench)
{
	ft_putstr_fd("[bench] ra: ", 2);
	ft_putnbr_fd(bench->counts[5], 2);
	ft_putstr_fd(" rb: ", 2);
	ft_putnbr_fd(bench->counts[6], 2);
	ft_putstr_fd(" rr: ", 2);
	ft_putnbr_fd(bench->counts[7], 2);
	ft_putstr_fd(" rra: ", 2);
	ft_putnbr_fd(bench->counts[8], 2);
	ft_putstr_fd(" rrb: ", 2);
	ft_putnbr_fd(bench->counts[9], 2);
	ft_putstr_fd(" rrr: ", 2);
	ft_putnbr_fd(bench->counts[10], 2);
	ft_putchar_fd('\n', 2);
}

void	print_benchmark(t_bench *bench, double disorder, t_strategy strategy)
{
	if (!bench)
		return ;
	ft_putstr_fd("[bench] disorder: ", 2);
	print_percent(disorder);
	ft_putstr_fd("\n[bench] strategy: ", 2);
	ft_putendl_fd(strategy_name(strategy), 2);
	ft_putstr_fd("[bench] total_ops: ", 2);
	ft_putnbr_fd(bench->total, 2);
	ft_putchar_fd('\n', 2);
	print_swap_counts(bench);
	print_rotate_counts(bench);
}
