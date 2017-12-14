#include <genesis.h> // gendev 0.3.0

// Define the limits of the screen
#define MIN_X 0
#define MAX_X 39
#define MIN_Y 0
#define MAX_Y 27

// Define the starting position of the character on the screen
#define START_X 1
#define START_Y 8

int next = 0;

// This function is called when any gamepad input changes
void joyHandler(u16 joy, u16 changed, u16 state) {
  // Ignore input from anything except player one
  if (joy != JOY_1) {
    return;
  }

  // Move the string around on the screen with gamepad input while ensuring
  // the current position is always visible.
  if (state & BUTTON_A) {
    next = 1;
  }
}

void slide1() {
  VDP_drawText("Sega Mega Drive Development", START_X, START_Y);
  VDP_drawText("by Cyle Riggs (@beardedfoo)", START_X, START_Y+1);
}

void slide2() {
  int y = START_Y;
  VDP_drawText("Sega Mega Drive:", START_X, y++);
  VDP_drawText("  Released in Japan, 1988", START_X, y++);
  VDP_drawText("  Marketed as Genesis in US market", START_X, y++);
}

void slide3() {
  int y = START_Y;
  VDP_drawText("Sega Mega Drive:", START_X, y++);
  VDP_drawText(" CPUs:", START_X, y++);
  VDP_drawText("  Motorola 68000 (16/32-bit) @ 7.6 MHz", START_X, y++);
  VDP_drawText("  Zilog Z80 (8-bit) @ 3.68 MHz", START_X, y++);
  VDP_drawText(" Memory:", START_X, y++);
  VDP_drawText("  RAM 64KB", START_X, y++);
}

void slide4() {
  int y = START_Y;  
  VDP_drawText("Video:", START_X, y++);
  VDP_drawText(" VDP (Custom Texas Instruments Chip)", START_X, y++);
  VDP_drawText(" Resolution: 320x224", START_X, y++);
  VDP_drawText(" 4 palettes x 15 colors", START_X, y++);
  VDP_drawText(" 64 sprites per frame", START_X, y++);
  VDP_drawText(" 2 background planes of 40x28 tiles", START_X, y++);
  VDP_drawText(" Tiles: 8x8 pixels", START_X, y++);
  VDP_drawText(" Sprites: 1x1 - 4x4 tiles", START_X, y++);
}

void slide5() {
  int y = START_Y;
  VDP_drawText("Development Scene:", START_X, y++);
  VDP_drawText(" -Historically stuck on emulators", START_X, y++);
  VDP_drawText(" -Historically windows only", START_X, y++);
  VDP_drawText(" -Required 68k and Z80 assembly", START_X, y++);
  VDP_drawText(" -New software and hardware tools", START_X, y++);  
  VDP_drawText("  emerging.", START_X, y++);  
}

void slide6() {
  int y = START_Y;
  VDP_drawText("My Goals:", START_X, y++);
  VDP_drawText(" -Integrate tools by various authors", START_X, y++);
  VDP_drawText(" -Properly open source: github", START_X, y++);
  VDP_drawText(" -Tutorials", START_X, y++);
  VDP_drawText(" -Simplify SDK intall", START_X, y++);
  VDP_drawText(" -Modernize: docker, beyond C?", START_X, y++);  
  VDP_drawText(" -Document hardware tools", START_X, y++);
  VDP_drawText(" -Promote 2D + couch co-op game dev", START_X, y++);
}

void end_slide() {
  int y = START_Y;
  VDP_drawText("The End!", START_X, y++);  
  VDP_drawText("Now, time for some demos!", START_X, y++);
  y++;  
  VDP_drawText("P.S. - This slideshow is running", START_X, y++);
  VDP_drawText("on a Sega Mega Drive...!", START_X, y++);
  y++;
  VDP_drawText("An @beardedfoo production", START_X, y++);
  y++;
  VDP_drawText("  github.com/beardedfoo", START_X, y++);
  VDP_drawText("  twitter.com/beardedfoo", START_X, y++);
  y++;
  VDP_drawText("  awesomespace.nl", START_X, y++);  
  
  while(1) { VDP_waitVSync(); }
}

void wait_for_next() {
  while(1) {
    VDP_waitVSync();

    if (next) {
      next = 0;
      
      for (int y = 0; y < MAX_Y; y++) {
        VDP_drawText("                                        ", 0, y);
      }

      return;
    }
  }
}

int main() {
  // Prepare the video chip for use
  VDP_init();

  // Prepare to read gamepad input
  JOY_init();

  // Register a function to respond to gamepad input
  JOY_setEventHandler(&joyHandler);

  // Wait for a time when the CRT is not drawing on the screen
  VDP_waitVSync();

  slide1();
  wait_for_next();

  slide2();
  wait_for_next();

  slide3();
  wait_for_next();

  slide4();
  wait_for_next();

  slide5();
  wait_for_next();

  slide6();
  wait_for_next();
  
  end_slide();
}
