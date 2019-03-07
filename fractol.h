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
# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>

# define KEYCODE_ESC 53
# define KEYCODE_Z 6
# define KEYCODE_X 7
# define KEYCODE_R 15
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
# define MOUSE_LEFT 1
# define MOUSE_UP 4
# define MOUSE_DOWN 5
# define MOUSE_LEFT 1
# define WIN_X 1200
# define WIN_Y 600
# define WIN_NAME "fractol"


typedef struct		s_key
{
	float			zoom;
	int				variation_cl;
	float			var_x;
	float			var_y;
}					t_key;

typedef struct		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct 		s_limit
{
	double			x2;
	double			x1;
	double			y2;
	double			y1;
}					t_limit;

typedef struct		s_context
{
	t_key			key;
	t_limit			limit;
	char			*data_a;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				size_l;
	int				choose;
	int				max_iteration;
}					t_context;

int					window(t_context *pctx);
void				reset(t_context *pctx);
void				browse_pixel(t_context *pctx);
int					key_press(int keycode, void *param);
int					mouse_press(int button, int x, int y, void *param);
int					closewindow(void *param);
int					julia_calcu(int x, int y, t_context *pctx);
int					mandelbrot_calcu(int x, int y, t_context *pctx);
void				sub_browse_pixel(t_context *pctx, int xmin, int xmax);


#endif
