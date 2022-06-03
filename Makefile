# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: jelvan-d <jelvan-d@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/04 10:33:36 by jelvan-d      #+#    #+#                  #
#    Updated: 2022/06/03 13:25:43 by tessa         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRCS		=	builtins/cd\
				builtins/echo\
				builtins/env\
				builtins/exit\
				builtins/export\
				builtins/pwd\
				builtins/unset\
				check_file_information\
				check_multiline_command\
				execute\
				execute_builtin\
				final_args\
				get_env\
				main\
				parser_arg\
				parser_check\
				parser_handle_args\
				parser\
				processes\
				redirection\
				signals\
				tokenizer\
				utils/free\
				utils/list\
				utils/malloc_wrapper\
				utils/print_error\
				utils/string\
				utils/string_count\
				utils/string_isthis\
				utils/string_skip_characters
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
