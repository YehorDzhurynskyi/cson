/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 15:19:33 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/10/27 14:34:07 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

void	*ft_memrealloc(void *ptr, size_t oldsize, size_t newsize)
{
	void *arr;

	arr = (void *)malloc(newsize);
	if (arr == NULL || ptr == NULL)
		return (arr);
	ft_memcpy(arr, ptr, oldsize);
	free(ptr);
	return (arr);
}
