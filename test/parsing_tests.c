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

static long long	perform_test(const char *file)
{
	int			err;
	t_cson		*cson;
	long long	addr;

	printf(" === File test: %s\n", file);
	cson = cson_parse_file(file, &err);
	addr = (long long)cson;
	cson_print(cson);
	cson_free(cson);
	return (addr);
}

#define SUCCESS	"\x1b[32mSUCCESS\x1b[0m"
#define FAIL	"\x1b[31mFAIL\x1b[0m"

int		main(void)
{
	long long	addr;

	printf("BASIC TESTS:\n");
	addr = 0xFFFFFFFFFFFFFFFF;
	addr &= perform_test(SAMPLE_DIR "simple_pairs.cson");
	addr &= perform_test(SAMPLE_DIR "tree_pairs.cson");
	addr &= perform_test(SAMPLE_DIR "large.cson");
	printf("%s\n", !addr ? FAIL : SUCCESS);

	printf("BASIC ERRORS TESTS:\n");
	addr = 0;
	addr |= perform_test("absentfile.cson");
	printf("%s\n", addr ? FAIL : SUCCESS);

	/*
	**	STRING
	*/
	printf("STRING TESTS:\n");
	addr = 0xFFFFFFFFFFFFFFFF;
	addr &= perform_test(SAMPLE_DIR "string/string.cson");
	addr &= perform_test(SAMPLE_DIR "string/string_eof.cson");
	addr &= perform_test(SAMPLE_DIR "string/multiple_string.cson");
	addr &= perform_test(SAMPLE_DIR "string/multiple_string_with_escp.cson");
	printf("%s\n", !addr ? FAIL : SUCCESS);

	printf("STRING ERRORS TESTS:\n");
	addr = 0;
	addr |= perform_test(SAMPLE_DIR "string/error_string1.cson");
	addr |= perform_test(SAMPLE_DIR "string/error_string2.cson");
	printf("%s\n", addr ? FAIL : SUCCESS);

	/*
	**	NUMBER
	*/
	printf("NUMBER TESTS:\n");
	addr = 0xFFFFFFFFFFFFFFFF;
	addr &= perform_test(SAMPLE_DIR "number/numbers.cson");
	addr &= perform_test(SAMPLE_DIR "number/number_eof.cson");
	printf("%s\n", !addr ? FAIL : SUCCESS);

	printf("NUMBER ERRORS TESTS:\n");
	addr = 0;
	addr |= perform_test(SAMPLE_DIR "number/error_number1.cson");
	addr |= perform_test(SAMPLE_DIR "number/error_number2.cson");
	addr |= perform_test(SAMPLE_DIR "number/error_number3.cson");
	addr |= perform_test(SAMPLE_DIR "number/error_number4.cson");
	addr |= perform_test(SAMPLE_DIR "number/error_number5.cson");
	addr |= perform_test(SAMPLE_DIR "number/error_number6.cson");
	addr |= perform_test(SAMPLE_DIR "number/error_number7.cson");
	addr |= perform_test(SAMPLE_DIR "number/error_number8.cson");
	addr |= perform_test(SAMPLE_DIR "number/error_number9.cson");
	printf("%s\n", addr ? FAIL : SUCCESS);

	/*
	**	BOOLEAN
	*/
	printf("BOOLEAN TESTS:\n");
	addr = 0xFFFFFFFFFFFFFFFF;
	addr &= perform_test(SAMPLE_DIR "bool/bool_eof.cson");
	addr &= perform_test(SAMPLE_DIR "bool/bools.cson");
	printf("%s\n", !addr ? FAIL : SUCCESS);

	printf("BOOLEAN ERROR TESTS:\n");
	addr = 0;
	addr |= perform_test(SAMPLE_DIR "bool/error_bool1.cson");
	addr |= perform_test(SAMPLE_DIR "bool/error_bool2.cson");
	addr |= perform_test(SAMPLE_DIR "bool/error_bool3.cson");
	addr |= perform_test(SAMPLE_DIR "bool/error_bool4.cson");
	addr |= perform_test(SAMPLE_DIR "bool/error_bool5.cson");
	addr |= perform_test(SAMPLE_DIR "bool/error_bool6.cson");
	addr |= perform_test(SAMPLE_DIR "bool/error_bool7.cson");
	addr |= perform_test(SAMPLE_DIR "bool/error_bool8.cson");
	addr |= perform_test(SAMPLE_DIR "bool/error_bool9.cson");
	printf("%s\n", addr ? FAIL : SUCCESS);

	/*
	**	ARRAY
	*/
	printf("ARRAY TESTS:\n");
	addr = 0xFFFFFFFFFFFFFFFF;
	addr &= perform_test(SAMPLE_DIR "array/array_string.cson");
	addr &= perform_test(SAMPLE_DIR "array/arrays.cson");
	printf("%s\n", !addr ? FAIL : SUCCESS);

	printf("ARRAY ERROR TESTS:\n");
	addr = 0;
	printf("%s\n", addr ? FAIL : SUCCESS);
#if 1
	system("leaks btest | tail -n 1");
#else
	system("leaks btest");
#endif
	return (0);
}