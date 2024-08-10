#include "ncurses_display.h"
#include "semi_htop.h"

int main() {
  HTOP htop;
  NCursesDisplay::Display(htop);
}