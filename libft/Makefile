LIBFT			:=	libft.a
LIBFT_SRC		=
LIBFT_OBJ		=
LIBFT_DIR		:=	./
LIBFT_OBJ_DIR	:=	./obj/

CFLAGS			:=	-c -Wall -Wextra -Werror
INCLUDE			:=	./include
CC				:=	gcc
INCLUDE			:=	-I./include/

all: $(LIBFT)

include ./libft.mk

clean:
	/bin/rm -f $(LIBFT_OBJ)

fclean: clean
	/bin/rm -f $(LIBFT)

re: fclean all
