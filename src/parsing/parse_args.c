/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhubaren <yhubaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 11:48:55 by yhubaren          #+#    #+#             */
/*   Updated: 2026/10/17 13:26:10 by yhubaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*ft_node_new(int val)
{
	t_node *new_node;
	
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = val;
	new_node->index = -1;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);	
}
void	ft_stack_add_back(t_stack *stack, t_node *new_node)
{
	if (!stack || !new_node)
		return ;
	if (stack->top == NULL)
	{
		stack->top = new_node;
		stack->bottom = new_node;
		stack->size = 1;
	}
	else
	{
		stack->bottom->next = new_node;
		new_node->prev = stack->bottom;
		stack->bottom = new_node;
		stack->size++;
	}
}
static void	process_token(t_stack *a, char **split_arr, char *token)
{
	long	num;
	t_node	*new_node;

	if (!is_valid_number(token))
		ft_error(&a, split_arr);
	num = ft_atol(token);
	if (num < INT_MIN || num > INT_MAX)
		ft_error(&a, split_arr);
	if (check_duplicate(a, (int)num))
		ft_error(&a, split_arr);
	new_node = ft_node_new((int)num);
	if (!new_node)
		ft_error(&a, split_arr);
	ft_stack_add_back(a, new_node);
}

void	parse_args(t_stack *a, int argc, char **argv)
{
	int		i;
	int		j;
	char	**split_arr;

	i = 1;
	while (i < argc)
	{
		split_arr = ft_split(argv[i], ' ');
		if (!split_arr || !split_arr[0])
			ft_error(&a, split_arr);
		j = 0;
		while (split_arr[j])
		{
			process_token(a, split_arr, split_arr[j]);
			j++;
		}
		ft_free_split(split_arr);
		i++;
	}
}