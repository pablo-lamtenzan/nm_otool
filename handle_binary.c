/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_binary.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 03:15:19 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 03:45:55 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static int          bin_error(t_data *data, t_file *file)
{
    if (file->error == ERR_OVERF)
        ft_printf("%s: %s truncated or malformed file\n", data->name_of_exec,
			file->name_of_file);
    else
        ft_printf("%s The file was not recognized as a valid object file\n",
			data->name_of_exec);
    return (FAILURE);
}

static int          start_parse_macho(t_data *data, t_file *file)
{
    |/* shit for otool (virtual archives) */
    if (parse_macho(data, file))
        return (FAILURE);
    /* TO DO : for nm print the struct symthem */
    return (SUCCES);
}

int                 start_bin(t_data *data, t_file *file)
{
    uint32_t        magic;
 
    /* TO DO : check overflow */

    // take magic byte
    magic = (uint32_t *)(file->start);
    // handle archives
    if (!ft_strncmp(file->start, ARMAG, SARMAG)) // to see now
        return (111111111111); /* handle archives */
    // handle fat
    else if (magic == FAT_MAGIC || magic == FAT_CIGAM)
    {
        // endian
        file->bitswap = magic == FAT_CIGAM ? TRUE : FALSE;
        return (111111111111111); /* handle fats */
    }
    // not fats 64 and 32 bits
    else if (magic == MH_MAGIC || magic == MH_CIGAM
            || magic == MH_MAGIC_64 || magic == MH_CIGAM_64)
    {
        // take type of arch (bits size)
        file->size_of_arch = magic == MH_MAGIC || MH_CIGAM ? ARCH_32 : ARCH_64;
        // endian
        file->bitswap = MH_CIGAM || MH_CIGAM_64 ? TRUE : FALSE;
        return (start_parse_macho(data, file));
    }
    return (FAILURE);
}

int             handle_binary(t_data *data, t_file *file)
{
    if (start_bin(data, file))
        return (bin_error(data, file));
    return (SUCCES);
}