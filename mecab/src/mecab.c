#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "ext/spl/spl_exceptions.h"
#include "ext/json/php_json.h"
#include "main/SAPI.h"

#include "zend_exceptions.h"
#include "zend_interfaces.h"
#include "SAPI.h"

#include "php_mecab.h"
#include "classes/mecab.php.h"

/* Handlers */
static zend_object_handlers mecab_php_object_handlers;

/* Class entries */
zend_class_entry *mecab_php_ce;

/* {{{ arginfo */
ZEND_BEGIN_ARG_INFO(arginfo_mecab_void, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mecab_php_ctor, 0, 0, 1)
    ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_mecab_str, 0, 0, 1)
    ZEND_ARG_INFO(0, str)
ZEND_END_ARG_INFO()
/* }}} */

/* {{{ mecab_php_class_methods */
static zend_function_entry mecab_php_class_methods[] = {
    PHP_ME(mecab_php_class, __construct, arginfo_mecab_php_ctor, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(mecab_php_class, __destruct,  arginfo_mecab_void,     ZEND_ACC_PUBLIC)
    PHP_ME(mecab_php_class, parse,       arginfo_mecab_str,      ZEND_ACC_PUBLIC)
    PHP_ME(mecab_php_class, wakati,      arginfo_mecab_str,      ZEND_ACC_PUBLIC)
    PHP_ME(mecab_php_class, yomi,        arginfo_mecab_str,      ZEND_ACC_PUBLIC)
    PHP_ME(mecab_php_class, tagger,      arginfo_mecab_str,      ZEND_ACC_PUBLIC)

    PHP_FE_END
};
/* }}} */

static void mecab_php_object_free_storage(zend_object *object) /* {{{ */
{
    mecab_php_object *intern = mecab_php_from_obj(object);
    if (!intern) {
        return;
    }
    zend_object_std_dtor(&intern->zo);
}
/* }}} */

static zend_object *mecab_php_object_new(zend_class_entry *class_type) /* {{{ */
{
    mecab_php_object *intern;

    intern = ecalloc(1, sizeof(mecab_php_object) + zend_object_properties_size(class_type));
    zend_object_std_init(&intern->zo, class_type);
    object_properties_init(&intern->zo, class_type);
    intern->zo.handlers = &mecab_php_object_handlers;

    return &intern->zo;
}
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
*/
PHP_MINIT_FUNCTION(mecab)
{
    zend_class_entry ce;

    /* Register Mecab Class */
    memcpy(&mecab_php_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    INIT_CLASS_ENTRY(ce, "Mecab", mecab_php_class_methods);
    ce.create_object = mecab_php_object_new;
    mecab_php_object_handlers.offset = XtOffsetOf(mecab_php_object, zo);
    mecab_php_object_handlers.clone_obj = NULL;
    mecab_php_object_handlers.free_obj = mecab_php_object_free_storage;
    mecab_php_ce = zend_register_internal_class(&ce);

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
*/
PHP_MSHUTDOWN_FUNCTION(mecab)
{
    UNREGISTER_INI_ENTRIES();

    return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
*/
PHP_MINFO_FUNCTION(mecab)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "Mecab-PHP support", "enabled");
    php_info_print_table_row(2, "Mecab-PHP module version", PHP_MECAB_VERSION);
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ mecab_module_entry
*/
zend_module_entry mecab_module_entry = {
    STANDARD_MODULE_HEADER,
    "mecab",
    NULL,
    PHP_MINIT(mecab),
    PHP_MSHUTDOWN(mecab),
    NULL,
    NULL,
    PHP_MINFO(mecab),
    PHP_MECAB_VERSION,
    STANDARD_MODULE_PROPERTIES
};
/* }}} */


#ifdef COMPILE_DL_MECAB
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(mecab)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */