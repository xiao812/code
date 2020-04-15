### 组成部分
显示规则    隐晦规则  变量定义  文件指示    注释

### 规则 
```
    target ... : prerequisites ...
        command
``` 
当 prerequistis 中有任一个文件比 target 新时， 执行 command
命令前有一个 Tab 字符 

### 使用变量 
相当于宏定义
```
    objects = main.o kbd.o search.o
    edit = $(objects)
        cc -o edit $(objects)
```

### 自动推导
自动推导： 有.o 自动推导 CC -c .c 

### 清空目标文件 
``` 
    .PHONY : clean 
    clean : 
        -rm edit $(objects)
```
### 导入其他Makefile 
#include 

### 通配符 
    *  ?   ~
```
    objects = *.o   # 不会展开
    objects = $(wildcard *.o)   # 会展开 
```

### 文件搜寻
```
    VPATH = src:../headers 
```
vpath <pattern> <directories> 为符合模式<pattern> 的文件指定搜索目录<directories>。
vpath <pattern> 清除符合模式<pattern> 的文件的搜索目录。
vpath 清除所有已被设置好了的文件搜索目录。

### 伪目标
    .PHONY 

### 多目标 

### 静态模式
``` 
    objects = foo.o bar.o 
    all : $(objects)
    $(objects): %.o : %.c 
        $(CC) -c $(CFLAGS) $ < -o $@
    # 等价于 
    foo.o : foo.c 
        $(CC) -c $(CFLAGS) foo.c -o foo.o 
    bar.o : bar.c 
        $(CC) -c $(CFLAGS) bar.c -o bar.o 
```

### 自动生成依赖性
    -M 和 -MM

### 嵌套执行make
```
    subsystem:
    cd subdir && $(MAKE)
    或
    subsystem:
    $(MAKE) -C subdir
```

### 关键字
    wailcard 
    override
    define

### 目标变量 
### 模式变量
