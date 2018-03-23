/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_parser.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSON_PARSER_H
# define CSON_PARSER_H

# include "cson.h"
# include <errno.h>

# define CSON_PARSER_BSIZE	1024

# define CSON_PARSER_BEFORE_KEY_STATE			0
# define CSON_PARSER_KEY_STATE					1
# define CSON_PARSER_AFTER_KEY_STATE			2
# define CSON_PARSER_BEFORE_VALUE_STATE			3
# define CSON_PARSER_STRING_VALUE_STATE			4
# define CSON_PARSER_ARRAY_VALUE_STATE			5
# define CSON_PARSER_EMPTY_OBJECT_VALUE_STATE	6
# define CSON_PARSER_OBJECT_VALUE_STATE			7
# define CSON_PARSER_NUMBER_VALUE_STATE			8
# define CSON_PARSER_TRUE_VALUE_STATE			9
# define CSON_PARSER_FALSE_VALUE_STATE			10
# define CSON_PARSER_EOV_STATE					11

typedef enum e_handler_status	t_handler_status;
enum				e_handler_status
{
	handler_error,
	handler_skip,
	handler_record
};

typedef struct s_cson_parser	t_cson_parser;
struct				s_cson_parser
{
	t_cson			*root;
	t_cson			*current;
	t_cson			*parent;
	char			*buffer;
	size_t			buffer_size;
	int				buffer_offset;
	int				state;
	int				current_line;
	int				err;
};

void				cson_log_parsing_error(t_cson_parser *parser, const char *msg, char error_symbol, int errcode);
void				cson_log_error(t_cson_parser *parser, const char *msg, int errcode);
t_cson				*cson_alloc(t_cson *is_root);
t_cson_parser		cson_init_parser(void);
void				cson_free_parser(t_cson_parser *parser);
void				cson_parse_chunk(t_cson_parser *parser, const char *buffer, size_t size);

/*
**	Finite-state machine handlers
*/
typedef t_handler_status	(*t_state_handler)(t_cson_parser *parser, char ch);

t_handler_status	cson_array_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_boolean_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_eov_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_before_value_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_after_key_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_key_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_before_key_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_number_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_empty_object_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_object_handler(t_cson_parser *parser, char ch);
t_handler_status	cson_string_handler(t_cson_parser *parser, char ch);

t_bool				cson_flush_buffer(t_cson_parser *parser);
t_bool				cson_assign_value(t_cson_parser *parser);

#endif
