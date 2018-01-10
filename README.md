redmirror: Redirection to mirrors
=================================

Simple tool to randomly distribute http requests across a number of mirrors
using 302 redirects. This tool depends on `kcgi`.

`/etc/httpd.conf` example config:

```
server "default" {
        listen on 127.0.0.1 port 80
        location "/pub/OpenBSD/*" {
                root strip 2
                fastcgi socket "/run/httpd.sock"
                root "/"
        }
}
```

Copy the `redmirror` binary to `/var/www/cgi-bin/redmirror`.

Run `kfcgi` like:

`kfcgi -v -U www -u www -- /cgi-bin/redmirror`

Put a list of mirrors that can be used in `/var/www/htdocs/index.txt`:

```
$ cat /var/www/htdocs/index.txt
https://fastly.cdn.openbsd.org/pub/OpenBSD
https://cloudflare.cdn.openbsd.org/pub/OpenBSD
https://mirror.leaseweb.com/pub/OpenBSD
```

You can now observe that requests are being distributed randomly:

```
$ for i in $(jot 300); do ftp -Mvo /dev/zero https://cdn.openbsd.org/pub/OpenBSD/README \
    | grep Requesting | awk '{ print $NF }' | paste - -; done | sort | uniq -c
90 https://cdn.openbsd.org/pub/OpenBSD/README https://cloudflare.cdn.openbsd.org/pub/OpenBSD/README
109 https://cdn.openbsd.org/pub/OpenBSD/README https://fastly.cdn.openbsd.org/pub/OpenBSD/README
101 https://cdn.openbsd.org/pub/OpenBSD/README https://mirror.leaseweb.com/pub/OpenBSD/README
```
