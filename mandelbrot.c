/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:00:33 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/02 11:00:41 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color				color_val_calculate(int val_cl)
{
	t_color		cl;

	if (val_cl < 0)
		val_cl = -val_cl;
	while (val_cl > 360)
		val_cl = val_cl - 360;
	if (val_cl >= 0 && val_cl < 121)
	{
		cl.b = 0;
		cl.g = val_cl * (255 / 120);
		cl.r = 255 - cl.g;
	}
	else if (val_cl < 240)
	{
		cl.b = (val_cl - 120) * 255 / 120;
		cl.g = 255 - cl.b;
		cl.r = 0;
	}
	else
	{
		cl.r = (val_cl - 240) * 255 / 120;
		cl.g = 0;
		cl.b = 255 - cl.r;
	}
	return (cl);
}

void				put_pixel_with_cl(double x, double y, t_context *pctx, int iteration)
{
	t_color		cl;
	int			val_cl;
	int			i;

	i = y * IMG_X + x;
	val_cl = iteration * 360 / MAX_ITERATION;
	cl = color_val_calculate(val_cl);
	pctx->data_a[i * 4 + 2] = cl.r;
	pctx->data_a[i * 4 + 1] = cl.g;
	pctx->data_a[i * 4] = cl.b;
}

int					window(t_context *pctx)
{
	int		bpp;
	int		size_l;
	int		endian;

	pctx->mlx_ptr = mlx_init();
	if (pctx->mlx_ptr == NULL)
		return (-1);
	pctx->win_ptr = mlx_new_window(pctx->mlx_ptr, WIN_X, WIN_Y, WIN_NAME);
	if (pctx->win_ptr == NULL)
		return (-1);
	pctx->img_ptr = mlx_new_image(pctx->mlx_ptr, IMG_X, IMG_Y);
	pctx->data_a = mlx_get_data_addr(pctx->img_ptr, &bpp,
	 &size_l, &endian);
	return (0);

}

int				mandelbrot_calcu(int x, int y)
{
	t_complex	z;
	t_complex	c;
	int			iteration;
	double		temp;

	c.re = ((double)x * 3 / IMG_X - 2);
	c.im = ((double)y * 2 / IMG_Y - 1);
	iteration = 0;
	z.re = 0;
	z.im = 0;
	while ((iteration < MAX_ITERATION) && (z.re * z.re + z.im * z.im < 4))
	{
		temp = z.re;
		z.re = z.re * z.re - z.im * z.im + c.re;
		z.im = 2 * z.im * temp + c.im;
        iteration++;
   	}
	return (iteration);
}


void			mandelbrot(void)
{
	t_context	ctx;
	int			iteration;

	window(&ctx);
	iteration = 0;
	int		x = 0;
	int		y = 0;
	while (y < WIN_Y)
	{
		while (x < WIN_X)
		{
			iteration = mandelbrot_calcu(x, y);
			if (iteration != MAX_ITERATION)
			{
				put_pixel_with_cl(x, y, &ctx, iteration);
			}
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(ctx.mlx_ptr,ctx.win_ptr, ctx.img_ptr, 0, 0);
	mlx_hook(ctx.win_ptr, 2, 0, key_press, &ctx);
	mlx_loop(ctx.mlx_ptr);

}

int					key_press(int keycode, void *param)
{
	t_context *pctx;

	pctx = (t_context *)param;
	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(pctx->mlx_ptr, pctx->win_ptr);
		exit(0);
	}

	// mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	// ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	return (0);
}

