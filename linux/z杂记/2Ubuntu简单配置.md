<head><meta charset="UTF-8"></head>
<style>
h1 {
    text-align: center;
    border-left: 5px solid #e86422;
    border-right: 5px solid #e86422;
}
h2 {
    border-left: 5px solid #ff7f00;
    border-right: 5px solid #ff7f00;
    padding-left: 10px;
}
h3 {
    border-left: 5px solid #e86422;
    padding-left: 8px;
}
h4 {
    border-left: 3px solid #f0a000;
    padding-left: 5px;
}
</style>

# Ubuntu 简单配置
由于手贱，几次搞坏 Ubuntu 系统，不得不重装
但每次重装之后，都要重新配置系统，然后就是不停的百度操作方法
这次根据个人的使用习惯，把 Ubuntu 的配置过程记录下来

## 关闭 ALT 快捷键
由于使用 vim，许多功能映射都需要 alt 键来完成
然而 alt 已经被系统定义为了 HUD 快捷键
那么怎么关闭掉系统的 alt 快捷键呢

System Settings -> Keyboard -> Shortcuts -> Launchers -> Key to show the HUD

此处，我们可以把 HUD 快捷键关闭掉，或者映射到其他键(比如右 alt)

## 更改键位映射
使用 vim 时，默认的键盘布局感觉很部方便，此时就需要修改键盘映射了
关于修改键盘映射，参见这篇文章吧 [buntu使用xkb修改按键映射](https://blog.csdn.net/weixin_40407199/article/details/79234552)

## 设置终端主题
由于不喜欢 Ubuntu 默认的紫红色终端主题，重设终端主题
1. 打开一个终端
2. 选择左上角的 Edit -> Profile Preferences -> Colors
3. 取消 "Use color from system theme" 复选框
4. Text and Background Color -> Build-in schemes 选择 "Solarized dark" (即 Text color - #839496, Bolod color - Same as text color, Background color - #002B36)
5. Palette -> Build-in schemes 选择 Linux console

## 隐藏侧边栏
码代码的时候，喜欢 vim 显示尽量宽一些，所以需要隐藏侧边栏
1. 右键 Ubuntu 主界面，选择 "Change Desktop Background"
2. 把 Behavior -> Auto-hide the Launchers 设置为 ON

这样侧边栏就会自动隐藏了，当把鼠标靠在左边并且移动时，会自动显示出来
另外，按 win 键也会显示侧边栏

## 修改默认提示符
当你的工作目录比较深入的时候，提示符就会很长，甚至占了足足一行，这样看起来很不习惯
使用 `echo ${PS1}` 命令查看 PS1 的值
```
\[\e]0;\u@\h: \w\a\]${debian_chroot:+($debian_chroot)}\u@\h:\w\$
```
我们只需要把最后一个小写的 w 改为大写即可
所以可以在 `~/.bashrc` 中添加这么一行
```
export PS1="\[\e]0;\u@\h: \w\a\]${debian_chroot:+($debian_chroot)}\u@\h:\W\$"
```

## 添加 `~/bin` 到 PATH
为了方便，经常会写一些脚本放在 `~/bin` 目录下，所以需要把 `~/bin` 添加到 PATH 变量中
在 `~/.bashrc` 中添加这么一行
```
export PATH=${PATH}:~/bin
```

