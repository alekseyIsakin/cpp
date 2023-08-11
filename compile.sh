#!/bin/bash

path=`readlink -e "${BASH_SOURCE:-$0}"`
TOP_DIRECTION=`dirname $path`
cd "$TOP_DIRECTION"

SHORT=c:,b:,B:,h
LONG=--clear:,--congigure-cmake:,--only-build:,--help
OPTS=$(getopt -a -n cmake_script --options $SHORT -- "$@")

eval set -- "$OPTS"

help(){
    echo "usage: compile  [-c | --clear]
                [-B | --congigure-cmake]
                [-b | --only-build]
                [-h | --help]
                            "
    exit 2
}

configure_cmake(){
    if [[ $1 -eq 1 ]] || [[ $1 -eq 0 ]] 
    then
        cd "$TOP_DIRECTION"
        mkdir -p app1/app1_build
        cd app1/app1_build
        cmake ../source
    fi
    if [[ $1 -eq 2 ]] || [[ $1 -eq 0 ]] 
    then
        cd "$TOP_DIRECTION"
        mkdir -p app2/app2_build
        cd app2/app2_build
        cmake ../source
    fi
}

compile(){
        if [[ $1 -eq 1 ]] || [[ $1 -eq 0 ]] 
    then
        cd $TOP_DIRECTION/app1/app1_build
        cmake --build .
    fi
    if [[ $1 -eq 2 ]] || [[ $1 -eq 0 ]] 
    then
        cd $TOP_DIRECTION/app2/app2_build
        cmake --build .
    fi
}

clear(){
    if [[ $1 -eq 1 ]] || [[ $1 -eq 0 ]] 
    then
        cd "$TOP_DIRECTION"
        rm app1/app1_build -fr
    fi
    if [[ $1 -eq 2 ]] || [[ $1 -eq 0 ]] 
    then
        cd "$TOP_DIRECTION"
        rm app2/app2_build -fr
    fi
}

while :
do
    case "$1" in 
        -c)
            clear $2
            exit 0
            ;;
        -B | --congigure-cmake)
            configure_cmake $2
            shift 2
            ;;
        -b | --only-build)
            compile
            cmake --build .
            shift 2
            ;;
        -h | --help)
            help
            ;;
        --)
            shift;
            break
            ;;
        *)
            echo "Unexpected option: $1"
            help
            ;;
    esac
done
