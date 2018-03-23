/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_object_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

static t_bool		assign_object(t_cson_parser *parser)
{
	parser->current->value_type = CSON_OBJECT_VALUE_TYPE;
	parser->current->value.tuple = alst_create(3);
	if (parser->current->value.tuple == NULL)
	{
		cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
		return (FALSE);
	}
	return (TRUE);
}

t_handler_status	cson_empty_object_handler(t_cson_parser *parser, char ch)
{
	if (ch == '}')
	{
		parser->state = CSON_PARSER_EOV_STATE;
		return (assign_object(parser) == FALSE ? handler_error : handler_skip);
	}
	cson_log_parsing_error(parser, "unrecognized symbol in empty object value, should be \"{}\"",
	ch, CSON_KEY_PARSING_ERROR);
	return (handler_error);
}

t_handler_status	cson_object_handler(t_cson_parser *parser, char ch)
{
	parser->state = CSON_PARSER_BEFORE_KEY_STATE;
	parser->parent = parser->current;
	return (assign_object(parser) == FALSE
	? handler_error : cson_before_key_handler(parser, ch));
}
