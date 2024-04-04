# 学习和代码实验中的笔记  


在通讯协议中要规定对其方式，避免对齐不一致引发问题。  

大端模式：高字节数据存放在内存低地址处    
大端模式：高字节数据存放在内存高地址处
https://blog.csdn.net/m0_58250087/article/details/126453463

多线程共享变量要添加valotile
int a;
a = i;		//a从内存读取
if(a == i)....;	//a从栈中读取

valotile int a;
a = i;		//a从内存读取
if(a == i)....;	//a从内存读取
https://blog.csdn.net/u010134355/article/details/125058164

i>>1 比 i/2 预算更快