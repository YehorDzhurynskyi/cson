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

static void	perform_test(const char *file)
{
	int		err;
	t_cson	*cson;

	ft_printf(" === File test: %s\n", file);
	cson = cson_parse_file(file, &err);
	cson_print(cson);
	ft_printf(" === Error mask: %05b\n\n", err);
	cson_free(cson);
}

int		main(void)
{
	perform_test(SAMPLE_DIR "simple_pairs.cson");
	perform_test(SAMPLE_DIR "tree_pairs.cson");
#if 1
	system("leaks btest | tail -n 1");
#else
	system("leaks btest");
#endif
	return (0);
}