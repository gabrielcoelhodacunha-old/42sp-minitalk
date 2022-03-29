/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcoelho- <gcoelho-@student.42sp.org>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:14:00 by gcoelho-          #+#    #+#             */
/*   Updated: 2022/03/29 18:44:28 by gcoelho-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	set_flags(char format, size_t *flags)
{
	if (!ft_strchr("xX", format))
		flags[ALTERNATE_FORM] = 0;
	if (ft_strchr("p", format))
		flags[ALTERNATE_FORM] = 1;
	if (!ft_strchr("di", format)
		|| (ft_strchr("di", format) && flags[SIGNED]))
		flags[BLANK] = 0;
	if ((ft_strchr("diuxX", format) && flags[PRECISION])
		|| flags[NEGATIVE_WIDTH])
		flags[ZERO_PADDING] = 0;
}
