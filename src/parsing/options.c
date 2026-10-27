/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvdovenk <mvdovenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/27 21:00:00 by mvdovenk          #+#    #+#             */
/*   Updated: 2026/10/27 21:00:00 by mvdovenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_option(const char *arg, const char *option)
{
	return (ft_strncmp(arg, option, ft_strlen(option) + 1) == 0);
}

static int	is_strategy_option(const char *arg)
{
	return (is_option(arg, "--simple") || is_option(arg, "--medium")
		|| is_option(arg, "--complex") || is_option(arg, "--adaptive"));
}

static t_strategy	get_strategy(const char *arg)
{
	if (is_option(arg, "--simple"))
		return (STRATEGY_SIMPLE);
	if (is_option(arg, "--medium"))
		return (STRATEGY_MEDIUM);
	if (is_option(arg, "--complex"))
		return (STRATEGY_COMPLEX);
	return (STRATEGY_ADAPTIVE);
}

static void	process_option(t_options *options, char *arg, int *strategy_set)
{
	if (is_option(arg, "--bench"))
		options->bench++;
	else if (is_strategy_option(arg))
	{
		if (*strategy_set)
			options->strategy = STRATEGY_INVALID;
		else
		{
			options->strategy = get_strategy(arg);
			*strategy_set = 1;
		}
	}
	else
		options->strategy = STRATEGY_INVALID;
}

t_options	parse_options(int argc, char **argv)
{
	t_options	options;
	int			i;
	int			strategy_set;

	options.strategy = STRATEGY_ADAPTIVE;
	options.bench = 0;
	strategy_set = 0;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] != '-' || argv[i][1] != '-')
		{
			i++;
			continue ;
		}
		process_option(&options, argv[i], &strategy_set);
		i++;
	}
	if (options.bench > 1 || options.strategy == STRATEGY_INVALID)
		options.strategy = STRATEGY_INVALID;
	return (options);
}
