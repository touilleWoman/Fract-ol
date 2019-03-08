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
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <pthread.h>

# define KEYCODE_ESC 53
# define KEYCODE_I 34
# define KEYCODE_O 31
# define KEYCODE_Z 6
# define KEYCODE_X 7
# define KEYCODE_R 15
# define KEYCODE_UP 126
# define KEYCODE_DOWN 125
# define KEYCODE_LEFT 123
# define KEYCODE_RIGHT 124
# define KEYCODE_A 0
# define KEYCODE_S 1
# define KEYCODE_C 8
# define KEYCODE_V 9
# define MOUSE_RIGHT 2
# define MOUSE_DOWN 4
# define MOUSE_UP 5
# define MOUSE_LEFT 1
# define WIN_X 800
# define WIN_Y 600
# define WIN_NAME "fractol"

typedef struct		s_complex
{
	double			re;
	double			im;
}					t_complex;

typedef struct		s_limit
{
	double			x2;
	double			x1;
	double			y2;
	double			y1;
}					t_limit;

typedef struct		s_context
{
	t_limit			limit;
	t_complex		julia;
	t_complex		julia_tmp;
	char			*data_a;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				size_l;
	int				choose;
	int				max_iteration;
	int				variation_cl;
	int				stop_mouse;
}					t_context;

typedef struct		s_params
{
	t_context		*pctx;
	int				xmin;
	int				xmax;
}					t_params;

int					tricorn(t_complex n, t_context *pctx);
int					julia2(t_complex n, t_context *pctx);
int					choose_fractal(char *str, t_context *pctx);
int					mouse_move(int x, int y, void *param);
t_complex			normalize_pixel(int x, int y, t_context *pctx);
void				*start_routine(void *raw_params);
int					window(t_context *pctx);
void				reset(t_context *pctx);
int					key_press(int keycode, void *param);
int					mouse_press(int button, int x, int y, void *param);
int					closewindow(void *param);
void				sub_browse_pixel(t_context *pctx, int xmin, int xmax);
int					julia_calcu(t_complex p, t_context *pctx);
int					mandelbrot_calcu(t_complex p, t_context *pctx);
void				thread(t_context *pctx);
double				abs_double(double a);
int					burningship_calcu(t_complex p, t_context *pctx);
void				put_pixel_with_cl(double x, double y,
	t_context *pctx, int iteration);
void				key_press2(int keycode, t_context *pctx);
void				mouse_press2(int button, double xp, double yp
	, t_context *pctx);
int					others(t_complex n, t_context *pctx);
int					others2(t_complex n, t_context *pctx);
int					others3(t_complex n, t_context *pctx);
int					others4(t_complex n, t_context *pctx);
int					switch_fractal(t_complex n, t_context *pctx);
#endif
