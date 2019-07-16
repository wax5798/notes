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

# Firefox 不能播放斗鱼直播的问题
前一段时间，我把 Ubuntu 14.04 升级到了 Ubuntu 16.04，发现我的 Firefox 不能播放斗鱼直播了。
通过 F12 打开调试信息，发现这样的打印
> The video on this page can’t be played. Your system may not have the required video codecs for: video/mp4; codecs="avc1.42E01E mp4a.40.2", audio/mp4; codecs="mp4a.40.2", video/mp4; codecs="avc1.64001f", audio/mp4; codecs="mp4a.40.2", video/mp4; codecs="avc1.64001f", audio/mp4; codecs="mp4a.40.2", video/mp4; codecs="avc1.64001f", audio/mp4; codecs="mp4a.40.2", video/mp4; codecs="avc1.64001f"

解决办法:
安装 ffmpeg
```
sudo apt-get install ffmpeg
```

然后重启 Firefox

