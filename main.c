#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "base64.h"

typedef struct file_r{
    size_t byte;
    char *buffer;
} file_r;

static void Usage(){
    puts("Usage: b64 [-e(encode) string]\n\t   [-d(decode) string]\n\t   [-ef(encode file) file]\n\t   [-df(decode file) input_file output_file]");
}

static file_r *read_file(const char *file){
    file_r *f = (file_r *) malloc(sizeof(file_r));
    FILE *fp;
    char *b;
    int len;
                                                                                                                                                                        
    fp = fopen(file , "rb");
                                                                                                                                                                                         
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    fseek(fp, 0, SEEK_SET);
                                                                                                                                                                                     
    b = (char *) malloc(len * sizeof(char));

    fread(b, len, 1, fp);
    fclose(fp);

    f -> buffer = b;
    f -> byte = (size_t) len;

    return f;
}

int main(int argc, char **argv){
    FILE *fpo;
    file_r *f;

    if(argc < 3){
        Usage();

        return -1;
    }

    if(strcmp(argv[1], "-d") == 0){
        puts(decode((const unsigned char *) argv[2], strlen(argv[2])));
    }else if(strcmp(argv[1], "-e") == 0){
        puts(encode((const unsigned char *) argv[2], strlen(argv[2])));
    }else if(strcmp(argv[1], "-ef") == 0){
        f = read_file((const char *) argv[2]);
        puts(encode((const unsigned char *) f -> buffer, f -> byte));
    }else if(strcmp(argv[1], "-df") == 0){
        if(argc < 4){
            fputs("Error: indicate input and output files!\nexit.", stderr);
            Usage();

            return -1;
        }

        fpo = fopen(argv[3], "wb");
        f = read_file((const char *) argv[2]);
        fwrite(decode((const unsigned char *) f -> buffer, f -> byte), f -> byte, 1, fpo);
    }else{
        Usage();
    }

    return 0;
}