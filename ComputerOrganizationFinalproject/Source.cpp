#include<iostream>
#include<fstream>
#include <string>
using namespace std;

char instructarr[6][4];//�s���O �U�@�B�Jcolumn+1
int checkline = 0;
string inputinstruct;
bool IFdone = false, IDdone = false, EXdone = false, MEMdone = false, WBdone = false;
int Register[32], Memory[32], RegDst, ALUSrc, Branch, MemRead, MemWrite, RegWrite, MemtoReg;
int rs[4], rt[4], rd[4], address[4];//0��ID���q  1��EX  2��MEM 3��WB
int EXoutput[3];//0��EX 1��MEM 2��WB
int MEMoutput;
void IF()
{
	fstream input;
	input.open("memory.txt", ios::in);
	for (int j = 0; j <= checkline; j++)
	{
		if (getline(input, inputinstruct))
		{
			if (checkline == j)//Ū�X���N�q�ĴX��}�lŪ
			{
				for (int i = 0; i < 3; i++)
				{
					instructarr[0][i] = inputinstruct[i];
				}
			}
		}
	}
	input.close();
	fstream output;
	output.open("result.txt", ios::out | ios::app);
	if (instructarr[0][0] != NULL)//�ū��O���L
	{
		output << instructarr[0] << ":IF" << endl;
	}
	output.close();
	for (int i = 0; i < 3; i++) //����O�ǤU�h
	{
		instructarr[1][i] = instructarr[0][i];
	}
	checkline++;
	IFdone = true;//IF����
	IDdone = false;//��ID
}
void ID()
{

	if (instructarr[1][0] == 'a' || (instructarr[1][0] == 's'&&instructarr[1][1] == 'u'))//add&sub ���Ȧs����
	{	
		RegDst = 1, ALUSrc = 0, Branch = 0, MemRead = 0, MemWrite = 0, RegWrite = 1, MemtoReg = 0;
		if (inputinstruct[6] <= 57 && inputinstruct[6] >= 48) //rd�����
		{
			rd[0] = ((int)(inputinstruct[5] - 48)) * 10 + (int)(inputinstruct[6] - 48);
			if (inputinstruct[11] <= 57 && inputinstruct[11] >= 48) //rd����ƥBrs�����
			{
				rs[0] = ((int)(inputinstruct[10] - 48)) * 10 + (int)(inputinstruct[11] - 48);
				if (inputinstruct[16] <= 57 && inputinstruct[16] >= 48) //rd����ƥBrs����ƥBrt�����
				{
					rt[0] = ((int)(inputinstruct[15] - 48)) * 10 + (int)(inputinstruct[16] - 48);
				}
				else //rd����ƥBrs����ƥBrt����
				{
					rt[0] = (int)(inputinstruct[15] - 48);
				}
			}
			else //rd����ƥBrs����
			{
				rs[0] = (int)(inputinstruct[10] - 48);
				if (inputinstruct[15] <= 57 && inputinstruct[15] >= 48) //rd����ƥBrs���ƥBrt�����
				{
					rt[0] = ((int)(inputinstruct[14] - 48)) * 10 + (int)(inputinstruct[15] - 48);
				}
				else //rd����ƥBrs���ƥBrt����
				{	
					rt[0] = (int)(inputinstruct[14] - 48);
				}
			}
		}
		else//rd����
		{
			rd[0] = (int)(inputinstruct[5] - 48);
			if (inputinstruct[10] <= 57 && inputinstruct[10] >= 48) //rd���ƥBrs�����
			{
				rs[0] = ((int)(inputinstruct[9] - 48)) * 10 + (int)(inputinstruct[10] - 48);
				if (inputinstruct[15] <= 57 && inputinstruct[15] >= 48) //rd���ƥBrs����ƥBrt�����
				{
					rt[0] = ((int)(inputinstruct[14] - 48)) * 10 + (int)(inputinstruct[15] - 48);
				}
				else //rd���ƥBrs����ƥBrt����
				{
					rt[0] = (int)(inputinstruct[14] - 48);
				}
			}
			else //rd���ƥBrs����
			{
				rs[0] = (int)(inputinstruct[9] - 48);
				if (inputinstruct[14] <= 57 && inputinstruct[14] >= 48) //rd���ƥBrs���ƥBrt�����
				{
					rt[0] = ((int)(inputinstruct[13] - 48)) * 10 + (int)(inputinstruct[14] - 48);
				}
				else //rd���ƥBrs���ƥBrt����
				{
					rt[0] = (int)(inputinstruct[13] - 48);
				}
			}
		}
	}
	
	if (instructarr[1][0] == 'l'||(instructarr[1][0] == 's'&&instructarr[1][1] == 'w')) //lw&&sw ���Ȧs����
	{
		RegDst = 0, ALUSrc = 1, Branch = 0, MemRead = 1, MemWrite = 0, RegWrite = 1, MemtoReg = 1;
		if (inputinstruct[5] <= 57 && inputinstruct[5] >= 48) //rt�����
		{
			rt[0] = ((int)(inputinstruct[4] - 48) * 10) + (int)(inputinstruct[5] - 48);
			if (inputinstruct[9] <= 57 && inputinstruct[9] >= 48) //rt�����address�����
			{
				address[0] = ((int)(inputinstruct[8] - 48) * 10) + (int)(inputinstruct[9] - 48);
				if (inputinstruct[13] <= 57 && inputinstruct[13] >= 48) //rt�����address�����rs�����
				{
					rs[0] = ((int)(inputinstruct[12] - 48) * 10) + (int)(inputinstruct[13] - 48);
				}
				else //rt�����address�����rs����
				{
					rs[0] = (int)(inputinstruct[12] - 48);
				}
			}
			else //rt�����address����
			{
				address[0] = (int)(inputinstruct[8] - 48);
				if (inputinstruct[12] <= 57 && inputinstruct[12] >= 48) //rt�����address����rs�����
				{
					rs[0] = ((int)(inputinstruct[11] - 48) * 10) + (int)(inputinstruct[12] - 48);
				}
				else //rt�����address����rs����
				{
					rs[0] = (int)(inputinstruct[11] - 48);
				}
			}
		}
		else //rt����
		{
			rt[0] = (int)(inputinstruct[4] - 48);
			if (inputinstruct[8] <= 57 && inputinstruct[8] >= 48) //rt����address�����
			{
				address[0] = ((int)(inputinstruct[7] - 48) * 10) + (int)(inputinstruct[8] - 48);
				if (inputinstruct[12] <= 57 && inputinstruct[12] >= 48) //rt����address�����rs�����
				{
					rs[0] = ((int)(inputinstruct[11] - 48) * 10) + (int)(inputinstruct[12] - 48);
				}
				else //rt����address�����rs����
				{
					rs[0] = (int)(inputinstruct[11] - 48);
				}
			}
			else //rt����address����
			{
				address[0] = (int)(inputinstruct[7] - 48);
				if (inputinstruct[11] <= 57 && inputinstruct[11] >= 48) //rt����address����rs�����
				{
					rs[0] = ((int)(inputinstruct[10] - 48) * 10) + (int)(inputinstruct[11] - 48);
				}
				else //rt����address����rs����
				{
					rs[0] = (int)(inputinstruct[10] - 48);
				}
			}
		}
	}

	if (instructarr[1][0] == 'l') //lw ���O
	{
		RegDst = 0, ALUSrc = 1, Branch = 0, MemRead = 1, MemWrite = 0, RegWrite = 1, MemtoReg = 1;
	}

	if (instructarr[1][0] == 's'&&instructarr[1][1] == 'w')//sw���O
	{
		RegDst = -1, ALUSrc = 1, Branch = 0, MemRead = 0, MemWrite = 1, RegWrite = 0, MemtoReg = -1;
	}
 

	/*if (instructarr[1][0] == 'b')	//beq
	{
		RegDst = -1, ALUSrc = 0, Branch = 1, MemRead = 0, MemWrite = 0, RegWrite = 0, MemtoReg = -1;
	}*/
	fstream output;
	output.open("result.txt", ios::out | ios::app);
	if (instructarr[1][0] != NULL)
	{
		output << instructarr[1] << ":ID" <<endl;
	}
	output.close();

	for (int i = 0; i < 3; i++)
	{
		instructarr[2][i] = instructarr[1][i];
	}

	rs[1] = rs[0];
	rt[1] = rt[0];
	rd[1] = rd[0];
	address[1] = address[0];
	if(instructarr[1][0] == 'l' || (instructarr[1][0] == 's'&&instructarr[1][1] == 'w'))cout << rt[0] << endl << address[0] << endl << rs[0] << endl;
	if (instructarr[1][0] == 'a' || (instructarr[1][0] == 's'&&instructarr[1][1] == 'u'))cout << rd[0] << endl << rs[0] << endl << rt[0] << endl;
	IDdone = true;//ID����
	EXdone = false;//��EX
}
void EX()
{
	if (instructarr[2][0] == 'a' )//add  ��ex
	{
		EXoutput[0] = Register[rs[1]] + Register[rt[1]];
	}

	if (instructarr[2][0] == 's'&&instructarr[2][1] == 'u')//sub  ��ex
	{
		EXoutput[0] = Register[rs[1]] - Register[rt[1]];
	}

	if (instructarr[2][0] == 'l' || (instructarr[2][0] == 's'&&instructarr[2][1] == 'w')) //sw lw ��ex
	{
		EXoutput[0] = Register[rs[1]] + address[1];
	}

	fstream output;
	output.open("result.txt", ios::out | ios::app);
	if (instructarr[2][0] != NULL)
	{
		output << instructarr[2] << ":EX  " ;
		if (instructarr[2][0] == 'a' || (instructarr[2][0] == 's'&&instructarr[2][1] == 'u'))
		{
			output << "10 000 10 " << endl;
		}
		if (instructarr[2][0] == 'l')
		{
			output << "01 010 11 " << endl;
		}
		if (instructarr[2][0] == 's'&&instructarr[2][1] == 'w')
		{
			output << "X1 001 0X " << endl;
		};
	}
	output.close();

	for (int i = 0; i < 3; i++)
	{
		instructarr[3][i] = instructarr[2][i];
	}

	EXoutput[1] = EXoutput[0];
	rs[2] = rs[1];
	rt[2] = rt[1];
	rd[2] = rd[1];
	address[2] = address[1];

	EXdone = true;//EX����
	MEMdone = false;//��MEM
}
void MEM()
{
	
	if (instructarr[3][0] == 'l') //memread lw
	{
		MEMoutput = Memory[EXoutput[1]/4];
	}

	if (instructarr[3][0] == 's'&&instructarr[3][1]=='w') //memwrite sw
	{
		Memory[EXoutput[1]/4] = Register[rt[2]];
	}

	EXoutput[2] = EXoutput[1];
	rs[3] = rs[2];
	rt[3] = rt[2];
	rd[3] = rd[2];
	address[3] = address[2];

	fstream output;
	output.open("result.txt", ios::out | ios::app);
	if (instructarr[3][0] != NULL)
	{
		output << instructarr[3] << ":MEM ";
		if (instructarr[3][0] == 'a' || (instructarr[3][0] == 's'&&instructarr[3][1] == 'u'))
		{
			output << "000 10 "<<endl;
		}
		if (instructarr[3][0] == 'l') 
		{
			output << "010 11 " << endl;
		}
		if (instructarr[3][0] == 's'&&instructarr[3][1] == 'w') 
		{
			output << "001 0X " << endl;
		}
	}
	output.close();

	for (int i = 0; i < 3; i++)
	{
		instructarr[4][i] = instructarr[3][i];
	}
	MEMdone = true;//MEM����
	WBdone = false;//��WB
}
void WB()
{
	if (instructarr[4][0] == 'a' || (instructarr[2][0] == 's'&&instructarr[2][1] == 'u'))//add sub WB
	{
		Register[rd[3]]=EXoutput[2];
	}

	if (instructarr[4][0] == 'l') // lw WB
	{
		Register[rt[3]]= MEMoutput;
	}

	fstream output;
	output.open("result.txt", ios::out | ios::app);
	if (instructarr[4][0] != NULL)
	{
		output << instructarr[4] << ":WB ";
		if (instructarr[4][0] == 'a' || (instructarr[4][0] == 's'&&instructarr[4][1] == 'u'))
		{
			output << "10 " << endl;
		}
		if (instructarr[4][0] == 'l')
		{
			output << "11 " << endl;
		}
		if (instructarr[4][0] == 's'&&instructarr[4][1] == 'w')
		{
			output << " 0X " << endl;
		}
	}
	output.close();
	WBdone = true;//WB����
}
int main()
{
	for (int i = 0; i < 32; i++)
	{
		Register[i] = 1;
		Memory[i] = 1;
	}
	Register[0] = 0;
	int num = 0,cycle=0;
	fstream clean;
	clean.open("result.txt", ios::out | ios::trunc);//�M��result.txt
	clean.close();
	fstream count;
	count.open("memory.txt", ios::in);
	while (getline(count, inputinstruct))  num++;
	count.close();
	while (true)
	{
		cycle++;
		if (!WBdone)
		{
			WB();
		}
		if (!MEMdone)
		{
			MEM();
		}
		if (!EXdone)
		{
			EX();
		}
		if (!IDdone)
		{
			ID();
		}
		if (checkline == num)  IFdone = true;//��IF�S���O��,�S�H��ID,ID���A����,�H������
		else
		{
			IF();
		}
		fstream output;
		output.open("result.txt", ios::out | ios::app);
		output << endl;
		output.close();
		if (IFdone && IDdone && EXdone && MEMdone && WBdone)break;//���d�����ɭ�=����
	}
	fstream output;
	output.open("result.txt", ios::out | ios::app);
	output << "�ݭn��"<<cycle<<"��cycles"<<endl;
	for (int i = 0; i < 21; i++) //$�ƪ�
	{
		output << " $" << i;
	}
	output << endl;
	for (int i = 0; i < 10; i++)
	{
		output << "  " << Register[i];
	}
	for (int i = 10; i < 21; i++)
	{
		output << "   " << Register[i];
	}
	output << endl;
	for (int i = 21; i < 32; i++)
	{
		output << " $" << i;
	}
	output << endl;
	for (int i = 21; i < 32; i++)
	{
		output << "   " << Register[i];
	}
	output << endl << endl;

	for (int i = 0; i < 21; i++) //word�ƪ�
	{
		output << " W" << i;
	}
	output << endl ;
	for (int i = 0; i < 10; i++)
	{
		output << "  " << Memory[i];
	}
	for (int i = 10; i < 21; i++)
	{
		output << "   " << Memory[i];
	}
	output << endl;
	for (int i = 21; i < 32; i++)
	{
		output << " W" << i;
	}
	output << endl;
	for (int i = 21; i < 32; i++)
	{
		output << "   " << Memory[i];
	}
	output << endl;
	output.close();
}
