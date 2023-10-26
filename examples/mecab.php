<?php

$mecab = new \MeCab('/var/lib/mecab/dic/ipadic-utf8');
$res = $mecab->parse('すもももももももものうち');
echo $res;
echo "\n";