//#include <Compress.h>
//#include <Huffman.cpp>

void CompressPro(const char *pFilename)
{
	HuffmanTree pHT;
	HuffmanCode pHC;
	HEAD sHead;
	InitHead(pFilename, sHead);      //初始化文件头,获得权重
	Compress(pFilename, pHT, pHC, sHead.weight, sHead);   //调用Compress()实现压缩，并保存文件.huf
}

/*
int main()
{
HEAD shead;
char filename[nSIZE];
InitHead(filename,shead);
int i;
for(i=0;i<nSIZE;i++)
cout<<shead.weight[i]<<" ";
}*/
