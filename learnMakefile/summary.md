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

### 条件判断
```
    <conditional-directive>
    <text-if-true>
    endif 
    或
    <conditional-directive>
    <text-if-true>
    else 
    <text-if-true>
    endif
```
ifeq ifneq  ifdef  ifndef 

### 使用函数
语法:
```
    $(<function> <arguments>)
    或 
    ${<function> <arguments>}
```
```
    subst       字符替换函数
    $(subst <from>,<to>,<text>)
    patsubst    模式字符串替换函数 
    $(patsubst <pattern>,<replacement>,<text>)  
    strip       去空格函数 
    $(strip a b c)
    fidstring   查找字符串函数
    $(finstring <find>,<in>)
    filter      过滤函数 
    $(filter <pattern...>,<text>)
    filter-out  反过滤函数 
    #(filter-out <pattern...>,<text>)
    sort        排序函数 
    $(sort <list>)
    word        取单词函数 
    $(word <n>, <text>)
    wordlist    取单词串函数 
    $(wordlist <ss>,<e>,<text>)
    words       单词个数统计函数 
    $(words <text>)
    firstword   首单词函数 
    $(firstword <text>)
    dir         取目录函数 
    $(dir <names...>)
    notdir      取文件函数 
    $(notdir <names...>)
    suffix      取后缀函数 
    $(sufffix <names...>)
    basename    取前缀函数 
    $(basename <namems...>)
    addsuffix   加后缀函数 
    $(addsuffix <suffix>,<names...>)
    addprefix   加前缀函数 
    $(addprefix <prefix>,<anmes...>)
    join        连接函数 
    $(join <list1>, <list2>)
    foreach     
    $(foreach <var>,<list>,<text>)
    if 
    $(if <condition>, <then-part>)
    $(if <condition>, <then-part>, <else-part>)
    call函数
    $(call <expression>,<parm1>,<parm2>,...,<parmn>)
    origin 函数 
    $(origin <variable>)
    shell 函数 
    $(error <text ...>)
```

### 自动化变量
$@ : 表示规则中的目标文件集
$% : 仅当目标是函数库文件中，表示规则中的目标成员名。
$< : 依赖目标中的第一个目标名字。
$? : 所有比目标新的依赖目标的集合。
$^ : 所有的依赖目标的集合。
$+ : 这个变量很像$^ ，也是所有依赖目标的集合。只是它不去除重复的依赖目标、
$* : 这个变量表示目标模式中% 及其之前的部分。