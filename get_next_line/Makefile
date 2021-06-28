# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2019/11/26 12:04:08 by jelvan-d      #+#    #+#                  #
#    Updated: 2021/06/28 13:04:25 by jelvan-d      ########   odam.nl          #
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

%.o:	%.c
	@echo "Compiling..." $^
	@gcc -o $@ $(FLAGS) -I $(INCLUDES) -c $^

clean:
	@rm -f $(OFILES)

fclean:		clean
	@rm -f $(NAME).a

re:		fclean all
