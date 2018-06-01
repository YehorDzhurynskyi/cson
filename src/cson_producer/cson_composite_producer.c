/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_composite_producer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_producer.h"

static size_t			cson_produce_children(t_cson_producer *producer,
const t_alst *tuple, unsigned int indent_depth)
{
	size_t	bytes_produced;
	int		i;
	t_alst	*tuple;

	bytes_produced = 0;
	i = 0;
	while (i < tuple->size)
		bytes_produced += cson_produce_node(producer,
		alst_get(tuple, i++), indent_depth);
	return (bytes_produced);
}

static size_t			cson_produce_array(t_cson_producer *producer,
const t_cson *cson, unsigned int indent_depth)
{
	size_t	bytes_produced;

	bytes_produced = 0;
	bytes_produced += cson_produce(producer, "[", 1);
	cson_produce_children(producer, cson_get_array(cson), indent_depth + 1);
	bytes_produced += cson_produce(producer, "]", 1);
	return (bytes_produced);
}

static size_t			cson_produce_object(t_cson_producer *producer,
const t_cson *cson, unsigned int indent_depth)
{
	size_t	bytes_produced;

	bytes_produced = 0;
	bytes_produced += cson_produce(producer, "{", 1);
	cson_produce_children(producer, cson_get_object(cson), indent_depth + 1);
	bytes_produced += cson_produce(producer, "}", 1);
	return (bytes_produced);
}

size_t					cson_produce_composite_value(t_cson_producer *producer,
const t_cson *cson, unsigned int indent_depth)
{
	if (cson_is_array(cson))
		return (cson_produce_array(producer, cson, indent_depth));
	else if (cson_is_object(cson))
		return (cson_produce_object(producer, cson, indent_depth));
}
