/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 12:55:57 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/18 14:20:46 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	exec_rotate(char *cmd, t_stack *a, t_stack *b)
{
	if (!ft_strncmp(cmd, "ra", 3))
		op_rotate(a);
	else if (!ft_strncmp(cmd, "rb", 3))
		op_rotate(b);
	else if (!ft_strncmp(cmd, "rr", 3))
	{
		op_rotate(a);
		op_rotate(b);
	}
	else if (!ft_strncmp(cmd, "rra", 4))
		op_rev_rotate(a);
	else if (!ft_strncmp(cmd, "rrb", 4))
		op_rev_rotate(b);
	else if (!ft_strncmp(cmd, "rrr", 4))
	{
		op_rev_rotate(a);
		op_rev_rotate(b);
	}
	else
		return (0);
	return (1);
}

static t_bench	*get_bench(t_stack *a, t_stack *b)
{
	if (a)
		return (a->bench);
	if (b)
		return (b->bench);
	return (NULL);
}

static void	count_operation(t_bench *bench, char *cmd)
{
	static char	*names[11] = {"sa", "sb", "ss", "pa", "pb", "ra",
		"rb", "rr", "rra", "rrb", "rrr"};
	int			i;

	if (!bench)
		return ;
	bench->total++;
	i = 0;
	while (i < 11)
	{
		if (!ft_strncmp(cmd, names[i], ft_strlen(names[i]) + 1))
			bench->counts[i]++;
		i++;
	}
}

void	exec_op(char *cmd, t_stack *a, t_stack *b)
{
	if (!ft_strncmp(cmd, "sa", 3))
		op_swap(a);
	else if (!ft_strncmp(cmd, "sb", 3))
		op_swap(b);
	else if (!ft_strncmp(cmd, "ss", 3))
	{
		op_swap(a);
		op_swap(b);
	}
	else if (!ft_strncmp(cmd, "pa", 3))
		op_push(a, b);
	else if (!ft_strncmp(cmd, "pb", 3))
		op_push(b, a);
	else if (!exec_rotate(cmd, a, b))
		return ;
	count_operation(get_bench(a, b), cmd);
	ft_putendl_fd(cmd, 1);
}
