//
//  chip8.c
//  chip-8
//
//  Created by Lonnie Gerol on 12/14/20.
//

#include "chip8.h"
static unsigned short program_counter;
static unsigned short current_opcode;
static unsigned short index_register;
static unsigned char memory[4096];
static unsigned char V[16]; // CPU Registers

// stack
static unsigned short stack[16];
static unsigned short stack_pointer;

// Graphics + sound
static unsigned char gfx[64 * 32];
static unsigned char delay_timer;
static unsigned char sound_timer;

// keypad
unsigned char key[16];


/**
 * Initializes registers and memory.
 */
void initialize() {
    // Initalizes registers and memory
    program_counter = 0x200; // Program counter starts at 0x200
    current_opcode = 0;
    index_register = 0;
    stack_pointer = 0;
}

void emulateCycle() {
    // Fetch Opcode
    // Decode Opcode
    // Execute Opcode

    // Update timers
}
