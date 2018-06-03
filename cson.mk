include ./src/src.mk
include ./src/cson_parser/cson_parser.mk
include ./src/cson_producer/cson_producer.mk
include ./src/cson_navigator/cson_navigator.mk
include ./src/cson_builder/cson_builder.mk

$(CSON): $(CSON_OBJ)
	ar rc $@ $^
	ranlib $@
