DrawMathGraph
====

実行ファイル  
[32bit](https://raw.githubusercontent.com/ugonight/DrawMathGraph/master/x86.zip)  
[64bit](https://raw.githubusercontent.com/ugonight/DrawMathGraph/master/x64.zip)  

## Description

グラフ理論用のグラフを描くツールです！  
最終的には色んなアルゴリズムを適用できるようなプログラムにしたいです！  

## Demo

![demo](https://github.com/ugonight/DrawMathGraph/blob/master/demo.gif)

## Requirement

DXライブラリ 山田　巧 様  
<http://dxlib.o.oo7.jp/>  

## Usage

### アプリケーションの使い方

右クリックで「鉛筆」→「矢印」→「消しゴム」とカーソルを変えられます。  
- 鉛筆  
  - 何もないところをクリックすると点を作成します  
  - 点からドラッグして別の点の上でドロップすると辺を作成できます  
- 矢印  
  - 点を移動することができます。  
  - 辺の上でドラッグすることで辺の方向点を設定できます。  
  - 左上の情報表示領域をダブルクリックすると文字入力モードになり、点や辺に値を付与できます。  
  - Runボタンを押すと定義された処理を実行できます。
- 消しゴム  
  - 点や辺を消せます  

その他の機能  
- Ctrl+Pキー
  - 画面をpngファイルで保存します。（アプリ下の階層にファイルが生成されます）

### 独自の関数を定義して使用する場合

1. プロジェクト一式をダウンロードします。  
    - `git clone https://github.com/ugonight/DrawMathGraph.git`
1. DrawMathGraph.slnを開きDxLibの設定をします。  
    - DXライブラリの使い方のページ(http://dxlib.o.oo7.jp/dxuse.html)
1. myProcess.cppを編集します。  
    - 使える関数などは[wikiページ](https://github.com/ugonight/DrawMathGraph/wiki)をご覧ください。
1. 実行します。  

## Licence

著作権を侵害するような行為以外はご自由にお使いください  
二次配布（改変したものも含む）などの場合は事前にご連絡ください  

## Author

[ugonight](https://github.com/ugonight)
 - twitter:[@ugonight_nanase](https://twitter.com/ugonight_nanase)  