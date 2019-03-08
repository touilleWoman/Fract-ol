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

void			reset(t_context *pctx)
{
	pctx->variation_cl = 0;
	pctx->limit.x2 = 2;
	pctx->limit.x1 = -2;
	pctx->limit.y2 = 1;
	pctx->limit.y1 = -1;
	pctx->max_iteration = 50;
	pctx->stop_mouse = 0;
}

int				mouse_press(int button, int x, int y, void *param)
{
	t_context	*pctx;
	t_complex	p;
	double		xp;
	double		yp;

	pctx = (t_context *)param;
	p = normalize_pixel(x, y, pctx);
	xp = p.re;
	yp = p.im;
	mouse_press2(button, xp, yp, pctx);
	if (button == MOUSE_RIGHT)
	{
		pctx->limit.x1 -= (xp - pctx->limit.x1) / 5;
		pctx->limit.x2 += (pctx->limit.x2 - xp) / 5;
		pctx->limit.y1 -= (yp - pctx->limit.y1) / 5;
		pctx->limit.y2 += (pctx->limit.y2 - yp) / 5;
		if (pctx->max_iteration >= 50)
			pctx->max_iteration -= 2;
	}
	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	thread(pctx);
	return (0);
}

void			mouse_press2(int button, double xp, double yp, t_context *pctx)
{
	if (button == MOUSE_UP)
	{
		pctx->limit.x1 += (xp - pctx->limit.x1) / 10;
		pctx->limit.x2 -= (pctx->limit.x2 - xp) / 10;
		pctx->limit.y1 += (yp - pctx->limit.y1) / 10;
		pctx->limit.y2 -= (pctx->limit.y2 - yp) / 10;
		pctx->max_iteration += 2;
	}
	if (button == MOUSE_DOWN)
	{
		pctx->limit.x1 -= (xp - pctx->limit.x1) / 10;
		pctx->limit.x2 += (pctx->limit.x2 - xp) / 10;
		pctx->limit.y1 -= (yp - pctx->limit.y1) / 10;
		pctx->limit.y2 += (pctx->limit.y2 - yp) / 10;
		if (pctx->max_iteration >= 50)
			pctx->max_iteration -= 2;
	}
	if (button == MOUSE_LEFT)
	{
		pctx->limit.x1 += (xp - pctx->limit.x1) / 5;
		pctx->limit.x2 -= (pctx->limit.x2 - xp) / 5;
		pctx->limit.y1 += (yp - pctx->limit.y1) / 5;
		pctx->limit.y2 -= (pctx->limit.y2 - yp) / 5;
		pctx->max_iteration += 2;
	}
}

int				mouse_move(int x, int y, void *param)
{
	t_context	*pctx;
	t_complex	p;
	double		xp;
	double		yp;

	pctx = (t_context *)param;
	p = normalize_pixel(x, y, pctx);
	xp = p.re;
	yp = p.im;
	if (pctx->stop_mouse == 0)
	{
		pctx->julia.re = xp;
		pctx->julia.im = yp;
		pctx->julia_tmp.re = xp;
		pctx->julia_tmp.im = yp;
	}
	if (pctx->stop_mouse == 1)
	{
		pctx->julia.re = pctx->julia_tmp.re;
		pctx->julia.im = pctx->julia_tmp.im;
	}
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
