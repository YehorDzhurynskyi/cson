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

int		main(void)
{
	int		err;
	t_cson	*cson;
	char dir[255];
	getcwd(dir, 255);

	cson = cson_parse_file(SAMPLE_DIR "simple_pairs.cson", &err);
	cson_print(cson);
	ft_printf("Error mask: %05b\n", err);
	system("leaks btest | tail -n 1");
	return (0);
}