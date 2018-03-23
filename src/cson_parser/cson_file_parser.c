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

static void	*shutdown_parsing(t_cson_parser *parser, int fd, int errcode)
{
	cson_log_error(parser, strerror(errno), errcode);
	cson_free_parser(parser);
	if (fd != -1)
		close(fd);
	return (NULL);
}

t_cson		*cson_parse_file(const char *filename, int *err)
{
	int				fd;
	t_cson_parser	parser;
	char			buffer[CSON_PARSER_BSIZE + 1];
	ssize_t			ret;

	fd = -1;
	if (cson_init_parser(&parser, err) == FALSE)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (shutdown_parsing(&parser, fd, CSON_FILE_OPENING_ERROR));
	while ((ret = read(fd, buffer, CSON_PARSER_BSIZE)) > 0)
	{
		cson_parse_chunk(&parser, buffer, (size_t)ret);
		if (*parser.err != 0)
			break ;
	}
	if (ret < 0)
		return (shutdown_parsing(&parser, fd, CSON_FILE_READING_ERROR));
	if (*parser.err != 0 || cson_flush_buffer(&parser) == FALSE)
		cson_free_parser(&parser);
	close(fd);
	free(parser.buffer);
	return (parser.root);
}
