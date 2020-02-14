/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_macho.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 03:58:39 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 05:01:47 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static int              parse_err_load_command(t_data *data, t_file *file,
    t_load_command *lc, uint32_t it)
{
    uint64_t            cmd_size;
    void                *end_of_cmds;

    // take size of cmd
    cmd_size = lc->cmdsize;
    // take end of cmd
    end_of_cmds = 1; /* TO DO */
    // if size > end of cmd : segfault big as fck
    if ((void *)lc + 1 > end_of_cmds)
    {
        ft_printf("%s: %s truncated or malformed object (load command %d exten\
            ds past the end all load commands in the file)\n",
            data->name_of_exec, file->name_of_file, it);
		file->error = ERR_WP;
		return (FAILURE);
    }
    return (SUCCES);
}

static int              parse_load_command(t_data *data, t_file *file, 
    t_load_command *lc, uint32_t it)
{
    uint32_t            cmd;

    // correct endian if there are
    cmd = swap_if_u32(file, lc->cmd);
    // verify if is possible o parse lc
    if (parse_err_load_command(data, file, lc, it)) /* TO DO */
        return (FAILURE);
    /* segments for otool */

    // symtab for nm
    if (data->bin == BIN_NM && cmd == LC_SYMTAB)
        return (parse_macho_symtab(file, (void *)lc));
    return (SUCCES);
}

int                     parse_macho(t_data *data, t_file *file)
{
    t_load_command      *lc;
    uint32_t            nb_commds;
    uint32_t            it;
    
    // set lc address after the load command meta data
    lc = (t_load_command *)(file->start + (file->size_of_arch == ARCH_32 ?
            sizeof(t_mach_hearder) : sizeof(t_mach_hearder_64)));
    /* TO DO : check segfault */
    
    /* otool shit */

    // take nb of commands in fct of 32 - 64 bits {swap_if_32 if for endian}
    nb_commds = swap_if_u32(file, file->size_of_arch == ARCH_32 ?
            ((t_mach_hearder *)(file->start))->ncmds :
            ((t_mach_hearder_64 *)(file->start))->ncmds);
    
    // parse the load command
    it = -1;
    while (++it < nb_commds)
    {
        /* TO DO : Check overflow */

        // lc + 1 for skip meta data
        if (parse_load_command(file, lc + 1, it))
            return (FAILURE);
        // uptate lc to go to the next command addr
        lc = (void *) + swap_if_u32(file, lc->cmdsize);
    }
    return (SUCCES);
    
}