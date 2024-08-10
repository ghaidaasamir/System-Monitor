#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include "semi_htop.h"

namespace NCursesDisplay {
void Display(HTOP& htop, int n = 10);
void DisplaySystem(HTOP& htop, WINDOW* window);
void DisplayProcesses(const std::vector<PROCESS>& processes, WINDOW* window,
                      int n);
std::string ProgressBar(float percent);
};  

#endif
