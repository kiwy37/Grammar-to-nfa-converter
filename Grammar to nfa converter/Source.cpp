#include<iostream>
#include<conio.h>
#include"Grammar.h"
#include"FiniteAutomaton.h"

int main()
{
	Grammar g;
	FiniteAutomaton a;
	int containsLambda = 0;
	g.ReadGrammar();
	std::set <std::string> seti;
	std::string word;

	if (g.VerifyGrammar() == true && g.IsRegular(containsLambda) == true)
	{
		int op = 9;
		do {
			std::cout << "Gramatica este corecta si regulata.\n";
			std::cout << "Maeniul este:\n";
			std::cout << "0. Exit\n";
			std::cout << "1. Afisrea gramaticii G\n";
			std::cout << "2. Generarea unui nr. n de cuvinte in gramatica G\n";
			std::cout << "3. Obtinerea automatului echivalent cu G\n";
			std::cout << "4. Verificare daca este acceptat cuvantul\n";
			std::cout << "5. Generarea unui cuvant in G + verificarea daca e acceptat de automat\n";
			std::cin >> op;
			system("CLS");
			switch (op)
			{
			case 0:
				std::cout << "La revedere!";
				break;
			case 1:
				g.PrintGrammar();
				system("pause");
				system("cls");
				break;

			case 2:
				std::cout << "Dati numarul de cuvinte:";
				int n;
				std::cin >> n;
				seti = g.generateNWords(n);
				system("CLS");
				g.printNWords(seti);
				std::cout << std::endl;
				system("pause");
				system("cls");
				break;

			case 3:
				a = a.GrammarToAutomaton(g, containsLambda);
				a.printAutomaton();
				system("pause");
				system("cls");
				break;

			case 4:
				std::cout << "Dati cuvantul: ";
				std::cin >> word;
				if (a.CheckWord(word))
					std::cout << "Cuvantul este acceptat de automat.\n";
				else
					std::cout << "Cuvantul nu este acceptat de automat.\n";
				system("pause");
				system("cls");
				break;
			case 5:
				a = a.GrammarToAutomaton(g, containsLambda);
				std::cout << "S-a generat: ";
				word = g.GenerateWord();
				if (a.CheckWord(word) == 1)
					std::cout << "\nCuvantul este acceptat de automat";
				else
					std::cout << "\nCuvantul nu este acceptat de automat";
				std::cout << std::endl;
				system("pause");
				system("cls");
				break;
			}
		} while (op);
	}
	else
	{
		if (g.VerifyGrammar() == false)
			std::cout << "Gramatica nu este valida.";

		if (g.IsRegular(containsLambda) == false)
			std::cout << "Gramatica nu este regulata.";
	}
	return 0;
}