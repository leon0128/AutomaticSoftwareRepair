# Automatic Software Repair

## 実行方法

`./asr <修正対象ソースコード> [オプション]`

## オプション

|オプション|説明|
|:--|:--|
|--help|ヘルプの表示|
|--version|バージョン情報の表示|
|--target <string>|修正する関数の設定|
|--pool <string>|利用する外部ソースコードの設定(未設定の場合のみ修正対象のソースコードが利用される)|
|--result <string>|修正結果ファイルの出力ファイル名("result.c")|
|--command-log|サブプロセスのコマンドログの表示|
|--time-log|実行時間の表示|
|--repair-log|修正ログの表示|
|--subprocess-log|サブプロセスの実行結果の表示|
|--preprocessor <string>|プリプロセッサコマンドの設定("cpp -P")|
|--compiler <string>|コンパイラコマンドの設定("gcc")|
|--test <string>|テスト用のスクリプトファイルの設定("test.sh")|
|--exec-extension <string>|実行形式ファイルの拡張子の設定("")<br>Windowsの場合は".exe"を指定すること|
|--null-filename <string>|Nullファイルの指定|
|--pos-prefix <string>|ポジティブテストケースのプレフィックスの指定|
|--neg-prefix <string>|ネガティブテストケースのプレフィックスの指定|
|--num-pos <unsigned int>|ポジティブテストケースの数の指定|
|--num-neg <unsigned int>|ネガティブテストケースの数の指定|
|--pos-weight <int>|ポジティブテストケースの重みの指定|
|--neg-weight <int>|ネガティブテストケースの重みの指定|
|--goal <int>|テストケースの目標スコアの指定|
|--failure <unsigned int>|ソースコード生成の失敗数上限の指定|
|--pop <unsigned int>|1世代あたりのソースコード生成数の指定|
|--gen <unsigned int>|世代数の指定|
|--elite <unsigned int>|次世代に持ち越すスコアの高いソースコードの数の指定|
|--tournament <unsigned int>|次世代に持ち越すソースコードの候補数の指定|
|--add-prob <double>|ソースコード修正時の文の追加操作発生確率|
|--sub-prob <double>|ソースコード修正時の文の削除操作発生確率|
|--swap-prob <double>|ソースコード修正時の文の置換操作発生確率|
|--new-creation-prob <double>|第2世代以降において、新たなソースコードが生成される確率|
|--num-concurrency <unsigned int>|同時実行数|
|--max-recursion <unsigned int>|型の比較において、再帰型の比較深度|
|--use-similarity|類似度の使用|
|--original <unsigned int>|類似度算出におけるオリジナル表現のグラム数|
|--type1 <unsigned int>|類似度算出におけるType1表現のグラム数|
|--type2 <unsigned int>|類似度算出におけるType2表現のグラム数|
|--type3 <unsigned int>|類似度算出におけるType3表現のグラム数|
|--capacity <unsigned int>|類似度算出におけるクエリの削減率|
|--num-use-external <unsigned int>|類似度使用時における外部ソースコード利用数|
|--change-prog|類似度使用時における外部ソースコードの選択隔離の変更|