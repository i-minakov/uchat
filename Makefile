NAME = uchat
INC = inc/*.h
SRC := $(wildcard src/*.c)
OBJ = $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
LIBMX = libmx/libmx.a
SSL_PATH = -I/usr/local/opt/openssl/include
FLAGS = $(SSL_PATH) $(SANFLAG) -std=c11 -Wall -Wextra -Werror -Wpedantic 
SANFLAG = -g -fsanitize=address
SQLITE = -lsqlite3
PTHREAD = -lpthread
SSL = -L/usr/local/opt/openssl/lib/ -lssl -lcrypto
INCD = inc

all: $(NAME)

install: $(NAME)

$(NAME): $(LIBMX) $(OBJ)
	@make clean
	@clang $(FLAGS) `pkg-config --cflags --libs gtk+-3.0` $(OBJ) $(LIBMX) -o $(NAME) $(SQLITE) $(SSL) $(PTHREAD)
	@printf "\x1b[32;1m$(NAME) created\x1b[0m\n"

$(LIBMX):
	@make -C libmx

$(OBJ): | obj

obj:
	@mkdir obj

obj/%.o: src/%.c $(INC)
	@clang $(FLAGS) `pkg-config --cflags gtk+-3.0` -o $@ -c $< 
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

clean:
	@rm -rf *.o ush.dSYM
	@make clean -C libmx

uninstall: clean
	@make uninstall -C libmx
	@make clean
	@rm -rf ./obj
	@rm -rf $(NAME)

reinstall: uninstall install

keys:
	@chmod 777 ./source/compiler_script.sh
	@./source/compiler_script.sh

db:
	@chmod 777 ./source/create_database.sh
	@./source/create_database.sh

del_cash:
	@./source/del_cash.sh

del_keys:
	@rm -rf keys

del_db:
	@rm database.db
	@rm -rf database

d:
	@clang $(FLAGS) $(SANFLAG) $(SQLITE) $(SSL) $(PTHREAD) src/*.c libmx/libmx.a
