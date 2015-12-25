#!/bin/bash
echo -e "\n redis-server redis_upload.conf & \n"
cd $HOME/release/redis
mkdir log
mkdir dump
redis-server redis_upload.conf &