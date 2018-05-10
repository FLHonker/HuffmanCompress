//#include <Huffman.h>
#include <stdio.h>
#include <iomanip>

//在控制台输出Huffman树每个节点的信息
void TestHufTree(HuffmanTree pHT)
{
	for (int i = 0; i < 2 * nSIZE - 1; i++)
	{
		cout << "HuffmanTree的结点信息为：" << endl;
		cout << "pHT[i]  \t" << "weight\t" << "parent\t" << "lchild\t" << "rchild\t" << endl;
		cout << "pHT[" << i << "]  \t" << pHT[i].weight << "\t" << pHT[i].parent
			<< "\t" << pHT[i].lchild << "\t" << pHT[i].rchild << endl;
	}
}

//采用先序遍历的方法，在控制台输出Huffman树每个结点的信息
void TestHufTreeN(HuffmanTree pHT, int root)
{
	cout << pHT[root].weight << " ";
	if (pHT[root].lchild != -1)
	{
		TestHufTreeN(pHT, pHT[root].lchild);
	}
	if (pHT[root].rchild != -1)
	{
		TestHufTreeN(pHT, pHT[root].rchild);
	}
}

//测试输出生成的各个结点的Huffman编码
void TestHufCode(HuffmanCode pHC)
{
	cout << " *生成的Huffman编码为：" << endl;
	for (int i = 0; i<nSIZE; i++)
		cout << "pHC[" << setfill('0') << setw(2) << i << "] = " << pHC[i] << endl;
}


