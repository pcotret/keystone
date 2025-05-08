/**
 * @file elf.h
 * @brief Definitions and structures for ELF (Executable and Linkable Format) files.
 *
 * This header defines the ELF32 and ELF64 structures and constants used to
 * interpret ELF binary formats for 32-bit and 64-bit architectures.
 */
#ifndef _ELF_H
#define _ELF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>


/* 16-bit half-word types */
typedef uint16_t Elf32_Half;     /**< 16-bit unsigned type for ELF32 */
typedef uint16_t Elf64_Half;     /**< 16-bit unsigned type for ELF64 */

/* 32-bit and signed 32-bit word types */
typedef uint32_t Elf32_Word;     /**< 32-bit unsigned type for ELF32 */
typedef	int32_t  Elf32_Sword;    /**< 32-bit signed type for ELF32 */
typedef uint32_t Elf64_Word;     /**< 32-bit unsigned type for ELF64 */
typedef	int32_t  Elf64_Sword;    /**< 32-bit signed type for ELF64 */

/* 64-bit and signed 64-bit extended word types */
typedef uint64_t Elf32_Xword;    /**< 64-bit unsigned type (not native to ELF32) */
typedef	int64_t  Elf32_Sxword;   /**< 64-bit unsigned type (not native to ELF32) */
typedef uint64_t Elf64_Xword;    /**< 64-bit unsigned type for ELF64 */
typedef	int64_t  Elf64_Sxword;   /**< 64-bit unsigned type for ELF64 */

/* Address and offset types */
typedef uint32_t Elf32_Addr;     /**< Program address in ELF32 */
typedef uint64_t Elf64_Addr;     /**< Program address in ELF64 */

typedef uint32_t Elf32_Off;      /**< File offset in ELF32 */
typedef uint64_t Elf64_Off;      /**< File offset in ELF64 */

/* Section index types */
typedef uint16_t Elf32_Section;  /**< Section index in ELF32 */
typedef uint16_t Elf64_Section;  /**< Section index in ELF64 */

/* Version symbol types */
typedef Elf32_Half Elf32_Versym; /**< Version symbol type for ELF32 */
typedef Elf64_Half Elf64_Versym; /**< Version symbol type for ELF64 */

#define EI_NIDENT (16)

/**
 * @struct Elf32_Ehdr
 * @brief ELF header for 32-bit binaries.
 *
 * This structure appears at the beginning of every ELF32 file and contains
 * information about the file's organization and how to interpret its contents.
 */
typedef struct {
  unsigned char	e_ident[EI_NIDENT]; /**< Magic number and other identification. */
  Elf32_Half	e_type;               /**< Object file type. */
  Elf32_Half	e_machine;            /**< Target architecture. */
  Elf32_Word	e_version;            /**< Object file version. */
  Elf32_Addr	e_entry;              /**< Entry point virtual address. */
  Elf32_Off	e_phoff;                /**< Program header table file offset. */
  Elf32_Off	e_shoff;                /**< Section header table file offset. */
  Elf32_Word	e_flags;              /**< Processor-specific flags. */
  Elf32_Half	e_ehsize;             /**< ELF header size in bytes. */
  Elf32_Half	e_phentsize;          /**< Program header table entry size. */
  Elf32_Half	e_phnum;              /**< Program header table entry count. */
  Elf32_Half	e_shentsize;          /**< Section header table entry size. */
  Elf32_Half	e_shnum;              /**< Section header table entry count. */
  Elf32_Half	e_shstrndx;           /**< Section header string table index. */
} Elf32_Ehdr;

/**
 * @struct Elf64_Ehdr
 * @brief ELF header for 64-bit binaries.
 *
 * This structure appears at the beginning of every ELF64 file and contains
 * information about the file's organization and how to interpret its contents.
 */
typedef struct {
  unsigned char	e_ident[EI_NIDENT]; /**< Magic number and other identification. */
  Elf64_Half	e_type;               /**< Object file type. */
  Elf64_Half	e_machine;            /**< Target architecture. */
  Elf64_Word	e_version;            /**< Object file version. */
  Elf64_Addr	e_entry;              /**< Entry point virtual address. */
  Elf64_Off	e_phoff;                /**< Program header table file offset. */
  Elf64_Off	e_shoff;                /**< Section header table file offset. */
  Elf64_Word	e_flags;              /**< Processor-specific flags. */
  Elf64_Half	e_ehsize;             /**< ELF header size in bytes. */
  Elf64_Half	e_phentsize;          /**< Program header table entry size. */
  Elf64_Half	e_phnum;              /**< Program header table entry count. */
  Elf64_Half	e_shentsize;          /**< Section header table entry size. */
  Elf64_Half	e_shnum;              /**< Section header table entry count. */
  Elf64_Half	e_shstrndx;           /**< Section header string table index. */
} Elf64_Ehdr;

/** \name ELF Magic Number Indexes and Values */
#define EI_MAG0     0           /**< File identification byte 0 index (0x7F). */
#define ELFMAG0     0x7f        /**< Value for byte 0: 0x7F. */
#define EI_MAG1     1           /**< File identification byte 1 index ('E'). */
#define ELFMAG1     'E'         /**< Value for byte 1: 'E'. */
#define EI_MAG2     2           /**< File identification byte 2 index ('L'). */
#define ELFMAG2     'L'         /**< Value for byte 2: 'L'. */
#define EI_MAG3     3           /**< File identification byte 3 index ('F'). */
#define ELFMAG3     'F'         /**< Value for byte 3: 'F'. */

/** \brief Full ELF magic number string ("\177ELF"). */
#define ELFMAG      "\177ELF"

/** \brief Number of bytes in the ELF magic number. */
#define SELFMAG     4

/** \name ELF Class (32-bit or 64-bit) */
#define EI_CLASS        4           /**< Index for file class in e_ident. */
#define ELFCLASSNONE    0           /**< Invalid class. */
#define ELFCLASS32      1           /**< 32-bit objects. */
#define ELFCLASS64      2           /**< 64-bit objects. */
#define ELFCLASSNUM     3           /**< Number of defined classes. */

/** \name Data Encoding */
#define EI_DATA         5           /**< Index for data encoding in e_ident. */
#define ELFDATANONE     0           /**< Invalid data encoding. */
#define ELFDATA2LSB     1           /**< Little-endian. */
#define ELFDATA2MSB     2           /**< Big-endian. */
#define ELFDATANUM      3           /**< Number of defined data encodings. */

/** \brief Index for version field in e_ident. */
#define EI_VERSION      6

#define EI_OSABI 7                  /**< Index in e_ident for OS/ABI identification. */
#define ELFOSABI_NONE 0            /**< UNIX System V ABI. */
#define ELFOSABI_SYSV 0            /**< Alias for UNIX System V ABI. */
#define ELFOSABI_HPUX 1            /**< HP-UX ABI. */
#define ELFOSABI_NETBSD 2          /**< NetBSD ABI. */
#define ELFOSABI_LINUX 3           /**< Linux ABI. */
#define ELFOSABI_GNU 3             /**< Alias for GNU/Linux ABI. */
#define ELFOSABI_SOLARIS 6         /**< Solaris ABI. */
#define ELFOSABI_AIX 7             /**< AIX ABI. */
#define ELFOSABI_IRIX 8            /**< IRIX ABI. */
#define ELFOSABI_FREEBSD 9         /**< FreeBSD ABI. */
#define ELFOSABI_TRU64 10          /**< TRU64 UNIX ABI. */
#define ELFOSABI_MODESTO 11        /**< Novell Modesto ABI. */
#define ELFOSABI_OPENBSD 12        /**< OpenBSD ABI. */
#define ELFOSABI_ARM 97            /**< ARM architecture ABI. */
#define ELFOSABI_STANDALONE 255    /**< Standalone (embedded) ABI. */

#define EI_ABIVERSION 8        /**< ABI version index in e_ident. */

#define EI_PAD        9        /**< Start of padding bytes in e_ident. */



#define ET_NONE   0            /**< No file type. */
#define ET_REL    1            /**< Relocatable file. */
#define ET_EXEC   2            /**< Executable file. */
#define ET_DYN    3            /**< Shared object file. */
#define ET_CORE   4            /**< Core file. */
#define ET_NUM    5            /**< Number of defined file types. */
#define ET_LOOS   0xfe00       /**< Lowest operating system-specific type. */
#define ET_HIOS   0xfeff       /**< Highest operating system-specific type. */
#define ET_LOPROC 0xff00       /**< Lowest processor-specific file type. */
#define ET_HIPROC 0xffff       /**< Highest processor-specific file type. */



#define EM_NONE         0     /**< No machine. */
#define EM_M32          1     /**< AT&T WE 32100. */
#define EM_SPARC        2     /**< SPARC. */
#define EM_386          3     /**< Intel 80386. */
#define EM_68K          4     /**< Motorola 68000. */
#define EM_88K          5     /**< Motorola 88000. */
#define EM_860          7     /**< Intel 80860. */
#define EM_MIPS         8     /**< MIPS RS3000 big-endian. */
#define EM_S370         9     /**< IBM System/370. */
#define EM_MIPS_RS3_LE 10     /**< MIPS RS3000 little-endian. */

#define EM_PARISC      15  /**< Hewlett-Packard PA-RISC. */
#define EM_VPP500      17  /**< Fujitsu VPP500. */
#define EM_SPARC32PLUS 18  /**< Enhanced SPARC with 32-bit addressing. */
#define EM_960         19  /**< Intel 80960. */
#define EM_PPC         20  /**< PowerPC. */
#define EM_PPC64       21  /**< 64-bit PowerPC. */
#define EM_S390        22  /**< IBM System/390. */

#define EM_V800        36  /**< NEC V800. */
#define EM_FR20        37  /**< Fujitsu FR20. */
#define EM_RH32        38  /**< TRW RH-32. */
#define EM_RCE         39  /**< Motorola RCE. */
#define EM_ARM         40  /**< ARM 32-bit architecture. */
#define EM_FAKE_ALPHA  41  /**< Digital Alpha (placeholder). */
#define EM_SH          42  /**< Hitachi SH. */
#define EM_SPARCV9     43  /**< SPARC v9 64-bit. */
#define EM_TRICORE     44  /**< Infineon Tricore. */
#define EM_ARC         45  /**< Argonaut RISC Core. */
#define EM_H8_300      46  /**< Hitachi H8/300. */
#define EM_H8_300H     47  /**< Hitachi H8/300H. */
#define EM_H8S         48  /**< Hitachi H8S. */
#define EM_H8_500      49  /**< Hitachi H8/500. */
#define EM_IA_64       50  /**< Intel IA-64. */
#define EM_MIPS_X      51  /**< Stanford MIPS-X. */
#define EM_COLDFIRE    52  /**< Motorola ColdFire. */
#define EM_68HC12      53  /**< Motorola M68HC12. */
#define EM_MMA         54  /**< Fujitsu MMA. */
#define EM_PCP         55  /**< Siemens PCP. */
#define EM_NCPU        56  /**< Sony nCPU. */
#define EM_NDR1        57  /**< Denso NDR1. */
#define EM_STARCORE    58  /**< Motorola Star*Core. */
#define EM_ME16        59  /**< Toyota ME16. */
#define EM_ST100       60  /**< STMicroelectronics ST100. */
#define EM_TINYJ       61  /**< Advanced Logic Corp. TinyJ. */
#define EM_X86_64      62  /**< AMD x86-64. */
#define EM_PDSP        63  /**< Sony DSP Processor. */

#define EM_FX66           66  /**< Siemens FX66. */
#define EM_ST9PLUS        67  /**< STMicroelectronics ST9+ 8-bit. */
#define EM_ST7            68  /**< STMicroelectronics ST7. */
#define EM_68HC16         69  /**< Motorola 68HC16. */
#define EM_68HC11         70  /**< Motorola 68HC11. */
#define EM_68HC08         71  /**< Motorola 68HC08. */
#define EM_68HC05         72  /**< Motorola 68HC05. */
#define EM_SVX            73  /**< Silicon Graphics SVx. */
#define EM_ST19           74  /**< STMicroelectronics ST19. */
#define EM_VAX            75  /**< Digital Equipment Corporation VAX. */
#define EM_CRIS           76  /**< Axis Communications CRIS. */
#define EM_JAVELIN        77  /**< Javelin. */
#define EM_FIREPATH       78  /**< Firepath. */
#define EM_ZSP            79  /**< LSI Logic ZSP. */
#define EM_MMIX           80  /**< Donald Knuth's MMIX. */
#define EM_HUANY          81  /**< Huany. */
#define EM_PRISM          82  /**< PRISM. */
#define EM_AVR            83  /**< Atmel AVR. */
#define EM_FR30           84  /**< Fujitsu FR30. */
#define EM_D10V           85  /**< Mitsubishi D10V. */
#define EM_D30V           86  /**< Mitsubishi D30V. */
#define EM_V850           87  /**< NEC V850. */
#define EM_M32R           88  /**< Mitsubishi M32R. */
#define EM_MN10300        89  /**< Mitsubishi MN10300. */
#define EM_MN10200        90  /**< Mitsubishi MN10200. */
#define EM_PJ             91  /**< PJ. */
#define EM_OR1K           92  /**< OpenRISC 1K. */
#define EM_OPENRISC       92  /**< OpenRISC 1K (same as EM_OR1K). */
#define EM_ARC_A5         93  /**< ARC A5. */
#define EM_ARC_COMPACT    93  /**< ARC Compact (same as EM_ARC_A5). */
#define EM_XTENSA         94  /**< Tensilica Xtensa. */
#define EM_VIDEOCORE      95  /**< VideoCore. */
#define EM_TMM_GPP        96  /**< Thomson Multimedia GPP. */
#define EM_NS32K          97  /**< National Semiconductor 32k. */
#define EM_TPC            98  /**< Texas Instruments TPC. */
#define EM_SNP1K          99  /**< Stanford SNP1K. */
#define EM_ST200          100 /**< STMicroelectronics ST200. */
#define EM_IP2K           101 /**< IP2K. */
#define EM_MAX            102 /**< Max. */
#define EM_CR             103 /**< CR. */
#define EM_F2MC16         104 /**< Fujitsu F2MC16. */
#define EM_MSP430         105 /**< Texas Instruments MSP430. */
#define EM_BLACKFIN       106 /**< Analog Devices Blackfin. */
#define EM_SE_C33         107 /**< SE C33. */
#define EM_SEP            108 /**< SEP. */
#define EM_ARCA           109 /**< ARCA. */
#define EM_UNICORE        110 /**< Unicore. */
#define EM_EXCESS         111 /**< Excess. */
#define EM_DXP            112 /**< DXP. */
#define EM_ALTERA_NIOS2   113 /**< Altera Nios II. */
#define EM_CRX            114 /**< CRX. */
#define EM_XGATE          115 /**< Freescale XGate. */
#define EM_C166           116 /**< Infineon C166. */
#define EM_M16C           117 /**< Renesas M16C. */
#define EM_DSPIC30F       118 /**< Microchip dsPIC30F. */
#define EM_CE             119 /**< CE. */
#define EM_M32C           120 /**< Renesas M32C. */
#define EM_TSK3000        131 /**< NXP TSK3000. */
#define EM_RS08           132 /**< Freescale RS08. */
#define EM_SHARC          133 /**< Analog Devices SHARC. */
#define EM_ECOG2          134 /**< Silicon Laboratories Ecore. */
#define EM_SCORE7         135 /**< SCORE7. */
#define EM_DSP24          136 /**< DSP24. */
#define EM_VIDEOCORE3     137 /**< VideoCore 3. */
#define EM_LATTICEMICO32  138 /**< LatticeMico32. */
#define EM_SE_C17         139 /**< SE C17. */
#define EM_TI_C6000       140 /**< Texas Instruments C6000. */
#define EM_TI_C2000       141 /**< Texas Instruments C2000. */
#define EM_TI_C5500       142 /**< Texas Instruments C5500. */
#define EM_TI_ARP32       143 /**< Texas Instruments ARP32. */
#define EM_TI_PRU         144 /**< Texas Instruments PRU. */
#define EM_MMDSP_PLUS     160 /**< MMDSP+ (Microchip). */
#define EM_CYPRESS_M8C    161 /**< Cypress M8C. */
#define EM_R32C           162 /**< Renesas R32C. */
#define EM_TRIMEDIA       163 /**< TriMedia. */
#define EM_QDSP6          164 /**< Qualcomm DSP6. */
#define EM_8051           165 /**< Intel 8051. */
#define EM_STXP7X         166 /**< STMicroelectronics STXP7X. */
#define EM_NDS32          167 /**< Nuvoton NDS32. */
#define EM_ECOG1X         168 /**< Silicon Laboratories ECOG1X. */
#define EM_MAXQ30         169 /**< Maxim MAXQ30. */
#define EM_XIMO16         170 /**< Xilinx XIMO16. */
#define EM_MANIK          171 /**< Manik. */
#define EM_CRAYNV2        172 /**< Cray NV2. */
#define EM_RX             173 /**< RX. */
#define EM_METAG          174 /**< Metag. */
#define EM_MCST_ELBRUS    175 /**< MCST Elbrus. */
#define EM_ECOG16         176 /**< Silicon Laboratories ECOG16. */
#define EM_CR16           177 /**< National Semiconductor CR16. */
#define EM_ETPU           178 /**< NXP eTPU. */
#define EM_SLE9X          179 /**< SLE9X. */
#define EM_L10M           180 /**< L10M. */
#define EM_K10M           181 /**< K10M. */
#define EM_AARCH64        183 /**< ARM AARCH64. */
#define EM_AVR32          185 /**< Atmel AVR32. */
#define EM_STM8           186 /**< STMicroelectronics STM8. */
#define EM_TILE64         187 /**< Tilera TILE64. */
#define EM_TILEPRO        188 /**< Tilera TILEPro. */
#define EM_MICROBLAZE     189 /**< Xilinx MicroBlaze. */
#define EM_CUDA           190 /**< NVIDIA CUDA. */
#define EM_TILEGX         191 /**< Tilera TILE-Gx. */
#define EM_CLOUDSHIELD    192 /**< CloudShield. */
#define EM_COREA_1ST      193 /**< CoreA 1st Generation. */
#define EM_COREA_2ND      194 /**< CoreA 2nd Generation. */
#define EM_ARC_COMPACT2   195 /**< ARC Compact2. */
#define EM_OPEN8          196 /**< Open8. */
#define EM_RL78           197 /**< Renesas RL78. */
#define EM_VIDEOCORE5     198 /**< VideoCore 5. */
#define EM_78KOR          199 /**< 78KOR. */
#define EM_56800EX        200 /**< Freescale 56800EX. */
#define EM_BA1            201 /**< BA1. */
#define EM_BA2            202 /**< BA2. */
#define EM_XCORE          203 /**< XMOS XCore. */
#define EM_MCHP_PIC       204 /**< Microchip PIC. */
#define EM_KM32           210 /**< KM32. */
#define EM_KMX32          211 /**< KMX32. */
#define EM_EMX16          212 /**< EMX16. */
#define EM_EMX8           213 /**< EMX8. */
#define EM_KVARC          214 /**< KVARC. */
#define EM_CDP            215 /**< CDP. */
#define EM_COGE           216 /**< COGE. */
#define EM_COOL           217 /**< COOL. */
#define EM_NORC           218 /**< NORC. */
#define EM_CSR_KALIMBA    219 /**< CSR Kalimba. */
#define EM_Z80            220 /**< Zilog Z80. */
#define EM_VISIUM         221 /**< Visium. */
#define EM_FT32           222 /**< FT32. */
#define EM_MOXIE          223 /**< Moxie. */
#define EM_AMDGPU         224 /**< AMD GPU. */
#define EM_RISCV          243 /**< RISC-V. */
#define EM_BPF            247 /**< Berkeley Packet Filter. */
#define EM_CSKY           252 /**< C-SKY. */
#define EM_NUM            253 /**< Reserved for future architectures. */

#define EM_ALPHA         0x9026 /**< Alpha architecture (used by DEC). */

#define EV_NONE          0    /**< No version information. */
#define EV_CURRENT       1    /**< Current version of ELF format. */
#define EV_NUM           2    /**< Number of version types (reserved for future use). */

/**
 * @struct Elf32_Shdr
 * @brief Section header for 32-bit ELF binaries.
 *
 * Describes each section within an ELF32 file, providing details such as
 * type, size, location, and alignment of the section.
 */
typedef struct {
  Elf32_Word	sh_name;      /**< Offset to the section name in the string table. */
  Elf32_Word	sh_type;      /**< Section type (e.g., SHT_PROGBITS, SHT_SYMTAB). */
  Elf32_Word	sh_flags;     /**< Section attributes (e.g., SHF_WRITE, SHF_ALLOC). */
  Elf32_Addr	sh_addr;      /**< Virtual address in memory (for loaded sections). */
  Elf32_Off	sh_offset;      /**< Offset of the section in the file. */
  Elf32_Word	sh_size;      /**< Size of the section in bytes. */
  Elf32_Word	sh_link;      /**< Link to another section (e.g., symbol table index). */
  Elf32_Word	sh_info;      /**< Extra information (e.g., index of related section). */
  Elf32_Word	sh_addralign; /**< Address alignment constraints. */
  Elf32_Word	sh_entsize;   /**< Entry size if section holds a table of fixed-size entries. */
} Elf32_Shdr;

/**
 * @struct Elf64_Shdr
 * @brief Section header for 64-bit ELF binaries.
 *
 * Describes each section within an ELF64 file, including its type, flags,
 * memory layout, and linkage information.
 */
typedef struct {
  Elf64_Word	sh_name;      /**< Offset to the section name in the string table. */
  Elf64_Word	sh_type;      /**< Section type (e.g., SHT_PROGBITS, SHT_SYMTAB). */
  Elf64_Xword	sh_flags;     /**< Section attributes (e.g., SHF_WRITE, SHF_ALLOC). */
  Elf64_Addr	sh_addr;      /**< Virtual address in memory (for loaded sections). */
  Elf64_Off	sh_offset;      /**< Offset of the section in the file. */  
  Elf64_Xword	sh_size;      /**< Size of the section in bytes. */
  Elf64_Word	sh_link;      /**< Link to another section (e.g., symbol table index). */
  Elf64_Word	sh_info;      /**< Extra information (e.g., index of related section). */
  Elf64_Xword	sh_addralign; /**< Address alignment constraints. */
  Elf64_Xword	sh_entsize;   /**< Entry size if section holds a table of fixed-size entries. */
} Elf64_Shdr;



#define SHN_UNDEF        0     /**< Undefined section header. */
#define SHN_LORESERVE    0xff00 /**< Lower bound for reserved section indices. */
#define SHN_LOPROC       0xff00 /**< Lower bound for processor-specific section indices. */
#define SHN_BEFORE       0xff00 /**< Section that appears before the others in a list. */

#define SHN_AFTER        0xff01 /**< Section that appears after the others in a list. */

#define SHN_HIPROC       0xff1f /**< Upper bound for processor-specific section indices. */
#define SHN_LOOS         0xff20 /**< Lower bound for OS-specific section indices. */
#define SHN_HIOS         0xff3f /**< Upper bound for OS-specific section indices. */
#define SHN_ABS          0xfff1 /**< Absolute section index (not relocated). */
#define SHN_COMMON       0xfff2 /**< Common symbols section. */
#define SHN_XINDEX       0xffff /**< Extended section index (index stored in section header). */
#define SHN_HIRESERVE    0xffff /**< Upper bound for reserved section indices. */



#define SHT_NULL            0         /**< No section header. */
#define SHT_PROGBITS        1         /**< Program data section. */
#define SHT_SYMTAB          2         /**< Symbol table section. */
#define SHT_STRTAB          3         /**< String table section. */
#define SHT_RELA            4         /**< Relocation entries with addends. */
#define SHT_HASH            5         /**< Symbol hash table section. */
#define SHT_DYNAMIC         6         /**< Dynamic linking information section. */
#define SHT_NOTE            7         /**< Notes section. */
#define SHT_NOBITS          8         /**< Section that contains no data. */
#define SHT_REL             9         /**< Relocation entries (no addends). */
#define SHT_SHLIB           10        /**< Reserved for future use. */
#define SHT_DYNSYM          11        /**< Dynamic symbol table section. */
#define SHT_INIT_ARRAY      14        /**< Section containing initialization functions. */
#define SHT_FINI_ARRAY      15        /**< Section containing finalization functions. */
#define SHT_PREINIT_ARRAY   16        /**< Section containing pre-initialization functions. */
#define SHT_GROUP           17        /**< Section containing groupings of sections. */
#define SHT_SYMTAB_SHNDX    18        /**< Section index in symbol table. */
#define SHT_RELR            19        /**< Relocation entries with relative addends. */
#define SHT_NUM             20        /**< Number of section types. */
#define SHT_LOOS            0x60000000 /**< Lower bound for OS-specific section types. */
#define SHT_GNU_ATTRIBUTES  0x6ffffff5 /**< Section containing GNU attributes. */
#define SHT_GNU_HASH        0x6ffffff6 /**< Section containing GNU hash table. */
#define SHT_GNU_LIBLIST     0x6ffffff7 /**< Section containing GNU library list. */
#define SHT_CHECKSUM        0x6ffffff8 /**< Section containing checksum information. */
#define SHT_LOSUNW          0x6ffffffa /**< Lower bound for Sun-specific section types. */
#define SHT_SUNW_move       0x6ffffffa /**< Sun-specific section for move information. */
#define SHT_SUNW_COMDAT     0x6ffffffb /**< Sun-specific section for COMDAT symbols. */
#define SHT_SUNW_syminfo    0x6ffffffc /**< Sun-specific section for symbol information. */
#define SHT_GNU_verdef      0x6ffffffd /**< Section containing GNU version definitions. */
#define SHT_GNU_verneed     0x6ffffffe /**< Section containing GNU version needs. */
#define SHT_GNU_versym      0x6fffffff /**< Section containing GNU version symbols. */
#define SHT_HISUNW          0x6fffffff /**< Upper bound for Sun-specific section types. */
#define SHT_HIOS            0x6fffffff /**< Upper bound for OS-specific section types. */
#define SHT_LOPROC          0x70000000 /**< Lower bound for processor-specific section types. */
#define SHT_HIPROC          0x7fffffff /**< Upper bound for processor-specific section types. */
#define SHT_LOUSER          0x80000000 /**< Lower bound for user-defined section types. */
#define SHT_HIUSER          0x8fffffff /**< Upper bound for user-defined section types. */

#define SHF_WRITE              (1 << 0)  /**< Section contains writable data. */
#define SHF_ALLOC              (1 << 1)  /**< Section is allocated in memory. */
#define SHF_EXECINSTR          (1 << 2)  /**< Section contains executable instructions. */
#define SHF_MERGE              (1 << 4)  /**< Section can be merged. */
#define SHF_STRINGS            (1 << 5)  /**< Section contains null-terminated strings. */
#define SHF_INFO_LINK          (1 << 6)  /**< Section has associated information link. */
#define SHF_LINK_ORDER         (1 << 7)  /**< Section has order information for linking. */
#define SHF_OS_NONCONFORMING   (1 << 8)  /**< Section is non-conforming for the OS. */

#define SHF_GROUP             (1 << 9)   /**< Section is part of a group. */
#define SHF_TLS               (1 << 10)  /**< Section contains Thread-Local Storage (TLS) data. */
#define SHF_COMPRESSED        (1 << 11)  /**< Section is compressed. */
#define SHF_MASKOS            0x0ff00000 /**< OS-specific section flags mask. */
#define SHF_MASKPROC          0xf0000000 /**< Processor-specific section flags mask. */
#define SHF_ORDERED           (1 << 30)  /**< Section is ordered (e.g., initialization). */
#define SHF_EXCLUDE           (1U << 31)  /**< Section is excluded from linking. */

/**
 * @struct Elf32_Chdr
 * @brief Compressed section header for 32-bit ELF binaries.
 *
 * Describes the compression details of a section in ELF32 format.
 * Used when a section is marked with SHF_COMPRESSED.
 */
typedef struct {
  Elf32_Word	ch_type;      /**< Compression format type (e.g., ELFCOMPRESS_ZLIB). */
  Elf32_Word	ch_size;      /**< Uncompressed data size in bytes. */
  Elf32_Word	ch_addralign; /**< Alignment of uncompressed data. */
} Elf32_Chdr;

/**
 * @struct Elf64_Chdr
 * @brief Compressed section header for 64-bit ELF binaries.
 *
 * Describes the compression details of a section in ELF64 format.
 * Used when a section is marked with SHF_COMPRESSED.
 */
typedef struct {
  Elf64_Word	ch_type;      /**< Compression format type (e.g., ELFCOMPRESS_ZLIB). */
  Elf64_Word	ch_reserved;  /**< Reserved, must be zero. */
  Elf64_Xword	ch_size;      /**< Uncompressed data size in bytes. */
  Elf64_Xword	ch_addralign; /**< Alignment of uncompressed data. */
} Elf64_Chdr;

#define ELFCOMPRESS_ZLIB      1               /**< Zlib compression for ELF sections. */
#define ELFCOMPRESS_LOOS      0x60000000      /**< Lower bound for OS-specific compression flags. */
#define ELFCOMPRESS_HIOS      0x6fffffff      /**< Upper bound for OS-specific compression flags. */
#define ELFCOMPRESS_LOPROC    0x70000000      /**< Lower bound for processor-specific compression flags. */
#define ELFCOMPRESS_HIPROC    0x7fffffff      /**< Upper bound for processor-specific compression flags. */

#define GRP_COMDAT            0x1             /**< Identifies a COMDAT group for section merging. */


/**
 * @struct Elf32_Sym
 * @brief Symbol table entry for 32-bit ELF binaries.
 *
 * Describes a symbol's name, value, size, and other attributes used in linking.
 */
typedef struct {
  Elf32_Word	st_name;    /**< Symbol name (index into string table). */
  Elf32_Addr	st_value;   /**< Symbol value (address). */
  Elf32_Word	st_size;    /**< Size of the symbol. */
  unsigned char	st_info;  /**< Symbol type and binding attributes. */
  unsigned char	st_other; /**< Symbol visibility. */
  Elf32_Section	st_shndx;
} Elf32_Sym;

/**
 * @struct Elf64_Sym
 * @brief Symbol table entry for 64-bit ELF binaries.
 *
 * Describes a symbol's name, value, size, and other attributes used in linking.
 */
typedef struct {
  Elf64_Word	st_name;    /**< Symbol name (index into string table). */
  unsigned char	st_info;  /**< Symbol type and binding attributes. */
  unsigned char st_other; /**< Symbol visibility. */
  Elf64_Section	st_shndx; /**< Section index associated with the symbol. */
  Elf64_Addr	st_value;   /**< Symbol value (address). */
  Elf64_Xword	st_size;    /**< Size of the symbol. */
} Elf64_Sym;

/**
 * @struct Elf32_Syminfo
 * @brief Auxiliary symbol information for 32-bit ELF binaries.
 *
 * Provides additional linking information such as symbol bindings to other symbols.
 */
typedef struct {
  Elf32_Half si_boundto; /**< Index of the related symbol. */
  Elf32_Half si_flags;   /**< Flags providing additional symbol info. */
} Elf32_Syminfo;

/**
 * @struct Elf64_Syminfo
 * @brief Auxiliary symbol information for 64-bit ELF binaries.
 *
 * Provides additional linking information such as symbol bindings to other symbols.
 */
typedef struct {
  Elf64_Half si_boundto; /**< Index of the related symbol. */
  Elf64_Half si_flags;   /**< Flags providing additional symbol info. */
} Elf64_Syminfo;

#define SYMINFO_BT_SELF        0xffff  /**< SymInfo backtrace value for the symbol itself. */
#define SYMINFO_BT_PARENT      0xfffe  /**< SymInfo backtrace value for the parent symbol. */
#define SYMINFO_BT_LOWRESERVE  0xff00  /**< Reserved values for lower range of SymInfo backtrace. */

#define SYMINFO_FLG_DIRECT     0x0001  /**< Flag indicating direct symbol information. */
#define SYMINFO_FLG_PASSTHRU   0x0002  /**< Flag indicating pass-through symbol information. */
#define SYMINFO_FLG_COPY       0x0004  /**< Flag indicating symbol should be copied. */
#define SYMINFO_FLG_LAZYLOAD   0x0008  /**< Flag indicating lazy loading of the symbol. */

#define SYMINFO_NONE           0       /**< No symbol information. */
#define SYMINFO_CURRENT        1       /**< Current symbol information. */
#define SYMINFO_NUM            2       /**< Total number of symbol information types. */

#define ELF32_ST_BIND(val)     (((unsigned char) (val)) >> 4)  /**< Extracts binding type from ELF32 symbol info. */
#define ELF32_ST_TYPE(val)     ((val) & 0xf)                   /**< Extracts type from ELF32 symbol info. */
#define ELF32_ST_INFO(bind, type) (((bind) << 4) + ((type) & 0xf))  /**< Combines binding and type into ELF32 symbol info. */

#define ELF64_ST_BIND(val)     ELF32_ST_BIND (val)   /**< Extracts binding type from ELF64 symbol info. */
#define ELF64_ST_TYPE(val)     ELF32_ST_TYPE (val)   /**< Extracts type from ELF64 symbol info. */
#define ELF64_ST_INFO(bind, type) ELF32_ST_INFO ((bind), (type))  /**< Combines binding and type into ELF64 symbol info. */

#define STB_LOCAL       0   /**< Symbol binding type: Local symbol. */
#define STB_GLOBAL      1   /**< Symbol binding type: Global symbol. */
#define STB_WEAK        2   /**< Symbol binding type: Weak symbol. */
#define STB_NUM         3   /**< Number of symbol binding types. */
#define STB_LOOS        10  /**< Symbol binding type: OS-specific low bound. */
#define STB_GNU_UNIQUE  10  /**< Symbol binding type: GNU unique symbol. */
#define STB_HIOS        12  /**< Symbol binding type: OS-specific high bound. */
#define STB_LOPROC      13  /**< Symbol binding type: Processor-specific low bound. */
#define STB_HIPROC      15  /**< Symbol binding type: Processor-specific high bound. */

#define STT_NOTYPE      0   /**< Symbol type: No type. */
#define STT_OBJECT      1   /**< Symbol type: Data object. */
#define STT_FUNC        2   /**< Symbol type: Function. */
#define STT_SECTION     3   /**< Symbol type: Section. */
#define STT_FILE        4   /**< Symbol type: Source file. */
#define STT_COMMON      5   /**< Symbol type: Common symbol. */
#define STT_TLS         6   /**< Symbol type: Thread-local storage. */
#define STT_NUM         7   /**< Number of symbol types. */
#define STT_LOOS        10  /**< Symbol type: OS-specific low bound. */
#define STT_GNU_IFUNC   10  /**< Symbol type: GNU indirect function. */
#define STT_HIOS        12  /**< Symbol type: OS-specific high bound. */
#define STT_LOPROC      13  /**< Symbol type: Processor-specific low bound. */
#define STT_HIPROC      15  /**< Symbol type: Processor-specific high bound. */

#define STN_UNDEF       0   /**< Undefined symbol index. */

#define ELF32_ST_VISIBILITY(o) ((o) & 0x03)   /**< Extracts visibility from ELF32 symbol info. */
#define ELF64_ST_VISIBILITY(o) ELF32_ST_VISIBILITY (o)   /**< Extracts visibility from ELF64 symbol info. */

#define STV_DEFAULT     0   /**< Symbol visibility: Default visibility. */
#define STV_INTERNAL    1   /**< Symbol visibility: Internal visibility. */
#define STV_HIDDEN      2   /**< Symbol visibility: Hidden visibility. */
#define STV_PROTECTED   3   /**< Symbol visibility: Protected visibility. */


/**
 * @struct Elf32_Rel
 * @brief Structure representing a relocation entry without addend (32-bit).
 *
 * This structure is used for relocation entries in sections of type `SHT_REL`.
 */
typedef struct {
  Elf32_Addr	r_offset; /**< Location to apply the relocation action. */
  Elf32_Word	r_info;   /**< Symbol table index and type of relocation. */
} Elf32_Rel;


/**
 * @struct Elf64_Rel
 * @brief Structure representing a relocation entry without addend (64-bit).
 *
 * This structure is used for relocation entries in sections of type `SHT_REL`.
 */
typedef struct {
  Elf64_Addr	r_offset; /**< Location to apply the relocation action. */
  Elf64_Xword	r_info;   /**< Symbol table index and type of relocation. */
} Elf64_Rel;


/**
 * @struct Elf32_Rela
 * @brief Structure representing a relocation entry with addend (32-bit).
 *
 * This structure is used for relocation entries in sections of type `SHT_RELA`.
 */
typedef struct {
  Elf32_Addr	r_offset; /**< Location to apply the relocation action. */
  Elf32_Word	r_info;   /**< Symbol table index and type of relocation. */
  Elf32_Sword	r_addend; /**< Constant addend used to compute value. */
} Elf32_Rela;

/**
 * @struct Elf64_Rela
 * @brief Structure representing a relocation entry with addend (64-bit).
 *
 * This structure is used for relocation entries in sections of type `SHT_RELA`.
 */
typedef struct {
  Elf64_Addr	r_offset;   /**< Location to apply the relocation action. */
  Elf64_Xword	r_info;     /**< Symbol table index and type of relocation. */
  Elf64_Sxword	r_addend; /**< Constant addend used to compute value. */
} Elf64_Rela;



#define ELF32_R_SYM(val)         ((val) >> 8)  /**< Extracts the symbol index from a 32-bit relocation entry. */
#define ELF32_R_TYPE(val)        ((val) & 0xff) /**< Extracts the relocation type from a 32-bit relocation entry. */
#define ELF32_R_INFO(sym, type)  (((sym) << 8) + ((type) & 0xff))  /**< Combines symbol index and relocation type into a 32-bit relocation entry. */

#define ELF64_R_SYM(i)           ((i) >> 32)  /**< Extracts the symbol index from a 64-bit relocation entry. */
#define ELF64_R_TYPE(i)          ((i) & 0xffffffff)  /**< Extracts the relocation type from a 64-bit relocation entry. */
#define ELF64_R_INFO(sym,type)   ((((Elf64_Xword) (sym)) << 32) + (type))  /**< Combines symbol index and relocation type into a 64-bit relocation entry. */


/**
 * @struct Elf32_Phdr
 * @brief Program header for 32-bit ELF binaries.
 *
 * Describes a segment to be loaded into memory, including its offset, size,
 * and memory attributes.
 */
typedef struct {
  Elf32_Word	p_type;   /**< Type of segment. */
  Elf32_Off	p_offset;   /**< Offset of the segment in the file image. */
  Elf32_Addr	p_vaddr;  /**< Virtual address of the segment in memory. */
  Elf32_Addr	p_paddr;  /**< Physical address of the segment (unused on most systems). */
  Elf32_Word	p_filesz; /**< Size of the segment in the file image. */
  Elf32_Word	p_memsz;  /**< Size of the segment in memory. */
  Elf32_Word	p_flags;  /**< Segment flags (e.g., read/write/execute). */
  Elf32_Word	p_align;  /**< Segment alignment (must be a power of 2). */
} Elf32_Phdr;

/**
 * @struct Elf64_Phdr
 * @brief Program header for 64-bit ELF binaries.
 *
 * Describes a segment to be loaded into memory, including its offset, size,
 * and memory attributes.
 */
typedef struct {
  Elf64_Word	p_type;   /**< Type of segment. */
  Elf64_Word	p_flags;  /**< Segment flags (e.g., read/write/execute). */
  Elf64_Off	p_offset;   /**< Offset of the segment in the file image. */
  Elf64_Addr	p_vaddr;  /**< Virtual address of the segment in memory. */
  Elf64_Addr	p_paddr;  /**< Physical address of the segment (unused on most systems). */
  Elf64_Xword	p_filesz; /**< Size of the segment in the file image. */
  Elf64_Xword	p_memsz;  /**< Size of the segment in memory. */
  Elf64_Xword	p_align;  /**< Segment alignment (must be a power of 2). */
} Elf64_Phdr;



#define PT_NULL             0  /**< Program header type: null (unused entry). */
#define PT_LOAD             1  /**< Program header type: loadable segment. */
#define PT_DYNAMIC          2  /**< Program header type: dynamic linking information. */
#define PT_INTERP           3  /**< Program header type: interpreter path. */
#define PT_NOTE             4  /**< Program header type: auxiliary information. */
#define PT_SHLIB            5  /**< Program header type: reserved for system use. */
#define PT_PHDR             6  /**< Program header type: program header table itself. */
#define PT_TLS              7  /**< Program header type: thread-local storage. */
#define PT_NUM              8  /**< Number of program header types. */
#define PT_LOOS             0x60000000  /**< Program header type: OS-specific range start. */
#define PT_GNU_EH_FRAME    0x6474e550  /**< Program header type: GNU exception handling frame. */
#define PT_GNU_STACK        0x6474e551  /**< Program header type: GNU stack properties. */
#define PT_GNU_RELRO        0x6474e552  /**< Program header type: GNU read-only relocation. */
#define PT_GNU_PROPERTY     0x6474e553  /**< Program header type: GNU property. */
#define PT_LOSUNW           0x6ffffffa  /**< Program header type: Sun Microsystems-specific range start. */
#define PT_SUNWBSS          0x6ffffffa  /**< Program header type: Sun writeable BSS section. */
#define PT_SUNWSTACK        0x6ffffffb  /**< Program header type: Sun stack segment. */
#define PT_HISUNW           0x6fffffff  /**< Program header type: Sun Microsystems-specific range end. */
#define PT_HIOS             0x6fffffff  /**< Program header type: high range end for OS-specific types. */
#define PT_LOPROC           0x70000000  /**< Program header type: processor-specific range start. */
#define PT_HIPROC           0x7fffffff  /**< Program header type: processor-specific range end. */

#define PN_XNUM            0xffff  /**< Special program header index for extended sections. */

#define PF_X                (1 << 0)  /**< Segment is executable. */
#define PF_W                (1 << 1)  /**< Segment is writable. */
#define PF_R                (1 << 2)  /**< Segment is readable. */
#define PF_MASKOS           0x0ff00000  /**< OS-specific segment flags mask. */
#define PF_MASKPROC         0xf0000000  /**< Processor-specific segment flags mask. */




#define NT_PRSTATUS         1  /**< Type of note: Process status. */
#define NT_PRFPREG          2  /**< Type of note: Floating-point registers. */
#define NT_FPREGSET         2  /**< Type of note: Alias for NT_PRFPREG. */
#define NT_PRPSINFO         3  /**< Type of note: Process status information. */
#define NT_PRXREG           4  /**< Type of note: Extended registers. */
#define NT_TASKSTRUCT       4  /**< Type of note: Task struct. */
#define NT_PLATFORM         5  /**< Type of note: Platform-specific information. */
#define NT_AUXV             6  /**< Type of note: Auxiliary vector. */
#define NT_GWINDOWS         7  /**< Type of note: GNU window registers. */
#define NT_ASRS             8  /**< Type of note: Architecture-specific registers. */
#define NT_PSTATUS          10 /**< Type of note: Process status (alternate). */
#define NT_PSINFO           13 /**< Type of note: Process status info (alternate). */
#define NT_PRCRED           14 /**< Type of note: Process credentials. */
#define NT_UTSNAME          15 /**< Type of note: UTS name (system name). */
#define NT_LWPSTATUS        16 /**< Type of note: LWP (light-weight process) status. */
#define NT_LWPSINFO         17 /**< Type of note: LWP status information. */
#define NT_PRFPXREG         20 /**< Type of note: Floating-point extended registers. */
#define NT_SIGINFO          0x53494749 /**< Type of note: Signal information. */
#define NT_FILE             0x46494c45 /**< Type of note: File information. */
#define NT_PRXFPREG         0x46e62b7f /**< Type of note: Extended floating-point registers. */
#define NT_PPC_VMX          0x100 /**< Type of note: PowerPC VMX registers. */
#define NT_PPC_SPE          0x101 /**< Type of note: PowerPC SPE registers. */
#define NT_PPC_VSX          0x102 /**< Type of note: PowerPC VSX registers. */
#define NT_PPC_TAR          0x103 /**< Type of note: PowerPC TAR register. */
#define NT_PPC_PPR          0x104 /**< Type of note: PowerPC PPR register. */
#define NT_PPC_DSCR         0x105 /**< Type of note: PowerPC DSCR register. */
#define NT_PPC_EBB          0x106 /**< Type of note: PowerPC EBB registers. */
#define NT_PPC_PMU          0x107 /**< Type of note: PowerPC PMU registers. */
#define NT_PPC_TM_CGPR      0x108 /**< Type of note: PowerPC TM CGPR registers. */
#define NT_PPC_TM_CFPR      0x109 /**< Type of note: PowerPC TM CFPR registers. */
#define NT_PPC_TM_CVMX      0x10a /**< Type of note: PowerPC TM CVMX registers. */
#define NT_PPC_TM_CVSX      0x10b /**< Type of note: PowerPC TM CVSX registers. */
#define NT_PPC_TM_SPR       0x10c /**< Type of note: PowerPC TM SPR registers. */
#define NT_PPC_TM_CTAR      0x10d /**< Type of note: PowerPC TM CTAR registers. */
#define NT_PPC_TM_CPPR      0x10e /**< Type of note: PowerPC TM CPPR registers. */
#define NT_PPC_TM_CDSCR     0x10f /**< Type of note: PowerPC TM CDSCR registers. */
#define NT_386_TLS           0x200 /**< Type of note: x86 TLS (thread-local storage). */
#define NT_386_IOPERM        0x201 /**< Type of note: x86 I/O permissions. */
#define NT_X86_XSTATE        0x202 /**< Type of note: x86 extended state. */
#define NT_S390_HIGH_GPRS    0x300 /**< Type of note: S390 high GPRS registers. */
#define NT_S390_TIMER        0x301 /**< Type of note: S390 timer registers. */
#define NT_S390_TODCMP       0x302 /**< Type of note: S390 TOD comparator registers. */
#define NT_S390_TODPREG      0x303 /**< Type of note: S390 TOD preg registers. */
#define NT_S390_CTRS         0x304 /**< Type of note: S390 control registers. */
#define NT_S390_PREFIX       0x305 /**< Type of note: S390 prefix registers. */
#define NT_S390_LAST_BREAK   0x306 /**< Type of note: S390 last break registers. */
#define NT_S390_SYSTEM_CALL  0x307 /**< Type of note: S390 system call registers. */
#define NT_S390_TDB          0x308 /**< Type of note: S390 TDB registers. */
#define NT_S390_VXRS_LOW     0x309 /**< Type of note: S390 low VXRS registers. */
#define NT_S390_VXRS_HIGH    0x30a /**< Type of note: S390 high VXRS registers. */
#define NT_S390_GS_CB        0x30b /**< Type of note: S390 GS CB registers. */
#define NT_S390_GS_BC        0x30c /**< Type of note: S390 GS BC registers. */
#define NT_S390_RI_CB        0x30d /**< Type of note: S390 RI CB registers. */
#define NT_ARM_VFP           0x400 /**< Type of note: ARM VFP registers. */
#define NT_ARM_TLS           0x401 /**< Type of note: ARM TLS registers. */
#define NT_ARM_HW_BREAK      0x402 /**< Type of note: ARM hardware breakpoints. */
#define NT_ARM_HW_WATCH      0x403 /**< Type of note: ARM hardware watchpoints. */
#define NT_ARM_SYSTEM_CALL   0x404 /**< Type of note: ARM system call registers. */
#define NT_ARM_SVE           0x405 /**< Type of note: ARM SVE registers. */
#define NT_ARM_PAC_MASK      0x406 /**< Type of note: ARM PAC mask. */
#define NT_ARM_PACA_KEYS     0x407 /**< Type of note: ARM PAC A keys. */
#define NT_ARM_PACG_KEYS     0x408 /**< Type of note: ARM PAC G keys. */
#define NT_ARM_TAGGED_ADDR_CTRL 0x409 /**< Type of note: ARM tagged address control. */
#define NT_ARM_PAC_ENABLED_KEYS 0x40a /**< Type of note: ARM PAC enabled keys. */
#define NT_METAG_CBUF        0x500 /**< Type of note: METAG CBUF registers. */
#define NT_METAG_RPIPE       0x501 /**< Type of note: METAG RPIPE registers. */
#define NT_METAG_TLS         0x502 /**< Type of note: METAG TLS registers. */
#define NT_ARC_V2            0x600 /**< Type of note: ARC V2 registers. */
#define NT_VMCOREDD          0x700 /**< Type of note: VM core dump. */
#define NT_MIPS_DSP          0x800 /**< Type of note: MIPS DSP registers. */
#define NT_MIPS_FP_MODE      0x801 /**< Type of note: MIPS FP mode. */
#define NT_MIPS_MSA          0x802 /**< Type of note: MIPS MSA registers. */
#define NT_VERSION           1   /**< Type of note: Version information. */



/**
 * @struct Elf32_Dyn
 * @brief Dynamic section entry for 32-bit ELF.
 *
 * Represents an entry in the dynamic section, which provides information
 * used at runtime by the dynamic linker.
 */
typedef struct {
  Elf32_Sword d_tag;  /**< Type of dynamic entry. */
  union {
    Elf32_Word d_val; /**< Integer value. */
    Elf32_Addr d_ptr; /**< Address value. */
  } d_un;
} Elf32_Dyn;

/**
 * @struct Elf64_Dyn
 * @brief Dynamic section entry for 64-bit ELF.
 *
 * Represents an entry in the dynamic section for 64-bit binaries.
 */
typedef struct {
  Elf64_Sxword d_tag;  /**< Type of dynamic entry. */
  union {
    Elf64_Xword d_val; /**< Integer value. */
    Elf64_Addr d_ptr;  /**< Address value. */
  } d_un;
} Elf64_Dyn;



#define DT_NULL             0  /**< Tag for null entry. */
#define DT_NEEDED           1  /**< Tag for needed library. */
#define DT_PLTRELSZ         2  /**< Tag for PLT relocation size. */
#define DT_PLTGOT           3  /**< Tag for PLT GOT entry. */
#define DT_HASH             4  /**< Tag for hash table. */
#define DT_STRTAB           5  /**< Tag for string table. */
#define DT_SYMTAB           6  /**< Tag for symbol table. */
#define DT_RELA             7  /**< Tag for relocation entries. */
#define DT_RELASZ           8  /**< Tag for relocation size. */
#define DT_RELAENT          9  /**< Tag for size of one relocation entry. */
#define DT_STRSZ            10 /**< Tag for string table size. */
#define DT_SYMENT           11 /**< Tag for symbol table entry size. */
#define DT_INIT             12 /**< Tag for initialization function address. */
#define DT_FINI             13 /**< Tag for finalization function address. */
#define DT_SONAME           14 /**< Tag for shared object name. */
#define DT_RPATH            15 /**< Tag for runtime library search path. */
#define DT_SYMBOLIC         16 /**< Tag for symbolic linking. */
#define DT_REL              17 /**< Tag for relocation entries. */
#define DT_RELSZ            18 /**< Tag for relocation entries size. */
#define DT_RELENT           19 /**< Tag for relocation entry size. */
#define DT_PLTREL           20 /**< Tag for PLT relocation type. */
#define DT_DEBUG            21 /**< Tag for debugging information. */
#define DT_TEXTREL          22 /**< Tag for text relocations. */
#define DT_JMPREL           23 /**< Tag for jump relocation entries. */
#define DT_BIND_NOW         24 /**< Tag for binding at load time. */
#define DT_INIT_ARRAY       25 /**< Tag for initialization array. */
#define DT_FINI_ARRAY       26 /**< Tag for finalization array. */
#define DT_INIT_ARRAYSZ     27 /**< Tag for initialization array size. */
#define DT_FINI_ARRAYSZ     28 /**< Tag for finalization array size. */
#define DT_RUNPATH          29 /**< Tag for runtime library search path. */
#define DT_FLAGS            30 /**< Tag for dynamic flags. */
#define DT_ENCODING         32 /**< Tag for encoding. */
#define DT_PREINIT_ARRAY    32 /**< Tag for pre-initialization array. */
#define DT_PREINIT_ARRAYSZ  33 /**< Tag for pre-initialization array size. */
#define DT_SYMTAB_SHNDX     34 /**< Tag for symbol table section index. */
#define DT_RELRSZ           35 /**< Tag for relocation entries size. */
#define DT_RELR             36 /**< Tag for relative relocations. */
#define DT_RELRENT          37 /**< Tag for relative relocation entry size. */
#define DT_NUM              38 /**< Number of dynamic tags. */
#define DT_LOOS             0x6000000d /**< Tag for OS-specific dynamic tag. */
#define DT_HIOS             0x6ffff000 /**< Tag for high end of OS-specific dynamic tags. */
#define DT_LOPROC           0x70000000 /**< Tag for low end of processor-specific dynamic tags. */
#define DT_HIPROC           0x7fffffff /**< Tag for high end of processor-specific dynamic tags. */
#define DT_PROCNUM          DT_MIPS_NUM /**< Tag for processor-specific dynamic tag number. */

#define DT_VALRNGLO         0x6ffffd00 /**< Tag for lower range of value tags. */
#define DT_GNU_PRELINKED    0x6ffffdf5 /**< Tag for GNU prelinked object. */
#define DT_GNU_CONFLICTSZ   0x6ffffdf6 /**< Tag for size of conflicts in GNU prelinked object. */
#define DT_GNU_LIBLISTSZ    0x6ffffdf7 /**< Tag for size of library list in GNU prelinked object. */
#define DT_CHECKSUM         0x6ffffdf8 /**< Tag for checksum. */
#define DT_PLTPADSZ         0x6ffffdf9 /**< Tag for padding size for PLT. */
#define DT_MOVEENT          0x6ffffdfa /**< Tag for move entries. */
#define DT_MOVESZ           0x6ffffdfb /**< Tag for size of move entries. */
#define DT_FEATURE_1        0x6ffffdfc /**< Tag for feature flags 1. */
#define DT_POSFLAG_1        0x6ffffdfd /**< Tag for position-independent code flag 1. */

#define DT_SYMINSZ          0x6ffffdfe /**< Tag for size of symbol information. */
#define DT_SYMINENT         0x6ffffdff /**< Tag for symbol information entry size. */
#define DT_VALRNGHI         0x6ffffdff /**< Tag for upper range of value tags. */
#define DT_VALTAGIDX(tag)   (DT_VALRNGHI - (tag)) /**< Compute tag index for values. */
#define DT_VALNUM           12 /**< Number of value tags. */

#define DT_ADDRRNGLO        0x6ffffe00 /**< Tag for lower range of address tags. */
#define DT_GNU_HASH         0x6ffffef5 /**< Tag for GNU hash table. */
#define DT_TLSDESC_PLT      0x6ffffef6 /**< Tag for TLS descriptor in PLT. */
#define DT_TLSDESC_GOT      0x6ffffef7 /**< Tag for TLS descriptor in GOT. */
#define DT_GNU_CONFLICT     0x6ffffef8 /**< Tag for conflict entries in GNU prelinked object. */
#define DT_GNU_LIBLIST      0x6ffffef9 /**< Tag for library list in GNU prelinked object. */
#define DT_CONFIG           0x6ffffefa /**< Tag for configuration. */
#define DT_DEPAUDIT         0x6ffffefb /**< Tag for dependency audit. */
#define DT_AUDIT            0x6ffffefc /**< Tag for audit entries. */
#define DT_PLTPAD           0x6ffffefd /**< Tag for padding in PLT. */
#define DT_MOVETAB          0x6ffffefe /**< Tag for move tab. */
#define DT_SYMINFO          0x6ffffeff /**< Tag for symbol information. */
#define DT_ADDRRNGHI        0x6ffffeff /**< Tag for upper range of address tags. */
#define DT_ADDRTAGIDX(tag)  (DT_ADDRRNGHI - (tag)) /**< Compute tag index for addresses. */
#define DT_ADDRNUM          11 /**< Number of address tags. */



#define DT_VERSYM           0x6ffffff0 /**< Tag for version symbol table. */

#define DT_RELACOUNT        0x6ffffff9 /**< Tag for number of RELA relocations. */
#define DT_RELCOUNT         0x6ffffffa /**< Tag for number of REL relocations. */


#define DT_FLAGS_1          0x6ffffffb /**< Tag for additional flags. */
#define DT_VERDEF           0x6ffffffc /**< Tag for version definition. */

#define DT_VERDEFNUM        0x6ffffffd /**< Tag for number of version definitions. */
#define DT_VERNEED          0x6ffffffe /**< Tag for version need. */

#define DT_VERNEEDNUM       0x6fffffff /**< Tag for number of version needs. */
#define DT_VERSIONTAGIDX(tag) (DT_VERNEEDNUM - (tag)) /**< Compute tag index for versions. */
#define DT_VERSIONTAGNUM    16 /**< Number of version tags. */



#define DT_AUXILIARY        0x7ffffffd /**< Tag for auxiliary entries. */
#define DT_FILTER           0x7fffffff /**< Tag for filter entries. */
#define DT_EXTRATAGIDX(tag) ((Elf32_Word)-((Elf32_Sword)(tag) << 1 >> 1) - 1) /**< Compute extra tag index. */
#define DT_EXTRANUM         3 /**< Number of extra tags. */


#define DF_ORIGIN           0x00000001  /**< Indicates the presence of origin in the dynamic section. */
#define DF_SYMBOLIC         0x00000002  /**< Indicates that the dynamic object is symbolically linked. */
#define DF_TEXTREL          0x00000004  /**< Marks that the dynamic object has text relocations. */
#define DF_BIND_NOW         0x00000008  /**< Indicates that the dynamic linking should happen immediately. */
#define DF_STATIC_TLS       0x00000010  /**< Marks the dynamic object as having static thread-local storage. */

#define DF_1_NOW            0x00000001  /**< Indicates immediate resolution of dynamic symbols. */
#define DF_1_GLOBAL         0x00000002  /**< Indicates the object is globally visible. */
#define DF_1_GROUP          0x00000004  /**< Marks the dynamic object as part of a group. */
#define DF_1_NODELETE       0x00000008  /**< Prevents deletion of the dynamic object after loading. */
#define DF_1_LOADFLTR       0x00000010  /**< Specifies that the object should load a filter. */
#define DF_1_INITFIRST      0x00000020  /**< Specifies that the object should be initialized first. */
#define DF_1_NOOPEN         0x00000040  /**< Indicates that the dynamic object should not be opened. */
#define DF_1_ORIGIN         0x00000080  /**< Indicates the use of the origin of the object. */
#define DF_1_DIRECT         0x00000100  /**< Marks the object for direct binding. */
#define DF_1_TRANS          0x00000200  /**< Marks the object for transitive linking. */
#define DF_1_INTERPOSE      0x00000400  /**< Specifies that the object interposes other objects. */
#define DF_1_NODEFLIB       0x00000800  /**< Indicates that default libraries should not be used. */
#define DF_1_NODUMP         0x00001000  /**< Prevents the object from being dumped. */
#define DF_1_CONFALT        0x00002000  /**< Indicates that the object has a configuration alternative. */
#define DF_1_ENDFILTEE      0x00004000  /**< Marks the object as an end filter. */
#define DF_1_DISPRELDNE     0x00008000  /**< Indicates that relocation has been deferred and needs to be resolved. */
#define DF_1_DISPRELPND     0x00010000  /**< Marks that the pending relocation is deferred. */
#define DF_1_NODIRECT       0x00020000  /**< Marks that direct linking should not be used. */
#define DF_1_IGNMULDEF      0x00040000  /**< Allows ignoring multiple definitions. */
#define DF_1_NOKSYMS        0x00080000  /**< Indicates that symbol tables should not be loaded. */
#define DF_1_NOHDR          0x00100000  /**< Specifies that headers should not be loaded. */
#define DF_1_EDITED         0x00200000  /**< Indicates that the object has been edited. */
#define DF_1_NORELOC        0x00400000  /**< Specifies that relocation is not needed. */
#define DF_1_SYMINTPOSE     0x00800000  /**< Marks that symbol interposition is used. */
#define DF_1_GLOBAUDIT      0x01000000  /**< Marks the object for global auditing. */
#define DF_1_SINGLETON      0x02000000  /**< Specifies that the object is a singleton. */
#define DF_1_STUB           0x04000000  /**< Marks the object as a stub. */
#define DF_1_PIE            0x08000000  /**< Indicates that the object is Position Independent Executable (PIE). */

#define DTF_1_PARINIT       0x00000001  /**< Marks that the object has parallel initialization. */
#define DTF_1_CONFEXP       0x00000002  /**< Marks that the object has a configuration export. */

#define DF_P1_LAZYLOAD      0x00000001  /**< Specifies that the object should be lazily loaded. */
#define DF_P1_GROUPPERM     0x00000002  /**< Marks the object as having group permissions. */



/**
 * @struct Elf32_Verdef
 * @brief Symbol version definition for 32-bit ELF.
 *
 * Describes the version of a defined symbol in the binary.
 */
typedef struct {
  Elf32_Half	vd_version; /**< Version of the structure format. */
  Elf32_Half	vd_flags;   /**< Version definition flags. */
  Elf32_Half	vd_ndx;     /**< Version index. */
  Elf32_Half	vd_cnt;     /**< Number of associated auxiliary entries. */
  Elf32_Word	vd_hash;    /**< Hash of the version name. */
  Elf32_Word	vd_aux;     /**< Offset to the first Verdaux entry. */
  Elf32_Word	vd_next;    /**< Offset to the next Verdef entry. */
} Elf32_Verdef;

/**
 * @struct Elf64_Verdef
 * @brief Symbol version definition for 64-bit ELF.
 *
 * Describes the version of a defined symbol in the binary.
 */
typedef struct {
  Elf64_Half	vd_version; /**< Version of the structure format. */
  Elf64_Half	vd_flags;   /**< Version definition flags. */
  Elf64_Half	vd_ndx;     /**< Version index. */
  Elf64_Half	vd_cnt;     /**< Number of associated auxiliary entries. */
  Elf64_Word	vd_hash;    /**< Hash of the version name. */
  Elf64_Word	vd_aux;     /**< Offset to the first Verdaux entry. */
  Elf64_Word	vd_next;    /**< Offset to the next Verdef entry. */
} Elf64_Verdef;



#define VER_DEF_NONE       0            /**< No version definition. */
#define VER_DEF_CURRENT    1            /**< Current version definition. */
#define VER_DEF_NUM        2            /**< Number of version definitions. */

#define VER_FLG_BASE       0x1          /**< Flag indicating base version. */
#define VER_FLG_WEAK       0x2          /**< Flag indicating weak version. */

#define VER_NDX_LOCAL      0            /**< Index for local version symbol. */
#define VER_NDX_GLOBAL     1            /**< Index for global version symbol. */
#define VER_NDX_LORESERVE  0xff00       /**< Lower reserved index range for versions. */
#define VER_NDX_ELIMINATE  0xff01       /**< Version index for elimination. */


/**
 * @struct Elf32_Verdaux
 * @brief Auxiliary version definition entry for 32-bit ELF.
 */
typedef struct {
  Elf32_Word	vda_name; /**< Offset to the version name string. */
  Elf32_Word	vda_next; /**< Offset to the next Verdaux entry. */
} Elf32_Verdaux;


/**
 * @struct Elf64_Verdaux
 * @brief Auxiliary version definition entry for 64-bit ELF.
 */
typedef struct {
  Elf64_Word	vda_name; /**< Offset to the version name string. */
  Elf64_Word	vda_next; /**< Offset to the next Verdaux entry. */
} Elf64_Verdaux;



/**
 * @struct Elf32_Verneed
 * @brief Symbol version dependency for 32-bit ELF.
 *
 * Describes the versions of undefined symbols that this binary needs.
 */
typedef struct {
  Elf32_Half	vn_version; /**< Version of the structure format. */
  Elf32_Half	vn_cnt;     /**< Number of associated auxiliary entries. */
  Elf32_Word	vn_file;    /**< Offset to the file name string. */
  Elf32_Word	vn_aux;     /**< Offset to the first Vernaux entry. */
  Elf32_Word	vn_next;    /**< Offset to the next Verneed entry. */
} Elf32_Verneed;

/**
 * @struct Elf64_Verneed
 * @brief Symbol version dependency for 64-bit ELF.
 *
 * Describes the versions of undefined symbols that this binary needs.
 */
typedef struct {
  Elf64_Half	vn_version; /**< Version of the structure format. */
  Elf64_Half	vn_cnt;     /**< Number of associated auxiliary entries. */
  Elf64_Word	vn_file;    /**< Offset to the file name string. */
  Elf64_Word	vn_aux;     /**< Offset to the first Vernaux entry. */
  Elf64_Word	vn_next;    /**< Offset to the next Verneed entry. */
} Elf64_Verneed;



#define VER_NEED_NONE     0            /**< No version needed. */
#define VER_NEED_CURRENT  1            /**< Current version needed. */
#define VER_NEED_NUM      2            /**< Number of version needs. */



/**
 * @struct Elf32_Vernaux
 * @brief Auxiliary version dependency entry for 32-bit ELF.
 *
 * Represents a version requirement for a specific symbol.
 */
typedef struct {
  Elf32_Word	vna_hash;  /**< Hash of the dependency version name. */
  Elf32_Half	vna_flags; /**< Version dependency flags. */
  Elf32_Half	vna_other; /**< Version index. */
  Elf32_Word	vna_name;  /**< Offset to version name string in string table. */
  Elf32_Word	vna_next;  /**< Offset to next Vernaux entry. */
} Elf32_Vernaux;

/**
 * @struct Elf64_Vernaux
 * @brief Auxiliary version dependency entry for 64-bit ELF.
 */
typedef struct {
  Elf64_Word	vna_hash;  /**< Hash of the dependency version name. */
  Elf64_Half	vna_flags; /**< Version dependency flags. */
  Elf64_Half	vna_other; /**< Version index. */
  Elf64_Word	vna_name;  /**< Offset to version name string in string table. */
  Elf64_Word	vna_next;  /**< Offset to next Vernaux entry. */
} Elf64_Vernaux;



#define VER_FLG_WEAK  0x2  /**< Flag indicating a weak version requirement. */



/**
 * @struct Elf32_auxv_t
 * @brief Auxiliary vector for 32-bit ELF.
 *
 * Contains key-value pairs passed from the kernel to the program during exec.
 */
typedef struct {
  uint32_t a_type;  /**< Entry type (e.g., AT_PHDR, AT_ENTRY). */
  union {
    uint32_t a_val; /**< Integer or address value. */
  } a_un;
} Elf32_auxv_t;

/**
 * @struct Elf64_auxv_t
 * @brief Auxiliary vector for 64-bit ELF.
 */
typedef struct {
  uint64_t a_type;  /**< Entry type (e.g., AT_PHDR, AT_ENTRY). */
  union {
    uint64_t a_val; /**< Integer or address value. */
  } a_un;
} Elf64_auxv_t;



#define AT_NULL          0    /**< Null value for auxiliary vector entry. */
#define AT_IGNORE        1    /**< Value to indicate the entry should be ignored. */
#define AT_EXECFD        2    /**< File descriptor of the executable. */
#define AT_PHDR          3    /**< Address of the program header. */
#define AT_PHENT         4    /**< Size of a program header table entry. */
#define AT_PHNUM         5    /**< Number of program header table entries. */
#define AT_PAGESZ        6    /**< Page size. */
#define AT_BASE          7    /**< Base address of the process. */
#define AT_FLAGS         8    /**< Flags associated with the process. */
#define AT_ENTRY         9    /**< Entry point of the executable. */
#define AT_NOTELF        10   /**< Indicator that the file is not an ELF. */
#define AT_UID           11   /**< User ID of the process. */
#define AT_EUID          12   /**< Effective user ID of the process. */
#define AT_GID           13   /**< Group ID of the process. */
#define AT_EGID          14   /**< Effective group ID of the process. */
#define AT_CLKTCK        17   /**< Clock ticks per second. */

#define AT_PLATFORM      15   /**< Platform string. */
#define AT_HWCAP         16   /**< Hardware capabilities of the system. */

#define AT_FPUCW         18   /**< Floating-point control word. */

#define AT_DCACHEBSIZE   19   /**< Size of the data cache. */
#define AT_ICACHEBSIZE   20   /**< Size of the instruction cache. */
#define AT_UCACHEBSIZE   21   /**< Size of the unified cache. */

#define AT_IGNOREPPC     22   /**< Ignore on PowerPC platforms. */

#define AT_SECURE        23   /**< Indicator that the process is running securely. */

#define AT_BASE_PLATFORM 24   /**< Base platform string. */

#define AT_RANDOM        25   /**< Address of the randomization base. */

#define AT_HWCAP2        26   /**< Extended hardware capabilities. */

#define AT_EXECFN        31   /**< Executable filename. */

#define AT_SYSINFO       32   /**< System information pointer. */
#define AT_SYSINFO_EHDR  33   /**< System information ELF header. */

#define AT_L1I_CACHESHAPE 34 /**< Shape of the L1 instruction cache. */
#define AT_L1D_CACHESHAPE 35 /**< Shape of the L1 data cache. */
#define AT_L2_CACHESHAPE 36  /**< Shape of the L2 cache. */
#define AT_L3_CACHESHAPE 37  /**< Shape of the L3 cache. */

#define AT_L1I_CACHESIZE 40  /**< Size of the L1 instruction cache. */
#define AT_L1I_CACHEGEOMETRY 41 /**< Geometry of the L1 instruction cache. */
#define AT_L1D_CACHESIZE 42  /**< Size of the L1 data cache. */
#define AT_L1D_CACHEGEOMETRY 43 /**< Geometry of the L1 data cache. */
#define AT_L2_CACHESIZE  44  /**< Size of the L2 cache. */
#define AT_L2_CACHEGEOMETRY 45 /**< Geometry of the L2 cache. */
#define AT_L3_CACHESIZE  46  /**< Size of the L3 cache. */
#define AT_L3_CACHEGEOMETRY 47 /**< Geometry of the L3 cache. */

#define AT_MINSIGSTKSZ   51   /**< Minimum stack size for signals. */

/**
 * @struct Elf32_Nhdr
 * @brief Note section header for 32-bit ELF.
 *
 * Used in PT_NOTE segments to store auxiliary information such as
 * build ID, ABI, etc.
 */
typedef struct {
  Elf32_Word n_namesz; /**< Size of the name field. */
  Elf32_Word n_descsz; /**< Size of the descriptor field. */
  Elf32_Word n_type;   /**< Note type. */
} Elf32_Nhdr;


/**
 * @struct Elf64_Nhdr
 * @brief Note section header for 64-bit ELF.
 */
typedef struct {
  Elf64_Word n_namesz; /**< Size of the name field. */
  Elf64_Word n_descsz; /**< Size of the descriptor field. */
  Elf64_Word n_type;   /**< Note type. */
} Elf64_Nhdr;




#define ELF_NOTE_SOLARIS    "SUNW Solaris"    /**< Solaris operating system identifier in ELF note. */
#define ELF_NOTE_GNU         "GNU"             /**< GNU operating system identifier in ELF note. */

#define ELF_NOTE_PAGESIZE_HINT 1 /**< Hint for page size in ELF note. */

#define NT_GNU_ABI_TAG       1    /**< Tag indicating the GNU ABI in the ELF note. */
#define ELF_NOTE_ABI         NT_GNU_ABI_TAG  /**< Alias for GNU ABI tag in ELF note. */

#define ELF_NOTE_OS_LINUX    0    /**< Linux operating system identifier in ELF note. */
#define ELF_NOTE_OS_GNU      1    /**< GNU operating system identifier in ELF note. */
#define ELF_NOTE_OS_SOLARIS2 2    /**< Solaris 2 operating system identifier in ELF note. */
#define ELF_NOTE_OS_FREEBSD  3    /**< FreeBSD operating system identifier in ELF note. */

#define NT_GNU_BUILD_ID      3    /**< Tag for the GNU build ID in ELF note. */
#define NT_GNU_GOLD_VERSION  4    /**< Tag for the GNU Gold version in ELF note. */
#define NT_GNU_PROPERTY_TYPE_0 5  /**< Tag for the GNU property type 0 in ELF note. */



/**
 * @struct Elf32_Move
 * @brief Move entry for 32-bit ELF.
 *
 * Used for data relocation in large static objects.
 */
typedef struct {
  Elf32_Xword m_value;  /**< Symbol value to be moved. */
  Elf32_Word m_info;    /**< Encoded symbol and type. */
  Elf32_Word m_poffset; /**< Offset in the symbol. */
  Elf32_Half m_repeat;  /**< Repeat count. */
  Elf32_Half m_stride;  /**< Stride between repetitions. */
} Elf32_Move;

/**
 * @struct Elf64_Move
 * @brief Move entry for 64-bit ELF.
 */
typedef struct {
  Elf64_Xword m_value;   /**< Symbol value to be moved. */
  Elf64_Xword m_info;    /**< Encoded symbol and type. */
  Elf64_Xword m_poffset; /**< Offset in the symbol. */
  Elf64_Half m_repeat;   /**< Repeat count. */
  Elf64_Half m_stride;   /**< Stride between repetitions. */
} Elf64_Move;


#define ELF32_M_SYM(info)    ((info) >> 8)    /**< Extract symbol index from ELF32 relocation info. */
#define ELF32_M_SIZE(info)   ((unsigned char)(info))    /**< Extract size from ELF32 relocation info. */
#define ELF32_M_INFO(sym, size)    (((sym) << 8) + (unsigned char)(size))    /**< Combine symbol index and size into ELF32 relocation info. */

#define ELF64_M_SYM(info)    ELF32_M_SYM(info)    /**< Extract symbol index from ELF64 relocation info (same as ELF32). */
#define ELF64_M_SIZE(info)   ELF32_M_SIZE(info)   /**< Extract size from ELF64 relocation info (same as ELF32). */
#define ELF64_M_INFO(sym, size)    ELF32_M_INFO(sym, size)    /**< Combine symbol index and size into ELF64 relocation info (same as ELF32). */

#define EF_CPU32    0x00810000    /**< Flag indicating the 32-bit CPU architecture in ELF. */

#define R_68K_NONE          0    /**< No relocation for 68K architecture. */
#define R_68K_32            1    /**< 32-bit relocation for 68K architecture. */
#define R_68K_16            2    /**< 16-bit relocation for 68K architecture. */
#define R_68K_8             3    /**< 8-bit relocation for 68K architecture. */
#define R_68K_PC32          4    /**< 32-bit PC-relative relocation for 68K architecture. */
#define R_68K_PC16          5    /**< 16-bit PC-relative relocation for 68K architecture. */
#define R_68K_PC8           6    /**< 8-bit PC-relative relocation for 68K architecture. */
#define R_68K_GOT32         7    /**< 32-bit GOT relocation for 68K architecture. */
#define R_68K_GOT16         8    /**< 16-bit GOT relocation for 68K architecture. */
#define R_68K_GOT8          9    /**< 8-bit GOT relocation for 68K architecture. */
#define R_68K_GOT32O        10   /**< 32-bit GOT offset relocation for 68K architecture. */
#define R_68K_GOT16O        11   /**< 16-bit GOT offset relocation for 68K architecture. */
#define R_68K_GOT8O         12   /**< 8-bit GOT offset relocation for 68K architecture. */
#define R_68K_PLT32         13   /**< 32-bit PLT relocation for 68K architecture. */
#define R_68K_PLT16         14   /**< 16-bit PLT relocation for 68K architecture. */
#define R_68K_PLT8          15   /**< 8-bit PLT relocation for 68K architecture. */
#define R_68K_PLT32O        16   /**< 32-bit PLT offset relocation for 68K architecture. */
#define R_68K_PLT16O        17   /**< 16-bit PLT offset relocation for 68K architecture. */
#define R_68K_PLT8O         18   /**< 8-bit PLT offset relocation for 68K architecture. */
#define R_68K_COPY          19   /**< Copy relocation for 68K architecture. */
#define R_68K_GLOB_DAT      20   /**< Global data relocation for 68K architecture. */
#define R_68K_JMP_SLOT      21   /**< Jump slot relocation for 68K architecture. */
#define R_68K_RELATIVE      22   /**< Relative relocation for 68K architecture. */
#define R_68K_TLS_GD32      25   /**< 32-bit TLS GD relocation for 68K architecture. */
#define R_68K_TLS_GD16      26   /**< 16-bit TLS GD relocation for 68K architecture. */
#define R_68K_TLS_GD8       27   /**< 8-bit TLS GD relocation for 68K architecture. */
#define R_68K_TLS_LDM32     28   /**< 32-bit TLS LDM relocation for 68K architecture. */
#define R_68K_TLS_LDM16     29   /**< 16-bit TLS LDM relocation for 68K architecture. */
#define R_68K_TLS_LDM8      30   /**< 8-bit TLS LDM relocation for 68K architecture. */
#define R_68K_TLS_LDO32     31   /**< 32-bit TLS LDO relocation for 68K architecture. */
#define R_68K_TLS_LDO16     32   /**< 16-bit TLS LDO relocation for 68K architecture. */
#define R_68K_TLS_LDO8      33   /**< 8-bit TLS LDO relocation for 68K architecture. */
#define R_68K_TLS_IE32      34   /**< 32-bit TLS IE relocation for 68K architecture. */
#define R_68K_TLS_IE16      35   /**< 16-bit TLS IE relocation for 68K architecture. */
#define R_68K_TLS_IE8       36   /**< 8-bit TLS IE relocation for 68K architecture. */
#define R_68K_TLS_LE32      37   /**< 32-bit TLS LE relocation for 68K architecture. */
#define R_68K_TLS_LE16      38   /**< 16-bit TLS LE relocation for 68K architecture. */
#define R_68K_TLS_LE8       39   /**< 8-bit TLS LE relocation for 68K architecture. */
#define R_68K_TLS_DTPMOD32  40   /**< 32-bit TLS DTPMOD relocation for 68K architecture. */
#define R_68K_TLS_DTPREL32  41   /**< 32-bit TLS DTPREL relocation for 68K architecture. */
#define R_68K_TLS_TPREL32   42   /**< 32-bit TLS TPREL relocation for 68K architecture. */
#define R_68K_NUM           43   /**< Total number of 68K relocation types. */


#define R_386_NONE            0    /**< No relocation for 386 architecture. */
#define R_386_32              1    /**< 32-bit relocation for 386 architecture. */
#define R_386_PC32            2    /**< 32-bit PC-relative relocation for 386 architecture. */
#define R_386_GOT32           3    /**< 32-bit GOT relocation for 386 architecture. */
#define R_386_PLT32           4    /**< 32-bit PLT relocation for 386 architecture. */
#define R_386_COPY            5    /**< Copy relocation for 386 architecture. */
#define R_386_GLOB_DAT        6    /**< Global data relocation for 386 architecture. */
#define R_386_JMP_SLOT        7    /**< Jump slot relocation for 386 architecture. */
#define R_386_RELATIVE        8    /**< Relative relocation for 386 architecture. */
#define R_386_GOTOFF          9    /**< GOT offset relocation for 386 architecture. */
#define R_386_GOTPC           10   /**< GOT PC-relative relocation for 386 architecture. */
#define R_386_32PLT           11   /**< 32-bit PLT relocation for 386 architecture (PLT). */
#define R_386_TLS_TPOFF       14   /**< TLS thread pointer offset relocation for 386 architecture. */
#define R_386_TLS_IE          15   /**< TLS indirect entry relocation for 386 architecture. */
#define R_386_TLS_GOTIE       16   /**< TLS GOT indirect entry relocation for 386 architecture. */
#define R_386_TLS_LE          17   /**< TLS local-external relocation for 386 architecture. */
#define R_386_TLS_GD          18   /**< TLS global dynamic relocation for 386 architecture. */
#define R_386_TLS_LDM         19   /**< TLS local dynamic relocation for 386 architecture. */
#define R_386_16              20   /**< 16-bit relocation for 386 architecture. */
#define R_386_PC16            21   /**< 16-bit PC-relative relocation for 386 architecture. */
#define R_386_8               22   /**< 8-bit relocation for 386 architecture. */
#define R_386_PC8             23   /**< 8-bit PC-relative relocation for 386 architecture. */
#define R_386_TLS_GD_32       24   /**< 32-bit TLS global dynamic relocation for 386 architecture. */
#define R_386_TLS_GD_PUSH     25   /**< TLS global dynamic push relocation for 386 architecture. */
#define R_386_TLS_GD_CALL     26   /**< TLS global dynamic call relocation for 386 architecture. */
#define R_386_TLS_GD_POP      27   /**< TLS global dynamic pop relocation for 386 architecture. */
#define R_386_TLS_LDM_32      28   /**< 32-bit TLS local dynamic relocation for 386 architecture. */
#define R_386_TLS_LDM_PUSH    29   /**< TLS local dynamic push relocation for 386 architecture. */
#define R_386_TLS_LDM_CALL    30   /**< TLS local dynamic call relocation for 386 architecture. */
#define R_386_TLS_LDM_POP     31   /**< TLS local dynamic pop relocation for 386 architecture. */
#define R_386_TLS_LDO_32      32   /**< 32-bit TLS local offset relocation for 386 architecture. */
#define R_386_TLS_IE_32       33   /**< 32-bit TLS indirect entry relocation for 386 architecture. */
#define R_386_TLS_LE_32       34   /**< 32-bit TLS local-external relocation for 386 architecture. */
#define R_386_TLS_DTPMOD32    35   /**< 32-bit TLS DTP module relocation for 386 architecture. */
#define R_386_TLS_DTPOFF32    36   /**< 32-bit TLS DTP offset relocation for 386 architecture. */
#define R_386_TLS_TPOFF32     37   /**< 32-bit TLS thread pointer offset relocation for 386 architecture. */
#define R_386_SIZE32          38   /**< 32-bit size relocation for 386 architecture. */
#define R_386_TLS_GOTDESC     39   /**< TLS GOT descriptor relocation for 386 architecture. */
#define R_386_TLS_DESC_CALL   40   /**< TLS descriptor call relocation for 386 architecture. */
#define R_386_TLS_DESC        41   /**< TLS descriptor relocation for 386 architecture. */
#define R_386_IRELATIVE       42   /**< I-relative relocation for 386 architecture. */
#define R_386_GOT32X          43   /**< GOT32 extended relocation for 386 architecture. */
#define R_386_NUM             44   /**< Total number of 386 relocation types. */






#define STT_SPARC_REGISTER   13   /**< Symbol type for SPARC register. */

#define EF_SPARCV9_MM         3   /**< SPARC v9 memory model. */
#define EF_SPARCV9_TSO        0   /**< SPARC v9 Total Store Order (TSO) memory model. */
#define EF_SPARCV9_PSO        1   /**< SPARC v9 Partial Store Order (PSO) memory model. */
#define EF_SPARCV9_RMO        2   /**< SPARC v9 Relaxed Memory Order (RMO) memory model. */
#define EF_SPARC_LEDATA       0x800000 /**< SPARC little-endian data flag. */
#define EF_SPARC_EXT_MASK     0xFFFF00 /**< Mask for SPARC extension flags. */
#define EF_SPARC_32PLUS       0x000100 /**< SPARC 32-bit plus feature flag. */
#define EF_SPARC_SUN_US1      0x000200 /**< SPARC Sun UltraSPARC I feature flag. */
#define EF_SPARC_HAL_R1       0x000400 /**< SPARC Hardware Abstraction Layer (HAL) version 1. */
#define EF_SPARC_SUN_US3      0x000800 /**< SPARC Sun UltraSPARC III feature flag. */



#define R_SPARC_NONE         0   /**< No relocation. */
#define R_SPARC_8            1   /**< 8-bit relocation. */
#define R_SPARC_16           2   /**< 16-bit relocation. */
#define R_SPARC_32           3   /**< 32-bit relocation. */
#define R_SPARC_DISP8        4   /**< 8-bit displacement. */
#define R_SPARC_DISP16       5   /**< 16-bit displacement. */
#define R_SPARC_DISP32       6   /**< 32-bit displacement. */
#define R_SPARC_WDISP30      7   /**< 30-bit word displacement. */
#define R_SPARC_WDISP22      8   /**< 22-bit word displacement. */
#define R_SPARC_HI22         9   /**< High 22 bits of address. */
#define R_SPARC_22           10  /**< 22-bit displacement. */
#define R_SPARC_13           11  /**< 13-bit displacement. */
#define R_SPARC_LO10         12  /**< Low 10 bits of address. */
#define R_SPARC_GOT10        13  /**< Global Offset Table (GOT) entry for 10-bit address. */
#define R_SPARC_GOT13        14  /**< GOT entry for 13-bit address. */
#define R_SPARC_GOT22        15  /**< GOT entry for 22-bit address. */
#define R_SPARC_PC10         16  /**< 10-bit program counter relative displacement. */
#define R_SPARC_PC22         17  /**< 22-bit program counter relative displacement. */
#define R_SPARC_WPLT30       18  /**< 30-bit word displacement for PLT (Procedure Linkage Table). */
#define R_SPARC_COPY         19  /**< Copy relocation. */
#define R_SPARC_GLOB_DAT     20  /**< Global data relocation. */
#define R_SPARC_JMP_SLOT     21  /**< Jump slot relocation (used for dynamic linking). */
#define R_SPARC_RELATIVE     22  /**< Relative relocation. */
#define R_SPARC_UA32         23  /**< 32-bit unsigned address relocation. */




#define R_SPARC_PLT32         24  /**< 32-bit PLT (Procedure Linkage Table) relocation. */
#define R_SPARC_HIPLT22       25  /**< High 22 bits of PLT relocation. */
#define R_SPARC_LOPLT10       26  /**< Low 10 bits of PLT relocation. */
#define R_SPARC_PCPLT32       27  /**< 32-bit program counter relative PLT relocation. */
#define R_SPARC_PCPLT22       28  /**< 22-bit program counter relative PLT relocation. */
#define R_SPARC_PCPLT10       29  /**< 10-bit program counter relative PLT relocation. */
#define R_SPARC_10            30  /**< 10-bit displacement. */
#define R_SPARC_11            31  /**< 11-bit displacement. */
#define R_SPARC_64            32  /**< 64-bit displacement. */
#define R_SPARC_OLO10         33  /**< Offset low 10 bits relocation. */
#define R_SPARC_HH22          34  /**< High 22 bits relocation for a 64-bit address. */
#define R_SPARC_HM10          35  /**< High middle 10 bits relocation for a 64-bit address. */
#define R_SPARC_LM22          36  /**< Low middle 22 bits relocation for a 64-bit address. */
#define R_SPARC_PC_HH22       37  /**< Program counter high 22 bits relocation. */
#define R_SPARC_PC_HM10       38  /**< Program counter high middle 10 bits relocation. */
#define R_SPARC_PC_LM22       39  /**< Program counter low middle 22 bits relocation. */
#define R_SPARC_WDISP16       40  /**< 16-bit word displacement relocation. */
#define R_SPARC_WDISP19       41  /**< 19-bit word displacement relocation. */
#define R_SPARC_GLOB_JMP      42  /**< Global jump relocation. */
#define R_SPARC_7             43  /**< 7-bit displacement relocation. */
#define R_SPARC_5             44  /**< 5-bit displacement relocation. */
#define R_SPARC_6             45  /**< 6-bit displacement relocation. */
#define R_SPARC_DISP64        46  /**< 64-bit displacement relocation. */
#define R_SPARC_PLT64         47  /**< 64-bit PLT relocation. */
#define R_SPARC_HIX22         48  /**< High 22 bits of indexed address relocation. */
#define R_SPARC_LOX10         49  /**< Low 10 bits of indexed address relocation. */
#define R_SPARC_H44           50  /**< High 44 bits of address relocation. */
#define R_SPARC_M44           51  /**< Middle 44 bits of address relocation. */
#define R_SPARC_L44           52  /**< Low 44 bits of address relocation. */
#define R_SPARC_REGISTER      53  /**< Register relocation. */
#define R_SPARC_UA64          54  /**< 64-bit unsigned address relocation. */
#define R_SPARC_UA16          55  /**< 16-bit unsigned address relocation. */
#define R_SPARC_TLS_GD_HI22   56  /**< TLS global dynamic high 22 bits relocation. */
#define R_SPARC_TLS_GD_LO10   57  /**< TLS global dynamic low 10 bits relocation. */
#define R_SPARC_TLS_GD_ADD    58  /**< TLS global dynamic address relocation. */
#define R_SPARC_TLS_GD_CALL   59  /**< TLS global dynamic call relocation. */
#define R_SPARC_TLS_LDM_HI22  60  /**< TLS local dynamic high 22 bits relocation. */
#define R_SPARC_TLS_LDM_LO10  61  /**< TLS local dynamic low 10 bits relocation. */
#define R_SPARC_TLS_LDM_ADD   62  /**< TLS local dynamic address relocation. */
#define R_SPARC_TLS_LDM_CALL  63  /**< TLS local dynamic call relocation. */
#define R_SPARC_TLS_LDO_HIX22 64  /**< TLS local dynamic offset high 22 bits relocation. */
#define R_SPARC_TLS_LDO_LOX10 65  /**< TLS local dynamic offset low 10 bits relocation. */
#define R_SPARC_TLS_LDO_ADD   66  /**< TLS local dynamic offset address relocation. */
#define R_SPARC_TLS_IE_HI22   67  /**< TLS index entry high 22 bits relocation. */
#define R_SPARC_TLS_IE_LO10   68  /**< TLS index entry low 10 bits relocation. */
#define R_SPARC_TLS_IE_LD     69  /**< TLS index entry load relocation. */
#define R_SPARC_TLS_IE_LDX    70  /**< TLS index entry load indexed relocation. */
#define R_SPARC_TLS_IE_ADD    71  /**< TLS index entry add relocation. */
#define R_SPARC_TLS_LE_HIX22  72  /**< TLS local entry high 22 bits relocation. */
#define R_SPARC_TLS_LE_LOX10  73  /**< TLS local entry low 10 bits relocation. */
#define R_SPARC_TLS_DTPMOD32  74  /**< TLS DTP module 32-bit relocation. */
#define R_SPARC_TLS_DTPMOD64  75  /**< TLS DTP module 64-bit relocation. */
#define R_SPARC_TLS_DTPOFF32  76  /**< TLS DTP offset 32-bit relocation. */
#define R_SPARC_TLS_DTPOFF64  77  /**< TLS DTP offset 64-bit relocation. */
#define R_SPARC_TLS_TPOFF32   78  /**< TLS TP offset 32-bit relocation. */
#define R_SPARC_TLS_TPOFF64   79  /**< TLS TP offset 64-bit relocation. */
#define R_SPARC_GOTDATA_HIX22 80  /**< GOT data high 22 bits relocation. */
#define R_SPARC_GOTDATA_LOX10 81  /**< GOT data low 10 bits relocation. */
#define R_SPARC_GOTDATA_OP_HIX22 82 /**< GOT data operation high 22 bits relocation. */
#define R_SPARC_GOTDATA_OP_LOX10 83 /**< GOT data operation low 10 bits relocation. */
#define R_SPARC_GOTDATA_OP    84  /**< GOT data operation relocation. */
#define R_SPARC_H34           85  /**< High 34 bits of address relocation. */
#define R_SPARC_SIZE32        86  /**< 32-bit size relocation. */
#define R_SPARC_SIZE64        87  /**< 64-bit size relocation. */
#define R_SPARC_GNU_VTINHERIT 250 /**< GNU virtual table inheritance relocation. */
#define R_SPARC_GNU_VTENTRY   251 /**< GNU virtual table entry relocation. */
#define R_SPARC_REV32         252 /**< 32-bit reversed relocation. */

#define R_SPARC_NUM           253 /**< Number of relocation types. */



#define DT_SPARC_REGISTER    0x70000001  /**< SPARC-specific dynamic tag for register. */
#define DT_SPARC_NUM         2           /**< Number of SPARC-specific dynamic tags. */

#define EF_MIPS_NOREORDER    1           /**< MIPS processor does not require instruction reordering. */
#define EF_MIPS_PIC          2           /**< MIPS position-independent code. */
#define EF_MIPS_CPIC         4           /**< MIPS compatible position-independent code. */
#define EF_MIPS_XGOT         8           /**< MIPS extended GOT (Global Offset Table). */
#define EF_MIPS_64BIT_WHIRL  16          /**< MIPS 64-bit whirlpool ABI support. */
#define EF_MIPS_ABI2         32          /**< MIPS ABI version 2 support. */
#define EF_MIPS_ABI_ON32     64          /**< MIPS ABI on 32-bit architecture. */
#define EF_MIPS_FP64         512         /**< MIPS support for 64-bit floating point. */
#define EF_MIPS_NAN2008      1024        /**< MIPS support for 2008 NAN (Not a Number) standards. */
#define EF_MIPS_ARCH         0xf0000000  /**< MIPS architecture version mask. */



#define EF_MIPS_ARCH_1      0x00000000  /**< MIPS architecture version 1. */
#define EF_MIPS_ARCH_2      0x10000000  /**< MIPS architecture version 2. */
#define EF_MIPS_ARCH_3      0x20000000  /**< MIPS architecture version 3. */
#define EF_MIPS_ARCH_4      0x30000000  /**< MIPS architecture version 4. */
#define EF_MIPS_ARCH_5      0x40000000  /**< MIPS architecture version 5. */
#define EF_MIPS_ARCH_32     0x50000000  /**< MIPS 32-bit architecture. */
#define EF_MIPS_ARCH_64     0x60000000  /**< MIPS 64-bit architecture. */
#define EF_MIPS_ARCH_32R2   0x70000000  /**< MIPS 32-bit architecture version R2. */
#define EF_MIPS_ARCH_64R2   0x80000000  /**< MIPS 64-bit architecture version R2. */

#define E_MIPS_ARCH_1       0x00000000  /**< MIPS architecture version 1. */
#define E_MIPS_ARCH_2       0x10000000  /**< MIPS architecture version 2. */
#define E_MIPS_ARCH_3       0x20000000  /**< MIPS architecture version 3. */
#define E_MIPS_ARCH_4       0x30000000  /**< MIPS architecture version 4. */
#define E_MIPS_ARCH_5       0x40000000  /**< MIPS architecture version 5. */
#define E_MIPS_ARCH_32      0x50000000  /**< MIPS 32-bit architecture. */
#define E_MIPS_ARCH_64      0x60000000  /**< MIPS 64-bit architecture. */



#define SHN_MIPS_ACOMMON    0xff00  /**< MIPS ACOMMON section type. */
#define SHN_MIPS_TEXT        0xff01  /**< MIPS TEXT section type. */
#define SHN_MIPS_DATA        0xff02  /**< MIPS DATA section type. */
#define SHN_MIPS_SCOMMON     0xff03  /**< MIPS SCOMMON section type. */
#define SHN_MIPS_SUNDEFINED  0xff04  /**< MIPS SUNDEFINED section type. */




#define SHT_MIPS_LIBLIST       0x70000000  /**< MIPS Library list section type. */
#define SHT_MIPS_MSYM          0x70000001  /**< MIPS Symbol table for messages section type. */
#define SHT_MIPS_CONFLICT      0x70000002  /**< MIPS Conflict section type. */
#define SHT_MIPS_GPTAB         0x70000003  /**< MIPS Global pointer table section type. */
#define SHT_MIPS_UCODE         0x70000004  /**< MIPS Microcode section type. */
#define SHT_MIPS_DEBUG         0x70000005  /**< MIPS Debug section type. */
#define SHT_MIPS_REGINFO       0x70000006  /**< MIPS Register information section type. */
#define SHT_MIPS_PACKAGE       0x70000007  /**< MIPS Package section type. */
#define SHT_MIPS_PACKSYM       0x70000008  /**< MIPS Packed symbols section type. */
#define SHT_MIPS_RELD          0x70000009  /**< MIPS Relocation entries section type. */
#define SHT_MIPS_IFACE         0x7000000b  /**< MIPS Interface section type. */
#define SHT_MIPS_CONTENT       0x7000000c  /**< MIPS Content section type. */
#define SHT_MIPS_OPTIONS       0x7000000d  /**< MIPS Options section type. */
#define SHT_MIPS_SHDR          0x70000010  /**< MIPS Section headers section type. */
#define SHT_MIPS_FDESC         0x70000011  /**< MIPS Function descriptor section type. */
#define SHT_MIPS_EXTSYM        0x70000012  /**< MIPS Extended symbols section type. */
#define SHT_MIPS_DENSE         0x70000013  /**< MIPS Dense section type. */
#define SHT_MIPS_PDESC         0x70000014  /**< MIPS Procedure descriptor section type. */
#define SHT_MIPS_LOCSYM        0x70000015  /**< MIPS Local symbols section type. */
#define SHT_MIPS_AUXSYM        0x70000016  /**< MIPS Auxiliary symbols section type. */
#define SHT_MIPS_OPTSYM        0x70000017  /**< MIPS Optional symbols section type. */
#define SHT_MIPS_LOCSTR        0x70000018  /**< MIPS Local string section type. */
#define SHT_MIPS_LINE          0x70000019  /**< MIPS Line number section type. */
#define SHT_MIPS_RFDESC        0x7000001a  /**< MIPS Relocation function descriptor section type. */
#define SHT_MIPS_DELTASYM      0x7000001b  /**< MIPS Delta symbol section type. */
#define SHT_MIPS_DELTAINST     0x7000001c  /**< MIPS Delta instruction section type. */
#define SHT_MIPS_DELTACLASS    0x7000001d  /**< MIPS Delta class section type. */
#define SHT_MIPS_DWARF         0x7000001e  /**< MIPS DWARF debug section type. */
#define SHT_MIPS_DELTADECL     0x7000001f  /**< MIPS Delta declaration section type. */
#define SHT_MIPS_SYMBOL_LIB    0x70000020  /**< MIPS Symbol library section type. */
#define SHT_MIPS_EVENTS        0x70000021  /**< MIPS Events section type. */
#define SHT_MIPS_TRANSLATE     0x70000022  /**< MIPS Translation section type. */
#define SHT_MIPS_PIXIE         0x70000023  /**< MIPS Pixie section type. */
#define SHT_MIPS_XLATE         0x70000024  /**< MIPS Translation table section type. */
#define SHT_MIPS_XLATE_DEBUG   0x70000025  /**< MIPS Translation debug section type. */
#define SHT_MIPS_WHIRL         0x70000026  /**< MIPS Whirlwind section type. */
#define SHT_MIPS_EH_REGION     0x70000027  /**< MIPS Exception handling region section type. */
#define SHT_MIPS_XLATE_OLD     0x70000028  /**< MIPS Old translation section type. */
#define SHT_MIPS_PDR_EXCEPTION 0x70000029  /**< MIPS PDR exception section type. */




#define SHF_MIPS_GPREL      0x10000000  /**< MIPS GP-relative section flag. */
#define SHF_MIPS_MERGE      0x20000000  /**< MIPS Merge section flag. */
#define SHF_MIPS_ADDR       0x40000000  /**< MIPS Address section flag. */
#define SHF_MIPS_STRINGS    0x80000000  /**< MIPS Strings section flag. */
#define SHF_MIPS_NOSTRIP    0x08000000  /**< MIPS Do not strip section flag. */
#define SHF_MIPS_LOCAL      0x04000000  /**< MIPS Local section flag. */
#define SHF_MIPS_NAMES      0x02000000  /**< MIPS Names section flag. */
#define SHF_MIPS_NODUPE     0x01000000  /**< MIPS No duplicate section flag. */






#define STO_MIPS_DEFAULT               0x0  /**< MIPS default symbol visibility. */
#define STO_MIPS_INTERNAL              0x1  /**< MIPS internal symbol visibility. */
#define STO_MIPS_HIDDEN                0x2  /**< MIPS hidden symbol visibility. */
#define STO_MIPS_PROTECTED             0x3  /**< MIPS protected symbol visibility. */
#define STO_MIPS_PLT                   0x8  /**< MIPS symbol used for PLT (Procedure Linkage Table). */
#define STO_MIPS_SC_ALIGN_UNUSED       0xff /**< MIPS special case for unused alignment. */

#define STB_MIPS_SPLIT_COMMON          13  /**< MIPS binding for split common symbols. */



/**
 * @union Elf32_gptab
 * @brief Global Offset Table (GOT) processing table for 32-bit ELF (MIPS-specific).
 *
 * Contains either header information or an entry describing global pointer values.
 */
typedef union {
  struct {
    Elf32_Word gt_current_g_value; /**< Current GP value used. */
    Elf32_Word gt_unused;          /**< Unused. */
  } gt_header;
  struct {
    Elf32_Word gt_g_value;         /**< Global pointer value. */
    Elf32_Word gt_bytes;           /**< Number of bytes associated with this GP value. */
  } gt_entry;
} Elf32_gptab;


/**
 * @struct Elf32_RegInfo
 * @brief MIPS register usage information.
 *
 * Describes usage of general-purpose and coprocessor registers for optimization.
 */
typedef struct {
  Elf32_Word	ri_gprmask;    /**< Bitmask of used general-purpose registers. */
  Elf32_Word	ri_cprmask[4]; /**< Bitmask of used coprocessor registers. */
  Elf32_Sword	ri_gp_value;   /**< Global pointer value. */
} Elf32_RegInfo;


/**
 * @struct Elf_Options
 * @brief ELF Options section entry.
 *
 * Used for processor- and platform-specific extensions (e.g., MIPS).
 */
typedef struct {
  unsigned char kind;    /**< Option kind identifier. */

  unsigned char size;    /**< Total size of this option. */
  Elf32_Section section; /**< Section index that this option applies to. */

  Elf32_Word info;       /**< Additional option-specific information. */
} Elf_Options;



#define ODK_NULL        0  /**< No option or null option type. */
#define ODK_REGINFO     1  /**< Option type for register information. */
#define ODK_EXCEPTIONS  2  /**< Option type for exceptions. */
#define ODK_PAD         3  /**< Option type for padding. */
#define ODK_HWPATCH     4  /**< Option type for hardware patch. */
#define ODK_FILL        5  /**< Option type for filling memory. */
#define ODK_TAGS        6  /**< Option type for tags. */
#define ODK_HWAND       7  /**< Option type for hardware AND. */
#define ODK_HWOR        8  /**< Option type for hardware OR. */




#define OEX_FPU_MIN     0x1f      /**< Minimum FPU exception flag. */
#define OEX_FPU_MAX     0x1f00    /**< Maximum FPU exception flag. */
#define OEX_PAGE0       0x10000   /**< Exception for page 0. */
#define OEX_SMM         0x20000   /**< Exception for SMM (System Management Mode). */
#define OEX_FPDBUG      0x40000   /**< Exception for FPU debug. */
#define OEX_PRECISEFP   OEX_FPDBUG /**< Exception for precise FPU. */
#define OEX_DISMISS     0x80000   /**< Dismiss exception flag. */

#define OEX_FPU_INVAL   0x10      /**< FPU invalid operation exception. */
#define OEX_FPU_DIV0    0x08      /**< FPU division by zero exception. */
#define OEX_FPU_OFLO    0x04      /**< FPU overflow exception. */
#define OEX_FPU_UFLO    0x02      /**< FPU underflow exception. */
#define OEX_FPU_INEX    0x01      /**< FPU inexact result exception. */



#define OHW_R4KEOP      0x1       /**< R4K EOP hardware exception. */
#define OHW_R8KPFETCH   0x2       /**< R8K prefetch exception. */
#define OHW_R5KEOP      0x4       /**< R5K EOP hardware exception. */
#define OHW_R5KCVTL     0x8       /**< R5K conversion exception. */

#define OPAD_PREFIX     0x1       /**< Padding prefix flag. */
#define OPAD_POSTFIX    0x2       /**< Padding postfix flag. */
#define OPAD_SYMBOL     0x4       /**< Padding symbol flag. */


/**
 * @struct Elf_Options_Hw
 * @brief Hardware-specific options flags.
 */
typedef struct {
  Elf32_Word hwp_flags1; /**< First hardware capability flag word. */
  Elf32_Word hwp_flags2; /**< Second hardware capability flag word. */
} Elf_Options_Hw;



#define OHWA0_R4KEOP_CHECKED   0x00000001  /**< R4K EOP checked exception flag. */
#define OHWA1_R4KEOP_CLEAN     0x00000002  /**< R4K EOP clean exception flag. */



#define R_MIPS_NONE		0   /**< No relocation */
#define R_MIPS_16		1   /**< 16-bit relocation */
#define R_MIPS_32		2   /**< 32-bit relocation */
#define R_MIPS_REL32		3   /**< 32-bit relative relocation */
#define R_MIPS_26		4   /**< 26-bit relocation */
#define R_MIPS_HI16		5   /**< HI16 relocation */
#define R_MIPS_LO16		6   /**< LO16 relocation */
#define R_MIPS_GPREL16		7   /**< GP-relative 16-bit relocation */
#define R_MIPS_LITERAL		8   /**< Literal relocation */
#define R_MIPS_GOT16		9   /**< GOT 16-bit relocation */
#define R_MIPS_PC16		10  /**< PC-relative 16-bit relocation */
#define R_MIPS_CALL16		11  /**< Call 16-bit relocation */
#define R_MIPS_GPREL32		12  /**< GP-relative 32-bit relocation */

#define R_MIPS_SHIFT5		16  /**< 5-bit shift relocation */
#define R_MIPS_SHIFT6		17  /**< 6-bit shift relocation */
#define R_MIPS_64		18  /**< 64-bit relocation */
#define R_MIPS_GOT_DISP		19  /**< GOT displacement relocation */
#define R_MIPS_GOT_PAGE		20  /**< GOT page relocation */
#define R_MIPS_GOT_OFST		21  /**< GOT offset relocation */
#define R_MIPS_GOT_HI16		22  /**< GOT high 16-bit relocation */
#define R_MIPS_GOT_LO16		23  /**< GOT low 16-bit relocation */
#define R_MIPS_SUB		24  /**< Subtraction relocation */
#define R_MIPS_INSERT_A		25  /**< Insert A relocation */
#define R_MIPS_INSERT_B		26  /**< Insert B relocation */
#define R_MIPS_DELETE		27  /**< Delete relocation */
#define R_MIPS_HIGHER		28  /**< Higher relocation */
#define R_MIPS_HIGHEST		29  /**< Highest relocation */
#define R_MIPS_CALL_HI16	30  /**< Call high 16-bit relocation */
#define R_MIPS_CALL_LO16	31  /**< Call low 16-bit relocation */
#define R_MIPS_SCN_DISP		32  /**< Section displacement relocation */
#define R_MIPS_REL16		33  /**< 16-bit relative relocation */
#define R_MIPS_ADD_IMMEDIATE	34  /**< Add immediate relocation */
#define R_MIPS_PJUMP		35  /**< Jump relocation */
#define R_MIPS_RELGOT		36  /**< Relative GOT relocation */
#define R_MIPS_JALR		37  /**< Jump and link register relocation */
#define R_MIPS_TLS_DTPMOD32	38  /**< TLS DTP module 32-bit relocation */
#define R_MIPS_TLS_DTPREL32	39  /**< TLS DTP relative 32-bit relocation */
#define R_MIPS_TLS_DTPMOD64	40  /**< TLS DTP module 64-bit relocation */
#define R_MIPS_TLS_DTPREL64	41  /**< TLS DTP relative 64-bit relocation */
#define R_MIPS_TLS_GD		42  /**< TLS GD relocation */
#define R_MIPS_TLS_LDM		43  /**< TLS LDM relocation */
#define R_MIPS_TLS_DTPREL_HI16	44  /**< TLS DTP relative high 16-bit relocation */
#define R_MIPS_TLS_DTPREL_LO16	45  /**< TLS DTP relative low 16-bit relocation */
#define R_MIPS_TLS_GOTTPREL	46  /**< TLS GOT TPREL relocation */
#define R_MIPS_TLS_TPREL32	47  /**< TLS TPREL 32-bit relocation */
#define R_MIPS_TLS_TPREL64	48  /**< TLS TPREL 64-bit relocation */
#define R_MIPS_TLS_TPREL_HI16	49  /**< TLS TPREL high 16-bit relocation */
#define R_MIPS_TLS_TPREL_LO16	50  /**< TLS TPREL low 16-bit relocation */
#define R_MIPS_GLOB_DAT		51  /**< Global data relocation */
#define R_MIPS_COPY		126  /**< Copy relocation */
#define R_MIPS_JUMP_SLOT        127  /**< Jump slot relocation */

#define R_MIPS_NUM		128  /**< Total number of relocation types */




#define PT_MIPS_REGINFO    0x70000000   /**< Program header type for MIPS register information */
#define PT_MIPS_RTPROC     0x70000001   /**< Program header type for MIPS runtime processing */
#define PT_MIPS_OPTIONS    0x70000002   /**< Program header type for MIPS specific options */
#define PT_MIPS_ABIFLAGS   0x70000003   /**< Program header type for MIPS ABI flags */

#define PF_MIPS_LOCAL      0x10000000   /**< Flag indicating MIPS local memory segment */




#define DT_MIPS_RLD_VERSION     0x70000001 /**< MIPS Relocation version */
#define DT_MIPS_TIME_STAMP      0x70000002 /**< MIPS Timestamp */
#define DT_MIPS_ICHECKSUM       0x70000003 /**< MIPS Internal checksum */
#define DT_MIPS_IVERSION        0x70000004 /**< MIPS Internal version */
#define DT_MIPS_FLAGS           0x70000005 /**< MIPS Flags */
#define DT_MIPS_BASE_ADDRESS    0x70000006 /**< MIPS Base address */
#define DT_MIPS_MSYM            0x70000007 /**< MIPS Symbol table */
#define DT_MIPS_CONFLICT        0x70000008 /**< MIPS Conflict */
#define DT_MIPS_LIBLIST         0x70000009 /**< MIPS Library list */
#define DT_MIPS_LOCAL_GOTNO     0x7000000a /**< MIPS Local GOT index */
#define DT_MIPS_CONFLICTNO      0x7000000b /**< MIPS Conflict index */
#define DT_MIPS_LIBLISTNO       0x70000010 /**< MIPS Library list index */
#define DT_MIPS_SYMTABNO        0x70000011 /**< MIPS Symbol table index */
#define DT_MIPS_UNREFEXTNO      0x70000012 /**< MIPS Unreferenced external symbol index */
#define DT_MIPS_GOTSYM          0x70000013 /**< MIPS Global offset table symbols */
#define DT_MIPS_HIPAGENO        0x70000014 /**< MIPS High page number */
#define DT_MIPS_RLD_MAP         0x70000016 /**< MIPS Relocation map */
#define DT_MIPS_DELTA_CLASS     0x70000017 /**< MIPS Delta class */
#define DT_MIPS_DELTA_CLASS_NO  0x70000018 /**< MIPS Delta class number */

#define DT_MIPS_DELTA_INSTANCE  0x70000019 /**< MIPS Delta instance */
#define DT_MIPS_DELTA_INSTANCE_NO 0x7000001a /**< MIPS Delta instance number */

#define DT_MIPS_DELTA_RELOC     0x7000001b /**< MIPS Delta relocation */
#define DT_MIPS_DELTA_RELOC_NO  0x7000001c /**< MIPS Delta relocation number */

#define DT_MIPS_DELTA_SYM       0x7000001d /**< MIPS Delta symbol */
#define DT_MIPS_DELTA_SYM_NO    0x7000001e /**< MIPS Delta symbol number */

#define DT_MIPS_DELTA_CLASSSYM  0x70000020 /**< MIPS Delta class symbol */
#define DT_MIPS_DELTA_CLASSSYM_NO 0x70000021 /**< MIPS Delta class symbol number */

#define DT_MIPS_CXX_FLAGS       0x70000022 /**< MIPS C++ flags */
#define DT_MIPS_PIXIE_INIT      0x70000023 /**< MIPS Pixie initialization */
#define DT_MIPS_SYMBOL_LIB      0x70000024 /**< MIPS Symbol library */
#define DT_MIPS_LOCALPAGE_GOTIDX 0x70000025 /**< MIPS Local page GOT index */
#define DT_MIPS_LOCAL_GOTIDX    0x70000026 /**< MIPS Local GOT index */
#define DT_MIPS_HIDDEN_GOTIDX   0x70000027 /**< MIPS Hidden GOT index */
#define DT_MIPS_PROTECTED_GOTIDX 0x70000028 /**< MIPS Protected GOT index */
#define DT_MIPS_OPTIONS          0x70000029 /**< MIPS Options */
#define DT_MIPS_INTERFACE        0x7000002a /**< MIPS Interface */
#define DT_MIPS_DYNSTR_ALIGN     0x7000002b /**< MIPS Dynamic string table alignment */
#define DT_MIPS_INTERFACE_SIZE   0x7000002c /**< MIPS Interface size */
#define DT_MIPS_RLD_TEXT_RESOLVE_ADDR 0x7000002d /**< MIPS RLD text resolve address */

#define DT_MIPS_PERF_SUFFIX      0x7000002e /**< MIPS Performance suffix */
#define DT_MIPS_COMPACT_SIZE     0x7000002f /**< MIPS Compact size */
#define DT_MIPS_GP_VALUE         0x70000030 /**< MIPS GP value */
#define DT_MIPS_AUX_DYNAMIC      0x70000031 /**< MIPS Auxiliary dynamic information */

#define DT_MIPS_PLTGOT           0x70000032 /**< MIPS PLT Global Offset Table */
#define DT_MIPS_RWPLT            0x70000034 /**< MIPS Read-Write PLT */
#define DT_MIPS_RLD_MAP_REL      0x70000035 /**< MIPS Relocation map relative */
#define DT_MIPS_NUM              0x36 /**< MIPS number of dynamic section entries */




#define RHF_NONE                         0 /**< No relocation handling flags set */
#define RHF_QUICKSTART                   (1 << 0) /**< Quickstart relocation handling flag */
#define RHF_NOTPOT                        (1 << 1) /**< Flag for not a power of two */
#define RHF_NO_LIBRARY_REPLACEMENT        (1 << 2) /**< No library replacement during relocation */
#define RHF_NO_MOVE                       (1 << 3) /**< No move relocation */
#define RHF_SGI_ONLY                      (1 << 4) /**< Relocation flag specific to SGI systems */
#define RHF_GUARANTEE_INIT                (1 << 5) /**< Guarantee that initialization occurs */
#define RHF_DELTA_C_PLUS_PLUS             (1 << 6) /**< Delta C++ relocation flag */
#define RHF_GUARANTEE_START_INIT          (1 << 7) /**< Guarantee that the start of initialization occurs */
#define RHF_PIXIE                         (1 << 8) /**< Flag for Pixie relocation handling */
#define RHF_DEFAULT_DELAY_LOAD            (1 << 9) /**< Default delayed load relocation */
#define RHF_REQUICKSTART                  (1 << 10) /**< Re-quickstart relocation flag */
#define RHF_REQUICKSTARTED                (1 << 11) /**< Flag indicating the relocation has been re-quickstarted */
#define RHF_CORD                          (1 << 12) /**< CORD relocation handling flag */
#define RHF_NO_UNRES_UNDEF                (1 << 13) /**< No unresolved undefined relocation flag */
#define RHF_RLD_ORDER_SAFE                (1 << 14) /**< Flag indicating that the relocation is order-safe */



/**
 * @struct Elf32_Lib
 * @brief Library dependency information for 32-bit ELF.
 */
typedef struct {
  Elf32_Word l_name;       /**< Offset to library name in string table. */
  Elf32_Word l_time_stamp; /**< Timestamp of the library. */
  Elf32_Word l_checksum;   /**< Checksum for integrity. */
  Elf32_Word l_version;    /**< Interface version. */
  Elf32_Word l_flags;      /**< Flags describing library properties. */
} Elf32_Lib;

/**
 * @struct Elf64_Lib
 * @brief Library dependency information for 64-bit ELF.
 */
typedef struct {
  Elf64_Word l_name;       /**< Offset to library name in string table. */
  Elf64_Word l_time_stamp; /**< Timestamp of the library. */
  Elf64_Word l_checksum;   /**< Checksum for integrity. */  
  Elf64_Word l_version;    /**< Interface version. */
  Elf64_Word l_flags;      /**< Flags describing library properties. */
} Elf64_Lib;




#define LL_NONE                      0 /**< No specific linking library flags set */
#define LL_EXACT_MATCH               (1 << 0) /**< Exact match linking library flag */
#define LL_IGNORE_INT_VER            (1 << 1) /**< Ignore internal version during linking */
#define LL_REQUIRE_MINOR             (1 << 2) /**< Require a minor version match for linking */
#define LL_EXPORTS                   (1 << 3) /**< Export symbols from the linking library */
#define LL_DELAY_LOAD                (1 << 4) /**< Flag to delay library loading */
#define LL_DELTA                     (1 << 5) /**< Delta-specific linking library flag */



/**
 * @typedef Elf32_Conflict
 * @brief Conflict table entry used in dynamic linking.
 *
 * This is typically used in symbol conflict resolution during relocations.
 */
typedef Elf32_Addr Elf32_Conflict;

/**
 * @struct Elf_MIPS_ABIFlags_v0
 * @brief MIPS ABI flags structure version 0.
 *
 * Encodes MIPS-specific ABI attributes in the `.MIPS.abiflags` section.
 */
typedef struct {
  Elf32_Half version;      /**< Version of the structure. */
  unsigned char isa_level; /**< ISA level (e.g., 1 for MIPS I). */
  unsigned char isa_rev;   /**< ISA revision. */
  unsigned char gpr_size;  /**< Size of general-purpose registers. */
  unsigned char cpr1_size; /**< Size of coprocessor 1 (FPU) registers. */
  unsigned char cpr2_size; /**< Size of coprocessor 2 registers. */
  unsigned char fp_abi;    /**< Floating-point ABI used. */
  Elf32_Word isa_ext;      /**< Bitfield of ISA extensions. */
  Elf32_Word ases;         /**< Bitfield of application-specific extensions. */
  Elf32_Word flags1;       /**< Additional processor-specific flags. */
  Elf32_Word flags2;       /**< Additional processor-specific flags. */
} Elf_MIPS_ABIFlags_v0;

#define MIPS_AFL_REG_NONE           0x00 /**< No registers selected */
#define MIPS_AFL_REG_32             0x01 /**< 32-bit registers selected */
#define MIPS_AFL_REG_64             0x02 /**< 64-bit registers selected */
#define MIPS_AFL_REG_128            0x03 /**< 128-bit registers selected */

#define MIPS_AFL_ASE_DSP            0x00000001 /**< Digital Signal Processing (DSP) ASE */
#define MIPS_AFL_ASE_DSPR2          0x00000002 /**< DSP R2 ASE */
#define MIPS_AFL_ASE_EVA            0x00000004 /**< Enhanced Virtual Addressing (EVA) ASE */
#define MIPS_AFL_ASE_MCU            0x00000008 /**< Microcontroller (MCU) ASE */
#define MIPS_AFL_ASE_MDMX           0x00000010 /**< MDMX ASE (MIPS SIMD) */
#define MIPS_AFL_ASE_MIPS3D         0x00000020 /**< MIPS 3D ASE */
#define MIPS_AFL_ASE_MT             0x00000040 /**< Multi-threading (MT) ASE */
#define MIPS_AFL_ASE_SMARTMIPS      0x00000080 /**< SmartMIPS ASE */
#define MIPS_AFL_ASE_VIRT           0x00000100 /**< Virtual ASE */
#define MIPS_AFL_ASE_MSA            0x00000200 /**< MIPS SIMD Architecture (MSA) ASE */
#define MIPS_AFL_ASE_MIPS16         0x00000400 /**< MIPS16 ASE (16-bit instructions) */
#define MIPS_AFL_ASE_MICROMIPS      0x00000800 /**< MicroMIPS ASE (compact encoding) */
#define MIPS_AFL_ASE_XPA            0x00001000 /**< XPA ASE (extended physical addressing) */
#define MIPS_AFL_ASE_MASK           0x00001fff /**< Mask for all ASE flags */

#define MIPS_AFL_EXT_XLR            1 /**< XLR Extension */
#define MIPS_AFL_EXT_OCTEON2        2 /**< Octeon2 Extension */
#define MIPS_AFL_EXT_OCTEONP        3 /**< OcteonP Extension */
#define MIPS_AFL_EXT_LOONGSON_3A    4 /**< Loongson 3A Extension */
#define MIPS_AFL_EXT_OCTEON         5 /**< Octeon Extension */
#define MIPS_AFL_EXT_5900           6 /**< 5900 Extension */
#define MIPS_AFL_EXT_4650           7 /**< 4650 Extension */
#define MIPS_AFL_EXT_4010           8 /**< 4010 Extension */
#define MIPS_AFL_EXT_4100           9 /**< 4100 Extension */
#define MIPS_AFL_EXT_3900           10 /**< 3900 Extension */
#define MIPS_AFL_EXT_10000          11 /**< 10000 Extension */
#define MIPS_AFL_EXT_SB1            12 /**< SB1 Extension */
#define MIPS_AFL_EXT_4111           13 /**< 4111 Extension */
#define MIPS_AFL_EXT_4120           14 /**< 4120 Extension */
#define MIPS_AFL_EXT_5400           15 /**< 5400 Extension */
#define MIPS_AFL_EXT_5500           16 /**< 5500 Extension */
#define MIPS_AFL_EXT_LOONGSON_2E    17 /**< Loongson 2E Extension */
#define MIPS_AFL_EXT_LOONGSON_2F    18 /**< Loongson 2F Extension */

#define MIPS_AFL_FLAGS1_ODDSPREG    1 /**< Odd Special Registers flag */


/**
 * @enum
 * @brief MIPS floating-point ABI types used in the `.MIPS.abiflags` section.
 *
 * These values describe the floating-point ABI in use, as encoded in the `fp_abi` field
 * of the `Elf_MIPS_ABIFlags_v0` structure.
 */
enum
{
  Val_GNU_MIPS_ABI_FP_ANY = 0,    /**< Unknown or unspecified FP ABI. */
  Val_GNU_MIPS_ABI_FP_DOUBLE = 1, /**< Double-precision hard-float. */
  Val_GNU_MIPS_ABI_FP_SINGLE = 2, /**< Single-precision hard-float. */
  Val_GNU_MIPS_ABI_FP_SOFT = 3,   /**< Software-emulated floating-point. */
  Val_GNU_MIPS_ABI_FP_OLD_64 = 4, /**< Old 64-bit FPU calling convention. */
  Val_GNU_MIPS_ABI_FP_XX = 5,     /**< No float arguments passed in float registers. */
  Val_GNU_MIPS_ABI_FP_64 = 6,     /**< New 64-bit FPU calling convention. */
  Val_GNU_MIPS_ABI_FP_64A = 7,    /**< New 64-bit FPU calling convention with 64-bit alignment. */
  Val_GNU_MIPS_ABI_FP_MAX = 7     /**< Maximum valid FP ABI value. */
};




#define EF_PARISC_TRAPNIL	0x00010000
#define EF_PARISC_EXT		0x00020000
#define EF_PARISC_LSB		0x00040000
#define EF_PARISC_WIDE		0x00080000
#define EF_PARISC_NO_KABP	0x00100000

#define EF_PARISC_LAZYSWAP	0x00400000
#define EF_PARISC_ARCH		0x0000ffff



#define EFA_PARISC_1_0		    0x020b
#define EFA_PARISC_1_1		    0x0210
#define EFA_PARISC_2_0		    0x0214



#define SHN_PARISC_ANSI_COMMON	0xff00

#define SHN_PARISC_HUGE_COMMON	0xff01



#define SHT_PARISC_EXT		0x70000000
#define SHT_PARISC_UNWIND	0x70000001
#define SHT_PARISC_DOC		0x70000002



#define SHF_PARISC_SHORT	0x20000000
#define SHF_PARISC_HUGE		0x40000000
#define SHF_PARISC_SBP		0x80000000



#define STT_PARISC_MILLICODE	13

#define STT_HP_OPAQUE		(STT_LOOS + 0x1)
#define STT_HP_STUB		(STT_LOOS + 0x2)



#define R_PARISC_NONE		0
#define R_PARISC_DIR32		1
#define R_PARISC_DIR21L		2
#define R_PARISC_DIR17R		3
#define R_PARISC_DIR17F		4
#define R_PARISC_DIR14R		6
#define R_PARISC_PCREL32	9
#define R_PARISC_PCREL21L	10
#define R_PARISC_PCREL17R	11
#define R_PARISC_PCREL17F	12
#define R_PARISC_PCREL14R	14
#define R_PARISC_DPREL21L	18
#define R_PARISC_DPREL14R	22
#define R_PARISC_GPREL21L	26
#define R_PARISC_GPREL14R	30
#define R_PARISC_LTOFF21L	34
#define R_PARISC_LTOFF14R	38
#define R_PARISC_SECREL32	41
#define R_PARISC_SEGBASE	48
#define R_PARISC_SEGREL32	49
#define R_PARISC_PLTOFF21L	50
#define R_PARISC_PLTOFF14R	54
#define R_PARISC_LTOFF_FPTR32	57
#define R_PARISC_LTOFF_FPTR21L	58
#define R_PARISC_LTOFF_FPTR14R	62
#define R_PARISC_FPTR64		64
#define R_PARISC_PLABEL32	65
#define R_PARISC_PLABEL21L	66
#define R_PARISC_PLABEL14R	70
#define R_PARISC_PCREL64	72
#define R_PARISC_PCREL22F	74
#define R_PARISC_PCREL14WR	75
#define R_PARISC_PCREL14DR	76
#define R_PARISC_PCREL16F	77
#define R_PARISC_PCREL16WF	78
#define R_PARISC_PCREL16DF	79
#define R_PARISC_DIR64		80
#define R_PARISC_DIR14WR	83
#define R_PARISC_DIR14DR	84
#define R_PARISC_DIR16F		85
#define R_PARISC_DIR16WF	86
#define R_PARISC_DIR16DF	87
#define R_PARISC_GPREL64	88
#define R_PARISC_GPREL14WR	91
#define R_PARISC_GPREL14DR	92
#define R_PARISC_GPREL16F	93
#define R_PARISC_GPREL16WF	94
#define R_PARISC_GPREL16DF	95
#define R_PARISC_LTOFF64	96
#define R_PARISC_LTOFF14WR	99
#define R_PARISC_LTOFF14DR	100
#define R_PARISC_LTOFF16F	101
#define R_PARISC_LTOFF16WF	102
#define R_PARISC_LTOFF16DF	103
#define R_PARISC_SECREL64	104
#define R_PARISC_SEGREL64	112
#define R_PARISC_PLTOFF14WR	115
#define R_PARISC_PLTOFF14DR	116
#define R_PARISC_PLTOFF16F	117
#define R_PARISC_PLTOFF16WF	118
#define R_PARISC_PLTOFF16DF	119
#define R_PARISC_LTOFF_FPTR64	120
#define R_PARISC_LTOFF_FPTR14WR	123
#define R_PARISC_LTOFF_FPTR14DR	124
#define R_PARISC_LTOFF_FPTR16F	125
#define R_PARISC_LTOFF_FPTR16WF	126
#define R_PARISC_LTOFF_FPTR16DF	127
#define R_PARISC_LORESERVE	128
#define R_PARISC_COPY		128
#define R_PARISC_IPLT		129
#define R_PARISC_EPLT		130
#define R_PARISC_TPREL32	153
#define R_PARISC_TPREL21L	154
#define R_PARISC_TPREL14R	158
#define R_PARISC_LTOFF_TP21L	162
#define R_PARISC_LTOFF_TP14R	166
#define R_PARISC_LTOFF_TP14F	167
#define R_PARISC_TPREL64	216
#define R_PARISC_TPREL14WR	219
#define R_PARISC_TPREL14DR	220
#define R_PARISC_TPREL16F	221
#define R_PARISC_TPREL16WF	222
#define R_PARISC_TPREL16DF	223
#define R_PARISC_LTOFF_TP64	224
#define R_PARISC_LTOFF_TP14WR	227
#define R_PARISC_LTOFF_TP14DR	228
#define R_PARISC_LTOFF_TP16F	229
#define R_PARISC_LTOFF_TP16WF	230
#define R_PARISC_LTOFF_TP16DF	231
#define R_PARISC_GNU_VTENTRY	232
#define R_PARISC_GNU_VTINHERIT	233
#define R_PARISC_TLS_GD21L	234
#define R_PARISC_TLS_GD14R	235
#define R_PARISC_TLS_GDCALL	236
#define R_PARISC_TLS_LDM21L	237
#define R_PARISC_TLS_LDM14R	238
#define R_PARISC_TLS_LDMCALL	239
#define R_PARISC_TLS_LDO21L	240
#define R_PARISC_TLS_LDO14R	241
#define R_PARISC_TLS_DTPMOD32	242
#define R_PARISC_TLS_DTPMOD64	243
#define R_PARISC_TLS_DTPOFF32	244
#define R_PARISC_TLS_DTPOFF64	245
#define R_PARISC_TLS_LE21L	R_PARISC_TPREL21L
#define R_PARISC_TLS_LE14R	R_PARISC_TPREL14R
#define R_PARISC_TLS_IE21L	R_PARISC_LTOFF_TP21L
#define R_PARISC_TLS_IE14R	R_PARISC_LTOFF_TP14R
#define R_PARISC_TLS_TPREL32	R_PARISC_TPREL32
#define R_PARISC_TLS_TPREL64	R_PARISC_TPREL64
#define R_PARISC_HIRESERVE	255



#define PT_HP_TLS		(PT_LOOS + 0x0)
#define PT_HP_CORE_NONE		(PT_LOOS + 0x1)
#define PT_HP_CORE_VERSION	(PT_LOOS + 0x2)
#define PT_HP_CORE_KERNEL	(PT_LOOS + 0x3)
#define PT_HP_CORE_COMM		(PT_LOOS + 0x4)
#define PT_HP_CORE_PROC		(PT_LOOS + 0x5)
#define PT_HP_CORE_LOADABLE	(PT_LOOS + 0x6)
#define PT_HP_CORE_STACK	(PT_LOOS + 0x7)
#define PT_HP_CORE_SHM		(PT_LOOS + 0x8)
#define PT_HP_CORE_MMF		(PT_LOOS + 0x9)
#define PT_HP_PARALLEL		(PT_LOOS + 0x10)
#define PT_HP_FASTBIND		(PT_LOOS + 0x11)
#define PT_HP_OPT_ANNOT		(PT_LOOS + 0x12)
#define PT_HP_HSL_ANNOT		(PT_LOOS + 0x13)
#define PT_HP_STACK		(PT_LOOS + 0x14)

#define PT_PARISC_ARCHEXT	0x70000000
#define PT_PARISC_UNWIND	0x70000001



#define PF_PARISC_SBP		0x08000000

#define PF_HP_PAGE_SIZE		0x00100000
#define PF_HP_FAR_SHARED	0x00200000
#define PF_HP_NEAR_SHARED	0x00400000
#define PF_HP_CODE		0x01000000
#define PF_HP_MODIFY		0x02000000
#define PF_HP_LAZYSWAP		0x04000000
#define PF_HP_SBP		0x08000000






#define EF_ALPHA_32BIT		1
#define EF_ALPHA_CANRELAX	2




#define SHT_ALPHA_DEBUG		0x70000001
#define SHT_ALPHA_REGINFO	0x70000002



#define SHF_ALPHA_GPREL		0x10000000


#define STO_ALPHA_NOPV		0x80
#define STO_ALPHA_STD_GPLOAD	0x88



#define R_ALPHA_NONE		0
#define R_ALPHA_REFLONG		1
#define R_ALPHA_REFQUAD		2
#define R_ALPHA_GPREL32		3
#define R_ALPHA_LITERAL		4
#define R_ALPHA_LITUSE		5
#define R_ALPHA_GPDISP		6
#define R_ALPHA_BRADDR		7
#define R_ALPHA_HINT		8
#define R_ALPHA_SREL16		9
#define R_ALPHA_SREL32		10
#define R_ALPHA_SREL64		11
#define R_ALPHA_GPRELHIGH	17
#define R_ALPHA_GPRELLOW	18
#define R_ALPHA_GPREL16		19
#define R_ALPHA_COPY		24
#define R_ALPHA_GLOB_DAT	25
#define R_ALPHA_JMP_SLOT	26
#define R_ALPHA_RELATIVE	27
#define R_ALPHA_TLS_GD_HI	28
#define R_ALPHA_TLSGD		29
#define R_ALPHA_TLS_LDM		30
#define R_ALPHA_DTPMOD64	31
#define R_ALPHA_GOTDTPREL	32
#define R_ALPHA_DTPREL64	33
#define R_ALPHA_DTPRELHI	34
#define R_ALPHA_DTPRELLO	35
#define R_ALPHA_DTPREL16	36
#define R_ALPHA_GOTTPREL	37
#define R_ALPHA_TPREL64		38
#define R_ALPHA_TPRELHI		39
#define R_ALPHA_TPRELLO		40
#define R_ALPHA_TPREL16		41

#define R_ALPHA_NUM		46


#define LITUSE_ALPHA_ADDR	0
#define LITUSE_ALPHA_BASE	1
#define LITUSE_ALPHA_BYTOFF	2
#define LITUSE_ALPHA_JSR	3
#define LITUSE_ALPHA_TLS_GD	4
#define LITUSE_ALPHA_TLS_LDM	5


#define DT_ALPHA_PLTRO		(DT_LOPROC + 0)
#define DT_ALPHA_NUM		1




#define EF_PPC_EMB		0x80000000


#define EF_PPC_RELOCATABLE	0x00010000
#define EF_PPC_RELOCATABLE_LIB	0x00008000



#define R_PPC_NONE		0
#define R_PPC_ADDR32		1
#define R_PPC_ADDR24		2
#define R_PPC_ADDR16		3
#define R_PPC_ADDR16_LO		4
#define R_PPC_ADDR16_HI		5
#define R_PPC_ADDR16_HA		6
#define R_PPC_ADDR14		7
#define R_PPC_ADDR14_BRTAKEN	8
#define R_PPC_ADDR14_BRNTAKEN	9
#define R_PPC_REL24		10
#define R_PPC_REL14		11
#define R_PPC_REL14_BRTAKEN	12
#define R_PPC_REL14_BRNTAKEN	13
#define R_PPC_GOT16		14
#define R_PPC_GOT16_LO		15
#define R_PPC_GOT16_HI		16
#define R_PPC_GOT16_HA		17
#define R_PPC_PLTREL24		18
#define R_PPC_COPY		19
#define R_PPC_GLOB_DAT		20
#define R_PPC_JMP_SLOT		21
#define R_PPC_RELATIVE		22
#define R_PPC_LOCAL24PC		23
#define R_PPC_UADDR32		24
#define R_PPC_UADDR16		25
#define R_PPC_REL32		26
#define R_PPC_PLT32		27
#define R_PPC_PLTREL32		28
#define R_PPC_PLT16_LO		29
#define R_PPC_PLT16_HI		30
#define R_PPC_PLT16_HA		31
#define R_PPC_SDAREL16		32
#define R_PPC_SECTOFF		33
#define R_PPC_SECTOFF_LO	34
#define R_PPC_SECTOFF_HI	35
#define R_PPC_SECTOFF_HA	36


#define R_PPC_TLS		67
#define R_PPC_DTPMOD32		68
#define R_PPC_TPREL16		69
#define R_PPC_TPREL16_LO	70
#define R_PPC_TPREL16_HI	71
#define R_PPC_TPREL16_HA	72
#define R_PPC_TPREL32		73
#define R_PPC_DTPREL16		74
#define R_PPC_DTPREL16_LO	75
#define R_PPC_DTPREL16_HI	76
#define R_PPC_DTPREL16_HA	77
#define R_PPC_DTPREL32		78
#define R_PPC_GOT_TLSGD16	79
#define R_PPC_GOT_TLSGD16_LO	80
#define R_PPC_GOT_TLSGD16_HI	81
#define R_PPC_GOT_TLSGD16_HA	82
#define R_PPC_GOT_TLSLD16	83
#define R_PPC_GOT_TLSLD16_LO	84
#define R_PPC_GOT_TLSLD16_HI	85
#define R_PPC_GOT_TLSLD16_HA	86
#define R_PPC_GOT_TPREL16	87
#define R_PPC_GOT_TPREL16_LO	88
#define R_PPC_GOT_TPREL16_HI	89
#define R_PPC_GOT_TPREL16_HA	90
#define R_PPC_GOT_DTPREL16	91
#define R_PPC_GOT_DTPREL16_LO	92
#define R_PPC_GOT_DTPREL16_HI	93
#define R_PPC_GOT_DTPREL16_HA	94
#define R_PPC_TLSGD		95
#define R_PPC_TLSLD		96


#define R_PPC_EMB_NADDR32	101
#define R_PPC_EMB_NADDR16	102
#define R_PPC_EMB_NADDR16_LO	103
#define R_PPC_EMB_NADDR16_HI	104
#define R_PPC_EMB_NADDR16_HA	105
#define R_PPC_EMB_SDAI16	106
#define R_PPC_EMB_SDA2I16	107
#define R_PPC_EMB_SDA2REL	108
#define R_PPC_EMB_SDA21		109
#define R_PPC_EMB_MRKREF	110
#define R_PPC_EMB_RELSEC16	111
#define R_PPC_EMB_RELST_LO	112
#define R_PPC_EMB_RELST_HI	113
#define R_PPC_EMB_RELST_HA	114
#define R_PPC_EMB_BIT_FLD	115
#define R_PPC_EMB_RELSDA	116


#define R_PPC_DIAB_SDA21_LO	180
#define R_PPC_DIAB_SDA21_HI	181
#define R_PPC_DIAB_SDA21_HA	182
#define R_PPC_DIAB_RELSDA_LO	183
#define R_PPC_DIAB_RELSDA_HI	184
#define R_PPC_DIAB_RELSDA_HA	185


#define R_PPC_IRELATIVE		248


#define R_PPC_REL16		249
#define R_PPC_REL16_LO		250
#define R_PPC_REL16_HI		251
#define R_PPC_REL16_HA		252



#define R_PPC_TOC16		255


#define DT_PPC_GOT		(DT_LOPROC + 0)
#define DT_PPC_OPT		(DT_LOPROC + 1)
#define DT_PPC_NUM		2

#define PPC_OPT_TLS		1


#define R_PPC64_NONE		R_PPC_NONE
#define R_PPC64_ADDR32		R_PPC_ADDR32
#define R_PPC64_ADDR24		R_PPC_ADDR24
#define R_PPC64_ADDR16		R_PPC_ADDR16
#define R_PPC64_ADDR16_LO	R_PPC_ADDR16_LO
#define R_PPC64_ADDR16_HI	R_PPC_ADDR16_HI
#define R_PPC64_ADDR16_HA	R_PPC_ADDR16_HA
#define R_PPC64_ADDR14		R_PPC_ADDR14
#define R_PPC64_ADDR14_BRTAKEN	R_PPC_ADDR14_BRTAKEN
#define R_PPC64_ADDR14_BRNTAKEN	R_PPC_ADDR14_BRNTAKEN
#define R_PPC64_REL24		R_PPC_REL24
#define R_PPC64_REL14		R_PPC_REL14
#define R_PPC64_REL14_BRTAKEN	R_PPC_REL14_BRTAKEN
#define R_PPC64_REL14_BRNTAKEN	R_PPC_REL14_BRNTAKEN
#define R_PPC64_GOT16		R_PPC_GOT16
#define R_PPC64_GOT16_LO	R_PPC_GOT16_LO
#define R_PPC64_GOT16_HI	R_PPC_GOT16_HI
#define R_PPC64_GOT16_HA	R_PPC_GOT16_HA

#define R_PPC64_COPY		R_PPC_COPY
#define R_PPC64_GLOB_DAT	R_PPC_GLOB_DAT
#define R_PPC64_JMP_SLOT	R_PPC_JMP_SLOT
#define R_PPC64_RELATIVE	R_PPC_RELATIVE

#define R_PPC64_UADDR32		R_PPC_UADDR32
#define R_PPC64_UADDR16		R_PPC_UADDR16
#define R_PPC64_REL32		R_PPC_REL32
#define R_PPC64_PLT32		R_PPC_PLT32
#define R_PPC64_PLTREL32	R_PPC_PLTREL32
#define R_PPC64_PLT16_LO	R_PPC_PLT16_LO
#define R_PPC64_PLT16_HI	R_PPC_PLT16_HI
#define R_PPC64_PLT16_HA	R_PPC_PLT16_HA

#define R_PPC64_SECTOFF		R_PPC_SECTOFF
#define R_PPC64_SECTOFF_LO	R_PPC_SECTOFF_LO
#define R_PPC64_SECTOFF_HI	R_PPC_SECTOFF_HI
#define R_PPC64_SECTOFF_HA	R_PPC_SECTOFF_HA
#define R_PPC64_ADDR30		37
#define R_PPC64_ADDR64		38
#define R_PPC64_ADDR16_HIGHER	39
#define R_PPC64_ADDR16_HIGHERA	40
#define R_PPC64_ADDR16_HIGHEST	41
#define R_PPC64_ADDR16_HIGHESTA	42
#define R_PPC64_UADDR64		43
#define R_PPC64_REL64		44
#define R_PPC64_PLT64		45
#define R_PPC64_PLTREL64	46
#define R_PPC64_TOC16		47
#define R_PPC64_TOC16_LO	48
#define R_PPC64_TOC16_HI	49
#define R_PPC64_TOC16_HA	50
#define R_PPC64_TOC		51
#define R_PPC64_PLTGOT16	52
#define R_PPC64_PLTGOT16_LO	53
#define R_PPC64_PLTGOT16_HI	54
#define R_PPC64_PLTGOT16_HA	55

#define R_PPC64_ADDR16_DS	56
#define R_PPC64_ADDR16_LO_DS	57
#define R_PPC64_GOT16_DS	58
#define R_PPC64_GOT16_LO_DS	59
#define R_PPC64_PLT16_LO_DS	60
#define R_PPC64_SECTOFF_DS	61
#define R_PPC64_SECTOFF_LO_DS	62
#define R_PPC64_TOC16_DS	63
#define R_PPC64_TOC16_LO_DS	64
#define R_PPC64_PLTGOT16_DS	65
#define R_PPC64_PLTGOT16_LO_DS	66


#define R_PPC64_TLS		67
#define R_PPC64_DTPMOD64	68
#define R_PPC64_TPREL16		69
#define R_PPC64_TPREL16_LO	70
#define R_PPC64_TPREL16_HI	71
#define R_PPC64_TPREL16_HA	72
#define R_PPC64_TPREL64		73
#define R_PPC64_DTPREL16	74
#define R_PPC64_DTPREL16_LO	75
#define R_PPC64_DTPREL16_HI	76
#define R_PPC64_DTPREL16_HA	77
#define R_PPC64_DTPREL64	78
#define R_PPC64_GOT_TLSGD16	79
#define R_PPC64_GOT_TLSGD16_LO	80
#define R_PPC64_GOT_TLSGD16_HI	81
#define R_PPC64_GOT_TLSGD16_HA	82
#define R_PPC64_GOT_TLSLD16	83
#define R_PPC64_GOT_TLSLD16_LO	84
#define R_PPC64_GOT_TLSLD16_HI	85
#define R_PPC64_GOT_TLSLD16_HA	86
#define R_PPC64_GOT_TPREL16_DS	87
#define R_PPC64_GOT_TPREL16_LO_DS 88
#define R_PPC64_GOT_TPREL16_HI	89
#define R_PPC64_GOT_TPREL16_HA	90
#define R_PPC64_GOT_DTPREL16_DS	91
#define R_PPC64_GOT_DTPREL16_LO_DS 92
#define R_PPC64_GOT_DTPREL16_HI	93
#define R_PPC64_GOT_DTPREL16_HA	94
#define R_PPC64_TPREL16_DS	95
#define R_PPC64_TPREL16_LO_DS	96
#define R_PPC64_TPREL16_HIGHER	97
#define R_PPC64_TPREL16_HIGHERA	98
#define R_PPC64_TPREL16_HIGHEST	99
#define R_PPC64_TPREL16_HIGHESTA 100
#define R_PPC64_DTPREL16_DS	101
#define R_PPC64_DTPREL16_LO_DS	102
#define R_PPC64_DTPREL16_HIGHER	103
#define R_PPC64_DTPREL16_HIGHERA 104
#define R_PPC64_DTPREL16_HIGHEST 105
#define R_PPC64_DTPREL16_HIGHESTA 106
#define R_PPC64_TLSGD		107
#define R_PPC64_TLSLD		108
#define R_PPC64_TOCSAVE		109
#define R_PPC64_ADDR16_HIGH	110
#define R_PPC64_ADDR16_HIGHA	111
#define R_PPC64_TPREL16_HIGH	112
#define R_PPC64_TPREL16_HIGHA	113
#define R_PPC64_DTPREL16_HIGH	114
#define R_PPC64_DTPREL16_HIGHA	115


#define R_PPC64_JMP_IREL	247
#define R_PPC64_IRELATIVE	248
#define R_PPC64_REL16		249
#define R_PPC64_REL16_LO	250
#define R_PPC64_REL16_HI	251
#define R_PPC64_REL16_HA	252

#define EF_PPC64_ABI	3

#define DT_PPC64_GLINK  (DT_LOPROC + 0)
#define DT_PPC64_OPD	(DT_LOPROC + 1)
#define DT_PPC64_OPDSZ	(DT_LOPROC + 2)
#define DT_PPC64_OPT	(DT_LOPROC + 3)
#define DT_PPC64_NUM	4

#define PPC64_OPT_TLS		1
#define PPC64_OPT_MULTI_TOC	2
#define PPC64_OPT_LOCALENTRY	4

#define STO_PPC64_LOCAL_BIT	5
#define STO_PPC64_LOCAL_MASK	0xe0
#define PPC64_LOCAL_ENTRY_OFFSET(x) (1 << (((x)&0xe0)>>5) & 0xfc)


#define EF_ARM_RELEXEC		0x01
#define EF_ARM_HASENTRY		0x02
#define EF_ARM_INTERWORK	0x04
#define EF_ARM_APCS_26		0x08
#define EF_ARM_APCS_FLOAT	0x10
#define EF_ARM_PIC		0x20
#define EF_ARM_ALIGN8		0x40
#define EF_ARM_NEW_ABI		0x80
#define EF_ARM_OLD_ABI		0x100
#define EF_ARM_SOFT_FLOAT	0x200
#define EF_ARM_VFP_FLOAT	0x400
#define EF_ARM_MAVERICK_FLOAT	0x800

#define EF_ARM_ABI_FLOAT_SOFT	0x200
#define EF_ARM_ABI_FLOAT_HARD	0x400


#define EF_ARM_SYMSARESORTED	0x04
#define EF_ARM_DYNSYMSUSESEGIDX	0x08
#define EF_ARM_MAPSYMSFIRST	0x10
#define EF_ARM_EABIMASK		0XFF000000


#define EF_ARM_BE8	    0x00800000
#define EF_ARM_LE8	    0x00400000

#define EF_ARM_EABI_VERSION(flags)	((flags) & EF_ARM_EABIMASK)
#define EF_ARM_EABI_UNKNOWN	0x00000000
#define EF_ARM_EABI_VER1	0x01000000
#define EF_ARM_EABI_VER2	0x02000000
#define EF_ARM_EABI_VER3	0x03000000
#define EF_ARM_EABI_VER4	0x04000000
#define EF_ARM_EABI_VER5	0x05000000


#define STT_ARM_TFUNC		STT_LOPROC
#define STT_ARM_16BIT		STT_HIPROC


#define SHF_ARM_ENTRYSECT	0x10000000
#define SHF_ARM_COMDEF		0x80000000



#define PF_ARM_SB		0x10000000

#define PF_ARM_PI		0x20000000
#define PF_ARM_ABS		0x40000000


#define PT_ARM_EXIDX		(PT_LOPROC + 1)


#define SHT_ARM_EXIDX		(SHT_LOPROC + 1)
#define SHT_ARM_PREEMPTMAP	(SHT_LOPROC + 2)
#define SHT_ARM_ATTRIBUTES	(SHT_LOPROC + 3)

/** 
 * \defgroup R_AARCH64 Relocation Types for AArch64
 * \brief A collection of relocation types for AArch64 architecture.
 * @{
 */

#define R_AARCH64_NONE            0
/** \name P32 Relocation Types */
#define R_AARCH64_P32_ABS32        1  /**< P32 Absolute relocation, 32-bit. */
#define R_AARCH64_P32_COPY         180 /**< P32 Copy relocation. */
#define R_AARCH64_P32_GLOB_DAT     181 /**< P32 Global Data relocation. */
#define R_AARCH64_P32_JUMP_SLOT    182 /**< P32 Jump Slot relocation. */
#define R_AARCH64_P32_RELATIVE     183 /**< P32 Relative relocation. */
#define R_AARCH64_P32_TLS_DTPMOD   184 /**< P32 TLS DTP Mod relocation. */
#define R_AARCH64_P32_TLS_DTPREL   185 /**< P32 TLS DTP Relocation. */
#define R_AARCH64_P32_TLS_TPREL    186 /**< P32 TLS TP Relocation. */
#define R_AARCH64_P32_TLSDESC      187 /**< P32 TLS Desc relocation. */
#define R_AARCH64_P32_IRELATIVE    188 /**< P32 I-relative relocation. */
/** @} */
/** \name Absolute Relocation Types */
#define R_AARCH64_ABS64            257 /**< Absolute relocation, 64-bit. */
#define R_AARCH64_ABS32            258 /**< Absolute relocation, 32-bit. */
#define R_AARCH64_ABS16            259 /**< Absolute relocation, 16-bit. */
/** @} */
/** \name Preload Relocation Types */
#define R_AARCH64_PREL64           260 /**< Preload relocation for 64-bit addresses. */
#define R_AARCH64_PREL32           261 /**< Preload relocation for 32-bit addresses. */
#define R_AARCH64_PREL16           262 /**< Preload relocation for 16-bit addresses. */
/** @} */
/** \name Move-Wide Unsigned Absolute Relocation Types */
#define R_AARCH64_MOVW_UABS_G0     263 /**< Move Wide Unsigned Absolute relocation for G0. */
#define R_AARCH64_MOVW_UABS_G0_NC  264 /**< Move Wide Unsigned Absolute relocation for G0, no carry. */
#define R_AARCH64_MOVW_UABS_G1     265 /**< Move Wide Unsigned Absolute relocation for G1. */
#define R_AARCH64_MOVW_UABS_G1_NC  266 /**< Move Wide Unsigned Absolute relocation for G1, no carry. */
#define R_AARCH64_MOVW_UABS_G2     267 /**< Move Wide Unsigned Absolute relocation for G2. */
#define R_AARCH64_MOVW_UABS_G2_NC  268 /**< Move Wide Unsigned Absolute relocation for G2, no carry. */
#define R_AARCH64_MOVW_UABS_G3     269 /**< Move Wide Unsigned Absolute relocation for G3. */
/** @} */
/** \name Move-Wide Signed Absolute Relocation Types */
#define R_AARCH64_MOVW_SABS_G0     270 /**< Move Wide Signed Absolute relocation for G0. */
#define R_AARCH64_MOVW_SABS_G1     271 /**< Move Wide Signed Absolute relocation for G1. */
#define R_AARCH64_MOVW_SABS_G2     272 /**< Move Wide Signed Absolute relocation for G2. */
/** @} */
/** \name Load/Store Relocation Types */
#define R_AARCH64_LD_PREL_LO19     273 /**< Load Preload LO19 for 64-bit addresses. */
#define R_AARCH64_ADR_PREL_LO21    274 /**< ADR Preload LO21 for 64-bit addresses. */
#define R_AARCH64_ADR_PREL_PG_HI21 275 /**< ADR Preload PG Hi21 for 64-bit addresses. */
#define R_AARCH64_ADR_PREL_PG_HI21_NC 276 /**< ADR Preload PG Hi21 for 64-bit addresses, no carry. */
#define R_AARCH64_ADD_ABS_LO12_NC  277 /**< Add Absolute relocation for low 12 bits, no carry. */
#define R_AARCH64_LDST8_ABS_LO12_NC 278 /**< Load/Store 8-bit Absolute relocation, low 12 bits, no carry. */
/** @} */
/** \name Branch and Jump Relocation Types */
#define R_AARCH64_TSTBR14          279 /**< Test Branch relocation for 14-bit addresses. */
#define R_AARCH64_CONDBR19         280 /**< Conditional Branch relocation for 19-bit addresses. */
#define R_AARCH64_JUMP26           282 /**< Jump relocation for 26-bit addresses. */
#define R_AARCH64_CALL26           283 /**< Call relocation for 26-bit addresses. */
/** @} */
/** \name Load/Store Relocation Types */
#define R_AARCH64_LDST16_ABS_LO12_NC 284 /**< Load/Store 16-bit Absolute relocation, low 12 bits, no carry. */
#define R_AARCH64_LDST32_ABS_LO12_NC 285 /**< Load/Store 32-bit Absolute relocation, low 12 bits, no carry. */
#define R_AARCH64_LDST64_ABS_LO12_NC 286 /**< Load/Store 64-bit Absolute relocation, low 12 bits, no carry. */
#define R_AARCH64_LDST128_ABS_LO12_NC 299 /**< Load/Store 128-bit Absolute relocation, low 12 bits, no carry. */
/** @} */
/** \name Move-Wide Preload Relocation Types */
#define R_AARCH64_MOVW_PREL_G0     287 /**< Move Wide Preload relocation for G0. */
#define R_AARCH64_MOVW_PREL_G0_NC  288 /**< Move Wide Preload relocation for G0, no carry. */
#define R_AARCH64_MOVW_PREL_G1     289 /**< Move Wide Preload relocation for G1. */
#define R_AARCH64_MOVW_PREL_G1_NC  290 /**< Move Wide Preload relocation for G1, no carry. */
#define R_AARCH64_MOVW_PREL_G2     291 /**< Move Wide Preload relocation for G2. */
#define R_AARCH64_MOVW_PREL_G2_NC  292 /**< Move Wide Preload relocation for G2, no carry. */
#define R_AARCH64_MOVW_PREL_G3     293 /**< Move Wide Preload relocation for G3. */
/** @} */
/** \name Global Offset Table (GOT) Relocation Types */
#define R_AARCH64_MOVW_GOTOFF_G0   300 /**< Global Offset relocation for G0. */
#define R_AARCH64_MOVW_GOTOFF_G0_NC 301 /**< Global Offset relocation for G0, no carry. */
#define R_AARCH64_MOVW_GOTOFF_G1   302 /**< Global Offset relocation for G1. */
#define R_AARCH64_MOVW_GOTOFF_G1_NC 303 /**< Global Offset relocation for G1, no carry. */
#define R_AARCH64_MOVW_GOTOFF_G2   304 /**< Global Offset relocation for G2. */
#define R_AARCH64_MOVW_GOTOFF_G2_NC 305 /**< Global Offset relocation for G2, no carry. */
#define R_AARCH64_MOVW_GOTOFF_G3   306 /**< Global Offset relocation for G3. */
/** @} */
/** \name GOT Relocation Types */
#define R_AARCH64_GOTREL64         307 /**< GOT Relative relocation for 64-bit addresses. */
#define R_AARCH64_GOTREL32         308 /**< GOT Relative relocation for 32-bit addresses. */
#define R_AARCH64_GOT_LD_PREL19    309 /**< GOT Load Preload LO19 relocation. */
#define R_AARCH64_LD64_GOTOFF_LO15 310 /**< Load 64-bit Global Offset relocation for low 15 bits. */
#define R_AARCH64_ADR_GOT_PAGE     311 /**< ADR Global Offset Page relocation. */
#define R_AARCH64_LD64_GOT_LO12_NC 312 /**< Load 64-bit Global Offset relocation, low 12 bits, no carry. */
#define R_AARCH64_LD64_GOTPAGE_LO15 313 /**< Load 64-bit Global Offset Page relocation, low 15 bits. */
/** @} */
/** \name TLS Global Descriptor Relocation Types */
#define R_AARCH64_TLSGD_ADR_PREL21 512 /**< TLS Global Descriptor Preload relocation for 21-bit addresses. */
#define R_AARCH64_TLSGD_ADR_PAGE21 513 /**< TLS Global Descriptor Page Preload relocation for 21-bit addresses. */
#define R_AARCH64_TLSGD_ADD_LO12_NC 514 /**< TLS Global Descriptor Add LO12 relocation, no carry. */
#define R_AARCH64_TLSGD_MOVW_G1    515 /**< TLS Global Descriptor Move for G1. */
#define R_AARCH64_TLSGD_MOVW_G0_NC 516 /**< TLS Global Descriptor Move for G0, no carry. */
/** @} */
/** \name TLS Local Descriptor Relocation Types */
#define R_AARCH64_TLSLD_ADR_PREL21     517 /**< TLSLD Address Preload relocation for 21-bit addresses. */
#define R_AARCH64_TLSLD_ADR_PAGE21     518 /**< TLSLD Address Page relocation for 21-bit addresses. */
#define R_AARCH64_TLSLD_ADD_LO12_NC    519 /**< TLSLD Add LO12 relocation, no carry. */
#define R_AARCH64_TLSLD_MOVW_G1        520 /**< TLSLD Move Wide relocation for G1. */
#define R_AARCH64_TLSLD_MOVW_G0_NC     521 /**< TLSLD Move Wide relocation for G0, no carry. */
#define R_AARCH64_TLSLD_LD_PREL19      522 /**< TLSLD Load Preload LO19 relocation. */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G2 523 /**< TLSLD Move Wide DTP-relative relocation for G2. */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G1 524 /**< TLSLD Move Wide DTP-relative relocation for G1. */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G1_NC 525 /**< TLSLD Move Wide DTP-relative relocation for G1, no carry. */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G0 526 /**< TLSLD Move Wide DTP-relative relocation for G0. */
#define R_AARCH64_TLSLD_MOVW_DTPREL_G0_NC 527 /**< TLSLD Move Wide DTP-relative relocation for G0, no carry. */
#define R_AARCH64_TLSLD_ADD_DTPREL_HI12 528 /**< TLSLD Add DTP-relative High 12 bits relocation. */
#define R_AARCH64_TLSLD_ADD_DTPREL_LO12 529 /**< TLSLD Add DTP-relative Low 12 bits relocation. */
#define R_AARCH64_TLSLD_ADD_DTPREL_LO12_NC 530 /**< TLSLD Add DTP-relative Low 12 bits relocation, no carry. */
#define R_AARCH64_TLSLD_LDST8_DTPREL_LO12 531 /**< TLSLD Load/Store 8-bit DTP-relative relocation, low 12 bits. */
#define R_AARCH64_TLSLD_LDST8_DTPREL_LO12_NC 532 /**< TLSLD Load/Store 8-bit DTP-relative relocation, low 12 bits, no carry. */
#define R_AARCH64_TLSLD_LDST16_DTPREL_LO12 533 /**< TLSLD Load/Store 16-bit DTP-relative relocation, low 12 bits. */
#define R_AARCH64_TLSLD_LDST16_DTPREL_LO12_NC 534 /**< TLSLD Load/Store 16-bit DTP-relative relocation, low 12 bits, no carry. */
#define R_AARCH64_TLSLD_LDST32_DTPREL_LO12 535 /**< TLSLD Load/Store 32-bit DTP-relative relocation, low 12 bits. */
#define R_AARCH64_TLSLD_LDST32_DTPREL_LO12_NC 536 /**< TLSLD Load/Store 32-bit DTP-relative relocation, low 12 bits, no carry. */
#define R_AARCH64_TLSLD_LDST64_DTPREL_LO12 537 /**< TLSLD Load/Store 64-bit DTP-relative relocation, low 12 bits. */
#define R_AARCH64_TLSLD_LDST64_DTPREL_LO12_NC 538 /**< TLSLD Load/Store 64-bit DTP-relative relocation, low 12 bits, no carry. */
/** @} */
/** \name TLS Immediate Relocation Types */
#define R_AARCH64_TLSIE_MOVW_GOTTPREL_G1     539 /**< TLSIE Move Wide GOT TP-relative relocation for G1. */
#define R_AARCH64_TLSIE_MOVW_GOTTPREL_G0_NC  540 /**< TLSIE Move Wide GOT TP-relative relocation for G0, no carry. */
#define R_AARCH64_TLSIE_ADR_GOTTPREL_PAGE21  541 /**< TLSIE Address GOT TP-relative relocation for 21-bit page. */
#define R_AARCH64_TLSIE_LD64_GOTTPREL_LO12_NC 542 /**< TLSIE Load 64-bit GOT TP-relative relocation, low 12 bits, no carry. */
#define R_AARCH64_TLSIE_LD_GOTTPREL_PREL19   543 /**< TLSIE Load GOT TP-relative Preload relocation for 19-bit. */
/** @} */
/** \name TLS Little Endian Relocation Types */
#define R_AARCH64_TLSLE_MOVW_TPREL_G2        544 /**< TLSLE Move Wide TPREL relocation for G2. */
#define R_AARCH64_TLSLE_MOVW_TPREL_G1        545 /**< TLSLE Move Wide TPREL relocation for G1. */
#define R_AARCH64_TLSLE_MOVW_TPREL_G1_NC     546 /**< TLSLE Move Wide TPREL relocation for G1, no carry. */
#define R_AARCH64_TLSLE_MOVW_TPREL_G0        547 /**< TLSLE Move Wide TPREL relocation for G0. */
#define R_AARCH64_TLSLE_MOVW_TPREL_G0_NC     548 /**< TLSLE Move Wide TPREL relocation for G0, no carry. */
#define R_AARCH64_TLSLE_ADD_TPREL_HI12       549 /**< TLSLE Add TPREL High 12 bits relocation. */
#define R_AARCH64_TLSLE_ADD_TPREL_LO12       550 /**< TLSLE Add TPREL Low 12 bits relocation. */
#define R_AARCH64_TLSLE_ADD_TPREL_LO12_NC    551 /**< TLSLE Add TPREL Low 12 bits relocation, no carry. */
#define R_AARCH64_TLSLE_LDST8_TPREL_LO12     552 /**< TLSLE Load/Store 8-bit TPREL relocation, low 12 bits. */
#define R_AARCH64_TLSLE_LDST8_TPREL_LO12_NC  553 /**< TLSLE Load/Store 8-bit TPREL relocation, low 12 bits, no carry. */
#define R_AARCH64_TLSLE_LDST16_TPREL_LO12    554 /**< TLSLE Load/Store 16-bit TPREL relocation, low 12 bits. */
#define R_AARCH64_TLSLE_LDST16_TPREL_LO12_NC 555 /**< TLSLE Load/Store 16-bit TPREL relocation, low 12 bits, no carry. */
#define R_AARCH64_TLSLE_LDST32_TPREL_LO12    556 /**< TLSLE Load/Store 32-bit TPREL relocation, low 12 bits. */
#define R_AARCH64_TLSLE_LDST32_TPREL_LO12_NC 557 /**< TLSLE Load/Store 32-bit TPREL relocation, low 12 bits, no carry. */
#define R_AARCH64_TLSLE_LDST64_TPREL_LO12    558 /**< TLSLE Load/Store 64-bit TPREL relocation, low 12 bits. */
#define R_AARCH64_TLSLE_LDST64_TPREL_LO12_NC 559 /**< TLSLE Load/Store 64-bit TPREL relocation, low 12 bits, no carry. */
/** @} */
/** \name TLS Descriptor Relocation Types */
#define R_AARCH64_TLSDESC_LD_PREL19         560 /**< TLSDESC Load Preload 19-bit relocation. */
#define R_AARCH64_TLSDESC_ADR_PREL21        561 /**< TLSDESC Address Preload 21-bit relocation. */
#define R_AARCH64_TLSDESC_ADR_PAGE21        562 /**< TLSDESC Address 21-bit page relocation. */
#define R_AARCH64_TLSDESC_LD64_LO12         563 /**< TLSDESC Load 64-bit, low 12 bits relocation. */
#define R_AARCH64_TLSDESC_ADD_LO12          564 /**< TLSDESC Add Low 12 bits relocation. */
#define R_AARCH64_TLSDESC_OFF_G1            565 /**< TLSDESC Offset G1 relocation. */
#define R_AARCH64_TLSDESC_OFF_G0_NC         566 /**< TLSDESC Offset G0, no carry relocation. */
#define R_AARCH64_TLSDESC_LDR               567 /**< TLSDESC Load Register relocation. */
#define R_AARCH64_TLSDESC_ADD               568 /**< TLSDESC Add relocation. */
#define R_AARCH64_TLSDESC_CALL              569 /**< TLSDESC Call relocation. */
/** @} */
/** \name TLS Little Endian and TLS Load Relocation Types */
#define R_AARCH64_TLSLE_LDST128_TPREL_LO12  570 /**< TLSLE Load/Store 128-bit TPREL relocation, low 12 bits. */
#define R_AARCH64_TLSLE_LDST128_TPREL_LO12_NC 571 /**< TLSLE Load/Store 128-bit TPREL relocation, low 12 bits, no carry. */
#define R_AARCH64_TLSLD_LDST128_DTPREL_LO12 572 /**< TLSLD Load/Store 128-bit DTPREL relocation, low 12 bits. */
#define R_AARCH64_TLSLD_LDST128_DTPREL_LO12_NC 573 /**< TLSLD Load/Store 128-bit DTPREL relocation, low 12 bits, no carry. */
/** @} */
/** \name General Relocation Types */
#define R_AARCH64_COPY             1024 /**< Copy relocation. */
#define R_AARCH64_GLOB_DAT         1025 /**< Global Data relocation. */
#define R_AARCH64_JUMP_SLOT        1026 /**< Jump Slot relocation. */
#define R_AARCH64_RELATIVE         1027 /**< Relative relocation. */
/** @} */
/** \name Abstract TLS Relocation Types */
#define R_AARCH64_TLS_DTPMOD     1028 /**< Module index for dynamic TLS (generic form). */
#define R_AARCH64_TLS_DTPMOD64   1028 /**< Module index for dynamic TLS (64-bit form). */
#define R_AARCH64_TLS_DTPREL     1029 /**< Offset from module's TLS block for dynamic TLS (generic form). */
#define R_AARCH64_TLS_DTPREL64   1029 /**< Offset from module's TLS block for dynamic TLS (64-bit form). */
#define R_AARCH64_TLS_TPREL      1030 /**< Offset from thread pointer for static TLS (generic form). */
#define R_AARCH64_TLS_TPREL64    1030 /**< Offset from thread pointer for static TLS (64-bit form). */
#define R_AARCH64_TLSDESC        1031 /**< Marker relocation for TLS Descriptor used in the TLSDESC ABI. */
/** @} */
/** @} */


/** @defgroup ElfRelocARM ARM ELF Relocation Types
 *  @brief ELF relocation types for the ARM architecture.
 *  @{
 */
#define R_ARM_NONE                 0   ///< No relocation
#define R_ARM_PC24                 1   ///< PC-relative 24-bit
#define R_ARM_ABS32                2   ///< Direct 32-bit
#define R_ARM_REL32                3   ///< PC-relative 32-bit
#define R_ARM_PC13                 4   ///< PC-relative 13-bit
#define R_ARM_ABS16                5   ///< Direct 16-bit
#define R_ARM_ABS12                6   ///< Direct 12-bit
#define R_ARM_THM_ABS5             7   ///< Thumb mode, 5-bit absolute
#define R_ARM_ABS8                 8   ///< Direct 8-bit
#define R_ARM_SBREL32              9   ///< Static base relative 32-bit
#define R_ARM_THM_PC22            10   ///< Thumb mode, PC-relative 22-bit
#define R_ARM_THM_PC8             11   ///< Thumb mode, PC-relative 8-bit
#define R_ARM_AMP_VCALL9          12   ///< VCALL instruction (virtual call)
#define R_ARM_TLS_DESC            13   ///< TLS descriptor
#define R_ARM_THM_SWI8            14   ///< Thumb mode, software interrupt 8-bit
#define R_ARM_XPC25               15   ///< Extended PC-relative 25-bit
#define R_ARM_THM_XPC22           16   ///< Thumb mode, extended PC-relative 22-bit
#define R_ARM_TLS_DTPMOD32        17   ///< TLS module index, 32-bit
#define R_ARM_TLS_DTPOFF32        18   ///< TLS offset in module, 32-bit
#define R_ARM_TLS_TPOFF32         19   ///< TLS offset in TLS block, 32-bit
#define R_ARM_COPY                20   ///< Copy symbol at runtime
#define R_ARM_GLOB_DAT            21   ///< Global data
#define R_ARM_JUMP_SLOT           22   ///< PLT entry
#define R_ARM_RELATIVE            23   ///< Relative relocation
#define R_ARM_GOTOFF              24   ///< Offset to GOT
#define R_ARM_GOTPC               25   ///< PC-relative offset to GOT
#define R_ARM_GOT32               26   ///< 32-bit GOT entry
#define R_ARM_PLT32               27   ///< 32-bit PLT address
#define R_ARM_CALL                28   ///< Call target
#define R_ARM_JUMP24              29   ///< 24-bit jump
#define R_ARM_THM_JUMP24          30   ///< Thumb mode, 24-bit jump
#define R_ARM_BASE_ABS            31   ///< Absolute base address
#define R_ARM_ALU_PCREL_7_0       32   ///< PC-relative ALU, bits 7:0
#define R_ARM_ALU_PCREL_15_8      33   ///< PC-relative ALU, bits 15:8
#define R_ARM_ALU_PCREL_23_15     34   ///< PC-relative ALU, bits 23:15
#define R_ARM_LDR_SBREL_11_0      35   ///< LDR static base relative, bits 11:0
#define R_ARM_ALU_SBREL_19_12     36   ///< ALU static base relative, bits 19:12
#define R_ARM_ALU_SBREL_27_20     37   ///< ALU static base relative, bits 27:20
#define R_ARM_TARGET1             38   ///< Target relocation 1
#define R_ARM_SBREL31             39   ///< Static base relative, bit 31
#define R_ARM_V4BX                40   ///< V4BX transition
#define R_ARM_TARGET2             41   ///< Target relocation 2
#define R_ARM_PREL31              42   ///< PC-relative, bit 31
#define R_ARM_MOVW_ABS_NC         43   ///< MOVW, absolute, no check
#define R_ARM_MOVT_ABS            44   ///< MOVT, absolute
#define R_ARM_MOVW_PREL_NC        45   ///< MOVW, PC-relative, no check
#define R_ARM_MOVT_PREL           46   ///< MOVT, PC-relative
#define R_ARM_THM_MOVW_ABS_NC     47   ///< Thumb MOVW, absolute, no check
#define R_ARM_THM_MOVT_ABS        48   ///< Thumb MOVT, absolute
#define R_ARM_THM_MOVW_PREL_NC    49   ///< Thumb MOVW, PC-relative, no check
#define R_ARM_THM_MOVT_PREL       50   ///< Thumb MOVT, PC-relative
#define R_ARM_THM_JUMP19          51   ///< Thumb mode, 19-bit jump
#define R_ARM_THM_JUMP6           52   ///< Thumb mode, 6-bit jump
#define R_ARM_THM_ALU_PREL_11_0   53   ///< Thumb ALU, PC-relative, bits 11:0
#define R_ARM_THM_PC12            54   ///< Thumb PC-relative, bits 11:0
#define R_ARM_ABS32_NOI           55   ///< Absolute 32-bit, no instruction
#define R_ARM_REL32_NOI           56   ///< Relative 32-bit, no instruction
#define R_ARM_ALU_PC_G0_NC        57   ///< ALU, PC-relative group 0, no check
#define R_ARM_ALU_PC_G0           58   ///< ALU, PC-relative group 0
#define R_ARM_ALU_PC_G1_NC        59   ///< ALU, PC-relative group 1, no check
#define R_ARM_ALU_PC_G1           60   ///< ALU, PC-relative group 1
#define R_ARM_ALU_PC_G2           61   ///< ALU, PC-relative group 2
#define R_ARM_LDR_PC_G1           62   ///< LDR, PC-relative group 1
#define R_ARM_LDR_PC_G2           63   ///< LDR, PC-relative group 2
#define R_ARM_LDRS_PC_G0          64   ///< LDRS, PC-relative group 0
#define R_ARM_LDRS_PC_G1          65   ///< LDRS, PC-relative group 1
#define R_ARM_LDRS_PC_G2          66   ///< LDRS, PC-relative group 2
#define R_ARM_LDC_PC_G0           67   ///< LDC, PC-relative group 0
#define R_ARM_LDC_PC_G1           68   ///< LDC, PC-relative group 1
#define R_ARM_LDC_PC_G2           69   ///< LDC, PC-relative group 2
#define R_ARM_ALU_SB_G0_NC        70   ///< ALU, static base group 0, no check
#define R_ARM_ALU_SB_G0           71   ///< ALU, static base group 0
#define R_ARM_ALU_SB_G1_NC        72   ///< ALU, static base group 1, no check
#define R_ARM_ALU_SB_G1           73   ///< ALU, static base group 1
#define R_ARM_ALU_SB_G2           74   ///< ALU, static base group 2
#define R_ARM_LDR_SB_G0           75   ///< LDR, static base group 0
#define R_ARM_LDR_SB_G1           76   ///< LDR, static base group 1
#define R_ARM_LDR_SB_G2           77   ///< LDR, static base group 2
#define R_ARM_LDRS_SB_G0          78   ///< LDRS, static base group 0
#define R_ARM_LDRS_SB_G1          79   ///< LDRS, static base group 1
#define R_ARM_LDRS_SB_G2          80   ///< LDRS, static base group 2
#define R_ARM_LDC_SB_G0           81   ///< LDC, static base group 0
#define R_ARM_LDC_SB_G1           82   ///< LDC, static base group 1
#define R_ARM_LDC_SB_G2           83   ///< LDC, static base group 2
#define R_ARM_MOVW_BREL_NC        84   ///< MOVW, GOT-relative, no check
#define R_ARM_MOVT_BREL           85   ///< MOVT, GOT-relative
#define R_ARM_MOVW_BREL           86   ///< MOVW, GOT-relative
#define R_ARM_THM_MOVW_BREL_NC    87   ///< Thumb MOVW, GOT-relative, no check
#define R_ARM_THM_MOVT_BREL       88   ///< Thumb MOVT, GOT-relative
#define R_ARM_THM_MOVW_BREL       89   ///< Thumb MOVW, GOT-relative
#define R_ARM_TLS_GOTDESC         90   ///< TLS GOT descriptor
#define R_ARM_TLS_CALL            91   ///< TLS call
#define R_ARM_TLS_DESCSEQ         92   ///< TLS descriptor sequence
#define R_ARM_THM_TLS_CALL        93   ///< Thumb TLS call
#define R_ARM_PLT32_ABS           94   ///< Absolute PLT 32-bit
#define R_ARM_GOT_ABS             95   ///< Absolute GOT entry
#define R_ARM_GOT_PREL            96   ///< PC-relative GOT entry
#define R_ARM_GOT_BREL12          97   ///< 12-bit GOT-relative
#define R_ARM_GOTOFF12            98   ///< 12-bit offset to GOT
#define R_ARM_GOTRELAX            99   ///< GOT entry relax
#define R_ARM_GNU_VTENTRY        100   ///< GNU vtable entry
#define R_ARM_GNU_VTINHERIT      101   ///< GNU vtable inheritance
#define R_ARM_THM_PC11           102   ///< Thumb PC-relative 11-bit
#define R_ARM_THM_PC9            103   ///< Thumb PC-relative 9-bit
#define R_ARM_TLS_GD32           104   ///< TLS general dynamic model
#define R_ARM_TLS_LDM32          105   ///< TLS local dynamic model
#define R_ARM_TLS_LDO32          106   ///< TLS local dynamic offset
#define R_ARM_TLS_IE32           107   ///< TLS initial exec model
#define R_ARM_TLS_LE32           108   ///< TLS local exec model
#define R_ARM_TLS_LDO12          109   ///< TLS 12-bit local dynamic offset
#define R_ARM_TLS_LE12           110   ///< TLS 12-bit local exec offset
#define R_ARM_TLS_IE12GP         111   ///< TLS 12-bit initial exec GP offset
#define R_ARM_ME_TOO             128   ///< Reserved (ME TOO)
#define R_ARM_THM_TLS_DESCSEQ    129   ///< Thumb TLS descriptor sequence
#define R_ARM_THM_TLS_DESCSEQ16  129   ///< Thumb TLS desc seq (16-bit alias)
#define R_ARM_THM_TLS_DESCSEQ32  130   ///< Thumb TLS desc seq (32-bit)
#define R_ARM_THM_GOT_BREL12     131   ///< Thumb GOT-relative 12-bit
#define R_ARM_IRELATIVE          160   ///< Indirect relative relocation
#define R_ARM_RXPC25             249   ///< RX PC-relative 25-bit
#define R_ARM_RSBREL32           250   ///< Read-only static base rel. 32-bit
#define R_ARM_THM_RPC22          251   ///< Thumb PC-relative call
#define R_ARM_RREL32             252   ///< Read-only relative 32-bit
#define R_ARM_RABS22             253   ///< Read-only absolute 22-bit
#define R_ARM_RPC24              254   ///< Read-only PC-relative 24-bit
#define R_ARM_RBASE              255   ///< Read-only base address

#define R_ARM_NUM                256   ///< Number of ARM relocation types
/** @} */


/** @defgroup ElfRelocCKCore C-SKY CKCore ELF Relocation Types
 *  @brief Relocation types for the C-SKY CKCore architecture.
 *  @{
 */
#define R_CKCORE_NONE               0   ///< No relocation
#define R_CKCORE_ADDR32             1   ///< Direct 32-bit address
#define R_CKCORE_PCRELIMM8BY4       2   ///< 8-bit PC-relative offset (multiplied by 4)
#define R_CKCORE_PCRELIMM11BY2      3   ///< 11-bit PC-relative offset (multiplied by 2)
#define R_CKCORE_PCREL32            5   ///< 32-bit PC-relative address
#define R_CKCORE_PCRELJSR_IMM11BY2  6   ///< 11-bit PC-relative jump offset for JSR (×2)
#define R_CKCORE_RELATIVE           9   ///< Relative relocation
#define R_CKCORE_COPY               10  ///< Runtime copy of symbol
#define R_CKCORE_GLOB_DAT           11  ///< Global data
#define R_CKCORE_JUMP_SLOT          12  ///< PLT entry
#define R_CKCORE_GOTOFF             13  ///< Offset to GOT
#define R_CKCORE_GOTPC              14  ///< PC-relative offset to GOT
#define R_CKCORE_GOT32              15  ///< 32-bit GOT entry
#define R_CKCORE_PLT32              16  ///< 32-bit PLT address
#define R_CKCORE_ADDRGOT            17  ///< Address of GOT entry
#define R_CKCORE_ADDRPLT            18  ///< Address of PLT entry
#define R_CKCORE_PCREL_IMM26BY2     19  ///< 26-bit PC-relative offset (×2)
#define R_CKCORE_PCREL_IMM16BY2     20  ///< 16-bit PC-relative offset (×2)
#define R_CKCORE_PCREL_IMM16BY4     21  ///< 16-bit PC-relative offset (×4)
#define R_CKCORE_PCREL_IMM10BY2     22  ///< 10-bit PC-relative offset (×2)
#define R_CKCORE_PCREL_IMM10BY4     23  ///< 10-bit PC-relative offset (×4)
#define R_CKCORE_ADDR_HI16          24  ///< High 16 bits of address
#define R_CKCORE_ADDR_LO16          25  ///< Low 16 bits of address
#define R_CKCORE_GOTPC_HI16         26  ///< High 16 bits of PC-relative GOT offset
#define R_CKCORE_GOTPC_LO16         27  ///< Low 16 bits of PC-relative GOT offset
#define R_CKCORE_GOTOFF_HI16        28  ///< High 16 bits of GOT offset
#define R_CKCORE_GOTOFF_LO16        29  ///< Low 16 bits of GOT offset
#define R_CKCORE_GOT12              30  ///< 12-bit GOT entry
#define R_CKCORE_GOT_HI16           31  ///< High 16 bits of GOT entry
#define R_CKCORE_GOT_LO16           32  ///< Low 16 bits of GOT entry
#define R_CKCORE_PLT12              33  ///< 12-bit PLT entry
#define R_CKCORE_PLT_HI16           34  ///< High 16 bits of PLT entry
#define R_CKCORE_PLT_LO16           35  ///< Low 16 bits of PLT entry
#define R_CKCORE_ADDRGOT_HI16       36  ///< High 16 bits of GOT address
#define R_CKCORE_ADDRGOT_LO16       37  ///< Low 16 bits of GOT address
#define R_CKCORE_ADDRPLT_HI16       38  ///< High 16 bits of PLT address
#define R_CKCORE_ADDRPLT_LO16       39  ///< Low 16 bits of PLT address
#define R_CKCORE_PCREL_JSR_IMM26BY2 40  ///< 26-bit PC-relative offset for JSR (×2)
#define R_CKCORE_TOFFSET_LO16       41  ///< Low 16 bits of TLS offset
#define R_CKCORE_DOFFSET_LO16       42  ///< Low 16 bits of DTP offset
#define R_CKCORE_PCREL_IMM18BY2     43  ///< 18-bit PC-relative offset (×2)
#define R_CKCORE_DOFFSET_IMM18      44  ///< 18-bit DTP offset
#define R_CKCORE_DOFFSET_IMM18BY2   45  ///< 18-bit DTP offset (×2)
#define R_CKCORE_DOFFSET_IMM18BY4   46  ///< 18-bit DTP offset (×4)
#define R_CKCORE_GOT_IMM18BY4       48  ///< 18-bit GOT offset (×4)
#define R_CKCORE_PLT_IMM18BY4       49  ///< 18-bit PLT offset (×4)
#define R_CKCORE_PCREL_IMM7BY4      50  ///< 7-bit PC-relative offset (×4)
#define R_CKCORE_TLS_LE32           51  ///< TLS local exec model, 32-bit
#define R_CKCORE_TLS_IE32           52  ///< TLS initial exec model, 32-bit
#define R_CKCORE_TLS_GD32           53  ///< TLS global dynamic model, 32-bit
#define R_CKCORE_TLS_LDM32          54  ///< TLS local dynamic model, 32-bit
#define R_CKCORE_TLS_LDO32          55  ///< TLS LDO relocation
#define R_CKCORE_TLS_DTPMOD32       56  ///< TLS module index
#define R_CKCORE_TLS_DTPOFF32       57  ///< TLS offset in module
#define R_CKCORE_TLS_TPOFF32        58  ///< TLS offset in TLS block
/** @} */

/** @defgroup ElfIA64Flags IA-64 ELF Flags and Relocations
 *  @brief Flags, section types, program types, and dynamic tags for IA-64 architecture.
 *  @{
 */
#define EF_IA_64_MASKOS     0x0000000f  ///< OS-specific flags
#define EF_IA_64_ABI64      0x00000010  ///< 64-bit ABI flag
#define EF_IA_64_ARCH       0xff000000  ///< Architecture version mask

#define PT_IA_64_ARCHEXT    (PT_LOPROC + 0)  ///< Architecture extension segment
#define PT_IA_64_UNWIND     (PT_LOPROC + 1)  ///< Unwind segment
#define PT_IA_64_HP_OPT_ANOT (PT_LOOS + 0x12) ///< HP optimization annotation
#define PT_IA_64_HP_HSL_ANOT (PT_LOOS + 0x13) ///< HP HSL annotation
#define PT_IA_64_HP_STACK   (PT_LOOS + 0x14) ///< HP stack segment

#define PF_IA_64_NORECOV    0x80000000  ///< Non-recoverable segment flag

#define SHT_IA_64_EXT       (SHT_LOPROC + 0) ///< IA-64 extension section
#define SHT_IA_64_UNWIND    (SHT_LOPROC + 1) ///< IA-64 unwind section

#define SHF_IA_64_SHORT     0x10000000  ///< Section uses short addressing
#define SHF_IA_64_NORECOV   0x20000000  ///< Section is non-recoverable

#define DT_IA_64_PLT_RESERVE (DT_LOPROC + 0) ///< Reserved entry for PLT
#define DT_IA_64_NUM        1           ///< Number of IA-64 specific dynamic tags
/** @} */

/** @defgroup RelocIA64 IA-64 Relocation Types
 *  ELF relocation types for the IA-64 (Itanium) architecture.
 *  @{
 */
#define R_IA64_NONE             0x00 /**< No relocation. */
#define R_IA64_IMM14            0x21 /**< 14-bit immediate relocation. */
#define R_IA64_IMM22            0x22 /**< 22-bit immediate relocation. */
#define R_IA64_IMM64            0x23 /**< 64-bit immediate relocation. */
#define R_IA64_DIR32MSB         0x24 /**< 32-bit direct MSB relocation. */
#define R_IA64_DIR32LSB         0x25 /**< 32-bit direct LSB relocation. */
#define R_IA64_DIR64MSB         0x26 /**< 64-bit direct MSB relocation. */
#define R_IA64_DIR64LSB         0x27 /**< 64-bit direct LSB relocation. */
#define R_IA64_GPREL22          0x2a /**< 22-bit GP-relative relocation. */
#define R_IA64_GPREL64I         0x2b /**< 64-bit GP-relative immediate relocation. */
#define R_IA64_GPREL32MSB       0x2c /**< 32-bit GP-relative MSB relocation. */
#define R_IA64_GPREL32LSB       0x2d /**< 32-bit GP-relative LSB relocation. */
#define R_IA64_GPREL64MSB       0x2e /**< 64-bit GP-relative MSB relocation. */
#define R_IA64_GPREL64LSB       0x2f /**< 64-bit GP-relative LSB relocation. */
#define R_IA64_LTOFF22          0x32 /**< 22-bit LTOFF relocation. */
#define R_IA64_LTOFF64I         0x33 /**< 64-bit LTOFF immediate relocation. */
#define R_IA64_PLTOFF22         0x3a /**< 22-bit PLTOFF relocation. */
#define R_IA64_PLTOFF64I        0x3b /**< 64-bit PLTOFF immediate relocation. */
#define R_IA64_PLTOFF64MSB      0x3e /**< 64-bit PLTOFF MSB relocation. */
#define R_IA64_PLTOFF64LSB      0x3f /**< 64-bit PLTOFF LSB relocation. */
#define R_IA64_FPTR64I          0x43 /**< 64-bit function pointer immediate relocation. */
#define R_IA64_FPTR32MSB        0x44 /**< 32-bit function pointer MSB relocation. */
#define R_IA64_FPTR32LSB        0x45 /**< 32-bit function pointer LSB relocation. */
#define R_IA64_FPTR64MSB        0x46 /**< 64-bit function pointer MSB relocation. */
#define R_IA64_FPTR64LSB        0x47 /**< 64-bit function pointer LSB relocation. */
#define R_IA64_PCREL60B         0x48 /**< 60-bit PC-relative branch relocation. */
#define R_IA64_PCREL21B         0x49 /**< 21-bit PC-relative branch relocation. */
#define R_IA64_PCREL21M         0x4a /**< 21-bit PC-relative memory relocation. */
#define R_IA64_PCREL21F         0x4b /**< 21-bit PC-relative function relocation. */
#define R_IA64_PCREL32MSB       0x4c /**< 32-bit PC-relative MSB relocation. */
#define R_IA64_PCREL32LSB       0x4d /**< 32-bit PC-relative LSB relocation. */
#define R_IA64_PCREL64MSB       0x4e /**< 64-bit PC-relative MSB relocation. */
#define R_IA64_PCREL64LSB       0x4f /**< 64-bit PC-relative LSB relocation. */
#define R_IA64_LTOFF_FPTR22     0x52 /**< 22-bit LTOFF function pointer relocation. */
#define R_IA64_LTOFF_FPTR64I    0x53 /**< 64-bit LTOFF function pointer immediate relocation. */
#define R_IA64_LTOFF_FPTR32MSB  0x54 /**< 32-bit LTOFF function pointer MSB relocation. */
#define R_IA64_LTOFF_FPTR32LSB  0x55 /**< 32-bit LTOFF function pointer LSB relocation. */
#define R_IA64_LTOFF_FPTR64MSB  0x56 /**< 64-bit LTOFF function pointer MSB relocation. */
#define R_IA64_LTOFF_FPTR64LSB  0x57 /**< 64-bit LTOFF function pointer LSB relocation. */
#define R_IA64_SEGREL32MSB      0x5c /**< 32-bit segment-relative MSB relocation. */
#define R_IA64_SEGREL32LSB      0x5d /**< 32-bit segment-relative LSB relocation. */
#define R_IA64_SEGREL64MSB      0x5e /**< 64-bit segment-relative MSB relocation. */
#define R_IA64_SEGREL64LSB      0x5f /**< 64-bit segment-relative LSB relocation. */
#define R_IA64_SECREL32MSB      0x64 /**< 32-bit section-relative MSB relocation. */
#define R_IA64_SECREL32LSB      0x65 /**< 32-bit section-relative LSB relocation. */
#define R_IA64_SECREL64MSB      0x66 /**< 64-bit section-relative MSB relocation. */
#define R_IA64_SECREL64LSB      0x67 /**< 64-bit section-relative LSB relocation. */
#define R_IA64_REL32MSB         0x6c /**< 32-bit relative MSB relocation. */
#define R_IA64_REL32LSB         0x6d /**< 32-bit relative LSB relocation. */
#define R_IA64_REL64MSB         0x6e /**< 64-bit relative MSB relocation. */
#define R_IA64_REL64LSB         0x6f /**< 64-bit relative LSB relocation. */
#define R_IA64_LTV32MSB         0x74 /**< 32-bit LTV MSB relocation. */
#define R_IA64_LTV32LSB         0x75 /**< 32-bit LTV LSB relocation. */
#define R_IA64_LTV64MSB         0x76 /**< 64-bit LTV MSB relocation. */
#define R_IA64_LTV64LSB         0x77 /**< 64-bit LTV LSB relocation. */
#define R_IA64_PCREL21BI        0x79 /**< 21-bit PC-relative indirect branch relocation. */
#define R_IA64_PCREL22          0x7a /**< 22-bit PC-relative relocation. */
#define R_IA64_PCREL64I         0x7b /**< 64-bit PC-relative immediate relocation. */
#define R_IA64_IPLTMSB          0x80 /**< MSB entry in the dynamic procedure linkage table. */
#define R_IA64_IPLTLSB          0x81 /**< LSB entry in the dynamic procedure linkage table. */
#define R_IA64_COPY             0x84 /**< Runtime copy relocation. */
#define R_IA64_SUB              0x85 /**< Subtraction relocation. */
#define R_IA64_LTOFF22X         0x86 /**< Extended LTOFF 22-bit relocation. */
#define R_IA64_LDXMOV           0x87 /**< LDXMOV relocation. */
#define R_IA64_TPREL14          0x91 /**< 14-bit thread pointer relative relocation. */
#define R_IA64_TPREL22          0x92 /**< 22-bit thread pointer relative relocation. */
#define R_IA64_TPREL64I         0x93 /**< 64-bit thread pointer relative immediate relocation. */
#define R_IA64_TPREL64MSB       0x96 /**< 64-bit thread pointer relative MSB relocation. */
#define R_IA64_TPREL64LSB       0x97 /**< 64-bit thread pointer relative LSB relocation. */
#define R_IA64_LTOFF_TPREL22    0x9a /**< 22-bit LTOFF thread pointer relative relocation. */
#define R_IA64_DTPMOD64MSB      0xa6 /**< 64-bit MSB module index relocation. */
#define R_IA64_DTPMOD64LSB      0xa7 /**< 64-bit LSB module index relocation. */
#define R_IA64_LTOFF_DTPMOD22   0xaa /**< 22-bit LTOFF module index relocation. */
#define R_IA64_DTPREL14         0xb1 /**< 14-bit DTP-relative relocation. */
#define R_IA64_DTPREL22         0xb2 /**< 22-bit DTP-relative relocation. */
#define R_IA64_DTPREL64I        0xb3 /**< 64-bit DTP-relative immediate relocation. */
#define R_IA64_DTPREL32MSB      0xb4 /**< 32-bit DTP-relative MSB relocation. */
#define R_IA64_DTPREL32LSB      0xb5 /**< 32-bit DTP-relative LSB relocation. */
#define R_IA64_DTPREL64MSB      0xb6 /**< 64-bit DTP-relative MSB relocation. */
#define R_IA64_DTPREL64LSB      0xb7 /**< 64-bit DTP-relative LSB relocation. */
#define R_IA64_LTOFF_DTPREL22   0xba /**< 22-bit LTOFF DTP-relative relocation. */
/** @} */ // end of RelocIA64

/** @defgroup ElfFlagsSH SuperH (SH) ELF Header Flags
 *  ELF `e_flags` values specific to the SH (SuperH) architecture.
 *  @{
 */
#define EF_SH_MACH_MASK    0x1f /**< Mask for machine subtype. */
#define EF_SH_UNKNOWN      0x0  /**< Unknown or unspecified SH architecture. */
#define EF_SH1             0x1  /**< SH-1 architecture. */
#define EF_SH2             0x2  /**< SH-2 architecture. */
#define EF_SH3             0x3  /**< SH-3 architecture. */
#define EF_SH_DSP          0x4  /**< SH-DSP architecture. */
#define EF_SH3_DSP         0x5  /**< SH-3-DSP architecture. */
#define EF_SH4AL_DSP       0x6  /**< SH-4AL-DSP architecture. */
#define EF_SH3E            0x8  /**< SH-3E (extended) architecture. */
#define EF_SH4             0x9  /**< SH-4 architecture. */
#define EF_SH2E            0xb  /**< SH-2E architecture. */
#define EF_SH4A            0xc  /**< SH-4A architecture. */
#define EF_SH2A            0xd  /**< SH-2A architecture. */
#define EF_SH4_NOFPU       0x10 /**< SH-4 without FPU. */
#define EF_SH4A_NOFPU      0x11 /**< SH-4A without FPU. */
#define EF_SH4_NOMMU_NOFPU 0x12 /**< SH-4 without MMU and FPU. */
#define EF_SH2A_NOFPU      0x13 /**< SH-2A without FPU. */
#define EF_SH3_NOMMU       0x14 /**< SH-3 without MMU. */
#define EF_SH2A_SH4_NOFPU  0x15 /**< Hybrid SH-2A/SH-4 without FPU. */
#define EF_SH2A_SH3_NOFPU  0x16 /**< Hybrid SH-2A/SH-3 without FPU. */
#define EF_SH2A_SH4        0x17 /**< Hybrid SH-2A/SH-4 with FPU. */
#define EF_SH2A_SH3E       0x18 /**< Hybrid SH-2A/SH-3E. */
/** @} */ // end of ElfFlagsSH

/** @defgroup RelocationSH SuperH (SH) Relocation Types
 *  ELF relocation types for Renesas SuperH (SH) architecture.
 *  @{
 */
#define R_SH_NONE           0 /**< No relocation. */
#define R_SH_DIR32          1 /**< Direct 32-bit. */
#define R_SH_REL32          2 /**< PC-relative 32-bit. */
#define R_SH_DIR8WPN        3 /**< 8-bit offset, word aligned, no base. */
#define R_SH_IND12W         4 /**< Indirect 12-bit word offset. */
#define R_SH_DIR8WPL        5 /**< 8-bit offset, word aligned, with base. */
#define R_SH_DIR8WPZ        6 /**< 8-bit offset, word aligned, zero base. */
#define R_SH_DIR8BP         7 /**< 8-bit byte offset from base. */
#define R_SH_DIR8W          8 /**< 8-bit word offset. */
#define R_SH_DIR8L          9 /**< 8-bit longword offset. */
#define R_SH_SWITCH16      25 /**< 16-bit switch table entry. */
#define R_SH_SWITCH32      26 /**< 32-bit switch table entry. */
#define R_SH_USES          27 /**< Relocation used by another. */
#define R_SH_COUNT         28 /**< Symbol reference count. */
#define R_SH_ALIGN         29 /**< Alignment directive. */
#define R_SH_CODE          30 /**< Code section relocation. */
#define R_SH_DATA          31 /**< Data section relocation. */
#define R_SH_LABEL         32 /**< Label relocation. */
#define R_SH_SWITCH8       33 /**< 8-bit switch table entry. */
#define R_SH_GNU_VTINHERIT 34 /**< GNU C++ vtable inheritance. */
#define R_SH_GNU_VTENTRY   35 /**< GNU C++ vtable entry. */
/** @name TLS Relocations
 *  Thread-Local Storage relocations for SH.
 *  @{
 */
#define R_SH_TLS_GD_32    144 /**< TLS General Dynamic 32-bit. */
#define R_SH_TLS_LD_32    145 /**< TLS Local Dynamic 32-bit. */
#define R_SH_TLS_LDO_32   146 /**< TLS Local Dynamic offset 32-bit. */
#define R_SH_TLS_IE_32    147 /**< TLS Initial Exec 32-bit. */
#define R_SH_TLS_LE_32    148 /**< TLS Local Exec 32-bit. */
#define R_SH_TLS_DTPMOD32 149 /**< TLS Module ID. */
#define R_SH_TLS_DTPOFF32 150 /**< TLS Offset in module. */
#define R_SH_TLS_TPOFF32  151 /**< TLS Offset in static block. */
/** @} */
/** @name GOT and PLT Relocations
 *  Global Offset Table and Procedure Linkage Table related.
 *  @{
 */
#define R_SH_GOT32            160 /**< 32-bit offset into GOT. */
#define R_SH_PLT32            161 /**< 32-bit PLT entry. */
#define R_SH_COPY             162 /**< Copy symbol at runtime. */
#define R_SH_GLOB_DAT         163 /**< Create GOT entry. */
#define R_SH_JMP_SLOT         164 /**< Create PLT entry. */
#define R_SH_RELATIVE         165 /**< Adjust by program base. */
#define R_SH_GOTOFF           166 /**< 32-bit offset from GOT. */
#define R_SH_GOTPC            167 /**< 32-bit PC-relative offset to GOT. */
#define R_SH_GOT20            201 /**< 20-bit GOT entry. */
#define R_SH_GOTOFF20         202 /**< 20-bit offset from GOT. */
#define R_SH_GOTFUNCDESC      203 /**< GOT entry for function descriptor. */
#define R_SH_GOTFUNCDEST20    204 /**< 20-bit GOT entry for function destination. */
#define R_SH_GOTOFFFUNCDESC   205 /**< Offset from GOT to function descriptor. */
#define R_SH_GOTOFFFUNCDEST20 206 /**< Offset from GOT to function destination. */
#define R_SH_FUNCDESC         207 /**< Function descriptor. */
#define R_SH_FUNCDESC_VALUE   208 /**< Value of function descriptor. */
/** @} */
#define R_SH_NUM              256 /**< Number of defined SH relocations. */
/** @} */ // end of RelocationSH


/** @defgroup Relocation390 IBM S/390 Relocation Types
 *  Relocation types used in ELF for IBM z/Architecture (s390).
 *  @{
 */
#define R_390_NONE         0 /**< No relocation. */
#define R_390_8            1 /**< Direct 8-bit. */
#define R_390_12           2 /**< Direct 12-bit. */
#define R_390_16           3 /**< Direct 16-bit. */
#define R_390_32           4 /**< Direct 32-bit. */
#define R_390_PC32         5 /**< PC-relative 32-bit. */
#define R_390_GOT12        6 /**< 12-bit offset into GOT. */
#define R_390_GOT32        7 /**< 32-bit offset into GOT. */
#define R_390_PLT32        8 /**< 32-bit PLT address. */
#define R_390_COPY         9 /**< Copy symbol at runtime. */
#define R_390_GLOB_DAT    10 /**< Create GOT entry. */
#define R_390_JMP_SLOT    11 /**< Create PLT entry. */
#define R_390_RELATIVE    12 /**< Adjust by program base. */
#define R_390_GOTOFF32    13 /**< 32-bit offset from GOT. */
#define R_390_GOTPC       14 /**< 32-bit PC-relative offset to GOT. */
#define R_390_GOT16       15 /**< 16-bit offset into GOT. */
#define R_390_PC16        16 /**< PC-relative 16-bit. */
#define R_390_PC16DBL     17 /**< PC-relative 16-bit shifted by 1. */
#define R_390_PLT16DBL    18 /**< PLT 16-bit shifted by 1. */
#define R_390_PC32DBL     19 /**< PC-relative 32-bit shifted by 1. */
#define R_390_PLT32DBL    20 /**< PLT 32-bit shifted by 1. */
#define R_390_GOTPCDBL    21 /**< PC-relative GOT offset shifted. */
#define R_390_64          22 /**< Direct 64-bit. */
#define R_390_PC64        23 /**< PC-relative 64-bit. */
#define R_390_GOT64       24 /**< 64-bit offset into GOT. */
#define R_390_PLT64       25 /**< 64-bit PLT address. */
#define R_390_GOTENT      26 /**< GOT entry offset. */
#define R_390_GOTOFF16    27 /**< 16-bit offset from GOT. */
#define R_390_GOTOFF64    28 /**< 64-bit offset from GOT. */
#define R_390_GOTPLT12    29 /**< 12-bit offset into GOT PLT. */
#define R_390_GOTPLT16    30 /**< 16-bit offset into GOT PLT. */
#define R_390_GOTPLT32    31 /**< 32-bit offset into GOT PLT. */
#define R_390_GOTPLT64    32 /**< 64-bit offset into GOT PLT. */
#define R_390_GOTPLTENT   33 /**< GOT PLT entry offset. */
#define R_390_PLTOFF16    34 /**< 16-bit offset from PLT. */
#define R_390_PLTOFF32    35 /**< 32-bit offset from PLT. */
#define R_390_PLTOFF64    36 /**< 64-bit offset from PLT. */
#define R_390_TLS_LOAD    37 /**< TLS load module index. */
#define R_390_TLS_GDCALL  38 /**< General Dynamic TLS call. */
#define R_390_TLS_LDCALL  39 /**< Local Dynamic TLS call. */
#define R_390_TLS_GD32    40 /**< GD 32-bit relocation. */
#define R_390_TLS_GD64    41 /**< GD 64-bit relocation. */
#define R_390_TLS_GOTIE12 42 /**< GOT entry for IE TLS, 12-bit. */
#define R_390_TLS_GOTIE32 43 /**< GOT entry for IE TLS, 32-bit. */
#define R_390_TLS_GOTIE64 44 /**< GOT entry for IE TLS, 64-bit. */
#define R_390_TLS_LDM32   45 /**< LDM 32-bit relocation. */
#define R_390_TLS_LDM64   46 /**< LDM 64-bit relocation. */
#define R_390_TLS_IE32    47 /**< Initial Exec TLS, 32-bit. */
#define R_390_TLS_IE64    48 /**< Initial Exec TLS, 64-bit. */
#define R_390_TLS_IEENT   49 /**< IE entry offset. */
#define R_390_TLS_LE32    50 /**< Local Exec TLS, 32-bit. */
#define R_390_TLS_LE64    51 /**< Local Exec TLS, 64-bit. */
#define R_390_TLS_LDO32   52 /**< LDO 32-bit. */
#define R_390_TLS_LDO64   53 /**< LDO 64-bit. */
#define R_390_TLS_DTPMOD  54 /**< Module index for TLS. */
#define R_390_TLS_DTPOFF  55 /**< Offset in TLS block. */
#define R_390_TLS_TPOFF   56 /**< Offset in static TLS block. */
#define R_390_20          57 /**< Direct 20-bit. */
#define R_390_GOT20       58 /**< 20-bit GOT offset. */
#define R_390_GOTPLT20    59 /**< 20-bit offset into GOT PLT. */
#define R_390_TLS_GOTIE20 60 /**< 20-bit IE TLS GOT entry. */
#define R_390_NUM         61 /**< Number of defined relocations. */
/** @} */ // end of Relocation390


/** @defgroup RelocationCRIS CRIS Relocation Types
 *  Relocation types for the CRIS architecture.
 *  @{
 */
#define R_CRIS_NONE           0 /**< No relocation. */
#define R_CRIS_8              1 /**< Direct 8-bit. */
#define R_CRIS_16             2 /**< Direct 16-bit. */
#define R_CRIS_32             3 /**< Direct 32-bit. */
#define R_CRIS_8_PCREL        4 /**< PC-relative 8-bit. */
#define R_CRIS_16_PCREL       5 /**< PC-relative 16-bit. */
#define R_CRIS_32_PCREL       6 /**< PC-relative 32-bit. */
#define R_CRIS_GNU_VTINHERIT  7 /**< C++ inheritance info. */
#define R_CRIS_GNU_VTENTRY    8 /**< C++ virtual table entry. */
#define R_CRIS_COPY           9 /**< Copy symbol at runtime. */
#define R_CRIS_GLOB_DAT      10 /**< Create GOT entry. */
#define R_CRIS_JUMP_SLOT     11 /**< Create PLT entry. */
#define R_CRIS_RELATIVE      12 /**< Adjust by program base. */
#define R_CRIS_16_GOT        13 /**< 16-bit GOT entry. */
#define R_CRIS_32_GOT        14 /**< 32-bit GOT entry. */
#define R_CRIS_16_GOTPLT     15 /**< 16-bit GOT PLT entry. */
#define R_CRIS_32_GOTPLT     16 /**< 32-bit GOT PLT entry. */
#define R_CRIS_32_GOTREL     17 /**< GOT-relative 32-bit. */
#define R_CRIS_32_PLT_GOTREL 18 /**< PLT GOT-relative 32-bit. */
#define R_CRIS_32_PLT_PCREL  19 /**< PC-relative to PLT. */
#define R_CRIS_NUM           20 /**< Number of defined relocations. */
/** @} */ // end of RelocationCRIS



/** @defgroup RelocationX86_64 x86_64 Relocation Types
 *  ELF relocation types for 64-bit x86 (AMD64 / Intel64).
 *  @{
 */
#define R_X86_64_NONE             0 /**< No relocation. */
#define R_X86_64_64               1 /**< Direct 64-bit. */
#define R_X86_64_PC32             2 /**< PC-relative 32-bit signed. */
#define R_X86_64_GOT32            3 /**< 32-bit GOT entry. */
#define R_X86_64_PLT32            4 /**< 32-bit PLT address. */
#define R_X86_64_COPY             5 /**< Copy symbol at runtime. */
#define R_X86_64_GLOB_DAT         6 /**< Create GOT entry. */
#define R_X86_64_JUMP_SLOT        7 /**< Create PLT entry. */
#define R_X86_64_RELATIVE         8 /**< Adjust by program base. */
#define R_X86_64_GOTPCREL         9 /**< PC-relative offset to GOT entry. */
#define R_X86_64_32              10 /**< Direct 32-bit zero extended. */
#define R_X86_64_32S             11 /**< Direct 32-bit sign extended. */
#define R_X86_64_16              12 /**< Direct 16-bit. */
#define R_X86_64_PC16            13 /**< PC-relative 16-bit. */
#define R_X86_64_8               14 /**< Direct 8-bit. */
#define R_X86_64_PC8             15 /**< PC-relative 8-bit. */
#define R_X86_64_DTPMOD64        16 /**< TLS module index. */
#define R_X86_64_DTPOFF64        17 /**< TLS offset in module. */
#define R_X86_64_TPOFF64         18 /**< Offset in static TLS block. */
#define R_X86_64_TLSGD           19 /**< TLS General Dynamic. */
#define R_X86_64_TLSLD           20 /**< TLS Local Dynamic. */
#define R_X86_64_DTPOFF32        21 /**< TLS offset 32-bit. */
#define R_X86_64_GOTTPOFF        22 /**< GOT offset for TLS. */
#define R_X86_64_TPOFF32         23 /**< Static TLS offset 32-bit. */
#define R_X86_64_PC64            24 /**< PC-relative 64-bit. */
#define R_X86_64_GOTOFF64        25 /**< 64-bit offset from GOT. */
#define R_X86_64_GOTPC32         26 /**< 32-bit PC-relative to GOT. */
#define R_X86_64_GOT64           27 /**< 64-bit GOT entry. */
#define R_X86_64_GOTPCREL64      28 /**< PC-relative 64-bit to GOT entry. */
#define R_X86_64_GOTPC64         29 /**< PC-relative to GOT. */
#define R_X86_64_GOTPLT64        30 /**< GOT entry for PLT. */
#define R_X86_64_PLTOFF64        31 /**< Offset to PLT. */
#define R_X86_64_SIZE32          32 /**< Symbol size 32-bit. */
#define R_X86_64_SIZE64          33 /**< Symbol size 64-bit. */
#define R_X86_64_GOTPC32_TLSDESC 34 /**< GOT offset for TLS descriptor. */
#define R_X86_64_TLSDESC_CALL    35 /**< Marker for TLS descriptor call. */
#define R_X86_64_TLSDESC         36 /**< TLS descriptor. */
#define R_X86_64_IRELATIVE       37 /**< Indirect relative relocation. */
#define R_X86_64_RELATIVE64      38 /**< Adjust by program base (64-bit). */
#define R_X86_64_GOTPCRELX       41 /**< Relaxed PC-relative GOT. */
#define R_X86_64_REX_GOTPCRELX   42 /**< Relaxed GOTPCRELX with REX prefix. */
#define R_X86_64_NUM             43 /**< Number of defined relocations. */
/** @} */ // end of RelocationX86_64


/**
 * @defgroup MN10300_Relocation_Types MN10300 Relocation Types
 * @brief Relocation type constants for the MN10300 architecture.
 * @{
 */
#define R_MN10300_NONE          0  /**< No relocation. */
#define R_MN10300_32            1  /**< Direct 32-bit relocation. */
#define R_MN10300_16            2  /**< Direct 16-bit relocation. */
#define R_MN10300_8             3  /**< Direct 8-bit relocation. */
#define R_MN10300_PCREL32       4  /**< 32-bit PC-relative relocation. */
#define R_MN10300_PCREL16       5  /**< 16-bit PC-relative relocation. */
#define R_MN10300_PCREL8        6  /**< 8-bit PC-relative relocation. */
#define R_MN10300_GNU_VTINHERIT 7  /**< GNU C++ vtable inheritance. */
#define R_MN10300_GNU_VTENTRY   8  /**< GNU C++ vtable entry. */
#define R_MN10300_24            9  /**< Direct 24-bit relocation. */
#define R_MN10300_GOTPC32       10 /**< 32-bit PC-relative GOT offset. */
#define R_MN10300_GOTPC16       11 /**< 16-bit PC-relative GOT offset. */
#define R_MN10300_GOTOFF32      12 /**< 32-bit offset from GOT. */
#define R_MN10300_GOTOFF24      13 /**< 24-bit offset from GOT. */
#define R_MN10300_GOTOFF16      14 /**< 16-bit offset from GOT. */
#define R_MN10300_PLT32         15 /**< 32-bit PLT entry. */
#define R_MN10300_PLT16         16 /**< 16-bit PLT entry. */
#define R_MN10300_GOT32         17 /**< 32-bit GOT entry. */
#define R_MN10300_GOT24         18 /**< 24-bit GOT entry. */
#define R_MN10300_GOT16         19 /**< 16-bit GOT entry. */
#define R_MN10300_COPY          20 /**< Runtime copy of variable. */
#define R_MN10300_GLOB_DAT      21 /**< Set GOT entry to data address. */
#define R_MN10300_JMP_SLOT      22 /**< Set GOT entry to function address. */
#define R_MN10300_RELATIVE      23 /**< Adjust by program base address. */
#define R_MN10300_NUM           24 /**< Number of relocation types defined. */
/** @} */

/**
 * @defgroup M32R_Relocation_Types M32R Relocation Types
 * @brief Relocation type constants for the M32R architecture.
 * @{
 */
#define R_M32R_NONE                0  /**< No relocation. */
#define R_M32R_16                  1  /**< Direct 16-bit relocation. */
#define R_M32R_32                  2  /**< Direct 32-bit relocation. */
#define R_M32R_24                  3  /**< Direct 24-bit relocation. */
#define R_M32R_10_PCREL            4  /**< 10-bit PC-relative relocation. */
#define R_M32R_18_PCREL            5  /**< 18-bit PC-relative relocation. */
#define R_M32R_26_PCREL            6  /**< 26-bit PC-relative relocation. */
#define R_M32R_HI16_ULO            7  /**< Upper 16 bits, unsigned. */
#define R_M32R_HI16_SLO            8  /**< Upper 16 bits, signed. */
#define R_M32R_LO16                9  /**< Lower 16 bits. */
#define R_M32R_SDA16              10  /**< Small data area 16-bit relocation. */
#define R_M32R_GNU_VTINHERIT      11  /**< GNU C++ vtable inheritance. */
#define R_M32R_GNU_VTENTRY        12  /**< GNU C++ vtable entry. */

#define R_M32R_16_RELA            33  /**< RELA 16-bit relocation. */
#define R_M32R_32_RELA            34  /**< RELA 32-bit relocation. */
#define R_M32R_24_RELA            35  /**< RELA 24-bit relocation. */
#define R_M32R_10_PCREL_RELA      36  /**< RELA 10-bit PC-relative relocation. */
#define R_M32R_18_PCREL_RELA      37  /**< RELA 18-bit PC-relative relocation. */
#define R_M32R_26_PCREL_RELA      38  /**< RELA 26-bit PC-relative relocation. */
#define R_M32R_HI16_ULO_RELA      39  /**< RELA upper 16 bits, unsigned. */
#define R_M32R_HI16_SLO_RELA      40  /**< RELA upper 16 bits, signed. */
#define R_M32R_LO16_RELA          41  /**< RELA lower 16 bits. */
#define R_M32R_SDA16_RELA         42  /**< RELA small data area. */
#define R_M32R_RELA_GNU_VTINHERIT 43  /**< RELA GNU vtable inheritance. */
#define R_M32R_RELA_GNU_VTENTRY   44  /**< RELA GNU vtable entry. */
#define R_M32R_REL32              45  /**< RELA 32-bit relative relocation. */

#define R_M32R_GOT24              48  /**< GOT entry 24-bit. */
#define R_M32R_26_PLTREL          49  /**< 26-bit PLT-relative relocation. */
#define R_M32R_COPY               50  /**< Runtime symbol copy. */
#define R_M32R_GLOB_DAT           51  /**< Create GOT data entry. */
#define R_M32R_JMP_SLOT           52  /**< Set GOT entry to function address. */
#define R_M32R_RELATIVE           53  /**< Adjust by base address. */
#define R_M32R_GOTOFF             54  /**< Offset from GOT. */
#define R_M32R_GOTPC24            55  /**< PC-relative GOT entry (24-bit). */
#define R_M32R_GOT16_HI_ULO       56  /**< GOT 16-bit upper unsigned. */

#define R_M32R_GOT16_HI_SLO       57  /**< GOT 16-bit upper signed. */

#define R_M32R_GOT16_LO           58  /**< GOT 16-bit lower. */
#define R_M32R_GOTPC_HI_ULO       59  /**< GOT PC-relative high unsigned. */

#define R_M32R_GOTPC_HI_SLO       60  /**< GOT PC-relative high signed. */

#define R_M32R_GOTPC_LO           61  /**< GOT PC-relative low. */

#define R_M32R_GOTOFF_HI_ULO      62  /**< GOT offset high unsigned. */

#define R_M32R_GOTOFF_HI_SLO      63  /**< GOT offset high signed. */

#define R_M32R_GOTOFF_LO          64  /**< GOT offset low. */
#define R_M32R_NUM                256 /**< Number of M32R relocation types defined. */
/** @} */

/**
 * @defgroup MicroBlaze_Relocation_Types MicroBlaze Relocation Types
 * @brief Relocation type constants for the Xilinx MicroBlaze architecture.
 * @{
 */
#define R_MICROBLAZE_NONE            0 /**< No relocation. */
#define R_MICROBLAZE_32              1 /**< Direct 32-bit relocation. */
#define R_MICROBLAZE_32_PCREL        2 /**< 32-bit PC-relative relocation. */
#define R_MICROBLAZE_64_PCREL        3 /**< 64-bit PC-relative relocation. */
#define R_MICROBLAZE_32_PCREL_LO     4 /**< Low 32 bits of PC-relative. */
#define R_MICROBLAZE_64              5 /**< Direct 64-bit relocation. */
#define R_MICROBLAZE_32_LO           6 /**< Low 32 bits relocation. */
#define R_MICROBLAZE_SRO32           7 /**< Store-relative offset 32-bit. */
#define R_MICROBLAZE_SRW32           8 /**< Store-relative word 32-bit. */
#define R_MICROBLAZE_64_NONE         9 /**< Reserved or unused. */
#define R_MICROBLAZE_32_SYM_OP_SYM  10 /**< Symbol operation on another symbol. */
#define R_MICROBLAZE_GNU_VTINHERIT  11 /**< GNU vtable inheritance. */
#define R_MICROBLAZE_GNU_VTENTRY    12 /**< GNU vtable entry. */
#define R_MICROBLAZE_GOTPC_64       13 /**< GOT PC-relative 64-bit. */
#define R_MICROBLAZE_GOT_64         14 /**< GOT 64-bit entry. */
#define R_MICROBLAZE_PLT_64         15 /**< PLT 64-bit entry. */
#define R_MICROBLAZE_REL            16 /**< Relative relocation. */
#define R_MICROBLAZE_JUMP_SLOT      17 /**< Set GOT entry to function address. */
#define R_MICROBLAZE_GLOB_DAT       18 /**< Set GOT entry to data address. */
#define R_MICROBLAZE_GOTOFF_64      19 /**< 64-bit offset from GOT. */
#define R_MICROBLAZE_GOTOFF_32      20 /**< 32-bit offset from GOT. */
#define R_MICROBLAZE_COPY           21 /**< Runtime copy. */
#define R_MICROBLAZE_TLS            22 /**< TLS relocation base. */
#define R_MICROBLAZE_TLSGD          23 /**< TLS General Dynamic model. */
#define R_MICROBLAZE_TLSLD          24 /**< TLS Local Dynamic model. */
#define R_MICROBLAZE_TLSDTPMOD32    25 /**< TLS module ID. */
#define R_MICROBLAZE_TLSDTPREL32    26 /**< TLS offset from DTP. */
#define R_MICROBLAZE_TLSDTPREL64    27 /**< 64-bit TLS offset from DTP. */
#define R_MICROBLAZE_TLSGOTTPREL32  28 /**< GOT entry for TLS TP offset. */
#define R_MICROBLAZE_TLSTPREL32     29 /**< TLS offset from TP. */
/** @} */

/** 
 * @defgroup NIOS2_Relocation_Types NIOS II Relocation Types
 * @brief Relocation type constants for the NIOS II architecture.
 * @{
 */
#define DT_NIOS2_GP           0x70000002 /**< Global pointer value used in NIOS II dynamic linking. */

#define R_NIOS2_NONE          0  /**< No relocation. */
#define R_NIOS2_S16           1  /**< 16-bit signed relocation. */
#define R_NIOS2_U16           2  /**< 16-bit unsigned relocation. */
#define R_NIOS2_PCREL16       3  /**< 16-bit PC-relative relocation. */
#define R_NIOS2_CALL26        4  /**< 26-bit call target relocation. */
#define R_NIOS2_IMM5          5  /**< 5-bit immediate relocation. */
#define R_NIOS2_CACHE_OPX     6  /**< Cache operation relocation. */
#define R_NIOS2_IMM6          7  /**< 6-bit immediate relocation. */
#define R_NIOS2_IMM8          8  /**< 8-bit immediate relocation. */
#define R_NIOS2_HI16          9  /**< High 16 bits of an address. */
#define R_NIOS2_LO16          10 /**< Low 16 bits of an address. */
#define R_NIOS2_HIADJ16       11 /**< High 16 bits adjusted relocation. */
#define R_NIOS2_BFD_RELOC_32  12 /**< Generic 32-bit relocation. */
#define R_NIOS2_BFD_RELOC_16  13 /**< Generic 16-bit relocation. */
#define R_NIOS2_BFD_RELOC_8   14 /**< Generic 8-bit relocation. */
#define R_NIOS2_GPREL         15 /**< GP-relative relocation. */
#define R_NIOS2_GNU_VTINHERIT 16 /**< GNU C++ vtable inheritance marker. */
#define R_NIOS2_GNU_VTENTRY   17 /**< GNU C++ vtable entry relocation. */
#define R_NIOS2_UJMP          18 /**< Unconditional jump relocation. */
#define R_NIOS2_CJMP          19 /**< Conditional jump relocation. */
#define R_NIOS2_CALLR         20 /**< Register-based call relocation. */
#define R_NIOS2_ALIGN         21 /**< Alignment filler. */
#define R_NIOS2_GOT16         22 /**< Global Offset Table 16-bit entry. */
#define R_NIOS2_CALL16        23 /**< Call target 16-bit relocation. */
#define R_NIOS2_GOTOFF_LO     24 /**< GOT offset low 16 bits. */
#define R_NIOS2_GOTOFF_HA     25 /**< GOT offset high-adjusted 16 bits. */
#define R_NIOS2_PCREL_LO      26 /**< PC-relative low 16 bits. */
#define R_NIOS2_PCREL_HA      27 /**< PC-relative high-adjusted 16 bits. */
#define R_NIOS2_TLS_GD16      28 /**< TLS General Dynamic model. */
#define R_NIOS2_TLS_LDM16     29 /**< TLS Local Dynamic model. */
#define R_NIOS2_TLS_LDO16     30 /**< TLS Local Dynamic offset. */
#define R_NIOS2_TLS_IE16      31 /**< TLS Initial Executable model. */
#define R_NIOS2_TLS_LE16      32 /**< TLS Local Executable model. */
#define R_NIOS2_TLS_DTPMOD    33 /**< TLS module ID relocation. */
#define R_NIOS2_TLS_DTPREL    34 /**< TLS offset from DTP. */
#define R_NIOS2_TLS_TPREL     35 /**< TLS offset from TP. */
#define R_NIOS2_COPY          36 /**< Runtime symbol copy. */
#define R_NIOS2_GLOB_DAT      37 /**< Set GOT entry to data address. */
#define R_NIOS2_JUMP_SLOT     38 /**< Set GOT entry to function address. */
#define R_NIOS2_RELATIVE      39 /**< Relative relocation. */
#define R_NIOS2_GOTOFF        40 /**< Offset to GOT from symbol. */
#define R_NIOS2_CALL26_NOAT   41 /**< 26-bit call without using AT register. */
#define R_NIOS2_GOT_LO        42 /**< GOT low 16 bits. */
#define R_NIOS2_GOT_HA        43 /**< GOT high-adjusted 16 bits. */
#define R_NIOS2_CALL_LO       44 /**< Call target low 16 bits. */
#define R_NIOS2_CALL_HA       45 /**< Call target high-adjusted 16 bits. */
/** @} */

/** 
 * @defgroup OR1K_Relocation_Types OpenRISC (OR1K) Relocation Types
 * @brief Relocation type constants for the OpenRISC architecture.
 * @{
 */
#define R_OR1K_NONE          0  /**< No relocation. */
#define R_OR1K_32            1  /**< Direct 32-bit relocation. */
#define R_OR1K_16            2  /**< Direct 16-bit relocation. */
#define R_OR1K_8             3  /**< Direct 8-bit relocation. */
#define R_OR1K_LO_16_IN_INSN 4  /**< Low 16 bits embedded in instruction. */
#define R_OR1K_HI_16_IN_INSN 5  /**< High 16 bits embedded in instruction. */
#define R_OR1K_INSN_REL_26   6  /**< 26-bit PC-relative relocation. */
#define R_OR1K_GNU_VTENTRY   7  /**< GNU vtable entry. */
#define R_OR1K_GNU_VTINHERIT 8  /**< GNU vtable inheritance. */
#define R_OR1K_32_PCREL      9  /**< 32-bit PC-relative relocation. */
#define R_OR1K_16_PCREL      10 /**< 16-bit PC-relative relocation. */
#define R_OR1K_8_PCREL       11 /**< 8-bit PC-relative relocation. */
#define R_OR1K_GOTPC_HI16    12 /**< GOT PC-relative high 16 bits. */
#define R_OR1K_GOTPC_LO16    13 /**< GOT PC-relative low 16 bits. */
#define R_OR1K_GOT16         14 /**< 16-bit GOT entry. */
#define R_OR1K_PLT26         15 /**< 26-bit PLT entry. */
#define R_OR1K_GOTOFF_HI16   16 /**< Offset to GOT high 16 bits. */
#define R_OR1K_GOTOFF_LO16   17 /**< Offset to GOT low 16 bits. */
#define R_OR1K_COPY          18 /**< Runtime copy of symbols. */
#define R_OR1K_GLOB_DAT      19 /**< Create global data entry. */
#define R_OR1K_JMP_SLOT      20 /**< Set GOT entry to function address. */
#define R_OR1K_RELATIVE      21 /**< Relative address relocation. */
#define R_OR1K_TLS_GD_HI16   22 /**< TLS GD model high 16 bits. */
#define R_OR1K_TLS_GD_LO16   23 /**< TLS GD model low 16 bits. */
#define R_OR1K_TLS_LDM_HI16  24 /**< TLS LDM model high 16 bits. */
#define R_OR1K_TLS_LDM_LO16  25 /**< TLS LDM model low 16 bits. */
#define R_OR1K_TLS_LDO_HI16  26 /**< TLS LDO model high 16 bits. */
#define R_OR1K_TLS_LDO_LO16  27 /**< TLS LDO model low 16 bits. */
#define R_OR1K_TLS_IE_HI16   28 /**< TLS IE model high 16 bits. */
#define R_OR1K_TLS_IE_LO16   29 /**< TLS IE model low 16 bits. */
#define R_OR1K_TLS_LE_HI16   30 /**< TLS LE model high 16 bits. */
#define R_OR1K_TLS_LE_LO16   31 /**< TLS LE model low 16 bits. */
#define R_OR1K_TLS_TPOFF     32 /**< Offset from TP. */
#define R_OR1K_TLS_DTPOFF    33 /**< Offset from DTP. */
#define R_OR1K_TLS_DTPMOD    34 /**< TLS module ID relocation. */
/** @} */

/**
 * @defgroup BPF_Relocation_Types BPF Relocation Types
 * @brief Relocation type constants for eBPF programs.
 * @{
 */
#define R_BPF_NONE   0 /**< No relocation. */
#define R_BPF_MAP_FD 1 /**< Relocation for map file descriptor. */
/** @} */

/** 
 * @defgroup riscv_relocations RISC-V Relocation Types
 * @brief Constants for different RISC-V relocation types.
 * 
 * This group contains all the relocation types used in RISC-V architecture.
 * These constants are used in ELF files to handle various kinds of relocation.
 * 
 * @{
 */
#define R_RISCV_NONE            0  /**< No relocation */
#define R_RISCV_32              1  /**< 32-bit relocation */
#define R_RISCV_64              2  /**< 64-bit relocation */
#define R_RISCV_RELATIVE        3  /**< Relative relocation */
#define R_RISCV_COPY            4  /**< Copy relocation */
#define R_RISCV_JUMP_SLOT       5  /**< Jump slot for dynamic linking */
#define R_RISCV_TLS_DTPMOD32    6  /**< TLS module index (32-bit) */
#define R_RISCV_TLS_DTPMOD64    7  /**< TLS module index (64-bit) */
#define R_RISCV_TLS_DTPREL32    8  /**< TLS data (32-bit) */
#define R_RISCV_TLS_DTPREL64    9  /**< TLS data (64-bit) */
#define R_RISCV_TLS_TPREL32     10 /**< TLS thread-specific (32-bit) */
#define R_RISCV_TLS_TPREL64     11 /**< TLS thread-specific (64-bit) */

#define R_RISCV_BRANCH          16 /**< Branch relocation */
#define R_RISCV_JAL             17 /**< JAL relocation */
#define R_RISCV_CALL            18 /**< Call relocation */
#define R_RISCV_CALL_PLT        19 /**< Call PLT relocation */
#define R_RISCV_GOT_HI20        20 /**< GOT high 20 bits */
#define R_RISCV_TLS_GOT_HI20    21 /**< TLS GOT high 20 bits */
#define R_RISCV_TLS_GD_HI20     22 /**< TLS global data high 20 bits */
#define R_RISCV_PCREL_HI20      23 /**< PC-relative high 20 bits */
#define R_RISCV_PCREL_LO12_I    24 /**< PC-relative low 12 bits (I-type) */
#define R_RISCV_PCREL_LO12_S    25 /**< PC-relative low 12 bits (S-type) */
#define R_RISCV_HI20            26 /**< High 20 bits */
#define R_RISCV_LO12_I          27 /**< Low 12 bits (I-type) */
#define R_RISCV_LO12_S          28 /**< Low 12 bits (S-type) */
#define R_RISCV_TPREL_HI20      29 /**< TLS thread-specific high 20 bits */
#define R_RISCV_TPREL_LO12_I    30 /**< TLS thread-specific low 12 bits (I-type) */
#define R_RISCV_TPREL_LO12_S    31 /**< TLS thread-specific low 12 bits (S-type) */
#define R_RISCV_TPREL_ADD       32 /**< TLS thread-specific addition */
#define R_RISCV_ADD8            33 /**< 8-bit addition */
#define R_RISCV_ADD16           34 /**< 16-bit addition */
#define R_RISCV_ADD32           35 /**< 32-bit addition */
#define R_RISCV_ADD64           36 /**< 64-bit addition */
#define R_RISCV_SUB8            37 /**< 8-bit subtraction */
#define R_RISCV_SUB16           38 /**< 16-bit subtraction */
#define R_RISCV_SUB32           39 /**< 32-bit subtraction */
#define R_RISCV_SUB64           40 /**< 64-bit subtraction */
#define R_RISCV_GNU_VTINHERIT   41 /**< GNU-specific inheritance */
#define R_RISCV_GNU_VTENTRY     42 /**< GNU-specific VT entry */
#define R_RISCV_ALIGN           43 /**< Alignment relocation */
#define R_RISCV_RVC_BRANCH      44 /**< RVC branch relocation */
#define R_RISCV_RVC_JUMP        45 /**< RVC jump relocation */
#define R_RISCV_RVC_LUI         46 /**< RVC LUI relocation */
#define R_RISCV_GPREL_I         47 /**< GP-relative (I-type) */
#define R_RISCV_GPREL_S         48 /**< GP-relative (S-type) */
#define R_RISCV_TPREL_I         49 /**< TLS thread-specific (I-type) */
#define R_RISCV_TPREL_S         50 /**< TLS thread-specific (S-type) */
#define R_RISCV_RELAX           51 /**< Relaxation relocation */
#define R_RISCV_SUB6            52 /**< 6-bit subtraction */
#define R_RISCV_SET6            53 /**< 6-bit set relocation */
#define R_RISCV_SET8            54 /**< 8-bit set relocation */
#define R_RISCV_SET16           55 /**< 16-bit set relocation */
#define R_RISCV_SET32           56 /**< 32-bit set relocation */
#define R_RISCV_32_PCREL        57 /**< 32-bit PC-relative relocation */
/** @} */ // end of riscv_relocations group

#ifdef __cplusplus
}
#endif


#endif