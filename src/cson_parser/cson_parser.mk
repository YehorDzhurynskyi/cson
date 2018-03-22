CSON_CSON_PARSER_DIR	:=	$(CSON_DIR)src/cson_parser/
CSON_CSON_PARSER_SRC	:=	cson_array_handler.c\
							cson_boolean_handler.c\
							cson_eov_handler.c\
							cson_file_parser.c\
							cson_key_handler.c\
							cson_number_handler.c\
							cson_object_handler.c\
							cson_parser.c\
							cson_string_handler.c\

CSON_CSON_PARSER_OBJ	=	$(addprefix $(CSON_OBJ_DIR), $(CSON_CSON_PARSER_SRC:.c=.o))
CSON_CSON_PARSER		+=	$(addprefix $(CSON_CSON_PARSER_DIR), $(CSON_CSON_PARSER_SRC))
CSON_OBJ				+=	$(CSON_CSON_PARSER_OBJ)

$(CSON_CSON_PARSER_OBJ): $(CSON_OBJ_DIR)%.o: $(CSON_CSON_PARSER_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
