# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/04 10:33:36 by jelvan-d      #+#    #+#                  #
#    Updated: 2021/05/18 18:28:49 by tevan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	cd\
				check_file\
				check_multiline_command\
				echo\
				env\
				execute\
				execute_builtin\
				export\
				exit\
				final_args\
				get_env\
				main\
				processes\
				pwd\
				redirection\
				signals\
				utils_error\
				utils_free\
				utils_list\
				utils_string_count\
				utils_string_isthis\
				utils_string_skip\
				utils_string\
				unset\
				token\
				token_arg\
				token_check\
				token_handle_arg_chars
CFILES		=	$(SRCS:%=%.c)
OFILES		=	$(CFILES:.c=.o)
INCLUDES	=	.
FLAGS		=	-Wall -Wextra -Werror
ifdef DEBUG
FLAGS += -g -fsanitize=address
endif
LIBRARIES	=	libft/libft.a\
				get_next_line/gnl.a

all:	$(NAME)

$(NAME): $(OFILES) $(LIBRARIES)
	@$(CC) $(FLAGS) $^ -o $(NAME)

$(LIBRARIES):
	@echo "Compiling libft"
	@$(MAKE) bonus -C libft
	@echo "Compiling get_next_line"
	@$(MAKE) -C get_next_line

%.o: %.c
	@echo "Compiling... $^"
	@gcc $(FLAGS) -I $(INCLUDES) -c $^

clean:
	@echo "Cleaning..."
	@rm -f $(OFILES) $(BOFILES)
	@make clean -C get_next_line
	@make clean -C libft

fclean: clean
	@echo "Extra cleaning..."
	@rm -f $(NAME)
	@make fclean -C get_next_line
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
