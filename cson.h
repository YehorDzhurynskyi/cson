/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cson.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CSON_H
# define CSON_H

# include "ft.h"

# define CSON_UNDEFINED_VALUE_TYPE	0x0
# define CSON_STRING_VALUE_TYPE		0x1
# define CSON_INTEGER_VALUE_TYPE	0x2
# define CSON_REAL_VALUE_TYPE		0x3
# define CSON_BOOLEAN_VALUE_TYPE	0x4
# define CSON_ARRAY_VALUE_TYPE		0x5
# define CSON_OBJECT_VALUE_TYPE		0x6

# define CSON_MEM_ALLOC_ERROR		0x1
# define CSON_FILE_OPENING_ERROR	0x2
# define CSON_FILE_READING_ERROR	0x3
# define CSON_KEY_PARSING_ERROR		0x4
# define CSON_VALUE_PARSING_ERROR	0x5

typedef union u_cson_value	t_cson_value;
union						u_cson_value
{
	long long				integer;
	double					real;
	long long				boolean;
	char					*string;
	t_alst					*tuple;
};

typedef struct s_cson		t_cson;
struct						s_cson
{
	char					*key;
	t_cson_value			value;
	int						value_type;
	t_cson					*parent;
};

t_cson						*cson_parse_file(const char *filename, int *err);
// int							cson_type_of_node(const t_cson *cson, const char *nodepath);
// char				*const	cson_get_string(const t_cson *cson, const char *nodepath);
// int							cson_get_integer(const t_cson *cson, const char *nodepath);
// double						cson_get_real(const t_cson *cson, const char *nodepath);
// const t_cson		*const	cson_get_array(const t_cson *cson, const char *nodepath, size_t *size);
// const t_cson		*const	cson_get_object(const t_cson *cson, const char *nodepath);
void						cson_print(const t_cson *cson);
void						cson_foreach(const t_cson *cson, void (*func)(const t_cson *item));
void						cson_free(t_cson *cson);

#endif
