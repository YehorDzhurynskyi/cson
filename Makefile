#	libft
LIBFT			:=	libft.a
LIBFT_DIR		:=	./libft/
LIBFT_SRC		=
LIBFT_OBJ		=
LIBFT_OBJ_DIR	:=	./obj/libft/

#	compilation
CC				:=	clang
CFLAGS			:=	-g -c -Wall -Wextra -Werror
INCLUDE			:=	-I$(LIBFT_DIR)include/ -I./include/ -I.

#	CSON
CSON			:=	libcson.a
CSON_DIR		:= ./
CSON_SRC		=
CSON_OBJ		=
CSON_OBJ_DIR	:=	./obj/

all: $(CSON)

include ./src/src.mk
include ./src/cson_parser/cson_parser.mk
include ./src/cson_navigator/cson_navigator.mk
include $(LIBFT_DIR)libft.mk

$(CSON): $(CSON_OBJ)
	ar rc $(CSON) $(CSON_OBJ)
	ranlib $(CSON)

clean:
	rm -f $(CSON_OBJ)
	rm -f $(LIBFT_OBJ)

fclean: clean
	rm -f $(LIBFT)
	rm -f $(CSON)

re: fclean all