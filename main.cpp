
#include <csignal>
#include <fcntl.h>
#include <linux/input.h>
#include <linux/version.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#define DEV_INPUT "/dev/input/event"
#define KEY_MAX			0x2ff

#define EXIT_SUCCES 0
#define EXIT_ERROR  0


// as far as i understood volatile is required to prevent some funny compiler interactions TwT
static volatile int stop = 0;

void interrupt_handler(int sig){
    stop=1;
}

int get_keycode(){

}
/**
 *  @param fd corresponds to /dev/input/input<FD>
 */
int record_event(int fd){
    int rd;
    input_event ev[64];

    fd_set rdfs; // allows for synchronious I/O??? https://linux.die.net/man/3/fd_set

	FD_ZERO(&rdfs);
	FD_SET(fd, &rdfs);

    while (!stop) {
        // multiplexing
        // as far as i understood this will multiply output.. kinda xd
        // https://www.man7.org/linux/man-pages/man2/select.2.html
        select(fd + 1, &rdfs, NULL, NULL, NULL);
        if(stop){
            break;
        }
        rd = read(fd,ev,sizeof(ev));

        if (rd < (int) sizeof(struct input_event)) {
			printf("expected %d bytes, got %d\n", (int) sizeof(struct input_event), rd);
			perror("\nevtest: error reading");
			return 1;
		}

        for (int i = 0; i < rd / sizeof(struct input_event); i++) {
            printf("code: %d value: %d\n",ev[i].code,ev[i].value);
        }

    }
    return EXIT_SUCCES;
}
/**
 * @param dev input device number
 */
int start_reading(int dev){
    if(getuid() != 0){
        printf("you run this program as regular user, some inputs may not work");
    }
    int fd;
    std::string filename = DEV_INPUT;
    filename.push_back(dev+'0');
    fd = open(filename.c_str(),O_RDONLY);

    signal(SIGINT, interrupt_handler);
	signal(SIGTERM, interrupt_handler);

    return record_event(fd);
}

int main(int argc, char **argv) {
  printf("%d\n", getuid());
  start_reading(5);
  return EXIT_FAILURE;
}
