= よくわかる海外招聘 RubyKaigi 編

ご存知の通り、来る 5 月 30 日、31 日と 6 月 1 日の 3 日間、RubyKaigi 2013 が開催される。
今年は私ではなく Ruby の会理事の角谷さんが実行委員長をやっているため、
重要な仕事は角谷さんにお任せして私自身はラクをしているのだが(その割にはバタバタしているのだが)、
数少ない例外として、海外スピーカーのビザ発行支援の手続きを私の方で行なっている。

ビザの発行支援についてはまとまった情報がほとんどないというか、正直みんなどうやって招聘しているのかよく分かっていない。
そもそも「招聘」の読み方もよく分からない(「しょうへい」と読みます。外務省サイト等では「招へい」と書かれることも多いですが、バランスが悪いのでここでは漢字にしてます)。これはきっと他の多くの方も同様だろう。
そこで、参考のために、イベント主催者側でのビザ申請のための必要な手続きについて、この場を借りてまとめてみる。
これを一通り読めば、他の Ruby やそれ以外のイベントで、ふと海外スピーカーを招聘したくなった時や、ついうっかり講演依頼をしてしまった場合にも多少は安心できるだろう。

== 招聘とビザ(査証)

ビザについての基本的な情報は、外務省のビザ(査証)のページにすべて書かれている。

 * 外務省: ビザ（査証） ( @<href>{http://www.mofa.go.jp/mofaj/toko/visa/} )

が、これをそのまま読むのもちょっと大変である。
最終的にはここを確認するべき、ということだけ念頭に置いて、以下説明を続ける。
なお、何となく響きがいいので、以下ではビザは「査証」に統一する。

大きな流れとしては以下のようになる。

 * 発表者の国籍を確認し、査証が必要かどうか調べる
 * 招聘理由書を書くための情報を聞き出す
 * 招聘理由書やその他の書類を書く
 * 書類を送付する
 * (発表者が)招聘者の送った書類と自分で書いた書類を大使館か総領事館に提出し、申請する

便利なチャートは外務省サイトにもある。

 * 短期滞在査証（ビザ）手続きチャート ( @<href>{http://www.mofa.go.jp/mofaj/toko/visa/nagare/tanki.html} )

というわけで順を追って説明するのだが、まずは査証の必要性である。

実は、海外の方が日本に渡航する際には原則として査証が必要である。

//quote{
日本に入国しようとする外国人は、原則として、自国政府の発給する有効な旅券（パスポート）に、日本国政府の発給する査証（ビザ）を受けたものを所持する必要があります。( @<href>{http://www.mofa.go.jp/mofaj/toko/visa/seido/index.html} )
//}

とはいえ、アメリカの方や韓国・台湾の方が査証なしで来日された話を聞いたり見たりした方も多いだろう。
一部の国や地域の国籍の方は査証なしで日本に入国できる。
それは「査証免除措置国・地域」と呼ばれ、外務省のページに各地域別査証免除措置国・地域一覧表に書かれている。

 * 入国時に査証を必要としない場合について ( @<href>{http://www.mofa.go.jp/mofaj/toko/visa/tanki/novisa.html} )

ここに書かれている国籍の方であれば、何も手続きは必要ない。
普通に旅費宿泊費を用意してもらい(あるいは主催者側で用意し)、予約等の手配を行う。

逆に言うと、ここに書かれている以外の国籍を持つ方の場合、
上記手配に加えて、査証の発行のための書類作成が必要になる。

なお、査証が必要な場合でも、主催者ではなくスピーカーの勤務先や顧客などの方で査証のための書類を用意してもらえる場合もある。
その場合も主催者は何もしなくてよいのだが、ちゃんと手続きを間に合うようにされているかは心配になるところではある(最悪そのへんでもたつくと、突然キャンセルになったりするので注意)。

== 査証の申請準備

査証申請の手続きは国籍によって若干違うようで、外務省サイトでは以下のような分類がされて、
それぞれ別の説明が書かれている。

 * 中国
 * ロシア・NIS諸国
 * フィリピン
 * その他

不思議な分類だがそれについてはここでは追求しないこととする。もっとも上記の4つについては、内容としてはほぼ同様であるのだが、念のためそれぞれを確認しておいた方がいいだろう。

ここで用語を確認しておく。「招聘人」と「申請人」である。
「招へい人」あるいは「招聘人」などと書かれているのが
イベント主催者であり、「申請者」というのが査証を発行してもらって
日本に渡航してくるスピーカー(あるいは参加者)である。

イベントのスピーカーとして呼ぶ場合、招聘人は法人が行った方がよさそうである。
試してみたことがないので分からないが、
招聘人が個人の場合だと何やら面倒くさそうというか、
「親戚や親しい友人を日本に呼ぶ」くらいの雰囲気(もしくは胡散臭さ)になりそうで、
一歩間違えると違法入国のお手伝いをしている方と区別しがたくなりかねない。
主催者が法人格をもっている場合は法人として招聘したい。
ちなみにRubyKaigiの場合、2011の時はRubyの会自体が
任意団体だったため、招聘人としてはRubyアソシエーションさんに
お願いしていたのだが、2013では一般社団法人日本Rubyの会が招聘人となっている。

== 書類について

用意する書類は４種類である

 1. 招聘理由書
 2. 身元保証書
 3. 滞在予定表
 4. 招聘機関に関する資料

ちなみにこれらの書類は日本語で提出できる(提出先は日本大使館または総領事館なので)。
申請人には送るだけ送って、申請人の書いた英語や母国語の書類と合わせて提出してもらう形になる。

1〜3については外務省の方でテンプレートと説明を用意している。たとえば
中国、ロシア・NIS諸国、フィリピン国籍以外の場合は以下のサイトからダウンロードできる。

 * 中国、ロシア・NIS諸国、フィリピン国籍以外の方が短期滞在を目的として日本へ渡航する場合 ( @<href>{http://www.mofa.go.jp/mofaj/toko/visa/tanki/other_visa.html} )

1の招聘理由書については、招聘人と査証申請人の情報を書いた上で、例えばRubyKaigiなら
「招聘目的」には「2013年5月30日〜6月1日まで開催される、プログラミング言語Rubyに関するカンファレンス「RubyKaigi 2013」にて講演を行うため」、
「招聘経緯」には「RubyKaigiは2006年から年一回開催されるカンファレンスである。招聘人は昨年末より講演者を募集しており、選考の結果申請人に講演を依頼することに決定した。」、
「申請人との関係」には「申請人はRubyKaigi 2013での講演を行うものであり、招聘人はそのカンファレンスを開催する主催団体の一つとなっている。」などと記載している。

2の「身元保証書」については、発行するかどうかは判断が必要だろう。
身元保証書では「滞在費」「帰国旅費」「法令の遵守」を保証させられる。
最低限ネットでの活動実績があればよいが、まったくどういう人か分からない場合
(そういう人をスピーカーとして呼ぶことはあまりないとは思うが)、
身元保証書については申請人側で用意してもらう判断もある。
少なくとも何かあった場合には帰国旅費の肩代わりや次年度以降の開催が困難に
なることも考慮した上で発行を判断するべきなのだろう。

ちなみに招聘人が日本の中央府省庁の課長職または大学の教授以上は必要ないらしい。教授すごい。

3の滞在予定表については、入国と出国の日にち、滞在する予定のホテルくらいは書かないとまずそうなので、
その辺りを申請人に確認しておく。
あくまで「予定」表なので、ホテルは仮予約でも構わないし、
前後の日程はざっくり都内なら都内の観光とでも書いておくので構わないようである。
もちろん決まっている場合にはそれを書いておく。

最後の招聘機関に関する資料は、普通に法人であれば登記簿謄本(履歴事項全部証明書)を取得できるので、その原本を添付すればよい。Rubyの会は一般社団法人なので、法務局の出張所で履歴事項全部証明書を発行してもらった。

これで一通り書類が揃ったことになる。
もっとも、これまでの説明で分かった通り、申請人の情報をもらわないと
記載できないことも多々あるので、そのやりとりに時間がかかることも多い。
余裕を持った日程で準備を進めたい
(……と言いつつ、ぎりぎりになってしまってすみませんでした……)。

== 書類の送付

書類ができ次第、それを申請人に送ることになる。

そういえば書類の送付先も重要で、たまに申請人が一定の場所にいない場合もあるので
気をつける必要がある。場合によっては、

 * 国籍の国
 * 申請人が住んでいる場所
 * 申請人が査証の申請をする日本大使館・総領事館のある場所

が全部異なることもありうるので要注意である。

海外に送付する手段はいろいろあるようだが、
日本から送る場合は郵便局で EMS(Express Mail Service) を使うのが手っ取り早いだろう。
送料は場所にもよるが、900 円 〜 1,700 円くらいで送れるようである。
日数も関東からなら数日 〜 1 週間程度で届くらしい。やってみると意外に簡単ですぐ届く。

== 申請

申請は申請人側におまかせなので、どういう仕組みかもよく知らない。
国というか大使館・総領事館によっても違いがあるのかしれない。
申請してから発給されるまでは、外務省のサイトでは「特に問題のない場合5業務日」で
「大使館／総領事館や渡航目的によっては、これより短い場合もあります」ということだそうである。
問題のある場合は 1 ヶ月以上かかる場合もあるので、はやめに準備するに越したことはないだろう。

以上、招聘のために必要そうな情報を一通り書いてみた。
RubyKaigi やその他のイベント開催の裏側では、このような作業(やもっと面倒な作業)が粛々と行われている。
これを参考に、国内の他のイベントにも海外からの素晴らしいスピーカーが参加されるようになることを期待したい。