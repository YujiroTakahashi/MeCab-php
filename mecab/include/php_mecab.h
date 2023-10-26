#ifndef PHP_MECAB_H
#define PHP_MECAB_H

#include <mecab.h>

#define PHP_MECAB_VERSION    "0.2.0"

extern zend_module_entry mecab_module_entry;
#define phpext_mecab_grn_ptr &mecab_module_entry

#endif  /* PHP_MECAB_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */