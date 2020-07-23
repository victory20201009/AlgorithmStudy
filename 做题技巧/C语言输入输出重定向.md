在C语言中更改流的指向，可以更好的输入数据，模板代码如下：

```c++
#include<stdio.h>
#include <stdlib.h>
#define  OPEN_STREAM_REDIRECT
const char IN_STREAM_FILE[] = "xxx";
const char OUT_STREAM_FILE[] = "xxx";

int _main(int argc,char** argv){
    printf("hello");
}

int main(int argc,char** argv){
    #ifdef OPEN_STREAM_REDIRECT
    if(!freopen(IN_STREAM_FILE,"r",stdin)){
        printf("in stream redirect error");
        exit(-1);
    }
    /**
    *  输出重定向会把源文件清空
    */
    if(!freopen(OUT_STREAM_FILE,"w",stdout)){
        printf("out stream redirect error");
        exit(-2);
    }
    #endif

    // TODO 写代码的地方
    _main(argc,argv);

    #ifdef OPEN_STREAM_REDIRECT
    fclose(stdin);
    fclose(stdout);
    #endif

    return 0;
}

```

