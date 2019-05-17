#!/bin/bash
kill -9 `ps -ef |grep pure-ftpd|awk '{print $2}'`
#./src/pure-ftpd --bind ip,21 --createhomedir  --noanonymous --chrooteveryone --dontresolve --daemonize --verboselog -l mysql:/root/pureftpd-mysql.conf
./src/pure-ftpd --bind 59.15.94.144,21 --limitrecursion 5000:500 -c 50 --createhomedir  --noanonymous --chrooteveryone --dontresolve --daemonize --verboselog -l mysql:/root/pureftpd-mysql.conf
