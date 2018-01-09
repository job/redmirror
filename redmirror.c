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

#include <sys/types.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <kcgi.h>


int main(void) {
	struct kreq req;
	struct kfcgi *fcgi;
	const char *page = "index";

	if (KCGI_OK != khttp_fcgi_init(&fcgi, NULL, 0, &page, 1, 0))
		return(EXIT_FAILURE);

	while (KCGI_OK == khttp_fcgi_parse(fcgi, &req)) {
		khttp_head(&req, kresps[KRESP_STATUS],
		    "%s derp", khttps[KHTTP_302]);
		khttp_free(&req);
	}

	khttp_fcgi_free(fcgi);
	return(EXIT_SUCCESS);
}

