## 修改root密码
在 搬瓦工 买了一个服务器，root的登录密码是自动生成的，而且比较复杂。所以想重新设置root的密码
```
root@ubuntu:~# passwd root
Enter new UNIX password: 
Retype new UNIX password: 
passwd: password updated successfully
```

## 添加普通用户
搬瓦工服务器默认只有一个root账户，安全起见，需要添加一个普通用户
```
root@ubuntu:~# adduser sadmin
```
之后按提示填写密码等信息即可
然后在root用户下执行`visudo`，并在`root ALL=(ALL:ALL) ALL`下添加`sadmin ALL=(ALL:ALL) ALL`
