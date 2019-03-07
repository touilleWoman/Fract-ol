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
	val_cl = iteration * 360 / pctx->max_iteration + pctx->key.variation_cl;
	cl = ft_color_val_calculate(val_cl);
	pctx->data_a[i * 4 + 2] = cl.r;
	pctx->data_a[i * 4 + 1] = cl.g;
	pctx->data_a[i * 4] = cl.b;
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
			if (pctx->choose == 1)
			{
				iteration = mandelbrot_calcu(x, y, pctx);
			}
			if (pctx->choose == 2)
			{
				iteration = julia_calcu(x, y, pctx);
			}
			if (iteration != pctx->max_iteration)
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

