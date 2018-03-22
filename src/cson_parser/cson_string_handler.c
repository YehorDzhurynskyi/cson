/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_string_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

t_handler_status	cson_string_handler(t_cson_parser *parser, char ch, int *err)
{
	if (parser->buffer[0] == ch)
	{
		parser->current->value.string = ft_strsub(parser->buffer + 1,
		0, parser->buffer_offset - 1);
		if (parser->current->value.string == NULL)
		{
			cson_log_error(strerror(errno), err, CSON_MEM_ALLOC_ERROR);
			return (handler_error);
		}
		parser->current->value_type = CSON_STRING_VALUE_TYPE;
		parser->buffer_offset = 0;
		parser->state = CSON_PARSER_EOV_STATE;
		return (handler_skip);
	}
	return (handler_record);
}
