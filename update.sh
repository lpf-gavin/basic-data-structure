#!/bin/sh
cd 'dirname $0'
git add *
git commit -m 'update by update.sh'
git push -u origin master
