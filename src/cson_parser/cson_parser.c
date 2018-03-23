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
		cson_boolean_handler,
		cson_boolean_handler,
		cson_eov_handler
	};
	return (state_handler_pool[state]);
}

void					cson_parse_chunk(t_cson_parser *parser, const char *buffer, size_t size)
{
	int					i;
	t_state_handler		state_handler;
	t_handler_status	status;

	i = -1;
	while (++i < (int)size)
	{
		if (buffer[i] == '\n')
			parser->current_line++;
		// ft_printf("STATE IS = %d, CHAR IS = %c\n", parser->state, buffer[i]);
		state_handler = determine_state_handler(parser->state);
		status = state_handler(parser, buffer[i]);
		if (status == handler_error)
			return ;
		else if (status == handler_record)
		{
			if (cson_ensure_buffer_capacity(parser) == FALSE)
			{
				cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
				return ;
			}
			parser->buffer[parser->buffer_offset++] = buffer[i];
		}
	}
}

t_bool					cson_init_parser(t_cson_parser *parser, int *err)
{
	parser->root = cson_alloc(NULL);
	parser->root->value.tuple = alst_create(3);
	parser->root->value_type = CSON_OBJECT_VALUE_TYPE;
	parser->current = parser->root;
	parser->parent = parser->root;
	parser->state = CSON_PARSER_BEFORE_KEY_STATE;
	parser->buffer_size = CSON_PARSER_BSIZE;
	parser->buffer = (char*)malloc(sizeof(char) * parser->buffer_size);
	parser->buffer_offset = 0;
	parser->current_line = 1;
	parser->err = err;
	if (parser->root == NULL || parser->root->value.tuple == NULL || parser->buffer == NULL)
	{
		cson_log_error(parser, strerror(errno), CSON_MEM_ALLOC_ERROR);
		cson_free_parser(parser);
		return (FALSE);
	}
	return (TRUE);
}

void					cson_free_parser(t_cson_parser *parser)
{
	cson_free(parser->root);
	free(parser->buffer);
	parser->buffer = NULL;
	parser->root = NULL;
}
