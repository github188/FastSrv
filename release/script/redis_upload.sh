#!/bin/bash
echo -e "\n redis-server redis_upload.conf & \n"
cd ../redis/
redis-server redis_upload.conf &