---
- ��Dell������PowerEdge R730�ϰ�װ����ϵͳ
---

ʵ��������㵽����̨���������Ƚ����ʡ����˶Է�����һ�ϲ�ͨ������ѧϰ�˰�װ����ϵͳ����γ��������������Ϥ�������Ĳ������������ڶԷ�������װ����ϵͳ��һ���ܽᡣ

# ��װϵͳ֮ǰ

## ����һ�²��Է������Ļ�������

`DELL 6��E5-2603v4 1.7GHz/8G/1TB SAS 7.2K 3.5/H330/DVDRW/495W�Ȳ��3���ʱ�`

## �����Ҫ��װ�Ĳ���ϵͳ�Ƿ���R730����

������ݵĲ���ϵͳ�汾�����Կ�[����](http://www.dell.com/support/home/cn/zh/cndhs1/drivers/supportedos/poweredge-r730 "R730֧�ֵ�OS")  

���β��Թ��Ĳ���ϵͳ��Microsoft Windows Server 2008 R2 �� Ubuntu 14.04.5 Server(64bit)

## ��װ��ʽ�Լ���װ�������

��װ��ʽ��U���������̣�����ϵͳ��װ��

������������  
[UltralSO](https://ultraiso.en.softonic.com/)  
[Rufus](https://rufus.en.softonic.com/)   

����ϵͳ�����ļ�  
[Microsoft Windows Server 2008 R2](https://msdn.itellyou.cn/)  
[Ubuntu 14.04.5 Server(64bit)](https://www.ubuntu.com/download/alternative-downloads)  

��������--RAID������  

1. ��http://www.dell.com/support/home/cn/zh/cndhs1
2. ������ķ����ǩ���߲�ƷID,���ύ
3. ѡ��������������أ� ����ϵͳѡ��Microsoft Windows Server 2008 R2
4. ����ѡ��Windows 2008R2 Driver 6.603.07.00 for PERC H330/H730/H730P/H830/H730P MX/FD33xD/FD33xS Controllers�� ����ѡ�� SAS RAID�� �Լ���Ҫ���ݾ������ͣ�ѡ����Ӧ��������

# ����1����װMicrosoft Windows Server 2008 R2

����������̣���μ���ƪ[����](http://www.jianshu.com/p/d0ff61a954d8)

���伸�㣬
1. �����ķ�����ֻ��һ��Ӳ�̣��Ǿ�ֻ����RAID0�����������RAID�����Բμ����͵�ϵͳ�ֲᡣ

2. ���״�ĵط�������������ѡ��ע�⣬�ӹ������ص�������exe�ļ�����Ҫ˫�������extract���൱�ڽ�ѹ������Ȼ��õ��������ļ��С�Ȼ�󣬽��������ļ��п�����U���С�
��ѡ��������������ʱ��һ��Ҫѡ����������ļ��У�������Ҫ��γ��ԡ�

PS:����������󣬿���ֱ�Ӱε�U�̣�Ȼ������ȥ�����������µ��������ٴβ��ԡ��Ҳ����˺ü�����

ʱ����Ҫ����ѡ����ʵ�RAID�������档

# ����2����װUbuntu 14.04.5 Server

���尲װ���̣���μ���ƪ[����](https://segmentfault.com/a/1190000005710708)��

һ��ʼ����װװ����Ubuntu 16.04.3 Server����װ�����İ棬��������һ��bug.[���޷���װbusybox-initramfs��](https://jingyan.baidu.com/article/59a015e35d0642f7948865e4.html?qq-pf-to=pcqq.c2c)�����Ƿ�����װUbuntu 16.04.3���İ棬ֱ�Ӱ�װUbuntu 14.04.5 Server��

Ubuntu��װ�����У�û���漰�����������⡣

��װ�����У�������bug��[GRUB installation failed 
](https://askubuntu.com/questions/199049/how-to-fix-a-failing-grub-pc-package-installation-in-hyper-v-virtual-machine)The 'grub-pc' package failed to install into /target/. Without the GRUB boot loader, the installed system will not boot.

һ��ʼ��ֱ����װϵͳ�������ǳ������bug�����google��һ�£�ԭ���ǲ��ϲ������������ߡ�����������ǶϿ����ߡ���Ȼ���ܳ��������������Ҳ�Ƿ��ˡ�

# �����ܽ�

1. �������豸����õĲο����Ͼ��ǹ�����

2. ����bug�Ļ�����Ҫ�����Լ�������⣬�����Լ����а��ս��������⡣������õİ취�ǿ��������ǲ������˳������Ƶ������

# ���������DELL��������صĳ�����ַ

DELL��������֧��   ������������ĵ�+����
http://www.dell.com/support/home/cn/zh/cndhs1

DELL������R730��Ʒ�����ֲ�
http://www.dell.com/support/manuals/cn/zh/cndhs1/poweredge-r730/r730_ompublication/dell-poweredge-r730-%E7%B3%BB%E7%BB%9F%E6%A6%82%E8%A7%88?guid=guid-4e82e765-cb70-458f-87a7-eadd87c62ed2&lang=zh-cn

��U�������̸�Dell������װϵͳ�Ҳ���RAID���н���취
http://blog.csdn.net/u014326004/article/details/78067603

ubuntu�������ط��������ַ
https://www.ubuntu.com/download/alternative-downloads

����--R730���� �ֲ���ĵ�
http://www.dell.com/support/home/cn/zh/cndhs1/product-support/product/poweredge-r730/manuals

ͨ��ʹ��Rufus����������USB�豸������Dell PowerEdge������
http://www.dell.com/support/article/cn/zh/cndhs1/sln296810/%E9%80%9A%E8%BF%87%E4%BD%BF%E7%94%A8rufus%E5%88%9B%E5%BB%BA%E5%8F%AF%E5%BC%95%E5%AF%BCusb%E8%AE%BE%E5%A4%87%E6%9D%A5%E6%9B%B4%E6%96%B0dell-poweredge%E6%9C%8D%E5%8A%A1%E5%99%A8?lang=zh








