<center><font color="#FFA500" size="6">volatile和CAS</font></center>

[TOC]

# 1 volatile

## 1.1 实例

```java
package com.victory.volatile_test;

import java.util.concurrent.TimeUnit;

public class VolatileTest{
    /*volatile*/
    boolean running=true;
    
    void m(){
        System.out.println("start");
        while(running){}
        System.out.println("end");
    }
    
    public static void main(String[] args)throws InterruptedException{
        VolatileTest vTest = new VolatileTest();
        new Thread(vTest::m,"t").start();
        TimeUnit.SECONDS.sleep(1);
        vTest.running=false;
    }
}
```

