# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/26 12:04:08 by jelvan-d      #+#    #+#                  #
#    Updated: 2020/07/08 17:20:51 by jelvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME			=	gnl

SRCS 			= 	get_next_line\
					get_next_line_utils

CFILES			=	$(SRCS:%=%.c)
OFILES			=	$(CFILES:.c=.o)
INCLUDES		=	.
FLAGS			=	-Wall -Wextra -Werror

all:	$(NAME)

$(NAME):	$(OFILES)
	@ar rc $(NAME).a $(OFILES)
	@echo "Your gnl library is ready!"

%.o:	%.c
	@echo "Compiling..." $^
	@gcc -o $@ $(FLAGS) -I $(INCLUDES) -c $^

clean:
	@echo "Cleaning..."
	@rm -f $(OFILES)

fclean:		clean
	@echo "Extra cleaning..."
	@rm -f $(NAME).a

re:		fclean all
