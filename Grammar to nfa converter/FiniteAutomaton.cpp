#include "FiniteAutomaton.h"

FiniteAutomaton FiniteAutomaton::GrammarToAutomaton(Grammar g, int lambda)
{
	FiniteAutomaton automaton;
	automaton.Q = g.getVN();
	automaton.Q.push_back('T');

	automaton.stareInitiala = g.getStart();

	automaton.sigma = g.getVT();

	if (lambda == 1)
		automaton.stariFinale.push_back('@');

	automaton.stariFinale.push_back('T');

	std::vector<std::pair<std::string, std::string>> prodVect = g.getP();

	for (int i = 0; i < prodVect.size(); i++)
	{
		if (prodVect[i].second.size() == 2)
		{
			automaton.deltha[{prodVect[i].first[0], prodVect[i].second[0]}].push_back(prodVect[i].second[1]);
		}
		else
			automaton.deltha[{prodVect[i].first[0], prodVect[i].second[0]}].push_back('T');
	}


	return automaton;
}

FiniteAutomaton& FiniteAutomaton::operator=(const FiniteAutomaton& f)
{
	deltha = f.deltha;
	Q = f.Q;
	sigma = f.sigma;
	stareInitiala = f.stareInitiala;
	stariFinale = f.stariFinale;
	return *this;
}

void FiniteAutomaton::printAutomaton()
{
	std::cout << "Q:";
	for (int i = 0;i < Q.size();i++)
		std::cout << Q[i] << " ";
	std::cout << std::endl;
	std::cout << "Sigma:";
	for (int i = 0;i < sigma.size();i++)
		std::cout << sigma[i] << " ";
	std::cout << std::endl;
	std::cout << "Stare initiala: ";
	std::cout << stareInitiala << " ";
	std::cout << std::endl;
	std::cout << "Stari finale:";
	for (int i = 0;i < stariFinale.size();i++)
		std::cout << stariFinale[i] << " ";
	std::cout << std::endl;

	for (auto it = deltha.begin(); it != deltha.end(); ++it)
	{
		std::cout << it->first.first << "," << it->first.second << "-";
		for (int j = 0;j < it->second.size();j++)
			std::cout << it->second[j] << " ";
		std::cout << std::endl;
	}
}

bool FiniteAutomaton::VerifyAutomaton()
{
	if (Q.empty() || sigma.empty() || stareInitiala == ' ' || stariFinale.empty() || deltha.empty())
	{
		return 0;
	}
	char state = 0;
	std::unordered_set <char> visited;
	std::queue <char> queue;
	queue.push(stareInitiala);
	visited.insert(stareInitiala);
	while (!queue.empty())
	{
		char currentState = queue.front();
		for (const auto& input : sigma)
		{
			std::string futureStates = deltha[{ currentState, input }];
			for (const auto& futureState : futureStates)
			{
				if (visited.find(futureState) == visited.end())
				{
					visited.insert(futureState);
					queue.push(futureState);
				}
			}
		}
		queue.pop();
	}
	for (const auto& finalState : stariFinale)
	{
		if (visited.find(finalState) != visited.end())
			return 1;
	}
	return 0;
}

bool FiniteAutomaton::CheckWord(std::string cuv)
{
	std::set<char> lista;

	lista.insert(stareInitiala);
	for (int i = 0;i < cuv.size();i++)
	{
		std::set<char> aux;
		for (auto it = lista.begin(); it != lista.end(); it++)
		{
			std::pair<char, char> p = std::make_pair(*it, cuv[i]);
			it = lista.find(*it);
			for (int k = 0;k < deltha[p].size();k++)
				aux.insert(deltha[p][k]);
		}
		lista.clear();
		for (auto x = aux.begin(); x != aux.end(); x++)
			lista.insert(*x);
	}
	for (int i = 0;i < stariFinale.size();i++)
	{
		auto pos = lista.find(stariFinale[i]);
		if (pos != lista.end())
			return true;
	}

	return false;
}

bool FiniteAutomaton::IsDeterministic()
{
	for (int i = 0;i < Q.size();i++)
		for (int j = 0;j < sigma.size();j++)
		{
			std::pair<char, char> p = std::make_pair(Q[i], sigma[j]);
			if (deltha[p].size() > 1)
				return false;
		}
	return true;
}