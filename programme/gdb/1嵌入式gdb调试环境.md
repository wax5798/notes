采用GDB方法调试，由于嵌入式系统资源有限性，一般不能直接在目标系统上进行调试，通常采用gdb+gdbserver的方式进行调试。目标系统必须包括gdbserver程序，宿主机也必须安装gdb程序。在此我们还不能直接采用linux发行版自带的gdb，需要交叉编译gdb和gdbserver。

可以到ftp://ftp.gnu.org/gnu/gdb下载源代码
以7.7.1为例，下载并解压到~/tools/gdb目录下，并在此路径下创建如下文件夹：
`build-7510`, `buildroot-gcc342`, ` gdb-7.7.1`, `obj-gdb`, `obj-gdbserver`

build-7510为安装路径，buildroot-gcc342为tool-chain, obj-gdb为gdb编译目录，obj-gdbserver为gdbserver编译目录

在obj-gdb目录下创建脚本 build.7510
``` sh
#!/bin/bash

PATH=${PATH}:/home/tplink/tools/gdb/buildroot-gcc342/bin
export PATH

../gdb-7.7.1/configure --target=mipsel-linux --enable-shared --prefix=/home/tplink/tools/gdb/build-7510 --without-x --disable-gdbtk --disable-tui --without-included-regex --without-included-gettext

make 

make install
```

在obj-gdbserver目录下创建脚本 build.7510
``` sh
#!/bin/bash

PATH=${PATH}:/home/tplink/tools/gdb/buildroot-gcc342/bin
export PATH

CC=mipsel-linux-gcc

../gdb-7.7.1/gdb/gdbserver/configure --host=mipsel-linux --without-included-regex --without-included-gettext

make

cp gdbserver ../build-7510/bin
```
注意：此处编译时有提示警告，在Makefile中去掉-static的选项即可

此时,~/tools/gdb/build-7510/bin路径下生成`gdbserver`, `mipsel-linux-gdb`, `mipsel-linux-run`三个文件

把gdbserver拷贝到开发板， 执行./gdbserver 192.168.0.10:1234 ./test
在宿主机运行 mipsel-linux-gcc ./test
然后执行(gdb)target remote 192.168.0.100:1234 连接到gdbserver
然后执行(gdb) set sysroot path... 连接到gdbserver

如果出现错误提示GDB can't find the start of the function at 的错误，可以尝试set sysroot 命令,指定开发板的根目录




