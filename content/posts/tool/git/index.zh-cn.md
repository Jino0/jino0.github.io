---
title: "git pro 读书笔记"
subtitle: ""
date: 2022-08-14T16:08:03+08:00
lastmod: 2022-08-18T01:05:03+08:00
draft: false
authors: []
description: ""

tags: ["git"]
categories: ["tool"]
series: []

hiddenFromHomePage: false
hiddenFromSearch: false

featuredImage: "elephant-3458033__480.jpeg"
featuredImagePreview: "elephant-3458033__480.jpeg"

toc:
  enable: true
math:
  enable: false
lightgallery: false
license: ""
---

  介绍 git 相关使用方法，一些命令的介绍。也是 [git pro 读书笔记](https://git-scm.com/book/en/v2)。
<!--more-->

## 什么是git

git 是分布式的版本管理系统。本地仓库有代码，远端仓库也有代码。没有网络可以先在本地开发，之后有了网络再进行提交。

## 版本控制

客户端并不只提取最新版本的文件快照， 而是把代码仓库完整地镜像下来，包括完整的历史记录。 
这么一来，任何一处协同工作用的服务器发生故障，事后都可以用任何一个镜像出来的本地仓库恢复。
因为每一次的克隆操作，实际上都是一次对代码仓库的完整备份。本质是对文件变更过程的管理工作，需要的时候可以进入指定的版本。

## 快照流

当你提交更新或者保存项目状态的时候，git基本上会对当时所有的文件创建一个快照并保存这个快照的索引。
如果文件没有修改，Git将不再重复存储该文件，而是保留一个链接指向之前存储的文件的索引。 

## 本地执行

git 既有远程仓库又有本地仓库，在本地几乎可以完成绝大多数的 git 的常用操作，置于推送到远程服务，啥时候有网啥时候弄就行。

## git 保存完整性

如果在传输的过程中，出现了文件丢失的情况，git会及时的发现，因为git底层有一个计算校验和的机制，叫做 SHA-1 散列 (hash，哈希)。是基于git中文件的内容或目录结构计算出来的一个由40个十六进制数组成的字符串。

git 一般只添加数据，很难让 git 执行任何不可逆操作，或者让他以任何方式清除数据。未提交更新时可能丢失或弄乱修改的内容，但是一旦提交快照到git中，就很难在丢失数据，要养成定期推送的好习惯。

## 三种状态

已提交(committed):以保存在本地数据库中

已暂存(staged): 对修改过的文件做了标记使之包含在在此提交的快照中

已修改(modified): 只是修改了文件，并没有保存到数据库中

## 获取git仓库的两种方式

1. 在已存在目录中初始化仓库: 如果你有一个尚未进行版本控制的项目目录，想要用 Git 来控制它，那么首先需要进入该项目目录中。执行：
```
 git init。
```
这是会在该文件下创建一个 .git 文件，但此时还没有被跟踪，下一步，开始追踪：
```
 git add *.c
 git add LICENSE  //添加为跟踪文件
 git commit -m 'initial project version'
```
2. `git clone <url>`	 会克隆下git仓库服务器上的几乎所有数据，不是用什么克隆什么。
```
Git clone < url>  newName 
```
支持，克隆本地后在本地用新名字。而且不但支持http协议，还支持SSH等多种协议。	
```
git status 
```
每一个文件都只有两种状态，已跟踪 或 未跟踪。已跟踪的文件就是已经纳入版本控制的文件。初次克隆仓库的时候，所有的文件都是已跟踪文件，未修改的状态。

`git status` 可以查看文件的状态。

## 跟踪新文件

假设现在刚创建了一个文件，该文件就是未跟踪状态。`git status`之后，会有 `Untrack files：XXX` 的提示，而且 git 仓库并不会直接把它纳入跟踪范围，需要手动添加，命令：
`git add XXX`。

暂存已修改的文件：当修改了一个已跟踪的文件之后，再 `git status` 会，显示 `Changes not staged for commit`。即修改没放到暂存区。放到暂存区的命令还是`git add <某文件>`。

`git add.` 可以将所有修改的文件均放到暂存区。放入暂存区再修改再`git status`会发现，该文件既在暂存区又在非暂存区。因为上次的`git add`仅仅包含上次的修改。

状态简览：使用命令`git status -s` 或者 `git status —short`会得到一种格式更为简洁的输出。
```
$ git status -s

M README              // 修改过的是 M 标记
MM Makefile           // A  
lib/git.rb            // 新添加到暂存区的是 A 标记
M  lib/simplegit.rb   
?? LICENSE.txt        // ？？表示新添加的未跟踪的文件
```

## 忽略文件

像一些日志文件、编译产生的临时文件等无用文件无需跟踪，我们就可以创建一个 `.gitignore` 文件来忽略这些文件。该文件格式规范如下：

所有`空行`或者以 `#` 开头的行都会被 Git 忽略。

可以使用标准的 `glob` 模式匹配，它会递归地应用在整个工作区中。

匹配模式可以以`/`开头防止递归。匹配模式可以以 `/` 结尾指定目录。

要忽略指定模式以外的文件或目录，可以在模式前加上叹号（!）取反。

> 所谓的 glob 模式是指 shell 所使用的简化了的正则表达式。   
> 星号（*）匹配零个或多个任意字符；
> [abc] 匹配任何一个列在方括号中的字符 （这个例子要么匹配一个 a，要么匹配一个 b，要么匹配一个 c）； 
> 问号（?）只匹配一个任意字符；如果在方括号中使用短划线分隔两个字符， 表示所有在这两个字符范围内的都可以匹配（比如 [0-9] 表示匹配所有 0 到 9 的数字）。 使用两个星号（**）表示匹配任意中间目录，比如 a/**/z 可以匹配 a/z 、 a/b/z 或 a/b/c/z 等。

我们再看一个 .gitignore 文件的例子：
```
# 忽略所有的 .a 文件     *.a

# 但跟踪所有的 lib.a，即便你在前面忽略了 .a 文件      !lib.a

# 只忽略当前目录下的 TODO 文件，而不忽略 subdir/TODO          /TODO

# 忽略任何目录下名为 build 的文件夹         build/

# 忽略 doc/notes.txt，但不忽略 doc/server/arch.txt    doc/*.txt

# 忽略 doc/ 目录及其所有子目录下的 .pdf 文件     doc/**/*.pdf
```
## 查看已暂存和未暂存的修改

`Git diff`：此命令比较的是工作目录中当前文件和暂存区域快照之间的差异。 也就是修改之后还没有暂存起来的变化内容。只显示尚未暂存的改动。

若要查看已暂存的将要添加到下次提交里的内容，可以用 `git diff --staged` 命令。 这条命令将比对已暂存文件与最后一次提交的文件差异：

## 提交更新

`git commit`：可以看到，默认的提交消息包含最后一次运行 `git status` 的输出，放在注释行里，另外开头还有一个空行，供你输入提交说明。

还可以直接：`git commit -m “说明信息”`  直接提交

给 git commit 加上 `-a` 之后，可以跳过 git add. 步骤直接提交。
```
git commit -am 'commit 信息'
```
## 移除文件	

`rm XXX` 这样删除文件，文件会出现在未暂存清单中，再 `git rm XXX`。就不再纳入版本管理了。

如果要删除之前放在暂存区的文件要加 `-f` 。

如果忘记了添加忽略文件或从暂存区移除但保存在本地磁盘上且不再版本控制，可以用 `git rm --cached xxx` ，xxx 可以是文件名字还可以是目录

## 移动文件

`git mv aaa bbb`：相当于下面三条指令，效果一样，`git mv` 更加方便。
```
mv aaa bbb
git rm aaa
git add bbb 
```
## 查看提交历史

`git log`：不传入任何参数的默认情况下，`git log` 会按时间先后顺序列出所有的提交，最近的更新排在最上面。  
这个命令会列出每个提交的 SHA-1 校验和、作者的名字和电子邮件地址、提交时间以及提交说明。

`-p` 或 `--patch` ，它会显示每次提交所引入的差异（按 补丁 的格式输出）。   
在包含 `git log` 输出的信息之外的同时，还会输出 `git diff` 输出的 diff 内容。

还可以限制显示的日志条目数量，`-2` 选项来只显示最近的两次提交。`-<n>`n次

`--stat` 选项：可以看到每次提交的简略统计信息

`git log --pretty=format `：可以定制记录的显示格式。更多[看这里](https://ruby-china.org/topics/939)
```
$ git log —since=2.weeks 最近两周

$ git log -S function_name 它接受一个字符串参数，并且只会显示那些添加或删除了该字符串的提交。 假设你想找出添加或删除了对某一个特定函数的引用的提交，可以调用
```
来看一个实际的例子，如果要在 Git 源码库中查看 Junio Hamano 在 2008 年 10 月其间， 除了合并提交之外的哪一个提交修改了测试文件，可以使用下面的命令：
```
$ git log --pretty="%h - %s" --author='Junio C Hamano' --since="2008-10-01" \

   --before="2008-11-01" --no-merges -- t/
```

## 提交信息合并

`git commit —amend` 会将暂存区的文件提交，如果上次提交后没有更改，只是修改提交信息。 

如果有文件没有提交：
```
$ git commit -m 'initial commit'
$ git add forgotten_file
$ git commit —amend
```
最终只会有一个提交结果，旧的提交结果就像从来没有存在过一样，保证了仓库提交历史的干净。

## 撤销操作

`git reset`：将当前的分支的 HEAD 指向给定的版本，并根据参数 [--soft, --mixed, --hard] 决定对于工作区和暂存区内文件的修改。默认参数为 `mixed`。

`git reset  --soft commit_id`：-soft 参数仅仅会将 HEAD 回退到某个版本，不修改暂存区和工作区的内容。

`git reset  --mixed commit_id`：--mixed 为默认，可以不用带该参数，用于重置暂存区的文件与上一次的提交(commit)保持一致，工作区文件内容保持不变。

`git reset  --hard commit_id`：--hard 参数撤销工作区中所有未提交的修改内容，将暂存区与工作区都回到上一次版本，并删除之前的所有信息提交。

将 HEAD 回退到指定版本号，比如有提交 1，2，3。可以直接回退到1，此时2，3，就没有了。下次提交需要加 -f 强制提交。

`git revert`：假设有提交 1，2，3。想要撤销2保留3，即可使用此命令，revert 后会生成提交4 ，4里面撤销了2，保留了3。

## 取消暂存的文件

`git reset HEAD xxx`  将文件从已暂存状态变为 修改未暂存状态。

## 取消对文件的修改：

`git checkout -- xxx`  但是 `git checkout -- <file>` 是一个危险的命令。 你对那个文件在本地的任何修改都会消失，Git 会用最近提交的版本覆盖掉它。

## 查看远程仓库

`git remote`： 会列出制定的每一个远程服务器的简写。如果已克隆会有默认名字：orgin。

`git remote -v`：会显示需要读写远程仓库使用的 Git 保存的简写与其对应的 URL。有多个的话，会一一列出。

## 查看某个远程仓库

`git remote show origin` ：同样会列出远程仓库的 URL 与跟踪分支的信息。 这些信息非常有用，它告诉你正处于 master 分支，并且如果运行 git pull， 就会抓取所有的远程引用，然后将远程 master 分支合并到本地 master 分支。 它也会列出拉取到的所有远程引用。 
显示的信息更加的详细。这个命令列出了当你在特定的分支上执行 git push 会自动地推送到哪一个远程分支。 它也同样地列出了哪些远程分支不在你的本地，哪些远程分支已经从服务器上移除了， 还有当你执行 git pull 时哪些本地分支可以与它跟踪的远程分支自动合并。

## 添加远程仓库

`git remote add <shortname> <url>` 添加一个新的远程 Git 仓库，shortnamae即重命名

## 推送到远程仓库
`git push <远程主机名> <本地分支名>:<远程分支名>`：git push 的命令格式。
`git push orgin master` <==> `git push origin master:master`：将 master 分支，推送到 origin 服务器上。

`git push --force origin master`：如果本地版本与远程版本有差异，但又要强制推送可以使用 --force 参数：

`git push origin --delete master`：删除主机的分支可以使用 --delete 参数，以下命令表示删除 origin 主机的 master 分支：

## 远程仓库的移除和重命名

`git remote rename pb paul` 将pb更名为paul。

`git remote remove Paul`：移除远程仓库

## 远程仓库拉取数据

`git fetch <remote>`：访问远程仓库，并拉取所有你还没有的数据。 执行完成后，你将会拥有那个远程仓库中所有分支的引用，可以随时合并或查看。

`Git clone` ：如果你使用 clone 命令克隆了一个仓库，命令会自动将其添加为远程仓库并默认以 “origin” 为简写。  

`git fetch origin` 会抓取克隆（或上一次抓取）后新推送的所有工作。 必须注意 git fetch 命令只会将数据下载到你的本地仓库——它并不会自动合并或修改你当前的工作。 当准备好时你必须手动将其合并入你的工作。

`git pull <远程主机名> <远程分支名>:<本地分支名>`：git clone + git merge ，git pull origin master:brantest，将远程主机 origin 的 master 分支拉取过来，与本地的 brantest 分支合并。   
`git pull origin master`如果远程分支是与当前分支合并，则冒号后面的部分可以省略。

git clone 命令会自动设置本地 master 分支跟踪克隆的远程仓库的 master 分支（或其它名字的默认分支）。 运行 `git pull` 通常会从最初克隆的服务器上抓取数据并自动尝试合并到当前所在的分支。

## 创建标签(轻量标签，附注标签)

**轻量标签**：像一个不会改变的分支，只是某个`特定提交`的引用。轻量标签本质上是将提交校验和存储到一个文件中——没有保存任何其他信息。     
创建轻量标签，不需要使用 -a、-s 或 -m 选项，只需要提供标签名字：

`git tag v1.4-lw`  创建名为 `v1.4-lw` 的轻量标签。查看该标签只会有提交信息

**附注标签**：是存储在 git 数据库中的一个完整对象，它们是可以被校验的，其中包含打标签者的名字、电子邮件地址、日期时间， 此外还有一个标签信息，并且可以使用 GNU Privacy Guard （GPG）签名并验证。 

`git tag -a v1.4 -m “My version 1.4”` 创建附注标签，-m 后为描述信息，没有的话会启动文本编辑器让你添加，类似于 git commit -m “描述信息” 。

## 列出标签

`git tag`(可带上-l或-list)：将标签列出来

`git tag -l “*v1*”`  (匹配标签名的通配模式下，必须加-l)：会筛选v1开头的

## 后期打标签

`git tag -a v1.2 9fceb02`：要在那个提交上打标签，你需要在命令的末尾指定提交的校验和（或部分校验和）

## 共享标签

推送标签并不会区分轻量标签和附注标签

`git push origin <tagname>`：向远程推送标签，这样别人拉代码时也会将标签拉下来

`git push origin —tags`：这将会把所有不在远程仓库服务器上的标签全部传送到那里。

## 删除标签
```
$ git tag -d <tagname>：删除一个轻量标签，仅本地
$ git push <remote> :refs/tags/<tagname> 来更新你的远程仓库同步删除
$ git push <remote> :refs/tags/<tagname> ：变体1 将冒号前面的空值推送到远程标签名，从而高效地删除它。
$ git push origin --delete <tagname>：变体2 更直观的删除远程标签的方式
```
## 检出标签

`git checkout 2.0.0`：查看某个标签所指向的文件版本，但是这会使你的仓库处于`分离头指针（detached HEAD）`的状态——--这个状态有些不好的副作用。在“分离头指针”状态下，如果你做了某些更改然后提交它们，标签不会发生变化，但你的新提交将不属于任何分支，并且将无法访问，除非通过确切的提交哈希才能访问。因此，如果你需要进行更改，比如你要修复旧版本中的错误，那么通常需要创建一个新分支：
```
git checkout -b version2 v2.0.0
switched to a new branch 'version2'
```
如果在这之后又进行了一次提交，version2 分支就会因为这个改动向前移动， 此时它就会和 v2.0.0 标签稍微有些不同，这时就要当心了。

## Git 命令别名
```
git config --global alias.co checkout   git co == git checkout
git config --global alias.br branch	    git br == git branch		
git config --global alias.unstage 'reset HEAD —'   git onstage fileA == git reset HEAD -- fileA
```
## 分支简介

在进行提交操作的时候，git 会保存一个提交对象，该提交对象会包含一个指向暂存内容快照的指针。以及作者的姓名邮箱、提交时输入的信息、父对象的指针等内容。   
首次提交产生的提交对象没有父对象，普通提交操作产生的提交对象有一个父对象， 而由多个分支合并产生的提交对象有多个父对象。

一个目录里面有三个文件，修改暂存提交之后。git 会计算该目录的校验和，并保存为树对象，该树对象有指向文件快照blob对象的指针。    
还有一个提交对象，包含指向树对象的指针。提交对象有指向树的指针，树对象有指向文件快照blob对象的指针。如果修改后再次提交，新的提交对象还会有一个指向上一次提交的对象的指针，即父指针。Git 的分支，其实本质上仅仅是指向提交对象的可变指针。

## 分支创建

`git branch aab` :会创建一个可以移动的新指针

Git 中的 HEAD 是一个指针，指向当前所在的本地分支 master (一般本地分支默认名称为 master)。

刚创建的 aab 指针和 master 指向的是同一个提交对象。HEAD 指向 master。

`git log --oneline —decorate` ：查看当前各个分支当前所指的对象。

`git checkout aab` ：	切换分支，此时 HEAD 指向 aab。

在 aab 上做了部分修改并提交后，aab分支会向前移动指向新的提交对象，但是 master 还是原来的不变。此时再切回 master，整个工作目录会变成 master 对应的状态。在这里修改并提交，master 会向前移动，master 的向前一步走和 aab 的向前一步走就**分叉**了。

由于 Git 的分支实质上仅是包含所指对象校验和（长度为 40 的 SHA-1 值字符串）的文件，所以它的创建和销毁都异常高效。 创建一个新分支就相当于往一个文件中写入 41 个字节（40 个字符和 1 个换行符），更加的简单高效。

## 分支的新建与合并
```
git branch xxx :      创建新分支
git checkout xxx :    切换到分支 xxx 上
git checkout -b xxx : 创建新分支并切换到新分支上。

git merge xxx :       当前分支合并 xxx 分支。如果要合并的分支并不是当前分支的直接祖先，此时 git 就会合并两个分支的末端和两个分支的公共祖先做一个三方合并。
git branch -d xxx :   删除分支 xxx 
```

## 分支管理

```
git branch :                        不加参数的时候会得到分支列表，列表中带有 * 的分支就是当前检出的分支，即 HEAD 指针指向的分支
git branch -v :                     查看每个分支的最后一次提交
git branch —merged :                查看已经合并到当前分支的分支
git branch —no-merged :             查看所有未合并工作的分支
git branch --no-merged master :     尚未合并到master分支上的分支有哪些
```

## 分支重命名

本地: `git branch -m oldName newName`

远程:    
1. 重命名远程分支对应的本地分支，`git branch -m oldName newName`
2. 删除远程分支，`git push --delete origin oldName`
3. 上传新命名的本地分支，`git push origin newName`
4. 把修改后的本地分支与远程分支关联，`git branch --set-upstream-to origin/newName`

## 远程分支

远程跟踪分支是远程分支状态的引用。它们是你无法移动的本地引用。一旦你进行了网络通信，Git 就会为你移动它们以精确反映远程仓库的状态。该分支在远程仓库中的位置就是你最后一次连接到它们的位置。如果在你工作的时候，别人向远程仓库推送了新的提交，那么远程仓库的 master 会更新。但是我们的 origin/master 分支并不会移动，还是我们之前与远程仓库通信时的位置。

假设你的网络里有一个在 git.ourcompany.com 的 Git 服务器。如果你从这里克隆，Git的 clone 命令会为你自动将其命名为 origin，拉取它的所有数据，创建一个指向的 master 分支的指针，并且在本地将其命名为 origin/master。 Git 也会给你一个与 origin的 master 分支在指向同一个地方的本地 master 分支。
```
git fecth orgin:                       用来拉取远程仓库的最新的修改数据，移动 origin/master 到更新后位置
git merge orgin:                       将拉取的数据与当前的本地数据合并
git push origin serverfix:             将本地的 serverfix 分支来更新远程仓库上的 serverfix
git push origin serverfix:serverfix:   效果一样
git push origin serverfix:a:           将本地分支 serverfix 推送到远程 a 分支上
```
## 跟踪分支

克隆仓库时，自动创建的 master 分支就是默认跟踪的 origin/master 分支，执行 git pull 后自动的去 origin/master 上拉取数据并合并到master分支上。跟踪分支后就知道了去那个服务器拉取数据，合并到那个分支上面。当然，可以手动设置让分支跟踪那个分支。
```
git checkout --track origin/serverfix:   设置分支 serverfix 跟踪远程仓库中的分支 serverfix
git checkout serverfix:                  如果你尝试检出的分支 (a) 不存在且 (b) 刚好只有一个名字与之匹配的远程分支
git checkout -b sf origin/serverfix :    将本地分支与远程分支设置为不同的名字,sf 会从 origin/serverfix 上面拉取数据
git branch -vv:                          可以查看设置的所有跟踪分支，还有分支所跟踪的远程分支与本地分支是否领先还是落后
git push origin --delete serverfix:      删除远程分支
```

## 变基

`变基`：[详见](https://git-scm.com/book/zh/v2/Git-%E5%88%86%E6%94%AF-%E5%8F%98%E5%9F%BA)

## cherry-pick
`git cherry-pick <commitHash>`：上面命令就会将指定的提交commitHash，应用于当前分支。这会在当前分支产生一个新的提交，当然它们的哈希值会不一样。