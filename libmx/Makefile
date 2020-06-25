NAME = libmx.a

INC = inc/libmx.h
SRC := $(wildcard src/*.c)
OBJ = $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: $(NAME)

install: $(NAME)

$(NAME): $(OBJ)
	@make clean
	@ar -rcs $(NAME) $(OBJ)
	@printf "\x1b[32;1m$@ created\x1b[0m\n"

$(OBJ): | obj

obj:
	@mkdir obj

obj/%.o: src/%.c $(INC)
	@clang $(FLAGS) -c $< -o $@
	@printf "\x1b[32mcompiled: \x1b[0m[libmx/$<]\n"

uninstall:
	@make clean
	@rm -rf ./obj
	@rm -rf $(NAME)

clean:
	@rm -rf *.o

reinstall: uninstall install
