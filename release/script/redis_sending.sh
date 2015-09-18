#!/bin/bash
echo -e "\n redis-server redis_sending.conf & \n"
cd ../redis/
redis-server redis_sending.conf &