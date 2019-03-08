/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 11:51:02 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/08 11:51:04 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex		normalize_pixel(int x, int y, t_context *pctx)
{
	t_complex	n;

	n.re = (x * (pctx->limit.x2 - pctx->limit.x1) / WIN_X + pctx->limit.x1);
	n.im = (y * (pctx->limit.y2 - pctx->limit.y1) / WIN_Y + pctx->limit.y1);
	return (n);
}

void			put_pixel_with_cl(double x, double y, t_context *pctx, int iter)
{
	t_color		cl;
	int			val_cl;
	int			i;

	i = y * WIN_X + x;
	val_cl = iter * 360 / pctx->max_iteration + pctx->variation_cl;
	cl = ft_color_val_calculate(val_cl);
	pctx->data_a[i * 4 + 2] = cl.r;
	pctx->data_a[i * 4 + 1] = cl.g;
	pctx->data_a[i * 4] = cl.b;
}

double			abs_double(double a)
{
	return (a >= 0 ? a : -a);
}

int				key_press(int keycode, void *param)
{
	t_context	*pctx;

	pctx = (t_context *)param;
	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(pctx->mlx_ptr, pctx->win_ptr);
		exit(0);
	}
	key_press2(keycode, pctx);
	keycode == KEYCODE_C ? pctx->variation_cl += 10 : keycode;
	keycode == KEYCODE_V ? pctx->variation_cl -= 10 : keycode;
	keycode == KEYCODE_R ? reset(pctx) : keycode;
	keycode == KEYCODE_A ? pctx->choose++ : keycode;
	keycode == KEYCODE_S ? pctx->choose-- : keycode;
	keycode == KEYCODE_Z ? pctx->stop_mouse = 1 : keycode;
	keycode == KEYCODE_X ? pctx->stop_mouse = 0 : keycode;
	keycode == KEYCODE_I ? pctx->max_iteration += 50 : keycode;
	keycode == KEYCODE_O ? pctx->max_iteration -= 50 : keycode;
	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	thread(pctx);
	return (0);
}

void			key_press2(int keycode, t_context *pctx)
{
	double		xd;
	double		yd;

	xd = (pctx->limit.x2 - pctx->limit.x1) / 10;
	yd = (pctx->limit.y2 - pctx->limit.y1) / 10;
	if (keycode == KEYCODE_RIGHT)
	{
		pctx->limit.x1 += xd;
		pctx->limit.x2 += xd;
	}
	if (keycode == KEYCODE_LEFT)
	{
		pctx->limit.x1 -= xd;
		pctx->limit.x2 -= xd;
	}
	if (keycode == KEYCODE_DOWN)
	{
		pctx->limit.y1 += yd;
		pctx->limit.y2 += yd;
	}
	if (keycode == KEYCODE_UP)
	{
		pctx->limit.y1 -= yd;
		pctx->limit.y2 -= yd;
	}
}
