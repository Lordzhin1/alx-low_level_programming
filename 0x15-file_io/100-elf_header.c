/*

File: 100-elf_header.c
Auth: Brennan D Baraban
*/
#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);
void close_elf(int elf_fd);

/**

check_elf - Checks if the file is an ELF file.
@e_ident: A pointer to an array of the ELF magic numbers.
This function verifies that the file is an ELF file. If it's not an ELF file, it exits with exit code 98.
*/
void check_elf(unsigned char *e_ident)
{
int i;
for (i = 0; i < 4; i++)
{
if (e_ident[i] != 127 &&
e_ident[i] != 'E' &&
e_ident[i] != 'L' &&
e_ident[i] != 'F')
{
dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
exit(98);
}
}
}
/**

print_magic - Prints the magic numbers of an ELF header.
@e_ident: A pointer to an array of the ELF magic numbers.
This function prints the magic numbers of an ELF header. The magic numbers are separated by spaces.
*/
void print_magic(unsigned char *e_ident)
{
int i;
printf(" Magic: ");
for (i = 0; i < EI_NIDENT; i++)
{
printf("%02x", e_ident[i]);
if (i == EI_NIDENT - 1)
printf("\n");
else
printf(" ");
}
}
/**

print_class - Prints the class of an ELF header.
@e_ident: A pointer to an array of the ELF class.
This function prints the class of an ELF header.
*/
void print_class(unsigned char *e_ident)
{
printf(" Class: ");
switch (e_ident[EI_CLASS])
{
case ELFCLASSNONE:
printf("none\n");
break;
case ELFCLASS32:
printf("ELF32\n");
break;
case ELFCLASS64:
printf("ELF64\n");
break;
default:
printf("<unknown: %x>\n", e_ident[EI_CLASS]);
}
}
/**

print_data - Prints the data of an ELF header.
@e_ident: A pointer to an array of the ELF data.
This function prints the data of an ELF header.
*/
void print_data(unsigned char *e_ident)
{
printf(" Data: ");
switch (e_ident[EI_DATA])
{
case ELFDATANONE:
printf("none\n");
break;
case ELFDATA2LSB:
printf("2's complement, little endian\n");
break;
case ELFDATA2MSB:
printf("2's complement, big endian\n");
break;
default:
printf("<unknown: %x>\n", e_ident[EI_CLASS]);
}
}
/**

print_version - Prints the version of an ELF header.
