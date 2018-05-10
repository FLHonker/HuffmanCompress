#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <Huffman.cpp>
#define nSIZE 256
#define ERROR  -1
using namespace std;

// 文件头
struct HEAD
{
	char type[4];		// 文件类型
	int length;		// 原文件长度
	int weight[nSIZE];	// 权值数值
};

int InitHead(const char *pFilename, HEAD &sHead)   // 初始化文件头
{
	strcpy(sHead.type, "HUF");// 文件类型
	sHead.length = 0;// 原文件长度
	for (int i = 0; i < nSIZE; i++)
	{
		sHead.weight[i] = 0;// 权值
	}
	// 以二进制流形式打开文件
	FILE *fin = fopen(pFilename, "rb");
	int ch;
	// 扫描文件，获得权重
	while ((ch = fgetc(fin)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	// 关闭文件
	fclose(fin);
	fin = NULL;

	return OK;
}

int WriteFile(const char *pFilename, const HEAD sHead, const char *pBuffer, const int nbuf)
{
	// 生成文件名
	char filename[nSIZE + 5] = { '\0' };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");
	/*
	ofstream fout(filename,ios::binary);
	fout.write(&sHead, sizeof(HEAD));
	fout.write(pBuffer,sizeof(char) * nbuf);
	fout.close();*/
	
	// 以二进制流形式打开文件
	FILE *fout = fopen(filename, "wb");
	// 写文件头
	//fwrite(&sHead, sizeof(HEAD), 1, fout);
	// 写压缩后的编码
	//fwrite(pBuffer, sizeof(char), nbuf, fout);
	// 关闭文件，释放文件指针
	fclose(fout);
	fout = NULL;
	
	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nbuf;
	cout << "压缩文件大小为：" << len << "B" << endl;
	double rate = len * 1.0 / sHead.length;
	cout.setf(ios::fixed);
	cout << "压缩率为：" << setprecision(4) << rate << "%" << endl;

	return len;
}


char Str2byte(const char *pBinStr)  //将形如“01010101”的字符串转换成字节
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;// 左移1位
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}

int Encode(const char *pFilename, const HuffmanCode pHC, char *pBuffer, const int nbuf)
{
	// 开辟缓冲区
	pBuffer = (char *)malloc(nbuf * sizeof(char));
	if (!pBuffer)
	{
		cerr << "开辟缓冲区失败!" << endl;
		return ERROR;
	}

	char cd[nSIZE] = { '\0' };  // 工作区
	int pos = 0;		// 缓冲区指针
	int ch;
	FILE *fin = fopen(pFilename, "rb");
	// 扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓冲区中。
	while ((ch = fgetc(fin)) != EOF)
	{
		strcat(cd, pHC[ch]);	// 从pHC复制编码串到cd
		// 压缩编码
		while (strlen(cd) >= 8)
		{
			// 截取字符串左边的8个字符，编码成字节
			pBuffer[pos++] = Str2byte(cd);
			// 字符串整体左移8字节
			for (int i = 0; i < nSIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	fclose(fin);
	fin = NULL;
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	return OK;
}

int Compress(const char *pFilename, HuffmanCode &pHC, const HEAD sHead)
{
	//计算缓冲区的大小  
	int nbuf = 0;
	for (int i = 0; i<nSIZE; i++)
	{
		nbuf += sHead.weight[i] * sizeof(pHC[i]);
	}
	nbuf = (nbuf % 8) ? nbuf / 8 + 1 : nbuf / 8;
	//cout<<"nbuf = "<<nbuf<<endl; 
	char *pBuffer = NULL;
	Encode(pFilename, pHC, pBuffer, nbuf);
	if (!pBuffer)
		return ERROR;
	int result = WriteFile(pFilename, sHead, pBuffer, nbuf);
	return result;
}