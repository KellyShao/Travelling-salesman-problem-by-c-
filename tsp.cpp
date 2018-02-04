#include <iostream>
#include<stdlib.h>
#include <bitset>//使用bitset标准库
using namespace std;

int resultCompare = 0;

int DMatrix(int Vrow, int Vcolumn, int mode, int W[4][4],int D[4][8]) {
	int visitCity[3];
	int cnt=0;
	int result=0;
	bitset<3> t;//可改数组大小*
	t = Vcolumn;
	string str = t.to_string();//二进制表示

	if (Vcolumn == 0) {
		resultCompare = W[Vrow][0];
	}

	else {
		//计算D矩阵值
		for (int cityj = 0; cityj < (mode - 1); cityj++) {
			int citybit = 0;
			if (str[cityj] == '1') {
				cnt = cnt + 1;
				str[cityj] = '0';//D[][visitcity新]
				for (int bitcnt = 0; bitcnt < mode - 1; bitcnt++) {
					if (str[bitcnt] == '1') {
						citybit = citybit + pow(2, mode - 2 - bitcnt);//计算result存在D矩阵第几列
					}
				}

				if (Vrow == (mode - 1 - cityj)) {
					resultCompare = 0;
					break;
				}
				else {
					/*if (D[mode - 1 - cityj][citybit] < 0) {
						result = W[Vrow][mode - 1 - cityj] + DMatrix(mode - 1 - cityj, citybit, 4, W, D);
					}
					else*/
						result = W[Vrow][mode - 1 - cityj] + D[mode - 1 - cityj][citybit];
					if (cnt == 1)
						resultCompare = result;
					else {
						if (result < resultCompare)
							resultCompare = result;
					}
				}
			str[cityj] = '1';
			}
		}
	}
	return resultCompare;
}

int main() {
	int mode,modeSize;
	//cin >> "请输入节点个数：\n">>mode;
	mode = 4;//改点多少*
	modeSize = pow(2 ,mode-1);//可改*

	int W[4][4] = { { 0,3,6,7 },{ 5,0,2,3 },{ 6,4,0,2 },{ 3,7,5,0 } };
	int D[4][8];

	//Matrix读入第一列
	for (int zerocolumn_row = 0; zerocolumn_row < mode; zerocolumn_row++) {//初始化第一行,减少循环次数
		D[zerocolumn_row][0] = W[zerocolumn_row][0];
	}

	//Matrix读入第一行
	for (int zerorow_column = 0; zerorow_column < (modeSize - 1); zerorow_column++) {
		D[0][zerorow_column] = 0;
	}

	for (int columni = 1; columni < (modeSize - 1); columni++) {
		for (int rowi = 1; rowi < mode; rowi++) {
			D[rowi][columni] = DMatrix(rowi, columni, mode, W, D);
		}
	}

	//Matrix读入最后一列
	for (int lastcolumn_row = 0; lastcolumn_row < mode; lastcolumn_row++) {
		if (lastcolumn_row == 0)
			D[0][modeSize - 1] = DMatrix(0, modeSize - 1, mode, W, D);
		else
			D[lastcolumn_row][modeSize - 1] = 0;
	}

	cout << "最短路径为：" << D[0][modeSize - 1]<<"\n";
	//cout<<"路径顺序为："<<
	}
	
	


