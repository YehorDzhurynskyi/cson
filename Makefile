DEPENDENCY_DIR	:=	./Dependencies/

#	libft
LIBFT_DIR		=	$(DEPENDENCY_DIR)libft/
LIBFT			=	$(LIBFT_DIR)/libft.a

#	compilation
CC				:=	clang
CFLAGS			:=	-g -c -Wall -Wextra -Werror
INCLUDE			:=	-I$(LIBFT_DIR) -I.

#	CSON
CSON			:=	libcson.a
CSON_DIR		:= ./
CSON_SRC		=
CSON_OBJ		=
CSON_OBJ_DIR	:=	./obj/

all: $(CSON)

include ./cson.mk

#	basic test
btest: ./test/parsing_tests.c $(LIBFT) $(CSON)
	$(CC) -DSAMPLE_DIR="\"/Users/ydzhuryn/forgit/cson/test/samples/\"" -I. -I./libft/ $< -L. -lcson -L./libft/ -lft -o $@.out

produce: ./test/producing_tests.c $(LIBFT) $(CSON)
	$(CC) -I. -I$(LIBFT_DIR) $< -L. -lcson -L$(LIBFT_DIR) -lft -o $@

clean:
#	rm -f $(LIBFT_OBJ)
	rm -f $(CSON_OBJ)

fclean: clean
#	rm -f $(LIBFT)
	rm -f $(CSON)

re: fclean all