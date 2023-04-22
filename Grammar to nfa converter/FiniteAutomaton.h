#pragma once
#include<unordered_map>
#include<unordered_set>
#include<fstream>
#include<queue>
#include<iostream>
#include<string>
#include"Grammar.h"

struct hashi
{
	size_t operator()(const std::pair<char, char>& pair) const
	{
		return pair.first * 12378 + pair.second * 3984;
	}
};

class FiniteAutomaton
{
public:
	FiniteAutomaton GrammarToAutomaton(Grammar g, int lambda);
	bool VerifyAutomaton();
	void printAutomaton();
	bool CheckWord(std::string cuv);
	bool IsDeterministic();
	FiniteAutomaton& operator=(const FiniteAutomaton& f);

private:
	std::string Q, sigma;
	std::unordered_map<std::pair<char, char>, std::string, hashi> deltha;
	char stareInitiala;
	std::string stariFinale;
};
