#!/bin/bash

path=`readlink -e "${BASH_SOURCE:-$0}"`
TOP_DIRECTION=`dirname $path`
cd "$TOP_DIRECTION"

PATH_APP1=app1/
PATH_APP2=app1/
BUILD_TYPE=debug #[ debug | release ]

SHORT=c:,b:,B:,h
LONG=--clear:,--congigure-cmake:,--only-build:,--help
OPTS=$(getopt -a -n cmake_script --options $SHORT -- "$@")

eval set -- "$OPTS"

help(){
    echo "usage: compile  [-c | --clear] [0 | 1 | 2]
                [-B | --congigure-cmake] [0 | 1 | 2]
                [-b | --only-build] [0 | 1 | 2]
                [-h | --help]
1 - for app1
2 - for app2
0 - for both"
    exit 2
}

configure_cmake(){
    if [[ $1 -eq 1 ]] || [[ $1 -eq 0 ]] 
    then
        cd "$TOP_DIRECTION"
        mkdir -p app1/app1_build_$BUILD_TYPE
        cd app1/app1_build_$BUILD_TYPE
        cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../source
    fi
    if [[ $1 -eq 2 ]] || [[ $1 -eq 0 ]] 
    then
        cd "$TOP_DIRECTION"
        mkdir -p app2/app2_build_$BUILD_TYPE
        cd app2/app2_build_$BUILD_TYPE
        cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../source
    fi
}

compile(){
    if [[ $1 -eq 1 ]] || [[ $1 -eq 0 ]] 
    then
        cd $TOP_DIRECTION/app1/app1_build_$BUILD_TYPE
        cmake --build .
    fi
    if [[ $1 -eq 2 ]] || [[ $1 -eq 0 ]] 
    then
        cd $TOP_DIRECTION/app2/app2_build_$BUILD_TYPE
        cmake --build .
    fi
}

clear(){
    if [[ $1 -eq 1 ]] || [[ $1 -eq 0 ]] 
    then
        cd "$TOP_DIRECTION"
        rm app1/app1_build* -fr
    fi
    if [[ $1 -eq 2 ]] || [[ $1 -eq 0 ]] 
    then
        cd "$TOP_DIRECTION"
        rm app2/app2_build* -fr
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
            compile $2
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
