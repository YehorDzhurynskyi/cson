/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_primitive_producer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_producer.h"
#include <stdlib.h>

static size_t			cson_produce_number(t_cson_producer *producer,
const t_cson *cson)
{
	char	*value;
	size_t	bytes_produced;

	if (cson_is_integer(cson))
		value = ft_itoa(cson_get_integer(cson));
	else if (cson_is_real(cson))
		value = ft_ldtoa(cson_get_real(cson), 6);
	bytes_produced += cson_write(producer, value, ft_strlen(value));
	free(value);
	return (bytes_produced);
}

size_t					cson_produce_primitive_value(t_cson_producer *producer,
const t_cson *cson)
{
	size_t	bytes_produced;
	char	*value;

	bytes_produced = 0;
	if (cson_is_integer(cson) || cson_is_real(cson))
	{
		bytes_produced += cson_produce_number(producer, cson);
	}
	else
	{
		if (cson_is_boolean(cson))
			value = cson_get_boolean(cson) ? "true" : "false";
		if (cson_is_string(cson))
			value = (char*)cson_get_string(cson);
		bytes_produced += cson_write(producer, value, ft_strlen(value));
	}
	return (bytes_produced);
}
