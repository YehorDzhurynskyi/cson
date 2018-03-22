/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_boolean_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

void				cson_boolean_set_value(t_cson_parser *parser, int value)
{
	parser->current->value.boolean = value;
	parser->current->value_type = CSON_BOOLEAN_VALUE_TYPE;
}

t_handler_status	cson_false_handler(t_cson_parser *parser, char ch, int *err)
{
	if ((parser->buffer_offset == 1 && ch != 'a')
	|| (parser->buffer_offset == 2 && ch != 'l')
	|| (parser->buffer_offset == 3 && ch != 's')
	|| (parser->buffer_offset == 4 && ch != 'e')
	|| (parser->buffer_offset == 5 && !ft_isws(ch)))
	{
		cson_log_parsing_error("wrong value (did you mean \"false\"?)",
		ch, err, CSON_VALUE_PARSING_ERROR);
		return (handler_error);
	}
	if (ft_isws(ch))
	{
		cson_boolean_set_value(parser, FALSE);
		parser->buffer_offset = 0;
		parser->state = CSON_PARSER_EOV_STATE;
		return (cson_eov_handler(parser, ch, err));
	}
	return (handler_record);
}

t_handler_status	cson_true_handler(t_cson_parser *parser, char ch, int *err)
{
	if ((parser->buffer_offset == 1 && ch != 'r')
	|| (parser->buffer_offset == 2 && ch != 'u')
	|| (parser->buffer_offset == 3 && ch != 'e')
	|| (parser->buffer_offset == 4 && !ft_isws(ch)))
	{
		cson_log_parsing_error("wrong value (did you mean \"true\"?)",
		ch, err, CSON_VALUE_PARSING_ERROR);
		return (handler_error);
	}
	if (ft_isws(ch))
	{
		cson_boolean_set_value(parser, TRUE);
		parser->buffer_offset = 0;
		parser->state = CSON_PARSER_EOV_STATE;
		return (cson_eov_handler(parser, ch, err));
	}
	return (handler_record);
}
