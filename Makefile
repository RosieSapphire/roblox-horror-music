CC=gcc
INCDIRS=-I./include/ -I/usr/include/
LIBS=-lm -lcsfml-system -lcsfml-audio

OPT_DEBUG=-O0
CFLAGS_DEBUG=-Wall -Wextra -Werror -ansi -pedantic -g3 $(INCDIRS) $(OPT_DEBUG)

OPT_RELEASE=-O2
CFLAGS_RELEASE=-ansi -pedantic $(INCDIRS) $(OPT_RELEASE)

CFILES=main.c
OBJECTS=obj/main.o

BINARY_RELEASE=roblox
BINARY_DEBUG=roblox-d

all: $(BINARY_RELEASE)
release: $(BINARY_RELEASE)
debug: $(BINARY_DEBUG)

$(BINARY_RELEASE): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)
	rm -rf obj/
	@echo -e "\033[92mCOMPILED \033[96mRELEASE \033[92mBUILD SUCCESSFULLY\033[0m"

$(BINARY_DEBUG): $(OBJECTS)d
	$(CC) -o $@ $^ $(LIBS)
	@echo -e "\033[92mCOMPILED \033[95mDEBUG \033[92mBUILD SUCCESSFULLY\033[0m"

obj/%.o: src/%.c
	@mkdir -p obj/
	$(CC) $(CFLAGS_RELEASE) -c -o $@ $^

obj/%.od: src/%.c
	@mkdir -p obj/
	$(CC) $(CFLAGS_DEBUG) -c -o $@ $^

run:
	./$(BINARY_RELEASE)

rund:
	gdb ./$(BINARY_DEBUG) --tui

go:
	make clean
	make release
	make run

god:
	make clean
	make debug
	make rund

clean:
	rm -rf $(BINARY_RELEASE) $(BINARY_DEBUG) obj/
	clear
