/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include <stdlib.h>

static t_bool			ensure_buffer_capacity(t_cson_parser *parser)
{
	char	*buffer;

	if (parser->buffer_offset == (int)parser->buffer_size - 1)
	{
		buffer = malloc(sizeof(char) * (parser->buffer_size * 2));
		if (buffer == NULL)
			return (FALSE);
		ft_memcpy(buffer, parser->buffer, parser->buffer_size);
		free(parser->buffer);
		parser->buffer_size = parser->buffer_size * 2;
		parser->buffer = buffer;
	}
	return (TRUE);
}

static t_state_handler	determine_state_handler(int state)
{
	static t_state_handler	state_handler_pool[] = {
		cson_before_key_handler,
		cson_key_handler,
		cson_after_key_handler,
		cson_before_value_handler,
		cson_string_handler,
		cson_array_handler,
		cson_empty_object_handler,
		cson_object_handler,
		cson_number_handler,
		cson_true_handler,
		cson_false_handler,
		cson_eov_handler
	};
	return (state_handler_pool[state]);
}

void	cson_parse_chunk(t_cson_parser *parser, const char *buffer, size_t size, int *err)
{
	int					i;
	t_state_handler		state_handler;
	t_handler_status	status;

	i = -1;
	while (++i < (int)size)
	{
		state_handler = determine_state_handler(parser->state);
		status = state_handler(parser, buffer[i], err);
		if (status == handler_error)
		{
			cson_free_parser(parser);
			return ;
		}
		else if (status == handler_record)
		{
			if (ensure_buffer_capacity(parser) == FALSE)
			{
				cson_log_error(strerror(errno), err, CSON_MEM_ALLOC_ERROR);
				cson_free_parser(parser);
			}
			parser->buffer[parser->buffer_offset++] = buffer[i];
		}
	}
}

t_cson	*parse_cson(const char *buffer, size_t size, int *err)
{
	t_cson_parser	parser;

	parser = cson_init_parser();
	if (parser.root == NULL || parser.root->value.tuple == NULL || parser.buffer == NULL)
	{
		cson_log_error(strerror(errno), err, CSON_MEM_ALLOC_ERROR);
		cson_free_parser(&parser);
		return (NULL);
	}
	cson_parse_chunk(&parser, buffer, size, err);
	free(parser.buffer);
	return (parser.root);
}

t_cson_parser	cson_init_parser(void)
{
	t_cson_parser	parser;

	parser.root = cson_alloc(NULL);
	parser.root->value.tuple = alst_create(3);
	parser.root->value_type = CSON_OBJECT_VALUE_TYPE;
	parser.current = parser.root;
	parser.parent = parser.root;
	parser.indent = 0;
	parser.state = CSON_PARSER_BEFORE_KEY_STATE;
	parser.buffer_size = CSON_PARSER_BSIZE;
	parser.buffer = (char*)malloc(sizeof(char) * parser.buffer_size);
	parser.buffer_offset = 0;
	return (parser);
}
