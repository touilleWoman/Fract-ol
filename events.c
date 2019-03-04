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
	if (keycode == KEYCODE_Z)
		pctx->key.zoom = pctx->key.zoom - 0.02;
	if (keycode == KEYCODE_X)
		pctx->key.zoom = pctx->key.zoom + 0.02;
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