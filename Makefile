NAME = minishell
DEBUG = no

CFLAGS = -Wall -Wextra -Werror -I/usr/local/include
CRFLAGS = -L/usr/local/lib -lreadline
DFLAGS = -g3 -fsanitize=leak -fsanitize=address -fsanitize=pointer-subtract -fsanitize=pointer-compare -fsanitize=undefined

ifeq ($(DEBUG), yes)
CFLAGS += $(DFLAGS)
endif

DIR_SRC =	sources/

LST_SRC =	main.c							\
			utils/free.c					\
			utils/error.c					\
			utils/utils.c					\
			utils/signal.c					\
			utils/s_access.c 				\
			utils/split_var.c 				\
			builtin/cd.c					\
			builtin/unset.c					\
			builtin/echo.c					\
			builtin/exit.c					\
			builtin/export.c				\
			builtin/builtin.c				\
			builtin/cd_utils.c				\
			builtin/exit_redir.c			\
			builtin/builtin_utils.c			\
			builtin/export_append.c			\
			builtin/export_unset_utils.c	\
			env/env_lst.c					\
			env/env_init.c					\
			env/env_creat.c					\
			env/env_utils.c					\
			input/input_utils.c				\
			input/check_input.c 			\
			input/check_pipes.c				\
			input/check_chevrons.c			\
			input/check_chevrons_utils.c	\
			expands/expands.c				\
			expands/expands_trim.c			\
			expands/expands_utils.c			\
			parsing/create_chain.c			\
			parsing/parsing.c				\
			parsing/free_cmd.c 				\
			parsing/split_pipes.c			\
			parsing/split_tokens.c			\
			parsing/token_parsing.c			\
			parsing/parsing_utils.c			\
			parsing/space_chevrons.c		\
			parsing/token_parsing_utils.c	\
			process/child.c					\
			process/process.c				\
			process/here_doc.c				\
			process/redirection.c			\
			process/get_arg_path.c			\
			process/process_utils.c			\
			process/here_doc_utils.c		\
			process/get_redirection.c		\
			process/redirection_utils.c		\
			process/get_redirection_utils.c
			
SOURCES	=	$(addprefix $(DIR_SRC), $(LST_SRC))

DIR_OBJ	=	objects/
OBJECTS = 	$(patsubst $(DIR_SRC)%.c, $(DIR_OBJ)%.o, $(SOURCES))

HEADERS =	$(DIR_SRC)minishell.h

LIBRARY = 	$(DIR_SRC)libft/libft.a

#  ==============================  RULES  ==============================  #

all: lib 
	$(MAKE) $(NAME)

lib :
	@$(MAKE) -C $(DIR_SRC)libft

debug :
	@$(MAKE) re DEBUG=yes

clean:
	@rm -rf $(DIR_OBJ)
	@$(MAKE) -C $(DIR_SRC)libft clean

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -C $(DIR_SRC)libft fclean
	@printf "$(RED)$(NAME) fclean done!\n$(END)"

re: fclean
	@$(MAKE) all

.PHONY: all clean fclean re lib debug

#  ===========================  COMPILATION  ===========================  #

$(NAME): $(DIR_OBJ) $(OBJECTS)
	cc $(OBJECTS) $(CFLAGS) $(CRFLAGS) $(LIBRARY) -o $(NAME)

$(DIR_OBJ)	:
	@mkdir -p $(DIR_OBJ)
	@mkdir -p $(DIR_OBJ)/env
	@mkdir -p $(DIR_OBJ)/utils
	@mkdir -p $(DIR_OBJ)/builtin
	@mkdir -p $(DIR_OBJ)/input
	@mkdir -p $(DIR_OBJ)/parsing
	@mkdir -p $(DIR_OBJ)/expands
	@mkdir -p $(DIR_OBJ)/process

$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(HEADERS) $(LIBRARY)
	cc $(CFLAGS) -c $< -o $@

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
