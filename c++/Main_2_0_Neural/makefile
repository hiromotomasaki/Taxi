# http://web.stanford.edu/class/cs193d/handouts/make.pdf コンパイルチュートリアル
# http://www.jsk.t.u-tokyo.ac.jp/~k-okada/makefile/ makefileチュートリアル
# http://www.ibe.kagoshima-u.ac.jp/edu/gengo0/exe1/p3.html 実行ファイル作成手順
# http://www.ie.u-ryukyu.ac.jp/~e085739/c.makefile.tuts.html 内部マクロ
# http://quruli.ivory.ne.jp/document/make_3.79.1/make-jp_2.html#Reading-Makefiles 変数の割り当て
# http://quruli.ivory.ne.jp/document/make_3.79.1/make-jp_5.html#Setting 変数の割り当てわかりやすい
# http://postd.cc/7-things-you-should-know-about-make/ 変数の割り当てこっちもわかりやすい
# http://www.ecoop.net/coop/translated/GNUMake3.77/make_toc.jp.html makefile 書くならこれを見る

# オブジェクトファイル hoge.o の作り方
# 依存関係なし
# g++ -c hoge.cpp
# オプションを色々つける場合
# hoge.cppにincludeされているヘッダーのうち, 自分で作成したもの, 環境変数で指定していないもののディレクトリを「-I /path/to/dir」の形で書く.
# またコンパイルのオプションも必要であれば書く
# g++ -c hoge.cpp -std=c++11 -I /usr/local/lib/lpsolve
# 

# 実行ファイル a.out の作り方
# g++ -o a.out -L /usr/local/lib/lpsolve/ main.o minus.o plus.o -llpsolve55
# のように ライブラリパス, 実行ファイル生成に関連するオブジェクトファイル, 使用するライブラリを書く

# ======================================================================= #
#                             ユーザー設定項目                            #
# ======================================================================= #

# ---------- プロジェクトフォルダ内のサブディレクトリの設定 ----------- #

# ******************************* 説明 ****************************** #
# 例えば 「*.cppファイルの保存先のディレクトリ」を「./Hoge」にしたい場合は
# 「SOURCE_DIR := ./Hoge」
# とする.
# 「*.cppファイルの保存先のディレクトリ」を「makefileと同じディレクトリ（makefileはプロジェクトのrootディレクトリである）」にしたい場合は
# 「SOURCE_DIR := 」
# とする.
# ******************************************************************* #

# *.cppファイルの保存先のディレクトリ
SOURCE_DIR := ./Source
# *.hファイルの保存先のディレクトリ
INCLUDE_DIR := ./Include
# コンパイルにより作成されたオブジェクトファイル(*.o)や依存関係ファイル(*.d)の保存先のディレクトリ
OBJECT_DIR := ./Object
# 実行ファイルの保存先のディレクトリ
BIN_DIR := ./Bin

# --------------------------------------------------------------------- #

# ---------- コンパイルから実行ファイル作成過程で必要な設定 ----------- #
# 使用するコンパイラ
COMPILER := g++
# BIN_DIRに作成される実行ファイル(main.out, outはなくても構わない)
PROGRAM := main.out
# コンパイル時に環境変数に登録されていないディレクトリにあるヘッダーのディレクトリを書く
INCLUDE_PATH := -I ./Include -I /usr/src/Caffe/include -I /usr/src/boost/include
# コンパイル時のその他のオプション
COMPILE_OPTION := -MMD -MP -O2 -std=c++11 -Wall -Wextra -g -pedantic -Winit-self -Wpointer-arith -DCPU_ONLY
# ******************************* 説明 ****************************** #
# -MMD : システムヘッダディレクトリ以外のヘッダーを調べコンパイルし*.dに依存関係を保存する
# -MP : 依存するヘッダファイルを偽のターゲットとして追加する。
# -O2 : 最適化レベル
# -std=c++11 : 対象ソースが C++11 準拠としてコンパイルする
# -Wall : 基本的な警告オプションを on にする 
# -Wextra : 追加の警告オプションを on にする
# -g : デバッグ情報を生成
# -pedantic : ISO C/C++ に存在しない文法を警告する
# -Winit-self : int i = i; など未定義の変数が自分を初期化すると警告るす
# -Wpointer-arith : 疑わしいポインター計算に対して警告を発行するかどうかを指定します。
# ******************************************************************* #
# リンク時に環境変数に登録されていないディレクトリにあるライブラリのディレクトリを書く.
# リンクするライブラリは「-l」で指定する.
# 1.静的(libfoo.so), 2.動的(libfoo.a)の順でLIBRARY_PATHからサーチされる
# 動的リンクは実行ファイルを実行するときに, 静的リンクはリンクを貼るときにリンクされる.
# 前者のほうがファイルサイズが少なくて済む
LIBRARY_PATH := -L /usr/src/Caffe/build/lib -L /usr/src/boost/lib
# リンク時に使用するライブラリを書く.
# このライブラリは環境変数またはLIBRARY_PATHから見えるところにある.
LIBRARY := -lboost_system -lboost_filesystem -lboost_date_time -lcaffe -lglog
# --------------------------------------------------------------------- #

# ======================================================================= #


# ディレクトリの文字列に空白文字が含まれていた場合, stripで空白文字ではなく空の文字と変形する. そして, これを第二引数の空の文字と比較をして一致していれば中に進む.
ifeq ($(strip $(SOURCE_DIR)), )
  SOURCE_DIR = .
endif
ifeq ($(strip $(INCLUDE_DIR)), )
  INCLUDE_DIR = .
endif
ifeq ($(strip $(OBJECT_DIR)), )
  OBJECT_DIR = .
endif
ifeq ($(strip $(BIN_DIR)), )
  BIN_DIR  = .
endif

# SOURCE_DIR 内の*.cppの文字列集合を取得
SOURCES = $(wildcard $(SOURCE_DIR)/*.cpp)
# OBJECT_DIR 内にある実行ファイル生成時にリンクされるオブジェクトファイル(*.o)
OBJECTS = $(addprefix $(OBJECT_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
# OBJECT_DIR 内にある各ファイルをコンパイルするときのヘッダーの依存関係を記したファイル(*.d)
DEPENDS = $(OBJECTS:.o=.d)
# BIN_DIR 内にある実行ファイル
BIN = $(addprefix $(BIN_DIR)/, $(PROGRAM))

############################################# 
 # メモ
 # subst : 置換動作
 # patsubst : 置換動作，ワイルドカードあり
 # strip : 空白文字の削除
 # findstring : 文字列を探す
 # filter : 一致する単語の削除
 # filter-out : 一致しない単語の削除
 # sort : ソートする
 # dir : ディレクトリ部分の抽出
 # nodir : ファイル部分の抽出
 # suffix : サフィックス（拡張子）部分
 # basename : サフィックス以外
 # addsuffix : サフィックスを加える
 # addprefix : プレフィックスを加える
 # join : 単語の連結
 # word : n番目の単語を返す
 # worldlist : 単語のリストを返す
 # words : 単語数を返す
 # firstword : 最初の名前を返す
 # wildcard : ワイルドカードによりファイル名リストを返す
 # foreach : 引数を複数回展開する

# ターゲット:依存するファイル
# 	コマンド

 # $@ : ターゲットファイル名
 # $% : ターゲットがアーカイブメンバだったときのターゲットメンバ名
 # $< : 最初の依存するファイルの名前
 # $? : ターゲットより新しいすべての依存するファイル名
 # $^ : すべての依存するファイルの名前
 # $+ : Makefileと同じ順番の依存するファイルの名前
 # $* : サフィックスを除いたターゲットの名前
############################################# 

# $(BIN): $(OBJECTS) $(LIBRARY)
# 	$(COMPILER) -o $@ $(LIBRARY_PATH) $^
$(BIN): $(OBJECTS)
	-mkdir -p $(BIN_DIR)
	$(COMPILER) -o $@ $^ $(LIBRARY_PATH) $(LIBRARY)
# -o $@ : 実行ファイル名の指定
# $^ : 実行ファイルの生成に必要なオブジェクトファイルの指定
# $(LIBRARY_PATH) : 使用するライブラリのパスの指定
# 指定されたパスから使用するライブラリ$(LIBRARY)の指定
$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	-mkdir -p $(OBJECT_DIR)
	$(COMPILER) -c $< -o $@ $(COMPILE_OPTION) $(INCLUDE_PATH)
# -c $< : 生成するオブジェクトの材料となるソースファイルの指定
# -o $@ : 生成するオブジェクト名の指定
# $(COMPILE_OPTION) : コンパイルのオプション
# $(INCLUDE_PATH) : ソースファイルの中で使われているヘッダーがあるパスの指定

-include $(DEPENDS)
# コンパイル時に依存関係を見て必要なソースを再コンパイルするのに必要

all: clean $(BIN)

.PHONY: clean
clean:
	-rm -f $(OBJECTS) $(DEPENDS) $(BIN)
# -mkdir -p : -pは指定したディレクトリをサブディレクトリごと作成するオプションmkdirに「-」が付いているのはすでに作成されていた場合に警告を無視するため


