
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <linux/version.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#define DEV_INPUT "/dev/input/event"

#define EXIT_SUCCES 0
#define EXIT_ERROR 1

#define NAME_ELEMENT(element) [element] = #element

/* extracted from /usr/include/linux/input-event-codes.h */
const char *names[KEY_MAX] = {NAME_ELEMENT(KEY_RESERVED),
                              NAME_ELEMENT(KEY_ESC),
                              NAME_ELEMENT(KEY_1),
                              NAME_ELEMENT(KEY_2),
                              NAME_ELEMENT(KEY_3),
                              NAME_ELEMENT(KEY_4),
                              NAME_ELEMENT(KEY_5),
                              NAME_ELEMENT(KEY_6),
                              NAME_ELEMENT(KEY_7),
                              NAME_ELEMENT(KEY_8),
                              NAME_ELEMENT(KEY_9),
                              NAME_ELEMENT(KEY_0),
                              NAME_ELEMENT(KEY_MINUS),
                              NAME_ELEMENT(KEY_EQUAL),
                              NAME_ELEMENT(KEY_BACKSPACE),
                              NAME_ELEMENT(KEY_TAB),
                              NAME_ELEMENT(KEY_Q),
                              NAME_ELEMENT(KEY_W),
                              NAME_ELEMENT(KEY_E),
                              NAME_ELEMENT(KEY_R),
                              NAME_ELEMENT(KEY_T),
                              NAME_ELEMENT(KEY_Y),
                              NAME_ELEMENT(KEY_U),
                              NAME_ELEMENT(KEY_I),
                              NAME_ELEMENT(KEY_O),
                              NAME_ELEMENT(KEY_P),
                              NAME_ELEMENT(KEY_LEFTBRACE),
                              NAME_ELEMENT(KEY_RIGHTBRACE),
                              NAME_ELEMENT(KEY_ENTER),
                              NAME_ELEMENT(KEY_LEFTCTRL),
                              NAME_ELEMENT(KEY_A),
                              NAME_ELEMENT(KEY_S),
                              NAME_ELEMENT(KEY_D),
                              NAME_ELEMENT(KEY_F),
                              NAME_ELEMENT(KEY_G),
                              NAME_ELEMENT(KEY_H),
                              NAME_ELEMENT(KEY_J),
                              NAME_ELEMENT(KEY_K),
                              NAME_ELEMENT(KEY_L),
                              NAME_ELEMENT(KEY_SEMICOLON),
                              NAME_ELEMENT(KEY_APOSTROPHE),
                              NAME_ELEMENT(KEY_GRAVE),
                              NAME_ELEMENT(KEY_LEFTSHIFT),
                              NAME_ELEMENT(KEY_BACKSLASH),
                              NAME_ELEMENT(KEY_Z),
                              NAME_ELEMENT(KEY_X),
                              NAME_ELEMENT(KEY_C),
                              NAME_ELEMENT(KEY_V),
                              NAME_ELEMENT(KEY_B),
                              NAME_ELEMENT(KEY_N),
                              NAME_ELEMENT(KEY_M),
                              NAME_ELEMENT(KEY_COMMA),
                              NAME_ELEMENT(KEY_DOT),
                              NAME_ELEMENT(KEY_SLASH),
                              NAME_ELEMENT(KEY_RIGHTSHIFT),
                              NAME_ELEMENT(KEY_KPASTERISK),
                              NAME_ELEMENT(KEY_LEFTALT),
                              NAME_ELEMENT(KEY_SPACE),
                              NAME_ELEMENT(KEY_CAPSLOCK),
                              NAME_ELEMENT(KEY_F1),
                              NAME_ELEMENT(KEY_F2),
                              NAME_ELEMENT(KEY_F3),
                              NAME_ELEMENT(KEY_F4),
                              NAME_ELEMENT(KEY_F5),
                              NAME_ELEMENT(KEY_F6),
                              NAME_ELEMENT(KEY_F7),
                              NAME_ELEMENT(KEY_F8),
                              NAME_ELEMENT(KEY_F9),
                              NAME_ELEMENT(KEY_F10),
                              NAME_ELEMENT(KEY_NUMLOCK),
                              NAME_ELEMENT(KEY_SCROLLLOCK),
                              NAME_ELEMENT(KEY_KP7),
                              NAME_ELEMENT(KEY_KP8),
                              NAME_ELEMENT(KEY_KP9),
                              NAME_ELEMENT(KEY_KPMINUS),
                              NAME_ELEMENT(KEY_KP4),
                              NAME_ELEMENT(KEY_KP5),
                              NAME_ELEMENT(KEY_KP6),
                              NAME_ELEMENT(KEY_KPPLUS),
                              NAME_ELEMENT(KEY_KP1),
                              NAME_ELEMENT(KEY_KP2),
                              NAME_ELEMENT(KEY_KP3),
                              NAME_ELEMENT(KEY_KP0),
                              NAME_ELEMENT(KEY_KPDOT),
                              NAME_ELEMENT(KEY_ZENKAKUHANKAKU),
                              NAME_ELEMENT(KEY_102ND),
                              NAME_ELEMENT(KEY_F11),
                              NAME_ELEMENT(KEY_F12),
                              NAME_ELEMENT(KEY_RO),
                              NAME_ELEMENT(KEY_KATAKANA),
                              NAME_ELEMENT(KEY_HIRAGANA),
                              NAME_ELEMENT(KEY_HENKAN),
                              NAME_ELEMENT(KEY_KATAKANAHIRAGANA),
                              NAME_ELEMENT(KEY_MUHENKAN),
                              NAME_ELEMENT(KEY_KPJPCOMMA),
                              NAME_ELEMENT(KEY_KPENTER),
                              NAME_ELEMENT(KEY_RIGHTCTRL),
                              NAME_ELEMENT(KEY_KPSLASH),
                              NAME_ELEMENT(KEY_SYSRQ),
                              NAME_ELEMENT(KEY_RIGHTALT),
                              NAME_ELEMENT(KEY_LINEFEED),
                              NAME_ELEMENT(KEY_HOME),
                              NAME_ELEMENT(KEY_UP),
                              NAME_ELEMENT(KEY_PAGEUP),
                              NAME_ELEMENT(KEY_LEFT),
                              NAME_ELEMENT(KEY_RIGHT),
                              NAME_ELEMENT(KEY_END),
                              NAME_ELEMENT(KEY_DOWN),
                              NAME_ELEMENT(KEY_PAGEDOWN),
                              NAME_ELEMENT(KEY_INSERT),
                              NAME_ELEMENT(KEY_DELETE),
                              NAME_ELEMENT(KEY_MACRO),
                              NAME_ELEMENT(KEY_MUTE),
                              NAME_ELEMENT(KEY_VOLUMEDOWN),
                              NAME_ELEMENT(KEY_VOLUMEUP),
                              NAME_ELEMENT(KEY_POWER),
                              NAME_ELEMENT(KEY_KPEQUAL),
                              NAME_ELEMENT(KEY_KPPLUSMINUS),
                              NAME_ELEMENT(KEY_PAUSE),
                              NAME_ELEMENT(KEY_SCALE),
                              NAME_ELEMENT(KEY_KPCOMMA),
                              NAME_ELEMENT(KEY_HANGEUL),
                              NAME_ELEMENT(KEY_HANGUEL),
                              NAME_ELEMENT(KEY_HANJA),
                              NAME_ELEMENT(KEY_YEN),
                              NAME_ELEMENT(KEY_LEFTMETA),
                              NAME_ELEMENT(KEY_RIGHTMETA),
                              NAME_ELEMENT(KEY_COMPOSE),
                              NAME_ELEMENT(KEY_STOP),
                              NAME_ELEMENT(KEY_AGAIN),
                              NAME_ELEMENT(KEY_PROPS),
                              NAME_ELEMENT(KEY_UNDO),
                              NAME_ELEMENT(KEY_FRONT),
                              NAME_ELEMENT(KEY_COPY),
                              NAME_ELEMENT(KEY_OPEN),
                              NAME_ELEMENT(KEY_PASTE),
                              NAME_ELEMENT(KEY_FIND),
                              NAME_ELEMENT(KEY_CUT),
                              NAME_ELEMENT(KEY_HELP),
                              NAME_ELEMENT(KEY_MENU),
                              NAME_ELEMENT(KEY_CALC),
                              NAME_ELEMENT(KEY_SETUP),
                              NAME_ELEMENT(KEY_SLEEP),
                              NAME_ELEMENT(KEY_WAKEUP),
                              NAME_ELEMENT(KEY_FILE),
                              NAME_ELEMENT(KEY_SENDFILE),
                              NAME_ELEMENT(KEY_DELETEFILE),
                              NAME_ELEMENT(KEY_XFER),
                              NAME_ELEMENT(KEY_PROG1),
                              NAME_ELEMENT(KEY_PROG2),
                              NAME_ELEMENT(KEY_WWW),
                              NAME_ELEMENT(KEY_MSDOS),
                              NAME_ELEMENT(KEY_COFFEE),
                              NAME_ELEMENT(KEY_SCREENLOCK),
                              NAME_ELEMENT(KEY_ROTATE_DISPLAY),
                              NAME_ELEMENT(KEY_DIRECTION),
                              NAME_ELEMENT(KEY_CYCLEWINDOWS),
                              NAME_ELEMENT(KEY_MAIL),
                              NAME_ELEMENT(KEY_BOOKMARKS),
                              NAME_ELEMENT(KEY_COMPUTER),
                              NAME_ELEMENT(KEY_BACK),
                              NAME_ELEMENT(KEY_FORWARD),
                              NAME_ELEMENT(KEY_CLOSECD),
                              NAME_ELEMENT(KEY_EJECTCD),
                              NAME_ELEMENT(KEY_EJECTCLOSECD),
                              NAME_ELEMENT(KEY_NEXTSONG),
                              NAME_ELEMENT(KEY_PLAYPAUSE),
                              NAME_ELEMENT(KEY_PREVIOUSSONG),
                              NAME_ELEMENT(KEY_STOPCD),
                              NAME_ELEMENT(KEY_RECORD),
                              NAME_ELEMENT(KEY_REWIND),
                              NAME_ELEMENT(KEY_PHONE),
                              NAME_ELEMENT(KEY_ISO),
                              NAME_ELEMENT(KEY_CONFIG),
                              NAME_ELEMENT(KEY_HOMEPAGE),
                              NAME_ELEMENT(KEY_REFRESH),
                              NAME_ELEMENT(KEY_EXIT),
                              NAME_ELEMENT(KEY_MOVE),
                              NAME_ELEMENT(KEY_EDIT),
                              NAME_ELEMENT(KEY_SCROLLUP),
                              NAME_ELEMENT(KEY_SCROLLDOWN),
                              NAME_ELEMENT(KEY_KPLEFTPAREN),
                              NAME_ELEMENT(KEY_KPRIGHTPAREN),
                              NAME_ELEMENT(KEY_NEW),
                              NAME_ELEMENT(KEY_REDO),
                              NAME_ELEMENT(KEY_F13),
                              NAME_ELEMENT(KEY_F14),
                              NAME_ELEMENT(KEY_F15),
                              NAME_ELEMENT(KEY_F16),
                              NAME_ELEMENT(KEY_F17),
                              NAME_ELEMENT(KEY_F18),
                              NAME_ELEMENT(KEY_F19),
                              NAME_ELEMENT(KEY_F20),
                              NAME_ELEMENT(KEY_F21),
                              NAME_ELEMENT(KEY_F22),
                              NAME_ELEMENT(KEY_F23),
                              NAME_ELEMENT(KEY_F24),
                              NAME_ELEMENT(KEY_PLAYCD),
                              NAME_ELEMENT(KEY_PAUSECD),
                              NAME_ELEMENT(KEY_PROG3),
                              NAME_ELEMENT(KEY_PROG4),
                              NAME_ELEMENT(KEY_ALL_APPLICATIONS),
                              NAME_ELEMENT(KEY_DASHBOARD),
                              NAME_ELEMENT(KEY_SUSPEND),
                              NAME_ELEMENT(KEY_CLOSE),
                              NAME_ELEMENT(KEY_PLAY),
                              NAME_ELEMENT(KEY_FASTFORWARD),
                              NAME_ELEMENT(KEY_BASSBOOST),
                              NAME_ELEMENT(KEY_PRINT),
                              NAME_ELEMENT(KEY_HP),
                              NAME_ELEMENT(KEY_CAMERA),
                              NAME_ELEMENT(KEY_SOUND),
                              NAME_ELEMENT(KEY_QUESTION),
                              NAME_ELEMENT(KEY_EMAIL),
                              NAME_ELEMENT(KEY_CHAT),
                              NAME_ELEMENT(KEY_SEARCH),
                              NAME_ELEMENT(KEY_CONNECT),
                              NAME_ELEMENT(KEY_FINANCE),
                              NAME_ELEMENT(KEY_SPORT),
                              NAME_ELEMENT(KEY_SHOP),
                              NAME_ELEMENT(KEY_ALTERASE),
                              NAME_ELEMENT(KEY_CANCEL),
                              NAME_ELEMENT(KEY_BRIGHTNESSDOWN),
                              NAME_ELEMENT(KEY_BRIGHTNESSUP),
                              NAME_ELEMENT(KEY_MEDIA),
                              NAME_ELEMENT(KEY_SWITCHVIDEOMODE),
                              NAME_ELEMENT(KEY_KBDILLUMTOGGLE),
                              NAME_ELEMENT(KEY_KBDILLUMDOWN),
                              NAME_ELEMENT(KEY_KBDILLUMUP),
                              NAME_ELEMENT(KEY_SEND),
                              NAME_ELEMENT(KEY_REPLY),
                              NAME_ELEMENT(KEY_FORWARDMAIL),
                              NAME_ELEMENT(KEY_SAVE),
                              NAME_ELEMENT(KEY_DOCUMENTS),
                              NAME_ELEMENT(KEY_BATTERY),
                              NAME_ELEMENT(KEY_BLUETOOTH),
                              NAME_ELEMENT(KEY_WLAN),
                              NAME_ELEMENT(KEY_UWB),
                              NAME_ELEMENT(KEY_UNKNOWN),
                              NAME_ELEMENT(KEY_VIDEO_NEXT),
                              NAME_ELEMENT(KEY_VIDEO_PREV),
                              NAME_ELEMENT(KEY_BRIGHTNESS_CYCLE),
                              NAME_ELEMENT(KEY_BRIGHTNESS_AUTO),
                              NAME_ELEMENT(KEY_BRIGHTNESS_ZERO),
                              NAME_ELEMENT(KEY_DISPLAY_OFF),
                              NAME_ELEMENT(KEY_WWAN),
                              NAME_ELEMENT(KEY_WIMAX),
                              NAME_ELEMENT(KEY_RFKILL),
                              NAME_ELEMENT(KEY_MICMUTE)};

// as far as i understood volatile is required to prevent some funny compiler
// interactions TwT
static volatile int stop = 0;

void interrupt_handler(int sig) { stop = 1; }

/**
 *  @param fd corresponds to /dev/input/input<FD>
 */
int record_event(int fd) {
  int rd;
  input_event ev[64];

  fd_set
      rdfs; // allows for synchronious I/O??? https://linux.die.net/man/3/fd_set

  FD_ZERO(&rdfs);
  FD_SET(fd, &rdfs);

  while (!stop) {
    // multiplexing
    // as far as i understood this will multiply output.. kinda xd
    // https://www.man7.org/linux/man-pages/man2/select.2.html
    select(fd + 1, &rdfs, NULL, NULL, NULL);
    if (stop) {
      break;
    }
    rd = read(fd, ev, sizeof(ev));

    if (rd < (int)sizeof(struct input_event)) {
      printf("expected %d bytes, got %d\n", (int)sizeof(struct input_event),
             rd);
      perror("\nevtest: error reading");
      return 1;
    }

    for (int i = 0; i < rd / sizeof(struct input_event); i++) {

      // v  2  hold
      // v   0  released
      // c 0 - ***is normally an error code***
      // https://aeb.win.tue.nl/linux/kbd/scancodes-1.html#ss1.3
      if (ev[i].value == 1 && ev[i].code != 0) {

        printf("%s\n", names[ev[i].code]);
      }
    }
  }
  return EXIT_SUCCES;
}
/**
 * @param dev input device number
 */
int start_reading(char *dev) {
  if (getuid() != 0) {
    fprintf(stderr,"you run this program as regular user, some inputs may not work");
  }
  int fd;
  char *filename = NULL;
  if (!dev) {
    // promt device select
  } else {
    filename = strdup(dev);
  }
  if (!filename) {
    fprintf(stderr,"Error, no device provided");
    return EXIT_FAILURE;
  }
  fd = open(filename, O_RDONLY);

  signal(SIGINT, interrupt_handler);
  signal(SIGTERM, interrupt_handler);

  return record_event(fd);
}

int main(int argc, char **argv) {
  printf("%d\n", getuid());
  start_reading(argv[2]);
  return EXIT_FAILURE;
}
