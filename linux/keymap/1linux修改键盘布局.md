参考自 [[http://blog.csdn.net/robertsong2004/article/details/36439597][xmodmap使用指南]]
* 理解xmodmap
  xmodmap 是一个在 X 图形环境下用于修改键盘和鼠标按钮映射的工具

  系统处理键盘输入的流程：
  - 键盘中的一个按键被按下时，会产生一个“信号”传给操作系统。
  - 操作系统得到这个信号之后，检查此信号对应的处理方法。
  - 执行对应的处理方法。
** keycode
   keycode即键盘产生的信号，比如我们按下a这个按钮产生的keycode是28。
** 处理方法
   我们使用 =xmodmap -pke= 可以查看当前的keymap表，显示结果的格式如下
   #+BEGIN_SRC 
   keycode  54 = c C c C
   #+END_SRC
   等号左边是按键产生的keycode，右边是keycode对应的处理方法。最多能有8种处理方法。以keycode 54为例，单独按下按键，处理方法为输入小写的c(第一种方法)，按下shift同时按下c，处理方法为输入大写的C(第二种方法)。至于其他方法基本没有接触，无需关注。
   如果我们需要修改keycode与行为之间的映射关系可以执行如下命令
   #+BEGIN_SRC sh
   xmodmap -e "keycode 38 = c C c C"
   #+END_SRC
   即按键a能产生按键c的效果
** 修饰键行为
   修饰键即为alt， ctrl等按键。
   我们先使用命令 =xmodmap= 来查看修饰方法
   #+BEGIN_SRC 
   $ xmodmap 
   xmodmap:  up to 4 keys per modifier, (keycodes in parentheses):

   shift       Shift_L (0x32),  Shift_R (0x3e)
   lock        Caps_Lock (0x42)
   control     Control_L (0x25),  Control_R (0x69)
   mod1        Alt_L (0x40),  Alt_R (0x6c),  Meta_L (0xcd)
   mod2        Num_Lock (0x4d)
   mod3      
   mod4        Super_L (0x85),  Super_R (0x86),  Super_L (0xce),  Hyper_L (0xcf)
   mod5        ISO_Level3_Shift (0x5c),  Mode_switch (0xcb)
   #+END_SRC
   以lock为例，keycode 0x42对应着Caps_Lock行为，Caps_Lock行为绑定在lock方法上，lock方法被触发则会切换大小写 
   
   那么我们怎样才能修改修饰行为呢？下面以右ctrl替换caps为例
   #+BEGIN_SRC sh
   # 解除按键Control_R与修饰行为control的绑定
   xmodmap -e "remove Control = Control_R"
   # 105为按键右ctrl的keycode
   xmodmap -e "keycode 105 = Caps_Lock NoSymbol Caps_Lock"
   # 把Caps_Lock绑定到lock
   xmodmap -e "add Lock = Caps_Lock"
   #+END_SRC
   更改之后的结果
   #+BEGIN_SRC
   $ xmodmap 
   xmodmap:  up to 4 keys per modifier, (keycodes in parentheses):

   shift       Shift_L (0x32),  Shift_R (0x3e)
   lock        Caps_Lock (0x42),  Caps_Lock (0x69)
   control     Control_L (0x25)
   mod1        Alt_L (0x40),  Alt_R (0x6c),  Meta_L (0xcd)
   mod2        Num_Lock (0x4d)
   mod3      
   mod4        Super_L (0x85),  Super_R (0x86),  Super_L (0xce),  Hyper_L (0xcf)
   mod5        ISO_Level3_Shift (0x5c),  Mode_switch (0xcb)
   #+END_SRC
   现在按键capslock和右ctrl都能触发lock修饰方法

* 我的配置
  如下是对我的poker的配置：
  - Caps功能移至右ctrl按键
  - Esc功能移至Caps按键
  - `~功能移至Esc按键
** 使用shell脚本
    以下是我的配置脚本
    #+BEGIN_SRC sh
    #!/bin/bash

    # keycode 105 = Control_R NoSymbol Control_R
    # keycode  66 = Caps_Lock NoSymbol Caps_Lock
    # keycode   9 = Escape NoSymbol Escape
    # keycode  49 = grave asciitilde grave asciitilde
    if [ "$1"x == "default"x ]; then
    echo "set xmodmap to default"
    xmodmap -e "remove Lock = Caps_Lock"
    xmodmap -e "keycode 105 = Control_R NoSymbol Control_R"
    xmodmap -e "keycode  66 = Caps_Lock NoSymbol Caps_Lock"
    xmodmap -e "keycode   9 = Escape NoSymbol Escape"
    xmodmap -e "keycode  49 = grave asciitilde grave asciitilde"
    xmodmap -e "add Lock = Caps_Lock"
    xmodmap -e "add Control = Control_R"
    else
    echo "set xmodmap"
    xmodmap -e "remove Control = Control_R"
    xmodmap -e "remove Lock = Caps_Lock"
    xmodmap -e "keycode 105 = Caps_Lock NoSymbol Caps_Lock"
    xmodmap -e "keycode 66 = Escape NoSymbol Escape"
    xmodmap -e "keycode 9 = grave asciitilde grave asciitilde"
    xmodmap -e "add Lock = Caps_Lock"
    fi
    #+END_SRC

** TODO 使用配置文件
   理论上，把配置信息写在~/.Xmodmap中，启动的时候会被自动加载。
    #+BEGIN_SRC 
    remove Control = Control_R
    remove Lock = Caps_Lock
    keycode 105 = Caps_Lock NoSymbol Caps_Lock
    keycode 66 = Escape NoSymbol Escape
    keycode 9 = grave asciitilde grave asciitilde
    add Lock = Caps_Lock
    #+END_SRC
   但貌似启动的时候会xmodmap配置会被重置，为了解决这个问题，我在~/.profile中添加了如下命令 =sleep 10 && xmodmap ~/.Xmodmap &= 

   如果配置文件不能生效，可以参考这篇文章，/可能/有帮助: [[http://blog.chinaunix.net/uid-13189580-id-3048310.html][Ubuntu自定义键位xmodmap ]]

   PS: 我在使用ibus的时候，每次切换输入法，xmodmap的配置都会被重置，所以改用了fcitx
