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
	xd = (pctx->limit.x2 - pctx->limit.x1) / 10;
	yd = (pctx->limit.y2 - pctx->limit.y2) / 10;
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
	double xpmin = pctx->limit.x1;
	double xpmax = pctx->limit.x2;
	double ypmin = pctx->limit.y1;
	double ypmax = pctx->limit.y2;

	double xd = (xpmax - xpmin) / 30;
	double yd = (ypmax - ypmin) / 30;


	// double xmed = (xpmax - xpmin) / 2 + xpmin;
	// double ymed = (ypmax - ypmin) / 2 + ypmin;

	// pctx->limit.x1 += xp - xmed;
	// pctx->limit.x2 +=  xp - xmed;
	// pctx->limit.y1 += yp - ymed;
	// pctx->limit.y2 += yp - ymed;

	if (button == MOUSE_UP)
	{

		pctx->limit.x1 += xd;
		pctx->limit.x2 -= xd;
		pctx->limit.y1 += yd;
		pctx->limit.y2 -= yd;
		// pctx->max_iteration +=10;

	}

	if (button == MOUSE_DOWN )
	{
		pctx->limit.x1 -= xd;
		pctx->limit.x2 += xd;
		pctx->limit.y1 -= yd;
		pctx->limit.y2 += yd;
		// if (pctx->max_iteration >=60)
		// {
		// 	pctx->max_iteration = pctx->max_iteration - 10;

		// }

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