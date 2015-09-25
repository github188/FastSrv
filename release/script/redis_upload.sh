#!/bin/bash
echo -e "\n redis-server redis_upload.conf & \n"
cd ../redis/
mkdir log
mkdir dump
redis-server redis_upload.conf &