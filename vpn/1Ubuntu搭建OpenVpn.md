## 写在前面
在搬瓦工上租了一个服务器，计划搭建一个VPN
参考了网上不少资料，折腾了2天终于搞定了，做一下备忘吧

参考: [OpenVpn For Ubuntu 16.04](https://help.ubuntu.com/lts/serverguide/openvpn.html)

**环境介绍**：
服务器系统: Ubuntu 16.04
客户端系统: Ubuntu 16.04
版本: OpenVPN 2.3.10

## 基本配置
OpenVpn的技术核心是虚拟网卡，其次是SSL协议实现
安装OpenVpn服务之后，主机上会多出一个名为tun0的虚拟网卡。而客户端在与服务器成功建立SSL连接之后，也会在本地多出一个tun0的虚拟网卡
搭建VPN服务的第一步，我们先使客户端与服务器能正确建立SSL连接

**step1**: 安装openvpn和easy-rsa
在服务器上安装openvpn和easy-rsa
```
$ sudo apt install openvpn easy-rsa
```

**step2**: 复制easy-rsa临时目录到home目录下
```
$ make-cadir ~/openvpn-rsa
```

**step3**: 配置生成证书的所需要的变量
使用文本编辑器打开~/openvpn-rsa/vars，修改如下变量的值
(这些变量具体有什么意义，我也不清楚，大家随便改改吧 o(╯□╰)o)
```
export KEY_COUNTRY="CN"
export KEY_PROVINCE="GD"
export KEY_CITY="ShenZhen"
export KEY_ORG="ORG"
export KEY_EMAIL="me@myhost.mydomain"
export KEY_OU="MyOrganizationalUnit"
export KEY_NAME="EasyRSA"
```

**step4**: 生成CA证书
```
$ cd ~/openvpn-rsa
$ source vars
$ ./clean-all
$ ./build-ca
```

**step5**: 生成服务器证书
```
$ ./build-key-server server
$ ./build-dh
$ cd keys/
$ sudo cp server.crt server.key ca.crt dh2048.pem /etc/openvpn/
```
server是指服务器名，此处可自行更改，为了方便，我把它设为server
此过程中，有几处需要用户确认的地方，根据提示输入回车或者y就行了
网上有些资料提示，server需要与vars文件中的`KEY_NAME`的值保持一致，但亲测貌似没必要

**step6**: 生成客户端证书
```
$ cd ~/openvpn-rsa
$ source vars
$ ./build-key clietn1
```
~/openvpn-rsa/keys目录下会生成client1.crt和client1.key文件，客户端会用到
此处client1可换成自己的名称

**step7**: 配置并启动服务器
为了让OpenVpn起来，我们先简单配置一下
```
$ sudo cp /usr/share/doc/openvpn/examples/sample-config-files/server.conf.gz /etc/openvpn/
$ sudo gzip -d /etc/openvpn/server.conf.gz
```
使用编辑器修改/etc/openvpn/server.conf文件，配置证书和密钥的正确路径
```
ca ca.crt
cert server.crt
key server.key
dh dh2048.pem
```
我们可以通过systemctl命令来启动、关闭或查看OpenVpn状态
```
$ sudo systemctl start/status/stop/restart openvpn@CONFIGFILENAME
```
上面的命令中，CONFIGFILENAME是指配置文件名，我们现在使用的配置文件是server.conf，所以CONFIGFILENAME替换成"server"即可
启动服务之后，我们通过ifconfig会发现一个新的网卡，信息如下
```
tun0      Link encap:UNSPEC  HWaddr 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00  
          inet addr:10.8.0.1  P-t-P:10.8.0.2  Mask:255.255.255.255
          UP POINTOPOINT RUNNING NOARP MULTICAST  MTU:1500  Metric:1
          RX packets:610374 errors:0 dropped:0 overruns:0 frame:0
          TX packets:721198 errors:0 dropped:9706 overruns:0 carrier:0
          collisions:0 txqueuelen:100 
          RX bytes:40928674 (40.9 MB)  TX bytes:927687322 (927.6 MB)``
```

**step8**: 配置客户端
我们还是在服务器PC上生成客户端的配置
```
$ mkdir ~/openvpn-rsa/clients
$ cp /usr/share/doc/openvpn/examples/sample-config-files/client.conf ~/openvpn-rsa/clients/base.conf
```
base.conf就是我们客户端通用的配置文件了
使用编辑器修改客户端配置文件，在上面对应~/openvpn-rsa/clients/base.conf，配置证书和密钥的正确路径以及服务器的地址等信息
```
ca ca.crt
cert client.crt
key client.key
remote vpnserver.example.com 1194
```
把vpnserver.example.com改为服务器的IP或域名，其他需要按上面的填写

**step9**: 打包客户端配置
编辑打包脚本~/openvpn-rsa/clients/make_client_tar.sh
```
#!/bin/bash

if [[ $# != "1" ]] ; then
    echo usage: $0 clientname
    exit 1
fi

KEY_DIR=~/openvpn-rsa/keys
CLIENT=$1

mkdir ${CLIENT}
cp ${KEY_DIR}/ca.crt ${CLIENT}/ca.crt
cp ${KEY_DIR}/${CLIENT}.crt ${CLIENT}/client.crt
cp ${KEY_DIR}/${CLIENT}.key ${CLIENT}/client.key

cp base.conf ${CLIENT}/client.conf

tar -cf ${CLIENT}.tar ${CLIENT}
rm ${CLIENT} -rf
```
修改权限并运行脚本
```
$ cd ~/openvpn-rsa/clients/
$ chmod u+x make_client_tar.sh
$ ./make_client_tar.sh client1
```
则会生成client1.tar打包文件

客户端证书只会在客户端用到，我们还需要把clietn1.tar通过安全的途径传输到客户端
如果只图方便而不考虑安全因素，可以使用python创建一个httpd服务器，然后客户端通过网页下载证书即可
```
$ sudo python2.7 -m SimpleHTTPServer 80
```

**step10**: 启动客户端
在客户端安装openvpn
```
$ sudo apt-get install openvpn
```
把之前打包的文件下载下来之后，解压配置文件
```
$ cd /etc/openvpn/
$ sudo cp ~/Downloads/client1.tar ./
$ sudo tar -xf client1.tar
$ sudo mv client1/* ./
$ sudo rm client1.tar client1 -rf
```
systemctl的使用方式还是一样
```
$ sudo systemctl start/status/stop/restart openvpn@CONFIGFILENAME
```
此处，把CONFIGFILENAME替换成client
启动客户端之后，通过ifconfig同样可以发现一个新网卡，信息如下
```
tun0      Link encap:UNSPEC  HWaddr 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00  
          inet addr:10.8.0.6  P-t-P:10.8.0.5  Mask:255.255.255.255
          UP POINTOPOINT RUNNING NOARP MULTICAST  MTU:1500  Metric:1
          RX packets:0 errors:0 dropped:0 overruns:0 frame:0
          TX packets:4 errors:0 dropped:0 overruns:0 carrier:0
          collisions:0 txqueuelen:100 
          RX bytes:0 (0.0 B)  TX bytes:261 (261.0 B)
```

**step11**: 确认连接是否成功
我们可以通过ping来检查服务器与客户端是否建立连接
```
$ ping -I tun0 10.8.0.1
```
如果能ping通，则说明一切正常
如果你在服务器本地有搭建服务的话，则可以通过tun0来安全访问了
但我们此时还不能通过OpenVpn上外网，使用命令`ping -I tun0 8.8.8.8`是ping不通的
因为数据到了服务器的tun0之后并不能转发出去，我们还需要一些其他配置

## 高级配置
**step1**: 打开ip转发功能
编辑文件/etc/sysctl.conf，去掉下面语句前的#
```
#net.ipv4.ip_forward=1 
```
重载配置
```
$ sudo sysctl -p /etc/sysctl.conf
```

**step2**: 通过iptables配置NAT
创建一个shell脚本`/etc/openvpn/openvpn_nat.sh`用来配置NAT
```
#!/bin/bash

iptables -F
iptables -A FORWARD -o eth0 -i tun0 -s 10.8.0.0/24 -m conntrack --ctstate NEW -j ACCEPT
iptables -A FORWARD -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
iptables -t nat -F POSTROUTING
iptables -t nat -A POSTROUTING -o eth0 -j MASQUERADE
iptables-save
```
其中eth0是服务器连接到外网的网卡
设置脚本权限
```
$ sudo chmod u+x /etc/openvpn/openvpn_nat.sh
```
在/etc/rc.local中设置开机执行脚本
```
/etc/openvpn/openvpn_nat.sh
```

**备注**:
本来打算在/etc/openvpn/server.conf中配置，让脚本在OpenVpn启动时执行的
```
up "/etc/openvpn/openvpn_nat.sh"
```
但测试发现，虽然手动重启OpenVpn时，脚本会被执行
但重启服务器却不会执行脚本

**step3**: 修改服务器配置
使用编辑器修改服务器配置文件/etc/openvpn/server.conf
```
$ push "redirect-gateway def1 bypass-dhcp"
```
使所有客户端把默认网关指向VPN，如果不配置这一项，需要在客户端手动配置路由表

**step4**: 让OpenVpn服务器开机启动
```
$ sudo systemctl enable openvpn@server
```

**step5**: 重启OpenVpn
在服务器上执行
```
$ sudo systemctl restart openvpn@server
```
在客户端执行
```
$ sudo systemctl restart openvpn@client
```

**step6**: 配置客户端DNS服务器
通过以上步骤，如果你能通过tun0 ping通8.8.8.8，那么说明服务器的NAT设置成功了
```
$ ping -I tun0 8.8.8.8
```
但是，如果你还ping不通www.baidu.com，那么你就需要指定默认DNS服务器
编辑/etc/network/interfaces，在文件中添加如下内容
```
dns-nameservers 8.8.8.8 74.82.42.42 8.8.4.4
```
重新加载DNS配置
```
$ sudo systemctl restart networking.service
```
如果成功，/etc/resolv.conf文件中会更新DNS服务器地址
 **step7**: 查看VPN是否正常工作
 在百度中搜索IP，如果显示的是你服务器的IP，则说明VPN正常工作了

## TODO
现在已经能通过VPN正常上(翻)网(墙)了
但是所有的数据都会从VPN过，希望访问国内网站时，能不走VPN
具体要怎么配置还有待研究
如果有知道的朋友，请告知，谢谢
