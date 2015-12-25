#!/bin/bash
echo -e "\n redis-server process status: \n"
ps -ef | grep redis-server | grep -v grep
echo -e "\n choose redis:"
echo -e "\n\t 1) redis-cli -h 127.0.0.1 -p 6379"
echo -e "\n\t 2) redis-cli -h 127.0.0.1 -p 6380 \n"
read -p " input 1/2 :  " need noneed
echo -e "\n\t start $need"

if [ $need == "1" ]; then
	cd $HOME/release/redis
	echo -e "\n\t redis-cli -h 127.0.0.1 -p 6379 \n"
	redis-cli -h 127.0.0.1 -p 6379
fi

if [ $need == "2" ]; then
	cd $HOME/release/redis
	echo -e "\n\t redis-cli -h 127.0.0.1 -p 6380 \n"
	redis-cli -h 127.0.0.1 -p 6380
fi
