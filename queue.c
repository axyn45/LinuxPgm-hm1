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
    return NULL;

  q->_size = 0;
  q->_tail = NULL;
  q->head = NULL;
  return q;
}

/*
  释放队列所用到的所有空间
  如果 q 为 NULL 则没有效果
*/
void q_free(queue_t *q)
{
  /* 如何释放链表元素和字符串 */
  /* 释放队列结构 */
  list_ele_t *cur = q->head;
  list_ele_t *nxt = (cur == NULL ? NULL : cur->next);

  while (cur != NULL)
  {
    if (cur == NULL)
      nxt = NULL;
    else
      nxt = cur->next;
    free(cur);
    cur = nxt;
    nxt = (cur == NULL ? NULL : cur->next);
  }
  free(q);
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
    return false;

  newh = malloc(sizeof(list_ele_t));
  /* 别忘了为字符串分配空间并拷贝它 */
  if (newh == NULL)
    return false;
  newh->value = malloc(sizeof(*s)), strcpy(newh->value, s);

  /* 如果其中一个malloc 调用返回 NULL 该怎么办? */

  if (newh->value == NULL)
  {
    free(newh);
    return false;
  }

  newh->next = q->head;
  q->head = newh;
  q->_size++;
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

    q->_tail->next = newt;
    q->_tail = newt;
    q->_size++;
    return true;
  }

  return false;
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
    return false;
  if (sp != NULL)
    strcpy(sp, q->head->value);
  list_ele_t *temp = q->head;
  q->head = q->head->next;
  free(temp->value), free(temp);
  q->_size--;
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
    return;

  q->_tail = q->head;

  list_ele_t *cur = q->head;
  list_ele_t *nxt = cur->next;

  while (nxt != NULL)
  {
    list_ele_t *t = nxt;
    nxt = nxt->next;
    t->next = cur;
    cur = t;
  }
  q->_tail->next = NULL;
}
