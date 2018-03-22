/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_eov_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

t_handler_status	cson_eov_handler(t_cson_parser *parser, char ch, int *err)
{
	if (ft_isws(ch) == FALSE)
	{
		cson_log_parsing_error("unrecognized symbol after the value",
		ch, err, CSON_VALUE_PARSING_ERROR);
		return (handler_error);
	}
	if (ch == '\n')
		parser->state = CSON_PARSER_BEFORE_KEY_STATE;
	return (handler_skip);
}
