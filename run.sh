#!/bin/bash
#--with-debug            For maintainers only - please do not use
./configure \
 --with-virtualhosts --with-welcomemsg --with-ftpwho --with-quotas \
 --with-peruserlimits --with-ratios --with-throttling --with-cookie \
 --with-virtualchroot --without-ascii --with-altlog \
 --with-diraliases --with-uploadscript --with-extauth --with-puredb \
 --with-tls --with-language=english \
 --with-mysql --with-everything \
 --with-debug 


#default 
#./src/pure-ftpd --bind 21 --createhomedir  --noanonymous --chrooteveryone --dontresolve -l mysql:/suyong1/devel/ftp/pure-ftpd-1.0.49-sync-1.0/pureftpd-mysql.conf
