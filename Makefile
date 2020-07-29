NAME = uchat
NAME_SERVER = uchat_server
INC = ./inc/*.h
SRC := $(wildcard src/*.c) 					\
	   $(wildcard src/daemon_voice/*.c) 	\
	   $(wildcard src/db/*.c) 				\
	   $(wildcard src/help/*.c) 			\
	   $(wildcard src/json_functions/*.c) 	\
	   $(wildcard src/server/*.c) 			\
	   $(wildcard src/client/*.c) 			\
	   $(wildcard src/ssl/*.c)
OBJ = $(addprefix obj/, $(notdir $(SRC:%.c=%.o)))
LIBMX = libmx/libmx.a
PA = ./source/libportaudio/libportaudio.a
SF = ./source/libsndfile/libsndfile.a

OG = ./source/libogg/libogg.a
FC = ./source/libflac/libFLAC.a
OP = ./source/libopus/libopus.a
VB = ./source/libvorbis/lib/libvorbis.a 	\
	 ./source/libvorbis/lib/libvorbisenc.a 	\
	 ./source/libvorbis/lib/libvorbisfile.a
OP_PATH = -I./source/libopus/include
VB_PATH = -I./source/libvorbis/include
OG_PATH = -I./source/libogg/include
FC_PATH = -I./source/libflac/include


SSL_PATH = -I/usr/local/opt/openssl/include
PA_PATH = -I./source/libportaudio/include
SF_PATH = -I./source/libsndfile/include
ADD_FLAG = -framework CoreAudio 	\
		   -framework AudioToolbox 	\
		   -framework AudioUnit 	\
		   -framework Carbon
FLAGS = $(SSL_PATH) $(SANFLAG) 												\
		$(PA_PATH) $(SF_PATH) $(OG_PATH) $(FC_PATH) $(VB_PATH) $(OP_PATH) 	\
		-std=c11 -Wall -Wextra -Werror -Wpedantic
SANFLAG = -g -fsanitize=address
SQLITE = -lsqlite3
PTHREAD = -lpthread
SSL = -L/usr/local/opt/openssl/lib/ -lssl -lcrypto
INCD = inc

all: $(NAME)

install: $(NAME)

$(NAME): $(LIBMX) $(OBJ)
	@chmod 777 ./source/create_database.sh
	@./source/create_database.sh
	@make clean
	@clang $(FLAGS) `pkg-config --cflags --libs gtk+-3.0` 		\
		   $(OBJ) $(LIBMX) $(PA) $(SF) $(OG) $(FC) $(VB) $(OP) 	\
		   -o $(NAME) $(SQLITE) $(SSL) $(PTHREAD) $(ADD_FLAG)
	@clang $(FLAGS) `pkg-config --cflags --libs gtk+-3.0` 		\
		   $(OBJ) $(LIBMX) $(PA) $(SF) $(OG) $(FC) $(VB) $(OP) 	\
		   -o $(NAME_SERVER) $(SQLITE) $(SSL) $(PTHREAD) $(ADD_FLAG)
	@printf "\x1b[32;1m$(NAME) created\x1b[0m\n"

$(LIBMX):
	@make -C libmx

$(OBJ): | obj

client: $(LIBMX) $(OBJ)
	@clang $(FLAGS) `pkg-config --cflags --libs gtk+-3.0` 		\
		   $(OBJ) $(LIBMX) $(PA) $(SF) $(OG) $(FC) $(VB) $(OP) 	\
		   -o $(NAME) $(SQLITE) $(SSL) $(PTHREAD) $(ADD_FLAG)

server: $(LIBMX) $(OBJ)
	@clang $(FLAGS) `pkg-config --cflags --libs gtk+-3.0` 		\
		   $(OBJ) $(LIBMX) $(PA) $(SF) $(OG) $(FC) $(VB) $(OP) 	\
		   -o $(NAME_SERVER) $(SQLITE) $(SSL) $(PTHREAD) $(ADD_FLAG)

obj:
	@mkdir obj

obj/%.o: src/%.c $(INC)
	@clang $(FLAGS) `pkg-config --cflags gtk+-3.0` -o $@ -c $<
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

obj/%.o: src/daemon_voice/%.c $(INC)
	@clang $(FLAGS) `pkg-config --cflags gtk+-3.0` -o $@ -c $<
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

obj/%.o: src/db/%.c $(INC)
	@clang $(FLAGS) `pkg-config --cflags gtk+-3.0` -o $@ -c $<
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

obj/%.o: src/help/%.c $(INC)
	@clang $(FLAGS) `pkg-config --cflags gtk+-3.0` -o $@ -c $<
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

obj/%.o: src/json_functions/%.c $(INC)
	@clang $(FLAGS) `pkg-config --cflags gtk+-3.0` -o $@ -c $<
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

obj/%.o: src/server/%.c $(INC)
	@clang $(FLAGS) `pkg-config --cflags gtk+-3.0` -o $@ -c $<
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

obj/%.o: src/client/%.c $(INC)
	@clang $(FLAGS) `pkg-config --cflags gtk+-3.0` -o $@ -c $<
	@printf "\x1b[32mcompiled: \x1b[0m[$<]\n"

obj/%.o: src/ssl/%.c $(INC)
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
	@rm -rf $(NAME_SERVER)
	@chmod 777 ./source/del_cash.sh
	@./source/del_cash.sh
	@rm -rf database.db
	@rm -rf database

reinstall: uninstall install

keys:
	@chmod 777 ./source/compiler_script.sh
	@./source/compiler_script.sh

db:
	@chmod 777 ./source/create_database.sh
	@./source/create_database.sh

del_cash:
	@chmod 777 ./source/del_cash.sh
	@./source/del_cash.sh

del_keys:
	@rm -rf ./source/keys

del_db:
	@rm -rf database.db
	@rm -rf database

d:
	@clang $(FLAGS) $(SANFLAG) $(SQLITE) $(SSL) $(PTHREAD) src/*.c libmx/libmx.a
