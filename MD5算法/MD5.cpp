#include<iostream>
#include<fstream>
#include<functional>
#include<iomanip>
using namespace std;
class MD5Code
{
public:
	unsigned char* get(char* fileName)
	{
		init();
		if (!getFileLength(fileName))
			return nullptr;
		getData(fileName);
		return MD5;
	}
	void save(char* fileName)
	{
		if (!get(fileName))
			return;
		fout.open("MD5.txt", ios::out);
		if (!fout.is_open())
			cout << "输出失败" << endl;
		for (int i = 0; i < 16; i++)
			fout << setw(2)<<setfill('0')<<hex << (unsigned int)MD5[i];
		fout.close();
	}
private:
	void init()
	{
		MD5[0] = 0x01;
		MD5[1] = 0x23;
		MD5[2] = 0x45;
		MD5[3] = 0x67;
		MD5[4] = 0x89;
		MD5[5] = 0xAB;
		MD5[6] = 0xCD;
		MD5[7] = 0xEF;
		MD5[8] = 0xFE;
		MD5[9] = 0xDC;
		MD5[10] = 0xBA;
		MD5[11] = 0x98;
		MD5[12] = 0x76;
		MD5[13] = 0x54;
		MD5[14] = 0x32;
		MD5[15] = 0x10;
		long long fDataBytes = 0;
	}
	bool getFileLength(char* fileName)
	{
		fin.open(fileName, ios::in);
		if (!fin.is_open())
		{
			cout << "文件打开失败!" << endl;
			return false;
		}
		fin.seekg(0, ios::end);
		fDataBytes = fin.tellg();
		return true;
	}
	void getData(char* fileName)
	{
		fin.seekg(0, ios::beg);
		int nRes = fin.is_open();
		long long groupNum = fDataBytes / 64;
		int	lastGroup = fDataBytes % 64;
		for (int i = 0; i < groupNum; i++)
		{
			char group[64] = { 0 };
			fin.read(group, 64);
			GetMD5(group);
		}
		if (lastGroup > 0 && lastGroup <= 56)
		{
			char str[64] = { 0 };
			long long count = fin.read(str, 64).gcount();
			*(unsigned long long*)(str + 56) = fDataBytes * 8;
			if (count < 56)
			{
				str[count] = -128;
			}
			GetMD5(str);
		}
		else if (0 == lastGroup)
		{
			char str[64] = { 0 };
			str[0] = -128;
			*(unsigned long long*)(str + 56) = fDataBytes * 8;
			for (int i = 1; i < 56; i++)
				str[i] = 0;
			GetMD5(str);
		}
		else if (lastGroup > 56)
		{
			char preStr[64] = { 0 };
			long long count = fin.read(preStr, 64).gcount();
			preStr[count] = -128;
			GetMD5(preStr);
			char lastStr[64] = { 0 };
			*(unsigned long long*)(lastStr + 56) = fDataBytes * 8;
			GetMD5(lastStr);
		}
		fin.close();
	}
	void GetMD5(char data[64])
	{
		unsigned int* pData = (unsigned int*)data;
		unsigned int A = pMD5[0];
		unsigned int B = pMD5[1];
		unsigned int C = pMD5[2];
		unsigned int D = pMD5[3];
		fun = [](unsigned int x, unsigned int y, unsigned int z) {return ((x & y) | ((~x) & z)); };
		A = newMD5(A, B, C, D, fun, pData[0], CS64[0], CS16[0]);
		D = newMD5(D, A, B, C, fun, pData[1], CS64[1], CS16[1]);
		C = newMD5(C, D, A, B, fun, pData[2], CS64[2], CS16[2]);
		B = newMD5(B, C, D, A, fun, pData[3], CS64[3], CS16[3]);
		A = newMD5(A, B, C, D, fun, pData[4], CS64[4], CS16[0]);
		D = newMD5(D, A, B, C, fun, pData[5], CS64[5], CS16[1]);
		C = newMD5(C, D, A, B, fun, pData[6], CS64[6], CS16[2]);
		B = newMD5(B, C, D, A, fun, pData[7], CS64[7], CS16[3]);
		A = newMD5(A, B, C, D, fun, pData[8], CS64[8], CS16[0]);
		D = newMD5(D, A, B, C, fun, pData[9], CS64[9], CS16[1]);
		C = newMD5(C, D, A, B, fun, pData[10], CS64[10], CS16[2]);
		B = newMD5(B, C, D, A, fun, pData[11], CS64[11], CS16[3]);
		A = newMD5(A, B, C, D, fun, pData[12], CS64[12], CS16[0]);
		D = newMD5(D, A, B, C, fun, pData[13], CS64[13], CS16[1]);
		C = newMD5(C, D, A, B, fun, pData[14], CS64[14], CS16[2]);
		B = newMD5(B, C, D, A, fun, pData[15], CS64[15], CS16[3]);
		fun = [](unsigned int x, unsigned int y, unsigned int z) {return ((x & z) | (y & (~z))); };
		A = newMD5(A, B, C, D, fun, pData[1], CS64[16], CS16[4]);
		D = newMD5(D, A, B, C, fun, pData[6], CS64[17], CS16[5]);
		C = newMD5(C, D, A, B, fun, pData[11], CS64[18], CS16[6]);
		B = newMD5(B, C, D, A, fun, pData[0], CS64[19], CS16[7]);
		A = newMD5(A, B, C, D, fun, pData[5], CS64[20], CS16[4]);
		D = newMD5(D, A, B, C, fun, pData[10], CS64[21], CS16[5]);
		C = newMD5(C, D, A, B, fun, pData[15], CS64[22], CS16[6]);
		B = newMD5(B, C, D, A, fun, pData[4], CS64[23], CS16[7]);
		A = newMD5(A, B, C, D, fun, pData[9], CS64[24], CS16[4]);
		D = newMD5(D, A, B, C, fun, pData[14], CS64[25], CS16[5]);
		C = newMD5(C, D, A, B, fun, pData[3], CS64[26], CS16[6]);
		B = newMD5(B, C, D, A, fun, pData[8], CS64[27], CS16[7]);
		A = newMD5(A, B, C, D, fun, pData[13], CS64[28], CS16[4]);
		D = newMD5(D, A, B, C, fun, pData[2], CS64[29], CS16[5]);
		C = newMD5(C, D, A, B, fun, pData[7], CS64[30], CS16[6]);
		B = newMD5(B, C, D, A, fun, pData[12], CS64[31], CS16[7]);
		fun = [](unsigned int x, unsigned int y, unsigned int z) {return (x ^ y ^ z); };
		A = newMD5(A, B, C, D, fun, pData[5], CS64[32], CS16[8]);
		D = newMD5(D, A, B, C, fun, pData[8], CS64[33], CS16[9]);
		C = newMD5(C, D, A, B, fun, pData[11], CS64[34], CS16[10]);
		B = newMD5(B, C, D, A, fun, pData[14], CS64[35], CS16[11]);
		A = newMD5(A, B, C, D, fun, pData[1], CS64[36], CS16[8]);
		D = newMD5(D, A, B, C, fun, pData[4], CS64[37], CS16[9]);
		C = newMD5(C, D, A, B, fun, pData[7], CS64[38], CS16[10]);
		B = newMD5(B, C, D, A, fun, pData[10], CS64[39], CS16[11]);
		A = newMD5(A, B, C, D, fun, pData[13], CS64[40], CS16[8]);
		D = newMD5(D, A, B, C, fun, pData[0], CS64[41], CS16[9]);
		C = newMD5(C, D, A, B, fun, pData[3], CS64[42], CS16[10]);
		B = newMD5(B, C, D, A, fun, pData[6], CS64[43], CS16[11]);
		A = newMD5(A, B, C, D, fun, pData[9], CS64[44], CS16[8]);
		D = newMD5(D, A, B, C, fun, pData[12], CS64[45], CS16[9]);
		C = newMD5(C, D, A, B, fun, pData[15], CS64[46], CS16[10]);
		B = newMD5(B, C, D, A, fun, pData[2], CS64[47], CS16[11]);
		fun = [](unsigned int x, unsigned int y, unsigned int z) {return (y ^ (x | (~z))); };
		A = newMD5(A, B, C, D, fun, pData[0], CS64[48], CS16[12]);
		D = newMD5(D, A, B, C, fun, pData[7], CS64[49], CS16[13]);
		C = newMD5(C, D, A, B, fun, pData[14], CS64[50], CS16[14]);
		B = newMD5(B, C, D, A, fun, pData[5], CS64[51], CS16[15]);
		A = newMD5(A, B, C, D, fun, pData[12], CS64[52], CS16[12]);
		D = newMD5(D, A, B, C, fun, pData[3], CS64[53], CS16[13]);
		C = newMD5(C, D, A, B, fun, pData[10], CS64[54], CS16[14]);
		B = newMD5(B, C, D, A, fun, pData[1], CS64[55], CS16[15]);
		A = newMD5(A, B, C, D, fun, pData[8], CS64[56], CS16[12]);
		D = newMD5(D, A, B, C, fun, pData[15], CS64[57], CS16[13]);
		C = newMD5(C, D, A, B, fun, pData[6], CS64[58], CS16[14]);
		B = newMD5(B, C, D, A, fun, pData[13], CS64[59], CS16[15]);
		A = newMD5(A, B, C, D, fun, pData[4], CS64[60], CS16[12]);
		D = newMD5(D, A, B, C, fun, pData[11], CS64[61], CS16[13]);
		C = newMD5(C, D, A, B, fun, pData[2], CS64[62], CS16[14]);
		B = newMD5(B, C, D, A, fun, pData[9], CS64[63], CS16[15]);

		pMD5[0] += A;
		pMD5[1] += B;
		pMD5[2] += C;
		pMD5[3] += D;
	}
	unsigned int newMD5(unsigned int md1, unsigned int md2, unsigned int md3, unsigned int md4,
		function<unsigned int(unsigned int, unsigned int, unsigned int)> fun, unsigned int data, unsigned int cs64, unsigned int cs16)
	{
		unsigned int md5_new = md1 + fun(md2, md3, md4) + data + cs64;
		md5_new = (md5_new << cs16) | (md5_new >> (32 - cs16));
		md1 = md2 + md5_new;
		return md1;
	}
private:
	long long fDataBytes=0;
	unsigned int CS16[16] = { 7,12,17,22,5,9,14,20,4,11,16,23,6,10,15,21 };
	unsigned char MD5[16] = { 0 };
	unsigned int* pMD5 = (unsigned int*)MD5;
	unsigned int CS64[64] = { 3614090360,3905402710,606105819,3250441966,4118548399,1200080426,2821735955,4249261313,1770035416,
		2336552879,4294925233,2304563134,1804603682,4254626195,2792965006,1236535329,4129170786,3225465664,643717713,3921069994,
		3593408605,38016083,3634488961,3889429448,568446438,3275163606,4107603335,1163531501,2850285829,4243563512,1735328473,
		2368359562,4294588738,2272392833,1839030562,4259657740,2763975236,1272893353,4139469664,3200236656,681279174,3936430074,
		3572445317,76029189,3654602809,3873151461,530742520,3299628645,4096336452,1126891415,2878612391,4237533241,1700485571,
		2399980690,4293915773,2240044497,1873313359,4264355552,2734768916,1309151649,4149444226,3174756917,718787259,3951481745 };
	ifstream fin;
	ofstream fout;
	function<unsigned int(unsigned int, unsigned int, unsigned int)>fun;
};
int main(int argc, char* argv[])
{
	MD5Code().save(argv[1]);
	system("pause");
	return 0;
}