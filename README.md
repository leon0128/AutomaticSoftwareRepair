# Automatic Software Repair README.md

## 実行方法

`./asr <修正対象ソースコード> [オプション]`

## テストケース

|引数|説明|
|:--|:--|
|$0|スクリプトファイル名|
|$1|テストケース識別子|
|$2|実行ファイル名|
|$3|利用可能な一時ファイル名(テストケース実行後に削除)|

テストケース例:

```
#! /usr/bin/bash

case $1 in
    p0) $2;; #ポジティブテストケース1回目の実行
    n0) $2;; #ネガティブテストケース1回目の実行
    n1) $2;; #ネガティブテストケース2回目の実行
esac
```

## オプション

|オプション|説明|初期値|
|:--|:--|:--:|
|--help|ヘルプの表示(未実装)|-|
|--version|バージョン情報の表示(未実装)|-|
|--target <string>|修正する関数の設定<br>指定した関数が一つも見つからない場合、全ての関数が修正対象となる。|""|
|--pool <string>|利用する外部ソースコードの設定(未設定の場合のみ修正対象のソースコードが利用される)|""|
|--result <string>|修正結果ファイルの出力ファイル名|"test/result.c"|
|--command-log|サブプロセスのコマンドログの表示|-|
|--time-log|実行時間の表示|-|
|--repair-log|修正ログの表示|-|
|--subprocess-log|サブプロセスの実行結果の表示|-|
|--analyze-log|解析状況の表示|-|
|--similarity-log|類似度のlogの表示|-|
|--specified-log|自由に変更可能な実験用のログの表示(ソースコードに直接書き込む)|-|
|--no-ignore-pool|解析に失敗した外部ソースコードを無視しない(プログラムが終了する)|-|
|--no-divide-for|for文の宣言を分割しない|-|
|--preprocessor <string>|プリプロセッサコマンドの設定|"cpp -P -I./test/ -D__extension__="|
|--compiler <string>|コンパイラコマンドの設定|"gcc"|
|--builtin <string>|ビルトイン識別子の定義用ファイル|"builtin.h"|
|--test <string>|テスト用のスクリプトファイルの設定|"test/testcase.sh"|
|--exec-extension <string>|実行形式ファイルの拡張子の設定("")<br>Windowsの場合は".exe"を指定すること|""|
|--null-filename <string>|Nullファイルの指定<br>Windowsの場合は、"NUL"を設定すること|"/dev/null"|
|--pos-prefix <string>|ポジティブテストケースのプレフィックスの指定|"p"|
|--neg-prefix <string>|ネガティブテストケースのプレフィックスの指定|"n"|
|--num-pos <unsigned int>|ポジティブテストケースの数の指定|1|
|--num-neg <unsigned int>|ネガティブテストケースの数の指定|1|
|--pos-weight <int>|ポジティブテストケースの重みの指定|1|
|--neg-weight <int>|ネガティブテストケースの重みの指定|10|
|--goal <int>|テストケースの目標スコアの指定|11|
|--failure <unsigned int>|ソースコード生成の失敗数上限の指定|256|
|--use-control-flow|__break__, __continue__, __case__ などを変更に使用|-|
|--create-same-op|同一の変更操作の生成を許可|-|
|--same-op-failure <unsigned int>|同一操作作成の制限回数|10000|
|--num-first-op <unsigned int>|事前に生成する操作数|10000|
|--random-identifier|文の追加/置換処理の際に、識別子を無作為に変換<br>`--random-identifier`, `--duplicated-identifier`, `--no-duplicated-identifier`のいずれも選択しない場合、`--no-duplicated-identifier`を利用|-|
|--duplicated-identifier|文の追加/置換処理の際に、同一の識別子を同一の識別子に変換<br>`--random-identifier`, `--duplicated-identifier`, `--no-duplicated-identifier`のいずれも選択しない場合、`--no-duplicated-identifier`を利用|-|
|--no-duplicated-identifier|文の追加/置換処理の際に、同一の識別子を同一の識別子に変換<br>重複なし<br>`--random-identifier`, `--duplicated-identifier`, `--no-duplicated-identifier`のいずれも選択しない場合、`--no-duplicated-identifier`を利用|-|
|--pop <unsigned int>|1世代あたりのソースコード生成数の指定|1000|
|--gen <unsigned int>|世代数の指定|10|
|--elite <unsigned int>|次世代に持ち越すスコアの高いソースコードの数の指定|2|
|--tournament <unsigned int>|次世代に持ち越すソースコードの候補数の指定|3|
|--add-prob <double>|ソースコード修正時の文の追加操作発生確率|0.2|
|--sub-prob <double>|ソースコード修正時の文の削除操作発生確率|0.2|
|--swap-prob <double>|ソースコード修正時の文の置換操作発生確率|0.6|
|--new-creation-prob <double>|第2世代以降において、新たなソースコードが生成される確率|0.2|
|--num-concurrency <unsigned int>|同時実行数|16|
|--max-recursion <unsigned int>|型の比較において、再帰型の比較深度|16|
|--no-use-similarity|類似度の使用しない|-|
|--original <unsigned int>|類似度算出におけるオリジナル表現のグラム数|1|
|--type1 <unsigned int>|類似度算出におけるType1表現のグラム数|4|
|--type2 <unsigned int>|類似度算出におけるType2表現のグラム数|4|
|--type3 <unsigned int>|類似度算出におけるType3表現のグラム数|4|
|--capacity <double>|類似度算出におけるクエリの削減率|1.0|
|--num-use-external <unsigned int>|類似度使用時における外部ソースコード利用数|32,768|
|--no-change-prob|類似度使用時における外部ソースコードの選択確率の変更の禁止|-|
|--use-proportion|類似度使用時における外部ソースコードの選択確率を類似度の比率で計算|-|