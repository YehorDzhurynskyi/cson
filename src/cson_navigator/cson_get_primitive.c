/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson_get_primitive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cson.h"

inline const char	*cson_get_string(const t_cson *cson)
{
	return (cson->value.string);
}

inline long long	cson_get_integer(const t_cson *cson)
{
	return (cson->value.integer);
}

inline double		cson_get_real(const t_cson *cson)
{
	return (cson->value.real);
}

inline t_bool		cson_get_boolean(const t_cson *cson)
{
	return (cson->value.boolean == 0 ? FALSE : TRUE);
}
