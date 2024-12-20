#!/bin/bash

SOURCE_DIR=./input
PJC_EXEC_DIR=pjc_exec
FPC_EXEC_DIR=fpc_exec

if [ $# -eq 0 ]
then
    echo "Syntax: compile_script.sh <clean or input_file> <bool for comparison>"
    exit
fi

if [ $1 = "clean" ]
then
    rm $SOURCE_DIR/*.o 2> /dev/null
    rm $SOURCE_DIR/*.s 2> /dev/null
    rm -r $SOURCE_DIR/$OUTPUT_DIR/ 2> /dev/null
    rm -r $SOURCE_DIR/$PJC_EXEC_DIR/ 2> /dev/null
    rm -r $SOURCE_DIR/$FPC_EXEC_DIR/ 2> /dev/null
    exit
fi

mkdir $SOURCE_DIR/$PJC_EXEC_DIR 2> /dev/null

./pjc $SOURCE_DIR/$1.pas
gcc -c -g3 $SOURCE_DIR/$1.s -o $SOURCE_DIR/$1.o
gcc -g3 $SOURCE_DIR/$1.o -o $SOURCE_DIR/$PJC_EXEC_DIR/$1

echo -e "\nContinue? (y/n)"
read cont
if [[ $cont = "y" || $cont = "yes" ]]
then
    echo -e "\n\n-------------------------------------PJC EXECUTABLE OUTPUT: $1-------------------------------------\n"
    ./$SOURCE_DIR/$PJC_EXEC_DIR/$1
    echo -e "\n----------------------------------------------------------------------------------------------------------"
    rm $SOURCE_DIR/*.o 2> /dev/null

    if [ $# -ge 2 ]
    then
        mkdir $SOURCE_DIR/$FPC_EXEC_DIR 2> /dev/null
        fpc $SOURCE_DIR/$1.pas -FE$SOURCE_DIR/$FPC_EXEC_DIR > /dev/null
        echo -e "\n\n-------------------------------------FPC EXECUTABLE OUTPUT: $1-------------------------------------\n"
        ./$SOURCE_DIR/$FPC_EXEC_DIR/$1
        echo -e "\n----------------------------------------------------------------------------------------------------------"
        rm $SOURCE_DIR/$FPC_EXEC_DIR/*.o 2> /dev/null
    fi
else
    exit
fi

exit
