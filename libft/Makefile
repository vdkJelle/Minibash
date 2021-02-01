# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jelvan-d <jelvan-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/31 09:58:25 by jelvan-d          #+#    #+#              #
#    Updated: 2019/11/16 16:32:23 by jelvan-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
SRCS		=	ft_atoi\
				ft_bzero\
				ft_calloc\
				ft_isalnum\
				ft_isalpha\
				ft_isascii\
				ft_isdigit\
				ft_isprint\
				ft_itoa\
				ft_memccpy\
				ft_memchr\
				ft_memcmp\
				ft_memcpy\
				ft_memmove\
				ft_memset\
				ft_putchar_fd\
				ft_putendl_fd\
				ft_putnbr_fd\
				ft_putstr_fd\
				ft_split\
				ft_strchr\
				ft_strdup\
				ft_strjoin\
				ft_strlcpy\
				ft_strlcat\
				ft_strlen\
				ft_strmapi\
				ft_strncmp\
				ft_strnstr\
				ft_strrchr\
				ft_strtrim\
				ft_substr\
				ft_tolower\
				ft_toupper
BONUS_SRCS	=	ft_lstadd_back_bonus\
				ft_lstadd_front_bonus\
				ft_lstclear_bonus\
				ft_lstdelone_bonus\
				ft_lstiter_bonus\
				ft_lstlast_bonus\
				ft_lstmap_bonus\
				ft_lstnew_bonus\
				ft_lstsize_bonus
CFILES		=	$(SRCS:%=%.c)
BCFILES		=	$(BONUS_SRCS:%=%.c)
OFILES		=	$(CFILES:.c=.o)
BOFILES		=	$(BCFILES:.c=.o)
INCLUDES	=	.
FLAGS		=	-Wall -Werror -Wextra

all:	$(NAME)

$(NAME):	$(OFILES)
	@ar rc $(NAME) $(OFILES)
	@echo "Library exluding bonus"

%.o:	%.c
	@echo "Compiling... $^"
	@gcc $(FLAGS) -I $(INCLUDES) -c $^

clean:
	@echo "Cleaning..."
	@rm -f $(OFILES) $(BOFILES)

fclean:		clean
	@echo "Extra cleaning..."
	@rm -f $(NAME)

re:			fclean all

bonus:		$(OFILES) $(BOFILES)
	@echo "Library including bonus"
	@ar rc $(NAME) $^
	@ranlib $(NAME)
