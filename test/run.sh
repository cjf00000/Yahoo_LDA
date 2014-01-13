#!/bin/bash
set -u

#server=10.1.1.245:10099

cat $HOME/data/nytimes.dat.human | ../bin/formatter

#../DM_Server \
#    1 \
#    0 \
#    1 \
#    $server \
#    --Ice.ThreadPool.Server.SizeMax=9 &
#sleep 3

#../learntopics \
#    --topics=100 \
#    --iter=100 \
#    --servers=$server \
#    --optimizestats=200 \
#    --printloglikelihood=1 \
#    --chkptdir="." \
#    --chkptinterval=100000 \
#    --alpha=100 \
#    --beta=0.01

killall DM_Server learntopics
