# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/04 10:33:36 by jelvan-d      #+#    #+#                  #
#    Updated: 2021/02/28 12:19:04 by tevan-de      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	cd\
				count_quotes\
				echo\
				executable\
				get_env\
				main\
				pwd\
				utils_list\
				utils_string1\
				utils_string2\
				utils_string_whitespaces\
				token
CFILES		=	$(SRCS:%=%.c)
OFILES		=	$(CFILES:.c=.o)
INCLUDES	=	.
FLAGS		=	-Wall -Wextra -Werror -g -fsanitize=address
LIBRARIES	=	libft/libft.a\
				get_next_line/gnl.a

all:	$(NAME)

$(NAME): $(OFILES) $(LIBRARIES)
	@gcc $(FLAGS) $^ -o $(NAME)

$(LIBRARIES):
	@echo "Compiling libft"
	@make bonus -C libft
	@echo "Compiling get_next_line"
	@make -C get_next_line

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
