#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MAXSIZE 1000

#if 1 // 顺序栈的表示  栈非空时 top永远指向栈顶元素的上一个位置
typedef struct {
    int* base;      // 栈底指针
    int* top;       // 栈顶指针
    int stacksize;  // 栈可用的最大容量
} Stack;

// 构造一个空栈s
void InitStack(Stack* s) {
    s->base = malloc(sizeof(int) * MAXSIZE);
    // s->base[n] == *(s->base+n)
    s->top = s->base;
    s->stacksize = MAXSIZE;
}

//插入元素value为新的栈顶元素
bool PushStack(Stack* s, int value)
{
    if (s->top - s->base == s->stacksize)
        return false; // 栈满 指向数组元素下一个空间
    *(s->top) = value;
    s->top++;  // 元素value压入栈顶 栈顶指针加1
    return true;
}

// 删除栈顶元素 用value返回其值
bool PopStack(Stack* s, int* value)
{
    if (s->top == s->base)
        return false;
    s->top -= 1;
    *value = *s->top;
    // s->top <==> (*s).top
    // *s->top <==> *((*s).top)
    return true;
}

// 返回s的栈顶元素 不修改栈顶指针
int TopStack(Stack* s) {
    if (s->top == s->base)
        return false;
    return *(s->top - 1);
}

// 销毁创造的栈
void DestoryStack(Stack* s)
{
    free(s->base);
}
#endif

// 由于这里的定义和上面的重复了, 所以可以把上面的 #if 1 改为 0 , 这里的改为 1 就可以切换不同实现
#if 0 // 使用链表（链式结构）实现栈 后进先出
//  区别于顺序结构, 链式结构支持无限长度, 所以没有 MAXSIZE
typedef struct {
    int data;
    struct Stack* next; //和单链表一致
} Stack;

// 构造一个空栈 栈顶指针置空
void InitStack(Stack* s) {
    s = NULL;//第一个结点作为栈顶
}

// 在栈顶插入元素value
void PushStack(Stack* stack, int value) {
    Stack* p = malloc(sizeof(Stack));
    p->data = value;  //生成新结点 将新结点数据域置为value
    p->next = stack;
    stack = p;  //插入的元素在栈顶
}

// 删除s的栈顶元素 用value返回其值
bool PopStack(Stack* stack, int* value) {
    if (stack == NULL)
        return false;  //栈空
    value = stack->data;  //将栈顶元素赋值给value
    Stack* p = stack;  //用p临时保存栈顶空间
    stack = stack->next; //修改栈顶指针后移
    free(p);  //释放原栈顶元素空间
    return true;
}

// 返回s的栈顶元素 不修改栈顶指针
int TopStack(Stack* stack,int* value)
{
    if (stack != NULL)
        value = stack->data;
    return value;
}

#endif

#if 0 // 队列的顺序表示 循环队列
typedef struct {
    int* base; //存储空间的基地址
    int front; //头指针
    int rear;  //尾指针
} Queue;

// 构造一个空队列q
void InitQueue(Queue* q) {
    q->base = malloc(sizeof(int) * MAXSIZE); //为队列分配数组空间
    q->front = q->rear = 0; //队列为空
}

//求队列长度
int QueueLength(Queue* queue) {
    return(queue->rear - queue->front + MAXSIZE) % MAXSIZE;
}

// 循环队列的入队
bool PushQueue(Queue* queue, int value) {
    if ((queue->rear + 1) % MAXSIZE == queue->front)
        return false; //队满
    queue->base[queue->rear] = value;  //新元素插入队尾
    queue->rear = (queue->rear + 1) % MAXSIZE;  //队尾指针加1
    return true;
}

// 移出队头元素 用value返回其值
bool PopQueue(Queue* queue, int* value) {
    if (queue->front == queue->rear)
        return false; //队空
    value = queue->base[queue->front]; //保存队头元素
    queue->front = (queue->front + 1) % MAXSIZE; //队头指针加1
    return true;
}

// 获取队头元素
int TopQueue(Queue* queue, int* value) {
    if (queue->front != queue->rear)  // 队列非空
        value = queue->base[queue->front];
    return value;  //返回队头元素的值
}

// 销毁创建的队列
void DestoryQueue(Queue* q) {
    free(q->base);
}

#endif

#if 0 // 使用链表（链式结构）实现队列 先进先出
typedef struct
{
    int data;
    struct  QNode* next;
}QNode; // 定义结点结构体

typedef struct
{
    QNode* front;  //队头指针
    QNode* rear;   //队尾指针
}Queue; // 定义队列结构体

// 构造一个空队列q
void InitQueue(Queue* q) {
    q->front = malloc(sizeof(QNode)); // 新生成的结点作为头节点
    q->rear = q->front;//队尾指向队指向新节点
    q->front->next = NULL;//带头结点,头结点指针域置空
}

// 链队的入队
void PushQueue(Queue* queue, int value) {
    QNode* p = malloc(sizeof(QNode));
    p->data = value;  //为入队元素分配结点空间 数据域置为value 用指针p指向
    p->next = NULL;
    queue->rear->next = p;  //将新结点插入队尾
    queue->rear = p;  //修改队尾指针
}

// 链队的出队 用value返回其值
bool PopQueue(Queue* queue, int* value) {
    if (queue->front == queue->rear)
        return false; //队列空出错
    QNode* p = queue->front->next;  //p指向队头元素
    value = p->data;
    queue->front->next = p->next;  //修改头节点指针域
    if (queue->rear == p)
        queue->rear = queue->front; //尾结点被删 指向头结点
    free(p);  //释放队头元素空间
    return true;
}

// 取队头元素
int TopQueue(Queue* queue,int* value)
{
    QNode* p = queue->front->next;
    if (queue->front != queue->rear)
        value = p->data;
    return value;
}

#endif

#define EXPECT_EQ(actual, expect)                                                                 \
    do {                                                                                          \
        if ((expect) != (actual))                                                                 \
            printf("%s:%d: actual: %d, expect: %d\n", __FILE__, __LINE__, (actual), (expect));    \
    } while(0)

#define EXPECT_TRUE(expect) EXPECT_EQ(expect, true)

int main() {
    Stack* s = malloc(sizeof(Stack));
    InitStack(s);
    int value = 0, value1 = 1, value2 = 2;

    EXPECT_TRUE(PushStack(s, value1)); // 元素1入栈
    EXPECT_EQ(TopStack(s), 1);         // 判断是否入栈成功
    EXPECT_TRUE(PushStack(s, value2)); // 元素2入栈
    EXPECT_EQ(TopStack(s), 2);         // 判断是否入栈成功
    EXPECT_TRUE(PopStack(s, &value));  // 元素2出栈
    EXPECT_EQ(value, 2);               // 判断是否出栈成功
    EXPECT_EQ(TopStack(s),1);          // 取栈顶元素判断是否为1
    DestoryStack(s);
    free(s);

    return 0;
}
