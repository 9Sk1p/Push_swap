/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhubaren <yhubaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/15 18:03:19 by yhubaren          #+#    #+#             */
/*   Updated: 2026/10/17 12:23:55 by yhubaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static long	parse_digits(const char *str, long sign, long i)
{
	long	number;
	long	digit;

	number = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		digit = str[i++] - '0';
		if (number > (LONG_MAX - digit) / 10)
		{
			if (sign == 1)
				return (LONG_MAX);
			return (LONG_MIN);
		}
		number = number * 10 + digit;
	}
	return (number * sign);
}

long	ft_atol(const char *str)
{
	long	sign;
	long	i;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (parse_digits(str, sign, i));
}

int	check_duplicate(t_node *a, long num)
{
	if (!a)
		return (0);
	while (a != NULL)
	{
		if (a->value == num)
			return (1);
		a = a->next;
	}
	return (0);
}
