//
//  chip8.c
//  chip-8
//
//  Created by Lonnie Gerol on 12/14/20.
//

#include "chip8.h"

static unsigned short program_counter;
static unsigned short current_opcode;
static unsigned short index_register; // I
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

// Fontset
unsigned char chip8_fontset[80] =
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

/**
 * Initializes registers and memory.
 */
void initialize() {
    // Initalizes registers and memory
    program_counter = 0x200; // Program counter starts at 0x200
    current_opcode  = 0;
    index_register  = 0;
    stack_pointer   = 0;

    // Clear display
    // Clear stack
    // Clear registers V0-VF
    // Clear memory

    // Load fontset
    for ( int i = 0; i < 80; ++i ) {
        memory[i] = chip8_fontset[i];
    }
}

void emulateCycle() {
    // Fetch Opcode
    // each location in memory stores 1 byte but each opcode is 2 bytes long so we fetch two successive bytes and merge them to get the opcode.
    current_opcode = memory[program_counter] << 8 | memory[program_counter + 1];

    // Decode Opcode
    // looking at the first 4 digits of opcode in switch statement
    switch (current_opcode & 0xF000) {

        // ANNN
        // first four digits are opcode last 12 are data
        case 0xA000:
            // look at the last twelve digits
            index_register = current_opcode & 0x0FFF;
            program_counter += 2;
            break;

        case 0x0000:
            switch (current_opcode & 0x0FFF) {
                // just checking the last 3 digits
                case 0x00E0:
                    break;
                case 0x00EE:
                    break;
            }

        default:
            printf("Unknown opcode: 0x%X\n", current_opcode);
    }

    // first 8 digits are the same
    switch(current_opcode & 0x00FF) {
        case 0x00E0:
            break;
        case 0x00EE:
            break;
    }

    // Execute Opcode

    // Update timers
}
