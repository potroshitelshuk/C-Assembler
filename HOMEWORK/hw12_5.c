#include <sys/stat.h>
// #include <string.h>
// #include <inttypes.h>
// #include <unistd.h>
// #include <ctype.h>
// #include <stdint.h>

struct Task {
    unsigned uid;
    int gid_count;
    unsigned *gids;
};


int myaccess(const struct stat *stb, const struct Task *task, int access) {
    int res = 1;
    int b = 0;
    if (task->uid == 0) {
        return res;
    }
    if (stb->st_uid == task->uid) {
        b = (stb->st_mode >> 6) & 7; 
        return (b & 1) >= (access & 1) && (b & 2) >= (access & 2) && (b & 4) >= (access & 4);
    }

    for (int x = 0; x != task->gid_count; ++x) {
        if (task->gids[x] == stb->st_gid) {
            b = (stb->st_mode >> 3) & 7; 
            return (b & 1) >= (access & 1) && (b & 2) >= (access & 2) && (b & 4) >= (access & 4);
        }
    }
    b = (stb->st_mode ) & 7; 
    return (b & 1) >= (access & 1) && (b & 2) >= (access & 2) && (b & 4) >= (access & 4);
}
