//#include<iostream>
//#include<fstream>
//#include<bitset>
//#include<functional>
//using namespace std;
////MD5转换历程的常量
//constexpr int CS16_1 = 7;
//constexpr int CS16_2 = 12;
//constexpr int CS16_3 = 17;
//constexpr int CS16_4 = 22;
//constexpr int CS16_5 = 5;
//constexpr int CS16_6 = 9;
//constexpr int CS16_7 = 14;
//constexpr int CS16_8 = 20;
//constexpr int CS16_9 = 4;
//constexpr int CS16_10 = 11;
//constexpr int CS16_11 = 16;
//constexpr int CS16_12 = 23;
//constexpr int CS16_13 = 6;
//constexpr int CS16_14 = 10;
//constexpr int CS16_15 = 15;
//constexpr int CS16_16 = 21;
//ifstream fin;
//long fDataBytes;
////开辟一个十六字节的空间
//unsigned char md5[16] = { 0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10 };
////强转换成一个四字节的空间，pArr是一个有4个数的数组指针,这四个数也被称为幻数/缓冲器
////由于小端存储,pMD5[4]=0x10325476;
//unsigned int* pMD5 = (unsigned int*)md5;
//unsigned int cs64[64];
//void init64();
//void getFileLength(char* fileName);
//void getData(char* fileName);
//unsigned int Md5_1(unsigned int x, unsigned int y, unsigned int z);
//unsigned int Md5_2(unsigned int x, unsigned int y, unsigned int z);
//unsigned int Md5_3(unsigned int x, unsigned int y, unsigned int z);
//unsigned int Md5_4(unsigned int x, unsigned int y, unsigned int z);
//unsigned int NewMD5(unsigned int md1, unsigned int md2,
//	unsigned int md3, unsigned int md4,
//	function<unsigned int(unsigned int, unsigned int, unsigned int)> fun,unsigned int data,unsigned int cs64,unsigned int cs16);
//void GetMD5(char data[64]);
///*argc为命令行参数的个数,默认为1
//argv记录了生成的可执行的路径
//argd为系统的环境的配置目录，
//仅在当前编译器下有效
//，当用一个可执行程序打开另外一个文件时，命令行参数+1*/
//int main(int argc, char* argv[], char* argd[])
//{
//	init64();
//	//调用命令行参数
//	getFileLength(argv[1]);
//	getData(argv[1]);
//	/*MD5数据要求64字节，512位为一组,累加后再次参与运算
//	所以要求的必须是一个六十四字节，最后八个字节存储数据的总字节数
//	可以一次性读取所有数据全部读完再计算(空间换时间)，
//	也可以读64字节处理64字节（时间换空间）*/
//	fin.close();
//	for (int i = 0; i < 16; i++)
//		cout << hex<<(int)md5[i] << endl;
//	system("pause");
//	return 0;
//}
////获取文件字节数量
//
//void getFileLength(char* fileName)
//{
//	fin.open(fileName, ios::in);
//	if (!fin.is_open())
//	{
//		cout << "文件打开失败!" << endl;
//		return;
//	}
//	//将文件指针指向文件结尾
//	//这里的0是偏移量，后一个参数决定是从文件的哪个位置
//	//若使用只有一个参数则代表是绝对位置
//	fin.seekg(0, ios::end);
//	//获取位置,返回下标
//	fDataBytes = fin.tellg();
//}
//
//void getData(char* fileName)
//{
//	//先将指针回归到文件头
//	fin.seekg(0, ios::beg);
//	//以64个字节为一组
//	int nRes = fin.is_open();
//	int groupNum = fDataBytes / 64;
//	int	lastGroup = fDataBytes % 64;
//	for (int i = 0; i < groupNum; i++)
//	{
//		char group[64] = { 0 };
//		fin.read(group, 64);
//		GetMD5(group);
//	}
//	//1.0<n<56
//	if (lastGroup > 0 && lastGroup <= 56)
//	{
//		//读数据
//		char str[64] = { 0 };
//		int count = fin.read(str, 64).gcount();
//
//		//str+56为最后8个字节，指针再解引用后即可直接赋值，用来存储文件的字节数
//		//在str的首地址+56即为最后八字节的首地址,用ull即为往后读取八字节,ull是一个八字节数据
//		*(unsigned long long*)(str + 56) = fDataBytes * 8;
//		if (count < 56)
//		{
//			//str[count]为最后一个字符的下一个字节
//			//128转换为二进制10000000，因为char是unsigned int类型数据范围为-128-127(复习一下反码，补码的知识)
//			// 反码
//			//在读取的数据之后直到第56位前，用1000000....填充
//			//1byte=8bit
//			str[count] = -128;
//		}
//		/*for (int i = 0; i < 64; i++)
//		{
//			cout << str[i]<<" "<<bitset<8>(str[i]) << endl;
//		}
//		在这里验证值时，不能直接用ull转换，str+56是一个地址，要转换成别的地址类型后再解引用
//		否则，便是直接将地址的值转换成十进制输出
//		cout << *(unsigned long long*)(str + 56) << endl;*/
//		GetMD5(str);
//	}
//	else if (0 == lastGroup)
//	{
//		//在申请64字节空间
//		char str[64] = { 0 };
//		//填充10000000
//		str[0] = -128;
//		*(unsigned long long*)(str + 56) = fDataBytes * 8;
//		for (int i = 1; i < 56; i++)
//			str[i] = 0;
//		GetMD5(str);
//	}
//	else if (lastGroup > 56)
//	{
//		char preStr[64] = { 0 };
//		int count = fin.read(preStr, 64).gcount();
//		preStr[count] = -128;
//		char lastStr[64] = { 0 };
//		*(unsigned long long*)(lastStr + 56) = fDataBytes * 8;
//		GetMD5(preStr);
//		GetMD5(lastStr);
//	}
//}
//
//unsigned int Md5_1(unsigned int x, unsigned int y, unsigned int z)
//{
//	return ((x & y) | ((~x) & z));
//}
//
//unsigned int Md5_2(unsigned int x, unsigned int y, unsigned int z)
//{
//	return ((x & z) | (y & (~z)));
//}
//
//unsigned int Md5_3(unsigned int x, unsigned int y, unsigned int z)
//{
//	return (x ^ y ^ z);
//}
//
//unsigned int Md5_4(unsigned int x, unsigned int y, unsigned int z)
//{
//	return (y ^ (x | (~z)));
//}
//
//unsigned int NewMD5(unsigned int md1, unsigned int md2, unsigned int md3, unsigned int md4,
//	function<unsigned int(unsigned int, unsigned int, unsigned int)> fun, unsigned int data, unsigned int cs64, unsigned int cs16)
//{
//	unsigned int md5_new = md1 + fun(md2, md3, md4) + data + cs64;
//	md5_new = (md5_new << cs16) | (md5_new >> (32 - cs16));
//	md1 = md2 + md5_new;
//	return md1;
//}
//
//void GetMD5(char data[64])
//{
//	unsigned int* pData = (unsigned int*)data;
//	unsigned int A = pMD5[0];
//	unsigned int B = pMD5[1];
//	unsigned int C = pMD5[2];
//	unsigned int D = pMD5[3];
//	A = NewMD5(A, B, C, D, &Md5_1, pData[0], cs64[0], CS16_1);
//	D = NewMD5(D, A, B, C, &Md5_1, pData[1], cs64[1], CS16_2);
//	C = NewMD5(C, D, A, B, &Md5_1, pData[2], cs64[2], CS16_3);
//	B = NewMD5(B, C, D, A, &Md5_1, pData[3], cs64[3], CS16_4);
//	A = NewMD5(A, B, C, D, &Md5_1, pData[4], cs64[4], CS16_1);
//	D = NewMD5(D, A, B, C, &Md5_1, pData[5], cs64[5], CS16_2);
//	C = NewMD5(C, D, A, B, &Md5_1, pData[6], cs64[6], CS16_3);
//	B = NewMD5(B, C, D, A, &Md5_1, pData[7], cs64[7], CS16_4);
//	A = NewMD5(A, B, C, D, &Md5_1, pData[8], cs64[8], CS16_1);
//	D = NewMD5(D, A, B, C, &Md5_1, pData[9], cs64[9], CS16_2);
//	C = NewMD5(C, D, A, B, &Md5_1, pData[10], cs64[10], CS16_3);
//	B = NewMD5(B, C, D, A, &Md5_1, pData[11], cs64[11], CS16_4);
//	A = NewMD5(A, B, C, D, &Md5_1, pData[12], cs64[12], CS16_1);
//	D = NewMD5(D, A, B, C, &Md5_1, pData[13], cs64[13], CS16_2);
//	C = NewMD5(C, D, A, B, &Md5_1, pData[14], cs64[14], CS16_3);
//	B = NewMD5(B, C, D, A, &Md5_1, pData[15], cs64[15], CS16_4);
//
//	A = NewMD5(A, B, C, D, &Md5_2, pData[1], cs64[16], CS16_5);
//	D = NewMD5(D, A, B, C, &Md5_2, pData[6], cs64[17], CS16_6);
//	C = NewMD5(C, D, A, B, &Md5_2, pData[11], cs64[18], CS16_7);
//	B = NewMD5(B, C, D, A, &Md5_2, pData[0], cs64[19], CS16_8);
//	A = NewMD5(A, B, C, D, &Md5_2, pData[5], cs64[20], CS16_5);
//	D = NewMD5(D, A, B, C, &Md5_2, pData[10], cs64[21], CS16_6);
//	C = NewMD5(C, D, A, B, &Md5_2, pData[15], cs64[22], CS16_7);
//	B = NewMD5(B, C, D, A, &Md5_2, pData[4], cs64[23], CS16_8);
//	A = NewMD5(A, B, C, D, &Md5_2, pData[9], cs64[24], CS16_5);
//	D = NewMD5(D, A, B, C, &Md5_2, pData[14], cs64[25], CS16_6);
//	C = NewMD5(C, D, A, B, &Md5_2, pData[3], cs64[26], CS16_7);
//	B = NewMD5(B, C, D, A, &Md5_2, pData[8], cs64[27], CS16_8);
//	A = NewMD5(A, B, C, D, &Md5_2, pData[13], cs64[28], CS16_5);
//	D = NewMD5(D, A, B, C, &Md5_2, pData[2], cs64[29], CS16_6);
//	C = NewMD5(C, D, A, B, &Md5_2, pData[7], cs64[30], CS16_7);
//	B = NewMD5(B, C, D, A, &Md5_2, pData[12], cs64[31], CS16_8);
//
//	A = NewMD5(A, B, C, D, &Md5_3, pData[5], cs64[32], CS16_9);
//	D = NewMD5(D, A, B, C, &Md5_3, pData[8], cs64[33], CS16_10);
//	C = NewMD5(C, D, A, B, &Md5_3, pData[11], cs64[34], CS16_11);
//	B = NewMD5(B, C, D, A, &Md5_3, pData[14], cs64[35], CS16_12);
//	A = NewMD5(A, B, C, D, &Md5_3, pData[1], cs64[36], CS16_9);
//	D = NewMD5(D, A, B, C, &Md5_3, pData[4], cs64[37], CS16_10);
//	C = NewMD5(C, D, A, B, &Md5_3, pData[7], cs64[38], CS16_11);
//	B = NewMD5(B, C, D, A, &Md5_3, pData[10], cs64[39], CS16_12);
//	A = NewMD5(A, B, C, D, &Md5_3, pData[13], cs64[40], CS16_9);
//	D = NewMD5(D, A, B, C, &Md5_3, pData[0], cs64[41], CS16_10);
//	C = NewMD5(C, D, A, B, &Md5_3, pData[3], cs64[42], CS16_11);
//	B = NewMD5(B, C, D, A, &Md5_3, pData[6], cs64[43], CS16_12);
//	A = NewMD5(A, B, C, D, &Md5_3, pData[9], cs64[44], CS16_9);
//	D = NewMD5(D, A, B, C, &Md5_3, pData[12], cs64[45], CS16_10);
//	C = NewMD5(C, D, A, B, &Md5_3, pData[15], cs64[46], CS16_11);
//	B = NewMD5(B, C, D, A, &Md5_3, pData[2], cs64[47], CS16_12);
//
//	A = NewMD5(A, B, C, D, &Md5_4, pData[0], cs64[48], CS16_13);
//	D = NewMD5(D, A, B, C, &Md5_4, pData[7], cs64[49], CS16_14);
//	C = NewMD5(C, D, A, B, &Md5_4, pData[14], cs64[50], CS16_15);
//	B = NewMD5(B, C, D, A, &Md5_4, pData[5], cs64[51], CS16_16);
//	A = NewMD5(A, B, C, D, &Md5_4, pData[12], cs64[52], CS16_13);
//	D = NewMD5(D, A, B, C, &Md5_4, pData[3], cs64[53], CS16_14);
//	C = NewMD5(C, D, A, B, &Md5_4, pData[10], cs64[54], CS16_15);
//	B = NewMD5(B, C, D, A, &Md5_4, pData[1], cs64[55], CS16_16);
//	A = NewMD5(A, B, C, D, &Md5_4, pData[8], cs64[56], CS16_13);
//	D = NewMD5(D, A, B, C, &Md5_4, pData[15], cs64[57], CS16_14);
//	C = NewMD5(C, D, A, B, &Md5_4, pData[6], cs64[58], CS16_15);
//	B = NewMD5(B, C, D, A, &Md5_4, pData[13], cs64[59], CS16_16);
//	A = NewMD5(A, B, C, D, &Md5_4, pData[4], cs64[60], CS16_13);
//	D = NewMD5(D, A, B, C, &Md5_4, pData[11], cs64[61], CS16_14);
//	C = NewMD5(C, D, A, B, &Md5_4, pData[2], cs64[62], CS16_15);
//	B = NewMD5(B, C, D, A, &Md5_4, pData[9], cs64[63], CS16_16);
//
//	pMD5[0] += A;
//	pMD5[1] += B;
//	pMD5[2] += C;
//	pMD5[3] += D;
//}
//
//void init64()
//{
//	for (int i = 1; i <= 64; i++)
//	{
//		//4294967296*abs(sin(i))后的值的整数部分
//		//因为sin(i)是一个小于1上的数,所以要用fabs将其转换成一个浮点型的绝对值
//		//4294967296（2的32次方）unsigned int的最大值
//		cs64[i - 1] = (unsigned int)(4294967296 * fabs(sin(i)));
//	}
//}
//
//
//
////MD5算法应用，注册时候将密码转换成MD5码上传给服务器，使入侵者无法得到源账号的密码
////发送一个文件给服务器,服务器检测文件完整性
////MD5中每个字节都参与了运算
////MD5值是由16个字节32个十六进制数（1-F）组成的
//// F对应的二进制为1111,32个就是128位(16字节)
////64元素常数组
////和这样的虫豸在一起,怎么能学到东西呢？