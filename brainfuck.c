#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DATA_SIZE 30000
#define MOD 256

unsigned char data[DATA_SIZE];

int match_forward[DATA_SIZE];  // matching brackets for the forward brackets '['
int match_backward[DATA_SIZE]; // matching brackets for the backward brackets ']'

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <program_path>\n", argv[0]);
        printf("Please provide the program path.\n");
        return EXIT_FAILURE;
    }

    char *program_path = argv[1];
    int fd = open(program_path, O_RDONLY);

    if (fd == -1)
    {
        perror("Error: could not open the program file");
        return EXIT_FAILURE;
    }

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1)
    {
        perror("Error: could not get program size");
        return EXIT_FAILURE;
    }
    off_t file_size = file_stat.st_size;

    void *ptr = mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (ptr == (void *)-1)
    {
        perror("Error: could not read program data");
        return EXIT_FAILURE;
    }

    close(fd);

    unsigned char *text = (unsigned char *)ptr; // program instructions

    int *stack = (int *)malloc(DATA_SIZE * sizeof(int));
    int sp = -1; // top of the stack

    for (off_t i = 0; i < file_size; i++)
    {
        if (text[i] == '[')
        {
            stack[++sp] = i;
        }
        else if (text[i] == ']')
        {
            int j = stack[sp--];
            match_backward[i] = j;
            match_forward[j] = i;
        }
    }

    free(stack);

    off_t ip = 0; // instruction pointer
    off_t dp = 0; // data pointer

    int j;

    while (ip < file_size)
    {
        char c = text[ip];

        switch (c)
        {
        case '>':
            dp++;
            ip++;
            break;

        case '<':
            dp--;
            ip++;
            break;

        case '+':
            data[dp] = ((int)data[dp] + 1) % MOD;
            ip++;
            break;

        case '-':
            data[dp] = ((int)data[dp] - 1 + MOD) % MOD;
            ip++;
            break;

        case '.':
            putchar(data[dp]);
            ip++;
            break;

        case ',':
            data[dp] = getchar();
            ip++;
            break;

        case '[':
            j = match_forward[ip];
            ip = data[dp] ? ip + 1 : j + 1;
            break;

        case ']':
            j = match_backward[ip];
            ip = data[dp] ? j + 1 : ip + 1;
            break;

        default:
            // ignore other characters, considered comments
            ip++;
            break;
        }
    }
}