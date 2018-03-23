/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_file_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

t_bool	cson_flush_buffer(t_cson_parser *parser)
{
	if (parser->state == CSON_PARSER_STRING_VALUE_STATE)
	{
		cson_log_error(parser, "the value of the string should have a closing quote", CSON_VALUE_PARSING_ERROR);
		return (FALSE);
	}
	return (cson_assign_value(parser));
}

void	cson_free_parser(t_cson_parser *parser)
{
	cson_free(parser->root);
	free(parser->buffer);
	parser->buffer = NULL;
	parser->root = NULL;
}

static void	*shutdown_parsing(t_cson_parser *parser, int fd, int errcode)
{
	cson_log_error(parser, strerror(errno), errcode);
	cson_free_parser(parser);
	if (fd != -1)
		close(fd);
	return (NULL);
}

t_cson	*cson_parse_file(const char *filename, int *err)
{
	int				fd;
	t_cson_parser	parser;
	char			buffer[CSON_PARSER_BSIZE + 1];
	ssize_t			ret;

	fd = -1;
	if (cson_init_parser(&parser) == FALSE)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (shutdown_parsing(&parser, fd, CSON_FILE_OPENING_ERROR));
	while ((ret = read(fd, buffer, CSON_PARSER_BSIZE)) > 0)
	{
		cson_parse_chunk(&parser, buffer, (size_t)ret);
		if (parser.err != 0)
			break ;
	}
	if (ret < 0)
		return (shutdown_parsing(&parser, fd, CSON_FILE_READING_ERROR));
	if (parser.err == 0 && cson_flush_buffer(&parser) == FALSE)
		cson_free_parser(&parser);
	close(fd);
	free(parser.buffer);
	*err = parser.err;
	return (parser.root);
}
