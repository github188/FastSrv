#!/bin/bash
echo -e "\n redis-server redis_sending.conf & \n"
cd ../redis/
mkdir log
mkdir dump
redis-server redis_sending.conf &