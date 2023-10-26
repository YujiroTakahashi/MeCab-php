Mecabクライアント
======================
PHP8 bindings for MeCab.

---

## 目次

* [利用方法](#install)
* [Docker環境実行](#docker)
* [MeCabクラス](#class00)


## <a name="install">利用方法

### MeCabライブラリのインストール ###
```    
$ sudo apt -y install libmecab2
```

### mecab-phpのインストール ###
```    
$ git clone https://github.com/YujiroTakahashi/mecab.git
$ cd ./mecab
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_BUILD_TYPE=Release
$ make -j
$ sudo -s
# make install
# cd /etc/php/8.3/mods-available
# echo extension=mecab.so > mecab.ini
# cd /etc/php/8.3/fpm/conf.d
# ln -s /etc/php/8.3/mods-available/mecab.ini ./30-mecab.ini
```

## <a name="docker">Docker環境実行
```
docker-compose build
docker-compose run shell php /opt/examples/mecab.php
```

## <a name="class00">クラス  

* [Mecab::__construct](#class10)― コンストラクタGroongaの初期化など
* [Mecab::parse](#class20) ― 形態素解析：：Dump
* [Mecab::wakati](#class30) ― 分かち書き
* [Mecab::yomi](#class40) ― 分かち書き読み
* [Mecab::tagger](#class50) ― 形態素解析：：配列

## <a name="class10"> コンストラクタMecabの初期化など

```php
public Proonga::__construct(string $path)
```
  
**引数**
  
* $path ・・・・・・ 辞書の保存先

---

## <a name="class20"> 形態素解析：：Dump

```php
public Proonga::parse(string $str): string
```
  
**引数**
  
* $str ・・・・・・ 解析対象の文字列


```php
<?php

/* オブジェクト生成 */
$mecab = new \Mecab('/var/lib/mecab/dic/unidic');
$res = $mecab->parse('すもももももももものうち');
echo $res;
```
```
すもも	名詞,普通名詞,一般,*,*,*,スモモ,李,すもも,スモモ,すもも,スモモ,和,*,*,*,*,*,*,体,スモモ,スモモ,スモモ,スモモ,0,C2,*,15660352771596800,56972
も	助詞,係助詞,*,*,*,*,モ,も,も,モ,も,モ,和,*,*,*,*,*,*,係助,モ,モ,モ,モ,*,"動詞%F2@-1,形容詞%F4@-2,名詞%F1",*,10324972564259328,37562
もも	名詞,普通名詞,一般,*,*,*,モモ,桃,もも,モモ,もも,モモ,和,*,*,*,*,*,*,体,モモ,モモ,モモ,モモ,0,C3,*,10425303000293888,37927
も	助詞,係助詞,*,*,*,*,モ,も,も,モ,も,モ,和,*,*,*,*,*,*,係助,モ,モ,モ,モ,*,"動詞%F2@-1,形容詞%F4@-2,名詞%F1",*,10324972564259328,37562
もも	名詞,普通名詞,一般,*,*,*,モモ,桃,もも,モモ,もも,モモ,和,*,*,*,*,*,*,体,モモ,モモ,モモ,モモ,0,C3,*,10425303000293888,37927
の	助詞,格助詞,*,*,*,*,ノ,の,の,ノ,の,ノ,和,*,*,*,*,*,*,格助,ノ,ノ,ノ,ノ,*,名詞%F1,*,7968444268028416,28989
うち	名詞,普通名詞,副詞可能,*,*,*,ウチ,内,うち,ウチ,うち,ウチ,和,*,*,*,*,*,*,体,ウチ,ウチ,ウチ,ウチ,0,C3,*,881267193291264,3206
```

---

## <a name="class30"> 分かち書き

```php
public Proonga::wakati(string $str): array
```
  
**引数**
  
* $str ・・・・・・ 解析対象の文字列


```php
<?php

/* オブジェクト生成 */
$mecab = new \Mecab('/var/lib/mecab/dic/unidic');
$res = $mecab->wakati('すもももももももものうち');
print_r($res);
```
```
Array
(
    [0] => すもも
    [1] => も
    [2] => もも
    [3] => も
    [4] => もも
    [5] => の
    [6] => うち
)
```

---

## <a name="class40"> 分かち書き：：読み

```php
public Proonga::yomi(string $str): array
```
  
**引数**
  
* $str ・・・・・・ 解析対象の文字列


```php
<?php

/* オブジェクト生成 */
$mecab = new \Mecab('/var/lib/mecab/dic/ipadic-utf8');
$res = $mecab->yomi('すもももももももものうち');
print_r($res);
```
```
Array
(
    [0] => Array
        (
            [surface] => すもも
            [kana] => スモモ
            [oto] => スモモ
        )

    [1] => Array
        (
            [surface] => も
            [kana] => モ
            [oto] => モ
        )

    [2] => Array
        (
            [surface] => もも
            [kana] => モモ
            [oto] => モモ
        )

    [3] => Array
        (
            [surface] => も
            [kana] => モ
            [oto] => モ
        )

    [4] => Array
        (
            [surface] => もも
            [kana] => モモ
            [oto] => モモ
        )

    [5] => Array
        (
            [surface] => の
            [kana] => ノ
            [oto] => ノ
        )

    [6] => Array
        (
            [surface] => うち
            [kana] => ウチ
            [oto] => ウチ
        )

)
```

---

## <a name="class50"> 形態素解析：：配列

```php
public Proonga::tagger(string $str): array
```
  
**引数**
  
* $str ・・・・・・ 解析対象の文字列


```php
<?php

/* オブジェクト生成 */
$mecab = new \Mecab('/var/lib/mecab/dic/unidic');
$res = $mecab->tagger('すもももももももものうち');
print_r($res);
```
```
Array
(
    [0] => Array
        (
            [surface] => すもも
            [feature] => 名詞,一般,*,*,*,*,すもも,スモモ,スモモ
            [id] => 140075455585142
            [posid] => 38
            [char_type] => 6
            [stat] => 0
            [rcAttr] => 1285
            [lcAttr] => 1285
            [isbest] => 1
            [alpha] => 0
            [beta] => 0
            [prob] => 0
            [wcost] => 7546
            [cost] => 7263
        )

    [1] => Array
        (
            [surface] => も
            [feature] => 助詞,係助詞,*,*,*,*,も,モ,モ
            [id] => 140075478613968
            [posid] => 16
            [char_type] => 6
            [stat] => 0
            [rcAttr] => 262
            [lcAttr] => 262
            [isbest] => 1
            [alpha] => 0
            [beta] => 0
            [prob] => 0
            [wcost] => 4669
            [cost] => 7774
        )

    [2] => Array
        (
            [surface] => もも
            [feature] => 名詞,一般,*,*,*,*,もも,モモ,モモ
            [id] => 140075456772088
            [posid] => 38
            [char_type] => 6
            [stat] => 0
            [rcAttr] => 1285
            [lcAttr] => 1285
            [isbest] => 1
            [alpha] => 0
            [beta] => 0
            [prob] => 0
            [wcost] => 7219
            [cost] => 15010
        )

    [3] => Array
        (
            [surface] => も
            [feature] => 助詞,係助詞,*,*,*,*,も,モ,モ
            [id] => 140075478613968
            [posid] => 16
            [char_type] => 6
            [stat] => 0
            [rcAttr] => 262
            [lcAttr] => 262
            [isbest] => 1
            [alpha] => 0
            [beta] => 0
            [prob] => 0
            [wcost] => 4669
            [cost] => 15521
        )

    [4] => Array
        (
            [surface] => もも
            [feature] => 名詞,一般,*,*,*,*,もも,モモ,モモ
            [id] => 140075456772088
            [posid] => 38
            [char_type] => 6
            [stat] => 0
            [rcAttr] => 1285
            [lcAttr] => 1285
            [isbest] => 1
            [alpha] => 0
            [beta] => 0
            [prob] => 0
            [wcost] => 7219
            [cost] => 22757
        )

    [5] => Array
        (
            [surface] => の
            [feature] => 助詞,連体化,*,*,*,*,の,ノ,ノ
            [id] => 140075478613449
            [posid] => 24
            [char_type] => 6
            [stat] => 0
            [rcAttr] => 368
            [lcAttr] => 368
            [isbest] => 1
            [alpha] => 0
            [beta] => 0
            [prob] => 0
            [wcost] => 4816
            [cost] => 23131
        )

    [6] => Array
        (
            [surface] => うち
            [feature] => 名詞,非自立,副詞可能,*,*,*,うち,ウチ,ウチ
            [id] => 140075461839492
            [posid] => 66
            [char_type] => 6
            [stat] => 0
            [rcAttr] => 1313
            [lcAttr] => 1313
            [isbest] => 1
            [alpha] => 0
            [beta] => 0
            [prob] => 0
            [wcost] => 5796
            [cost] => 23729
        )
)
```


    

ライセンス
----------
Copyright &copy; 2014 Yujiro Takahashi  
Licensed under the [MIT License][MIT].  
Distributed under the [MIT License][MIT].  

[MIT]: http://www.opensource.org/licenses/mit-license.php
