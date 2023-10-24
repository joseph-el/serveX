NAME := webserv

PREFIX_FOLDER   := $(shell pwd)
SERVER_PATH_PWD := $(shell pwd)
CONFIG_FILE     := $(addsuffix /cfg/config.cfg,$(PREFIX_FOLDER))

SET_PREFIX := -D SERVER_PATH=\"$(SERVER_PATH_PWD)\" -D DEFAULT_CONF=\"$(CONFIG_FILE)\" 
CPPFLAGS   := -Wall -Wextra -Werror -std=c++98 
CC 		   := c++

HTTP_FILES    := HttpStatusMapping.cpp cgi.hpp headers.cpp mimeTypes.hpp request.cpp requestBody.hpp socket.cpp \
              	 HttpStatusMapping.hpp client.cpp headers.hpp cgi_extension.hpp redirective.cpp request.hpp response.cpp socket.hpp \
              	 cgi.cpp client.hpp mimeTypes.cpp redirective.hpp requestBody.cpp response.hpp cgi_extension.cpp

UTILITY_FILES  := StringManipulation.cpp filesManipulation.cpp location_data.cpp server_data.cpp time.cpp \
                  StringManipulation.hpp filesManipulation.hpp location_data.hpp server_data.hpp time.hpp templates_helper.hpp

CORE_FILES     := config.cpp config.hpp optioneer.cpp optioneer.hpp server-core.cpp server-core.hpp logger.cpp logger.hpp


CORE_CPP_FILES     := $(filter %.cpp,$(CORE_FILES))
CORE_HPP_FILES 	   := $(filter %.hpp,$(CORE_FILES))
HTTP_CPP_FILES 	   := $(filter %.cpp,$(HTTP_FILES))
HTTP_HPP_FILES     := $(filter %.hpp,$(HTTP_FILES))
UTILITY_CPP_FILES  := $(filter %.cpp,$(UTILITY_FILES))
UTILITY_HPP_FILES  := $(filter %.hpp,$(UTILITY_FILES))


SRCS 	:= Webserv-core.cpp\
		$(addprefix www/,$(HTTP_CPP_FILES))\
		$(addprefix core/, $(CORE_CPP_FILES))\
		$(addprefix utility/, $(UTILITY_CPP_FILES))

SRCS    := $(addprefix source/, $(SRCS))

HEADERS = $(addprefix core/, $(CORE_HPP_FILES))\
	$(addprefix www/, $(HTTP_HPP_FILES))\
	$(addprefix  utility/, $(UTILITY_HPP_FILES))


HEADERS := $(HEADERS:%=source/%)

OBJS 	:= $(SRCS:%.cpp=%.o)

INCLUDES := www core utility
INCLUDES := $(addprefix -I source/, $(INCLUDES))


COM_COLOR := \033[0;34m
OBJ_COLOR := \033[0;36m
OK_COLOR  := \033[0;32m
NO_COLOR  := \033[m

COM_STRING := "Compiling"

all : $(NAME)
	reset && echo "Find config file cfg at : $(CONFIG_FILE)"
	@echo "$(OK_COLOR) [Webserv ✅] $(NO_COLOR)"


$(NAME) : $(OBJS)
		@echo "$(OK_COLOR) [OBJS ✅] $(NO_COLOR)"
		@$(CC) $^ -o $@ 

%.o: %.cpp $(HEADERS)
	@printf "%-100.900b\r" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@)$(NO_COLOR)\n";
	@$(CC) $(CPPFLAGS) $(SET_PREFIX) $(INCLUDES) -c $< -o $@

clean :
	@echo "$(OK_COLOR) [clean 🧹] $(NO_COLOR)"
	@rm -f $(OBJS)
fclean : clean
	@rm -f $(NAME)

re : fclean all