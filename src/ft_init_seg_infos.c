/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_seg_infos.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aollivie <aollivie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:21:45 by aollivie          #+#    #+#             */
/*   Updated: 2017/11/07 16:33:04 by aollivie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

void	ft_init_seg_infos(t_seg_infos *seg_infos)
{
	seg_infos->text_nsect = NO_SECT;
	seg_infos->data_nsect = NO_SECT;
	seg_infos->bss_nsect = NO_SECT;
	return ;
}
