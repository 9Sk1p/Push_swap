/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhubaren <yhubaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/22 14:16:00 by yhubaren          #+#    #+#             */
/*   Updated: 2026/08/22 14:16:00 by yhubaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*res;
	char	ch;

	ch = (char)c;
	res = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == ch)
			res = (char *)&s[i];
		i++;
	}
	if (s[i] == ch)
		res = (char *)&s[i];
	return (res);
}
