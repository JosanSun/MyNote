---
- 在Dell服务器PowerEdge R730上安装操作系统
---

实验室最近搞到了两台服务器，比较新鲜。本人对服务器一窍不通，首先学习了安装操作系统跟拆拔常见组件。慢慢熟悉服务器的操作方法。现在对服务器安装操作系统做一个总结。

# 安装系统之前

## 介绍一下测试服务器的基本配置

`DELL 6核E5-2603v4 1.7GHz/8G/1TB SAS 7.2K 3.5/H330/DVDRW/495W热插拔3年质保`

## 检查所要安装的操作系统是否与R730兼容

具体兼容的操作系统版本，可以看[官网](http://www.dell.com/support/home/cn/zh/cndhs1/drivers/supportedos/poweredge-r730 "R730支持的OS")  

本次测试过的操作系统有Microsoft Windows Server 2008 R2 和 Ubuntu 14.04.5 Server(64bit)

## 安装方式以及安装组件下载

安装方式：U盘做引导盘，进行系统安装。

制作引导工具  
[UltralSO](https://ultraiso.en.softonic.com/)  
[Rufus](https://rufus.en.softonic.com/)   

操作系统镜像文件  
[Microsoft Windows Server 2008 R2](https://msdn.itellyou.cn/)  
[Ubuntu 14.04.5 Server(64bit)](https://www.ubuntu.com/download/alternative-downloads)  

驱动程序--RAID控制器  

1. 打开http://www.dell.com/support/home/cn/zh/cndhs1
2. 输入你的服务标签或者产品ID,点提交
3. 选择驱动程序和下载， 操作系统选择Microsoft Windows Server 2008 R2
4. 名称选择，Windows 2008R2 Driver 6.603.07.00 for PERC H330/H730/H730P/H830/H730P MX/FD33xD/FD33xS Controllers。 类型选择， SAS RAID。 自己需要根据具体类型，选择相应的驱动。

# 样例1：安装Microsoft Windows Server 2008 R2

具体操作流程，请参见这篇[文章](http://www.jianshu.com/p/d0ff61a954d8)

补充几点，
1. 如果你的服务器只有一个硬盘，那就只能组RAID0。具体如何组RAID，可以参见附送的系统手册。

2. 容易错的地方，就是驱动的选择。注意，从官网下载的驱动是exe文件，需要双击，点击extract（相当于解压缩）。然后得到驱动的文件夹。然后，将驱动的文件夹拷贝到U盘中。
在选择加载驱动程序的时候，一定要选择最里面的文件夹，可能需要多次尝试。

PS:如果驱动错误，可以直接拔掉U盘，然后重新去官网下载最新的驱动，再次测试。我测试了好几个。

时间主要卡在选择合适的RAID驱动上面。

# 样例2：安装Ubuntu 14.04.5 Server

具体安装过程，请参见这篇[文章](https://segmentfault.com/a/1190000005710708)。

一开始，安装装的是Ubuntu 16.04.3 Server，安装的中文版，但是遇到一个bug.[“无法安装busybox-initramfs”](https://jingyan.baidu.com/article/59a015e35d0642f7948865e4.html?qq-pf-to=pcqq.c2c)。于是放弃安装Ubuntu 16.04.3中文版，直接安装Ubuntu 14.04.5 Server。

Ubuntu安装过程中，没有涉及到驱动的问题。

安装过程中，遇到了bug。[GRUB installation failed 
](https://askubuntu.com/questions/199049/how-to-fix-a-failing-grub-pc-package-installation-in-hyper-v-virtual-machine)The 'grub-pc' package failed to install into /target/. Without the GRUB boot loader, the installed system will not boot.

一开始，直接重装系统，但还是出现这个bug。最后，google了一下，原来是插上不能联网的网线。解决方法就是断开网线。居然还能出现这种情况，我也是服了。

# 经验总结

1. 遇到新设备，最好的参考资料就是官网。

2. 遇到bug的话，不要尝试自己解决问题，除非自己很有把握解决这个问题。否则，最好的办法是看看网上是不是有人出现类似的情况。

# 个人整理的DELL服务器相关的常用网址

DELL官网服务支持   可以下载相关文档+驱动
http://www.dell.com/support/home/cn/zh/cndhs1

DELL服务器R730产品介绍手册
http://www.dell.com/support/manuals/cn/zh/cndhs1/poweredge-r730/r730_ompublication/dell-poweredge-r730-%E7%B3%BB%E7%BB%9F%E6%A6%82%E8%A7%88?guid=guid-4e82e765-cb70-458f-87a7-eadd87c62ed2&lang=zh-cn

用U盘启动盘给Dell服务器装系统找不到RAID阵列解决办法
http://blog.csdn.net/u014326004/article/details/78067603

ubuntu官网下载服务器版地址
https://www.ubuntu.com/download/alternative-downloads

官网--R730所有 手册和文档
http://www.dell.com/support/home/cn/zh/cndhs1/product-support/product/poweredge-r730/manuals

通过使用Rufus创建可引导USB设备来更新Dell PowerEdge服务器
http://www.dell.com/support/article/cn/zh/cndhs1/sln296810/%E9%80%9A%E8%BF%87%E4%BD%BF%E7%94%A8rufus%E5%88%9B%E5%BB%BA%E5%8F%AF%E5%BC%95%E5%AF%BCusb%E8%AE%BE%E5%A4%87%E6%9D%A5%E6%9B%B4%E6%96%B0dell-poweredge%E6%9C%8D%E5%8A%A1%E5%99%A8?lang=zh








