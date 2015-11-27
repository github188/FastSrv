#!/bin/sh
. /etc/profile
. ~/.bash_profile

PROCESS=`ps -u $USER | grep upload|grep -v run_upload|grep -v grep|grep -v PPID|awk '{ print $1}'`
for i in $PROCESS
do
  echo "Kill process : name = upload, pid = $i"
  kill -9 $i
done
echo "cd $HOME/code/bin"
cd $HOME/code/bin
echo "$HOME/code/bin/upload -r 6379 -d coglink2/coglink2013@CLORCL -l $HOME/code/log/upload.log &"
$HOME/code/bin/upload -r 6379 -d coglink2/coglink2013@CLORCL -l $HOME/code/log/upload.log &