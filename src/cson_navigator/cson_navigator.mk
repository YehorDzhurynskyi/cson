CSON_CSON_NAVIGATOR_DIR	:=	$(CSON_DIR)src/cson_navigator/
CSON_CSON_NAVIGATOR_SRC	:=	cson_foreach.c\
							cson_depth.c\

CSON_CSON_NAVIGATOR_OBJ	=	$(addprefix $(CSON_OBJ_DIR), $(CSON_CSON_NAVIGATOR_SRC:.c=.o))
CSON_CSON_NAVIGATOR		+=	$(addprefix $(CSON_CSON_NAVIGATOR_DIR), $(CSON_CSON_NAVIGATOR_SRC))
CSON_OBJ				+=	$(CSON_CSON_NAVIGATOR_OBJ)

$(CSON_CSON_NAVIGATOR_OBJ): $(CSON_OBJ_DIR)%.o: $(CSON_CSON_NAVIGATOR_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
