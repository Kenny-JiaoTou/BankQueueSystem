#include "../include/util/ProiorityQueue.h"

ProirityQueue* pq_create(int(*CompareFunction)(const void*, const void*))
{
	ProirityQueue* queue = malloc(sizeof(ProirityQueue));
	if (NULL == queue) return NULL;
	queue->size = 0;
	queue->capacity = PQ_INIT_CAPACITY;
	queue->elements = malloc(sizeof(void*) * queue->capacity);
	queue->CompareFunction = CompareFunction;
	return queue;
}

void pq_resize(ProirityQueue* proirityQueue)
{
	void** temp = proirityQueue->elements;
	proirityQueue->capacity *= 2;
	proirityQueue->elements = malloc(sizeof(void*) * proirityQueue->capacity);
	if (proirityQueue->elements == NULL) {
		return;
	}
	memcpy(proirityQueue->elements, temp, sizeof(void*) * proirityQueue->capacity);
	safe_free(temp);
}

int parent(int index)
{
	return (index - 1) / 2;
}

int leftChild(int index)
{
	return index * 2 + 1;
}

int rightChild(int index)
{
	return index * 2 + 2;
}

void* pq_top(ProirityQueue* queue)
{
	return queue->elements[0];
}

void pq_sift_up(ProirityQueue* queue, int index)
{
	while (index > 0 && queue->CompareFunction(queue->elements[parent(index)], queue->elements[index]) < 0) {
		swap(&queue->elements[index], &queue->elements[parent(index)], sizeof(queue->elements[index]));
		index = parent(index);
	}
}

void pq_sift_down(ProirityQueue* queue, int index)
{
	while (leftChild(index) < queue->size) {
		//在此轮循环中,data[index]和data[j]交换位置
		int j = leftChild(index);	//左孩子下标
		// j+1 >= size 时表示已到末尾
		// 非末尾元素时，如果 元素j+1 > 元素j，则将交换的元素设置为 元素j+1
		if (j + 1 < queue->size && queue->CompareFunction(queue->elements[j + 1], queue->elements[j]) > 0) {
			j++;
		}
		////元素k >= 元素j时，退出循环
		if (queue->CompareFunction(queue->elements[index], queue->elements[j]) >= 0) {
			break;
		}
		swap(&queue->elements[index], &queue->elements[j], sizeof(void*));
		index = j;					//交换后进入下一轮
	}
}

void pq_push(ProirityQueue* queue, void* element)
{
	if (queue->size == queue->capacity) {
		pq_resize(queue);
	}
	queue->elements[queue->size++] = element;
	pq_sift_up(queue, queue->size - 1);
}

void* pq_pop(ProirityQueue* queue)
{
	void * element = pq_top(queue);		//获取堆顶元素
	swap(&queue->elements[0], &queue->elements[queue->size - 1], sizeof(void*));	//首尾交换
	//删除尾元素
	queue->elements[queue->size - 1] = NULL;
	queue->size--;
	pq_sift_down(queue, 0);			//下沉首元素
	return element;
}

void* pq_replace(ProirityQueue* queue, void* element)
{
	void* top = pq_top(queue);
	queue->elements[0] = element;
	pq_sift_down(queue, 0);
	return top;
}

void pq_heapify(ProirityQueue* queue)
{
	for (int i = parent(queue->size - 1); i >= 0; i--) {
		pq_sift_down(queue, i);
	}
}

void pq_free(ProirityQueue* queue)
{
	pq_clear(queue);
	safe_free(queue->elements);
	safe_free(queue);
}

void pq_clear(ProirityQueue* queue)
{
	while (queue->size) {
		void* top = pq_top(queue);	//取出队首
		pq_pop(queue);				//去除队首			
		safe_free(top);				//释放空间
	}
	return 0;
}
