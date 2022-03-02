void myexit() {
asm volatile("mov $1, %%eax \n"
        "xor %%ebx, %%ebx \n"
        "int $0x80":::"eax", "ebx");
}

void _start() {
    char symb;
    int fl;
    while (1) {
    asm volatile("movl $3, %%eax \n"
        "movl $0, %%ebx \n"
        "movl %1, %%ecx \n"
        "movl $1, %%edx \n"
        "int $0x80 \n"
        "movl %%eax, %0"
        :"=g" (fl):"g" (&symb):"%eax", "%ebx", "%ecx", "%edx", "memory");
    if (!fl)
        break;
    if (symb >= 'a' && symb <= 'z')
        symb -= 32;
        asm volatile("movl $4, %%eax \n"
            "movl $1, %%ebx \n"
            "movl %1, %%ecx \n"
            "movl $1, %%edx \n"
            "int $0x80 \n"
            "movl %%eax, %0"
            :"=g" (fl):"g" (&symb): "eax", "%ebx", "%ecx", "%edx", "memory");
    }
	myexit();
}