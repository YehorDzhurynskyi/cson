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

t_handler_status	cson_array_handler(t_cson_parser *parser, char ch)
{
#if 0
	parser->current->value_type = CSON_ARRAY_VALUE_TYPE;
	parser->current->value.tuple = alst_create(3);
	if (parser->current->value.tuple == NULL)
	{
		cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
		return (handler_error);
	}
	parser->state = CSON_PARSER_BEFORE_VALUE_STATE;
	parser->parent = parser->current;
	return (cson_before_value_handler(parser, ch));
#else
	(void)ch;
	cson_log_error(parser, "this library doesn't support arrays yet", CSON_VALUE_PARSING_ERROR);
	return (handler_error);
#endif
}
