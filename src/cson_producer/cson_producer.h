/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_producer.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSON_PRODUCER_H
# define CSON_PRODUCER_H

# include "cson.h"

typedef (t_error_code	(*t_flush_buffer_func)(unsigned char *buffer,
unsigned int buffer_position, void *dest_ptr));

typedef struct s_cson_producer	t_cson_producer;
struct					s_cson_producer
{
	t_flush_buffer_func	flush_func;
	unsigned char		buffer[CSON_PRODUCER_BSIZE];
	unsigned int		buffer_position;
	void				*dest_ptr;
};

void					cson_log_producing_error(const char *msg, int errcode);
size_t					cson_produce(t_cson_producer *producer,
const unsigned char *src, size_t srcsize);
size_t					cson_produce_primitive_value(t_cson_producer *producer,
const t_cson *cson);
size_t					cson_produce_composite_value(t_cson_producer *producer,
const t_cson *cson);
size_t					cson_produce(t_cson_producer *producer,
const unsigned char *src, size_t srcsize);
size_t					cson_produce_node(t_cson_producer *producer,
const t_cson *cson, unsigned int indent_depth);

#endif
