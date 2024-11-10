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

pass=0
fail=0
while IFS=',' read -r input input2
do
    
    output=$(./main <<< "$input")
    
    if [ $input2 == $output ]; then
         pass=$((pass + 1))  # Increment pass
         echo "input: $input, main: $output, correct: $input2 ==> passed"
    else
        fail=$((fail + 1))  # Increment fail
        echo "input: $input, main: $output, correct: $input2 ==> failed"
    fi

done < "./test_inputs.txt"
echo ""
echo "Tests passed: $pass"
echo "Tests failed: $fail"