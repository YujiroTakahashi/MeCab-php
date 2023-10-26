#ifndef PHP_CLASSES_MECAB_PHP_H
#define PHP_CLASSES_MECAB_PHP_H

#include <string.h>
#include <stdint.h>

#ifdef __cplusplus

#include <iostream>
#include <string>
#include <vector>
#include <mecab.h>

extern "C" {

#include "php.h"
#include "php_ini.h"
#include "main/SAPI.h"

#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "Zend/zend_smart_str.h"
#include "ext/json/php_json.h"
#include "ext/standard/php_http.h"
#include "ext/standard/url.h"
#include "SAPI.h"
#include "php_mecab.h"

#endif /* __cplusplus */

typedef void *TaggerHandle;

typedef struct _mecab_php_object {
    TaggerHandle tagger;
    zend_object zo;
} mecab_php_object;

static inline mecab_php_object *mecab_php_from_obj(zend_object *obj) {
    return (mecab_php_object*)((char*)(obj) - XtOffsetOf(mecab_php_object, zo));
}

#define Z_MECAB_PHP_P(zv) mecab_php_from_obj(Z_OBJ_P((zv)))


PHP_METHOD(mecab_php_class, __construct);
PHP_METHOD(mecab_php_class, __destruct);
PHP_METHOD(mecab_php_class, parse);
PHP_METHOD(mecab_php_class, wakati);
PHP_METHOD(mecab_php_class, yomi);
PHP_METHOD(mecab_php_class, tagger);

#ifdef __cplusplus
}   // extern "C"
#endif /* __cplusplus */

#endif /* PHP_CLASSES_MECAB_PHP_H */