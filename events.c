/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleblond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:11:54 by jleblond          #+#    #+#             */
/*   Updated: 2019/03/04 13:11:55 by jleblond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void				reset(t_context *pctx)
{
	pctx->variation_cl = 0;
	pctx->limit.x2 = 2;
	pctx->limit.x1 = -2;
	pctx->limit.y2 = 1;
	pctx->limit.y1 = -1;
	pctx->max_iteration = 50;
}

int					key_press(int keycode, void *param)
{
	t_context	*pctx;
	double		xd;
	double		yd;

	pctx = (t_context *)param;
	if (keycode == KEYCODE_ESC)
	{
		mlx_destroy_window(pctx->mlx_ptr, pctx->win_ptr);
		exit(0);
	}
	xd = (pctx->limit.x2 - pctx->limit.x1) / 20;
	yd = (pctx->limit.y2 - pctx->limit.y1) / 20;
	if (keycode == KEYCODE_LEFT)
	{
		pctx->limit.x1 += xd;
		pctx->limit.x2 += xd;
	}
	if (keycode == KEYCODE_RIGHT)
	{
		pctx->limit.x1 -= xd;
		pctx->limit.x2 -= xd;
	}
	if (keycode == KEYCODE_UP)
	{
		pctx->limit.y1 += yd;
		pctx->limit.y2 += yd;
	}
	if (keycode == KEYCODE_DOWN)
	{
		pctx->limit.y1 -= yd;
		pctx->limit.y2 -= yd;
	}
	if (keycode == KEYCODE_C)
		pctx->variation_cl = pctx->variation_cl + 10;
	if (keycode == KEYCODE_V)
		pctx->variation_cl = pctx->variation_cl - 10;
	if (keycode == KEYCODE_R)
		reset(pctx);
	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	thread(pctx);
	return (0);
}


int				mouse_press(int button, int x, int y, void *param)
{
	t_context *pctx;
	t_complex p;
	double		xp;
	double		yp;

	pctx = (t_context *)param;
	p = normalize_pixel(x, y, pctx);
	xp = p.re;
	yp = p.im;

	// double xd = (pctx->limit.x2 - pctx->limit.x1) / 20;
	// double yd = (pctx->limit.y2 - pctx->limit.y1) / 20;
	// double xmid = (pctx->limit.x2 - pctx->limit.x1) / 2;
	// double ymid = (pctx->limit.y2 - pctx->limit.y1) / 2;

	if (button == MOUSE_LEFT)
	{
		pctx->limit.x1 = pctx->limit.x1 * 0.8;
		pctx->limit.x2 = pctx->limit.x2 * 0.8;
		pctx->limit.y1 = pctx->limit.y1 * 0.8;
		pctx->limit.y2 = pctx->limit.y2 * 0.8;
		pctx->limit.x1 += xp * 0.8;
		pctx->limit.x2 += xp * 0.8;
		pctx->limit.y1 += yp * 0.8;
		pctx->limit.y2 += yp * 0.8;
		pctx->max_iteration += 2;
	}
	if (button == MOUSE_UP)
	{
		pctx->limit.x1 = pctx->limit.x1 * 0.8;
		pctx->limit.x2 = pctx->limit.x2 * 0.8;
		pctx->limit.y1 = pctx->limit.y1 * 0.8;
		pctx->limit.y2 = pctx->limit.y2 * 0.8;

		// pctx->limit.x1 += xd;
		// pctx->limit.x2 -= xd;
		// pctx->limit.y1 += yd;
		// pctx->limit.y2 -=; yd
		// pctx->limit.x1 = xp - xmid;
		// pctx->limit.x2 = xp + xmid;
		// pctx->limit.y1 = yp - ymid;
		// pctx->limit.y2 = yp + ymid;
		pctx->max_iteration += 2;
	}

	if (button == MOUSE_DOWN )
	{
		pctx->limit.x1 = pctx->limit.x1 * 1.25;
		pctx->limit.x2 = pctx->limit.x2 * 1.25;
		pctx->limit.y1 = pctx->limit.y1 * 1.25;
		pctx->limit.y2 = pctx->limit.y2 * 1.25;
		// pctx->limit.x1 -= xd;
		// pctx->limit.x2 += xd;
		// pctx->limit.y1 -= yd;
		// pctx->limit.y2 += yd;
		if (pctx->max_iteration >= 50)
			pctx->max_iteration -= 2;
	}
	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	thread(pctx);
	return (0);
}
int				mouse_move(int x, int y, void *param)
{
	t_context 	*pctx;
	t_complex 	p;
	double		xp;
	double		yp;

	pctx = (t_context *)param;
	p = normalize_pixel(x, y, pctx);
	xp = p.re;
	yp = p.im;
	pctx->julia.re = xp;
	pctx->julia.im = yp;
	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	thread(pctx);
	return (0);
}

int				closewindow(void *param)
{
	t_context *pctx;

	pctx = (t_context *)param;
	mlx_destroy_window(pctx->mlx_ptr, pctx->win_ptr);
	exit(0);
	return (0);
}