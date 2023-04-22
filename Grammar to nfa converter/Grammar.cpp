#include "Grammar.h"

std::set<std::string> Grammar::generateNWords(int n)
{
	std::set<std::string> set;
	std::string str;
	while (set.size() < n)
	{
		str = GenerateWord();
		set.insert(str);
	}
	return set;
}

void Grammar::printNWords(std::set<std::string> set)
{
	std::cout << "Cuvintele sunt:";
	for (auto it = set.begin(); it != set.end(); ++it)
		std::cout << *it << " ";
}

void Grammar::ReadGrammar()
{
	std::ifstream f;
	f.open("input.txt");
	if (f.is_open())
	{
		std::string linie;
		getline(f, linie);
		for (int i = 0;i < linie.size();i++)
			if (linie[i] != ' ')
				m_simboluriNeterminale.push_back(linie[i]);

		linie.clear();
		getline(f, linie);
		for (int i = 0;i < linie.size();i++)
			if (linie[i] != ' ')
				m_simboluriTerminale.push_back(linie[i]);

		f >> m_start;

		int NrRules;
		f >> NrRules;

		for (int i = 0;i <= NrRules;i++)
		{
			linie.clear();
			getline(f, linie);
			std::pair<std::string, std::string> regula;

			size_t found = linie.find("-");
			if (found != std::string::npos)
			{
				for (int j = 0;j < found;j++)
					regula.first += linie[j];

				for (int j = found + 1;j < linie.size();j++)
					regula.second += linie[j];

				m_reguli.push_back(regula);
			}
		}
		f.close();
	}
	else
		std::cout << "Nu s-a putut deschide fisierul";
}

void Grammar::PrintGrammar()
{
	std::cout << "VN:\n";
	for (int i = 0;i < m_simboluriNeterminale.size();i++)
		std::cout << m_simboluriNeterminale[i] << " ";
	std::cout << std::endl;
	std::cout << "VT:\n";
	for (int i = 0;i < m_simboluriTerminale.size();i++)
		std::cout << m_simboluriTerminale[i] << " ";
	std::cout << "\nS: " << m_start << std::endl;
	std::cout << "Reguli:\n";
	for (int i = 0;i < m_reguli.size();i++)
	{
		std::cout << m_reguli[i].first << "->" << m_reguli[i].second << std::endl;
	}
}

bool Grammar::VerifyGrammar()
{
	//REUNIUNE
	std::set<char> Reunion;
	for (int i = 0;i < m_simboluriNeterminale.size();i++)
		Reunion.insert(m_simboluriNeterminale[i]);
	for (int i = 0;i < m_simboluriTerminale.size();i++)
		Reunion.insert(m_simboluriTerminale[i]);
	if (Reunion.size() != m_simboluriNeterminale.size() + m_simboluriTerminale.size())
		return false;

	//S E IN VN
	std::vector<char>::iterator it;
	it = find(m_simboluriNeterminale.begin(), m_simboluriNeterminale.end(), m_start);
	if (it == m_simboluriNeterminale.end())
		return false;

	//MEMBRUL STANG CONTINE CEL PUTIN UN NETERMINAL
	for (int i = 0;i < m_reguli.size();i++)	//pentru fiecare regula
	{
		int suma = 0, k = 0;
		for (int j = 0;j < m_simboluriNeterminale.size();j++)	//ma plimb prin simboluri
		{
			suma += std::count(m_reguli[i].first.begin(), m_reguli[i].first.end(), m_simboluriNeterminale[j]);
			if (suma)
				k++;
			if (k)
				break;
		}
		if (!k)
			return false;
	}

	//EXISTA CEL PUTIN O PRODUCTIE CARE ARE IN STANGA DOAR UN S (mai e de completat daca apare S de 2 ori)
	int ok = 0;
	for (int i = 0;i < m_reguli.size();i++)
	{
		int suma = 0;
		suma += std::count(m_reguli[i].first.begin(), m_reguli[i].first.end(), m_start);
		if (suma == 1)
		{
			ok = 1;
			break;
		}
	}
	if (ok == 0)
		return false;

	//FIECARE PRODUCTIE CONTINE DOAR ELEMENTE DIN VN SI VT
	std::set<char> elemente;
	for (int i = 0;i < m_simboluriNeterminale.size();i++)
		elemente.insert(m_simboluriNeterminale[i]);
	for (int i = 0;i < m_simboluriTerminale.size();i++)
		elemente.insert(m_simboluriTerminale[i]);

	for (int i = 0;i < m_reguli.size();i++)
	{
		for (int j = 0;j < m_reguli[i].first.size();j++)
		{
			auto pos = elemente.find(m_reguli[i].first[j]);
			if (pos == elemente.end())
				return false;
		}
	}

	return true;
}

bool Grammar::IsRegular(int& check)
{
	int ok = 0, exista_productii_care_se_duc_in_lambda = 0, am_S_in_membrul_sta = 0;
	for (int i = 0;i < m_reguli.size();i++)
	{
		if (m_reguli[i].second.size() == 1 && m_reguli[i].second[0] == m_start)
			am_S_in_membrul_sta = 1;

		if (m_reguli[i].second.size() == 2 && (m_reguli[i].second[0] == m_start || m_reguli[i].second[1] == m_start))
			am_S_in_membrul_sta = 1;


		if (m_reguli[i].second.size() == 1 && m_reguli[i].second[0] == '@')
		{
			exista_productii_care_se_duc_in_lambda = 1;
			check = 1;
		}

		if (am_S_in_membrul_sta == 1 && exista_productii_care_se_duc_in_lambda == 1)
			return false;

		ok = 0;
		if (m_reguli[i].first.size() != 1)
			return false;

		if (m_reguli[i].second.size() == 2 && std::find(m_simboluriNeterminale.begin(), m_simboluriNeterminale.end(), m_reguli[i].second[1]) != m_simboluriNeterminale.end() && std::find(m_simboluriTerminale.begin(), m_simboluriTerminale.end(), m_reguli[i].second[0]) != m_simboluriTerminale.end())
			ok = 1;

		if (m_reguli[i].second.size() == 1 && std::find(m_simboluriTerminale.begin(), m_simboluriTerminale.end(), m_reguli[i].second[0]) != m_simboluriTerminale.end())
			ok = 1;

		if (ok == 0)
			return false;
	}
	if (ok == 1)
		return true;
}

bool Grammar::isFinal(std::string cuv)
{
	int k = 0;

	for (int i = 0;i < m_simboluriTerminale.size();i++)
	{
		k += std::count(cuv.begin(), cuv.end(), m_simboluriTerminale[i]);
	}
	if (k == cuv.size())
		return true;
	return false;
}

int Grammar::howManyTimesDoesTheRuleApply(std::string cuv, int x)
{
	int nPos = m_reguli[x].first.find(cuv, 0);
	int index = 0, count = 0;
	while ((index = cuv.find(m_reguli[x].first, index)) != std::string::npos) {
		count++;
		index += m_reguli[x].first.length();
	}

	return count;
}

std::vector<int> Grammar::AplicableRules(std::string cuv)
{
	std::vector<int> reguli;
	for (int i = 0;i < m_reguli.size();i++)
	{
		size_t found = cuv.find(m_reguli[i].first);
		if (found != std::string::npos)
			reguli.push_back(i);
	}
	return reguli;
}

std::string Grammar::GenerateWord()
{
	std::vector<int> aplicableRules;
	std::string cuvant(1, m_start), temp(1, m_start);


	std::cout << m_start;


	while (isFinal(cuvant) == 0)
	{
		aplicableRules.clear();
		aplicableRules = AplicableRules(cuvant);
		std::random_device rd;
		std::mt19937 eng(rd());
		std::uniform_int_distribution<> distr(0, aplicableRules.size() - 1);
		int x = aplicableRules[distr(eng)];
		ApplyRule(cuvant, x);
		std::cout << "->" << cuvant;
	}
	return cuvant;
}

void Grammar::ApplyRule(std::string& cuv, int rule)
{
	int count = howManyTimesDoesTheRuleApply(cuv, rule);
	std::random_device rd;
	std::mt19937 eng(rd());
	int numberApply;
	std::uniform_int_distribution<> distr(1, count);
	numberApply = distr(eng);

	int i = 0;
	for (i = 0;i < cuv.size();i++)
	{
		if (cuv[i] == m_reguli[rule].first[0])
			numberApply--;
		if (numberApply == 0)
			break;
	}
	std::string temp = "";
	for (int j = 0;j < cuv.size();j++)
		if (j != i + 1)
			temp += cuv[j];
	temp.replace(i, i + 1, m_reguli[rule].second);
	cuv = "";
	cuv = temp;
}

std::string Grammar::getVT()
{
	std::string s(m_simboluriTerminale.begin(), m_simboluriTerminale.end());
	return s;
}

std::string Grammar::getVN()
{
	std::string s(m_simboluriNeterminale.begin(), m_simboluriNeterminale.end());
	return s;
}

char Grammar::getStart()
{
	return m_start;
}

std::vector<std::pair<std::string, std::string>> Grammar::getP()
{
	return m_reguli;
}
