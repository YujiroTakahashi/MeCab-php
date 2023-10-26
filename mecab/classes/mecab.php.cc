#include "mecab.php.h"

/* {{{ proto std::vector<std::string> _explode(const std::string str, const char delimiter)
 */
std::vector<std::string> _explode(const std::string str, const char delimiter)
{
    std::vector<std::string> result;

    size_t pos = str.find(delimiter);
    size_t last = 0;

    while (pos != std::string::npos) {
        size_t size = pos - last;
        result.push_back(str.substr(last, size));

        last = pos + 1;
        pos = str.find(delimiter, pos + 1);
    } // while (pos != std::string::npos)

    if (str.length() > last) {
        result.push_back(str.substr(last));
    }

    return result;
}

/* {{{ proto void mecab::__construct()
 */
PHP_METHOD(mecab_php_class, __construct)
{
    mecab_php_object *mecab_obj = Z_MECAB_PHP_P(ZEND_THIS);
    char *dictionary;
    size_t dictionary_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(dictionary, dictionary_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    if (!dictionary_len) {
        zend_throw_exception(NULL, "Dictionary path is empty.", 0);
        return ;
    }

    std::string dicpath(dictionary);
    std::string option("-d" + dicpath); 
    MeCab::Tagger *tagger = MeCab::createTagger(option.c_str());
    mecab_obj->tagger = static_cast<TaggerHandle>(tagger);
}
/* }}} */

/* {{{ proto void mecab::__destruct()
 */
PHP_METHOD(mecab_php_class, __destruct)
{
    mecab_php_object *mecab_obj = Z_MECAB_PHP_P(ZEND_THIS);

    if (zend_parse_parameters_none() == FAILURE) {
        return;
    }

    if (nullptr != mecab_obj->tagger) {
        delete static_cast<MeCab::Tagger*>(mecab_obj->tagger);
        mecab_obj->tagger = nullptr;
    }
}
/* }}} */

/* {{{ proto string mecab::parse(string str)
 */
PHP_METHOD(mecab_php_class, parse)
{
    mecab_php_object *mecab_obj = Z_MECAB_PHP_P(ZEND_THIS);
    char *str;
    size_t str_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, str_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    MeCab::Tagger *tagger = static_cast<MeCab::Tagger*>(mecab_obj->tagger);
    const MeCab::Node* node = tagger->parseToNode(str);
    std::string parsed("");
    for (; node; node = node->next) {
        if (node->stat != MECAB_BOS_NODE && node->stat != MECAB_EOS_NODE) {
            std::string surface(node->surface, 0, node->length);
            parsed.append(surface);
            parsed.append("\t");
            parsed.append(node->feature);
            parsed.append("\n");
        }
    } // for (; node; node = node->next)
    RETURN_STRINGL(parsed.c_str(), parsed.length());
}
/* }}} */

/* {{{ proto array mecab::wakachi(string str)
 */
PHP_METHOD(mecab_php_class, wakati)
{
    mecab_php_object *mecab_obj = Z_MECAB_PHP_P(ZEND_THIS);
    char *str;
    size_t str_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, str_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    array_init(return_value);
    zend_ulong ridx = 0;
    MeCab::Tagger *tagger = static_cast<MeCab::Tagger*>(mecab_obj->tagger);
    const MeCab::Node* node = tagger->parseToNode(str);
    for (; node; node = node->next) {
        if (node->stat != MECAB_BOS_NODE && node->stat != MECAB_EOS_NODE) {
            zval surfaceVal;
            std::string surface(node->surface, 0, node->length);
            ZVAL_STRING(&surfaceVal, surface.c_str());
            add_index_zval(return_value, ridx, &surfaceVal);
            ridx++;
        }
    } // for (; node; node = node->next)
}
/* }}} */

/* {{{ proto array mecab::yomi(string str)
 */
PHP_METHOD(mecab_php_class, yomi)
{
    mecab_php_object *mecab_obj = Z_MECAB_PHP_P(ZEND_THIS);
    char *str;
    size_t str_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, str_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    array_init(return_value);
    zend_ulong ridx = 0;
    MeCab::Tagger *tagger = static_cast<MeCab::Tagger*>(mecab_obj->tagger);
    const MeCab::Node* node = tagger->parseToNode(str);
    for (; node; node = node->next) {
        if (node->stat != MECAB_BOS_NODE && node->stat != MECAB_EOS_NODE) {
            zval rowVals, surfaceVal, kanaVal, otoVal;

            array_init(&rowVals);

            std::string surface(node->surface, 0, node->length);
            ZVAL_STRING(&surfaceVal, surface.c_str());
            zend_hash_str_add(Z_ARRVAL(rowVals), "surface", sizeof("surface")-1, &surfaceVal);

            auto features = _explode(node->feature, ',');
            ZVAL_STRING(&kanaVal, features[features.size() -2].c_str());
            zend_hash_str_add(Z_ARRVAL(rowVals), "kana", sizeof("kana")-1, &kanaVal);

            ZVAL_STRING(&otoVal, features[features.size() -1].c_str());
            zend_hash_str_add(Z_ARRVAL(rowVals), "oto", sizeof("oto")-1, &otoVal);

            add_index_zval(return_value, ridx, &rowVals);
            ridx++;
        }
    } // for (; node; node = node->next)
}
/* }}} */


/* {{{ proto array mecab::tagger(string str)
 */
PHP_METHOD(mecab_php_class, tagger)
{
    mecab_php_object *mecab_obj = Z_MECAB_PHP_P(ZEND_THIS);
    char *str;
    size_t str_len;

    ZEND_PARSE_PARAMETERS_START(1, 1)
        Z_PARAM_STRING(str, str_len)
    ZEND_PARSE_PARAMETERS_END_EX(RETURN_FALSE);

    array_init(return_value);
    zend_ulong ridx = 0;
    MeCab::Tagger *tagger = static_cast<MeCab::Tagger*>(mecab_obj->tagger);
    const MeCab::Node* node = tagger->parseToNode(str);
    for (; node; node = node->next) {
        if (node->stat != MECAB_BOS_NODE && node->stat != MECAB_EOS_NODE) {
            zval rowVals, surfaceVal, featureVal, idVal, posIdVal, charTypeVal, statVal;
            zval rcAttrVal, lcAttrVal, isBestVal, alphaVal, betaVal, probVal, wcostVal, costVal;

            array_init(&rowVals);

            std::string surface(node->surface, 0, node->length);
            ZVAL_STRING(&surfaceVal, surface.c_str());
            zend_hash_str_add(Z_ARRVAL(rowVals), "surface", sizeof("surface")-1, &surfaceVal);

            ZVAL_STRING(&featureVal, node->feature);
            zend_hash_str_add(Z_ARRVAL(rowVals), "feature", sizeof("feature")-1, &featureVal);

            ZVAL_LONG(&idVal, (zend_long)node->feature);
            zend_hash_str_add(Z_ARRVAL(rowVals), "id", sizeof("id")-1, &idVal);

            ZVAL_LONG(&posIdVal, (zend_long)node->posid);
            zend_hash_str_add(Z_ARRVAL(rowVals), "posid", sizeof("posid")-1, &posIdVal);

            ZVAL_LONG(&charTypeVal, (zend_long)node->char_type);
            zend_hash_str_add(Z_ARRVAL(rowVals), "char_type", sizeof("char_type")-1, &charTypeVal);

            ZVAL_LONG(&statVal, (zend_long)node->stat);
            zend_hash_str_add(Z_ARRVAL(rowVals), "stat", sizeof("stat")-1, &statVal);

            ZVAL_LONG(&rcAttrVal, (zend_long)node->rcAttr);
            zend_hash_str_add(Z_ARRVAL(rowVals), "rcAttr", sizeof("rcAttr")-1, &rcAttrVal);

            ZVAL_LONG(&lcAttrVal, (zend_long)node->lcAttr);
            zend_hash_str_add(Z_ARRVAL(rowVals), "lcAttr", sizeof("lcAttr")-1, &lcAttrVal);

            ZVAL_LONG(&isBestVal, (zend_long)node->isbest);
            zend_hash_str_add(Z_ARRVAL(rowVals), "isbest", sizeof("isbest")-1, &isBestVal);

            ZVAL_DOUBLE(&alphaVal, node->alpha);
            zend_hash_str_add(Z_ARRVAL(rowVals), "alpha", sizeof("alpha")-1, &alphaVal);

            ZVAL_DOUBLE(&betaVal, node->beta);
            zend_hash_str_add(Z_ARRVAL(rowVals), "beta", sizeof("beta")-1, &betaVal);

            ZVAL_DOUBLE(&probVal, node->prob);
            zend_hash_str_add(Z_ARRVAL(rowVals), "prob", sizeof("prob")-1, &probVal);

            ZVAL_LONG(&wcostVal, (zend_long)node->wcost);
            zend_hash_str_add(Z_ARRVAL(rowVals), "wcost", sizeof("wcost")-1, &wcostVal);

            ZVAL_LONG(&costVal, (zend_long)node->cost);
            zend_hash_str_add(Z_ARRVAL(rowVals), "cost", sizeof("cost")-1, &costVal);

            add_index_zval(return_value, ridx, &rowVals);
            ridx++;
        }
    } // for (; node; node = node->next)
}
/* }}} */
