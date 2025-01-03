#include<stdio.h>
#include<stdlib.h>

#define SIZE 100

 // 读取data.txt，统计每种商品在不同供应商处的折扣，并按照折扣从大到小进行排序
 // 输出每个商品最大的折扣信息（包括供应商），并将排序后的数据输出到result.txt
 
 // 结构体数组
struct shopping
{
	char name[20]; // 商品名
	int number;    // 编号
	char give[20]; // 供应商
	float piece;   // 折扣
}shop[SIZE];

 // 从data.txt读取商品信息
void load()
{
	FILE* fp = fopen("data.txt", "rb");
	if (fp == NULL)
	{
		printf("cannot open file\n");
		return;
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (fread(&shop[i], sizeof(struct shopping), 1, fp) != 1)
		{
			if (feof(fp))
			{
				fclose(fp);
				return;
			}
			printf("file read error\n");
		}
	}
	fclose(fp);
}

 // 按折扣排序
int compare(const void* a, const void* b)
{
	return ((struct shopping*)a)->piece - ((struct shopping*)b)->piece;
}

 // 将结构体数组保存到文件
void save()
{
	FILE* fp = fopen("result.txt", "wb");
	if (fp == NULL)
	{
		printf("cannot open file\n");
		return;
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (fwrite(&shop[i], sizeof(struct shopping), 1, fp) != 1)
			printf("file write error\n");
	}

	fclose(fp);
}

// 数据从文件到屏幕
void lalala()
{
	FILE* fp = fopen("result.txt", "rb");
	if (fp == NULL)
	{
		printf("cannot open file\n");
		return;
	}
	for (int i = 0; i < SIZE; i++)
	{
		fread(&shop[i], sizeof(struct shopping), 1, fp);
		printf("%s %d %s %f\n", shop[i].name, shop[i].number, shop[i].give, shop[i].piece);
	}
	fclose(fp);
}

int main()
{
	load();

	qsort(shop, SIZE, sizeof(struct shopping), compare);

	save();
	lalala();

	return 0;
}
