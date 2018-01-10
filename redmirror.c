/*
 * Copyright (c) 2018 Job Snijders <job@openbsd.org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <kcgi.h>
#include <libmemcached/memcached.h>

int main(void) {
	int mc = 0;
	int mi;
	struct kreq req;
	struct kfcgi *fcgi;
	static const char filename[] = "/htdocs/index.txt";
	const char *page = "index";
	char mirrors[100][BUFSIZ];
	FILE *fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "failed to open %s", filename);
		exit(1);
	}

	while(fgets(mirrors[mc], sizeof(mirrors[0]), fp)) {
		mirrors[mc][strlen(mirrors[mc]) - 1] = '\0';
		mc++;
	}

	fclose(fp);

	if (KCGI_OK != khttp_fcgi_init(&fcgi, NULL, 0, &page, 1, 0))
		return(EXIT_FAILURE);

	while (KCGI_OK == khttp_fcgi_parse(fcgi, &req)) {
		khttp_head(&req, kresps[KRESP_STATUS],
		    "%s", khttps[KHTTP_302]);
		mi = arc4random_uniform(mc);
		khttp_head(&req, kresps[KRESP_LOCATION],
		    "%s%s", mirrors[mi], req.fullpath);
		khttp_body(&req);
		khttp_free(&req);
	}

	khttp_fcgi_free(fcgi);
	return(EXIT_SUCCESS);
}
