/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhubaren <yhubaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/24 14:53:04 by yhubaren          #+#    #+#             */
/*   Updated: 2026/08/24 14:53:04 by yhubaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp;

	if (size != 0 && (count * size) / size != count)
		return (NULL);
	tmp = malloc(count * size);
	if (tmp == 0)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}
