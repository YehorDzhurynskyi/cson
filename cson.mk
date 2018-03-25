include ./src/src.mk
include ./src/cson_parser/cson_parser.mk
include ./src/cson_navigator/cson_navigator.mk

$(CSON): $(CSON_OBJ)
	ar rc $@ $^
	ranlib $@
