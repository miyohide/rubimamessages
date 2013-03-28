= mruby ヒッチハイクガイド

今回は (今回も) 時間がないので、 最近ひそかにリリースされつつある (正式リリースではないそうなのであいまいな表現にしてみるが) mruby のコードを読解するためのメモをそのまま流用したい。

 * @<href>{http://github.com/mruby/mruby}

Ruby 処理系のコードの読み方と言えば、青木峰郎さんの名著、Ruby Hacking Guide こと『Ruby ソースコード完全解説』があるので、それに倣って書いてみる。ただし、言うまでもないが、全部書くのは紙面も時間も私自身のコード読解力もないため、第 2 章「オブジェクト」の前半の部分に相当するくらいである。興味のある方は、以下のページも合わせて読んでみるとよいだろう。

 * @<href>{http://i.loveruby.net/ja/rhg/book/object.html}

また、書く内容も「解説」というより「鑑賞」に近い。むしろガイドブック片手に眺めるくらいの気持ちが似合っている。そんなわけで「mruby ハッキングガイド」などとは名乗らず、このタイトルにしてみた。別に人類や Rubyist が滅びるわけではない。

なお、以下ではいわゆる MRI というか、普通の CRuby 処理系のソースコードを ruby と呼び、mruby と区別する。

== 値とオブジェクト

それではさっそく RHG を片手に mruby を読んでみよう。

ruby の値は VALUE という型であり、実際にはこれを即値として扱うか、オブジェクトを表す構造体へのポインタとして扱っていた。


//emlist[(include/ruby/ruby.h)]{
 typedef uintptr_t VALUE;
//}

一方、mruby のそれは大きく異なる。

//emlist[(include/mruby.h)]{
typedef struct mrb_value {
  union {
    mrb_float f;
    void *p;
    mrb_int i;
    mrb_sym sym;
  } value;
  enum mrb_vtype tt:8;
} mrb_value;
//}

VALUE はなくなり、代わりに用意されているのがこの mrb_value だ。 float と void * と int とシンボルとを union でまとめている。

これはつまり、ruby ではトリッキーに埋め込まれた一部の即値以外は VALUE のポインタの先を見て値を取り出すようになっていたのが、mruby では mrb_value のみで素直に値を表せるようになった、ということだ。比較的大きな変更ではないだろうか。特に浮動小数点演算の影響が大きそうだ。……と思ったが、よくよく考えてみると変わったのは浮動小数点数くらいのような気もする。そこまで大きな変更ではないかもしれない。

もちろん、union だけではそれが整数なのか小数なのか、 それとも全く別のオブジェクト(へのポインタ)なのか分からない。ruby では ポインタの先にある値で区別していたが、mruby でそれをしてしまうと 値を持っている意味がなくなる。そのために追加されたのが mrb_vtype だろう。 mrb_vtype の定義は以下のようになる。

//emlist[(include/mruby.h)]{
enum mrb_vtype {
  MRB_TT_FALSE = 0,   /*   0 */
  MRB_TT_FREE,        /*   1 */
  MRB_TT_TRUE,        /*   2 */
  MRB_TT_FIXNUM,      /*   3 */
  MRB_TT_SYMBOL,      /*   4 */
  MRB_TT_UNDEF,       /*   5 */
  MRB_TT_FLOAT,       /*   6 */
  MRB_TT_OBJECT,      /*   7 */
  MRB_TT_CLASS,       /*   8 */
  MRB_TT_MODULE,      /*   9 */
  MRB_TT_ICLASS,      /*  10 */
  MRB_TT_SCLASS,      /*  11 */
  MRB_TT_PROC,        /*  12 */
  MRB_TT_ARRAY,       /*  13 */
  MRB_TT_HASH,        /*  14 */
  MRB_TT_STRING,      /*  15 */
  MRB_TT_RANGE,       /*  16 */
  MRB_TT_REGEX,       /*  17 */
  MRB_TT_STRUCT,      /*  18 */
  MRB_TT_EXCEPTION,   /*  19 */
  MRB_TT_MATCH,       /*  20 */
  MRB_TT_FILE,        /*  21 */
  MRB_TT_ENV,         /*  22 */
  MRB_TT_DATA,        /*  23 */
  MRB_TT_THREAD,      /*  24 */
  MRB_TT_THREADGRP,   /*  25 */
  MRB_TT_MAXDEFINE    /*  26 */
};
//}

この mrb_vtype により、例えば float についても mrb_value のみで値が取得できるようになっている。

なお、mrb_float が何かは mrbconf.h で定義できるようになっている。

//emlist[(include/mrbconf.h)]{
#undef MRB_USE_FLOAT

#ifdef MRB_USE_FLOAT
typedef float mrb_float;
#else
typedef double mrb_float;
#endif
//}

通常は double だが、MRB_USE_FLOAT を #define すれば float になる。 これは省メモリ環境でも動作させるための配慮だと思われる。

一方、mrb_int と mrb_sym は決め打ちになっている。

//emlist[(include/mrbconf.h)]{
typedef int mrb_int;
typedef intptr_t mrb_sym;
//}

概ね予想通りの定義ではないだろうか。

== オブジェクト構造体

引き続き RHG に従って mruby を読んでいこう。

VALUE が mrb_value に変わったところから、オブジェクト構造体も気になる。 こちらはどうなっているだろうか。

ruby の場合、オブジェクト構造体は include/ruby/ruby.h にあったが、mruby では各ヘッダファイルに分かれている。

//emlist[(include/mruby/object.h)]{
struct RObject {
  MRUBY_OBJECT_HEADER;
  struct kh_iv *iv;
};

struct RString {
  MRUBY_OBJECT_HEADER;
  int len;
  union {
    int capa;
    struct RString *shared;
  } aux;
  char *buf;
};

struct RArray {
  MRUBY_OBJECT_HEADER;
  size_t len;
  size_t capa;
  mrb_value *buf;
};
//}

ぱっと見たところでは、こちらは ruby のそれとあまり変わっていない。むしろだいぶシンプルになった感覚がある。少し安心する。

MRUBY_OBJECT_HEADER は気になるが、きっと ruby での RBasic のような、 各オブジェクトに共通する要素をまとめたものだろう、と想像はつく。 中身は以下のようになっている。

//emlist[(include/mruby/object.h)]{
#define MRUBY_OBJECT_HEADER \
  enum mrb_vtype tt:8; \
  int color:3;\
  unsigned int flags:21;\
  struct RClass *c;\
  struct RBasic *gcnext
//}

c はそのオブジェクトのクラスだろう。RHG にもある通り、mrb_vtype だけでは すべてのクラスが表現できないため、別途 RClass 型の変数 c が使われている。

このクラスと flags は ruby とも共通するが、それ以外にも情報が増えている。 何となく GC に関連するような気がするが、ここでは深入りしない。

なお、mruby での RBasic は以下のようになっている。

//emlist[(include/mruby/object.h)]{
struct RBasic {
  MRUBY_OBJECT_HEADER;
};
//}

推測通りだっただろうか。

== 基本的なオブジェクト

ruby ではいくつかのオブジェクトはポインタではなく、値が埋め込まれていた。

//emlist[(ruby/ruby.h)]{
enum ruby_special_consts {
    RUBY_Qfalse = 0,
    RUBY_Qtrue  = 2,
    RUBY_Qnil   = 4,
    RUBY_Qundef = 6,
(略)
};

#define Qfalse ((VALUE)RUBY_Qfalse)
#define Qtrue  ((VALUE)RUBY_Qtrue)
#define Qnil   ((VALUE)RUBY_Qnil)
#define Qundef ((VALUE)RUBY_Qundef)     /* undefined value for placeholder */
//}

この辺り、mruby ではどうなっているだろうか。

//emlist[(include/mruby.h)]{
static inline mrb_value
mrb_false_value()
{
  mrb_value v;

  v.tt = MRB_TT_FALSE;
  v.value.i = 1;
  return v;
}
//}

なんと static インライン関数になっている。

C のインライン関数は C99 で標準に取り込まれた、らしい。mruby はその特徴として、 C99 準拠がうたわれている。そのため、C99 の機能は遠慮なく使っているのだろう。

もっとも、C99 の inline はヒントであって最適化やそのほかのコンパイラの都合によりインライン化されないこともあり……という話はよく知らないので深入りしないでおく。

mruby に戻る。mrb_false_value() は見ての通り、型情報として MRB_TT_FALSE を持ち、 値としては 1 を持つ mrb_value を返している。

MRB_TT_FLASE は Ruby の false だけではない。nil の時にも使われる。mrb_nil_value() はこうだ。

//emlist[(include/mruby.h)]{
static inline mrb_value
mrb_nil_value()
{
  mrb_value v;

  v.tt = MRB_TT_FALSE;
  v.value.p = 0;
  return v;
}
//}

こちらはポインタとして 0 を与えている。なぜ v.value.i ではないのかは分からなかった。

ちなみに nil かどうかを調べるマクロは以下のようになっている。

//emlist[(include/mruby.h)]{
#define mrb_nil_p(o)  ((o).tt == MRB_TT_FALSE && !(o).value.i)
//}

同様に、真偽値を返す mrb_test() はこうなる。

//emlist[(include/mruby.h)]{
#define mrb_test(o)   ((o).tt != MRB_TT_FALSE)
//}

つまり、MRB_TT_FALSE は false かどうかではなく、Ruby の「偽」の値を表すものだと考えればよいようだ。

ついでなので、true と undef を返す mrb_true_value() と mrb_undef_value() も紹介しておく。

//emlist[(include/mruby.h)]{
static inline mrb_value
mrb_true_value()
{
  mrb_value v;

  v.tt = MRB_TT_TRUE;
  v.value.i = 1;
  return v;
}

static inline mrb_value
mrb_undef_value()
{
  mrb_value v;

  v.tt = MRB_TT_UNDEF;
  v.value.i = 0;
  return v;
}
//}

同じような形になっている。

== メソッド

続いてクラスを見てみよう。mruby のクラスの構造体も、ruby 同様 RClass になっている。

//emlist[(include/mruby/class.h)]{
struct RClass {
  MRUBY_OBJECT_HEADER;
  struct kh_iv *iv;
  struct kh_mt *mt;
  struct RClass *super;
};
//}

ruby そっくりだ。iv がインスタンス変数、mt がメソッドテーブルだと推測できる。

メソッド探索は mrb_method_search() になる。

//emlist{
struct RProc*
mrb_method_search(mrb_state *mrb, struct RClass* c, mrb_sym mid)
{
  struct RProc *m;

  m = mrb_method_search_vm(mrb, &c, mid);
  if (!m) {
    mrb_raise(mrb, E_NOMETHOD_ERROR, "no method named %s\n", mrb_sym2name(mrb, mid));
  }
  return m;
}
//}

これを見る限り、どうやら mrb_method_search_vm が本体のようだ。こちらはこうなっている。

//emlist{
struct RProc*
mrb_method_search_vm(mrb_state *mrb, struct RClass **cp, mrb_sym mid)
{
  khiter_t k;
  struct RProc *m;
  struct RClass *c = *cp;

  while (c) {
    khash_t(mt) *h = c->mt;

    if (h) {
      k = kh_get(mt, h, mid);
      if (k != kh_end(h)) {
        m = kh_value(h, k);
        if (!m) break;
        *cp = c;
        return m;
      }
    }
    c = c->super;
  }
  return 0;                  /* no method */
}
//}

kh_ で始まるものはハッシュの操作になっている。中身は include/khash.h に詳しいが、ここでは触れないでおく。

OOPL のメソッド探索の挙動に親しみがあるのなら、おおまかな挙動もだいたい推測がつくかもしれない。 各クラスが持つメソッドテーブル c->mt に対し、 メソッドの ID である mid があればその値 (m) を返し、なければクラスをさかのぼり、 見つからなければ 0 を返す。ちょっと kh_ 関連のクセはあるが、 やっていることはふつうのメソッド探索である。

なお、この第一引数である mrb_state というのは、mruby のインタプリタの本体というか、 その状態を持っている値である。定義は長いが以下のようになっている。

//emlist[(include/mruby.h)]{
typedef struct mrb_state {
  void *jmp;

  mrb_allocf allocf;

  mrb_value *stack;
  mrb_value *stbase, *stend;

  mrb_callinfo *ci;
  mrb_callinfo *cibase, *ciend;

  mrb_code **rescue;
  int rsize;
  struct RProc **ensure;
  int esize;

  struct RObject *exc;
  struct kh_iv *globals;

  struct mrb_irep **irep;
  size_t irep_len, irep_capa;

  struct RClass *object_class;
  struct RClass *class_class;
  struct RClass *module_class;
  struct RClass *proc_class;
  struct RClass *string_class;
  struct RClass *array_class;
  struct RClass *hash_class;

  struct RClass *float_class;
  struct RClass *fixnum_class;
  struct RClass *true_class;
  struct RClass *false_class;
  struct RClass *nil_class;
  struct RClass *symbol_class;

  struct RClass *kernel_module;
  struct heap_page *heaps;
  struct heap_page *sweeps;
  struct heap_page *free_heaps;
  size_t live; /* count of live objects */
  struct RBasic *arena[MRB_ARENA_SIZE];
  int arena_idx;

  enum gc_state gc_state; /* state of gc */
  int current_white_part; /* make white object by white_part */
  struct RBasic *gray_list; /* list of gray objects */
  struct RBasic *variable_gray_list; /* list of objects to be traversed atomically */
  size_t gc_live_after_mark;
  size_t gc_threshold;
  mrb_int gc_interval_ratio;
  mrb_int gc_step_ratio;

  mrb_sym symidx;
  struct kh_n2s *name2sym;      /* symbol table */
  struct kh_s2n *sym2name;      /* reverse symbol table */
#ifdef INCLUDE_REGEXP
  struct RNode *local_svar;/* regexp */
#endif

  struct RClass *eException_class;
  struct RClass *eStandardError_class;
  struct RClass *eRuntimeError_class;
} mrb_state;
//}

長いと書いたが本当に長い。というか object_class や class_class など、 普通の意味では state ではないものも含んでる。

いずれにしても、確かにこれくらいあれば、ruby の実行状態を表すために必要な情報は全て含まれていそうだ。

以下、mrb_state の解説をするか、変数周りについての解説をするか、というところだが、 すでに長くなってしまったので（そして私自身もまだ理解できていないので）今回はここまでにする。 なんとなく、mruby の雰囲気はつかめただろうか。

CRuby 1.9 のソースに比べれば、全体的にシンプルになっているような気がする。Ruby 処理系の実装に興味があるのなら、CRuby （や JRuby、rubinious） もさることながら、mruby のソースを読んでみるのもおすすめしたい。