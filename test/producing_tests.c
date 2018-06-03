/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int		main(int argc, const char *argv[])
{
	t_error_code	err;

	if (argc <= 2)
	{
		dprintf(2, "usage: src_file dest_file");
		return (1);
	}
	const t_cson *cson = cson_parse_file(argv[1], &err);
	err = cson_produce_file(cson, argv[2], TRUE);
	return (0);
}
