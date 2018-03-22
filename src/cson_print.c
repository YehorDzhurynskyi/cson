/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_foreach.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

static int	count_depth(const t_cson *cson)
{
	int depth;

	depth = 0;
	while (cson->parent)
	{
		depth++;
		cson = cson->parent;
	}
	return (depth);
}

static void	print_node(const t_cson *cson)
{
	int	depth;

	depth = count_depth(cson);
	while (depth--)
		ft_putchar('\t');
	ft_printf("%s:", cson->key);
	if (cson->value_type == CSON_STRING_VALUE_TYPE)
		ft_printf(" '%s'", cson->value.string);
	else if (cson->value_type == CSON_INTEGER_VALUE_TYPE)
		ft_printf(" %d", cson->value.integer);
	else if (cson->value_type == CSON_REAL_VALUE_TYPE)
		ft_printf(" %f", cson->value.real);
	else if (cson->value_type == CSON_BOOLEAN_VALUE_TYPE)
		ft_printf(" %s", cson->value.boolean == FALSE ? "false" : "true");
	else if (cson->value_type == CSON_OBJECT_VALUE_TYPE && cson->value.tuple->size == 0)
		ft_printf(" {}");
	else if (cson->value_type == CSON_ARRAY_VALUE_TYPE)
		ft_printf(" [");
	ft_putchar('\n');
}

void		cson_print(const t_cson *cson)
{
	cson_foreach(cson, print_node);
}
