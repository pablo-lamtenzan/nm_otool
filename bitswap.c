/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitswap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 04:37:52 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 04:45:12 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int32_t             ft_bitswap_i32(int32_t nb)
{
    nb = ((nb << 8) & 0xFF00FF00) | ((nb >> 8) & 0xFF00FF);
	return ((nb << 16) | ((nb >> 16) & 0xFFFF));
}

uint32_t            ft_bitswap_u32(uint32_t nb)
{
    nb = ((nb << 8) & 0xFF00FF00) | ((nb >> 8) & 0xFF00FF);
	return ((nb << 16) | ((nb >> 16) & 0xFFFF));
}

uint64_t            ft_bitswap_u64(uint64_t nb)
{
    nb = ((nb << 8) & 0xFF00FF00FF00FF00ULL) | ((nb >> 8) & 0x00FF00FF00FF00FFULL);
	nb = ((nb << 16) & 0xFFFF0000FFFF0000ULL)
		| ((nb >> 16) & 0x0000FFFF0000FFFFULL);
	return ((nb << 32) | (nb >> 32));
}

uint32_t            swap_if_u32(t_file *file, uint32_t nb)
{
    return (file->bitswap ? ft_bitswap_u32(nb) : nb);
}

uint64_t            swap_if_64(t_file *file, uint64_t nb)
{
    return (file->bitswap ? ft_bitswap_u64(nb) : nb);
}
