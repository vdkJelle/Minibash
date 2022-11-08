# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 11:16:05 by jelvan-d      #+#    #+#                  #
#    Updated: 2022/11/08 15:39:37 by jelvan-d      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
CC			=	gcc
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
ifdef DEBUG
FLAGS += -g -fsanitize=address
endif

all:	$(NAME)

$(NAME):	$(OFILES)
	@ar rc $(NAME) $(OFILES)

%.o:	%.c
	@echo "Compiling... $^"
	@gcc $(FLAGS) -I $(INCLUDES) -c $^

clean:
	@rm -f $(OFILES) $(BOFILES)

fclean:		clean
	@rm -f $(NAME)

re:			fclean all

bonus:		$(OFILES) $(BOFILES)
	@ar rc $(NAME) $^
	@ranlib $(NAME)
