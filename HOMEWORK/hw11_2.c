#include <unistd.h>

void copy_file(int in_fd, int out_fd) {
    char mas[4 * 1024];
    // int sum = 0;
    int input;
    while ((input = read(in_fd, mas, 4 * 1024)) > 0) {
        int output = write(out_fd, mas, input);
        while (output < input) {
            output += write(out_fd, mas + output, input - output);
        // if (output == 0)
      //     break;
      // if (output < 0)
      //     return -1;
      // sum += output;
      // ptr += output;
      // input -= output;
        }
    }
}
