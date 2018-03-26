/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson_parser.h"

inline t_bool	cson_is_key_symbol(char ch)
{
	return (ft_isprint(ch) && ch != '#' && ch != ':'
	&& ch != ' ');
}

inline t_bool	cson_is_quoted_key(const t_cson_parser *parser)
{
	return (parser->buffer[0] == '\'' || parser->buffer[0] == '"');
}
