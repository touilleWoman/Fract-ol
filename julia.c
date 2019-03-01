/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:18:57 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/01 10:27:03 by jleblond         ###   ########.fr       */
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

void				put_pixel_with_cl(int i, t_context *pctx)
{
	t_color		cl;
	int			val_cl;

	val_cl =120;
	cl = color_val_calculate(val_cl);
	pctx->data_a[i * 4 + 2] = cl.r;
	pctx->data_a[i * 4 + 1] = cl.g;
	pctx->data_a[i * 4] = cl.b;
}

// int				get_pixel_val(int x, int y)
// {

// }

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

int					julia_calcu()
{
	float	zx;
	float	zy;
	int		iteration;
	float	xtemp;

	iteration = 0;
	while (zx * zx + zy * zy < 4 && iteration < MAX_ITERATION)
	{
		xtemp = zx * zx - zy * zy;
		zy = 2 * zx * zy  + cy;
        zx = xtemp + cx;
        iteration++;
	}
	return(iteration);


}

void				julia(void)
{
	t_context	ctx;
	int			iteration;

	window(&ctx);
	iteration = pixtel_calcu();
	printf("%d\n", iteration);

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
	// draw(pctx);
	return (0);
}

