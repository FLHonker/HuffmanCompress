#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include <string.h>
#define OK 0
#define nSIZE 256
#define MAXVALUE 999999
using namespace std;

// Huffman树节点
struct HTNode
{
	int weight;// 权值
	int parent;// 父节点
	int lchild;// 左孩子
	int rchild;// 右孩子
};

// Huffman树
typedef HTNode* HuffmanTree;	  // 动态分配数组存储Huffman树
typedef char HuffmanCode[nSIZE][nSIZE];  //字符串数组，记录Huffman编码

void CreateHuffmanTree(HuffmanTree &pHT, int weight[])
{
	/* i、j：循环变量，m1、m2：构造哈夫曼树不同过程中两个最小权值结点的权值，
	x1、x2：构造哈夫曼树不同过程中两个最小权值结点在数组中的序号。*/
	int i, j, m1, m2, x1, x2;
	HuffmanTree p;
	pHT = (HuffmanTree)malloc(2 * nSIZE * sizeof(HTNode));
	for (p = pHT, i = 0; i < nSIZE; ++i, ++p)
		*p = { weight[i], -1, -1, -1 };
	for (; i < 2 * nSIZE - 1; ++i, ++p)
		*p = { 0, -1, -1, -1 };
	/* 循环构造 Huffman 树 */
	for (i = 0; i<nSIZE - 1; i++)
	{
		m1 = m2 = MAXVALUE;     /* m1、m2中存放两个无父结点且结点权值最小的两个结点 */
		x1 = x2 = 0;
		/* 找出所有结点中权值最小、无父结点的两个结点，并合并之为一颗二叉树 */
		for (j = 0; j<nSIZE + i; j++)
		{
			if (pHT[j].weight < m1 && pHT[j].parent == -1)
			{
				m2 = m1;
				x2 = x1;
				m1 = pHT[j].weight;
				x1 = j;
			}
			else if (pHT[j].weight < m2 && pHT[j].parent == -1)
			{
				m2 = pHT[j].weight;
				x2 = j;
			}
		}
		/* 设置找到的两个子结点 x1、x2 的父结点信息 */
		pHT[x1].parent = nSIZE + i;
		pHT[x2].parent = nSIZE + i;
		pHT[nSIZE + i].weight = pHT[x1].weight + pHT[x2].weight;
		pHT[nSIZE + i].lchild = x1;
		pHT[nSIZE + i].rchild = x2;
	}
}

int HuffmanCoding(HuffmanCode &pHC, HuffmanTree &pHT)
{
	// 无栈非递归遍历Huffman树，求Huffman编码
	char cd[nSIZE] = { '\0' };// 记录访问路径
	int cdlen = 0;// 记录当前路径长度
	int i, c, p;
	for (i = 0; i < nSIZE; i++)
	{
		int start = 255;
		c = i;
		p = pHT[c].parent;
		while (p != -1)         /* 双亲结点存在 */
		{
			if (pHT[p].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
			c = p;
			p = pHT[c].parent;    /* 设置下一循环条件 */
		}
		//cd[cdlen] = '\0';

		/* 保存求出的每个叶结点的哈夫曼编码 */
		strcpy(pHC[i], &cd[start]);
		//pHC[i] = (char*)malloc((cdlen + 1) * sizeof(char));
		//pHC[i] = cd;
	}
	return OK;
}


