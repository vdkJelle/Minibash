# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/04 10:33:36 by jelvan-d      #+#    #+#                  #
#    Updated: 2021/06/28 15:03:40 by jelvan-d      ########   odam.nl          #
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
LIBRARIES	=	libft/libft.a\
				get_next_line/gnl.a

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
	@$(CC) $(FLAGS) $^ -o $(NAME)

$(LIBRARIES):
	@echo "   _                   ____    _____  _____" 
	@echo "  |\"|        ___    U | __\")u |\" ___||_ \" _|" 
	@echo "U | | u     |_\"_|    \\|  _ \\/U| |_  u  | |"   
	@echo " \\| |/__     | |      | |_) |\\|  _|/  /| |\\"  
	@echo "  |_____|  U/| |\\u    |____/  |_|    u |_|U"
	@echo "  //  \\\\\.-,_|___|_,-._|| \\\\\_  )(\\\\\,- _// \\\\\_"
	@echo " (_\")(\"_)\\_)-' '-(_/(__) (__)(__)(_/(__) (__)" 
	@$(MAKE) bonus -sC libft
	@echo "   ____  U _____ u  _____        _   _   U _____ u __  __    _____         _                  _   _   U _____ u"
	@echo "U /\"___|u\| ___\"|/ |_ \" _|      | \\ |\"|  \\| ___\"|/ \\ \\/\"/   |_ \" _|       |\"|        ___     | \\ |\"|  \\| ___\"|/"
	@echo "\\| |  _ / |  _|\"     | |       <|  \\| |>  |  _|\"   /\\  /\\     | |       U | | u     |_\"_|   <|  \\| |>  |  _|\""
	@echo " | |_| |  | |___    /| |\\      U| |\\  |u  | |___  U /  \\ u   /| |\\       \\| |/__     | |    U| |\\  |u  | |___"
	@echo "  \\____|  |_____|  u |_|U       |_| \\_|   |_____|  /_/\\_\\   u |_|U        |_____|  U/| |\\u   |_| \\_|   |_____|"  
	@echo "  _)(|_   <<   >>  _// \\\\\_      ||   \\\\\,-.<<   >>,-,>> \\\\\_  _// \\\\\_       //  \\\\\.-,_|___|_,-.||   \\\\\,-.<<   >>"
	@echo " (__)__) (__) (__)(__) (__)     (_\")  (_/(__) (__)\_)  (__)(__) (__)     (_\")(\"_)\_)-' '-(_/ (_\")  (_/(__) (__) "
	@$(MAKE) -sC get_next_line

obj/%.o: src/%.c
	@mkdir -p $(@D)
	@echo "Compiling... $^"
	@gcc $(FLAGS) -I $(INCLUDES) -c $^ -o $@

clean:
	@echo "Cleaning..."
	@rm -f $(OFILES) $(BOFILES)
	@make clean -sC get_next_line
	@make clean -sC libft

fclean: clean
	@echo "Extra cleaning..."
	@rm -f $(NAME)
	@make fclean -sC get_next_line
	@make fclean -sC libft

re: fclean all

.PHONY: all clean fclean re
