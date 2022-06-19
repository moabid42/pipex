#include "../includes/elf_parser.h"
#include "../includes/elf_macros.h"


char* add_ELF; // addr of the content of the ELF
char* SHSTRTAB; // addr of the section header string table
char* STRTAB; // addr of the string table
char* DYNSTR; //addr of the dynamic string table

Elf32_Shdr* SYMTAB32; // the symbol table for ELF32
Elf32_Shdr* DYNSYM32; // the dynamic symbol table for ELF32

Elf64_Shdr* SYMTAB64; // the symbol table for ELF64
Elf64_Shdr* DYNSYM64; // the dynamic symbol table for ELF64


void usage(char* prog){
    printf("[*] Usage: %s <elf_file>\n", prog);
    exit(EXIT_FAILURE);
}

void fatal(char* msg){
    puts(msg);
    exit(EXIT_FAILURE);
}

int check_magic(unsigned char* ident){
    int check = strncmp((char *)ident + 1, "ELF", 3);
    return (ident[0] == 0x7f && check == 0)? 1 : 0;
}

void space(int count){
    for(int i=0; i < count; i++)
        printf(" ");
}


/*
 * This fucntion returns the corresponding data encoding
 * string of the variable data
 */
char* get_hdata(unsigned char data){
    switch(data){
        case ELFDATA2_LSB:
            return "Two's complement, little-endian";
        case ELFDATA2_MSB:
            return "Two's complement, big-endian";
  
        default :
            return "Unknown data format";
    }
}

/*
 * This function returns the corresponding version string 
 * of the variable version
 */
char* get_hversion(unsigned char version){
    switch(version){
        case 1:
            return "Current version";
        default :
            return "Invalid version";
    }
}

/*
 * This function returns the corresponding os and abi
 * string of the variable osabi
 */
char* get_hosabi(unsigned char osabi){
    switch(osabi){
        case ELFOSABI_SYSV:
            return "UNIX System V ABI";
        case ELFOSABI_HPUX:
            return "HP-UX ABI";
        case ELFOSABI_NETBSD:
            return "NETBSD ABI";
        case ELFOSABI_LINUX:
            return "Linux ABI";
        case ELFOSABI_SOLARIS:
            return "Solaris ABI";
        case ELFOSABI_IRIX:
            return "IRIX ABI";   
        case ELFOSABI_FREEBSD:
            return "FreeBSD ABI";
        case ELFOSABI_TRU64:
            return "TRU64 UNIX ABI";
        case ELFOSABI_ARM:
            return "ARM architecture ABI";
        case ELFOSABI_STANDALONE:
            return "Stand-alone (embedded) ABI";
  
        default :
            return "Unknown";
    }
}

/*
 * This function returns the corresponding elf file
 * type string of the variable type
 */
char* get_htype(unsigned short type){
    switch(type){
        case ET_REL:
            return "Relocatable";
        case ET_EXEC:
            return "Executable";
        case ET_DYN:
            return "Shared object";
        case ET_CORE:
            return "Core";
        default:
            return "Unknown";
    }
}

/*
 * This function returns the corresponding machine
 * string of the variable machine
 */
char* get_hmachine(unsigned short machine){
    switch(machine){
        case EM_M32:
            return "AT&T WE 32100";
        case EM_SPARC:
            return "Sun Microsystems SPARC";
        case EM_386:
            return "Intel 80386";
        case EM_68K:
            return "Motorola 68000";
        case EM_88K:
            return "Motorola 88000";
        case EM_860:
            return "Intel 80860";
        case EM_MIPS:
            return "MIPS RS3000 (big-endian only)";
        case EM_PARISC:
            return "HP/PA";
        case EM_SPARC32PLUS:
            return "SPARC with enhanced instruction set";
        case EM_PPC:
            return "PowerPC";
        case EM_PPC64:
            return "PowerPC 64-bit";
        case EM_S390:
            return "IBM S/390";
        case EM_ARM:
            return "Advanced RISC Machines";
        case EM_SH:
            return "Renesas SuperH";
        case EM_SPARCV9:
            return "SPARC v9 64-bit";
        case EM_IA_64:
            return "Intel Itanium";
        case EM_X86_64:
            return "AMD x86-64";
        case EM_VAX:
            return "DEC Vax";
        
        default:
            return "Unknown";
    }
}

/*
 * This function returns the corresponding program header
 * type string of the variable type
 */ 
char* get_phtype(unsigned int type){
    switch(type){
        case PT_NULL:
            return "NULL";
        case PT_LOAD:
            return "LOAD";
        case PT_DYNAMIC:
            return "DYNAMIC";
        case PT_INTERP:
            return "INTERP";
        case PT_NOTE:
            return "NOTE";
        case PT_SHLIB:
            return "SHLIB";
        case PT_PHDR:
            return "PHDR";
        case PT_TLS:
            return "TLS";
        case PT_LOPROC:
            return "LOPROC";
        case PT_HIPROC:
            return "HIPROC";
        case PT_GNU_STACK:
            return "GNU_STACK";
        default:
            return "UNKNWON";
    }
}

/*
 * This function returns the corresponding program header
 * flags string of the variable flags
 */
char* get_phflags(unsigned int flags){
    char* perm = malloc(4);
    perm[3] = '\0';
    
    if(flags & PF_R)
        perm[0] = 'r';
    else
        perm[0] = '-';
        
    if(flags & PF_W)
        perm[1] = 'w';
    else
        perm[1] = '-';
    
    if(flags & PF_X)
        perm[2] = 'x';
    else
        perm[2] = '-';
        
    return perm;
}

/*
 * This function returns the corresponding section header
 * type string of the variable type
 */
char* get_shtype(unsigned int type){
    switch(type){
        case SHT_NULL:
            return "NULL";
        case SHT_PROGBITS:
            return "PROGBITS";
        case SHT_SYMTAB:
            return "SYMTAB";
        case SHT_STRTAB:
            return "STRTAB";
        case SHT_RELA:
            return "RELA";
        case SHT_HASH:
            return "HASH";
        case SHT_DYNAMIC:
            return "DYNAMIC";
        case SHT_NOTE:
            return "NOTE";
        case SHT_NOBITS:
            return "NOBITS";
        case SHT_REL:
            return "REL";
        case SHT_SHLIB:
            return "SHLIB";
        case SHT_DYNSYM:
            return "DYNSYM";
        case SHT_LOPROC:
            return "LOPROC";
        case SHT_HIPROC:
            return "HIPROC";
        case SHT_LOUSER:
            return "LOUSER";
        case SHT_HIUSER:
            return "HIUSER";
        
        default:
            return "UNKNOWN";
    }
}

/*
 * This function returns the corresponding program header
 * flags string of the variable flags
 */
char* get_shflags(unsigned int flags){
    char* perm = malloc(4);
    perm[3] = '\0';
    
    if(flags & SHF_ALLOC)
        perm[0] = 'A';
    else
        perm[0] = ' ';
        
    if(flags & SHF_WRITE)
        perm[1] = 'W';
    else
        perm[1] = ' ';
    
    if(flags & SHF_EXECINSTR)
        perm[2] = 'X';
    else
        perm[2] = ' ';
        
    return perm;    
}

/*
 * This function returns the corresponding symbol table
 * index type string of the variable info
 * for a 32 bits ELF
 */
char* get_symtype32(unsigned char info){
    switch(ELF32_ST_TYPE(info)){
        case STT_NOTYPE:
            return "NOTYPE";
        case STT_OBJECT:
            return "OBJECT";
        case STT_FUNC:
            return "FUNCTION";
        case STT_SECTION:
            return "SECTION";
        case STT_FILE:
            return "FILE";
        case STT_LOPROC:
            return "LOPROC";
        case STT_HIPROC:
            return "HIPROC";
            
        default:
            return "UNKNOWN";        
    }
}

/*
 * This function returns the corresponding symbol table
 * index type string of the variable info
 * for a 64 bits ELF
 */
char* get_symtype64(unsigned char info){
    switch(ELF64_ST_TYPE(info)){
        case STT_NOTYPE:
            return "NOTYPE";
        case STT_OBJECT:
            return "OBJECT";
        case STT_FUNC:
            return "FUNCTION";
        case STT_SECTION:
            return "SECTION";
        case STT_FILE:
            return "FILE";
        case STT_LOPROC:
            return "LOPROC";
        case STT_HIPROC:
            return "HIPROC";
            
        default:
            return "UNKNOWN";        
    }
}

/*
 * This function returns the corresponding symbol table
 * index binding string of the variable info
 * for a 32 bits ELF
 */
char* get_symbind32(unsigned char info){
    switch(ELF32_ST_BIND(info)){
        case STB_LOCAL:
            return "LOCAL";
        case STB_GLOBAL:
            return "GLOBAL";
        case STB_WEAK:
            return "WEAK";
        case STB_LOPROC:
            return "LOPROC";
        case STB_HIPROC:
            return "HIPROC";
            
        default :
            return "UNKNOWN";
    }
}

/*
 * This function returns the corresponding symbol table
 * index binding string of the variable info
 * for a 64 bits ELF
 */
char* get_symbind64(unsigned char info){
    switch(ELF64_ST_BIND(info)){
        case STB_LOCAL:
            return "LOCAL";
        case STB_GLOBAL:
            return "GLOBAL";
        case STB_WEAK:
            return "WEAK";
        case STB_LOPROC:
            return "LOPROC";
        case STB_HIPROC:
            return "HIPROC";
            
        default :
            return "UNKNOWN";
    }
} 

/*
 * This function returns the corresponding symbol table
 * index visibilty string of the variable other
 * for a 32 bits ELF
 */
char* get_symvis32(unsigned char other){
    switch(ELF32_ST_VISIBILITY(other)){
        case STV_DEFAULT:
            return "DEFAULT";
        case STV_INTERNAL:
            return "INTERNAL";
        case STV_HIDDEN:
            return "HIDDEN";
        case STV_PROTECTED:
            return "PROTECTED";
            
        default :
            return "UNKNOWN";
    }
}   

/*
 * This function returns the corresponding symbol table
 * index visibilty string of the variable other
 * for a 64 bits ELF
 */
char* get_symvis64(unsigned char other){
    switch(ELF64_ST_VISIBILITY(other)){
        case STV_DEFAULT:
            return "DEFAULT";
        case STV_INTERNAL:
            return "INTERNAL";
        case STV_HIDDEN:
            return "HIDDEN";
        case STV_PROTECTED:
            return "PROTECTED";
            
        default :
            return "UNKNOWN";
    }
} 


/*
 * This function prints all inforamtion contained
 * on an Elf32 header
 */
void print_ehdr32(struct elf_header_32 hdr){
    puts("");
    puts("===============ELF32 header===============");
    puts("");
    printf("Magic number : "); 
    for(int i=0; i < 4; i++)
        printf("0x%02x ", hdr.e_ident[i]);
    puts("");
    printf("Data : %s (0x%x)\n", get_hdata(hdr.e_ident[5]), hdr.e_ident[5]);
    printf("Version : %s (0x%x)\n", get_hversion(hdr.e_ident[6]), hdr.e_ident[6]);
    printf("OS&ABI : %s (0x%x)\n", get_hosabi(hdr.e_ident[7]), hdr.e_ident[7]);
    printf("ABI version : 0x%x\n", hdr.e_ident[8]);
    printf("Type : %s (0x%x)\n", get_htype(hdr.e_type), hdr.e_type);
    printf("Machine : %s (0x%x)\n", get_hmachine(hdr.e_machine), hdr.e_machine);
    printf("Version : 0x%x\n", hdr.e_version);
    printf("Entry point : 0x%lx\n", hdr.e_entry);
    printf("Program header offset : 0x%lx\n", hdr.e_phoff);
    printf("Section header offset : 0x%lx\n", hdr.e_shoff);
    printf("Flags : 0x%x\n", hdr.e_flags);
    printf("ELF header size : %d bytes\n", hdr.e_ehsize);
    printf("Program header entry size : %d bytes\n", hdr.e_phentsize);
    printf("Program header entry count : %d\n", hdr.e_phnum);
    printf("Section header entry size : %d bytes\n", hdr.e_shentsize);
    printf("Section header entry count : %d\n", hdr.e_shnum);
    printf("Section header string index : %d\n", hdr.e_shstrndx);
    puts("");
    puts("===================EOH===================");
}

/*
 * This is the main function that will map the  
 * ELF32 into memory, parse it and print each  
 * component of it
 */
void parse_elf32(struct elf_header_32 hdr, struct elf_file *elf) {
    
    struct stat elf_stat;
    
    if(fstat(elf->fd, &elf_stat) < 0)
        fatal("[-] Can't get the file size");
    add_ELF = mmap(NULL, elf_stat.st_size, PROT_READ, MAP_PRIVATE, elf, 0);
    if(add_ELF == MAP_FAILED)
        fatal("[-] Can't allocate memory for the file");
    
    print_ehdr32(hdr);
    
    if(hdr.e_phoff)
        print_ephtbl32(hdr);
    if(hdr.e_shoff)
        print_eshtbl32(hdr);
    
    print_esymtbl32(SYMTAB32, ".symtab");
    print_esymtbl32(DYNSYM32, ".dynsym");
}

/*
 * This function prints all information contained
 * on an Elf32 program header table
 */
void print_ephtbl32(struct elf_header_32 hdr){
    //Get the program header table
    Elf32_Phdr* phdr = (Elf32_Phdr*) &add_ELF[hdr.e_phoff];
    
    puts("");
    puts("==========================================Program header table==========================================");
    printf("offset in file : 0x%lx\n", hdr.e_phoff);
    printf("Number of entry : %d\n", hdr.e_phnum);
    puts("");
    //title of the table
    printf("Type");
    space(10);
    printf("Offset");
    space(5);
    printf("File size");
    space(2);
    printf("Mem size");
    space(3);
    printf("Virt addr");
    space(2);
    printf("Phys addr");
    space(2);
    printf("Align");
    space(6);
    printf("Flags\n");
    
    //print each phdr
    for(int i=0; i < hdr.e_phnum; i++){
        print_ephdr32(&phdr[i]);
    }
    
    puts("");
    puts("===================================================EOPHT===================================================");
    puts("");
    
}

/*
 * This function prints all information contained
 * on Elf32 section header table
 */
void print_eshtbl32(struct elf_header_32 hdr){
    //Get the section header table
    Elf32_Shdr* shdr = (Elf32_Shdr*) &add_ELF[hdr.e_shoff];
    
    puts("");
    puts("===========================================Section header table===========================================");
    printf("offset in file : 0x%lx\n", hdr.e_shoff);
    printf("Number of entry : %d\n", hdr.e_shnum);
    puts("");
    //title of the table
    space(6);
    printf("Name");
    space(16);
    printf("Type");
    space(10);
    printf("Address");
    space(4);
    printf("Offset");
    space(5);
    printf("Size");
    space(7);
    printf("Entry Size");
    space(1);
    printf("Align");
    space(6);
    printf("Flags  ");
    printf("Link   ");
    printf("Info\n");
    
    //Get the section header string table
    SHSTRTAB = &add_ELF[shdr[hdr.e_shstrndx].sh_offset];
    
    //print each shdr
    for(int i=0; i < hdr.e_shnum; i++){
        print_eshdr32(&shdr[i], i);
    }
    
    puts("");
    puts("===================================================EOSHT===================================================");
    puts("");
    
}

/*
 * This function prints all information contained
 * on an Elf32 symbol table
 */
void print_esymtbl32(Elf32_Shdr* shdr, char* name){
    
    if(!shdr){
        puts("");
        printf("[*] There is no %s section\n", name);
        return ;
    }

    //Get the symbol table
    Elf32_Sym* sym = (Elf32_Sym*) &add_ELF[shdr->sh_offset];
    
    puts("");
    printf("==========================================%s table===========================================\n", name);
    printf("offset in file : 0x%lx\n", shdr->sh_offset);
    printf("Number of entry : %d\n", shdr->sh_size / shdr->sh_entsize);
    puts("");
    //title of the table
    space(6);
    printf("Value");
    space(6);
    printf("Size ");   
    printf("Type");
    space(5);
    printf("Bind");
    space(3);
    printf("Visibility ");
    printf("Index ");
    printf("Name");
    puts("");
    
    //print each shdr
    for(uint64_t i=0; i < shdr->sh_size / shdr->sh_entsize; i++){
        print_esym32(&sym[i], i, name);
    }
    
    puts("");
    puts("===============================================EOST===============================================");
    puts("");
    
}

/*
 * This function prints a 32 bits program header
 */
void print_ephdr32(Elf32_Phdr* phdr){
    int printed;
    puts("");
    printed = printf("%s", get_phtype(phdr->p_type));
    space(14 - printed);
    printf("0x%08lx ", phdr->p_offset);
    printf("0x%08x ", phdr->p_filesz);
    printf("0x%08x ", phdr->p_memsz);
    printf("0x%08lx ", phdr->p_vaddr);
    printf("0x%08lx ", phdr->p_paddr);
    printf("0x%08x ", phdr->p_align);
    printf("%s", get_phflags(phdr->p_flags));
    puts("");
}

/*
 * This function prints a 32 bits section header
 */
void print_eshdr32(Elf32_Shdr* shdr, int index){
    int printed;
    puts("");
    printf("[%03d] ", index);
    printed = printf("%s", &SHSTRTAB[shdr->sh_name]);
    space(20 - printed);
    printed = printf("%s", get_shtype(shdr->sh_type));
    space(14 - printed);
    printf("0x%08lx ", shdr->sh_addr);
    printf("0x%08lx ", shdr->sh_offset);
    printf("0x%08x ", shdr->sh_size);
    printf("0x%08x ", shdr->sh_entsize);
    printf("0x%08x ", shdr->sh_addralign);
    printf(" %s    ", get_shflags(shdr->sh_flags));
    printed = printf("0x%x ", shdr->sh_link);
    space(7 - printed);
    printf("0x%x ", shdr->sh_info);
    puts("");
    
    if(!strcmp(".symtab", &SHSTRTAB[shdr->sh_name]))
        SYMTAB32 = shdr;
    else if(!strcmp(".dynsym", &SHSTRTAB[shdr->sh_name]))
        DYNSYM32 = shdr;
    else if(!strcmp(".strtab", &SHSTRTAB[shdr->sh_name]))
        STRTAB = &add_ELF[shdr->sh_offset];
    else if(!strcmp(".dynstr", &SHSTRTAB[shdr->sh_name]))
        DYNSTR = &add_ELF[shdr->sh_offset];
            
}

void print_esym32(Elf32_Sym* sym, int index, char* name){
    
    //set the apropriate string table
    char* strtab;
    if(!strcmp(".dynsym", name))
        strtab = DYNSTR;
    else
        strtab = STRTAB;
        
    int printed;
    puts("");
    printf("[%03d] ", index);
    printf("0x%08lx ", sym->st_value);
    printed = printf("%4d ", sym->st_size);
    printed = printf("%s", get_symtype64(sym->st_info));
    space(9 - printed);
    printed = printf("%s", get_symbind64(sym->st_info));
    space(7 - printed);
    printed = printf("%s", get_symvis64(sym->st_other));
    space(10 - printed);
    printed = printf("%6d ", sym->st_shndx);
    printf("%s", &strtab[sym->st_name]);    
    puts("");
   
}

/*
 *
 *
 ****************************************************************
 * Limits between 32 and 64 bits functions                      *****************
 ****************************************************************
 *
 *
 *
 */

/*
 * This function prints all information contained
 * on an Elf64 header
 */
void print_ehdr64(struct elf_header_64 hdr){
    puts("");
    puts("===============ELF64 header===============");
    puts("");
    printf("Magic number : "); 
    for(int i=0; i < 4; i++)
        printf("0x%02x ", hdr.e_ident[i]);
    puts("");
    printf("Data : %s (0x%x)\n", get_hdata(hdr.e_ident[5]), hdr.e_ident[5]);
    printf("Version : %s (0x%x)\n", get_hversion(hdr.e_ident[6]), hdr.e_ident[6]);
    printf("OS&ABI : %s (0x%x)\n", get_hosabi(hdr.e_ident[7]), hdr.e_ident[7]);
    printf("ABI version : 0x%x\n", hdr.e_ident[8]);
    printf("Type : %s (0x%x)\n", get_htype(hdr.e_type), hdr.e_type);
    printf("Machine : %s (0x%x)\n", get_hmachine(hdr.e_machine), hdr.e_machine);
    printf("Version : 0x%x\n", hdr.e_version);
    printf("Entry point : 0x%lx\n", hdr.e_entry);
    printf("Program header offset : 0x%lx\n", hdr.e_phoff);
    printf("Section header offset : 0x%lx\n", hdr.e_shoff);
    printf("Flags : 0x%x\n", hdr.e_flags);
    printf("ELF header size : %d bytes\n", hdr.e_ehsize);
    printf("Program header entry size : %d bytes\n", hdr.e_phentsize);
    printf("Program header entry count : %d\n", hdr.e_phnum);
    printf("Section header entry size : %d bytes\n", hdr.e_shentsize);
    printf("Section header entry count : %d\n", hdr.e_shnum);
    printf("Section header string index : %d\n", hdr.e_shstrndx);
    puts("");
    puts("===================EOH===================");
}

/*
 * This function prints all information contained
 * on an Elf64 program header table
 */
void print_ephtbl64(struct elf_header_64 hdr){
    //Get the program header table
    Elf64_Phdr* phdr = (Elf64_Phdr*) &add_ELF[hdr.e_phoff];
    
    puts("");
    puts("==========================================Program header table==========================================");
    printf("offset in file : 0x%lx\n", hdr.e_phoff);
    printf("Number of entry : %d\n", hdr.e_phnum);
    puts("");
    //title of the table
    printf("Type");
    space(10);
    printf("Offset");
    space(13);
    printf("File size");
    space(10);
    printf("Mem size");
    space(11);
    printf("Virtual addr");
    space(7);
    printf("Physical addr");
    space(6);
    printf("Align");
    space(14);
    printf("Flags\n");
    
    //print each phdr
    for(int i=0; i < hdr.e_phnum; i++){
        print_ephdr64(&phdr[i]);
    }
    
    puts("");
    puts("===================================================EOPHT===================================================");
    puts("");
    
}

/*
 * This function prints all information contained
 * on an Elf64 section header table
 */
void print_eshtbl64(struct elf_header_64 hdr){
    //Get the section header table
    Elf64_Shdr* shdr = (Elf64_Shdr*) &add_ELF[hdr.e_shoff]; 
    
    puts("");
    puts("===========================================Section header table===========================================");
    printf("offset in file : 0x%lx\n", hdr.e_shoff);
    printf("Number of entry : %d\n", hdr.e_shnum);
    puts("");
    //title of the table
    space(6);
    printf("Name");
    space(16);
    printf("Type");
    space(10);
    printf("Address");
    space(12);
    printf("Offset");
    space(13);
    printf("Size");
    space(15);
    printf("Entry Size");
    space(9);
    printf("Align");
    space(14);
    printf("Flags  ");
    printf("Link   ");
    printf("Info\n");
    
    //Get the section header string table
    SHSTRTAB = &add_ELF[shdr[hdr.e_shstrndx].sh_offset];
    
    //print each shdr
    for(int i=0; i < hdr.e_shnum; i++){
        print_eshdr64(&shdr[i], i);
    }
    
    puts("");
    puts("===================================================EOSHT===================================================");
    puts("");
    
}

/*
 * This function prints all information contained
 * on an Elf64 symbol table
 */
void print_esymtbl64(Elf64_Shdr* shdr, char* name){
    
    if(!shdr){
        puts("");
        printf("[*] There is no %s section\n", name);
        return ;
    }

    //Get the symbol table
    Elf64_Sym* sym = (Elf64_Sym*) &add_ELF[shdr->sh_offset];
    
    puts("");
    printf("==========================================%s table===========================================\n", name);
    printf("offset in file : 0x%lx\n", shdr->sh_offset);
    printf("Number of entry : %ld\n", shdr->sh_size / shdr->sh_entsize);
    puts("");
    //title of the table
    space(6);
    printf("Value");
    space(14);
    printf("Size ");   
    printf("Type");
    space(5);
    printf("Bind");
    space(3);
    printf("Visibility ");
    printf("Index ");
    printf("Name");
    puts("");
    
    //print each shdr
    for(uint64_t i=0; i < shdr->sh_size / shdr->sh_entsize; i++){
        print_esym64(&sym[i], i, name);
    }
    
    puts("");
    puts("===============================================EOST===============================================");
    puts("");
    
}

/*
 * This function prints a 64 bits program header
 */
void print_ephdr64(Elf64_Phdr* phdr){
    int printed;
    puts("");
    printed = printf("%s", get_phtype(phdr->p_type));
    space(14 - printed);
    printf("0x%016lx ", phdr->p_offset);
    printf("0x%016lx ", phdr->p_filesz);
    printf("0x%016lx ", phdr->p_memsz);
    printf("0x%016lx ", phdr->p_vaddr);
    printf("0x%016lx ", phdr->p_paddr);
    printf("0x%016lx ", phdr->p_align);
    printf("%s", get_phflags(phdr->p_flags));
    puts("");
   
}

/*
 * This function prints a 64 bits section header
 */
void print_eshdr64(Elf64_Shdr* shdr, int index){
    int printed;
    puts("");
    printf("[%03d] ", index);
    printed = printf("%s", &SHSTRTAB[shdr->sh_name]);
    space(20 - printed);
    printed = printf("%s", get_shtype(shdr->sh_type));
    space(14 - printed);
    printf("0x%016lx ", shdr->sh_addr);
    printf("0x%016lx ", shdr->sh_offset);
    printf("0x%016lx ", shdr->sh_size);
    printf("0x%016lx ", shdr->sh_entsize);
    printf("0x%016lx ", shdr->sh_addralign);
    printf(" %s    ", get_shflags(shdr->sh_flags));
    printed = printf("0x%x ", shdr->sh_link);
    space(7 - printed);
    printf("0x%x ", shdr->sh_info);
    puts("");
    
    if(!strcmp(".symtab", &SHSTRTAB[shdr->sh_name]))
        SYMTAB64 = shdr;
    else if(!strcmp(".dynsym", &SHSTRTAB[shdr->sh_name]))
        DYNSYM64 = shdr;
    else if(!strcmp(".strtab", &SHSTRTAB[shdr->sh_name]))
        STRTAB = &add_ELF[shdr->sh_offset];
    else if(!strcmp(".dynstr", &SHSTRTAB[shdr->sh_name]))
        DYNSTR = &add_ELF[shdr->sh_offset];
    
}   

/*
 * This function prints a 64 bits symbol table index
 */
void print_esym64(Elf64_Sym* sym, int index, char* name){
    
    //set the apropriate string table
    char* strtab;
    if(!strcmp(".dynsym", name))
        strtab = DYNSTR;
    else
        strtab = STRTAB;

    int printed;
    puts("");
    printf("[%03d] ", index);
    printf("0x%016lx ", sym->st_value);
    printed = printf("%4ld ", sym->st_size);
    printed = printf("%s", get_symtype64(sym->st_info));
    space(9 - printed);
    printed = printf("%s", get_symbind64(sym->st_info));
    space(7 - printed);
    printed = printf("%s", get_symvis64(sym->st_other));
    space(10 - printed);
    printed = printf("%6d ", sym->st_shndx);
    printf("%s", &strtab[sym->st_name]);    
    puts("");
   
}

/*
 * This is the main function that will map the  
 * ELF64 into memory, parse it and print each  
 * component of it
 */
void parse_elf64(struct elf_header_64 hdr, struct elf_file *elf){
    
    struct stat elf_stat;

    if(fstat(elf->fd, &elf_stat) < 0)
        fatal("[-] Can't get the file size");
    add_ELF = mmap(NULL, elf_stat.st_size, PROT_READ, MAP_PRIVATE, elf->fd, 0);
    if(add_ELF == MAP_FAILED)
        fatal("[-] Can't allocate memory for the file");
    
    print_ehdr64(hdr);
    
    if(hdr.e_phoff)
        print_ephtbl64(hdr);
    if(hdr.e_shoff)
        print_eshtbl64(hdr);
        
    print_esymtbl64(SYMTAB64, ".symtab");
    print_esymtbl64(DYNSYM64, ".dynsym");
}
