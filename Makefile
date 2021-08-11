GCC=gcc -Wall -Werror -Wextra
SOURCES=$(wildcard ./sources/*.c)
NAME=pipex
MAKEFLAGS += --no-print-directory
SOURCES_PATH = $(addprefix sources/, $(SOURCES))

all: $(NAME)

$(NAME):
	gcc $(SOURCES) pipex.c -o $(NAME)

clean:
	rm -rf pipex

re: clean all

fclean: clean