#include<stdio.h>
#include<math.h>
#include<string.h>
#include <math.h>


int passwdmeter(char *passwd)
{
	int i = 0;
	//1.密码长度
	int passwdlen;
	passwdlen = strlen(passwd);
 
	//2~5.大小写字母个数,数字个数,符号个数
	int UppercaseLetters = 0;
	int LowercaseLetters = 0;
	int Numbers = 0,Symbols = 0;
	for(i = 0;i < passwdlen; i++)
	{
		if (passwd[i]>='a' && passwd[i] <= 'z')
			LowercaseLetters++;
		else if (passwd[i]>='A' && passwd[i] <= 'Z')
			UppercaseLetters++;
		else if(passwd[i]>='0' && passwd[i] <= '9')
			Numbers++;
		else
			Symbols++;
	}
	
	//6.位于中间的数字或符号
	int MiddleNumbersorSymbols = Numbers+Symbols;
 
	if (passwd[0]>='a' && passwd[0] <= 'z') ;
	else if (passwd[0]>='A' && passwd[0] <= 'Z') ;
	else if(passwd[0]>='0' && passwd[0] <= '9')
		MiddleNumbersorSymbols--;
	else
		MiddleNumbersorSymbols--;
	
	if (passwd[passwdlen - 1]>='a' && passwd[passwdlen - 1] <= 'z') ;
	else if (passwd[passwdlen - 1]>='A' && passwd[passwdlen - 1] <= 'Z') ;
	else if(passwd[passwdlen - 1]>='0' && passwd[passwdlen - 1] <= '9')
		MiddleNumbersorSymbols--;
	else
		MiddleNumbersorSymbols--;
 
	//7.最低条件得分
	int Requirements = 0;
	if(UppercaseLetters > 0)Requirements++;
	if(LowercaseLetters > 0)Requirements++;
	if(Numbers > 0)Requirements++;
	if(Symbols > 0)Requirements++;
	if(passwdlen > 8)Requirements++;
 
	//总加得分
	int Bonus = passwdlen*4 + Symbols*6 + MiddleNumbersorSymbols*2;
	if (UppercaseLetters)Bonus+= (passwdlen - UppercaseLetters)*2;
	if (LowercaseLetters)Bonus+= (passwdlen - LowercaseLetters)*2;
	if (Requirements > 3)Bonus+= Requirements*2;
	if (Numbers != passwdlen)Bonus+= Numbers*4;
 
	//1.只有字母
	int LettersOnly = 0;
	if (UppercaseLetters + LowercaseLetters == passwdlen)
		LettersOnly = passwdlen;
 
	//2.只有数字
	int NumbersOnly = 0;
	if (Numbers == passwdlen)
		NumbersOnly = passwdlen;
 
	//3.重复字符数（大小写敏感）
	int RepeatCharacters = 0;
	int repChar = 0;
	for(i = 0; i < passwdlen; i++) {
		int exists = 0;
		int j = 0;
		for (j = 0; j < passwdlen; j++) {
		    if (passwd[i] == passwd[j] && i != j) {
		        exists = 1;
		        RepeatCharacters += abs(passwdlen/(j-i));
		    }
		}
		if (exists) {
		    repChar++;
		    int unqChar = passwdlen - repChar;
		    ///RepeatCharacters = (unqChar) ? ceil(RepeatCharacters/(double)unqChar) : ceil(RepeatCharacters);
                   if (unqChar > 0)
                   {
                       double rt = RepeatCharacters/(double)unqChar;
                       RepeatCharacters = (int)ceil(rt);
                   }


		}
	}
 
	//4~6.连续大小写字母，数字
	int ConsecutiveUppercaseLetters = 0;
	int ConsecutiveLowercaseLetters = 0;
	int ConsecutiveNumbers			= 0;
 
	int flag = 0;//1-小写，2-大写，3-数字
	int count = 0;
	for(i = 0 ;i < passwdlen;i++)
	{
		if(i == 0){
			if (passwd[i]>='a' && passwd[i] <= 'z'){flag = 1;count = 1;}
			else if (passwd[i]>='A' && passwd[i] <= 'Z'){flag = 2;count = 1;}
			else if(passwd[i]>='0' && passwd[i] <= '9'){flag = 3;count = 1;}
		}else
		{
			int tmpflag = 0;
			if (passwd[i]>='a' && passwd[i] <= 'z')
			{
				tmpflag = 1;
			}
			else if (passwd[i]>='A' && passwd[i] <= 'Z')
			{
				tmpflag = 2;
			}
			else if(passwd[i]>='0' && passwd[i] <= '9')
			{
				tmpflag = 3;
			}else
			{
				tmpflag = 0;
			}
 
			if(tmpflag == flag)
				count++;
			else
			{
				if(count >= 2)
				{
					switch(flag)
					{
						case 1:
							ConsecutiveLowercaseLetters += count-1;break;
						case 2:
							ConsecutiveUppercaseLetters += count-1;break;
						case 3:
							ConsecutiveNumbers += count-1;break;
						default:
						break;
					}
				}
				flag = tmpflag;
				count = 1;
			}
		}
	}
 
	if(count >= 2)
	{
		switch(flag)
		{
			case 1:
				ConsecutiveLowercaseLetters += count-1;break;
			case 2:
				ConsecutiveUppercaseLetters += count-1;break;
			case 3:
				ConsecutiveNumbers += count-1;break;
			default:
			break;
		}
	}
	
	//7~9 正序或者逆序的字母数字及符号
	int SequentialLetters = 0;
 
	int Sequenflag = 0;//1-正序，2-反序
	int Sequencount = 1; 
	for(i = 1 ;i < passwdlen;i++)
	{
		int value = passwd[i];
		if(passwd[i]>='a' && passwd[i] <= 'z' && passwd[i-1]>='A' && passwd[i-1] <= 'Z')
			value = passwd[i] - 32;
		else if(passwd[i-1]>='a' && passwd[i-1] <= 'z' && passwd[i]>='A' && passwd[i] <= 'Z')
			value = passwd[i] + 32;
		
		int tmpflag = 0;
		if (value - 1 == passwd[i-1])
		{
			tmpflag = 1;
		}else if (value + 1 == passwd[i-1])
			tmpflag = 2;
		else 
			tmpflag = 0;
 
		if(Sequenflag == 0 && tmpflag != 0)
		{
			Sequencount = 1;
			Sequenflag = tmpflag;
		}
		
		if (tmpflag == Sequenflag)
		{
			Sequencount++;
		}else
		{
			if(Sequencount >= 3 && Sequenflag != 0)
				SequentialLetters += Sequencount-2;
 
			Sequencount = 1;
			Sequenflag = tmpflag;
		}
	}
 
	if(Sequencount >= 3 && Sequenflag != 0)
		SequentialLetters += Sequencount-2;
	
	//减分项计算
	int Bonus2 = LettersOnly + NumbersOnly + RepeatCharacters + (ConsecutiveUppercaseLetters+ConsecutiveLowercaseLetters+ConsecutiveNumbers)*2 + SequentialLetters*3;
 
	int sum = 0;
	if (Bonus - Bonus2 < 0)
		return 0;
 
	return (Bonus - Bonus2) > 100?100:(Bonus - Bonus2);
}


void main(int argc, char **argv)
{
if (2 != argc)
{
 printf("please input one parameter!\n");
}

printf("command name=%s, parameter=%s\n", argv[0], argv[1]);

char *passwd = argv[1];
int score = passwdmeter(passwd);

printf("the final score is: %d\n\n", score);
}
