### 中文路径显示乱码
使用git通常都会遇到这样的问题，git显示中文路径会出现乱码，比如这样：
```
ntracked files:
  (use "git add <file>..." to include in what will be committed)

	"1\346\210\221\347\232\204git\351\205\215\347\275\256.md"
```
**解决办法**: `git config --global core.quotepath false`

### .gitignore配置
