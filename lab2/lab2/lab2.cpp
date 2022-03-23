#include <iostream>
#include <vector>

using namespace std;

int symmetry1 = 0, reflexivity1 = 0, transitivity1 = 0, antisymmetry1 = 0;

void symmetry(int** a, int n)
{
	int not_symmetry1 = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] != a[j][i])
				not_symmetry1++;

		}
	}
	if (not_symmetry1 == 0) cout << "отношение симметрично" << endl;
	symmetry1++;
}

void antisymmetry(int** a, int n)
{
	int not_antisymmetry1 = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] == 1 && a[j][i] == 1 && i != j)
				not_antisymmetry1++;

		}
	}
	if (not_antisymmetry1 == 0) {
		cout << "отношение антисимметрично" << endl;
		antisymmetry1++;
	}
}

void reflexivity(int** a, int n)
{
	int chek = 0;
	for (int i = 0; i < n; i++)
	{
		if (a[i][i] == 1)
			chek++;
	}
	if (chek == n) {
		cout << "отношение рефлексивно" << endl;
		reflexivity1++;
	}
}

void transitivity(int** a, int n)
{
	int chek = 0;
	int not_transitivity1 = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (a[i][j])
			{
				for (int k = 0; k < n; k++)
				{
					if (a[j][k] && !a[i][k])
					{
						not_transitivity1++;
					}
					else
					{
						chek++;
					}
				}

			}


		}
	}
	if (chek == 1) {
		cout << "отношение транзитивно" << endl;
		transitivity1++;
	}
}

void pr_symmetry(int** a, int n)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (a[i][j] == 1)
				a[j][i] = 1;
}

void pr_reflexivity(int** a, int n)
{
	for (int i = 0; i < n; i++)
		a[i][i] = 1;
}

void pr_transitivity(int** a, int n)
{
	for (int i = 0; i < n; i++)	{
		for (int j = 0; j < n; j++)	{
			for (int k = 0; k < n; k++)	{
				if (a[j][k] == 1) {
					for (int p = 0; p < n; p++)	{
						if (a[k][p] == 1)
							a[j][p] = 1;
					}
				}
			}
		}
	}
}

void pr(int** a, int n) {
	int** a1;
	a1 = new int* [n];
	for (int i = 0; i < n; i++)
	{
		a1[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			a1[i][j] = a[i][j];
		}
	}

	pr_symmetry(a1, n);
	pr_reflexivity(a1, n);
	pr_transitivity(a1, n);
	cout << "замыкание эквивалентности" << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << a1[i][j] << ' ';
		cout << endl;
	}
	vector<vector<int>> res;
	int* count = new int[n];
	for (int i = 0; i < n; i++) {
		count[i] = 1;
	}

	for (int i = 0; i < n; i++) {
		if (count[i]) {
			vector<int> srez;
			for (int j = i; j < n; j++) {
				if (a1[i][j] && count[j]) {
					count[j] = 0;
					srez.push_back(j);
				}
			}
			count[i] = 0;
			res.push_back(srez);
		}
	}

	cout << "Фактор-множество: {";
	for (int i = 0; i < res.size(); i++) {
		cout << "{";
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] + 1;
			if (j != res[i].size() - 1)
				cout << ", ";
		}
		cout << "}";
		if (i != res.size() - 1)
			cout << ", ";
	}
	cout << "}" << endl;

	cout << "Полная система представителей на заданном множестве: {";
	for (int i = 0; i < res.size(); i++) {
		cout << res[i][0] + 1;
		if (i != res.size() - 1)
			cout << ", ";
	}
	cout << "}" << endl << endl;

}

void rel_equivalence() {
	int n;
	cout << "n=";
	cin >> n;
	int** a;
	a = new int* [n];
	cout << "Введите матрицу \n";
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
		for (int j = 0; j < n; j++)
		{
			cin >> a[i][j];
		}
	}

	symmetry(a, n);
	reflexivity(a, n);
	transitivity(a, n);
	antisymmetry(a, n);

	if (symmetry1 > 0 && reflexivity1 > 0 && transitivity1 > 0)
		cout << "Отношение является отношением эквивалентности\n";
	else {
		cout << "Отношение не является отношением эквивалентности \n";
		pr(a, n);
	}
}

vector <pair <int, int> > all_min (vector <int> a) {
	vector <pair<int, int> > res;
	res.push_back(make_pair(a[0], 0));
	for (int i = 1; i < a.size(); i++) {
		int checker = 0;
		for (int j = 0; j < res.size(); j++)
			if (a[i] % res[j].first == 0)
				checker++;
		if (checker == 0)
			res.push_back(make_pair(a[i], i));
	}
	return res;
}

void hasse(vector <int> a) {
	vector <vector <int>> res;
	int lvl = 0;
	cout << endl << "Диаграмма Хассе: \n";
	while (a.size() > 0) {
		vector <pair<int, int>> A_i = all_min(a);
		vector <int> help;
		for (int i = A_i.size() - 1; i >= 0; i--) {
			a.erase(a.begin() + A_i[i].second);
			help.push_back(A_i[i].first);
		}
		res.push_back(help);
		lvl++;
	}
	for (int i = res.size() - 1; i >= 0; i--) {
		cout << i + 1 << ") ";
		for (int j = 0; j < res[i].size(); j++) {
			cout << ' ' << res[i][j] << " ,";
		}
		cout << endl;
	}
	vector <pair<int, int>> res_pairs;
	for (int i = res.size() - 1; i > 0; i--) {
		for (int j = 0; j < res[i].size(); j++) {
			for (int k = 0; k < res[i - 1].size(); k++) {
				if (res[i][j] % res[i - 1][k] == 0) {
					res_pairs.push_back(make_pair(res[i][j], res[i - 1][k]));
				}
			}
		}
	}
	cout << endl;
	for (int i = 0; i < res_pairs.size(); i++) {
		cout << '(' << res_pairs[i].first << ", " << res_pairs[i].second << ")";
		if (i < res_pairs.size() - 1) cout << ", ";
	}
	cout << endl;
}


vector <int> find_all(int n, int k) {
	vector <int> res;
	for (int i = 2 - k; i < n / 2.0 + 1; i++) {
		if (n % i == 0)
			res.push_back(i);
	}
	res.push_back(n);
	return res;
}

void order_number() {
	int n;
	cout << "\nВведите число: ";
	cin >> n;

	int one, k;
	cout << "1 - включить единицу в делители числа \n0 - не включать единицу в делители числа \n";
	cin >> one;
	if (one)
		k = 1;
	else
		k = 0;
	cout << endl;
	vector <int> res = find_all(n, k);
	vector <pair<int, int>> min = all_min(res);
	cout << endl << "Минимальные элементы: ";
	for (int i = 0; i < min.size(); i++) {
		cout << min[i].first;
		if (i < min.size() - 1) cout << ", ";
	}
	cout << endl;
	if (min.size() == 1) cout << "Наименьший элемент: " << min[0].first << endl;
	else cout << "Наименьший элемент: нет" << endl;

	cout << "Максимальные элементы: " << n << endl;
	cout << "Наибольший элемент: " << n << endl;

	hasse(res);
}

vector <int> all_min_matr(vector <vector <int>> v, int n) {
	vector <int> res;
	for (int i = 0; i < n; i++) {
		if (v[i][i] > -1) {
			int checker = 0;
			for (int j = 0; j < n; j++)
				if (v[j][i] == 1)
					if (i != j)
						checker++;
			if (checker == 0)
				res.push_back(i);
		}
	}
	return res;
}


vector <int> all_max_matr(vector <vector <int>> v, int n) {
	vector <int> res;
	for (int i = 0; i < n; i++) {
		int checker = 0;
		for (int j = 0; j < n; j++)
			if (v[i][j])
				if (i != j)
					checker++;
		if (checker == 0)
			res.push_back(i);
	}
	return res;
}

void hasse_pair(vector <vector <int>> v, int n, vector <vector <int>> hasse_diag) {
	vector <pair<int, int>> res;
	for (int i = hasse_diag.size() - 1; i > 0; i--)
		for (int j = 0; j < hasse_diag[i].size(); j++)
			for (int k = 0; k < hasse_diag[i - 1].size(); k++)
				if (v[hasse_diag[i - 1][k]][hasse_diag[i][j]])
					res.push_back(make_pair(hasse_diag[i - 1][k] + 1, hasse_diag[i][j] + 1));

	for (int i = 0; i < res.size(); i++) {
		cout << "(" << res[i].first << ", " << res[i].second << ")";
		if (i != res.size() - 1) cout << ",  ";
		else cout << endl << endl;
	}
}

void hasse_matr(vector <vector <int>> v_real, int n) {
	vector <vector <int>> v;
	v.resize(n);
	cout << endl << "Диаграмма Хассе: \n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			v[i].push_back(v_real[i][j]);
	}
	vector <vector <int>> res;
	while (true) {
		vector <int> A_i = all_min_matr(v, n);
		if (A_i.size() == 0)
			break;
		vector <int> help;
		for (int k = A_i.size() - 1; k >= 0; k--) {
			for (int i = v.size() - 1; i >= 0; i--) {
				for (int j = v[i].size() - 1; j >= 0; j--) {
					if (A_i[k] == j)
						v[i][j] = -1;
				}
				if (A_i[k] == i) {
					for (int j = v[i].size() - 1; j >= 0; j--)
						v[i][j] = -1;
				}
			}
			help.push_back(A_i[k]);
		}
		res.push_back(help);
	}
	for (int i = res.size() - 1; i >= 0; i--) {
		cout << i + 1 << ") ";
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] + 1 << " ";
		}
		cout << endl;
	}
	cout << endl << "\n";
	hasse_pair(v_real, n, res);
}

void order_matrix() {
	int n;
	cout << "n=";
	cin >> n;
	vector <vector <int>> v;
	v.resize(n);
	cout << "Введите матрицу \n" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int x_cin;
			cin >> x_cin;
			v[i].push_back(x_cin);
		}
	}

	//if (antisymmetry1 > 0 && reflexivity1 > 0 && transitivity1 > 0)
	//	cout << "Отношение является отношением порядка\n";
	//else {
	//	cout << "Отношение не является отношением порядка \n";
	//	return;
	//}

	vector <int> min = all_min_matr(v, n);
	vector <int> max = all_max_matr(v, n);

	cout << endl << "Минимальные элементы: ";
	for (int i = 0; i < min.size(); i++) {
		cout << min[i] + 1;
		if (i < min.size() - 1) cout << ", ";
	}
	cout << endl;
	if (min.size() == 1) cout << "Наименьший элемент: " << min[0] + 1 << endl;
	else cout << "Наименьший элемент: нет" << endl;

	cout << "Максимальные элементы: ";
	for (int i = 0; i < max.size(); i++) {
		cout << max[i] + 1;
		if (i < max.size() - 1) cout << ", ";
	}
	cout << endl;
	if (max.size() == 1) cout << "Наибольший элемент: " << max[0] + 1 << endl;
	else cout << "Наибольший элемент: нет" << endl;
	cout << endl;
	hasse_matr(v, n);
}

vector<int> p(vector<int> a1, vector<int> a2) {
	vector<int> res;
	for (int i = 0; i < a1.size(); i++)
		for (int j = 0; j < a2.size(); j++)
			if (a1[i] == a2[j])
				res.push_back(a1[i]);
	return res;
}

bool check(vector<vector<int>> a1, vector<int> a2) {
	for (int i = 0; i < a1.size(); i++) {
		if (a1[i].size() == a2.size()) {
			int a = a2.size();
			for (int j = 0; j < a1[i].size(); j++) {
				if (a1[i][j] == a2[j])
					a--;
			}
			if (a == 0)
				return false;
		}
	}
	return true;
}

vector <pair<vector <int>, int>> all_min_zm(vector<vector<int>> a) {
	vector <pair<vector <int>, int>> res;
	for (int i = 0; i < a.size(); i++) {
		int count = 0;
		for (int j = 0; j < a.size(); j++) {
			if (p(a[i], a[j]) == a[i] || p(a[i], a[j]) != a[j]) {
				count++;
			}
		}
		if (count == a.size())
			res.push_back(make_pair(a[i], i));
	}
	return res;
}

vector<int> fi(int** matr, int x, int n) {
	vector<int> res;
	for (int i = 0; i < n; i++) {
		if (matr[x][i])
			res.push_back(i);
	}
	return res;
}

void c(vector<vector<vector<int>>> a, int** matr, int n) {
	char alf[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o' };
	vector<vector<pair<vector<int>, vector<int>>>> res;
	res.resize(a.size());
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a[i].size(); j++) {
			vector<int> count;
			int checker = 0;
			for (int k = 0; k < a[i][j].size(); k++) {
				checker++;
				if (k == 0)
					count = fi(matr, a[i][j][k], n);
				else
					count = p(count, fi(matr, a[i][j][k], n));
			}
			if (checker > 0)
				res[i].push_back(make_pair(a[i][j], count));
			else {
				vector<int> help;
				for (int i = 0; i < n; i++)
					help.push_back(i);
				res[i].push_back(make_pair(a[i][j], help));
			}
		}
	}
	cout << endl << "Диаграмма Хассе решётки концептов:" << endl;
	for (int i = res.size() - 1; i >= 0; i--) {
		cout << i + 1 << ") ";
		for (int j = 0; j < res[i].size(); j++) {
			cout << "({";
			for (int k = 0; k < res[i][j].first.size(); k++) {
				cout << res[i][j].first[k] + 1;
				if (k != res[i][j].first.size() - 1) cout << ", ";
			}
			cout << "}, {";
			for (int k = 0; k < res[i][j].second.size(); k++) {
				cout << alf[res[i][j].second[k]];
				if (k != res[i][j].second.size() - 1) cout << ", ";
			}
			cout << "})  ";
		}
		cout << endl;
	}
}

void hasse_zm(vector<vector<int>> a, int** matr, int n) {
	vector<vector<vector<int>>> res;
	int lvl = 0;
	while (a.size() > 0) {
		vector <pair<vector <int>, int>> A_i = all_min_zm(a);
		vector<vector<int>> help;
		for (int i = A_i.size() - 1; i >= 0; i--) {
			a.erase(a.begin() + A_i[i].second);
			help.push_back(A_i[i].first);
		}
		res.push_back(help);
		lvl++;
	}
	cout << "Диаграмма Хассе системы замыкания: " << endl;
	for (int i = res.size() - 1; i >= 0; i--) {
		cout << i + 1 << ") ";
		for (int j = 0; j < res[i].size(); j++) {

			cout << "{";
			for (int k = 0; k < res[i][j].size(); k++) {
				cout << res[i][j][k] + 1;
				if (k != res[i][j].size() - 1) cout << ", ";
			}
			cout << "}  ";
		}
		cout << endl;
	}

	vector<pair<vector<int>, vector<int>>> res_pairs;
	for (int i = 0; i < res.size() - 1; i++) {
		for (int j = 0; j < res[i].size(); j++) {
			for (int k = 0; k < res[i + 1].size(); k++) {
				if (p(res[i][j], res[i + 1][k]) == res[i][j]) {
					res_pairs.push_back(make_pair(res[i][j], res[i + 1][k]));
				}
			}
		}
	}

	cout << endl;
	c(res, matr, n);
}

vector<vector<int>> zm (int** a, int n) {
	vector<vector<int>> res;
	vector<int> G;
	for (int i = 0; i < n; i++)
		G.push_back(i);
	res.push_back(G);

	for (int i = 0; i < n; i++) {
		vector<int> count;
		for (int j = 0; j < n; j++) {
			if (a[j][i])
				count.push_back(j);
		}
		if (check(res, count))
			res.push_back(count);
		for (int i = 0; i < res.size(); i++) {
			vector<int> new_count = p(res[i], count);
			if (check(res, new_count))
				res.push_back(new_count);
		}
	}

	cout << endl << "Система замыканий на множестве объектов:" << endl << "{";
	for (int i = 0; i < res.size(); i++) {
		cout << "{";
		for (int j = 0; j < res[i].size(); j++) {
			cout << res[i][j] + 1;
			if (j != res[i].size() - 1)
				cout << ", ";
		}
		cout << "}";
		if (i != res.size() - 1)
			cout << ", ";
	}
	cout << "}" << endl << endl;

	hasse_zm(res, a, n);

	return res;
}

void consept() {
	int n;
	cout << "n= ";
	cin >> n;
	int** a;
	a = new int* [n];
	cout << "Введите матрицу \n";
	for (int i = 0; i < n; i++) {
		a[i] = new int[n];
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
	zm(a, n);
}

int main()
{
	setlocale(LC_ALL, "ru");
	for (;;) {
		cout << "1 - Отношение эквивалентности \n2 - Отношение порядка, ввод числом \n3 - Отношение порядка, ввод матрицей \n4 - Вычисление решетки концептов \n";
		int x;
		cin >> x;
		switch (x) {
		case 1:
			rel_equivalence();
			cout << endl;
			break;
		case 2:
			order_number();
			cout << endl;
			break;
		case 3:
			order_matrix();
			cout << endl;
			break;
		case 4:
			consept();
			cout << endl;
			break;
		}
	}
}