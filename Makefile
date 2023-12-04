NAME := serveX

PREFIX_FOLDER   := $(shell pwd)
SERVER_PATH_PWD := $(shell pwd)
CONFIG_FILE     := $(addsuffix /cfg/sx_config.cfg,$(PREFIX_FOLDER))


SET_PREFIX := -D SERVER_PATH=\"$(SERVER_PATH_PWD)\" -D DEFAULT_CONF=\"$(CONFIG_FILE)\" 
CPPFLAGS   := -Wall -Wextra -Werror -std=c++17
DEBUG	   := -fsanitize=address -g 
CC 		   := c++

CORE_FILES 		:= serveX-core.cpp serveX-core.hpp sx_config.cpp sx_config.hpp sx_logger.cpp sx_logger.hpp sx_optioneer.cpp sx_optioneer.hpp

UTILITY_FILES 	:= sx_StringManipulation.cpp sx_filesManipulation.hpp sx_server_data.cpp sx_time.cpp \
            	   sx_StringManipulation.hpp sx_location_data.cpp sx_server_data.hpp sx_time.hpp \
                   sx_filesManipulation.cpp sx_location_data.hpp sx_templates_helper.hpp

HTTP_FILES		:= sx_HttpStatusMapping.cpp sx_client.cpp sx_redirective.cpp sx_response.cpp \
             	   sx_HttpStatusMapping.hpp sx_client.hpp sx_redirective.hpp sx_response.hpp \
             	   sx_cgi.cpp sx_headers.cpp sx_request.cpp sx_socket.cpp \
             	   sx_cgi.hpp sx_headers.hpp sx_request.hpp sx_socket.hpp \
             	   sx_cgiExtension.cpp sx_mimetype.cpp sx_requestBody.cpp \
             	   sx_cgiExtension.hpp sx_mimetype.hpp sx_requestBody.hpp

CORE_CPP_FILES     := $(filter %.cpp,$(CORE_FILES))
CORE_HPP_FILES 	   := $(filter %.hpp,$(CORE_FILES))
HTTP_CPP_FILES 	   := $(filter %.cpp,$(HTTP_FILES))
HTTP_HPP_FILES     := $(filter %.hpp,$(HTTP_FILES))
UTILITY_CPP_FILES  := $(filter %.cpp,$(UTILITY_FILES))
UTILITY_HPP_FILES  := $(filter %.hpp,$(UTILITY_FILES))

SRCS 	:= serveX-main.cpp\
		$(addprefix www/,$(HTTP_CPP_FILES))\
		$(addprefix core/, $(CORE_CPP_FILES))\
		$(addprefix utility/, $(UTILITY_CPP_FILES))

HEADERS = $(addprefix core/, $(CORE_HPP_FILES))\
	$(addprefix www/, $(HTTP_HPP_FILES))\
	$(addprefix  utility/, $(UTILITY_HPP_FILES))

OBJS 	:= $(SRCS:%.cpp=%.o)

INCLUDES := www core utility
INCLUDES := $(addprefix -I , $(INCLUDES))

COM_COLOR := \033[0;34m
OBJ_COLOR := \033[0;36m
OK_COLOR  := \033[0;32m
NO_COLOR  := \033[m

COM_STRING := "Compiling"

all : $(NAME)
	@clear; echo "Find config file cfg at : $(CONFIG_FILE)"
	@echo "$(OK_COLOR) [ServeX ✅] $(NO_COLOR)"


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