/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_number_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

static t_bool		check_for_fractional_delimeter(t_cson_parser *parser, char ch, int *err)
{
	if (ft_strnchr(parser->buffer, '.', parser->buffer_offset))
	{
		cson_log_parsing_error("wrong number of \".\" in number value",
		ch, err, CSON_VALUE_PARSING_ERROR);
		return (FALSE);
	}
	return (TRUE);
}

t_bool				cson_number_set_value(t_cson_parser *parser, int *err)
{
	if (parser->buffer_offset == 1
	&& (parser->buffer[0] == '+' || parser->buffer[0] == '-'))
	{
		cson_log_error("number value can't consist of sign only",
		err, CSON_VALUE_PARSING_ERROR);
		return (FALSE);
	}
	parser->buffer[parser->buffer_offset] = '\0';
	if (!ft_strnchr(parser->buffer, '.', parser->buffer_offset))
	{
		parser->current->value.integer = ft_atoi(parser->buffer);
		parser->current->value_type = CSON_INTEGER_VALUE_TYPE;
	}
	else
	{
		parser->current->value.real = ft_atoi(parser->buffer); // TODO: add real number parse method
		parser->current->value_type = CSON_REAL_VALUE_TYPE;
	}
	return (TRUE);
}

t_handler_status	cson_number_handler(t_cson_parser *parser, char ch, int *err)
{
	if (ft_isws(ch))
	{
		if (cson_number_set_value(parser, err) == FALSE)
			return (handler_error);
		parser->buffer_offset = 0;
		parser->state = CSON_PARSER_EOV_STATE;
		return (cson_eov_handler(parser, ch, err));
	}
	if (!ft_isdigit(ch) && ch != '.')
	{
		cson_log_parsing_error("unrecognized symbol in number value",
		ch, err, CSON_VALUE_PARSING_ERROR);
		return (handler_error);
	}
	if (ch == '.' && check_for_fractional_delimeter(parser, ch, err) == FALSE)
		return (handler_error);
	return (handler_record);
}
