/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 03:08:37 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 03:44:22 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void        new_file(t_file *file, const char *name, uint64_t size,
        void *start)
{
    ft_bzero(file, sizeof(t_file));
    file->name_of_file = name;
    file->size = size;
    file->start = start;
    file->error = ERR_NULL;
    file->bitswap = 0;
    file->end = file->start + file->size;
}