#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<algorithm>
#include<random>

class Grammar
{
public:

	//getters

	std::string getVT();
	std::string getVN();
	char getStart();
	std::vector<std::pair<std::string, std::string>> getP();

	//function required
	bool VerifyGrammar();
	bool IsRegular(int& check);
	std::string GenerateWord();
	void PrintGrammar();
	void ReadGrammar();



	std::set<std::string> generateNWords(int n);
	void printNWords(std::set<std::string> set);
	bool isFinal(std::string cuv);
	int howManyTimesDoesTheRuleApply(std::string cuv, int x);
	std::vector<int> AplicableRules(std::string cuv);
	void ApplyRule(std::string& cuv, int rule);

private:
	std::vector<char> m_simboluriNeterminale, m_simboluriTerminale;
	char m_start;
	std::vector<std::pair<std::string, std::string>> m_reguli;
};

