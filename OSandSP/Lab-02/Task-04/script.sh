#!/bin/bash

if [ -z $1 ]; then
    echo "Parameters not found!"
else
    dirpath=/proc/$1
    if [ ! -d "$dirpath" ]; then
        echo "pid = $1 process not found"
    else
        ppid=$(ps -q $1 -o ppid=)
        ppid=`echo $ppid | sed -e 's/ *$//g'`
        echo "Name: $(ps -q $1 -o comm=)"
        echo "Pid:  ${1}"
        echo "PPid: ${ppid}"
        if [ ! -z $2 ]; then
            for fd in $(ls /proc/$1/fd); do
                echo "fd = $fd"
            done
        fi
    fi
fi
