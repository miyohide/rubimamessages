= ソーシャルコーディングとは何かについて考える

ここのところ、「ソーシャルコーディング」という言葉が一部で流行しつつある。 単に狭いところで流行っているだけではない。 Ruby の会が行う今後の活動においても、おそらく活動の一端を支えるキーワードの 1 つになるのではないか、 と思われるくらいには重要な考え方である。

とはいえ、まだあまり馴染みがないとか、何度か聞いたことがあるけどはっきりと意味を 理解しているかどうか怪しい、という方も少なくないだろう。 それも当然で、ソーシャルコーディングは明確な定義を持った言葉ではない(と私も思っている)。 そのため、私自身の解釈も確固とした後ろ盾を持ったものではないのだが、 できる限りの説明を試みたい。

ソーシャルコーディングという言葉が広く使われるようになったきっかけは、 言うまでもなく GitHub である。GitHub のロゴの右下に書かれている言葉、 「SOCIAL CODING」は、まさしく GitHub を母体にして生まれた開発スタイルであり、 今では GitHub 以外の文脈でも使われるようになったと言えるだろう。

GitHub が「ソーシャル」であるとされるのは、例えば開発者をフォローしたりメッセージを 送れたりするなど、ソーシャルネットワークサービスによくある機能を備えているからと思われている向きも あるようだ。しかしながら、それだけが理由ではない(もちろん関係はあるが、それは GitHub がソーシャルになったために 「あると便利な機能」になっているだけで、それ自体が原因ではない)。GitHub では、コーディングという活動の中に、 というよりもむしろソフトウェア開発のワークフローの中に、ソーシャルな要素を強く盛り込んでいるためである。

もっとも、ソーシャルコーディング自体はまったく新しい概念ではない。 ある意味では、これまで広く行われていたフリーソフトウェアやオープンソースソフトウェアの 開発手法と変わるものではないと言ってよい。むしろそれらを現在の技術により進化・加速させたものだと 考えるべきだろう。

ソーシャルコーディングに使われる技術的なしくみの中でも、とりわけ特徴的なものを３つ挙げてみる。

 * 分散バージョン管理システム
 * pull requestを備えたパッチベースのチケットシステム
 * 自動化されたテスト

1番目の分散バージョン管理と、2番目の pull request が、ソーシャルコーディングにおいて その根幹に関わる重要な技術である。とはいえ、分散ではないバージョン管理は、 少し前からもはや必須というくらいに広まっていたし、BTS や ITS と言ったチケットシステムも特にめずらしくはなかった。 また、svn でもリモートとローカルを切り離して、ネットワークにつながっていない 時でも開発を行えるようにした svk なども、それなりには使われていた。 ３番目の自動化テストも同様である。

このように、ソーシャルコーディングで使われている技術は、 もともと十年以上も前からFLOSS 界隈で使われていた技術の発展型である。 しかしながら、その使われ方は、十年前とは異なった影響を及ぼし始めている。

これまでよく言われていた FLOSS での開発とは異なる、 ソーシャルコーディングに特徴的なポリシーを２つほどあげてみよう。

 * フォークの積極的な推進・活用
 * あまりリリースしない(しなくてよい)

前者のフォークについては意外に思う方もいるかもしれない。昔から、主に FLOSS 方面のソフトウェア開発に おいて、フォークは多くの場合避けるべきものとされていた。 実際、Wikipedia からの孫引きによれば、ジャーゴンファイルでも以下のように書かれている(らしい)。

//quote{
フォークは「良くないこと」であると考えられている。理由として、フォークの結果 多くの開発の労力が浪費されるという点だけでなく、本家争い、引き継ぎ、設計の方 向性などについて、後継となるグループ間で激しい口論が行われる点がある。 (@<href>{http://ja.wikipedia.org/wiki/%E3%83%95%E3%82%A9%E3%83%BC%E3%82%AF_(%E3%82%BD%E3%83%95%E3%83%88%E3%82%A6%E3%82%A7%E3%82%A2%E9%96%8B%E7%99%BA),Wikipedia「フォーク (ソフトウェア開発)」}より)
//}

しかし、分散バージョン管理システムの普及は、フォークの意味を全く異なるものに変えた。 とりわけ GitHub でのフォークは容易を極める。単に fork ボタンを押すだけである。 これ以上ないほどのカジュアルさでフォークできてしまう。これはフォークに対して忌避感を抱いている人なら 愕然とするだろう。

なぜここまで簡単になったのか。それは、分散バージョン管理により、

 * 異なるブランチを作ること
 * それを公開すること
 * そしてそれを元のブランチ(幹)や、また別のブランチにとりこむこと

といったことが基本的な機能として実現できてしまうようになったためである。

思えば、従来型のソフトウェア開発は、たぶんに中央集権的であった。 バザールといっても、本当の意味でみなが対等に市場に参加しているわけではなく、 オリジナルのレポジトリと、そこから派生してできたリポジトリが同じ立場に なるわけではなく、オリジナルのレポジトリにアクセスできる開発者、そして そのアクセス権を管理するところに、一種の権力構造ができるようになる (この辺りについては、@IT 誌で西村賢氏が書いた「ソーシャル化する OSS 開発者たち」 ( @<href>{http://www.atmarkit.co.jp/news/analysis/200904/14/git.html} ) が詳しい)。 これはすなわち、ある種の「伽藍」として機能していた、ということだろう。

GitHub はそれに比べればより「バザール」度が高い。 分散バージョン管理による複数レポジトリへ容易にフォークする機能に加え、pull request と チケットシステムが合体したことにより、ボタンひとつでフォークしたレポジトリをマージまで できるようになった。 これは、ソフトウェアの開発作業そのものが、よりソーシャル化されたことに他ならない。 コードを書く、テストを書く、pull request を送る (pull request ボタンを押してコメントを書く)、 merge する(merge ボタンを押す)、といった流れが、ごく当たり前の「作業」のレベルまで 落ちてきたことになる。

さらにここで bundler が登場する。bundler を使えば、rubygems.org で公開されているコードと、 フォークしてできたコードを、同じように扱うことができる。これによって、例えば何かしらの ライブラリに様々なフォークがあったとして、それが本家にマージすらされなくとも、 好きなフォークのコードを使うことができるようになる。どのフォークも好きでなければ、 自分の GitHub レポジトリにフォークを作ってそれを使うことも簡単である。 これはつまり、「リリース」という機能の重要性を減らすこととなった(もちろん、その意味が ゼロになるわけではないが、以前と比べればその決定的な意味合いが大きく後退しているように見える)。

このようにみると、ソーシャルコーディングを基盤としたにソフトウェア開発の世界は、 より一層混沌としているようにみえる。 しかしながら、それは一昔前、人々が当時の「バザール」の世界を眺めたときに感じた混沌に相似しているように思う。

少し発散してきたような気もするので、ここでいったんまとめたい。 ソーシャルコーディングは、ソフトウェア開発の世界になにか新しいものを付け加えてくれるものではない。 むしろ、これまでのやり方を改良し、その流れを加速させるものである。 より徹底したバザールの形、私たちがソーシャルコーディングという言葉で名付けているものは、そんな形をしている何者かである。