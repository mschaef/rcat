#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define BLOCK_SIZE (1024)

int main(int argc, char *argv[]) {
     if (argc != 2) {
          fprintf(stderr, "Usage: %s FILENAME\n", argv[0]);
          return 1;
     }

     int in;

     in = open(argv[1], O_RDONLY);

     if (in == -1) {
          fprintf(stderr, "Error opening input file: %s (%s)",
                  argv[1], strerror(errno));
          return 2;
     }

     char block_buf[BLOCK_SIZE];
     size_t n;

     while(1) {
          size_t bytes_read = read(in, block_buf, BLOCK_SIZE);

          fprintf(stderr, "n=%zu, errno=%d\n", bytes_read, errno);

          if (bytes_read == 0) {
               break;
          }


          fwrite(block_buf, 1, bytes_read, stdout);
     }

     close(in);

     return 0;
}
