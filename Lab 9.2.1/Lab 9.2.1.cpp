#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Special { ПЗ, КН, ІТ, СА };

string s_special[] = {
	"Інженерія програмного забезпечення",
	"Комп'ютерні науки",
	"Інформаційні системи та технології",
	"Системний Аналіз" };

struct student
{
	string prizv;
	int kurs;
	Special spec;
	int math;
	int informatic;
	int physics;
};
void Create(student* s, const int kilkist);
void Print(student* s, const int kilkist);
void Sort(student* s, const int kilkist);
int* IndexSort(student* s, const int kilkist);
void PrintIndexSorted(student* s, int* I, const int kilkist);
int BinSearch(student* s, const int kilkist, const string prizv, const string spec, const int matematic);
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int klkst_student;
	cout << "Введіть кількість студентів:";cin >> klkst_student;
	cout << endl;
	student* s = new student[klkst_student];

	string prizv;
	int kurs;
	int math;
	int found;

	int menuItem;
	do {
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - індексне впорядкування та вивід даних" << endl;
		cout << " [5] - бінарний пошук студента" << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть пункт меню: "; cin >> menuItem;
		switch (menuItem)
		{
		case 1:
			Create(s, klkst_student);
			break;
		case 2:
			Print(s, klkst_student);
			break;
		case 3:
			Sort(s, klkst_student);
			break;
		case 4:
			PrintIndexSorted(s, IndexSort(s, klkst_student), klkst_student);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cin.get();
			cin.sync();
			cout << " прізвище: ";
			getline(cin, prizv);

			cout << " курс: ";
			cin >> kurs;

			cout << " бал з математики: "; cin >> math;
			cout << endl;
			if ((found = BinSearch(s, klkst_student, prizv,spec, klkst_student)) != -1)
				cout << "Знайдено студента в списку під номером " << found + 1 << endl;
			else
				cout << "Шуканого студента в списку не знайдено" << endl;
			break;

		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
		cout << endl;
	} while (menuItem != 0);

	delete[] s;
	}
}
void Create(student* s, const int kilkist)
{
	int kurs, special;
	for (int i = 0;i < kilkist;i++)
	{
		cout << endl;
		cout << "студент №" << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "прізвище:";getline(cin, s[i].prizv);
		cout << "курс:";cin >> s[i].kurs;
		cout << "спеціальність(0 -Інженерія програмного забезпечення, 1 - Комп'ютерні науки, 2 - Інформаційні системи та технології, 3 -Системний Аналіз):";cin >> special;
		s[i].spec = (Special)special;
		cout << "оцінка з математики:";cin >> s[i].math;
		cout << "оцінка з інформатики:";cin >> s[i].informatic;
		cout << "оцінка з фізики:";cin >> s[i].physics;
	}
}

void Print(student* s, const int kilkist)
{
	cout << "======================================================================================================"
		<< endl;
	cout << "|  № |  Прізвище    | Курс | Спеціальність                      | Фізика | Математика  | Інформатика |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < kilkist; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[i].prizv
			<< "| " << setw(3) << right << s[i].kurs << "  "
			<< "| " << setw(35) << left << s_special[s[i].spec] << ""
			<< "| " << setw(4) << right << s[i].math << "   "
			<< "| " << setw(6) << right << s[i].informatic << "      "
			<< "| " << setw(6) << right << s[i].physics << "      |" << endl;
	}
	cout << "======================================================================================================" << endl;
}
void Sort(student* s, const int kilkist)
{
	student tmp;

	for (int i0 = 0;i0 < kilkist - 1;i0++)
		for (int i1 = 0;i1 < kilkist - i0 - 1;i1++)
		{
			if ((s[i1].spec > s[i1 + 1].spec)
				|| (s[i1].spec == s[i1 + 1].spec && s[i1].math > s[i1 + 1].math)
				|| (s[i1].spec == s[i1 + 1].spec && s[i1].math == s[i1 + 1].math && s[i1].prizv > s[i1 + 1].prizv)
				)
			{
				tmp = s[i1];
				s[i1] = s[i1 + 1];
				s[i1 + 1] = tmp;
			}
		}
}
int* IndexSort(student* s, const int kilkist)
{
	int* I = new int[kilkist];

	for (int i = 0;i < kilkist;i++)
		I[i] = i;
	int i, j, value;
	for(i=1;i<kilkist;i++)
	{
		value = I[i];
		for (j = i - 1;
		j >= 0 && (
			(s[I[j]].spec > s[value].spec)
			||
			(s[I[j]].spec == s[value].spec && s[I[j]].math > s[value].math)
			||
			(s[I[j]].spec == s[value].spec && s[I[j]].math == s[value].math && s[I[j]].prizv > s[value].prizv)
			);
			j--)
			{
			I[j + 1] = I[j];
            }
			I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(student* s, int* I, const int kilkist)
{
	cout << "========================================================================================="
		<< endl;
	cout << "| №  | Прізвище     | Курс | Спеціальність         | Фізика | Математика  | Інформатика |"
		<< endl;
	cout << "-----------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < kilkist; i++)
	{
		cout << "| " << setw(2) << right << i + 1 << " "
			<< "| " << setw(13) << left << s[I[i]].prizv
			<< "| " << setw(3) << right << s[I[i]].kurs << "  "
			<< "| " << setw(22) << left << s_special[s[I[i]].spec] << ""
			<< "| " << setw(4) << right << s[I[i]].math << "   "
			<< "| " << setw(6) << right << s[I[i]].informatic << "      "
			<< "| " << setw(6) << right << s[I[i]].physics << "     |" << endl;
	}
	cout << "=========================================================================================" << endl;
}
int BinSearch(student* s, const int kilkist, const string prizv,const string spec,  const int math)

	int L = 0, R = kilkist - 1, m;
	do{
		m = (L + R) / 2;
		if (s[m].spec == spec && s[m].math == math && s[m].prizv == prizv)
			return m;
		if (
			(s[m].spec < spec)
			|| (s[m], spec == spec && s[m].math < math)
			|| (s[m].spec == spec && s[m].math == math && s[m].prizv < prizv)
			)
		{
			R = m - 1;
		}
		else {
			L = m + 1;
		}
	} while (L<=R);
return -1;