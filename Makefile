# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jleblond <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/01 09:47:50 by jleblond          #+#    #+#              #
#    Updated: 2019/03/01 10:00:49 by jleblond         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = fractol

SOURCE = main.c window.c events.c fractals.c tools.c

OFILE = $(SOURCE:.c=.o)

HEADER = fractol.h

LIBFTA = libft/libft.a

INC = -I ./libft -I minilibx_macos

all:$(NAME)

$(NAME): $(OFILE)
	$(CC) $(CFLAGS) $(OFILE) $(LIBFTA) $(INC) -L minilibx_macos  -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c $(HEADER) $(LIBFTA)
	$(CC) $(CFLAGS) -c $(SOURCE) $(INC)

$(LIBFTA): FORCE
	make -C ./libft

FORCE:

clean:
	rm -f $(OFILE)

fclean: clean
	rm -f $(NAME)

re:fclean all


