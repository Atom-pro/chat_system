#!/bin/bash

ROOT_PATH=$(pwd)
conf=$ROOT_PATH/conf/server.conf
server=$ROOT_PATH/udpServer


_proc=$(basename $0)
function usage(){
    printf "Usage: %s [-s(start) | -t(stop) | -rt(restart)]\n" "$_proc"
}

function serverStart()
{
    name=$(basename $server)
    if `pidof $name>>/dev/null`;then
        echo "server is already running!" #>>$log
    else
        port=$(awk -F: '/^PORT/{print $NF}' $conf)
        ip=$(awk -F: '/^IP/{print $NF}' $conf)
        $server $ip $port
    fi
}

function serverStop()
{
    name=$(basename $server) 
    pid=$(pidof $name)
    if [ $? -eq 0 ]; then
        kill -9 $pid
    else
        echo "server is not running" #>>$log
    fi
}

function serverRestart()
{
    serverStop
    serverStart
}

if [ $# -ne 1 ];then
    usage;
    exit 1;
fi

case $1 in
    -s | start )
        serverStart
    ;;
    -t | stop )
        serverStop
    ;;
    -rt | restart )
        serverRestart
    ;;
    * )
        usage
        exit 1
esac
