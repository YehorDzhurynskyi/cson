/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_logger.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

void	cson_log_parsing_error(const char *msg, char error_symbol, int *err, int errcode)
{
	*err = errcode;
	ft_printf_fd(2, "[%#x] CSON Parsing error: %s on symbol"
	"- '%c' (ascii code is %d)\n", errcode, msg, error_symbol, (int)error_symbol);
}

void	cson_log_error(const char *msg, int *err, int errcode)
{
	*err = errcode;
	ft_printf_fd(2, "[%#x] CSON Parsing error: %s\n", errcode, msg);
}
