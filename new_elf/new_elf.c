#include <stdio.h>
#include <elf.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void rc4_init(unsigned char *key, unsigned char *state, size_t keylen) {
    unsigned char j = 0;
    for (size_t i = 0; i < 256; i++) {
        state[i] = i;
    }
    for (size_t i = 0; i < 256; i++) {
        j = (j + state[i] + key[i % keylen]) % 256;
        unsigned char temp = state[i];
        state[i] = state[j];
        state[j] = temp;
    }
}

unsigned char rc4_output(unsigned char *state, size_t *i, size_t *j) {
    *i = (*i + 1) % 256;
    *j = (*j + state[*i]) % 256;
    unsigned char temp = state[*i];
    state[*i] = state[*j];
    state[*j] = temp;
    return state[(state[*i] + state[*j]) % 256];
}

void encrypt_message(unsigned char *message, size_t message_len, unsigned char *key, size_t keylen) {
    unsigned char state[256];
    rc4_init(key, state, keylen);

    size_t i = 0, j = 0;
    for (size_t k = 0; k < message_len; k++) {
        message[k] ^= rc4_output(state, &i, &j);
    }
}


union Elf_Ehdr {
 Elf32_Ehdr arch32;
 Elf64_Ehdr arch64;
};

static int ges32(char* name, void* data, int len, off_t *off, int *size);
static int ges64(char* name, void* data, int len, off_t *off, int *size);
int get_elf_section(char* name, void* data, int len, off_t *off, int *size)
{
 int arch = ELFCLASS32;
  
 if (len < EI_NIDENT) {
  return __LINE__;
 }
 if (memcmp( data, ELFMAG, sizeof(uint32_t)) != 0) {
  printf("Файл не соответствует формату ELF\n");
  return __LINE__;
 }
  
 arch = (unsigned int) ((((unsigned char*) data)[EI_CLASS]));
 switch (arch) {
 case ELFCLASS32:
  printf("\tАрхитектурв: x86\n");
  break;
 case ELFCLASS64:
  printf("\tАрхитектурв: x86_64\n");
  break;
 default:
  printf("\tАрхитектурв: НЕИЗВЕСТНА\n");
  return __LINE__;
 }
 
 return (arch == ELFCLASS32) ?
  (ges32(name, data, len, off, size)) :
  (ges64(name, data, len, off, size));
}

static int ges32(char* sname, void* data, int len, off_t *off, int *size)
{
 Elf32_Ehdr *hdr = (Elf32_Ehdr*) data;
 Elf32_Shdr *shdr;
 Elf32_Half i;
 char* ptr;
 char* names;
 int found = 0;
 
 if (len < sizeof(Elf32_Ehdr))
  return __LINE__;
 
 /* Определяем число секций */
 if ((!hdr->e_shnum) || (hdr->e_shstrndx == SHN_UNDEF)) {
  fprintf( stderr, "Секции не найдены\n");
  return __LINE__;
 }
  
 if (len < hdr->e_shoff)
  return __LINE__;
 
 /* Получаем массив заголовков */
 shdr = (Elf32_Shdr*) (data + hdr->e_shoff);
  
 if (len < (shdr[hdr->e_shstrndx].sh_offset))
  return __LINE__;
 /* Получаем массив имен */
 names = (char*) (data + shdr[hdr->e_shstrndx].sh_offset);
  
 for (i = 0; i < hdr->e_shnum; i++) {
  /* Берем только исполняемые секции */
  if ((shdr[i].sh_flags & SHF_EXECINSTR) != SHF_EXECINSTR)
   continue;
  
  ptr = &(names[shdr[i].sh_name]);
  
  printf("Смещение %08X - секция %s\n", shdr[i].sh_offset, ptr);
  if ((!found) && (strcmp(ptr, sname) == 0)) {
   *off = shdr[i].sh_offset;
   *size = shdr[i].sh_size;
   found = 1;
  }
 }
 if (found) return 0;
 fprintf( stderr, "Секция %s не найдена\n", sname);
 return __LINE__;
 
}

static int ges64(char* sname, void* data, int len, off_t *off, int *size)
{
 Elf64_Ehdr *hdr = (Elf64_Ehdr*) data;
 Elf64_Shdr *shdr;
 Elf64_Half i;
 char* ptr;
 char* names;
 int found = 0;
 
 /* Определяем число секций */
 if ((!hdr->e_shnum) || (hdr->e_shstrndx == SHN_UNDEF)) {
  fprintf( stderr, "Секции не найдены\n");
  return __LINE__;
 }
 
 /* Получаем массив заголовков */
 shdr = (Elf64_Shdr*) (data + hdr->e_shoff);
 
 /* Получаем массив имен */
 names = (char*) (data + shdr[hdr->e_shstrndx].sh_offset);
 
 for (i = 0; i < hdr->e_shnum; i++) {
  /* Берем только исполняемые секции */
  if ((shdr[i].sh_flags & SHF_EXECINSTR) != SHF_EXECINSTR)
   continue;
  ptr = &(names[shdr[i].sh_name]);
  printf("Смещение %08lX - секция %s\n", shdr[i].sh_offset, ptr);
  if ((!found) && (strcmp(ptr, sname) == 0)) {
   *off = shdr[i].sh_offset;
   *size = shdr[i].sh_size;
   found = 1;
  }
 }
 if (found) return 0;
 fprintf( stderr, "Секция %s не найдена\n", sname);
 return __LINE__;
}


int main(int argc, char *argv[]) {
    char* data;
    int fd;
    struct stat st;
    off_t offset;
    int size;
    if (argc != 2) {
        printf("USAGE: %s <elf>\n", argv[0]);
        exit(-1);
    }

    if (stat(argv[1], &st) == -1) {
        perror("stat");
        exit(-1);
    }

    if (NULL == (data = malloc(st.st_size))) {
        perror("malloc");
        exit(-2);
    }

    if (0 < (fd = open(argv[1], O_RDWR))) {
        read(fd, data, st.st_size);
        close(fd);

        if (get_elf_section(".upx", data, st.st_size, &offset, &size)) {
            printf("Section not found\n");
        } else {
            printf("Offset = %lu; Size = %u\n", offset, size);

            char message[] = "Hello, world\n";
            unsigned char key[] = "IKBO_25_22";
            size_t keylen = strlen(key);
            
            encrypt_message((unsigned char *)message, strlen(message), key, keylen);

            printf("Зашифрованное сообщение:%s", message);
            /* for(int i = 0; i < 12; i++){
                printf("%S\n", message[i]+48);
            } */
        }

    }
    free(data);
    return 0;
}
