#!/bin/sh
. /etc/profile
. ~/.bash_profile

PROCESS=`ps -u $USER | grep balance|grep -v run_balance|grep -v grep|grep -v PPID|awk '{ print $1}'`
for i in $PROCESS
do
  echo "Kill process : name = balance, pid = $i"
  kill -9 $i
done
echo "cd $HOME/code/bin"
cd $HOME/code/bin
echo "$HOME/code/bin/balance -h 21000 -p 22000 -r 6379 -d coglink2/coglink2013@CLORCL -l $HOME/code/log/balance.log &"
$HOME/code/bin/balance -h 21000 -p 22000 -r 6379 -d coglink2/coglink2013@CLORCL -l $HOME/code/log/balance.log &