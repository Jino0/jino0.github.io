# Mac+hugo+github搭建个人博客


添加字数统计
作为一个静态网页生成器，Hugo 为使用者提供了很多与网页相关的模板变量，而与文章字数相关的模板变量有两个：

.FuzzyWordCount: 文章内容的大致单词数 (字数)
.WordCount: 文章内容的单词数 (字数)
我们可以看到 .FuzzyWordCount 提供的是一个大概的值 (整 100)，比如 1 个字算 100 字，2 个字还算 100 字，201 个字算 200 字。这样统计出来的字数可能会比实际情况更多一点，虽然更有牌面但全都是整数未免也太假了。所以我还是决定使用 .WordCount。

image-20200816082207539

参考用法，在html文件中任意位置添加:

{{ .FuzzyWordCount }} Words | Read in about {{ .ReadingTime }} Min
更多与模板变量相关信息请参考：Variables and Params

终极优化，部署博客到阿里云oss
部署博客有很多选择，国内外都有很多服务可以用，各有各的优缺点：

GithubPages	码云Pages	Netlify	Heroku	阿里云OSS
纯静态托管	是	是	是	否👍	是
CDN加速	否	否	是👍	否	是👍
访问速度	慢	快👍	一般	一般	很快👍
支持404重定向	否	是👍	是👍	是👍	是👍
自定义重定向	否	否	是👍	是👍	否
具体选择哪个，根据个人对博客的需求进行选择。
