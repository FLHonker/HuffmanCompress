#include <iostream>
#include <Huffman.h>
#include <Compress.h>
using namespace std;


int main()
{
	char tmpfile[nSIZE];
	cout << "============ Huffman文件压缩 ============" << endl;
	cout << "请输入文件完整路径名: ";
	cin >> tmpfile;
	char *filename = tmpfile;
	HEAD shead;
	HuffmanTree pHT;
	HuffmanCode pHC;
	char *pBuffer = NULL;
	InitHead(filename, shead);
	CreateHuffmanTree(pHT, shead.weight); //构造HuffmanTree

	/*测试HuffmanTree结点信息*/
	//cout<<"生成的Huffman树结点信息为："<<endl;
	//cout<<"pHT[i]  \t"<<"weight\t"<<"parent\t"<<"lchild\t"<<"rchild\t"<<endl;
	//for(int i=0;i<2*nSIZE-1;i++)
	//cout<<"pHT["<<i<<"]  \t"<<pHT[i].weight<<'\t'<<pHT[i].parent<<'\t'<<pHT[i].lchild<<'\t'<<pHT[i].rchild<<'\t'<<endl;

	HuffmanCoding(pHC, pHT);    //生成Huffman编码

	/*测试生成的Huffman编码*/
	//cout<<" *生成的Huffman编码为："<<endl;
	//for(int i=0;i<nSIZE;i++)
	//cout<<"pHC["<<setfill('0')<<setw(2)<<i<<"] = "<<pHC[i]<<endl;

	/*测试压缩文件，计算压缩率*/
	int nbuf = 0;
	for (int i = 0; i<nSIZE; i++)
	{
		nbuf += shead.weight[i] * sizeof(pHC[i]);
	}
	nbuf = (nbuf % 8) ? nbuf / 8 + 1 : nbuf / 8;
	Encode(filename, pHC, pBuffer, nbuf);
	int result = WriteFile(filename, shead, pBuffer, nbuf);

	//Compress(filename, pHC, shead);   //压缩保存文件
	return 0;
}
