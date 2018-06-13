# Compilation
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
OBJ_OUT = $(patsubst %.o,$(OUT)/%.o,$(OBJECTS))
TARGET  = main

.PHONY: all clean

.all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(MKD) $(OUT)
	$(CC) $(OBJ_OUT) -o $(OUT)/$(TARGET) -lm

%.o: %.c
	$(MKD) $(OUT)
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $(OUT)/$@

clean:
	$(RMD) $(OUT) %.o
