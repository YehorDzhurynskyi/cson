/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_key_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

t_handler_status	cson_before_value_handler(t_cson_parser *parser, char ch, int *err)
{
	if (ft_isws(ch))
		return (handler_skip);
	else if (ch == '[')
	{
		parser->state = CSON_PARSER_ARRAY_VALUE_STATE;
		return (handler_skip);
	}
	else if (ch == 't')
		parser->state = CSON_PARSER_TRUE_VALUE_STATE;
	else if (ch == 'f')
		parser->state = CSON_PARSER_FALSE_VALUE_STATE;
	else if (ch == '\'' || ch == '"')
		parser->state = CSON_PARSER_STRING_VALUE_STATE;
	else if (ch == ft_isdigit(ch) || ch == '+' || ch == '-')
		parser->state = CSON_PARSER_NUMBER_VALUE_STATE;
	else
	{
		cson_log_parsing_error("unrecognized symbol before a value",
		ch, err, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (handler_record);
}

t_handler_status	cson_after_key_handler(t_cson_parser *parser, char ch, int *err)
{
	if (ch == '\n' || ch == '{')
	{
		if (ch == '\n')
			parser->state = CSON_PARSER_OBJECT_VALUE_STATE;
		else if (ch == '{')
			parser->state = CSON_PARSER_EMPTY_OBJECT_VALUE_STATE;
		return (handler_skip);
	}
	return (cson_before_value_handler(parser, ch, err));
}

t_handler_status	cson_key_handler(t_cson_parser *parser, char ch, int *err)
{
	if (ch == ':')
	{
		if (parser->buffer_offset == 0)
		{
			cson_log_parsing_error("cson <key> can't be an empty string",
			ch, err, CSON_KEY_PARSING_ERROR);
			return (handler_error);
		}
		parser->state = CSON_PARSER_AFTER_KEY_STATE;
		parser->current = cson_alloc(parser->parent);
		alst_add(parser->parent->value.tuple, parser->current);
		if (parser->current == NULL)
		{
			cson_log_error(strerror(errno), err, CSON_MEM_ALLOC_ERROR);
			return (handler_error);
		}
		parser->current->key = ft_strsub(parser->buffer, 0, parser->buffer_offset);
		if (parser->current->key == NULL)
		{
			cson_log_error(strerror(errno), err, CSON_MEM_ALLOC_ERROR);
			return (handler_error);
		}
		parser->buffer_offset = 0;
		return (handler_skip);
	}
	if (!ft_isalpha(ch))
	{
		cson_log_parsing_error("cson <key> should contain only alpha characters",
		ch, err, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (handler_record);
}

t_handler_status	cson_before_key_handler(t_cson_parser *parser, char ch, int *err)
{
	int	i;

	if (ft_isalpha(ch))
	{
		i = 0;
		while (i++ < parser->indent - parser->buffer_offset)
			parser->current = parser->parent;
		parser->indent = parser->indent - (parser->indent - parser->buffer_offset);
		parser->state = CSON_PARSER_KEY_STATE;
		parser->buffer_offset = 0;
		return (handler_record);
	}
	else if (ch != '\t' || parser->buffer_offset >= parser->indent)
	{
		cson_log_parsing_error("bad identation before key",
		ch, err, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (handler_record);
}
