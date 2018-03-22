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

void	cson_free_parser(t_cson_parser *parser)
{
	cson_free(parser->root);
	free(parser->buffer);
	parser->buffer = NULL;
	parser->root = NULL;
}

t_cson		*cson_parse_file(const char *filename, int *err)
{
	int				fd;
	t_cson_parser	parser;
	char			buffer[CSON_PARSER_BSIZE + 1];
	ssize_t			ret;

	parser = cson_init_parser();
	if (parser.root == NULL || parser.root->value.tuple == NULL || parser.buffer == NULL)
	{
		cson_log_error(strerror(errno), err, CSON_MEM_ALLOC_ERROR);
		cson_free_parser(&parser);
		return (NULL);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		cson_log_error(strerror(errno), err, CSON_FILE_OPENING_ERROR);
		cson_free_parser(&parser);
		return (NULL);
	}
	while ((ret = read(fd, buffer, CSON_PARSER_BSIZE)) > 0)
	{
		cson_parse_chunk(&parser, buffer, (size_t)ret, err);
		if (*err != 0)
			break ;
	}
	if (ret < 0)
	{
		cson_log_error(strerror(errno), err, CSON_FILE_READING_ERROR);
		cson_free_parser(&parser);
	}
	close(fd);
	free(parser.buffer);
	return (parser.root);
}
