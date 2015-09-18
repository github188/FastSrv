#!/bin/bash
echo -e "\n redis-server redis_upload_raw.conf & \n"
cd ../redis/
redis-server redis_upload_raw.conf &