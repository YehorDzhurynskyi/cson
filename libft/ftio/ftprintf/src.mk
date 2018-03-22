SRC_DIR	:=	./src/
SRC_SRC	:=	printf.c\
			conversion.c\
			color.c\
			parser.c\
			conversion_handler.c\
			recognizer.c\
			conversion_recognizer.c\
			output.c\
			integer.c\
			hinteger.c\
			hhinteger.c\
			linteger.c\
			llinteger.c\
			zinteger.c\
			jinteger.c\
			tinteger.c\
			number_manager.c\
			real_manager.c\
			text_manager.c\
			wtext_manager.c\
			multibyte.c\
			real.c\
			freal.c\
			ereal.c\
			greal.c\
			wildcard.c\

SRC_OBJ	=	$(addprefix $(OBJ_DIR), $(SRC_SRC:.c=.o))
SRC		+=	$(addprefix $(SRC_DIR), $(SRC_SRC))
OBJ		+=	$(SRC_OBJ)

$(SRC_OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $(INCLUDE) $< -o $@
