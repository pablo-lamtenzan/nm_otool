/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamtenz <plamtenz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 00:15:34 by plamtenz          #+#    #+#             */
/*   Updated: 2020/02/14 06:00:32 by plamtenz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

/*
**      --> CONSTANTS
*/
#define TRUE                        1
#define FALSE                       0
#define FAILURE                     -1
#define SUCCES                      0
#define DEFAULT_EXEC                "a.out"
#define MINUS                       '-'
#define BIN_NM                      0
#define BIN_OTOOL                   1
#define ARCH_32                     0
#define ARCH_64                     1
#define ERR_NULL                    0
#define ERR_OVERF                   1
#define ERR_WP                      2

/*
**      --> MASKS
*/
#define MASK_N                      1
#define MASK_R                      2
#define MASK_G                      4
#define MASK_P                      8
#define MASK_U                      16
#define MASK_UU                     32
#define MASK_J                      64
#define MASK_A                      128
#define MASK_D                      256
#define MASK_M                      512
#define MASK_F                      1024
#define MASK_T                      2048
#define MASK_HLP                    4096
#define FILE_MACHO                  1
#define FILE_ARCH                   2
#define FILE_FAT                    4


/*
**      --> INCLUDES
*/
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/fat.h>
#include <ar.h>

/*
**      --> STRUCTS FOR EXECUTION
*/
typedef struct                      s_data
{
    const char                      *name_of_exec;
    int                             nfiles;
    const char                      **names_of_execs;
    cpu_type_t                      cpu_type;
    char                            bin;
    uint64_t                        flags;
}                                   t_data;

typedef struct                      s_flag_data
{
    char                            *simple_name;
    char                            full_name[20];
    uint64_t                        val;
}                                   t_flag_data;


typedef struct                      s_flag_arch
{
    char                            *name;
    cpu_type_t                      cpu_type;
    cpu_subtype_t                   cpu_subtype;
}                                   t_flag_arch;

/*
**      --> TYPEDEF STRUCTS OF THE HEADER OF FILES SUPORTED BY NM OR ATOOL
*/
typedef struct fat_header           t_fat_hearder;
typedef struct fat_arch             t_fat_arch;
typedef struct ar_hdr               t_ar_hdr;
typedef struct mach_header          t_mach_hearder;
typedef struct mach_header_64       t_mach_hearder_64;

/*
**      --> COMMANDS IN MACH-O FILE
*/
typedef struct load_command         t_load_command;

/*
**      --> LC_SEGMENT
*/
typedef struct segment_command      t_segment_command;
typedef struct segment_command_64   t_segment_command_64;
typedef struct section              t_section;
typedef struct section_64           t_section_64;

/*
**      --> LC_SYMTAB
*/
typedef struct symtab_command       t_symtab_command;
typedef struct nlist                t_nlist;
typedef struct nlist_64             t_nlist_64;

/*
**      --> STRUCT FOR PARSE A FILE
*/
typedef struct                      s_file
{
    void                            *start;
    void                            *end;
    char                            error;
    const char                      *name_of_file;
    const char                      *virtual_name;
    uint_fast64_t                   size;
    uint_fast64_t                   nb_of_sections;
    char                            bitswap;
    char                            type_of_file;
    char                            size_of_arch;
    struct s_data_symb              data_symb;
    
    
}                                   t_file;
 
 /*
 **     --> FOR STORE SYMBOLS
 */
typedef struct                      s_data_symb
{
    char                            *name;
    char                            name_error;
    uint_fast8_t                    type;
    char                            type_p;
    uint8_t                         section;
    uint16_t                        desc;
    uint64_t                        val;
    void                            *next;
}                                   t_data_symb;

/*
**      --> FOR STORE SECTIONS
*/
typedef struct                      s_data_sect
{
    char                            *name;
    uint64_t                        index;
    uint64_t                        addr;
    uint64_t                        size;
    uint32_t                        offset;
    void                            *next;
}                                   t_data_sect;

/*
**      --> METHODS FOR EXEC
*/
int                                 init_exec(t_data *data, char bin, int ac, char **argv);
void                                nm_help(char const *bin);
int                                 start_exec(t_data *data, const char *name_of_file);
void                                new_file(t_file *file, const char *name, uint64_t size,
        void *start);
int                                 handle_binary(t_data *data, t_file *file);
int                                 parse_macho(t_data *data, t_file *file);
t_data_symb                         *init_data_symb(t_file *file, t_data_symb *new,
        char *sym_name, void *sym);
void                                fill_fata_symb(t_file *file, t_data_symb *new);

/*
**      --> BITSWAP FOR ENDIANS METHODS
*/
int32_t                             ft_bitswap_i32(int32_t nb);
uint32_t                            ft_bitswap_u32(uint32_t nb);
uint64_t                            ft_bitswap_u64(uint64_t nb);
uint32_t                            swap_if_u32(t_file *file, uint32_t nb);
uint64_t                            swap_if_64(t_file *file, uint64_t nb);

#endif

