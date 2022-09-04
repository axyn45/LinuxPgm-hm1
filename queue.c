/*
 * C 编程技能测试实验代码
 * 为课程预检验
 */

/*
 * 程序实现一个同时支持 FIFO 和 LIFO 的队列
 *
 * 使用单链表表示队列元素
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  创建空队列
  如果没有分配空间则返回 NULL
*/
queue_t *q_new()
{
	queue_t *q = malloc(sizeof(queue_t));
	/* 如果 malloc 返回 NULL 呢? */
	if (q == NULL)
		return NULL;	//空则返回空值

	q->_size = 0;		//初始化链表长度为0
	q->_tail = NULL;	//初始化链表尾为空
	q->head = NULL;
	return q;			//返回创建的链表
}

/*
  释放队列所用到的所有空间
  如果 q 为 NULL 则没有效果
*/
void q_free(queue_t *q)
{
	/* 如何释放链表元素和字符串 */
	/* 释放队列结构 */
	if(q->head==NULL) {free(q); return;}	//若表头为空则释放q并返回
	list_ele_t *cur = q->head;		//让cur指向链表表头
	list_ele_t *nxt =cur->next;		//若表头为空则nxt也为空，否则指向cur下一个元素

	while (nxt != NULL)	
	{
		free(cur);			//释放cur
		cur = nxt;			//cur后移
		nxt = nxt->next;	//nxt后移
	}
	free(cur);		//释放cur
	free(q);		//释放q
}

/*
  在队首插入一个元素
  成功则返回 true
  q 为 NULL 或者 无法分配空间则返回 false
  参数 s 指向待存储的字符串
  函数必须显式地分配空间并拷贝字符串到空间里面
 */
bool q_insert_head(queue_t *q, char *s)
{
	list_ele_t *newh;
	/* 如果 q 为 NULL你该怎么办? */
	if (q == NULL)
		return false;	//q空则返回空值

	newh = malloc(sizeof(list_ele_t));
	/* 别忘了为字符串分配空间并拷贝它 */
	if (newh == NULL)
		return false; 		//空间分配失败，返回false
	newh->value = malloc(sizeof(*s)), strcpy(newh->value, s);	//为字符串分配空间

	/* 如果其中一个malloc 调用返回 NULL 该怎么办? */

	if (newh->value == NULL)	//分配字符串空间失败
	{
		free(newh);				//释放新建节点
		return false;			//返回false
	}

	newh->next = q->head;		//插入链表
	q->head = newh;				//连接表头
	q->_size++;					//表长加一
	return true;
}

/*
  在队尾插入一个元素
  成功则返回 true
  q 为 NULL 或者 无法分配空间则返回 false
  参数 s 指向待存储的字符串
  函数必须显式地分配空间并拷贝字符串到空间里面
 */
bool q_insert_tail(queue_t *q, char *s)
{
	/* 你需要为该函数编写完整的代码 */
	/* 记住: 函数时间复杂度为 O(1) */
	if (q != NULL)
	{
		//分配空间和异常处理
		list_ele_t *newt = malloc(sizeof(list_ele_t *));
		if (newt == NULL)
			return false;
		newt->value = malloc(sizeof(s));
		if (newt->value == NULL)
		{
			free(newt);
			return false;
		}

		strcpy(newt->value, s);

		q->_tail->next = newt;	//插入表尾
		q->_tail = newt;		//更新表尾指针
		q->_size++;				//表长加一
		return true;
	}
	else return false;	//无法分配空间，返回false
}

/*
  移除队首元素Attempt to remove element from head of queue.
  成功则返回 true
  队列为 NULL 或者为 空 则返回 false
  如果 sp 非空 并移除了一个元素，则将移除的字符串拷贝给 *sp
  (至多 bufsize-1 个字符, 加上1个 null 结束符（'\0',0）)
  元素和字符串使用的空间需要释放
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
	/* 你需要修复这个代码 */
	if (q == NULL || q->_size == 0)
		return false;		//表为初始化或为空则返回false
	if (sp != NULL)
		strcpy(sp, q->head->value);

	list_ele_t *temp = q->head;		//临时保存表头
	q->head = q->head->next;		//表头指针后移
	free(temp->value), free(temp);	//释放原表头
	q->_size--;						//表长减一
	return true;
}

/*
  返回队列的元素数量
  如果队列为 NULL 或者为 空 则返回 0
 */
int q_size(queue_t *q)
{
	/* 你需要为这个函数编写代码 */
	/* 记住: 函数时间复杂度为 O(1) */
	if (q != NULL && q->_size > 0)
	{
		return q->_size;
	}
	return 0;
}

/*
  反转队列元素
  如果 q 为 NULL 则没有效果
  该函数不能直接或者间接调用其他函数为队列元素分配任何额外的空间
  (例如, 不能调用 q_insert_head, q_insert_tail, 或者 q_remove_head).
  应该是通过重排现有元素实现
 */
void q_reverse(queue_t *q)
{
	/* 你需要为这个函数编写代码 */
	if (q == NULL || q->_size <= 1)
		return;		//表未初始化或长度小于2则直接返回

	q->_tail = q->head;	//表头变表尾

	list_ele_t *cur = q->head;
	list_ele_t *nxt = cur->next;

	while (nxt != NULL)
	{
		list_ele_t *t = nxt;	//临时节点保存nxt
		nxt = nxt->next;		//nxt后移
		t->next = cur;			//原本的nxt放到cur前
		cur = t;				//cur后移
	}
	q->_tail->next = NULL;	//表尾next变为空
}
