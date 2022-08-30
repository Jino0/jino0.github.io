---
title: "常用数据类型"
subtitle: ""
date: 2022-08-18T20:10:22+08:00
lastmod: 2022-08-18T20:19:22+08:00
draft: true
# draft: false
description: ""

tags: ["data"]
categories: ["iOS"]
series: []

hiddenFromHomePage: false
hiddenFromSearch: false

featuredImage: "emotions.jpeg"
featuredImagePreview: "emotions.jpeg"

toc:
  enable: true
math:
  enable: false
lightgallery: true
license: ""
---

本文中介绍些常见的数据类型，是学习笔记，也是各种总结。
<!--more-->

## 数据类型

sizeof 运算符可以获取类型和变量的确切大小

[整数类型](https://www.notion.so/29ffc5e8cf384b43a95b618f0ad8de98)

[浮点类型](https://www.notion.so/ff1dbd16e82945be996c53e066c681d1)

[void](https://www.notion.so/c2425f494dc34357a2ae9b5638ceac58)

### 布尔型

OC 中布尔值有两个类型，YES 和 NO；并不是所有的非 0 整数都会得到 YES，例子768 就是 NO。BOOL 类型实质是 signed char。 

数组、结构体均为与 C 语言同质化的数据类型。

### 数组

<aside>
🚚 支持象C语言那样操作数组，即多维数组，数组作为函数参数及函数返回值均可，指定数组名称即可生成指向数组的第一个元素的指针，也是数组第一个元素的地址。

</aside>

### 结构体

```objectivec
#import <Foundation/Foundation.h>

struct Books {
   NSString *title;
   NSString *author;
   NSString *subject;
   int   book_id;
};

@interface SampleClass:NSObject
/* 函数声明 */
- (void) printBook:( struct Books) book ;
- (void) printBookAlso:( struct Books*) book ;
@end

@implementation SampleClass 
- (void) printBook:( struct Books) book {
   NSLog(@"Book title : %@\n", book.title);
   NSLog(@"Book author : %@\n", book.author);
   NSLog(@"Book subject : %@\n", book.subject);
   NSLog(@"Book book_id : %d\n", book.book_id);
}
- (void) printBookAlso:( struct Books*) book {
   NSLog(@"Book title : %@\n", book->title);
   NSLog(@"Book author : %@\n", book->author);
   NSLog(@"Book subject : %@\n", book->subject);
   NSLog(@"Book book_id : %d\n", book->book_id);
}
@end

int main() {
   struct Books Book1;        /* 声明 Book类型变量 Book1 */

   /* book 1 设置成员信息 */
   Book1.title = @"Objective-C";
   Book1.author = @"Jimi"; 
   Book1.subject = @"Objective-C编程教程";
   Book1.book_id = 88774078;

   SampleClass *sampleClass = [[SampleClass alloc]init];
   /* print Book1 info */
   [sampleClass printBook: Book1];
   [sampleClass printBookAlso: &Book1];

   return 0;
}
```

<aside>
🔧 当使用结构体的指针进行访问内部成员的时候，要使用 - > 符号。
不是指针的时候用 .  即可。

</aside>

位域

```objectivec
struct packed_struct {
   unsigned int f1:1;
   unsigned int f2:1;
   unsigned int f3:1;
   unsigned int f4:1;
   unsigned int type:4;
   unsigned int my_int:9;
} pack;
```

### 类型定义

OC 提供了 typedef 关键字来给类型指定一个新的名称，起别名。通常用大写，但小写也合法。

```objectivec
typedef unsigned char BYTE;
BYTE b1,b2;
```

BYTE 即为 unsigned char 的别名，可以用来定义该类型的变量。

typedef 也可以为自定义的数据类型指定新的名称。使用带结构的 typedef 来定义新的数据类型，然后使用该数据类型来定义变量。 

```objectivec
#import <Foundation/Foundation.h>

typedef struct Books {
   NSString *title;
   NSString *author;
   NSString *subject;
   int book_id;
} Book;

int main() {
   Book book;  //使用Book定义新的结构体即可。
   return 0;
}
```

typedef 与 #define 的区别

- typedef 仅限于为类型提供符号名称，但是 #define 也可以为值定义别名，1 定义为 ONE。
- typedef 由编译器执行，但是 #define 语句由预处理器处理。

### 类型转换

使用强制转换运算符将值从一种数据类型转换为另一种数据类型的方法，比如将 int 转换为 long。

```objectivec
#import <Foundation/Foundation.h>

int main() {
   int sum = 17, count = 5;
   CGFloat mean;

   mean = (CGFloat) sum / count;
   NSLog(@"Value of mean : %f\n", mean );

   return 0;
}
//即将一个整数除以另一个整数的结果变为浮点数。3.400000
//⚠️请你运算符优先于除法，先将 sum 转换为 double 再进行除法。
```

### 整型提升

是将整数类型“小于” `int`或`unsigned int`的值转换为`int`或`unsigned int`的过程。 考虑在`int`中添加字符的示例 -

```objectivec
#import <Foundation/Foundation.h>

int main() {
   int  i = 17;
   char c = 'c';  /* ascii value is 99 */
   int sum;

   sum = i + c;
   NSLog(@"Value of sum : %d\n", sum );

   return 0;
}
//这里，sum的值将变为116，因为编译器进行整数提升。
//并在执行加法运算之前将字符'c'的值转换为ascii值。
```

通用的算术转换：隐式执行通常的算术转换以将它们的值转换为通用类型。编译器首先执行整数提升，如果操作数仍然具有不同的类型，则它们将转换为在以下层次结构中显示最高的类型。

<aside>
🏟️ int → unsigned int → long → unsigned long → long long → unsigned long long → float → double → long double

</aside>

通常的算术转换不是为赋值运算符执行，也不是为逻辑运算符`&&`和`||`执行。下面看一个例子来理解这个概念，当一个算术表达式包含多种基本类型的时候，整个算术表达式的数据类型会自动提升为表达式中最高等级操作数相同的等级。

```objectivec
#import <Foundation/Foundation.h>

int main() {
   int  i = 17;
   char c = 'c';  /* ascii value is 99 */
   CGFloat sum;

   sum = i + c;
   NSLog(@"Value of sum : %f\n", sum );
   return 0;
}
// 116
//很容易理解第一个c字符被转换为整数，但是因为最终值是float，所以通常的算术转换适用.
//编译器将i和c转换为float并相加，所以最终产生的是float类型。
```

当将一个基本数据类型的值赋给另一个基本类型的时候，会自动转换

```objectivec
//整型可以直接为浮点型赋值
int a =10;
float f = a;
//输出： 10.000000
NSLog(@"%f",f);
       
//浮点型为整型赋值，舍弃小数后的
double d = 34.7823;
int i1 = d;
//输出：34
NSLog(@"%d",i1);
       
//取值范围大的给小的会丢失精度
int i2 = 35000;
short s = i2;
//输出：-30536
NSLog(@"%d",s);
```

### 变量

变量表示可以操作存储区域的名称，OC中变量都会有一个特定的类型决定了变量的内存布局和大小，可存值的大小和应用与变量的操作集。

变量的名字可以由字母、数字、下划线、字符组成，但是必须以字母和下划线开头，区分大小写。

### 变量定义

<aside>
💡 type variable_list;

</aside>

type 必须是有效的 OC 数据类型，包括 char w_char int float double bool 或任何有意义的对象等。

variable_list 可以包含一个或多个逗号分隔的标识符名称。

### 有效声明举例

```objectivec
int i, j, k;  //创建名字为i, j, k 的 int 型变量。
char c, h;
float f, s;
double d;
```

### 初始化

变量可以在声明时初始化即分配初始值

```objectivec
type variable_name = value;
extern int d = 3, f = 5;    // declaration of d and f.
int d = 3, f = 5;           // definition and initializing d and f 
byte z = 22;                // definition and initializes z.
char x = 'x';               // the variable x has the value 'x'
```

对于没有初始化变量的定义，具有静态存储时间的变量用 null 隐式初始化也就是所有字节都为 0 ；所有其他变量的初始值未定义。

### 变量声明extern

变量声明就是告诉编译器存在一个给定类型和名称的变量，一遍编译器进一步的编译，不需要完整的详细信息，仅在编译时有意义，编译器在链接程序时需要实际的变量声明。

extern 关键字可以实现在一个文件中声明的变量在其他的文件中也可以使用，变量声明的作用体现子程序链接时。

```objectivec
//.h 中声明
#import <Foundation/Foundation.h>
@interface ExternModel : NSObject
	extern NSString * str;  //此处有extern 就是全局变量，没有的话就是成员属性，但是成员属性没在大括号中，是不合法的
@end

//.m 中对于全局变量赋值
#import <Foundation/Foundation.h>
#import "ExternModel.h"
@interface ExternModel : NSObject
		NSString * str = @"HI Iceland";  //此处有extern 就是全局变量，没有的话就是成员属性，但是成员属性没在大括号中，是不合法的
@end

//其他文件中引入时，引入ExternModel.h
NSString *str; //这样的话会是一个没有初始化的普通变量
extern NSString *str; //这样将成功导入 ExternModel.h 中的str;值为.m中的赋值。
```

### 左值和右值

- **左值** - 引用内存位置的表达式称为“左值”表达式。左值可以显示为赋值的左侧或右侧。
- **右值** - 术语右值是指存储在内存中某个地址的数据值。右值是一个不能赋值给它的表达式，这意味着右值可能出现在赋值的右边但不是左边。

变量是左值，因此可能出现在赋值的左侧。 数字文字是右值，因此无法分配，也不能出现在左侧。 

### 整数文字

可以包含前缀可以包含后缀

```objectivec
212         /* 合法有效 */
215u        /* 合法有效 */
0xFeeL      /* 合法有效 */
032UU       /* 非法无效: 不能重复后缀*/
85         /* decimal 10进制*/
0213       /* octal 八进制*/
0x4b       /* hexadecimal 十六进制*/
30         /* int */
30u        /* unsigned int */
30l        /* long */
30ul       /* unsigned long */
```

### 浮点文字

浮点文字有整数部分、小数点和指数部分。可以以十进制或指数形式表示。都要写全不能有缺失

```objectivec
3.14159
314159E-5L
```

### 字符常量

字符常量用单引号括起来存储在 char 类型中，包括普通字符 'x'，转义序列 '\t'，通用字符'\u02c0'

[Copy of 转义序列](https://www.notion.so/c7b6b123e8de42e0ab996f63ab824240)

### 字符串文字

常用双引号，\ 符号可以使字符串分行展示

### 定义常量

可以使用 #define or const

```objectivec
#define LENGTH 20
#define WIDTH 25
#define NEWLINE \n'

const type vaiable = value;
const int LENGTH = 20;
```

### 内存布局

在使用编译型语言编写代码时，必须告诉编译器每个变量的名称，以声明任何将要在程序中使用的变量。编译器随后查看变量的声明类型，为其保留相应数据的字节，并将变量名和这些字节关联起来。

### 自动变量

在 OC 程序中的函数或者子程序中声明的变量叫做自动变量或局部变量。

```objectivec
void logAverage(float a, float b)
{
	float average;
	average = (a + b) * 0.5;
	printf("The average is %f\n", average);
}
//上面的 average 就是自动变量，在栈上创建。
//从声明本身到函数结束有效。
```

自动变量不是由系统初始化的，在再次给它们分配一个值之前，已经包含了上次使用它们时在内存位置中留下的随机垃圾信息。

自动变量与函数的单次调用有关。如果有函数调用自己的递归代码，则每次对函数的调用都有其自己的栈帧及其自动变量的副本。在一个调用中修改该变量的值，不会修改堆栈上的任何其他调用中该变量的值。

使用一个&运算符将一个自动变量的地址取出，并且分配给函数之外的一个指针变量来保存，这是很糟糕的做法，因为只要函数退出，指针变量就指向了垃圾信息。

自动变量中自动的含义是，当调用使用了自动变量的函数时，它们的存储在栈上分配。然而，仍然必须用一个声明告诉编译器与自动变量相关的信息。

函数参数实际上是在调用函数时，已经用提供的值初始化了的自动变量。它们在栈上创建，并且当函数返回时，它们变成无效的。在函数体中重置它们的值，但修改它们的值对于调用者函数中相应的变量没有影响。

### **外部变量**

在Objective-C程序中，把在main例程或任何子程序作用域之外的源文件中声明的变量称为外部变量。例如在下面的代码中，变量pageCount就是一个外部变量。

```objectivec
int pageCount;
main()
{
	...
	printf("The current page count is：％d\n", pageCount );

}
void addpage()
{
	pageCount++;
	……
}
void deletePage
{
	pageCount——;
	……
}
```

因为外部变量有时候也用作全局变量，以便在不同的函数和不同的源文件之间共享信息，所以上述做法并不一定是一种好的设计选择。

在使用外部变量时需要注意以下3点。

（1）编译器在虚拟地址空间的数据段中分配了外部变量的内存位置。

（2）外部变量在程序的生命周期中都持久存在，它们不会超出作用域或消失，并且只有当给它们分配一个新值时其值才会改变。如果没有显式初始化它，那么编译器会将外部变量初始化为0。

（3）外部变量在单个函数的作用域之外是可见的（可用的）。实际上，外部变量是全局标记，除非将一个外部变量声明为static的，否则可能对于任何源文件中的任何函数都是可见的。

### 作用域

作用域即可以看见调用该变量的范围。

**控制实例变量的作用域的指令**

实例变量的作用域仅限与为该类定义的实例方法，任何实例变量都能直接通过该变量名来访问该类的实例变量。实例变量可以通过子类继承，继承过来的实例变量可以通过变量名在给类定义的方法中直接访问。

```objectivec
@interface Printer：NSObject
{
　@private     //之后的变量到花括号结束或下一个指令前，均为该类型。
							 //该类方法可以，子类不可以
　@protected   //默认类型，可被该类和子类直接访问
　//其他实例变量
	@public      //该类变量是的其他方法或函数可以通过指针运算符 "->" 来访问。
	//            可以被该类访问还可以被其他类或模版中定义的方法访问
	@package     //可以在类实现的任何地方访问该变量
	//
}
……
@end
```

**外部变量**

外部变量即函数之外声明的变量从文件中声明它的地方开始，一直到文件的末尾处均可以访问到该变量。使用 extern 关键字可以将一个外部变量的可见性扩展到不同的文件中。使用 static 关键字开始外部变量的声明，会将该变量的作用域限定在声明他它的文件之中。static 优先与 extern；

```objectivec
//a文件
int globalNum = 0;  //定义了外部变量，可以被其他函数或方法访问并修改其值。
//b文件
extern int globalNum;  //告知系统将引用其他文件中的变量，这是声明。
	//使用外部变量需要遵守的一个原则就是变量必须定义在源文件中的某个位置。

//另一种定义外部变量的方法
extern int gMoveNumber = 0;
//这种方法会有警告，extern 语句是声明不是定义，在 OC 中的声明不会引起分配变量的存储空间
//定义会引起变量存储空间的分配。上述语句强行将声明语句当作定义语句来用，违背了该原则。

//外部变量可以被 extern 声明很多次，但是只能定义一次。
```

**静态变量**

OC 中用 static 关键字来定义静态变量，定义在任何方法和函数之外的静态变量，可以被该文件中的所有位于该语句之后的方法或函数访问，其他文件中的函数和方法则不行。

```objectivec
//Objective-C既支持全局变量，也支持局部变量，具体用法和C/C++中相同。
//假如需要在类A的implementation文件中定义一个static变量
//然后为类A定义静态成员函数来操作该变量，
//这样在其他类中就不需要创建类A的实例来对static变量进行访问。
//虽然该static变量并不是类A的静态成员变量，但是也实现了同样的效果。
//在这个时候，使用局部变量就会更加科学。
//为什么不定义全局变量，关键就在于变量的作用域，static变量的作用域被限制在单一的文件中。
//看下面的代码。

@interface Example：NSObject {
}

- (id)init;
+(int)instanceCount;
@end

#import "example.h"
static int count;
@implementation Example
-(id)init{
　self = [super init];
　if(nil！=self){
　　 count+=1;
　}
　return self;
}

+(int)instanceCount{
　return count;
}
@end

//在上述代码中，可以通过[Example instanceCount] 访问静态变量count，而无须创建实例。
```

**复合语句和作用域**

复合语句是包含在花括号中的一个语句序列，复合语句的内部是一个独立的作用域。可以在复合语句中的任意位置声明一个变量，该变量从声明它的地方到复合语句结束的地方都是可见的。复合语句存在于它的作用域中，这个作用域叫做该复合语句的外围作用域。在外围作用域中声明的变量，在复合语句中是可见的；但是在复合语句中声明的变量，在外围作用域中是不可见的。

```objectivec
//如果在一条复合语句中声明了一个变量，而该变量与外围作用域中的一个变量具有相同的名称
//那么在内部变量的作用域中，内部的变量将会覆盖外围作用域中的变量

void someFunction()　
{　
　int a = 7;　
　int b = 2;　
　{
　　　int c;　
　　　c = a * b;　// c 是14, 封闭的范围仍然是可见的
　　　int a = 10; //掩盖了外围作用域中的变量　
　　　c =　a * b; // c 现在是 20　
　}
}
```

### 存储类说明符

**auto**

auto 用来声明一个自动局部变量，是函数或方法内部变量的默认声明方式，只在一个函数内使用。

```objectivec
auto int index;  <==>  int index; //两者等效
//自动变量自动会为它自动分配空间退出时自动解除分配的空间。
//静态变量有默认的初始值 0 ，但是自动变量没有。
```

**const**

告诉编译器指定的变量在程序运行期间不变。初始化时候再给该变量赋值，编译器会发出警告。

```objectivec
int a = 10;
int b = 15;
int *const ptr = &a;   //指向整数的常量指针 ptr
*ptr = 20;//现在 20．
ptr = &b; // 错误
// const 指向指针变量时声明顺序从左向右读取，不能修改 ptr 的值以指向一个不同的变量，
//但是可以使用 ptr 来修改他指向的变量。

//如果 const 放在了声明的其他内容的前面，意义就变了
//此处可以修改 ptr 指向另一个变量，但是不能通过 ptr 来修改它指向的任何变量
int a = 10;　
int b = 15;　
const int *ptr = &a;　 //指向 int 常量的指针
*ptr = 20; // 错误 
a = 20;　　// 正确
ptr = &b;　//正确
```

**volatile**

使用关键字 volatile 声明变量后，其内容可能会被程序中 main 线程以外的其他函数修改，然后编译器会避免像没有该关键字时那样优化。如果变量的存储属于外部设备的一个硬件寄存器，并且该设备已经被内存映射到了程序的地址空间中，就会出现这种情况。

```objectivec
int contine = 1;
while( continue ){
	do ...
}
//如果做的事没有修改 continue 那么编译器会认为 没有被修改，会优化为 
while(1) {
	do ...
}

//如果声明为 volatile 则会避免这种优化，
//目的也是为了防止编译器优化掉看似多余的变量赋值，同时避免重复的检测值没有变化的变量。

//输出端口的地址存储为名为 outPort 的变量。
*outPort = 'O';
*outPort = 'N';
//没有 volatile 关键字的情况智能的编译器会删除第一个赋值语句，直接进入第二个赋值语句。
```

**static**

static 可以声明静态变量，当它用于函数中的变量或外部变量，是两种含义

```objectivec
void print() {
    int times = 0;  
    times++;
    NSLog(@"%d", times);
}

int main(int argc, const char * argv[]) {
    @autoreleasepool {
        print();
        print();
        print();
    }
    return 0;
}
//times 是静态变量，三次输出为 1 2 3
//times 是自动变量，三次输出为 1 1 1
//static 变量全局仅初始化一次，所以之后的值会在基础上累加，自动变量每次都初始化，所以111

//函数内定义，仅在函数内可以看到
//没有初始值的话，会默认赋值为 0
//静态被存放在数据区，程序运行的过程中，它一直被存放在数据区
//在对函数的多次调用中，对一个static 变量的引用都指向同一个位置

//static 用于外部变量时，能够将该变量的可见性缩减到声明它的文件中，extern 将失效。
```

**extern**

将其他文件中已定义的变量导入本文件中。

**enum**

枚举的意义在于将数字转换为有意义的变量，所以名字一定要起的能表达它代表的含义。

```objectivec
//定义枚举类型 dic
enum dic {up=10, down, right=3, left};  //赋值之后往后一次加一，都没赋值就从0开始

int main(int argc, const char * argv[]) {
    @autoreleasepool {

        enum dic d;
        d = left;
        NSLog(@"%d", d);  //即 left 的值

        NSLog(@"%d", up);
        NSLog(@"%d", down);
        NSLog(@"%d", right);
        NSLog(@"%d", left);

    }
    return 0;
}
```

**typedef**

通过 typedef 语句为数据类型起别名，增加变量可读性。

```objectivec
typedef int Counter;
counter i;  <==>  int i ;
```