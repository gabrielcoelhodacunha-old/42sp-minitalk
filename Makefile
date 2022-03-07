NAME		= minitalk
LIBFT		= libft/libft.a
UTILS		= utils/libutils.a
SERVER		= server/server
CLIENT		= client/client
MAKE_IN_PATH	= $(MAKE) -C
MAKE_LIBFT	= $(MAKE_IN_PATH) libft
MAKE_UTILS	= $(MAKE_IN_PATH) utils
MAKE_SERVER	= $(MAKE_IN_PATH) server
MAKE_CLIENT	= $(MAKE_IN_PATH) client
VALGRIND	= valgrind -q --leak-check=full --show-leak-kinds=all --track-origin=yes

all:		$(NAME)

$(LIBFT):
		$(MAKE_LIBFT) printf

$(UTILS):
		$(MAKE_UTILS)

$(SERVER):
		$(MAKE_SERVER)

$(CLIENT):
		$(MAKE_CLIENT)

$(NAME):	$(LIBFT) $(UTILS) $(SERVER) $(CLIENT)

run_server:	$(SERVER)
		$(VALGRIND) $(SERVER)

run_client:	$(CLIENT)
		$(VALGRIND) $(CLIENT) $(PID) $(MESSAGE)

bonus:		$(LIBFT) $(UTILS)
		$(MAKE_SERVER) bonus
		$(MAKE_CLIENT) bonus

run_server_bonus:	$(SERVER)
			$(VALGRIND) $(SERVER)_bonus

run_client_bonus:	$(CLIENT)
			$(VALGRIND) $(CLIENT)_bonus $(PID) $(MESSAGE)

clean:
		$(MAKE_LIBFT) clean
		$(MAKE_UTILS) clean
		$(MAKE_SERVER) clean
		$(MAKE_CLIENT) clean

fclean:
		$(MAKE_LIBFT) fclean
		$(MAKE_UTILS) fclean
		$(MAKE_SERVER) fclean
		$(MAKE_CLIENT) fclean

re:		clean all

.PHONY:	all clean fclean re run_server run_client run_server_bonus run_client_bonus
