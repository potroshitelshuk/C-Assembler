#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <dirent.h>
#include <limits.h>
#include <unistd.h>
#include <ctype.h>

int main(int argc, const char* argv[]) {
    unsigned long long size = 0;
    DIR *dir = opendir(argv[1]);
    struct dirent *dirent_ = readdir(dir);
    uid_t uid = getuid();
    while (dirent_) {
        char arr[PATH_MAX + 1];
        snprintf(arr, PATH_MAX, "%s/%s", argv[1], dirent_->d_name);
        struct stat st;
        if (stat(arr, &st) == 0 && S_ISREG(st.st_mode) &&
         st.st_uid == uid && isupper(dirent_->d_name[0])) {
            // printf("%lld\n", st.st_size);
            size += st.st_size;
        }
        dirent_ = readdir(dir);
    }
    printf("%llu\n", size);
    closedir(dir);
    return 0;
}
