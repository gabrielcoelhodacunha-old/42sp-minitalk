NAME	= libft.a
CC	= cc
CFLAGS	= -Wall -Wextra -Werror
SRCP	= src
PART_1	= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
	  ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	  ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
	  ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
	  ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	  ft_atoi.c ft_calloc.c ft_strdup.c
PART_2	= ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
	  ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
	  ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	  ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	  ft_lstmap.c
PFP	= ft_printf
PFSRC	= ft_printf.c print_without_format.c print_formated.c get_flags.c \
	  print_char.c print_string.c print_hexadecimal.c ft_uitoa_base.c \
	  print_signed_decimal.c print_unsigned_decimal.c set_flags.c \
	  print_pointer.c handle_flags.c handle_alternate_form.c \
	  handle_width.c handle_precision.c handle_signed.c handle_blank.c
ICDP	= include
ICDS	= -I$(ICDP)
OBJP	= obj
OBJS	= $(PART_1:%.c=$(OBJP)/%.o) $(PART_2:%.c=$(OBJP)/%.o)
BOBJS	= $(BONUS:%.c=$(OBJP)/%.o)
PFOBJP	= $(OBJP)/$(PFP)
PFOBJS	= $(PFSRC:%.c=$(PFOBJP)/%.o)
AR	= ar -rcs
RM	= rm -fr
MKDIR	= mkdir -p
VPATH	= . $(SRCP) $(OBJP) $(PFP)

$(OBJP)/%.o:	%.c
		$(CC) $(CFLAGS) $(ICDS) -c $< -o $@

all:		$(NAME)

$(OBJP):
		$(MKDIR) $(OBJP)

$(NAME):	$(OBJP) $(OBJS)
		$(AR) $(NAME) $(OBJS)

bonus:		$(NAME) $(BOBJS)
		$(AR) $(NAME) $(BOBJS)

$(PFOBJP):
		$(MKDIR) $(PFOBJP)

printf:		$(NAME) $(PFOBJP) $(PFOBJS)
		$(AR) $(NAME) $(PFOBJS)

clean:
		$(RM) $(OBJP)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all bonus clean fclean re printf
