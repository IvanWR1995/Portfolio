#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include<wchar.h>
#define CODE_SPACE 32
/*������������ ���� stdio.h - � ������ ������������ ����� ���������� ������� ����� - ������, ���� � �������.
������������ ���� locale.h - ������������ ����, ������������ ��� �����������
������������ ���� wchar.h - ������������ ��� ������������� ������� �������� � ����������� �������� �����.
������������ ���� stdlib.h - ��������� ��� ������������� ������� ��� ������ � �������.
������������ ���� windows.h - ������������ ��� ����� ��������� �������� ������
*/
struct Header//��������� Header ������ ����������� ����� ��������� � ������������ dbf - �����
{
	unsigned long recnumb;//����� ������� ��������� � ��������� 4 - 8 �����
	unsigned int headDescrland, reclang;//headDescrland - ������ ������  ��������� ���. ����������� 8 -10 ����, reclang - ������ ����� ������ 10 - 12 ����� 
	wchar_t DescriptorName[255][12];//����� ������������,������������ ���������� ������� � dbf -����� 255
	int LenBox[255], count_Box;// LenBox - ������ ����� ������,count_Box - ���������� ����� � ������
};
struct List{
	
	wchar_t *DataBuf;
	struct List *Next, *Prev;
}*ListMy  = NULL;
/*������ ���������� � ������� ��������� List,������� �������� � ���� DataBuf - ������ �������� � �������� ������,
*Next - ��������� �� ��������� ������� ������, *Prev - ��������� �� ���������� ������� ������.
��� ������ �� ������� ���������� ��������� ������ :
*/
//*ListMy - ��������� �� ������ ,� ������� ����������� �������� ���� ������ ��� ����������  ��������  ��� ����������.

struct Header obj_Head;//���������� ������ � ������� ������������ ���������� ���������� ��  ��������� � ������������

/*
1)void Add(struct List **List_in,wchar_t*DataIn); - ���������� ������ �������� ������ � ����� ������.
� �������� ���������� ���������:
List_in - ����� ��������� �� ������ ������ ������ � ������� ���������� ���������� ������ �������� ������.
*DataIn - ������,������������ � ����� �������� ������

2)struct List** List_Search(struct List **List_in, unsigned long index_in)- ������� ������ �������� ������.���� �������� ������
�� ���������� ,�� ������� ���������� NULL.
� �������� ���������� ���������:
List_in - ����� ��������� �� ������ ������ ������ � ������� ���������� ���������� ������ �������� ������.
index_in -  ���������� ����� ������� ������.

3)void List_Delete(struct List **List_in)- ������� �������� ��������.� �������� ��������� ��������� ����� ���������  ,�������������
�� ������� ������(��������� � ������ 2).����� ������� ����� ������ ������� � ������� List_Search ,� ������� ����� �������������
���������� � List_Delete, ����� ������� �������.
� �������� ���������� ���������:
List_in - ����� ��������� �� ��������� ������ ������ .

4)void List_Free(struct List **List_in)- ������� �������� ����� ������.� �������� ��������� ��������� ����� ��������� �� ������ ������� ������.
� �������� ���������� ���������:
List_in - ����� ��������� �� ������ ������ ������ � ������� ���������� ���������� ������ �������� ������.

5)int List_Insert(struct List **List_in, wchar_t*DataIn) - ������� ������� �������� � ������������ ����� ������.����������  1 ,���� ������� �������� ��������� ������ ,� 0 ���� ������ ���� ��� �������� ������ 1 ��-�
� �������� ���������� ���������:
List_in - ����� ��������� �� ������,����� �������� ����������� ����� �������� .
*DataIn - ������ ������������ ��������
��� ��������� ������ ������������ ���������������� ����������� :���� "��������� ����������������",

6)int DbfToTxt(wchar_t *NameFile)
������� ������ dbf - ����� ����� ��������� ���������(����������/��������) ���������� � ������ ��������� ,� ������ ����������� ����� � txt - ����
� �������� ���������� ���������:
NameFile - ��� ������������ dbf - �����

7)int ReadBaseFile(wchar_t* NameFile); 
������� ������ dbf - �����,� ���������� ���������� ������ � ������ ��� ������������ ���������,����� ���������� ����� ���������
� �������� ���������� ���������:
NameFile - ��� ������������ dbf - �����

8)int WriteToFile(struct List **List_in, wchar_t*NameFile);
������� ������ ��������� ��������� � dbf - ����.
� �������� ���������� ���������:
NameFile - ��� ������������ dbf - �����
List_in - ����� ��������� �� ������ ,��� ������ ������ � ����� � dbf -���� .

9)void menu(wchar_t*)
������� �������� �� ����� ����,������������ ����� ������ ���� � �������� ������������� �������
� �������� ���������� ���������:
NameFile - ��� ������������ dbf - �����

10)struct List**AddToBegin(struct List **List_in, wchar_t* DataIn)
������� ���������� �������� � ������ ������.
� �������� ���������� ���������:
List_in - ����� ��������� �� ������ ������ ������ � ������� ���������� ���������� ������ �������� ������.
*DataIn - ������,������������ � ����� �������� ������

*/
void Add(struct List **List_in, wchar_t*DataIn);
struct List** List_Search(struct List **List_in,unsigned long);
void List_Delete(struct List **List_in);
void List_Free(struct List **List_in);
int List_Insert(struct List **List_in, wchar_t*DataIn);
int DbfToTxt(wchar_t *NameFile);
int ReadBaseFile(wchar_t* NameFile);
int WriteToFile(struct List **List_in, wchar_t*NameFile);
void menu(wchar_t*);
void AddToBegin(struct List **List_in, wchar_t* DataIn);

int main()
{
	wchar_t NameFile[255] = { 0 }, s[255] = {0};// ��� ������������ dbf - �����
	setlocale(LC_ALL, "russian");//��������� ������� ������ 
	unsigned test = 0;
	wprintf(L"������� ��� �������������� �����:");
	SetConsoleCP(1251);//��������� ������� ��������  ��� ������ ����� 1251
	_getws_s(NameFile,255);


	SetConsoleCP(866);//��������� ������� �������� ��� ����� 866
	if (ReadBaseFile(NameFile))//������ dbf - �����,� ���������� ���������� ������ � ������ ��� ������������ ���������,����� ���������� ����� ���������
	{
		menu(NameFile);//������ � ��������� ����
		List_Free(&ListMy);//�������� ������ � ������� ����������� �� dbf - �����
	}
	return 0;
}

void Add(struct List **List_in, wchar_t* DataIn)//������� ���������� ������� � ������
{
	struct List* temp = *List_in;// ������������ ��������� temp �� ������ ������ 
	if ((*List_in) == NULL)//�������� �� ������������� ������� ��-�� � ������,���� ������� ��-�� ���, �� �� ��������� � ���������� �������.
	{

		*List_in = (struct List*)malloc(sizeof(struct List)); //��������� ������ ��� �������
		(*List_in)->DataBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(DataIn) + 1));
		//���������� ��-��
		wcscpy((*List_in)->DataBuf, DataIn);//���������� ���������� ������,� ������� ������
		(*List_in)->Next = NULL;//��������� ��������� �� ��������� ��-� ������ � NULL,��� �������� ����� ������
		(*List_in)->Prev = NULL;//��������� ��������� �� ���������� ��-� ������ � NULL,��� ��������,��� ������ ������ �������� ������ � ������
	}
	else //������ ,���� ������ ��� �������� ��������. 
	{
		while (temp->Next != NULL)//���� ������ ���������� ��������
			temp = temp->Next;
		temp->Next = (struct List*)malloc(sizeof(struct List));//��������� ������ ��� �������
		//���������� ��-��
		if (temp->Next)
		{
			temp->Next->DataBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(DataIn) + 1));
			wcscpy(temp->Next->DataBuf, DataIn);//���������� ���������� ������,� ������� ������
			temp->Next->Next = NULL;//��������� ��������� �� ��������� ��-� ������ � NULL,��� �������� ����� ������
			temp->Next->Prev = temp;//��������� ��������� �� ���������� ��-� ������ 
		}
	}
}
struct List** List_Search(struct List **List_in, unsigned long index_in)//������� ������ ��-�� � ������
{
	struct List* temp = *List_in;// ������������ ��������� temp �� ������ ������
	unsigned long index = 0;
	while (temp != NULL)//���� ������ ���������������� ��-�� ������,���� ������ ��-�� ��� ,�� ���� ����������� ,� ������� ���������� NULL 
	{

		if (index == index_in)//��������� ������ �������� ��-�� ������ � �������,���� ������ ���������,�� ���������� �������� �� ������� �������
			return temp;
		temp = temp->Next;//��������� � ���������� ��-�� ������.
		index++;
	}
	return NULL;
}
void List_Delete(struct List **List_in)
{
	struct List* tmp = *List_in, **my_tmp = NULL;// ������������ ��������� tmp �� ��������� �������
	if (tmp)//�������� �� ������������ ���������� ��-��
	{
		if ((tmp->Prev == NULL) && (tmp->Next == NULL))//������ �������� ������������� ��-�� �� ������
		{
			free(tmp->DataBuf);
			free(tmp);
			*List_in = NULL;//��������� ����������� ��������� � NULL,��� �������� ,��� ������ ���� 
			return;
		}
		else if ((tmp->Prev != NULL) && (tmp->Next != NULL))//������  �������� �������� ������������ � �������� ������
		{
			tmp->Prev->Next = tmp->Next;//������������ Next  ����������� ��-��,�� Next ���������� ��-��
			tmp->Next->Prev = tmp->Prev;//������������ Prev  ���������� ��-��,�� Prev ���������� ��-��
		}
		else if (tmp->Next != NULL)//������  �������� ������� ��-�� ������ 
		{

			tmp = (*List_in)->Next;//������������ ��������� �� ������ ������ �� ��������� ��-�
			tmp->Prev = NULL;//��������� ���������  Prev  ����. ��-�� ������ � NULL,��� ��������,��� ������ ������ �����  �������� �������  ������
			free((*List_in)->DataBuf);
			free((*List_in));
			ListMy = tmp;
			return;

		}
		else//������ �������� ���������� ��-�� �� ������
		{

			(tmp)->Prev->Next = NULL;//��������� ���������  Next ����������� ��-�� � NULL,��� �������� ,��� �� ���������� ��������� ��-��� ������
		}
		free(tmp->DataBuf);
		free(tmp);
	}

}
void List_Free(struct List **List_in)//������� �������� ����� ������ (������ ��������� ��������������� � ������� ��-�� �� ����������)
{
	struct List *temp = *List_in, *temp_next = 0;//*temp-��������� �� ��������� ������� ������,*temp_next-��������� �� ��������� ��-� ������
	while (temp != NULL)//���� ������������ �������� ��-��� ������
	{
		temp_next = temp->Next;//����� ���������� �������� ������
		if (temp)//�������� �� ������������� ���������� ��-�� ������
		{
			free(temp->DataBuf);
			free(temp);//������� ��-� ������
		}
		temp = temp_next;//����������� ��������� �� ��������� ��-� ������ ��� ��� ������������ �������
	}
	*List_in = NULL;

}
int List_Insert(struct List **List_in, wchar_t* DataIn)//������� �������� �������� � ������,����� ����������� � ������� �������
{
	struct List *tmp = 0;//��������� � ������� ����������� ���� ��-� ������.
	if ((*List_in) && ((*List_in)->Next))
		tmp = (*List_in)->Next;//���������� ���� ��-�� 
	else
		return 0;

	(*List_in)->Next = (struct List*)malloc(sizeof(struct List));//��������� ������ ��� ����� ��-�.
	(*List_in)->Next->DataBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(DataIn) + 1));
	if ((*List_in)->Next)
	{
		(*List_in)->Next->Prev = (*List_in);//��������� ��������� �� ���������� ��-� � ������������ �������� ������ �� �������,���������� � �������
		wcscpy((*List_in)->Next->DataBuf, DataIn);//���������� ������ 
		(*List_in)->Next->Next = tmp;//� ������������ ��-�� ������������� ��������� �� ���� ��-� �� ��-� ����������� � tmp
		tmp->Prev = (*List_in)->Next;//�  ��-�� ,������������, � tmp ������������� ��������� �� ���������� ������� �� ����������� ��-� 
		return 1;
	}
}
int DbfToTxt(wchar_t *NameFile)
{
	FILE *fout = NULL, *f = NULL;
	int count_byte = 0, num_rec = 0, count_col = 0, write_count = 0, count = 0, count_space = 0;
	wchar_t *buf = NULL, *b = NULL;
	/*
	fout - ��������� �� �������������� ���� database.txt
	num_rec - ���������� ������������ � ���� �������
	count_byte - ���������� ���������� �������� ������ ����
	count_col - ����������  ���������� ����� ������
	buf - ��������� �����,���� ����������� ��������� ������ �����
	*/
	fout = fopen("database.txt", "w");//�������� ����� database.txt
	if (!(f = _wfopen(NameFile, L"r+")))
	{
		wprintf(L"���� %s �� ������.", NameFile);//����� ������ �� �������
		return 0;
	}
	buf = (wchar_t*)malloc(sizeof(wchar_t)*(obj_Head.reclang + 1));//��������� ������ ��� 1-�� ������
	if (!buf)
	{
		wprintf(L"������ ��������� ������");//����� ������ �� �������
		return 0;
	}

	for (write_count = 0; write_count != obj_Head.count_Box; write_count++)//���� ������ ���� �����,write_count - ����� ���������� ���� �����,count - ���-�� �����
	{
		b = obj_Head.DescriptorName[write_count];

		while (*b)//���� ������ �����
			fputwc(*b++, fout);
		count_space = obj_Head.LenBox[write_count] - wcslen(obj_Head.DescriptorName[write_count]);//���������� ������� ������ ����� ���� 
		//� ������ ������ ���� ��� �������������� �������
		if (count_space < 0)//�������� ���� ������ ����� ���� ������  ������ ������ ����� ���� 
			count_space = 0;


		while (count_space)//���� ������ ����������� �������� �� ������ ����
		{
			count_space--;
			fputwc(L' ', fout);//������ �������� � ����
		}

		fputwc(L'|', fout);//������ ����������� ���� ������� ��������
	}
	fputwc(L'\n', fout);

	fseek(fout, 0, SEEK_END);//��������� ��������� � txt-����� ����� ���� �����
	fseek(f, obj_Head.headDescrland + 1, SEEK_SET);//��������� ��������� � dbf-�����  �� ������ �������
	b = buf;
	fwprintf(fout, L"\n");

	for (num_rec = 0; num_rec != obj_Head.recnumb; num_rec++)//����  ������ ���� �������
	{
		for (count_col = 0; count_col != obj_Head.count_Box; count_col++)//����  ������ ���� �����
		{
			while (count_byte != obj_Head.LenBox[count_col])//���� ������ ����
			{
				*b++ = fgetwc(f);//���������� ����� ������ 
				count_byte++;//���������� �������� ��������� ��������
			}
			while (count_byte < wcslen(obj_Head.DescriptorName[count_col]))//���� ���������� ������������ ��������� ������ ����  ��� ��������������
			{
				*b++ = ' ';
				count_byte++;//���������� �������� ��������� ��������
			}
			count_byte = 0;
			*b = 0;
			fwprintf(fout, L"%s|", buf);
			b = buf;
			*b = 0;
		}
		fgetwc(f);//������ ������� ������������ ������
		fwprintf(fout, L"\n\n");//������ ��������� ����� ��� ��������� ����� �������
		b = buf;
		*b = 0;


	}

	fclose(f);//�������� dbf- �����
	fclose(fout);//�������� ���������������  ����� database.txt
	if (buf)//�������� ������ ���������� ��� �������� ��������� ������
		free(buf);
	wprintf(L" DBF-���� ��� ������������ � ������� � ����� database.txt \n");
	return 1;
}
int ReadBaseFile(wchar_t* NameFile)//������ dbf - �����,� ���������� ���������� ������ � ������ ��� ������������ ���������,����� ���������� ����� ���������

{
	FILE *f = NULL, *fout = NULL;
	int count = 0, num_rec = 0, count_col = 0;
	wchar_t buf[12] = { 0 }, *b = buf, c = 0;
	wchar_t *Data = NULL;
	/*
	f - ��������� �� ����������� ����
	fout - ��������� �� �������������� ����
	write_count - ����� ���������� ���� �����
	count - ���-�� ��������� ���� �����
	count_space - ���-�� �������� ��� ���������� ����� ���� �� ������ ������ ����
	buf - ����� ��� ���������� �������� ��������� ������.
	num_rec - ������� ���������� �������
	count_col - ������� ���������� ����� � �������
	*b - ��������� �� buf
	*/
	if (!(f = _wfopen(NameFile, L"rb")))//������� �������� �������� ����� � �������� ������
	{
		wprintf(L"���� %s �� ������.", NameFile);//����� ������ �� �������
		system("pause");
		return 0;
	}

	fseek(f, 4, SEEK_SET);//������� ���������������� � ����� ,������� �������� ��������� ������������ ������ �� pos_file ����
	for (count = 0; count != 4 / sizeof(wchar_t); count++)//���������� ����� ������� � �����
	{
		*b++ = getwc(f);
	}
	count = 0;
	memcpy(&obj_Head.recnumb, buf, 4);//������ � ���������  ����� ������� � ����� 
	obj_Head.headDescrland = getwc(f);//������ � ������ � ��������� ������ ������  ��������� ���. �����������
	obj_Head.reclang = getwc(f);
	fclose(f);
	if (!(f = _wfopen(NameFile, L"r")))
	{
		wprintf(L"���� %s �� ������.", NameFile);//����� ������ �� �������
		return 0;
	}
	while (1)//���� ������ ����� ������
	{
		//����� ��������� �� ������ ����� ����
		fseek(f, 32 * (obj_Head.count_Box+1), SEEK_SET);//������� ���������������� � ����� ,������� �������� ��������� ������������ ������ �� 32 * (obj_Head.count_Box+1) ���� 
		b = obj_Head.DescriptorName[obj_Head.count_Box];//��������� �� ����� ,��������������� ��� ������ ����� ����
		while (count != 11)//���� ������ ������� ���������� ����
		{
			c = fgetwc(f);//������ ��������� �������� � �����
			if (c == 13)//������ �������� ����� �������� ����� ������
				break;
			*b++ = c;
			count++;//���������� �������� ���������� �������� ����
		}
		count = 0;
		*b = 0;
		if (c == 13)//������ �������� ����� �������� ����� ������
			break;
		fseek(f, 32 * (obj_Head.count_Box + 1) + 16, SEEK_SET);//��������� ��������� ����� �� ������� ������ ����.
		obj_Head.LenBox[obj_Head.count_Box] = fgetwc(f);//������ ������ ����
		obj_Head.count_Box++;//���������� �������� ��������� ���� �����

	}

	Data = (wchar_t*)malloc(sizeof(wchar_t)*(obj_Head.reclang + obj_Head.count_Box * 12 + 1));// ��������� ������ ��� �������� ����� ������


	fseek(f, obj_Head.headDescrland, SEEK_SET);//��������� 
	for (num_rec = 0; num_rec != obj_Head.recnumb; num_rec++)//���� ������ � ������ ���� �������
	{
		b = Data;
		*b = 0;
		fgetwc(f);//������ ������� ������� ������ 
		for (count_col = 0; count_col != obj_Head.count_Box; count_col++)//���� ������  ���� �����
		{
			count = 0;
			while (count != obj_Head.LenBox[count_col])//���� ������ ������ ����
			{
				*b++ = fgetwc(f);//���������� ����� ������ 
				count++;//���������� �������� ��������� ��������
			}
			
		}
		*b = 0;
		Add(&ListMy, Data);//���������� ������ � ������
	}
	fclose(f);//�������� dbf-�����
	free(Data);//�������� ����� � ���� ���������� ��� ����� ��� ���������� �������� �������
	return 1;
}
int WriteToFile(struct List **List_in,wchar_t*NameFile)
/*
������� ������ ��������� ��������� � dbf - ����.
� �������� ���������� ���������:
NameFile - ��� ������������ dbf - �����
List_in - ����� ��������� �� ������ ,��� ������ ������ � ����� � dbf -���� .

*/
{
	struct List *temp = (*List_in);
	FILE *f = NULL;
	wchar_t buf_char[5] = { 0 }, *b = NULL;
	/*
	*temp - ��������� ���� struct List ��� ������ ������ ���������� �  ������  � ������ ��������������� ������  � dbf
	f - ��������� �� ����������� dbf  - ����
	buf_char - ����� ��� �������� ������ ����� �������
	*/
	if (!(f = _wfopen(NameFile, L"rb+")))
	{
		wprintf(L"���� %s �� ������.", NameFile);//����� ������ �� �������
		return 0;
	
	}
	memcpy(buf_char, &obj_Head.recnumb, 4);
	fseek(f, 4, SEEK_SET);//��������� ��������� � ���� ��� �������� ����� ������� �������� � �����
	b = buf_char;
	while (*b)//���� ������ ����� ������� �������� � �����
	{
		fputwc(*b, f);
		*b++;
	}
	fclose(f);//�������� �������������� dbf -�����
	if (!(f = _wfopen(NameFile, L"r+")))//�������� ����� ��� ������ ��������� ������
	{
		wprintf(L"���� %s �� ������.", NameFile);//����� ������ �� �������
		return 0;
	}
	fseek(f, obj_Head.headDescrland, SEEK_SET);//��������� ��������� ��������� ����� ��������� � ������������
	while (temp != NULL)//���� ������ ���� ����� �������� � ������
	{
		fwprintf(f,L" %s",temp->DataBuf);
		temp = temp->Next;//������� � ���������� �������� ������

	}
	fclose(f);//�������� �������������� dbf -�����
	return 1;

}
void menu(wchar_t* NameFile)
/*������� �������� �� ����� ����, ������������ ����� ������ ���� � �������� ������������� �������
� �������� ���������� ��������� :
NameFile - ��� ������������ dbf - �����
*/
{
	struct List  *ListFind = NULL;
	wchar_t buf[200] = {0},*Data = NULL,*b = buf,*b_cpy = 0;
	int Number_menu = 0, count = 0, index = 0, len = 0, len_Name = 0;;
	/*
	*ListFind - ��������� �� ������� ������ ,��� �������� ������ ��������� ��� ������ �� ������
	*Data - ����������� ���������� �����,��� �������� ������ ����� ������� � ������
	b_cpy - ��������� �� ����� Data
	buf - ����� ��� �������� �������� 1 -�� ���� ������ 
	*b  - ��������� �� buf
	Number_menu - ���������� � ������� ����������� ����� ���������� ����
	len - ������ ��������� �������� ����
	count - ������� ��������� �����
	len_Name - ������ ����� �������� ���� 
	*/
	Data = (wchar_t*)malloc(sizeof(wchar_t)*(obj_Head.reclang + obj_Head.count_Box * 12 + 1));//��������� ������ ��� ���������� �������� ������ ������
	while (1)//���� ������ ����
	{
		wprintf(L"1)�������� ������� �  ������ ���� ������ \n2)�������� ������� � ���� ������\n3)�������� ������� � ����� ���� ������\n4)������� ������� �� ���� ������\n");
		wprintf(L"5)��������� ��������� � dbf-�����\n6)�����\n7)���������  dbf -����  � ���� ������� txt\n");
		wprintf(L"������� ����� ���������� ����\n");
		scanf("%d", &Number_menu);//���������� ������ ����
		system("cls");//�������� ������

		switch (Number_menu)//
		{
		case 1://�����:1)�������� ������� �  ������ ���� ������ 
			b_cpy = Data;
			for (count = 0; count != obj_Head.count_Box; count++)//���������� �������� ���� �����
			{
				wprintf(L"������� ��������  ���� %s ", obj_Head.DescriptorName[count]);
				SetConsoleCP(1251);
				scanf("%S", buf);
				SetConsoleCP(866);
				len = wcslen(buf);
				len_Name = wcslen(obj_Head.DescriptorName[count]);
				b = buf + len;
				while (len != obj_Head.LenBox[count])//���� ���������� ������������ ��������� ������ ����  ��� ��������������
				{
					*b++ = L' ';
					len++;//���������� �������� ��������� ��������
					*b = 0;
				}
				b = buf;
				while (*b)//���� ������ ������ � ����� Data
				{
					*b_cpy++ = *b++;
				}
				b = buf;
				*b = 0;
			}
			*b_cpy = 0;
			obj_Head.recnumb++;//���������� �������� �������
			AddToBegin(&ListMy, Data);//���������� ��������� ������ � ������ ������
			system("pause");
			system("cls");
			break;
		case 2:/*�����:2)�������� ������� � ���� ������\n*/
			wprintf(L"����� ���������� ��������� � ���� = %d."
					L"������� ����� ��������,����� �������� ������ �������� ����� �������= \n",obj_Head.recnumb);
			
			b_cpy = Data;
			if (!scanf("%d", &index))//���������� ������ ������ ����� ������� ����������� ����� ������  � �������� ���������� ��������� �����
			{
				fflush(stdin);
				wprintf(L"������.����� ������������ ������� ������ ���� � ���������[0,%d].��� ����������� � ���� ������� ������:", obj_Head.recnumb);
				while (CODE_SPACE != getch());
				system("cls");
				break;
			}
			if ((index > obj_Head.recnumb)||(index<0))
			{
				fflush(stdin);
				wprintf(L"������.����� ������������ ������� ������ ���� � ���������[0,%d].��� ����������� � ���� ������� ������:", obj_Head.recnumb);
				while (CODE_SPACE != getch());
				system("cls");
				break;
			}
			for (count = 0; count != obj_Head.count_Box; count++)//���������� �������� ���� �����
			{
				wprintf(L"������� ��������  ���� %s ", obj_Head.DescriptorName[count]);
				SetConsoleCP(1251);
				scanf("%S", buf);
				SetConsoleCP(866);
				len = wcslen(buf);
				len_Name = wcslen(obj_Head.DescriptorName[count]);
				b = buf + len;
				while (len != obj_Head.LenBox[count])//���� ���������� ������������ ��������� ������ ����  ��� ��������������
				{
					*b++ = L' ';
					len++;//���������� �������� ��������� ��������
					*b = 0;
				}
				b = buf;
				while (*b)//���� ������ ������ � ����� Data
				{
					*b_cpy++ = *b++;
				}
				b = buf;
				*b = 0;
			}*b_cpy = 0;
			obj_Head.recnumb++;//���������� �������� �������
			ListFind=List_Search(&ListMy, index);//����� �������� ����� �������� ���� �������� ����� ������
			List_Insert(&ListFind, Data);//������� ����� ������  ������
			system("pause");
			system("cls");
			break;
		case 3://�����:1)�������� ������� �  ������ ���� ������ 
			b_cpy = Data ;
			for (count = 0; count != obj_Head.count_Box; count++)//���� ����� �������� ���� �����
			{
				wprintf(L"������� ��������  ���� %s ", obj_Head.DescriptorName[count]);
				SetConsoleCP(1251);
				scanf("%S", buf);
				SetConsoleCP(866);
				len = wcslen(buf);
				wprintf(L"%s", buf);
				len_Name = wcslen(obj_Head.DescriptorName[count]);
				b = buf + len;
				while (len != obj_Head.LenBox[count])//���� ���������� ������������ ��������� ������ ����  ��� ��������������
				{
					*b++ = L' ';
					len++;//���������� �������� ��������� ��������
					*b = 0;
				}
				b = buf;
				while (*b)//���� ������ ��������� ������ � ����� Data
				{
					*b_cpy++ = *b++;
				}
				b = buf;
				*b = 0;
			}
			*b_cpy = 0;
			obj_Head.recnumb++;//���������� �������� �������
			Add(&ListMy, Data);//��������� � ����� ������ ������
			system("pause");
			system("cls");
			break;
		case 4://�����:4)������� ������� �� ���� ������
			wprintf(L"����� ���������� ������� ������ ���� � ���������[0,%d].������� ����� ���������� ��������\n", obj_Head.recnumb);
			if(!scanf("%d", &index))//���������� ������ ��������� ������ � �������� ���������� ��������� �����
			{
				fflush(stdin);
				wprintf(L"������.����� ������������ ������� ������ ���� � ���������[0,%d].��� ����������� � ���� ������� ������:", obj_Head.recnumb);
				while (CODE_SPACE != getch());
				system("cls");
				break;
			}
			if ((index > obj_Head.recnumb) || (index<0))
			{
				fflush(stdin);
				wprintf(L"������.����� ���������� ������� ������ ���� � ���������[0,%d].��� ����������� � ���� ������� ������:", obj_Head.recnumb);
				while (CODE_SPACE != getch());
				system("cls");
				break;
			}
			ListFind = List_Search(&ListMy, index);//����� ��������� ������
			List_Delete(&ListFind);//�������� ������
			obj_Head.recnumb--;//���������� �������� �������
			system("cls");
			break;
		case 5:/*����� : 5)��������� ��������� � dbf - �����*/
			if (!WriteToFile(&ListMy, NameFile))//������ ���������� ������ � dbf - ����
			{
				if (Data)
					free(Data);
				return;
			}
			system("cls");
			break;
		case 6://�����:6)�����
			free(Data);//�������� ������ ���������� ��� ����� Data
			return;
		case 7://7)���������  dbf -����  � ���� ������� txt
			if (!WriteToFile(&ListMy, NameFile))//���������� ��������� � dbf �����
			{
				if (Data)
					free(Data);
				return;
			}
			if (!DbfToTxt(NameFile))//������ dbf - ����� � �������� ��������������� ���������� �����
			{
				if (Data)
					free(Data);
				return;
			}
			break;
		default:
			fflush(stdin);
			wprintf(L"������ ����� ������ ����.��� ����������� ������� ������: ");
			while (CODE_SPACE != getch());
				system("cls");
		}
	}
	if (Data)
		free(Data);

}
void AddToBegin(struct List **List_in, wchar_t* DataIn)
{
	(*List_in)->Prev = (struct List *)malloc(sizeof(struct List));//��������� ������ ��� ����������� ��������
	(*List_in)->Prev->DataBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(DataIn) + 1));//��������� ������ ��� ������
	wcscpy((*List_in)->Prev->DataBuf, DataIn);//���������� ���������� ������,� ������� ������
	(*List_in)->Prev->Next = (*List_in);//��������� ��������� Next � ��������� �� �������
	(*List_in)->Prev->Prev = NULL;//��������� ��������� Prev � ����������� �� NULL  
	(*List_in) = (*List_in)->Prev;//������������ ���������  � �������� �� ������ ������

}