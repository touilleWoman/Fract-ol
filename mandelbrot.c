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


void				put_pixel_with_cl(double x, double y, t_context *pctx, int iteration)
{
	t_color		cl;
	int			val_cl;
	int			i;

	i = y * IMG_X + x;
	val_cl = iteration * 360 / MAX_ITERATION + pctx->key.variation_cl;
	cl = ft_color_val_calculate(val_cl);
	pctx->data_a[i * 4 + 2] = cl.r;
	pctx->data_a[i * 4 + 1] = cl.g;
	pctx->data_a[i * 4] = cl.b;
}



int				mandelbrot_calcu(int x, int y, t_context *pctx)
{
	t_complex	z;
	t_complex	c;
	int			iteration;
	double		temp;

	c.re = ((double)x * (pctx->limit.xmax - pctx->limit.xmin) / IMG_X + pctx->limit.xmin  + pctx->key.var_x);
	c.im = ((double)y * (pctx->limit.ymax - pctx->limit.ymin) / IMG_Y + pctx->limit.ymin + pctx->key.var_y);
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

int					window(t_context *pctx)
{
	int		bpp;
	int		endian;

	reset(pctx);
	pctx->mlx_ptr = mlx_init();
	if (pctx->mlx_ptr == NULL)
		return (-1);
	pctx->win_ptr = mlx_new_window(pctx->mlx_ptr, WIN_X, WIN_Y, WIN_NAME);
	if (pctx->win_ptr == NULL)
		return (-1);
	pctx->img_ptr = mlx_new_image(pctx->mlx_ptr, IMG_X, IMG_Y);
	pctx->data_a = mlx_get_data_addr(pctx->img_ptr, &bpp,
		 &pctx->size_l, &endian);

	browse_pixel(pctx);
	mlx_hook(pctx->win_ptr, 2, 0, key_press, pctx);
	mlx_hook(pctx->win_ptr, 17, 0, closewindow, pctx);
	mlx_hook(pctx->win_ptr, 4, 0, mouse_press, pctx);
	mlx_loop(pctx->mlx_ptr);
	return (0);

}

void			browse_pixel(t_context *pctx)
{
	int			iteration;

	iteration = 0;
	int		x = 0;
	int		y = 0;
	while (y < WIN_Y)
	{
		while (x < WIN_X)
		{
			iteration = mandelbrot_calcu(x, y, pctx);
			if (iteration != MAX_ITERATION)
			{
				put_pixel_with_cl(x, y, pctx, iteration);
			}
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(pctx->mlx_ptr,pctx->win_ptr, pctx->img_ptr, 0, 0);


}

