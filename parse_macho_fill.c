/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_macho_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 05:30:35 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 06:00:04 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_data_symb             *init_data_symb(t_file *file, t_data_symb *new,
        char *sym_name, void *sym)
{
    char                err_name;

    ft_bzero(new, sizeof(t_data_symb));
    err_name = 0;
    new->type_p = ' ';
    new->name = /* some strdup hwo can handle overflows */1;
    // verify name
    if (err_name)
        new->name_error = TRUE;
    if (!err_name)
        return (NULL);
    // handle 32b 64b and TAKE DATA FROM META
    if (file->size_of_arch == ARCH_32)
    {
        new->type = ((t_nlist *)sym)->n_type;
        new->section = ((t_nlist *)sym)->n_sect;
        new->desc = ((t_nlist *)sym)->n_desc;
        new->val = swap_if_u32(file, ((t_nlist *)sym)->n_value);
    }
    else
    {
        new->type = ((t_nlist_64 *)sym)->n_type;
        new->section = ((t_nlist_64 *)sym)->n_sect;
        new->desc = ((t_nlist_64 *)sym)->n_desc;
        new->val = swap_if_u64(file, ((t_nlist_64 *)sym)->n_value);
    }
    return (new);
}

void                fill_fata_symb(t_file *file, t_data_symb *new)
{
    // set type of the symbols
    
    if (N_STAB & new->type)
    {
        new->type_p = '-';
        /* debug shit */
    }
    else if ((N_TYPE & new->type) == N_UNDF)
    {
        if (new->name_error)
            new->type_p = 'C';
        else if (new->type & N_EXT)
            new->type_p = 'U';
        else
            new->type_p = '?';
    }
    else if ((N_TYPE & new->type == N_SECT))
        ; /* do stuff the sections */
    else if ((N_TYPE & new->type) == N_ABS)
        new->type_p = 'A';
    else if ((N_TYPE & new->type) == N_INDR)
        new->type_p = 'I';
}