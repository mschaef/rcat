#include <stdio.h>

#define BLOCK_SIZE (1024)

int main(int argc, char *argv[]) {
     if (argc != 2) {
          fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
          return 1;
     }

     FILE *in;

     in = fopen(argv[1], "rb");

     if (in == NULL) {
          fprintf(stderr, "Input file not found: %s", argv[1]);
          return 2;
     }

     char block_buf[BLOCK_SIZE];
     size_t n;

     while(1) {
          n = fread(block_buf, 1, BLOCK_SIZE, in);

          if (n == 0) {
               break;
          }

          fprintf(stderr, "n=%d\n", n);
          fwrite(block_buf, 1, n, stdout);
     }

     fclose(in);

     return 0;
}
