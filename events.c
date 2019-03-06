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
	pctx->key.zoom = 1;
	pctx->key.variation_cl = 0;
	pctx->limit.xmax = 2;
	pctx->limit.xmin = -2;
	pctx->limit.ymax = 1;
	pctx->limit.ymin = -1;
	pctx->key.var_x = 0;
	pctx->key.var_y = 0;
	pctx->max_iteration = 50;

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
	if (keycode == KEYCODE_LEFT)
		pctx->key.var_x = pctx->key.var_x + 0.1;
	if (keycode == KEYCODE_RIGHT)
		pctx->key.var_x = pctx->key.var_x - 0.1;
	if (keycode == KEYCODE_UP)
		pctx->key.var_y = pctx->key.var_y + 0.1;
	if (keycode == KEYCODE_DOWN)
		pctx->key.var_y = pctx->key.var_y - 0.1;
	if (keycode == KEYCODE_C)
		pctx->key.variation_cl = pctx->key.variation_cl + 10;
	if (keycode == KEYCODE_V)
		pctx->key.variation_cl = pctx->key.variation_cl - 10;
	if (keycode == KEYCODE_R)
		reset(pctx);


	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	browse_pixel(pctx);


	return (0);
}


int				mouse_press(int button, int x, int y, void *param)
{
	t_context *pctx;
	float		b;
	float		h = 10;

	pctx = (t_context *)param;
	if (button == MOUSE_UP)
	{
		pctx->limit.xmax = pctx->limit.xmax * 0.8;
		pctx->limit.xmin = pctx->limit.xmin * 0.8;
		pctx->limit.ymax = pctx->limit.ymax * 0.8;
		pctx->limit.ymin = pctx->limit.ymin * 0.8;
		pctx->max_iteration = pctx->max_iteration + 50;
		double temp = pctx->limit.xmax;
		double temp2 =pctx->limit.ymax;
		pctx->limit.xmax = ((double)x * (pctx->limit.xmax - pctx->limit.xmin) / IMG_X + pctx->limit.xmin  + pctx->key.var_x) + h;
		pctx->limit.xmin = ((double)x * (temp - pctx->limit.xmin) / IMG_X + pctx->limit.xmin  + pctx->key.var_x) - h;
		pctx->limit.ymax =  ((double)y * (pctx->limit.ymax - pctx->limit.ymin) / IMG_Y + pctx->limit.ymin + pctx->key.var_y) + h;
		pctx->limit.ymin =  ((double)y * (temp2 - pctx->limit.ymin) / IMG_Y + pctx->limit.ymin + pctx->key.var_y) - h;

	}
	if (button == MOUSE_DOWN )
	{
		b = 1.25;
		pctx->limit.xmax = pctx->limit.xmax * b;
		pctx->limit.xmin = pctx->limit.xmin * b;
		pctx->limit.ymax = pctx->limit.ymax * b;
		pctx->limit.ymin = pctx->limit.ymin * b;

		if (pctx->max_iteration >=100)
		{
			pctx->max_iteration = pctx->max_iteration - 50;

		}
		x++;
		y++;

	}
	mlx_clear_window(pctx->mlx_ptr, pctx->win_ptr);
	ft_bzero(pctx->data_a, (pctx->size_l) * WIN_Y);
	browse_pixel(pctx);
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