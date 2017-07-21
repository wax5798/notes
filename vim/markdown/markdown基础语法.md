
[TOC]

# 概述
## Markdown 参考文档
> <http://wowubuntu.com/markdown/index.html>

## 兼容HTML

不在 Markdown 涵盖范围之内的标签，都可以直接在文档里面用 HTML 撰写。不需要额外标注这是 HTML 或是 Markdown；只要直接加标签就可以了。
要制约的只有一些 HTML 区块元素――比如 `<div>`、`<table>`、`<pre>`、`<p>` 等标签，必须在前后加上空行与其它内容区隔开，还要求它们的开始标签与结尾标签不能用制表符或空格来缩进。HTML 的区段（行内）标签如 `<span>`、`<cite>`、`<del>` 可以在 Markdown 的段落、列表或是标题里随意使用。

例子如下：

    This is a paragraph

    <table>
        <tr>
            <td>Foo</td>
        </br>
    </table>

    This is another paragraph
请注意，在 HTML 区块标签间的 Markdown 格式语法将不会被处理。

# 区块元素
## 标题
在行首插入1到6个#，对应1到6阶，例如：

    # This is H1
    ## This is H2
    ###### This is H6

## 区块引用
Markdown 可以通过两种方式来建立区块引用：
1. 在每一行前面加上 >
2. 在整个段落第一行最前面加上 >

区块引用可以嵌套，并且区块内也可以使用其他 Markdown 语法
例子如下：

    > first level of quoting
    > 
    > > nested blockquote
    > 
    > * list1
    > * list2

## 列表
无序列表使用星号、加号或是减号作为列表标记。
有序列表使用数字接着一个英文句点。而且这里列表标记上使用的数字并不会影响输出 HTML 的结果。
列表项目可以包含多个段落，每个项目下的段落都必须缩进 4 个空格或是 1 个制表符
如果要在列表项目内放进引用，那 > 就需要缩进
如果要放代码区块的话，该区块就需要缩进两次，也就是 8 个空格或是 2 个制表符

    * first level list
        * second level list
            > quote
        * second level list
            1. third level list
                    code

## 代码区块
要在 Markdown 中建立代码区块很简单，只要简单地缩进 4 个空格或是 1 个制表符就可以（需要与前面的内容保持至少一个空行）
一个代码区块会一直持续到没有缩进的那一行（或是文件结尾）

    This is a normal paragraph

        This is code

## 分隔线
你可以在一行中用三个以上的星号、减号、底线来建立一个分隔线，行内不能有其他东西。你也可以在星号或是减号中间插入空格。


# 区段元素
## 链接
Markdown 支持两种形式的链接语法： 行内式和参考式两种形式。
要建立一个行内式的链接，只要在方块括号后面紧接着圆括号并插入网址链接即可，如果你还想要加上链接的 title 文字，只要在网址后面，用双引号把 title 文字包起来即可。如果你是要链接到同样主机的资源，你可以使用相对路径

    网址链接 [link](http://www.baidu.com "baidu")
    本地资源 [local](/usr/include/stdio.h)

参考式的链接是在链接文字的括号后面再接上另一个方括号，而在第二个方括号里面要填入用以辨识链接的标记

    This is [an example][id] reference-style link.
接着，在文件的任意处，你可以把这个标记的链接内容定义出来

    [id]: http://example.com/  "Optional Title Here"
网址定义只有在产生链接的时候用到，并不会直接出现在文件之中。
链接辨别标签可以有字母、数字、空白和标点符号，但是并不区分大小写
链接内容定义的形式为：
* 方括号（前面可以选择性地加上至多三个空格来缩进），里面输入链接文字
* 接着一个冒号
* 接着一个以上的空格或制表符
* 接着链接的网址
* 选择性地接着 title 内容，可以用单引号、双引号或是括弧包着

隐式链接标记功能让你可以省略指定链接标记，这种情形下，链接标记会视为等同于链接文字，要用隐式链接标记只要在链接文字后面加上一个空的方括号，如果你要让 "Google" 链接到 google.com

    [Google][]
    [Google]: http://google.com/

## 强调
Markdown 使用星号（`*`）和底线（`_`）作为标记强调字词的符号，被 `*` 或 `_` 包围的字词会被转成用 `<em>` 标签包围，用两个 `*` 或 `_` 包起来的话，则会被转成 `<strong>`
但是如果你的 `*` 和 `_` 两边都有空白的话，它们就只会被当成普通的符号。
如果要在文字前后直接插入普通的星号或底线，你可以用反斜线

    *斜体*
    **粗体**
    ~~删除线~~
    \*文本\*

## 代码
如果要标记一小段行内代码，你可以用反引号把它包起来（\`）
如果要在代码区段内插入反引号，你可以用多个反引号来开启和结束代码区段

    Use the `printf()` function.
    ``There is a literal backtick (`) here.``

使用 "\`\`\`" + "语言名称" 加强代码块标记
示例1： C 语言

    ``` c
    int main()
    {
        return 0
    }
    ```
示例2： 流程图

``` flow
st=>start: Start
e=>end: End
op=>operation: My Operation
cond=>condition: Yes or No?

st->op->cond
cond(yes)->e
cond(no)->op
```
示例3： 时序图

    ``` sequence
    Alice->Bob: Hello Bob, how are you?
    Note right of Bob: Bob thinks
    Bob-->Alice: I am good thanks!
    ```

## 图片
Markdown 使用一种和链接很相似的语法来标记图片，同样也允许两种样式： 行内式和参考式

    ![Alt text](/path/to/img.jpg)
    ![Alt text](/path/to/img.jpg "Optional title")

    ![Alt text][id]
    [id]: url/to/image  "Optional title attribute"

# 其他
## 自动链接
Markdown 支持以比较简短的自动链接形式来处理网址和电子邮件信箱，只要是用尖括号包起来， Markdown 就会自动把它转成链接。一般网址的链接文字就和链接地址一样

    <http://example.com/>

## 反斜杠
Markdown 可以利用反斜杠来插入一些在语法中有其它意义的符号
Markdown 支持以下这些符号前面加上反斜杠来帮助插入普通的符号

    \   反斜线
    `   反引号
    *   星号
    _   底线
    {}  花括号
    []  方括号
    ()  括弧
    #   井字号
    +   加号
    -   减号
    .   英文句点
    !   惊叹号

