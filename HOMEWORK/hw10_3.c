#include <syscall.h>

struct FileReadState {
    int fd;
    unsigned char *buf;
    int bufsize;
    int lc;
    int it1, it2;
};
unsigned char buf[4096];
struct FileReadState state = {0, buf, 4096, 0, 0, 0};
struct FileReadState *stin = &state;
int lastchar() {
    return stin->lc;
}
int nextchar() {
    int fl = 0;
    if (stin->lc == -1) {
        return -1;
    }
    if (stin->it1 == stin->it2) {
        if (stin->it2 == stin->bufsize) {
            stin->it2 = 0;
            stin->it1 = 0;
        }
        int dif = stin->bufsize - stin->it2;
        asm volatile(
            "mov %1, %%eax \n"
            "mov %2, %%ebx \n"
            "mov %3, %%ecx \n"
            "mov %4, %%edx \n"
            "int $0x80 \n"
            "mov %%eax, %0 \n"
        : "=g"(fl)
        : "g" (__NR_read), "g" (0), "g" (stin->buf + stin->it2), "g" (dif)
        : "%eax", "%ebx", "%ecx", "%edx", "memory");
        if (fl > 0) {
            stin->it2 += fl;
        } else {
            stin->lc = -1;
            return stin->lc;
        }
    }
    int ind = stin->it1;
    stin->lc = stin->buf[ind];
    stin->it1++;
    return stin->lc;
}
// CE?
// void exit(int exit_code) {
//     __asm__ volatile(
//         "int    $0x80\n\t"
//         :: "a"(__NR_exit), "b"(exit_code)
//     );
//     for (;;) {}
// }
// void _start(void) {
//     int current_char = nextchar();
//     while (current_char != -1) {
//         unsigned char c = (unsigned char)current_char;
//         asm volatile(
//             "movl $4, %%eax\n"
//             "movl $1, %%ebx\n"
//             "movl %0, %%ecx\n"
//             "movl $1, %%edx\n"
//             "int $0x80\n"
//             ::"g"(&c)
//             :"%eax", "%ebx", "%ecx", "%edx", "memory"  
//         );
//         current_char = nextchar();
//     }
//     asm volatile(
//         "movl $4, %%eax\n"
//         "movl $1, %%ebx\n"
//         "movl %0, %%ecx\n"
//         "movl $4, %%edx\n"
//         "int $0x80\n"
//         ::"g"(&current_char)
//         :"%eax", "%ebx", "%ecx", "%edx", "memory"
//     );
//     exit(0);
// }
