/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_array_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

t_handler_status	cson_array_handler(t_cson_parser *parser, char ch, int *err)
{
	parser->state = CSON_PARSER_BEFORE_VALUE_STATE;
	parser->current->value.tuple = alst_create(3);
	if (parser->current->value.tuple == NULL)
	{
		cson_log_error(strerror(errno), err, CSON_MEM_ALLOC_ERROR);
		return (handler_error);
	}
	parser->current->value_type = CSON_OBJECT_VALUE_TYPE;
	parser->parent = parser->current;
	return (cson_before_value_handler(parser, ch, err));
}
