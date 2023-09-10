#Output Program Name
NAME = parsingConfig

# Colors :
GREEN = \033[0;32m
YELLOW = \033[0;33m
RED= \033[0;31m
BLUE = \033[0;34m
STOP = \033[0m

# Commands And Flags :
CPP = c++
FLAGS =	-Wall -Wextra -Werror -std=c++98
RM = rm -rf

# loading source files :
CONFFILEPARSERS = ./srcs/ParseConfigFile/ConfigFileParser.cpp \
				  ./srcs/ParseConfigFile/ServerConfig.cpp \
				  ./srcs/ParseConfigFile/LocationConfig.cpp

SRCS = main.cpp $(CONFFILEPARSERS)

all : $(NAME)
	@echo "You Can Use $(GREEN)*** $(NAME) ***$(STOP)"

$(NAME) : $(SRCS)
	@$(CPP) $(FLAGS) $(SRCS) -o $(NAME)
	@echo "$(BLUE)Compiling the source files... $(STOP)"

clean :
	@echo "$(YELLOW)Cleaning... $(STOP)"

fclean : clean
	@$(RM) $(NAME)
	@echo "$(RED)Deleting The $(NAME) ... $(STOP)"

re : fclean all