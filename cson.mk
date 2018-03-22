$(CSON): $(CSON_OBJ)
	ar rc $@ $^
	ranlib $@
