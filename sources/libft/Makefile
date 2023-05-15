NAME = libft.a
AR = ar
ARFLAGS = rsc
CC = cc
CFLAGS = -Wall -Wextra -Werror -I .

DIR_SRC =	sources/
LST_SRC =	ft_isalpha.c			\
			ft_isdigit.c 			\
			ft_isalnum.c			\
			ft_isascii.c			\
			ft_isprint.c			\
			ft_strlen.c				\
			ft_memset.c				\
			ft_bzero.c				\
			ft_memcpy.c				\
			ft_memmove.c			\
			ft_strlcpy.c			\
			ft_strlcat.c			\
			ft_toupper.c			\
			ft_tolower.c			\
			ft_strchr.c				\
			ft_strrchr.c			\
			ft_strncmp.c			\
			ft_memchr.c				\
			ft_memcmp.c				\
			ft_strnstr.c			\
			ft_atoi.c				\
			ft_calloc.c				\
			ft_strdup.c				\
			ft_substr.c				\
			ft_strjoin.c			\
			ft_strtrim.c			\
			ft_split.c				\
			ft_itoa.c				\
			ft_strmapi.c			\
			ft_striteri.c			\
			ft_putchar_fd.c			\
			ft_putstr_fd.c			\
			ft_putendl_fd.c			\
			ft_putnbr_fd.c			\
			ft_lstnew.c				\
			ft_lstadd_front.c		\
			ft_lstsize.c			\
			ft_lstlast.c			\
			ft_lstadd_back.c		\
			ft_lstdelone.c			\
			ft_lstclear.c			\
			ft_lstiter.c			\
			ft_printf.c				\
			ft_dprintf.c			\
			ft_putchar.c			\
			ft_putstr.c				\
			ft_putnbr_base.c		\
			ft_putnbr_base_fd.c		\
			ft_print_address.c		\
			ft_dprint_address.c		\
			get_next_line.c			\
			get_next_line_utils.c
SOURCES	=	$(addprefix $(DIR_SRC), $(LST_SRC))

DIR_OBJ	=	objects/
OBJECTS = 	$(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)%.o, $(SOURCES))

HEADERS =	$(DIR_SRC)libft.h

#  ===========================  COMPILATION  ===========================  #

$(NAME): $(DIR_OBJ) $(OBJECTS)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJECTS)
	@printf "$(GREEN)\nlibft created !\n$(END)"

$(DIR_OBJ)	:
	@mkdir -p $(DIR_OBJ)

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "$(RERASE)$(YELLOW)Making $(NAME) ...$(END)"

#  ==============================  RULES  ==============================  #

all: $(NAME)

clean:
	@rm -rf $(DIR_OBJ)

fclean: clean
	@rm -rf $(NAME)
	@printf "$(RED)$(NAME) fclean done!\n$(END)"

re: fclean all

.PHONY: all clean fclean re

#  =============================  OPTIONS  =============================  #

ERASE		= 	\033[2K
RERASE		= 	\r\033[2K
BLACK		=	\033[0;30m
RED			=	\033[0;31m
GREEN		=	\033[0;32m
ORANGE		=	\033[0;33m
BLUE		=	\033[0;34m
PURPLE		=	\033[0;35m
CYAN		=	\033[0;36m
GRAY_LIGHT	=	\033[0;37m
GRAY_DARK	=	\033[1;30m
RED_LIGHT	=	\033[1;31m
GREEN_LIGHT	=	\033[1;32m
YELLOW 		=	\033[1;33m
BLUE_LIGHT	=	\033[1;34m
VIOLET		=	\033[1;35m
CYAN		=	\033[1;36m
WHITE		=	\033[1;37m
END			=	\033[0m