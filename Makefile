# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/04 10:33:36 by jelvan-d      #+#    #+#                  #
#    Updated: 2021/03/10 16:07:39 by jelvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	cd\
				count_quotes\
				echo\
				env\
				executable\
				export\
				exit\
				get_env\
				main\
				pwd\
				utils_export\
				utils_list\
				utils_string1\
				utils_string2\
				utils_string3\
				utils_string_strjoin\
				utils_string_whitespaces\
				unset\
				token
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
	@gcc $(FLAGS) $^ -o $(NAME)

$(LIBRARIES):
	@echo "Compiling libft"
	@$(MAKE) bonus -C libft
	@echo "Compiling get_next_line"
	@$(MAKE) -C get_next_line

%.o:	%.c
	@echo "Compiling... $^"
	@gcc $(FLAGS) -I $(INCLUDES) -c $^

clean:
	@echo "Cleaning..."
	@rm -f $(OFILES) $(BOFILES)
	@make clean -C get_next_line
	@make clean -C libft

fclean:		clean
	@echo "Extra cleaning..."
	@rm -f $(NAME)
	@make fclean -C get_next_line
	@make fclean -C libft

re:			fclean all

.PHONY: all clean fclean re
