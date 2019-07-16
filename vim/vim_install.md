<head><meta charset="UTF-8"></head>
<style>
h1 {
    text-align: center;
}
</style>

## 环境
系统: ubuntu 16.04

## 安装库
sudo apt install libncurses5-dev libgnome2-dev libgnomeui-dev libgtk2.0-dev libatk1.0-dev libbonoboui2-dev libcairo2-dev libx11-dev libxpm-dev libxt-dev python-dev ruby-dev lua5.1 liblua5.1-dev libperl-dev git

## 移除已安装的 vim
sudo apt-get remove vim-common vim-runtime vim-gui-common

https://github.com/ycm-core/YouCompleteMe/wiki/Building-Vim-from-source
ftp://ftp.vim.org/pub/vim/unix/

## 配置
./configure --with-features=huge \
            --enable-multibyte \
	    --enable-rubyinterp=yes \
	    --enable-pythoninterp=yes \
	    --with-python-config-dir=/usr/lib/python2.7/config-x86_64-linux-gnu \
	    --enable-perlinterp=yes \
	    --enable-luainterp=yes \
            --enable-gui=gtk2 \
            --enable-cscope \
	   --prefix=/usr/local

--with-python-config-dir 一定要根据本机配置

## 编译安装
make VIMRUNTIMEDIR=/usr/local/share/vim/vim81
sudo make install
