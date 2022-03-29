NAME			= minitalk
SERVER			= ./server
CLIENT			= ./client
SERVER_SRC		= server.c
CLIENT_SRC		= client.c
SERVER_OBJECTS		= $(SERVER_SRC:%.c=obj/%.o)
CLIENT_OBJECTS		= $(CLIENT_SRC:%.c=obj/%.o)
INCLUDES		= -Iinclude -Ilibft/include
BONUS_SERVER		= $(SERVER)_bonus
BONUS_CLIENT		= $(CLIENT)_bonus
BONUS_SERVER_SRC	= server_bonus.c
BONUS_CLIENT_SRC	= client_bonus.c
BONUS_SERVER_OBJECTS	= $(BONUS_SERVER_SRC:%.c=bonus_obj/%.o)
BONUS_CLIENT_OBJECTS	= $(BONUS_CLIENT_SRC:%.c=bonus_obj/%.o)
BONUS_INCLUDES		= -Ibonus_include -Ilibft/include
MAKE_IN_PATH		= $(MAKE) -sC
MAKE_LIBFT		= $(MAKE_IN_PATH) libft
LIBFT			= libft/libft.a
LIBRARIES		= -Llibft -lft
CC			= cc
CC_FLAGS		= -Wall -Wextra -Werror
MKDIR			= mkdir -p
RM			= rm -fr
VALGRIND		= valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes
VPATH			= . src obj bonus_src bonus_obj

all:			$(NAME)

$(NAME):		$(SERVER) $(CLIENT)

clean:
			$(MAKE_LIBFT) clean
			$(RM) obj
			$(RM) bonus_obj

fclean:			clean
			$(RM) $(LIBFT)
			$(RM) $(SERVER) $(CLIENT)
			$(RM) $(BONUS_SERVER) $(BONUS_CLIENT)

re:			fclean all

bonus:			$(BONUS_SERVER) $(BONUS_CLIENT)

$(SERVER):		$(LIBFT) obj $(SERVER_OBJECTS)
			$(CC) $(CC_FLAGS) -o $(SERVER) $(SERVER_OBJECTS) $(LIBRARIES)

$(CLIENT):		$(LIBFT) obj $(CLIENT_OBJECTS)
			$(CC) $(CC_FLAGS) -o $(CLIENT) $(CLIENT_OBJECTS) $(LIBRARIES)

obj:
			$(MKDIR) obj

obj/%.o:		%.c
			$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

run_server:		$(SERVER)
			$(VALGRIND) $(SERVER)

run_client:		$(CLIENT)
			$(VALGRIND) $(CLIENT) $(PID) $(MESSAGE)

$(BONUS_SERVER):	$(LIBFT) bonus_obj $(BONUS_SERVER_OBJECTS)
			$(CC) $(CC_FLAGS) -o $(BONUS_SERVER) $(BONUS_SERVER_OBJECTS) $(LIBRARIES)

$(BONUS_CLIENT):	$(LIBFT) bonus_obj $(BONUS_CLIENT_OBJECTS)
			$(CC) $(CC_FLAGS) -o $(BONUS_CLIENT) $(BONUS_CLIENT_OBJECTS) $(LIBRARIES)

bonus_obj:
			$(MKDIR) bonus_obj

bonus_obj/%.o:		%.c
			$(CC) $(CC_FLAGS) $(BONUS_INCLUDES) -c $< -o $@

run_server_bonus:	$(BONUS_SERVER)
			$(VALGRIND) $(BONUS_SERVER)

run_client_bonus:	$(BONUS_CLIENT)
			$(VALGRIND) $(BONUS_CLIENT) $(PID) $(MESSAGE)

$(LIBFT):
			$(MAKE_LIBFT) printf

.PHONY:	all clean fclean re bonus
