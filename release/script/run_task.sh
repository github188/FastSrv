#!/bin/sh
. /etc/profile
. ~/.bash_profile

PROCESS=`ps -u $USER | grep task|grep -v run_task|grep -v grep|grep -v PPID|awk '{ print $1}'`
for i in $PROCESS
do
  echo "Kill process : name = task, pid = $i"
  kill -9 $i
done
echo "cd $HOME/code/bin"
cd $HOME/code/bin
echo "$HOME/code/bin/task -a 220.248.44.218 -h 21000 -i 30 -p 22001 -r 6379 -s 6380 -d coglink2/coglink2013@CLORCL -l $HOME/code/log/task.log &"
$HOME/code/bin/task -a 220.248.44.218 -h 21000 -i 30 -p 22001 -r 6379 -s 6380 -d coglink2/coglink2013@CLORCL -l $HOME/code/log/task.log &