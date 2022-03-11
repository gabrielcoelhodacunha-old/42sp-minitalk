NAME		= minitalk
LIBFT		= libft/libft.a
UTILS		= utils/libutils.a
SERVER		= server/server
CLIENT		= client/client
MAKE_IN_PATH	= $(MAKE) -C
MAKE_LIBFT	= $(MAKE_IN_PATH) libft
MAKE_UTILS	= #$(MAKE_IN_PATH) utils
MAKE_SERVER	= $(MAKE_IN_PATH) server
MAKE_CLIENT	= $(MAKE_IN_PATH) client
MAKE_SERVER_RUN	= $(MAKE_SERVER) run
MAKE_CLIENT_RUN	= $(MAKE_CLIENT) run

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
		$(MAKE_SERVER_RUN)

run_client:	$(CLIENT)
		$(MAKE_CLIENT_RUN) $(PID) $(MESSAGE)

bonus:		$(LIBFT) $(UTILS)
		$(MAKE_SERVER) bonus
		$(MAKE_CLIENT) bonus

run_server_bonus:	$(SERVER)
			$(MAKE_SERVER_RUN)_bonus

run_client_bonus:	$(CLIENT)
			$(MAKE_CLIENT_RUN)_bonus $(PID) $(MESSAGE)

clean:
		$(MAKE_LIBFT) clean
		#$(MAKE_UTILS) clean
		$(MAKE_SERVER) clean
		$(MAKE_CLIENT) clean

fclean:
		$(MAKE_LIBFT) fclean
		#$(MAKE_UTILS) fclean
		$(MAKE_SERVER) fclean
		$(MAKE_CLIENT) fclean

re:		fclean all

.PHONY:	all clean fclean re run_server run_client run_server_bonus run_client_bonus
