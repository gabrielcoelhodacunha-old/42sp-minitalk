NAME		= client
BONUS		= $(NAME)_bonus
CC		= cc
CC_FLAGS	= -Wall -Wextra -Werror -g3
SRC		= main.c
SRC_BONUS	= main_bonus.c
LIBFT_PATH	= ../libft
LIBFT_INCLUDE	= $(LIBFT_PATH)/include
UTILS_PATH	= ../utils
UTILS_INCLUDE	= $(UTILS_PATH)/include
INCLUDES	= -Iinclude -I$(LIBFT_INCLUDE) #-I$(UTILS_INCLUDE) 
OBJECTS		= $(SRC:%.c=obj/%.o)
OBJECTS_BONUS	= $(SRC_BONUS:%.c=obj/%.o)
LIBRARIES	= -L$(LIBFT_PATH) -lft #-L$(UTILS_PATH) -lutil
MKDIR		= mkdir -p
RM		= rm -fr
VPATH		= . src obj bonus

obj/%.o:	%.c
		$(CC) $(CC_FLAGS) $(INCLUDES) -c $< -o $@

all:		$(NAME)

obj:
		$(MKDIR) obj

$(NAME):	obj $(OBJECTS)
		$(CC) $(CC_FLAGS) -o $(NAME) $(OBJECTS) $(LIBRARIES)

bonus:		$(BONUS)

$(BONUS):	obj $(OBJECTS_BONUS)
		$(CC) $(CC_FLAGS) -o $(BONUS) $(OBJECTS_BONUS) $(LIBRARIES)

clean:
		$(RM) obj

fclean:		clean
		$(RM) $(NAME)
		$(RM) $(BONUS)

re:		fclean all

.PHONY:	all clean fclean re bonus
