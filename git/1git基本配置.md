## 配置的保存
git的环境变量保存在三个不同的地方
- `/etc/getconfig`文件: 系统中对所有用户都普遍适用的配置。若配置时使用 --system 选项，读写的就是这个文件
- `~/.gitconfig`文件: 用户目录下的配置文件只适用于该用户。若配置时使用 --global 选项，读写的就是这个文件
- `.git/config`文件: 这里的配置仅仅针对当前项目有效

每一个级别的配置都会覆盖上层的相同配置，所以`.git/config`里的配置会覆盖`/etc/gitconfig`中的同名变量

## 用户信息
配置用户名和电子邮件
```
$ git config [--global] user.name "asd"
$ git config [--global] user.email "asd@qq.com"
```

## 默认编辑器
在git commit时，默认使用nano编辑器，如果想把vim设置成git的默认编辑器，可以使用如下命令
```
git config --global core.editor vim
```

## 中文路径显示乱码
使用git status时，如果文件名是中文，会显示形如 274\232\350\256\256\346\200\273\347\273\223.png 的乱码
```
git config --global core.quotepath false
```

## 改变远程库的url
此方法可以用来将一个版本库从https迁移到SSH
`git remote -v`可以查看关联的url
`git remote set-url origin git@xxx.git`更改关联url

## 避免重复登录
使用http关联远程库时，每次pull/push操作都需要输入帐号密码
如果配置下面全局变量，则只需要第一次的时候输入帐号密码，之后就不需要了
```
git config --global credential.helper store
```
## 命令自动补全
由于系统自带的git版本比较低，所以下载了最新版的源码自己编译。但发现自己编译的git不能自动补全
下面是解决命令不能自动不全的方法:
```
cp git-2.9.5/contrib/completion/git-completion.bash ~/.git-completion.bash
```
在~/.bashrc中添加这样一行
```
source ~/.git-completion.bash
```
重新打开终端即可

## 知识
- git命令中，可以使用HEAD~1表示HEAD的上一次提交
