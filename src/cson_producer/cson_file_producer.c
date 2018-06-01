/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_file_producer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"
#include <errno.h>

t_error_code	cson_produce_file(const t_cson *cson, const char *filename, t_bool override_file)
{
	int	fd;

	if (cson == NULL || filename == NULL)
		return (CSON_NULL_PARAMETER_ERRROR);
	fd = open(filename, O_WRONLY | O_CREAT
	| (override_file ? O_TRUNC : O_EXCL), 0666);
	if (fd < 0)
	{
		cson_log_producing_error(strerror(errno), CSON_FILE_OPENING_ERROR);
		return (CSON_FILE_OPENING_ERROR);
	}

}
