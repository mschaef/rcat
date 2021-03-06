/*
 * rcat.c --
 *
 * (C) Copyright 2021 Mike Schaeffer
 *
 * See the file "license.terms" for information on usage and
 * redistribution of this file, and for a DISCLAIMER OF ALL
 * WARRANTIES.
 */


#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#define BLOCK_SIZE (32 * 1024)


int rcat(char *filename) {
     int in;

     in = open(filename, O_RDONLY);

     if (in == -1) {
          fprintf(stderr, "Error opening input file: %s (%s)",
                  filename, strerror(errno));
          return 2;
     }

     char block_buf[BLOCK_SIZE];

     size_t read_ofs;
     size_t n;

     read_ofs = 0;
     int failed = 0;

     while(1) {
          if (failed || (read_ofs % (1024 * 1024) == 0)) {
               fprintf(stderr, "ofs=%zu\n", read_ofs);
               failed = 0;
          }

          lseek(in, read_ofs, SEEK_SET);
          size_t bytes_read;

          bytes_read = read(in, block_buf, BLOCK_SIZE);

          if (bytes_read == 0) {
               break;
          } else if (bytes_read == -1) {
               fprintf(stderr, "ofs=%zu, (error: %s)\n", read_ofs, strerror(errno));
               failed = 1;

               if (EINTR == errno) {
                    continue;
               } else if (EIO == errno) {
                    memset(block_buf, 0, BLOCK_SIZE);
                    bytes_read = BLOCK_SIZE;
               }
          } else {
               fwrite(block_buf, 1, bytes_read, stdout);
          }

          read_ofs += bytes_read;
     }

     close(in);

     return 0;
}

int main(int argc, char *argv[]) {
     if (argc < 2) {
          fprintf(stderr, "Usage: %s FILENAME(s)\n", argv[0]);
          return 1;
     }

     for(int ii = 1; ii < argc; ii++) {
          int rc = rcat(argv[ii]);

          if (rc) {
               return rc;
          }
     }


     return 0;
}
