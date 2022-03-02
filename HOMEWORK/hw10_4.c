#include <asm/unistd.h>

int nextchar(void);
typedef struct FileWriteState {
    int fd;
    unsigned char *buf;
    int bufsize;
    int full;
} FileWriteState;
static unsigned char buf[4096];
FileWriteState init = {1, buf, 4096, 0};
FileWriteState *stout = &init;
__attribute__((fastcall)) void flush(FileWriteState *out) {
    int res = 0;
    asm volatile (
        "mov    %1, %%eax \n"
        "mov    %2, %%ebx \n"
        "mov    %3, %%ecx \n"
        "mov    %4, %%edx \n"
        "int    $0x80 \n"
        "mov    %%eax, %0 \n"
        : "=g"(res)
        : "g"(__NR_write), "g"(out->fd),
          "g"((unsigned int)out->buf), "g"(out->full)
        :"eax", "ebx", "ecx", "edx", "memory");
}
__attribute__((fastcall)) void writechar(int c, FileWriteState *out) {
    if (out->bufsize == out->full) { // if full -> flush
        flush(out);
        out->full = 0;
    }
    out->buf[out->full] = c;
    out->full += 1;
}
// void exit(int exit_code)
// {
//     __asm__ volatile(
//         "int    $0x80\n\t":: "a"(__NR_exit), "b"(exit_code));
//     for (;;) {}
// }
// void _start(void)
// {
//     int current_char = 0;
//     while((current_char = nextchar()) != -1) {
//         writechar(current_char, stout);
//     }
//     writechar('\n', stout);
//     flush(stout);
//     exit(0);
// }
