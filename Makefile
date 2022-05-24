# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/04 10:33:36 by jelvan-d      #+#    #+#                  #
#    Updated: 2022/05/23 21:23:28 by tevan-de      ########   odam.nl          #
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
CFILES		=	$(SRCS:%=src/%.c)
OFILES		=	$(SRCS:%=obj/%.o)
INCLUDES	=	./includes/.
FLAGS		=	-Wall -Wextra -Werror
ifdef DEBUG
FLAGS += -g -fsanitize=address
endif
LIBRARIES	=	libft/libft.a

all:	announce $(NAME)

announce:
	@echo '  __  __              _   _                ____     _   _  U _____ u  _       _'
	@echo 'U|" \/ "|u   ___     | \ |"|       ___    / __"| u |"| |"| \| ___"|/ |"|     |"|'
	@echo '\| |\/| |/  |_"_|   <|  \| |>     |_"_|  <\___ \/ /| |_| |\ |  _|" U | | u U | | u   '
	@echo ' | |  | |    | |    U| |\  |u      | |    u___) | U|  _  |u | |___  \| |/__ \| |/__  '
	@echo ' |_|  |_|  U/| |\u   |_| \_|     U/| |\u  |____/>> |_| |_|  |_____|  |_____| |_____| '
	@echo '<<,-,,-..-,_|___|_,-.||   \\,-.-,_|___|_,-.)(  (__)//   \\  <<   >>  //  \\  //  \\  '
	@echo ' (./  \.)\_)-" "-(_/ (_")  (_/ \_)-" "-(_/(__)    (_") ("_)(__) (__)(_")("_)(_")("_) '

$(NAME): $(OFILES) $(LIBRARIES)
	@$(CC) $(FLAGS) $^ -o $(NAME) -lreadline

$(LIBRARIES):
	@echo "   _                   ____    _____  _____" 
	@echo "  |\"|        ___    U | __\")u |\" ___||_ \" _|" 
	@echo "U | | u     |_\"_|    \\|  _ \\/U| |_  u  | |"   
	@echo " \\| |/__     | |      | |_) |\\|  _|/  /| |\\"  
	@echo "  |_____|  U/| |\\u    |____/  |_|    u |_|U"
	@echo "  //  \\\\\.-,_|___|_,-._|| \\\\\_  )(\\\\\,- _// \\\\\_"
	@echo " (_\")(\"_)\\_)-' '-(_/(__) (__)(__)(_/(__) (__)" 
	@$(MAKE) bonus -sC libft

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "Compiling... $^"
	@gcc $(FLAGS) -I $(INCLUDES) -c $^ -o $@

clean:
	@echo "Cleaning..."
	@rm -f $(OFILES) $(BOFILES)
	@make clean -sC libft

fclean: clean
	@echo "Extra cleaning..."
	@rm -f $(NAME)
	@make fclean -sC libft

re: fclean all

.PHONY: all clean fclean re
