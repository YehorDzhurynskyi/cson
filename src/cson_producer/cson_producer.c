/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_producer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_producer.h"

static t_cson_producer	cson_create_producer(t_flush_buffer_func flush_func,
void *dest_ptr)
{
	t_cson_producer producer;

	producer.buffer_position = 0;
	producer.dest_ptr = dest_ptr;
	producer.flush_func = flush_func;
	return (producer);
}

static void				cson_flush_buffer(t_cson_producer *producer)
{
	producer->flush_func(producer->buffer,
	producer->buffer_position, producer->dest_ptr);
	producer->buffer_position = 0;
}

size_t					cson_produce(const t_cson *cson,
t_flush_buffer_func flush_func, void *dest_ptr)
{
	t_cson_producer	producer;
	size_t			bytes_produced;

	producer = cson_create_producer(flush_func, dest_ptr);
	bytes_produced = cson_produce_node(&producer, cson, 0);
	cson_flush_buffer(&producer);
	return (bytes_produced);
}

size_t					cson_produce_bytes(t_cson_producer *producer,
const char *src, size_t srcsize)
{
	size_t	bytes_produced;
	size_t	nbytes;

	bytes_produced = 0;
	while (srcsize > 0)
	{
		nbytes = srcsize < CSON_PRODUCER_BSIZE - producer->buffer_position
		? srcsize : CSON_PRODUCER_BSIZE - producer->buffer_position;
		ft_memcpy(producer->buffer + producer->buffer_position, src, nbytes);
		bytes_produced += nbytes;
		producer->buffer_position += nbytes;
		src += nbytes;
		srcsize -= nbytes;
		if (producer->buffer_position >= CSON_PRODUCER_BSIZE)
			cson_flush_buffer(producer);
	}
	return (bytes_produced);
}

size_t					cson_produce_indentation(t_cson_producer *producer,
int indent_depth)
{
	int		i;
	size_t	bytes_produced;

	bytes_produced = 0;
	i = 0;
	while (i++ < indent_depth)
		bytes_produced += cson_produce_bytes(producer, "\t", 1);
	return (bytes_produced);
}

static inline t_bool	cson_is_quoted_key(const char *key)
{
	while (*key)
	{
		if (!ft_isalnum(*key++))
			return (TRUE);
	}
	return (FALSE);
}

size_t					cson_produce_node(t_cson_producer *producer,
const t_cson *cson, int indent_depth)
{
	size_t	bytes_produced;
	t_bool	is_quoted_key;

	bytes_produced = cson_produce_indentation(producer, indent_depth);
	if (cson->key != NULL)
	{
		is_quoted_key = cson_is_quoted_key(cson->key);
		if (is_quoted_key)
			bytes_produced += cson_produce_bytes(producer, "\"", 1);
		bytes_produced += cson_produce_bytes(producer, cson->key, ft_strlen(cson->key));
		if (is_quoted_key)
			bytes_produced += cson_produce_bytes(producer, "\"", 1);
		bytes_produced += cson_produce_bytes(producer, ": ", 2);
	}
	if (cson_is_primitive(cson))
		bytes_produced += cson_produce_primitive_value(producer, cson);
	else if (cson_is_composite(cson))
		bytes_produced += cson_produce_composite_value(producer, cson, indent_depth);
	bytes_produced += cson_produce_bytes(producer, "\n", 1);
	return (bytes_produced);
}
