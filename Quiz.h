#pragma once
#include "question.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <algorithm>
class Quiz
{
     /** Creating three vectors of different question types **/
	std::vector <TFQuestion> tf;
	std::vector <MCQuestion> mcq;
	std::vector <CQuestion> complete;

public:

	//Implementation for the Push_Back function and .Size Function
	void pushmcq(MCQuestion m1) {mcq.push_back(m1);}
	void pushtf(TFQuestion t1) {tf.push_back(t1);}
	void pushcomplete(CQuestion c1) {complete.push_back(c1);}

	/** Getters that retrieve # of questions for each type **/

	int get_mcqsize() { return mcq.size(); }
	int get_tfsize() { return tf.size(); }
	int get_cqsize() { return complete.size(); }

	/** functions that prints all questions of the same type **/

	void display_tf()
	{
		for (int i = 0; i < get_tfsize(); i++)
		{
			std::cout << '[' << i+1 << ']' << ' ';
			tf[i].display_question();
		}
	}
	void display_mcq()
	{
		for (int i = 0; i < get_mcqsize(); i++)
		{
			std::cout << '[' << i+1 << ']' << ' ';
			mcq[i].display_question();
		}
	}
	void display_complete()
	{
		for (int i = 0; i < get_cqsize(); i++)
		{
			std::cout << '[' << i+1 << ']' << ' ';
			complete[i].display_question();
		}
	}

	/** Functions that check whether the Question is repeated or not. Then return boolean **/

	bool check_mcq(std::string ques)
	{
		for (unsigned int i = 0; i < mcq.size(); i++)
		{
			if (mcq[i] == ques)
				return 1;
		}
		return 0;
	}
	bool check_tf(std::string ques)
	{
		for (unsigned int i = 0; i < tf.size(); i++)
		{
			if (tf[i] == ques)
				return 1;
		}
		return 0;
	}
	bool check_complete(std::string ques)
	{
		for (unsigned int i = 0; i < complete.size(); i++)
		{
			if (complete[i] == ques)
				return 1;
		}
		return 0;
	}

	/**Deletes a question of a certain id (Entered by the user) **/

	void erase(int id)
	{
	    /** Three for-loops check every question's id for each question's type **/

		for (unsigned int i = 0; i < mcq.size(); i++)
		{
			if (mcq[i].get_id() == id)
				mcq.erase(mcq.begin() + i );
		}
		for (unsigned int i = 0; i < tf.size(); i++)
		{
			if (tf[i].get_id() == id)
				tf.erase(tf.begin() + i);
		}
		for (unsigned int i = 0; i < complete.size(); i++)
		{
			if (complete[i].get_id() == id)
				complete.erase(complete.begin() + i);
		}
	}

	std::string lower_case(std::string name) /** Used when the user enter an answer in any casing, the answer will be converted to lowercase **/
	{
		for (unsigned int i = 0; i < name.size(); i++)
		{
			if (name[i] >= 'A' && name[i] <= 'Z')
			{
				name[i] = name[i] + 32;
			}
		}
		return name;
	}
/** Methods that randomize the questions order per question type **/

	std::vector <int> mcq_questions_random_order()
	{
		std::vector <int> questions_order;
		questions_order.clear();
		std::srand(std::time(0));
		int random;
		for (int i = 0; i < 3; i++)
		{
			random = std::rand() % mcq.size() + 1;
			if (std::find(questions_order.begin(), questions_order.end(), random) != questions_order.end()) {
				i--;
				continue;
			}
			else
				questions_order.push_back(random);
		}
		return questions_order;
	}


	std::vector <int> tf_questions_random_order()
	{
		std::vector <int> questions_order;
		questions_order.clear();
		std::srand(std::time(0));
		int random;
		for (int i = 0; i < 2; i++)
		{
			random = std::rand() % tf.size() + 1;
			if (std::find(questions_order.begin(), questions_order.end(), random) != questions_order.end()) {
				i--;
				continue;
			}
			else
				questions_order.push_back(random);
		}
		return questions_order;
	}

	std::vector <int> complete_questions_random_order()
	{
		std::vector <int> questions_order;
		questions_order.clear();
		std::srand(std::time(0));
		int random;
		for (int i = 0; i < 1; i++)
		{
			random = std::rand() % complete.size() + 1;
			if (std::find(questions_order.begin(), questions_order.end(), random) != questions_order.end()) {
				i--;
				continue;
			}
			else
				questions_order.push_back(random);
		}
		return questions_order;
	}

	std::vector <int> mcq_choice_random_order(std::vector <int> &correct_answers)
	{
		std::vector <int> choice_order;
		choice_order.clear();
		correct_answers.clear();
		for (int i = 1; i <= 3; i++)
		{ /** Start of the outer loop that go through three MCQ questions **/
			for (int j = 1; j <= 4; j++)
			{ /** start of the inner loop **/
				int random = std::rand() % 4 + 1;
				if (std::find(choice_order.begin() + ((i - 1) * 4), choice_order.end(), random) != choice_order.end()) {
					j--;
					continue;
				}
				else
				{
					if (random == 1)
					{
						correct_answers.push_back(j);
					}
					choice_order.push_back(random);
				}

			} /** end of the inner loop **/

		} /** end of the outer loop **/
		return choice_order;
	}

/** start new quiz method parameterized with reference player object **/

	void start(player& p1)
	{
		//int result = 0;
		int tf_result = 0;
		int mcq_result = 0;
		int c_result = 0;
		//int complete_result = 0;
		std::vector <int> mcq_correct_answer;
		std::vector <int> mcq_questions_order =	mcq_questions_random_order();
		std::vector <int> tf_questions_order = tf_questions_random_order();
		std::vector <int> complete_questions_order = complete_questions_random_order();
		std::vector <int> mcq_choice_order = mcq_choice_random_order(mcq_correct_answer);

		for (int i = 0; i < 3; i++)
		{ /** start of the outer loop - MCQ-question loop **/

			int answer; /** player's entry **/
			std::cout << mcq[mcq_questions_order[i] - 1].get_question() << std::endl;
			p1.mcq_questions.push_back(mcq[mcq_questions_order[i] - 1].get_question());
			p1.mcq_answers.push_back(mcq[mcq_questions_order[i] - 1].get_a());
			for (int j = 0; j < 4; j++)
			{ /** start of the inner loop - choices per question loop **/
				if (j == 0)
					std::cout << "[1]";
				else if (j == 1)
					std::cout << "[2]";
				else if (j == 2)
					std::cout << "[3]";
				else if (j == 3)
					std::cout << "[4]";

				if (mcq_choice_order[j + (i * 4)] == 1)
				{
					std::cout << mcq[mcq_questions_order[i] - 1].get_a() << "\t";
				}
				else if (mcq_choice_order[j + (i * 4)] == 2)
				{
					std::cout << mcq[mcq_questions_order[i] - 1].get_b() << "\t";
					p1.mcq_answers.push_back(mcq[mcq_questions_order[i] - 1].get_b());
				}
				else if (mcq_choice_order[j + (i * 4)] == 3)
				{
					std::cout << mcq[mcq_questions_order[i] - 1].get_c() << "\t";
					p1.mcq_answers.push_back(mcq[mcq_questions_order[i] - 1].get_c());
				}
				else if (mcq_choice_order[j + (i * 4)] == 4)
				{
					std::cout << mcq[mcq_questions_order[i] - 1].get_d() << "\t";
					p1.mcq_answers.push_back(mcq[mcq_questions_order[i] - 1].get_d());
				}
			} /** end of the inner loop **/
			do {
				std::cout << "\nAnswer : ";
				std::cin >> answer;
			} while (answer < 1 || answer > 4);

			if (answer == mcq_correct_answer[i])
				mcq_result++;

			if (mcq_choice_order[(answer - 1) + (i * 4)] == 1)
				p1.answers_entered.push_back(mcq[mcq_questions_order[i] - 1].get_a());
			else if (mcq_choice_order[(answer - 1) + (i * 4)] == 2)
				p1.answers_entered.push_back(mcq[mcq_questions_order[i] - 1].get_b());
			else if (mcq_choice_order[(answer - 1) + (i * 4)] == 3)
				p1.answers_entered.push_back(mcq[mcq_questions_order[i] - 1].get_c());
			else if (mcq_choice_order[(answer - 1) + (i * 4)] == 4)
				p1.answers_entered.push_back(mcq[mcq_questions_order[i] - 1].get_d());

            /** Loop through each question and print its choices then the player do answer within the range 1 to 4 **/

		} /** end of the outer loop **/

		for (int i = 0; i < 2; i++)
		{
			std::string answer;
			std::cout << tf[tf_questions_order[i] - 1].get_question() << std::endl << "True or False : ";
			std::cin >> answer;
			answer = lower_case(answer);
			if (answer == tf[tf_questions_order[i] - 1].get_answer())
				tf_result++;
			p1.answers_entered.push_back(answer);
			p1.tf.push_back(tf[tf_questions_order[i] - 1].get_question());
			p1.tf.push_back(tf[tf_questions_order[i] - 1].get_answer());
		}

		std::string answer;
		std::cout << complete[complete_questions_order[0] - 1].get_question() << std::endl << "Complete : ";
		std::cin >> answer;
		answer = lower_case(answer);
		p1.answers_entered.push_back(answer);
		if (answer == complete[complete_questions_order[0] - 1].get_answer())
			c_result++;
		p1.complete.push_back(complete[complete_questions_order[0] - 1].get_question());
		p1.complete.push_back(complete[complete_questions_order[0] - 1].get_answer());
		std::cout << "correct mcq question : " << mcq_result << " / 3" << std::endl;
		std::cout << "correct tf question : " << tf_result << " / 2" << std::endl;
		std::cout << "correct complete question : " << c_result << " / 1" << std::endl;
		std::cout << "total result : " << mcq_result*2 + tf_result + c_result*3 << " / 11" << std::endl;
		p1.results.push_back(mcq_result*2 + tf_result + c_result * 3);
		p1.mcq_result.push_back(mcq_result);
		p1.tf_result.push_back(tf_result);
		p1.c_result.push_back(c_result);
		p1.quiz_taken++;
	}
};

