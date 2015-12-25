#!/bin/sh
PROCESS=`ps -u $USER | grep balance|grep -v run_balance|grep -v grep|grep -v PPID|awk '{ print $1}'`
for i in $PROCESS
do
  echo "Kill process : name = balance, pid = $i"
  kill -9 $i
done

PROCESS=`ps -u $USER | grep task|grep -v run_task|grep -v grep|grep -v PPID|awk '{ print $1}'`
for i in $PROCESS
do
  echo "Kill process : name = task, pid = $i"
  kill -9 $i
done

PROCESS=`ps -u $USER | grep upload|grep -v run_upload|grep -v grep|grep -v PPID|awk '{ print $1}'`
for i in $PROCESS
do
  echo "Kill process : name = upload, pid = $i"
  kill -9 $i
done

PROCESS=`ps -u $USER | grep sending|grep -v run_sending|grep -v grep|grep -v PPID|awk '{ print $1}'`
for i in $PROCESS
do
  echo "Kill process : name = sending, pid = $i"
  kill -9 $i
done