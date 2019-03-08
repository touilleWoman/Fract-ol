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

t_complex	normalize_pixel(int x, int y, t_context *pctx)
{
	t_complex	n;

	n.re = (x * (pctx->limit.x2 - pctx->limit.x1) / WIN_X + pctx->limit.x1);
	n.im = (y * (pctx->limit.y2 - pctx->limit.y1) / WIN_Y + pctx->limit.y1);
	return (n);
}

void		put_pixel_with_cl(double x, double y, t_context *pctx, int iter)
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
