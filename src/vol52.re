= Rubyレポジトリの変遷について

RubyKaigi 2015に先立ち、先日、Ruby Conference 2015 が開催された。
これは毎年アメリカで開催されているカンファレンスで、
まつもとさんによるキーノートと質疑応答が目玉の一つとなっているのだが、
その質疑応答にはなぜか「定番の質問」というのがある。
「Ruby にマクロは入らないのか」とか「メインのリポジトリを git(and/or github) にしないのか」といったものだ。

前者は（まつもとさんからは「No」という返答しか期待できないため）ほとんどネタにすぎないのだが、
後者はあまりネタではなく、それなりに切実な思いがあるのだろう。

そこで今回は、git 以前の話として、Ruby のメインリポジトリの変遷を振り返ってみたい。

== CVSの導入まで

Ruby が公開された当初、20年近く昔には、バージョン管理システムを使ったソフトウェアの配布というのはほとんど行われていなかった。
そんなんである程度以上の規模のソフトウェアをどうやって開発してたのか？
と思われるかもしれないが、私自身もどうやっていたのか不思議に思ったりする（よく覚えていない）。

CRuby も例にもれず、公開当初はレポジトリがなかった。
まつもとさんの手元では RCS 等が使われていたのかもしれない。
(初期のソースにも「$Author$」や「$Date$」が展開されている形跡は残っている)。

とはいえ、一人でメンテナンスしていたころはさておき、（当時流行の）オープンソースソフトウェアとして
外部からも盛んに協力を求めようとすると、何かしらの公開リポジトリが求められるようになった。
そこで、CVS が導入されることになる。

後述するが、CVS リポジトリは後に Subversion に変換されており、SVN レポジトリを掘ればCVS時代の commit が出てくる。
最初期の commit は以下の URL で見られる。

 * @<href>{http://svn.ruby-lang.org/cgi-bin/viewvc.cgi?limit_changes=0&view=revision&revision=2}

また、現在 github で公開されている git のリポジトリからも見ることができる。

コミットログは以下のようになっている。

//emlist[][]{
  commit 3db12e8b236ac8f88db8eb4690d10e4a3b8dbcd4
  Author: matz <matz@b2dd03c8-39d4-4d8f-98ff-823fe69b080e>
  Date:   Fri Jan 16 12:13:05 1998 +0000

  Initial revision
//}

1998 年ということは、Ruby のバージョン 1.1 の頃だ（詳しくは[[0022-ForeWord]]で触れている）。

とはいえ、コミットは随時記録されているが、これがこのまま公開されていたわけではなかった。
CVS についての話題は、随分とあとの 1999 年 3 月の ML に出ている([[ruby-dev:6376]])。

@<href>{http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-dev/6376}

//emlist[][]{
  Subject: [ruby-dev:6376] Open CVS (Re: Re: Ruby 1.3.1-990315)
  From: matz netlab.co.jp (Yukihiro Matsumoto)
  Date: Wed, 17 Mar 1999 02:05:58 +0900

  |CVSでバージョン管理してて、CVSで配布しないのは何か
  |わけあり？

  わけはですね，Open CVSの設定がまだうまくいってないからです．
  というか，全然作業にかかってない．だいたい私は新しいツールに
  順応するのが遅いので．

  マシン(cvs.netlab.co.jp)は用意したんですけどねえ．
//}

この後、まつもとさん以外の方からの協力もあり、1999 年の 4 月に CVS サーバの準備ができたようで、
CVS のアカウントを募集している([[ruby-dev:6667]])。

 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-dev/6667}

//emlist[][]{
  Subject: [ruby-dev:6667] Open CVS
  Date: Tue, 27 Apr 1999 10:52:28 +0900

  まつもと ゆきひろです

  Ruby CVSの書き込み権が欲しい人は

  cvsadmin / cvs.netlab.co.jp

  にメールして下さい．必要な情報は

  私は誰？
  アカウント名
  cryptされたパスワード

  です．
//}

申請すれば誰でもコミット権がもらえる、という牧歌的な時代だった。

とはいえ、その後も([[ruby-dev:8592]])などで「CVS難しい」とたびたび書いているので、あまり安定した運用だったわけではなかったようだった。

また、この頃はサーバの管理業務についてもまつもとさんが行っていたため（前田さんもある程度フォローしていたはず）、
他の人が見るに見かねて協力する、ということもあった。CVS サーバも例に漏れず、
細かいトラブルなどがあった後、knuさんが管理者に立候補したのが 2000 年の 12 月で([[ruby-dev:11876]])、
そこから翌年1月には CVSweb、CVSup、Anonymous CVS がそれぞれ整備された旨がアナウンスされた。

 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/vframe.rb/ruby/ruby-dev/12018?11919-12395}

//emlist[][]{
  Subject: [ruby-dev:12018] Ruby CVS repositories are ready now
  From: "Akinori MUSHA" <knu iDaemons.org>
  Date: Mon, 15 Jan 2001 05:18:46 +0900

  　どうも、お待たせしました。

  　Ruby の CVS レポジトリですが、最終的に配置が確定しました。
  CVSweb サイト

  http://www.ruby-lang.org/~knu/cgi-bin/cvsweb.cgi/

  でどんな感じか散歩できます。
//}

この時点では、cvsweb の CGI は knu さんの個人ディレクトリの下に置かれていたが、最終的にはwww.ruby-lang.org の直下に置かれることになる。

 * @<href>{https://www.ruby-lang.org/en/news/2002/01/06/ruby-cvs-repository-guide/}

ここからしばらく、CVSでの運用が続いた。

== CVS から Subversion へ

CVS からSubversion への移行については、
2005 年の 7 月に前田さんから送られたメールにて提案されている。

* @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-dev/26421}

//emlist[][]{
  Subject: [ruby-dev:26421] Subversion
  From: Shugo Maeda <shugo ruby-lang.org>
  Date: Fri, 1 Jul 2005 00:22:58 +0900


  前田です。
  # 同じ内容をruby-coreにもポストしています。

  現在Rubyの開発にはCVSが使われています。CVSはとても有用なソフトウェア
  ですが、いくつかの問題を抱えています。

  先日、lithium.ruby-lang.org(Rubyの開発用のホスト)がDebian sargeに
  アップグレードされましたが、sargeには公式なSubversionのパッケージ
  があります。
  そろそろ、Subversionへの移行を検討してはどうでしょうか。
//}

特に強い反対はなく、3 日後の 7 月 3 日には、実験的な SVN サーバが立てられ、速度の問題などが指摘されている。

 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-dev/26444}

//emlist[][]{
  Subject: [ruby-dev:26444] Re: Subversion
  From: Kouhei Sutou <kou cozmixng.org>
  Date: Sun, 3 Jul 2005 15:25:52 +0900

  > というわけで、CVS からの移行の前に、お試しで Subversion の
  > リポジトリも用意してもらえれば、議論もしやすいのではないか
  > と思います。

  用意してみました．

  http://www.cozmixng.org/repos/ruby-svn/

  一時的に作ってみたもので，しばらくしたら削除するつもりなので
  適当に実験してみてください．
//}

それでも最終的な移行までにはそれなりの時間がかかっている。
これには単なるレポジトリの移行作業以外に、1.9 開発ブランチの本格化や、
YARV のとりこみなどもこのタイミングで行われたせいもあるようだ。

 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/vframe.rb/ruby/ruby-dev/29964?29793-35143}

//emlist[][]{
  Subject: [ruby-dev:29964] 1.8, 1.9, svn化, などなどのまとめ
  From: "U.Nakamura" <usa garbagecollect.jp>
  Date: Tue, 28 Nov 2006 15:03:36 +0900
//}

最終的には 1 年半ほどたった 2006 年の年末、2006 年 12 月 20 日に CVS がフリーズされ、
翌日の 12 月 21 日に SVN がスタートする。

 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/vframe.rb/ruby/ruby-dev/30039?29793-35143}

//emlist[][]{
  Subject: [ruby-dev:30039] CVS freeze
  From: SASADA Koichi <ko1 atdot.net>
  Date: Wed, 20 Dec 2006 11:22:30 +0900
//}

 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/vframe.rb/ruby/ruby-dev/30039?29793-35143}

//emlist[][]{
  Subject: [ruby-dev:30043] SVN ready
  From: Shugo Maeda <shugo ruby-lang.org>
  Date: Thu, 21 Dec 2006 19:39:48 +0900
//}

そしてその翌日の 12 月 22 日、Subversion への移行が正式にアナウンスされる。

 * @<href>{https://www.ruby-lang.org/ja/news/2006/12/22/cvs-repository-moved-to-svn/}

なお、CVSサーバの方は翌2007年の3月16日に停止された。

 * @<href>{https://www.ruby-lang.org/ja/news/2007/03/01/cvs-services-will-be-permanently-unavailable/}

== githubでのミラー

そして git である。

前述のとおり、実は（というほどでもなくそれなりに有名なはずではあるが）Ruby のほぼ最新のソースは github から git で入手できる。

git を使いたいという話は、たびたびメーリングリストに出ている。少し探してみたところで、
2009 年 1 月と 2009 年 9 月に ruby-talk でスレッドができていた。

 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-core/21039}
 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-core/25285}

そこからしばらく（例によって）試験的な動きがあり、最終的には 2010 年 2 月 28 日に、 github.com/ruby/ruby が公式ミラーとして公開された。

 * @<href>{http://blade.nagaokaut.ac.jp/cgi-bin/scat.rb/ruby/ruby-core/28355}

//emlist[][]{
  Subject: [ruby-core:28355] [ANN] Toward rich diversity of Ruby development.
  From: Urabe Shyouhei <shyouhei ruby-lang.org>
  Date: Sun, 28 Feb 2010 01:35:35 +0900

  A short announcement: thanks to some helps of GitHub people, I now have
  http://github.com/ruby/ruby
//}

== 現在の議論

現在の主戦場、というと言葉は悪いかもしれないが（別に意見の深刻な対立があるわけではなく、単に議論の場という意味なので）、とにかく現在の論点が出ている所としては、redmine の Feature #11741 である。

 * @<href>{https://bugs.ruby-lang.org/issues/11741}

ここでたびたび意見を述べている Eric Wong について触れておくと、多くの方には「unicorn の作者」と説明するのが分かりやすいだろう。
Unicorn は Rails 絡みのプロジェクトにしてはめずらしく github でホストされておらず、
（非公式のミラーとしては @<href>{https://github.com/defunkt/unicorn} があるので、それを使えばよい）
自前で git レポジトリを公開している。
なぜ github を使わないのかは、本人が書いたものが以下の URL (ML アーカイブ) にある。

 * @<href>{http://bogomips.org/unicorn-public/20140801213202.GA2729%40dcvr.yhbt.net/}

この手の主張に触れたことのないひとには、とても極端な意見に思われるかもしれないが、
自由なソフトウェアを推進している人たちの間では特にめずらしくない、ある意味ごく普通の意見の一つでしかないとも言える。

reddit にも上記 URL についてのスレッドがあるが( @<href>{https://www.reddit.com/r/ruby/comments/2cdks1/eric_wong_on_why_unicorn_will_not_be_hosted_on/} )、その最初のコメントにある冒頭のひとこと、
「I love github, but I have nothing against this attitude.」（意訳：私は github が好きだけど、こういうスタンスは一理ある）
というくらいの意見であれば、さほど特異な感想ではないだろう。


率直な話として、git にしない積極的な理由はないとしても、現状すでに github で公式にミラーされている git レポジトリがある以上、git をプライマリにするメリットはどれほどあるのかよく分からない。
そして、git にするというよりも github 1ヶ所に集約したい（言い換えると他の場所を全て廃止したい）、という希望は、何かしらの反発を招かざるをえない。
上記の reddit のコメントにもあったように、分散SCMなのに一極集中が必要なのはどうなのか、という素朴な違和感もある。
かといって様々な代替手段も用意するのは単純に手間がかかる。

……といったような状況なので、この問題はどういう落とし所がよいのか、よく分からない。興味のある方はぜひ Feature #11741 にコメントを書いていただきたい。

なお、今号の記事の執筆にも blade ( @<href>{http://blade.nagaokaut.ac.jp/} ) を多用した。
blade の偉大さはいくら書いても書ききれない。
改めてここに記して感謝いたします。いつもありがとうございます。

(るびま編集長　高橋征義)
