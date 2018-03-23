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

t_handler_status	cson_before_value_handler(t_cson_parser *parser, char ch)
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
	else if (ft_isdigit(ch) || ch == '+' || ch == '-')
		parser->state = CSON_PARSER_NUMBER_VALUE_STATE;
	else
	{
		cson_log_parsing_error(parser, "unrecognized symbol before a value",
		ch, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (handler_record);
}

t_handler_status	cson_after_key_handler(t_cson_parser *parser, char ch)
{
	if (ch == '\n' || ch == '{')
	{
		if (ch == '\n')
			parser->state = CSON_PARSER_OBJECT_VALUE_STATE;
		else if (ch == '{')
			parser->state = CSON_PARSER_EMPTY_OBJECT_VALUE_STATE;
		return (handler_skip);
	}
	return (cson_before_value_handler(parser, ch));
}

t_handler_status	cson_key_handler(t_cson_parser *parser, char ch)
{
	if (ch == ':')
	{
		if (parser->buffer_offset == 0)
		{
			cson_log_parsing_error(parser, "cson <key> can't be an empty string",
			ch, CSON_KEY_PARSING_ERROR);
			return (handler_error);
		}
		parser->current = cson_alloc(parser->parent);
		if (parser->current == NULL)
		{
			cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
			return (handler_error);
		}
		alst_add(parser->parent->value.tuple, parser->current);
		parser->current->key = ft_strsub(parser->buffer, 0, parser->buffer_offset);
		if (parser->current->key == NULL)
		{
			cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
			return (handler_error);
		}
		parser->state = CSON_PARSER_AFTER_KEY_STATE;
		parser->buffer_offset = 0;
		return (handler_skip);
	}
	if (!ft_isalpha(ch))
	{
		cson_log_parsing_error(parser, "cson <key> should contain only alpha characters",
		ch, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (handler_record);
}

t_handler_status	cson_before_key_handler(t_cson_parser *parser, char ch)
{
	int	depth;
	int	i;

	if (ft_isalpha(ch))
	{
		if (parser->parent != parser->root)
		{
			depth = cson_depth_of_node(parser->parent);
			if (parser->buffer_offset - depth > 0)
			{
				cson_log_error(parser, "bad identation before key",
				CSON_KEY_PARSING_ERROR);
				return (handler_error);
			}
			i = 0;
			while (i++ < depth - parser->buffer_offset)
				parser->parent = parser->parent->parent;
		}
		parser->state = CSON_PARSER_KEY_STATE;
		parser->buffer_offset = 0;
		return (handler_record);
	}
	else if (ch != '\t' && ft_isws(ch))
	{
		parser->buffer_offset = 0;
		return (handler_skip);
	}
	else if (ch != '\t')
	{
		cson_log_parsing_error(parser, "bad symbol before key",
		ch, CSON_KEY_PARSING_ERROR);
		return (handler_error);
	}
	return (handler_record);
}
