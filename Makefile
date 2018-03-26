#	libft
LIBFT			:=	libft.a
LIBFT_DIR		:=	./libft/
LIBFT_SRC		=
LIBFT_OBJ		=
LIBFT_OBJ_DIR	:=	./obj/libft/

#	compilation
CC				:=	clang
CFLAGS			:=	-g -c -Wall -Wextra -Werror
INCLUDE			:=	-I$(LIBFT_DIR) -I$(LIBFT_DIR)/include/ -I./include/ -I.

#	CSON
CSON			:=	libcson.a
CSON_DIR		:= ./
CSON_SRC		=
CSON_OBJ		=
CSON_OBJ_DIR	:=	./obj/

all: $(CSON)

include $(LIBFT_DIR)libft.mk
include ./cson.mk

#	basic test
btest: ./test/parsing_tests.c $(LIBFT) $(CSON)
	$(CC) -DSAMPLE_DIR="\"/Users/ydzhuryn/forgitln/cson/test/samples/\"" -I. -I./libft/ $< -L. -lcson -L./libft/ -lft -o $@.out


clean:
#	rm -f $(LIBFT_OBJ)
	rm -f $(CSON_OBJ)

fclean: clean
#	rm -f $(LIBFT)
	rm -f $(CSON)

re: fclean all