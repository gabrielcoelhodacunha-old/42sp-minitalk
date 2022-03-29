NAME		= minitalk
SERVER		= ./server
CLIENT		= ./client
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

all:		$(NAME)

$(NAME):	$(SERVER) $(CLIENT)

clean:
		$(MAKE_LIBFT) clean
		$(RM) obj

fclean:		clean
		$(RM) $(LIBFT) $(SERVER) $(CLIENT)

re:		fclean all

$(SERVER):	$(LIBFT) obj $(SERVER_OBJECTS)
		$(CC) $(CC_FLAGS) -o $(SERVER) $(SERVER_OBJECTS) $(LIBRARIES)

$(CLIENT):	$(LIBFT) obj $(CLIENT_OBJECTS)
		$(CC) $(CC_FLAGS) -o $(CLIENT) $(CLIENT_OBJECTS) $(LIBRARIES)

$(LIBFT):
		$(MAKE_LIBFT) printf

obj:
		$(MKDIR) obj

obj/%.o:	%.c
		$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

run_server:	$(SERVER)
		$(VALGRIND) $(SERVER)

run_client:	$(CLIENT)
		$(VALGRIND) $(CLIENT) $(PID) $(MESSAGE)

.PHONY:	all clean fclean re
