NAME		= server
CC		= cc
CC_FLAGS	= -Wall -Wextra -Werror -g3
SRC		= main.c
LIBFT_PATH	= ../libft
LIBFT_INCLUDE	= $(LIBFT_PATH)/include
UTILS_PATH	= ../utils
UTILS_INCLUDE	= $(UTILS_PATH)/include
INCLUDES	= -Iinclude -I$(UTILS_INCLUDE) -I$(LIBFT_INCLUDE)
OBJECTS		= $(src:%.c=obj/%.o)
LIBRARIES	= -L$(LIBFT_PATH) -lft -L$(UTILS_PATH) -lutil
MKDIR		= mkdir -p
RM		= rm -fr
VPATH		= src obj $(LIBFT_PATH) $(UTILS_PATH)

obj/%.o:	%.c
		$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

obj:
		$(MKDIR) obj

$(NAME):	obj $(OBJECTS)
		$(CC) -o $(NAME) $(OBJECTS) $(LIBRARIES)

clean:
		$(RM) obj

fclean:		clean
		$(RM) $(NAME)

re:		clean all

.PHONY:	all clean fclean re
