/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:06:17 by jleblond          #+#    #+#             */
/*   Updated: 2019/02/18 15:06:18 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>

# define MAX_ITERATION 50
# define KEYCODE_ESC 53
# define KEYCODE_Z 6
# define KEYCODE_X 7
# define KEYCODE_UP 126
# define KEYCODE_DOWN 125
# define KEYCODE_LEFT 123
# define KEYCODE_RIGHT 124
# define KEYCODE_Q 12
# define KEYCODE_W 13
# define KEYCODE_A 0
# define KEYCODE_S 1
# define KEYCODE_C 8
# define KEYCODE_V 9
# define KEYCODE_ONE 18
# define KEYCODE_TWO 19
# define KEYCODE_J 38
# define KEYCODE_K 40
# define KEYCODE_L 37
# define KEYCODE_I 34
# define WIN_X 800
# define WIN_Y 600
# define IMG_X 800
# define IMG_Y 600
# define WIN_NAME "fractol"

typedef struct		s_context
{
	char			*data_a;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
}					t_context;

typedef struct 		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_color;

void			mandelbrot(void);
int		key_press(int keycode, void *param);
#endif
