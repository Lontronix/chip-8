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

        case 0x0000:
            switch (current_opcode & 0x0FFF) {
                    // just checking the last 3 digits
                    // 00E0 - Clears the screen.
                case 0x00E0:
                    break;
                    // 00EE - returns from a subroutine.
                case 0x00EE:
                    break;
            }
        // 1NNN - Jumps to adress NNN
        case 0x1000:
            break;
        // 2NNN - Calls subroutine at NNN.
        case 0x2000:
            break;
        // 3XNN - Skips the next instruction if VX equals NN. (Usually the next instruction is a jump to skip a code block)
        case 0x3000:
            break;
        //4XNN - Skips the next instruction if VX doesn't equal NN. (Usually the next instruction is a jump to skip a code block)
        case 0x4000:
            break;
        //5XY0 - Skips the next instruction if VX equals VY. (Usually the next instruction is a jump to skip a code block)
        case 0x5000:
            break;
        //6XNN - Sets VX to NN.
        case 0x6000:
            break;
        //7XNN - Adds NN to VC (Carry flag is unchanged)
        case 0x7000:
            break;
        case 0x8000:
            switch (current_opcode & 0x000F) {
                    // 8XY0 - Sets VX to the value of VY
                case 0x0000:
                    break;
                    // 8XY1 - Sets VX to VX or VY (Bitwise OR Operation)
                case 0x0001:
                    break;
                    // 8XY2 - Sets VX to VX and VY (Bitwise AND operation)
                case 0x0002:
                    break;
                    // 8XY3 - Sets VX to VX xor VY
                case 0x0003:
                    break;
                    // 8XY4 - Adds VY to VX. VF is set to 1 when there's a carry, and to 0 when there isn't
                case 0x0004:
                    break;
                    // 8XY5 - VY is subtracted from VX. VF is set to 0 when there's a borrow, and 1 when there isn't
                case 0x0005:
                    break;
                    // 8XY6 - Stores the least signficiant bit of VX in VF and then shifts VX to the right by 1.
                case 0x0006:
                    break;
                    // 8XY7 - Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
                case 0x0007:
                    break;
                    // 8XYE - Stores the most significant bit of VX in VF and then shifts VX to the left by 1.
                case 0x000E:
                    break;
            }
        // 9XY0 - Skips the next instruction if VX doesn't equal VY.
        case 0x9000:
            break;
        // ANNN - Sets I to the address NNN.
        // first four digits are opcode last 12 are data
        case 0xA000:
            // look at the last twelve digits
            index_register = current_opcode & 0x0FFF;
            program_counter += 2;
            break;
        // BNNN - Jumps to the address NNN plus V0.
        case 0xB000:
            break;
        // CXNN - Sets VX to the result of a bitwise and operation on a random number.
        case 0xC000:
            break;
        // DXYN - Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N+1 pixels.
        case 0xD000:
            break;
        case 0xE000:
            switch (current_opcode & 0x00FF) {
                // EX9E - Skips the next instruction if the key stored in VX is pressed.
                case 0x009E:
                    break;
                // EXA1 - Skips the next instruction if the key stored in VX isn't pressed.
                case 0x00A1:
                    break;
            }
        case 0xF000:
            switch (current_opcode & 0x00FF) {
                // FX07 - Sets VX to the value of the delay timer.
                case 0x0007:
                    break;
                // FX0A - A key press is awaited, and then stored in VX.
                case 0x000A:
                    break;
                // FX15 - Setes the delay timer to VX.
                case 0x0015:
                    break;
                // FX18 - sets the sound timer to VX.
                case 0x0018:
                    break;
                // FX1E - Adds VX to I.
                case 0x001E:
                    break;
                // FX29 - Sets I to the location of the sprite for the characater in VX.
                case 0x0029:
                    break;
                // FX33
                case 0x0033:
                    break;
                // FX55 - Stores V0 to VX (including VX) in memory starting at address I.
                case 0x0055:
                    break;
                // FX65 - Fills V0 to VX (including VX) with values from memory starting at address I.
                case 0x0065:
                    break;
            }

        default:
            printf("Unknown opcode: 0x%X\n", current_opcode);
    }

    // Execute Opcode

    // Update timers
}
