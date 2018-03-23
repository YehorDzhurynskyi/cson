/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_string_parser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include <stdlib.h>

t_cson	*cson_parse_str(const char *str, size_t size, int *err)
{
	t_cson_parser	parser;

	parser = cson_init_parser();
	if (parser.root == NULL || parser.root->value.tuple == NULL || parser.buffer == NULL)
	{
		cson_log_error(&parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
		cson_free_parser(&parser);
		return (NULL);
	}
	cson_parse_chunk(&parser, str, size);
	if (cson_flush_buffer(&parser) == FALSE)
		cson_free_parser(&parser);
	free(parser.buffer);
	*err = parser.err;
	return (parser.root);
}
