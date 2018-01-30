#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<windows.h>
#include<wchar.h>
#define CODE_SPACE 32
/*заголовочный файл stdio.h - в данном заголовочном файле определены функции ввода - вывода, типы и макросы.
заголовочный файл locale.h - заголовочный файл, используемый для локализации
заголовочный файл wchar.h - используется для использования широких символов и поддержания русского языка.
заголовочный файл stdlib.h - подключен для использования функций для работы с памятью.
заголовочный файл windows.h - используется для смены кодировки входного потока
*/
struct Header//структура Header хранит необходимые даные заголовка и дескрипторов dbf - файла
{
	unsigned long recnumb;//число записей указанное в заголовке 4 - 8 байты
	unsigned int headDescrland, reclang;//headDescrland - полной длинны  заголовка вкл. дескрипторы 8 -10 байт, reclang - длинна одной записи 10 - 12 байты 
	wchar_t DescriptorName[255][12];//имена дескрипторов,максимальное количество которых в dbf -файле 255
	int LenBox[255], count_Box;// LenBox - длинны полей записи,count_Box - количество полей в записи
};
struct List{
	
	wchar_t *DataBuf;
	struct List *Next, *Prev;
}*ListMy  = NULL;
/*Список реализован с помощью структуры List,которая содержит в себе DataBuf - данные хранимые в элементе списка,
*Next - указатель на следующий элемент списка, *Prev - указатель на предыдущий элемент списка.
Для работы со списком реализоваы следующие методы :
*/
//*ListMy - указатель на список ,в который добавляются элементы базы данных для выполнения  операций  над элементами.

struct Header obj_Head;//глобальный объект в который записывается причитаная информация из  заголовка и дескрипторов

/*
1)void Add(struct List **List_in,wchar_t*DataIn); - добавление нового элемента списка в конец списка.
В качестве аргументов принимает:
List_in - адрес указателя на первый элемет списка в который происходит добавление нового элемента списка.
*DataIn - данные,содержащтеся в новом элементе списка

2)struct List** List_Search(struct List **List_in, unsigned long index_in)- функция поиска элемента списка.Если элемента списка
не существует ,то функция возвращает NULL.
В качестве аргументов принимает:
List_in - адрес указателя на первый элемет списка в который происходит добавление нового элемента списка.
index_in -  порядковый номер искомых данных.

3)void List_Delete(struct List **List_in)- функция удаления элемента.В качестве параметра принимает адрес указателя  ,возвращенного
из функции поиска(описанной в пункте 2).Таким образом найдя нужный элемент с помощью List_Search ,и передав адрес возвращенного
указателся в List_Delete, можно удалить элемент.
В качестве аргументов принимает:
List_in - адрес указателя на удаляемый элемет списка .

4)void List_Free(struct List **List_in)- функция удаления всего списка.В качестве аргумента принимает адрес указателя на первый элемент списка.
В качестве аргументов принимает:
List_in - адрес указателя на первый элемет списка в который происходит добавление нового элемента списка.

5)int List_Insert(struct List **List_in, wchar_t*DataIn) - функция вставки элемента в произвольное место списка.Возвращает  1 ,если вставка элемента произошла удачно ,и 0 если список пуст или содержит только 1 эл-т
В качестве аргументов принимает:
List_in - адрес указателя на элемет,после которого вставляется новый документ .
*DataIn - данные вставляемого элемента
При написании данной лабораторной руководствовался литературой :Кнут "Искусство программирования",

6)int DbfToTxt(wchar_t *NameFile)
Функция чтения dbf - файла после внесенных изменений(довавления/удаления) введенного в начале программы ,и записи прочитанных даных в txt - файл
В качестве аргументов принимает:
NameFile - имя открываемого dbf - файла

7)int ReadBaseFile(wchar_t* NameFile); 
Функция чтения dbf - файла,и добавления прочтенных данных в список для последующего изменения,также сохранения даных заголовка
В качестве аргументов принимает:
NameFile - имя открываемого dbf - файла

8)int WriteToFile(struct List **List_in, wchar_t*NameFile);
Функция записи внесенных изменений в dbf - файл.
В качестве аргументов принимает:
NameFile - имя открываемого dbf - файла
List_in - адрес указателя на список ,для записи данных в сиске в dbf -файл .

9)void menu(wchar_t*)
Функция печатает на экран меню,обрабатывает выбор пункта меню и вызывает соответвующую функцию
В качестве аргументов принимает:
NameFile - имя открываемого dbf - файла

10)struct List**AddToBegin(struct List **List_in, wchar_t* DataIn)
Функция добавления элемента в начало списка.
В качестве аргументов принимает:
List_in - адрес указателя на первый элемет списка в который происходит добавление нового элемента списка.
*DataIn - данные,содержащтеся в новом элементе списка

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
	wchar_t NameFile[255] = { 0 }, s[255] = {0};// имя открываемого dbf - файла
	setlocale(LC_ALL, "russian");//установка текущей локали 
	unsigned test = 0;
	wprintf(L"Введите имя редактируемого файла:");
	SetConsoleCP(1251);//установка кодовой страницы  для потока ввода 1251
	_getws_s(NameFile,255);


	SetConsoleCP(866);//установка кодовой страницы для ввода 866
	if (ReadBaseFile(NameFile))//чтение dbf - файла,и добавления прочтенных данных в список для последующего изменения,также сохранения даных заголовка
	{
		menu(NameFile);//печать и обработка меню
		List_Free(&ListMy);//удаление списка с данными прочтенными из dbf - файла
	}
	return 0;
}

void Add(struct List **List_in, wchar_t* DataIn)//функция добавления элемнта в список
{
	struct List* temp = *List_in;// устаналиваем укаратель temp на начало списка 
	if ((*List_in) == NULL)//проверка на существование первого эл-та в списке,если первого эл-та нет, то он создается с переданным данными.
	{

		*List_in = (struct List*)malloc(sizeof(struct List)); //выделение памяти под элемент
		(*List_in)->DataBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(DataIn) + 1));
		//Добавление эл-та
		wcscpy((*List_in)->DataBuf, DataIn);//сохранение добаляемых данных,в элемент списка
		(*List_in)->Next = NULL;//установка указателя на следующий эл-т списка в NULL,что означает конец списка
		(*List_in)->Prev = NULL;//установка указателя на предыдущий эл-т списка в NULL,что означает,что данный элемнт является первым в списке
	}
	else //случай ,если список уже содержит элементы. 
	{
		while (temp->Next != NULL)//цикл поиска последнего элемента
			temp = temp->Next;
		temp->Next = (struct List*)malloc(sizeof(struct List));//выделение памяти под элемент
		//Добавление эл-та
		if (temp->Next)
		{
			temp->Next->DataBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(DataIn) + 1));
			wcscpy(temp->Next->DataBuf, DataIn);//сохранение добаляемых данных,в элемент списка
			temp->Next->Next = NULL;//установка указателя на следующий эл-т списка в NULL,что означает конец списка
			temp->Next->Prev = temp;//установка указателя на предыдущий эл-т списка 
		}
	}
}
struct List** List_Search(struct List **List_in, unsigned long index_in)//функция поиска эл-та в списке
{
	struct List* temp = *List_in;// устаналиваем укаратель temp на начало списка
	unsigned long index = 0;
	while (temp != NULL)//цикл поиска соответствуещего эл-та списка,если такого эл-та нет ,то цикл завершается ,и функция возвращает NULL 
	{

		if (index == index_in)//сравнивем данные текущего эл-та списка с искомым,если данные совпадают,то возвращаем укзатель на текущий элемент
			return temp;
		temp = temp->Next;//переходим к следующему эл-ту списка.
		index++;
	}
	return NULL;
}
void List_Delete(struct List **List_in)
{
	struct List* tmp = *List_in, **my_tmp = NULL;// устаналиваем укаратель tmp на удаляемый элемент
	if (tmp)//проверка на сущесвование удаляемого эл-та
	{
		if ((tmp->Prev == NULL) && (tmp->Next == NULL))//случай удаления единственного эл-та из списка
		{
			free(tmp->DataBuf);
			free(tmp);
			*List_in = NULL;//установка переданного указателя в NULL,что означает ,что список пуст 
			return;
		}
		else if ((tmp->Prev != NULL) && (tmp->Next != NULL))//случай  удаления элемента находящегося в середине списка
		{
			tmp->Prev->Next = tmp->Next;//переставляем Next  предыдущего эл-та,на Next удаляемого эл-та
			tmp->Next->Prev = tmp->Prev;//переставляем Prev  следующего эл-та,на Prev удаляемого эл-та
		}
		else if (tmp->Next != NULL)//случай  удаления первого эл-та списка 
		{

			tmp = (*List_in)->Next;//переставляем указатель на начало списка на следующий эл-т
			tmp->Prev = NULL;//установка указателя  Prev  след. эл-та списка в NULL,что означает,что данный элемнт будет  является началом  списка
			free((*List_in)->DataBuf);
			free((*List_in));
			ListMy = tmp;
			return;

		}
		else//случай удаления последнего эл-та из списка
		{

			(tmp)->Prev->Next = NULL;//установка указателя  Next предыдущего эл-та в NULL,что означает ,что он становится последним эл-том списка
		}
		free(tmp->DataBuf);
		free(tmp);
	}

}
void List_Free(struct List **List_in)//функция удаления всего списка (список удаляется последовательно с первого эл-та до последнего)
{
	struct List *temp = *List_in, *temp_next = 0;//*temp-указатель на удаляемый эдемент списка,*temp_next-указатель на следующий эл-т списка
	while (temp != NULL)//цикл поочередного удаления эл-тов списка
	{
		temp_next = temp->Next;//адрес следующего элемента списка
		if (temp)//проверка на существование удаляемого эл-та списка
		{
			free(temp->DataBuf);
			free(temp);//удаляем эл-т списка
		}
		temp = temp_next;//передвигаем указатель на следующий эл-т списка для его последующего удления
	}
	*List_in = NULL;

}
int List_Insert(struct List **List_in, wchar_t* DataIn)//функция встравки элемента в список,после переданного в функцию элемета
{
	struct List *tmp = 0;//указатель в который сохраняется след эл-т списка.
	if ((*List_in) && ((*List_in)->Next))
		tmp = (*List_in)->Next;//сохранение след эл-та 
	else
		return 0;

	(*List_in)->Next = (struct List*)malloc(sizeof(struct List));//выделение памяти под новый эл-т.
	(*List_in)->Next->DataBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(DataIn) + 1));
	if ((*List_in)->Next)
	{
		(*List_in)->Next->Prev = (*List_in);//установка указателя на предыдущий эл-т у вставляемого элемента списка на текущий,переданный в функцию
		wcscpy((*List_in)->Next->DataBuf, DataIn);//сохранение данных 
		(*List_in)->Next->Next = tmp;//у вставляемого эл-та устанавливаем указатель на след эл-т на эл-т сохраненный в tmp
		tmp->Prev = (*List_in)->Next;//у  эл-та ,сохраненного, в tmp устанавливаем указатель на предыдущий элемент на вставленный эл-т 
		return 1;
	}
}
int DbfToTxt(wchar_t *NameFile)
{
	FILE *fout = NULL, *f = NULL;
	int count_byte = 0, num_rec = 0, count_col = 0, write_count = 0, count = 0, count_space = 0;
	wchar_t *buf = NULL, *b = NULL;
	/*
	fout - указатель на результирующий файл database.txt
	num_rec - количество напечатанных в файл записей
	count_byte - количество записанных символов данных поля
	count_col - количество  записанных полей данных
	buf - временный буфер,куда сохраняются считанные данные полей
	*/
	fout = fopen("database.txt", "w");//открытие файла database.txt
	if (!(f = _wfopen(NameFile, L"r+")))
	{
		wprintf(L"Файл %s не найден.", NameFile);//вывод ошибки на консоль
		return 0;
	}
	buf = (wchar_t*)malloc(sizeof(wchar_t)*(obj_Head.reclang + 1));//выделение памяти под 1-ну запись
	if (!buf)
	{
		wprintf(L"Ошибка выделения памяти");//вывод ошибки на консоль
		return 0;
	}

	for (write_count = 0; write_count != obj_Head.count_Box; write_count++)//цикл записи имен полей,write_count - число записанных имен полей,count - кол-во полей
	{
		b = obj_Head.DescriptorName[write_count];

		while (*b)//цикл записи имени
			fputwc(*b++, fout);
		count_space = obj_Head.LenBox[write_count] - wcslen(obj_Head.DescriptorName[write_count]);//вычисление разницы длинны имени поля 
		//и длинны данных поля для форматирования таблицы
		if (count_space < 0)//проверка если длинна имени поля больше  длинны данных этого поля 
			count_space = 0;


		while (count_space)//цикл записи недостающих пробелов до ширины поля
		{
			count_space--;
			fputwc(L' ', fout);//запись пробелов в файл
		}

		fputwc(L'|', fout);//запись разделяющих поля таблицы символов
	}
	fputwc(L'\n', fout);

	fseek(fout, 0, SEEK_END);//установка указателя в txt-файле после имен полей
	fseek(f, obj_Head.headDescrland + 1, SEEK_SET);//установка указателя в dbf-файле  на начало записей
	b = buf;
	fwprintf(fout, L"\n");

	for (num_rec = 0; num_rec != obj_Head.recnumb; num_rec++)//цикл  печати всех записей
	{
		for (count_col = 0; count_col != obj_Head.count_Box; count_col++)//цикл  печати всех полей
		{
			while (count_byte != obj_Head.LenBox[count_col])//цикл печати поля
			{
				*b++ = fgetwc(f);//считывание полей записи 
				count_byte++;//увеличение счетчика считанных символов
			}
			while (count_byte < wcslen(obj_Head.DescriptorName[count_col]))//цикл заполнения недостающими пробелами данных поля  для форматирования
			{
				*b++ = ' ';
				count_byte++;//увеличение счетчика считанных символов
			}
			count_byte = 0;
			*b = 0;
			fwprintf(fout, L"%s|", buf);
			b = buf;
			*b = 0;
		}
		fgetwc(f);//чтение пробела разделяющего записи
		fwprintf(fout, L"\n\n");//запись переносов строк для отделения строк таблицы
		b = buf;
		*b = 0;


	}

	fclose(f);//закрытие dbf- файла
	fclose(fout);//закрытие результирующего  файла database.txt
	if (buf)//очищение памяти выделенной для хранение временных данных
		free(buf);
	wprintf(L" DBF-файл был преобразован в таблицу в файле database.txt \n");
	return 1;
}
int ReadBaseFile(wchar_t* NameFile)//чтение dbf - файла,и добавления прочтенных данных в список для последующего изменения,также сохранения даных заголовка

{
	FILE *f = NULL, *fout = NULL;
	int count = 0, num_rec = 0, count_col = 0;
	wchar_t buf[12] = { 0 }, *b = buf, c = 0;
	wchar_t *Data = NULL;
	/*
	f - указатель на считываемый файл
	fout - указатель на результирующий файл
	write_count - число записанных имен полей
	count - кол-во считанных имен полей
	count_space - кол-во пробелов для заполнения имени поля до длинны данных поля
	buf - буфер для временного хранения считанных данных.
	num_rec - счетчик количества записей
	count_col - счетчик каличества полей в записях
	*b - указатель на buf
	*/
	if (!(f = _wfopen(NameFile, L"rb")))//усливие проверки открытия файла в бинарном режиме
	{
		wprintf(L"Файл %s не найден.", NameFile);//вывод ошибки на консоль
		system("pause");
		return 0;
	}

	fseek(f, 4, SEEK_SET);//функция позиционирования в файле ,которая сдвигает указатель относительно начала на pos_file байт
	for (count = 0; count != 4 / sizeof(wchar_t); count++)//считывание числа записей в файле
	{
		*b++ = getwc(f);
	}
	count = 0;
	memcpy(&obj_Head.recnumb, buf, 4);//запись в структуру  числа записей в файле 
	obj_Head.headDescrland = getwc(f);//чтение и запись в структуру полной длинны  заголовка вкл. дескрипторы
	obj_Head.reclang = getwc(f);
	fclose(f);
	if (!(f = _wfopen(NameFile, L"r")))
	{
		wprintf(L"Файл %s не найден.", NameFile);//вывод ошибки на консоль
		return 0;
	}
	while (1)//цикл чтения полей записи
	{
		//сдвиг указателя на начало имени поля
		fseek(f, 32 * (obj_Head.count_Box+1), SEEK_SET);//функция позиционирования в файле ,которая сдвигает указатель относительно начала на 32 * (obj_Head.count_Box+1) байт 
		b = obj_Head.DescriptorName[obj_Head.count_Box];//установка на буфер ,предназначенный для записи имени поля
		while (count != 11)//цикл чтения нужного количества байт
		{
			c = fgetwc(f);//запись считанных символов в буфер
			if (c == 13)//чтение симввола конца описания полей записи
				break;
			*b++ = c;
			count++;//увеличение счетчика количества считаных байт
		}
		count = 0;
		*b = 0;
		if (c == 13)//чтение симввола конца описания полей записи
			break;
		fseek(f, 32 * (obj_Head.count_Box + 1) + 16, SEEK_SET);//установка указателя файла на позицию длинны поля.
		obj_Head.LenBox[obj_Head.count_Box] = fgetwc(f);//чтение длинны поля
		obj_Head.count_Box++;//увеличение счетчика считанных имен полей

	}

	Data = (wchar_t*)malloc(sizeof(wchar_t)*(obj_Head.reclang + obj_Head.count_Box * 12 + 1));// выделение памяти для хранения одной записи


	fseek(f, obj_Head.headDescrland, SEEK_SET);//установка 
	for (num_rec = 0; num_rec != obj_Head.recnumb; num_rec++)//цикл чтения и печати всех записей
	{
		b = Data;
		*b = 0;
		fgetwc(f);//чтение первого пробела записи 
		for (count_col = 0; count_col != obj_Head.count_Box; count_col++)//цикл чтения  всех полей
		{
			count = 0;
			while (count != obj_Head.LenBox[count_col])//цикл чтения одного поля
			{
				*b++ = fgetwc(f);//считывание полей записи 
				count++;//увеличение счетчика считанных символов
			}
			
		}
		*b = 0;
		Add(&ListMy, Data);//добавление записи в список
	}
	fclose(f);//закрытие dbf-файла
	free(Data);//очищение места в куче выделенное под буфер для временного хранения записей
	return 1;
}
int WriteToFile(struct List **List_in,wchar_t*NameFile)
/*
Функция записи внесенных изменений в dbf - файл.
В качестве аргументов принимает:
NameFile - имя открываемого dbf - файла
List_in - адрес указателя на список ,для записи данных в сиске в dbf -файл .

*/
{
	struct List *temp = (*List_in);
	FILE *f = NULL;
	wchar_t buf_char[5] = { 0 }, *b = NULL;
	/*
	*temp - указатель типа struct List для чтения данных записанных в  список  и записи редактированных данных  в dbf
	f - указатель на открываемый dbf  - файл
	buf_char - буфер для хранения нового числа записей
	*/
	if (!(f = _wfopen(NameFile, L"rb+")))
	{
		wprintf(L"Файл %s не найден.", NameFile);//вывод ошибки на консоль
		return 0;
	
	}
	memcpy(buf_char, &obj_Head.recnumb, 4);
	fseek(f, 4, SEEK_SET);//установка указателя в файл для измеения числа записей хранимых в файле
	b = buf_char;
	while (*b)//цикл записи числа записей хранимых в файле
	{
		fputwc(*b, f);
		*b++;
	}
	fclose(f);//закрытие редактируемого dbf -файла
	if (!(f = _wfopen(NameFile, L"r+")))//открытие файла для записи текстовых данных
	{
		wprintf(L"Файл %s не найден.", NameFile);//вывод ошибки на консоль
		return 0;
	}
	fseek(f, obj_Head.headDescrland, SEEK_SET);//установка файлового указателя после заголовка и дескрипторов
	while (temp != NULL)//цикл записи всех даннх хранимых в списке
	{
		fwprintf(f,L" %s",temp->DataBuf);
		temp = temp->Next;//переход к следующему элементу списка

	}
	fclose(f);//закрытие редактируемого dbf -файла
	return 1;

}
void menu(wchar_t* NameFile)
/*Функция печатает на экран меню, обрабатывает выбор пункта меню и вызывает соответвующую функцию
В качестве аргументов принимает :
NameFile - имя открываемого dbf - файла
*/
{
	struct List  *ListFind = NULL;
	wchar_t buf[200] = {0},*Data = NULL,*b = buf,*b_cpy = 0;
	int Number_menu = 0, count = 0, index = 0, len = 0, len_Name = 0;;
	/*
	*ListFind - указатель на элемент списка ,для хранения данных найденных при поиске по списку
	*Data - деномически выделяемый буфер,для хранения данных перед записью в список
	b_cpy - указатель на буфер Data
	buf - Буфер для хранения значения 1 -го поля записи 
	*b  - указатель на buf
	Number_menu - переменная в которую сохраняется номер выбранного меню
	len - длинна введеного значения поля
	count - счетчик считанных полей
	len_Name - длинна имени текущего поля 
	*/
	Data = (wchar_t*)malloc(sizeof(wchar_t)*(obj_Head.reclang + obj_Head.count_Box * 12 + 1));//выделение памяти для временного хранения данных записи
	while (1)//цикл печати меню
	{
		wprintf(L"1)Добавить элемент в  начало базы данных \n2)Вставить элемент в базу данных\n3)Добавить элемент в конец базы данных\n4)Удалить элемент из базы данных\n");
		wprintf(L"5)Сохранить изменения в dbf-файле\n6)Выход\n7)Перевести  dbf -файл  в файл формата txt\n");
		wprintf(L"Введите номер выбранного меню\n");
		scanf("%d", &Number_menu);//считывание номера меню
		system("cls");//очищение экрана

		switch (Number_menu)//
		{
		case 1://Пункт:1)Добавить элемент в  начало базы данных 
			b_cpy = Data;
			for (count = 0; count != obj_Head.count_Box; count++)//считывание значения всех полей
			{
				wprintf(L"Введите значения  поля %s ", obj_Head.DescriptorName[count]);
				SetConsoleCP(1251);
				scanf("%S", buf);
				SetConsoleCP(866);
				len = wcslen(buf);
				len_Name = wcslen(obj_Head.DescriptorName[count]);
				b = buf + len;
				while (len != obj_Head.LenBox[count])//цикл заполнения недостающими пробелами данных поля  для форматирования
				{
					*b++ = L' ';
					len++;//увеличение счетчика считанных символов
					*b = 0;
				}
				b = buf;
				while (*b)//цикл записи данных в буфер Data
				{
					*b_cpy++ = *b++;
				}
				b = buf;
				*b = 0;
			}
			*b_cpy = 0;
			obj_Head.recnumb++;//увеличение счетчика записей
			AddToBegin(&ListMy, Data);//добавление введенных данных в начало списка
			system("pause");
			system("cls");
			break;
		case 2:/*Пункт:2)Вставить элемент в базу данных\n*/
			wprintf(L"Всего количество элементов в базе = %d."
					L"Введите номер элементе,после которого хотите вставить новый элемент= \n",obj_Head.recnumb);
			
			b_cpy = Data;
			if (!scanf("%d", &index))//считывание номера записи после которой вставляются новые данные  и проверка количества считанных полей
			{
				fflush(stdin);
				wprintf(L"Ошибка.Номер вставляемого элемена должен быть в диапазоне[0,%d].Для возвращения в меню нажмите пробел:", obj_Head.recnumb);
				while (CODE_SPACE != getch());
				system("cls");
				break;
			}
			if ((index > obj_Head.recnumb)||(index<0))
			{
				fflush(stdin);
				wprintf(L"Ошибка.Номер вставляемого элемена должен быть в диапазоне[0,%d].Для возвращения в меню нажмите пробел:", obj_Head.recnumb);
				while (CODE_SPACE != getch());
				system("cls");
				break;
			}
			for (count = 0; count != obj_Head.count_Box; count++)//считывание значения всех полей
			{
				wprintf(L"Введите значения  поля %s ", obj_Head.DescriptorName[count]);
				SetConsoleCP(1251);
				scanf("%S", buf);
				SetConsoleCP(866);
				len = wcslen(buf);
				len_Name = wcslen(obj_Head.DescriptorName[count]);
				b = buf + len;
				while (len != obj_Head.LenBox[count])//цикл заполнения недостающими пробелами данных поля  для форматирования
				{
					*b++ = L' ';
					len++;//увеличение счетчика считанных символов
					*b = 0;
				}
				b = buf;
				while (*b)//цикл записи данных в буфер Data
				{
					*b_cpy++ = *b++;
				}
				b = buf;
				*b = 0;
			}*b_cpy = 0;
			obj_Head.recnumb++;//увеличение счетчика записей
			ListFind=List_Search(&ListMy, index);//Поиск элемента после которого надо вставить новые данные
			List_Insert(&ListFind, Data);//вставка новых данных  список
			system("pause");
			system("cls");
			break;
		case 3://Пункт:1)Добавить элемент в  начало базы данных 
			b_cpy = Data ;
			for (count = 0; count != obj_Head.count_Box; count++)//цикл ввода значения всех полей
			{
				wprintf(L"Введите значения  поля %s ", obj_Head.DescriptorName[count]);
				SetConsoleCP(1251);
				scanf("%S", buf);
				SetConsoleCP(866);
				len = wcslen(buf);
				wprintf(L"%s", buf);
				len_Name = wcslen(obj_Head.DescriptorName[count]);
				b = buf + len;
				while (len != obj_Head.LenBox[count])//цикл заполнения недостающими пробелами данных поля  для форматирования
				{
					*b++ = L' ';
					len++;//увеличение счетчика считанных символов
					*b = 0;
				}
				b = buf;
				while (*b)//цикл записи введенных данных в буфер Data
				{
					*b_cpy++ = *b++;
				}
				b = buf;
				*b = 0;
			}
			*b_cpy = 0;
			obj_Head.recnumb++;//увеличение счетчика записей
			Add(&ListMy, Data);//добавлние в конец списка данных
			system("pause");
			system("cls");
			break;
		case 4://Пункт:4)Удалить элемент из базы данных
			wprintf(L"Номер удаляемого элемена должен быть в диапазоне[0,%d].Введите номер удаляемого элемента\n", obj_Head.recnumb);
			if(!scanf("%d", &index))//считывание номера удаляемой записи и проверка количества считанных полей
			{
				fflush(stdin);
				wprintf(L"Ошибка.Номер вставляемого элемена должен быть в диапазоне[0,%d].Для возвращения в меню нажмите пробел:", obj_Head.recnumb);
				while (CODE_SPACE != getch());
				system("cls");
				break;
			}
			if ((index > obj_Head.recnumb) || (index<0))
			{
				fflush(stdin);
				wprintf(L"Ошибка.Номер удаляемого элемена должен быть в диапазоне[0,%d].Для возвращения в меню нажмите пробел:", obj_Head.recnumb);
				while (CODE_SPACE != getch());
				system("cls");
				break;
			}
			ListFind = List_Search(&ListMy, index);//поиск удаляемой записи
			List_Delete(&ListFind);//удаление записи
			obj_Head.recnumb--;//уменьшение счетчика записей
			system("cls");
			break;
		case 5:/*Пункт : 5)Сохранить изменения в dbf - файле*/
			if (!WriteToFile(&ListMy, NameFile))//запись содержания списка в dbf - файл
			{
				if (Data)
					free(Data);
				return;
			}
			system("cls");
			break;
		case 6://Пункт:6)Выход
			free(Data);//удаление памяти выделенной под буфер Data
			return;
		case 7://7)Перевести  dbf -файл  в файл формата txt
			if (!WriteToFile(&ListMy, NameFile))//сохранения изменений в dbf файле
			{
				if (Data)
					free(Data);
				return;
			}
			if (!DbfToTxt(NameFile))//чтение dbf - файла и создание результирующего текстового файла
			{
				if (Data)
					free(Data);
				return;
			}
			break;
		default:
			fflush(stdin);
			wprintf(L"Ошибка ввода номера меню.Для проболжения нажмите пробел: ");
			while (CODE_SPACE != getch());
				system("cls");
		}
	}
	if (Data)
		free(Data);

}
void AddToBegin(struct List **List_in, wchar_t* DataIn)
{
	(*List_in)->Prev = (struct List *)malloc(sizeof(struct List));//выделение памяти для предыдущего элемента
	(*List_in)->Prev->DataBuf = (wchar_t*)malloc(sizeof(wchar_t)*(wcslen(DataIn) + 1));//выделение памяти под запись
	wcscpy((*List_in)->Prev->DataBuf, DataIn);//сохранение добаляемых данных,в элемент списка
	(*List_in)->Prev->Next = (*List_in);//установка указателя Next у предыдуще на текущий
	(*List_in)->Prev->Prev = NULL;//установка указателя Prev у предыдущего на NULL  
	(*List_in) = (*List_in)->Prev;//перестановка указателя  у текущего на начало списка

}