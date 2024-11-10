#!/bin/bash
echo "start building main program"
echo "compiling to assembly lines ..."
cc main.c -S
cc increment.c -S
echo "translating to opcodes ..."
cc main.s -c
cc increment.s -c
echo "statically linking all required opcode ..."
cc main.o increment.o -o main
echo "build successfully done:"
./main