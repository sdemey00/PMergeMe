# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdemey <sdemey@student.s19.be>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/26 10:37:33 by sdemey            #+#    #+#              #
#    Updated: 2026/01/17 16:08:50 by sdemey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= PmergeMe

CC		= c++
FLAGS	= -Wall -Wextra -Werror -std=c++98

BLDD	= build

SRCS	=	main.cpp \
			PmergeMe.cpp
OBJS	= $(patsubst %.cpp, $(BLDD)/%.o, $(SRCS))
INCS	= -I .
DEPS	= $(OBJS:.o=.d)

.PHONY: clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $@

$(BLDD)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(FLAGS) $(INCS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(BLDD)

fclean: clean
	rm -rf $(NAME)

re: fclean all
