# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trobicho <trobicho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/16 22:25:09 by trobicho          #+#    #+#              #
#    Updated: 2021/10/20 10:10:35 by trobicho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = g++
CXXFLAGS	=	-std=c++14 -g

NAME = new_vulkan

INCLUDE_PATH = /home/tom/projects/lib
SRCS_PATH	=	./
HDRS_PATH	=	./
OBJS_PATH	=	./obj

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	INCS_FLAGS	= -I$(VULKAN_SDK)/include \
		-I$(GLFW3_PATH)/include \
		-I $(INCLUDE_PATH)
	LDFLAGS = -L$(VULKAN_SDK)/lib `pkg-config --static --libs glfw3` -lvulkan -lm
else
	LDFLAGS = -L$(GLFW3_PATH)/lib -L$(VULKAN_SDK)/lib `pkg-config --static --libs glm` -lvulkan -lglfw -lm
endif


SRCS_NAME =	main.cpp \
		Basic_vulk.cpp \
		validation_layer.cpp \
		device_phy.cpp \
		queue.cpp \
		swapchain.cpp \
		info.cpp

HDRS_NAME =	Basic_vulk.hpp \

OBJS_NAME	=	$(SRCS_NAME:.cpp=.o) $(SRCS_UI_NAME:.cpp=.o) 

SRCS = $(addprefix $(SRCS_PATH)/, $(SRCS_NAME))
HDRS = $(addprefix $(HDRS_PATH)/, $(HDRS_NAME))
OBJS = $(addprefix $(OBJS_PATH)/, $(OBJS_NAME))

all: $(NAME)

$(NAME): $(SRCS) $(HDRS) $(OBJS) Makefile
	$(CC) $(CXXFLAGS) $(INCS_FLAGS) $(SRCS) $(LDFLAGS) -o $(NAME)

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.cpp $(HDRS) Makefile
	@mkdir $(OBJS_PATH) 2> /dev/null || true
	@echo "\033[38;2;0;255;0m[cc]\033[0m: $< -> $@"
	@printf "\e[1A"
	@$(CC) $(CXXFLAGS) -I $(HDRS_PATH) $(INCS_FLAGS) -c $< -o $@
	@printf "\e[0K"

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
