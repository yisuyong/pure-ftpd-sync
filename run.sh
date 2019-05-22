#!/bin/bash
kill -9 `ps -ef |grep pure-ftpd|awk '{print $2}'`
/usr/local/pureftpd/pure-ftpd --bind x.x.x.x,21 --limitrecursion 5000:500 -c 50 --createhomedir  --noanonymous --chrooteveryone --dontresolve --daemonize --verboselog -l mysql:/usr/local/pureftpd/pureftpd-mysql.conf
