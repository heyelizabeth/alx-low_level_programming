#include "main.h"

/*
 * e_ident[] - IDENTIFICATION INDEXES
 *
 * Description: The initial bytes mark the file as an object file
 *              and provide machine-independent data.
 * The initial bytes of an ELF header (and an object file)
 *  correspond to the e_ident member.
*/

/**
 * check_if_elf - checks if file is an ELF file by checking if it
 *                contains the magic numbers/file signature of an ELF file
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void check_if_elf(unsigned char *e_ident)
{
	int index = 0;

	while (index < 4)
	{
		if (e_ident[index] != 127 &&
		    e_ident[index] != 'E' &&
		    e_ident[index] != 'L' &&
		    e_ident[index] != 'F') /*0x7F is 127 in ASCII*/
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}

		index++;
	}
}

/**
 * print_magic - prints the magic numbers of the ELF file
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void print_magic(unsigned char *e_ident)
{
	int index = 0;

	printf("  Magic    ");

	while (index < EI_NIDENT) /*EI_NIDENT == sizeof(e_ident[]) = 16*/
	{
		printf("%02x", e_ident[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" "); /*space each number*/

		index++;
	}
}

/**
 * print_class - prints the class of the ELF file
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void print_class(unsigned char *e_ident)
{
	printf("  Class:                             ");

	switch (e_ident[EI_CLASS]) /*EI_CLASS - File class*/
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
 * print_data - prints the data encoding of the ELF file
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void print_data(unsigned char *e_ident)
{
	printf("  Data:                              ");

	switch (e_ident[EI_DATA]) /*EI_DATA - Data encoding*/
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
			printf("<unknown: %x>\n", e_ident[EI_DATA]);
	}
}

/**
 * print_version - print the version of the ELF file
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void print_version(unsigned char *e_ident)
{
	printf("  Version:                           ");/*EI_VERSION - File version*/

	if (e_ident[EI_VERSION] == EV_CURRENT)
		printf("%d (current)\n", e_ident[EI_VERSION]);
	else
		printf("%i\n", e_ident[EI_VERSION]);
}

/**
 * print_osabi - prints the OS/ABI of the ELF file
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void print_osabi(unsigned char *e_ident)
{
	printf("  OS/ABI:                            ");

	switch (e_ident[EI_OSABI])/*EI_OSABI = OS Application Binary Interface*/
	{
		case ELFOSABI_SYSV:
			printf("UNIX - System V\n");
			break;
		case ELFOSABI_HPUX:
			printf("UNIX - HP-UX\n");
			break;
		case ELFOSABI_NETBSD:
			printf("UNIX - NetBSD\n");
			break;
		case ELFOSABI_LINUX:
			printf("UNIX - Linux\n");
			break;
		case ELFOSABI_SOLARIS:
			printf("UNIX - Solaris\n");
			break;
		case ELFOSABI_AIX:
			printf("UNIX - AIX\n");
			break;
		case ELFOSABI_IRIX:
			printf("UNIX - IRIX\n");
			break;
		case ELFOSABI_FREEBSD:
			printf("UNIX - FreeBSD\n");
			break;
		case ELFOSABI_TRU64:
			printf("UNIX - TRU64\n");
			break;
		case ELFOSABI_ARM:
			printf("ARM\n");
			break;
		case ELFOSABI_STANDALONE:
			printf("Standalone App\n");
			break;
		default:
			printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/**
 * print_abi - prints the Application Binary Interface of the ELF file
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void print_abi(unsigned char *e_ident)
{
	printf("  ABI Version:                       %d\n",
		e_ident[EI_ABIVERSION]); /*EI_ABIVERSION = ABI version*/
}

/**
 * print_type - prints the type of the ELF file
 *
 * @e_type: the object file type
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void print_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type >>= 8;

	printf("  Type:                              ");

	switch (e_type)
	{
		case ET_NONE:
			printf("NONE (Unknown type)\n");
			break;
		case ET_REL:
			printf("REL (Relocatable file)\n");
			break;
		case ET_EXEC:
			printf("EXEC (Exexutable file)\n");
			break;
		case ET_DYN:
			printf("DYN (Shared object file)\n");
			break;
		case ET_CORE:
			printf("CORE (Core file)\n");
			break;
		default:
			printf("<unknown: %x\n", e_type);
	}
}

/**
 * print_entry - prints the entry point of an ELF file
 *
 * @e_entry: the virtual memory address from where the
 *           process starts executing
 *
 * @e_ident: a pointer to an array of bytes specifies
 *           how to interpret the file
 *
 * Return: nothing
*/
void print_entry(unsigned long int e_entry, unsigned char *e_ident)

