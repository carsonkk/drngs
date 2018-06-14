# Compilation
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c,$(OUT)/%.o,$(SOURCES))
TARGETS = $(patsubst %.o,%,$(OBJECTS))

.PHONY: all clean

.all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(MKD) $(OUT)
	for f in $(TARGETS); do $(CC) $(SRC_DIR)/$(OUT)/*.o $$f.o -o $$f -lm; done

$(OUT)/%.o: %.c
	$(MKD) $(OUT)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

clean:
	$(RMD) $(OUT) %.o
