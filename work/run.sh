#!/bin/bash
set -u

#cat $HOME/data/nytimes.human | ../bin/formatter

#server=localhost:10123
#
#../bin/DM_Server \
#    1 \
#    0 \
#    1 \
#    $server \
#    --Ice.ThreadPool.Server.SizeMax=9 &
#sleep 3
#    --servers=$server \

../bin/learntopics \
    --topics=100 \
    --iter=100 \
    --optimizestats=200 \
    --printloglikelihood=1 \
    --chkptdir="." \
    --chkptinterval=100000 \
    --alpha=100 \
    --beta=0.01


./teardown.sh
