# 使用xkb修改按键映射

## 目的
由于使用vim时，经常要用到ESC键。奈何ESC键距离太远，操作起来很不方便，所以想把ESC键映射到CAPS键，而以前的CAPS则映射到右CTRL
最初的想法是使用xmodmap，但配置好了之后才发现xmodmap与fcitx有兼容性问题（ibus也有同样的问题）。
关于这一点还专门到fcitx的github上提了issue，但得到的回复是， _不建议使用xmodmap，建议使用xkb_ 。
记录下我的配置步骤，备忘

## 步骤
1、查看当前键盘布局 `setxkbmap -print`
```
xkb_keymap {
	xkb_keycodes  { include "evdev+aliases(qwerty)"	};
	xkb_types     { include "complete"	};
	xkb_compat    { include "complete"	};
	xkb_symbols   { include "pc+us+inet(evdev)"	};
	xkb_geometry  { include "pc(pc105)"	};
};
```
`xkb_symbols`属性后面的pc即我们需要修改的文件，**修改前务必做好备份**

2、使用编辑器打开`/usr/share/X11/xkb/symbols/pc`，修改如下内容
```
- key <CAPS> {    [ Caps_Lock     ]   };
+ key <CAPS> {    [ Escape        ]   };
 .
 .
 .
- key <RCTL> {    [ Control_R     ]   };
+ key <RCTL> {    [ Caps_Lock     ]   };
```

3、保存文件并重新登录桌面
