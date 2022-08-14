---
title: "Mac+hugo+github搭建个人博客"
date: 2022-08-05T14:37:23+08:00
lastMod: 2022-08-14T15:10:23+08:00

draft: false
tags: ["hugo"]
categories: ["hugo"]
series: ["hugos"]
---

使用 mac+hugo+github 搭建个人博客。

## 准备工作

### brew安装

```安装命令
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```
### github
github上创建一个仓库，仓库的名称格式一定是：**username.github.io**

## 安装步骤
### hugo 安装
打开终端 输入命令,直接按住那个 hugo,在已安装 homebrew 的环境下。

brew 命令可直接检测是否已成功安装 brew,当出现 Example usage: 等信息的情况下，即已成功安装 brew。

```
brew install hugo
hugo version        // 可查看是否已经安装好。
```
### 创建总目录

```
hugo new site myblog
```
最后一个单词 myblog 为在当前目录下生成文件夹名，也是你的网站的大本营，后续大部分的操作都在这个文件夹下进行。

### 配置主题

可在 [hugo 官网](https://themes.gohugo.io/) 主题进行下载主题,下载的主题要放在博客根目录的 themes 目录下。

以 [hugo-theme-even](https://github.com/olOwOlo/hugo-theme-even) 为 🌰

```
git init
git clone https://github.com/olOwOlo/hugo-theme-even themes/even  
```
按着主题中的 .toml 文件修改 myBlog 中的 .toml 文件，因为需要给主题设置些参数。

一定好好研究主题中的 .toml 文件或直接 copy 过来。

### 本地运行
```
hugo server -t theme-name --buildDrafts
```

其中 **theme-name** 为你下载的主题名称,如果没问题就会提示成功的信息，给出本地调试链接:localhost:1313,此时终端会持续运行，不会结束。

浏览器打开 localhost:1313 ，如果能正常显示，说明在本地服务器运行已经没问题。

### 显示文章

如要在网页上显示文章，在根目录下的 content–>post 中生成一个 .md 文件，此时将写好的文章 copy 至此文件中，可再按照上一条命令进行测试。

输入命令创建即可

```
hugo new post/readme.md
```

### 在github上测试

首先在github上创建好仓库，注意事项见“准备工作”。

在根目录下输入命令
```
hugo --theme=theme-name --baseUrl="https://username.github.io/" --buildDrafts，
```
此命令会在根目录下生成一 public 的文件夹，里面存放的就是生成的网页的代码。

接下来需要将这个目录上传至建好的仓库中，在 public 目录下依次使用命令:
```
git init
git add .
git commit -m "init"
git remote add origin https://github.com/username/username.github.io.git
git push -u origin master
```
最后一个命令输完后可能需要 github 密码, 需要到 GitHub 中申请个人令牌

经过以上操作后，在网页中访问 https://username.github.io/即可看到搭建后的网页
