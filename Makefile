NAME		= minitalk
SERVER		= server
CLIENT		= client
MAKE_IN_PATH	= $(MAKE) -C
MAKE_LIBFT	= $(MAKE_IN_PATH) libft
LIBFT		= libft/libft.a
SERVER_SRC	= server.c
CLIENT_SRC	= client.c
SERVER_OBJECTS	= $(SERVER_SRC:%.c=obj/%.o)
CLIENT_OBJECTS	= $(CLIENT_SRC:%.c=obj/%.o)
INCLUDES	= -Iinclude -Ilibft/include
LIBRARIES	= -Llibft -lft
CC		= cc
CC_FLAGS	= -Wall -Wextra -Werror -g3
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

$(SERVER):	obj $(SERVER_OBJECTS)
		$(CC) $(CC_FLAGS) -o $(SERVER) $(SERVER_OBJECTS) $(LIBRARIES)

$(CLIENT):	obj $(CLIENT_OBJECTS)
		$(CC) $(CC_FLAGS) -o $(CLIENT) $(CLIENT_OBJECTS) $(LIBRARIES)

$(NAME):	$(LIBFT) $(SERVER) $(CLIENT)

run_server:	$(SERVER)
		$(VALGRIND) $(SERVER)

run_client:	$(CLIENT)
		$(VALGRIND) $(CLIENT) $(PID) $(MESSAGE)

clean:
		$(MAKE_LIBFT) clean
		$(RM) obj

fclean:		clean
		$(MAKE_LIBFT) fclean
		$(RM) $(SERVER) $(CLIENT)

re:		fclean all

.PHONY:	all clean fclean re run_server run_client
