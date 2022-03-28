NAME		= minitalk
MAKE_IN_PATH	= $(MAKE) -sC
MAKE_LIBFT	= $(MAKE_IN_PATH) libft
LIBFT		= libft/libft.a
SERVER_SRC	= server.c
CLIENT_SRC	= client.c
SERVER_OBJECTS	= $(SERVER_SRC:%.c=obj/%.o)
CLIENT_OBJECTS	= $(CLIENT_SRC:%.c=obj/%.o)
INCLUDES	= -Iinclude -Ilibft/include
LIBRARIES	= -Llibft -lft
CC		= cc
CC_FLAGS	= -Wall -Wextra -Werror #-g3
MKDIR		= mkdir -p
RM		= rm -fr
VALGRIND	= valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes
VPATH		= . src obj

obj/%.o:	%.c
		$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

$(LIBFT):
		$(MAKE_LIBFT) printf

obj:
		$(MKDIR) obj

server:		$(LIBFT) obj $(SERVER_OBJECTS)
		$(CC) $(CC_FLAGS) -o server $(SERVER_OBJECTS) $(LIBRARIES)

client:		$(LIBFT) obj $(CLIENT_OBJECTS)
		$(CC) $(CC_FLAGS) -o client $(CLIENT_OBJECTS) $(LIBRARIES)

$(NAME):	server client

run_server:	server
		$(VALGRIND) ./server

run_client:	client
		$(VALGRIND) ./client $(PID) $(MESSAGE)

clean:
		$(MAKE_LIBFT) clean
		$(RM) obj

fclean:		clean
		$(RM) $(LIBFT) server client

re:		fclean all

.PHONY:	all clean fclean re
