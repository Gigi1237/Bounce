#pragma once

#include "internal.h"

class Fade2D;

typedef void(Fade2D::*ClassKeyHandler)(int, int);


void genericKeyHandler(Fade2D* lib, int key, int scancode, int action, int mods);

void addClassKeyHandler(Fade2D* lib);
