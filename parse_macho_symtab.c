/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_macho_symtab.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 05:02:37 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 06:04:01 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

t_data_symb         *new_data_sym(t_file *file, void *strtab, void *sym)
{
    t_data_symb     new;
    char            *sym_name;

    // manage 32 / 64 bit and endian
    sym_name = strtab + swap_if_u32(file, file->size_of_arch == ARCH_32 ?
        ((t_nlist *)sym)->n_un.n_strx : ((t_nlist_64 *)sym)->n_un.n_strx);
    // init symbol struct
    init_data_symb(file, &new, sym_name, sym);
    // set symbols
    fill_fata_symb(file, &new);

    /* no good but is for understand need some lstnew */
    return (new = malloc(sizeof(t_data_symb *)));
    //return lstnew
}         

int                 parse_macho_symtab(t_file *file, t_symtab_command *sym_cmd)
{
    void            *sym;
    uint64_t        sym_size;
    void            *strtab;
    uint64_t        nb_syms;
    t_data_symb     data_sym;

    /* TO DO : check overflow */
    
    // skip meta data and manage endian
    strtab = (void *)file->start + swap_if_u32(file, sym_cmd->symoff);
    sym = (void *)file->start + swap_if_u32(file, sym_cmd->symoff);
    // take nb of sym and manege endian
    nb_syms = swap_if_u32(file, sym_cmd->nsyms);
    // take size hadling 64 or 32 bits
    sym_size = file->size_of_arch == ARCH_32 ? sizeof(t_nlist) :
            sizeof(t_nlist_64);
    // take values into a linked list of each sym
    while (nb_syms--)
    {
        /* TO DO : check overflow */
        
        if (!(data_sym = new_data_sym(file, strtab, sym)))
            return (FAILURE);
        /* TO DO lstadd */
        
        // go to next sym
        sym += sym_size;
    }
    return (SUCCES);
}