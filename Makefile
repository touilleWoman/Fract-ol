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



CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = fractol

SOURCE = main.c julia.c

OFILE = $(SOURCE:.c=.o)

HEADER = fractol.h

LIBFTA = libft/libft.a

INC = -I ./libft -I minilibx_macos

all: $(OFILE) $(LIBFTA)
	$(CC) $(CFLAGS) $(OFILE) $(LIBFTA) $(INC) -L minilibx_macos  -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $(SOURCE) $(INC)

$(LIBFTA):
	make -C ./libft

clean:
	rm -f $(OFILE)

fclean: clean
	rm -f $(NAME)

re:fclean all

.PHONY: all clean fclean re
