# 介绍
## 对象模型
   所有用来表示项目历史信息的文件，是通过一个40字符的“对象名”来索引的。

   每个对象(object)包括三个部分: 类型、大小和内容。类型可以是 *blob*、*tree*、*commit*、*tag*
   - *blob* 用来存储文件数据，通常是一个文件
   - *tree* 有点像一个目录，它管理一些"tree"或是"blob"
   - 一个 *commit* 只指向一个"tree"，他用来标记项目某一个特定时间点的状态
   - 一个 *tag* 是来标记某一个提交(commit)的方法

   我们可以使用 `git show SHA` 来查看一个对象， `git ls-tree SHA` 可以查看tree更详细的信息

## TODO GIT目录与工作目录
   忽略

## TODO 索引
   忽略

# 第一步
## 安装与配置
   ubuntu 下使用 =$ sudo apt-get install git-core= 即可完成安装

   需要做如下配置:
   #+BEGIN_SRC sh
   $ git config --global user.name "wax5798"
   $ git config --global user.name "xxxx@mail.com"
   $ git config --global core.quotepath false       # 防止中文路径乱码
   #+END_SRC
   如果想让配置只在当前项目中生效，命令中不带--golbal选项

# 正常的工作流程
  - =git init= 创建一个空的仓库或重新初始化
  - =git add file1 file2= 把更新内容添加到索引
  - =git diff --cached= 查看即将被提交的文件都作了那些修改
  - =git commit= 提交当前索引中的内容, 也可以通过 =-m "comment"= 的方式加入注释
  - =git commit -a= 把所有修改过的文件(不包括新建的文件)都加入索引，然后提交
  - =git checkout -- <paths>= 使工作目录与索引或HEAD同步

# 分支与合并
  - =git branch exp= 创建一个分支
  - =git branch= 查看当前仓库的分支列表
  - =git checkout exp= 切换到某个分支
  - =git merge exp= 将某个或者多个分支合并到当前分支
  - 如果merge的两个分支有冲突，可使用 =git diff= 或 =git status= 查看冲突，编辑过冲突文件使用 =git commit -a= 提交
  - =gitk= 显示项目历史
  - =git branch -d exp2= 删除某个被当前分支合并的分支
  - =git branch -D exp2= 强制删除某个分支
      
# TODO git reset
## git reset [-q] [<tree-ish>] [--] <paths>...
   把path对应的索引reset至<tree-ish>的状态，<tree-ish>多为HEAD
## git reset [<mode>] [-q] [<commit>]
   将当前的分支重设到指定的<commit>(默认为HEAD)，并根据[<mode>]更新索引和工作目录

   [<mode>]可以取如下值
   1. --hard 重设 索引和工作目录
   2. --soft 索引和工作目录的内容不变
   3. --mixed 默认模式，仅重设索引，不重设工作目录
   4. --merge 忽略
   5. --keep 忽略

# 查看历史——GIT 日志
  忽略

# 比较提交——GIT Diff
  - =git diff master..test= 显示两个分支间的差异
  - =git diff master...test= 显示父分支和"test"分支的差异
  - =git diff= 查看工作目录中，没有添加到索引的修改(与索引或上次提交比较)，不会被"git commit"提交
  - =git diff --cached= 当前索引与上次提交的差异，这些差异会在"git commit"时被提交
  - =git diff HEAD= 查看工作目录与上次提交的差别，这些差异会在"git commit -a"时被提交
  - =git diff test= 查看当前工作目录与 test 分支的差异
  - =git diff test -- ./dir= 查看在 test 分支下，dir 路径下的差异
  - =-- stat= 参数，只显示被改动的文件，不显示详细信息

# 分布式的工作流程
  我们有一个仓库 =~/git/tmp/gitRepos=
  - =git clone ~/git/tmp/gitRepos/ user1= 把gitRepos仓库克隆到 user1 目录
