#########################################################################
# File Name: easy_make.sh
# Author: Yibo Lin
# mail: yibolin@utexas.edu
# Created Time: Wed 30 Sep 2015 10:43:55 AM CDT
#########################################################################
#!/bin/bash

# the source code or makefile maybe modified for specific usage 

function fmake {
    # make single threaded Csdp, but multiple threading safe on higher level 
    make
}

function fclean {
    make clean
}

function fextraclean {
    fclean
}

if [[ $# -ne 1 ]]; then 
    echo "$0: usage: source script < make | install | clean | extraclean >"
    return
fi

cmd="$1"

if [[ $cmd == "make" ]]; then 
    fmake 
elif [[ $cmd == "install" ]]; then 
    fmake 
    fclean
elif [[ $cmd == "clean" ]]; then 
    fclean 
elif [[ $cmd == "extraclean" ]]; then 
    fextraclean
else 
    echo "Error: unknown command $cmd"
fi

