NAME = uchat

INC = ./inc/header.h ./inc/ssl.h ./inc/cJSON.h ./inc/json_functions.h ./inc/database.h ./inc/uchat.h

HEADTMP = ./header.h ./ssl.h ./cJSON.h ./json_functions.h ./database.h ./uchat.h

SRC = ./*.c #./client.c ./server.c ./main.c ./ssl.c ./daemon.c ./cJSON.c ./json_functions.c ./mx_help.c ./mx_db.c

SRCS = ./src/*.c #./src/client.c ./src/server.c ./src/main.c ./src/ssl.c ./src/daemon.c ./src/cJSON.c ./src/json_functions.c ./src/mx_help.c ./src/mx_db.c

OBJ = ./*.o #./client.o ./server.o ./main.o ./ssl.o ./daemon.o ./cJSON.o ./json_functions.o ./mx_help.o ./mx_db.o

OBJO = ./obj/*.o #./obj/client.o ./obj/server.o ./obj/main.o ./obj/ssl.o ./obj/daemon.o ./obj/cJSON.o ./obj/json_functions.o ./obj/mx_help.o ./obj/mx_db.o

SSL_PATH = -I/usr/local/opt/openssl/include

CFLGS = $(SSL_PATH) `pkg-config --cflags gtk+-3.0 pkg-config --libs gtk+-3.0`  -g -fsanitize=address

SQLITE = -lsqlite3

PTHREAD = -lpthread

SSL = -L/usr/local/opt/openssl/lib/ -lssl -lcrypto

all: install clean

install:
	@make -C libmx -f Makefile install
	@cp $(INC) $(SRCS) .
	@clang $(CFLGS) -c $(SRC)
	@mkdir -pv obj
	@mv $(OBJ) ./obj
	@clang $(CFLGS) $(OBJO) libmx/libmx.a -o $(NAME) $(SQLITE) $(SSL) $(PTHREAD)

uninstall: clean
	@make -C libmx -f Makefile uninstall
	@rm -rf $(NAME)

clean:
	@make clean -C libmx
	@rm -rf $(OBJO)
	@rm -rf $(SRC)
	@rm -rf $(OBJ)
	@rm -rf $(HEADTMP)
	@rm -rf ./obj

reinstall: uninstall install

keys:
	@chmod 777 ./source/compiler_script.sh
	@./source/compiler_script.sh

db:
	@chmod 777 ./source/create_database.sh
	@./source/create_database.sh

del_keys:
	@rm -rf keys

del_db:
	@rm database.db
	@rm -rf database

