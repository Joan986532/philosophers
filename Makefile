# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jnauroy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/12 16:49:14 by jnauroy           #+#    #+#              #
#    Updated: 2025/03/31 10:26:58 by jnauroy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRC_DIR = sources
HEAD_DIR = headers

NAME = philo

SOURCES = $(SRC_DIR)/philo.c

LIBFT = libft_philo/libft.a

OBJECTS = $(SOURCES.c=.o)

CFLAGS = -g -Wall -Wextra -Werror

#------------------------------------------------------------------------------#

all: $(NAME)

$(NAME): $(OBJECTS)
	$(MAKE) -C libft_philo
	cc $(OBJECTS) $(CFLAGS) -o $(NAME)

clean:
	rm -f $(OBJECTS)
fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
