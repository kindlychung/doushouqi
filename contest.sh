#!/bin/sh
## *******************************************************************
##   (C) Copyright 2014 Leiden Institute of Advanced Computer Science
##   Universiteit Leiden
##   All Rights Reserved
## *******************************************************************
## Open Dag 21 maart 2014 --- King of the Jungle
## *******************************************************************
## FILE INFORMATION:
##   File:     contest.sh
##   Author:   Jonathan K. Vis
##   Revision: 0.01a
##   Date:     2014/03/18
## *******************************************************************
## DESCRIPTION:
##   Allows for engines to play each other.
## *******************************************************************

if [ ! -p ./channel.fifo ];
then
  mkfifo ./channel.fifo
fi
if [ -f ./moves_white.log ];
then
  rm ./moves_white.log
fi
if [ -f ./moves_black.log ];
then
  rm ./moves_black.log
fi

(awk '/^black/ { print $2; fflush(); }' | tee -a ./moves_black.log | $1) < ./channel.fifo | \
awk '/^white/ { print $2; fflush(); }' | tee -a ./moves_white.log | $2 > ./channel.fifo

paste -d '\n' ./moves_white.log ./moves_black.log

if [ -p ./channel.fifo ];
then
  rm ./channel.fifo
fi
if [ -f ./moves_white.log ];
then
  rm ./moves_white.log
fi
if [ -f ./moves_black.log ];
then
  rm ./moves_black.log
fi

