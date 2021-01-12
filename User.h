#pragma once
#include <iostream>
#include <string>
#include <vector>

/**Base class**/

class user
{
protected:
	std::string username, password , first_name , last_name;
public:
	/** Default constructor to Initialize User's data **/
	user(std::string us, std::string ps , std::string fn, std::string ls)
	{
		username = us;
		password = ps;
		first_name = fn;
		last_name = ls;
	}
};

/** Child classes **/

class admin : private user
{
public:

	/** Default constructor with parameterized list initialization to the base (user) class **/

	admin(std::string us, std::string pa, std::string fn, std::string ls) :user(us,pa,fn,ls){}

	/** Prints admin menu **/

	void print_menu()
	{
		std::cout << "Welcome "<< first_name << " " << last_name << " (ADMIN), please choose from the following options : " << std::endl;
		std::cout << "[1] Switch accounts" << std::endl;
		std::cout << "[2] Update your name" << std::endl;
		std::cout << "[3] View all users" << std::endl;
		std::cout << "[4] Add new user" << std::endl;
		std::cout << "[5] View all questions" << std::endl;
		std::cout << "[6] Add new question" << std::endl;
		std::cout << "[7] Load questions from file" << std::endl;
		std::cout << "[8] Exit the program" << std::endl;
	}
	/** Getters **/

	std::string get_name() { return username; }
	std::string get_password() { return password; }
	std::string get_fs() { return first_name; }
	std::string get_ls() { return last_name; }

	/** Setters **/

	void set_fs(std::string fs) { first_name = fs; }
	void set_ls(std::string ls) { last_name = ls; }

	/** Operator overriding to check for equality **/

	bool operator==(std::string user)
	{
		if (username == user)
		{
			return 1;
		}
		return 0;
	}
};

class player : private user
{
public:
	/** for quiz stats **/

	std::vector <int> results , mcq_result , tf_result , c_result;

	/** for displaying two quizzes **/

	std::vector <std::string> answers_entered;
	std::vector <std::string> mcq_questions;
	std::vector <std::string> mcq_answers;
	std::vector <std::string> tf;
	std::vector <std::string> complete;

	int quiz_taken = 0; /** Number of Quizzes taken. **/

	/** Prints player's list **/
	void print_menu()
	{
		std::cout << "Welcome " << first_name << " " << last_name << " (PLAYER), please choose from the following options :" << std::endl;
		std::cout << "[1] Switch accounts" << std::endl;
		std::cout << "[2] Update your name" << std::endl;
		std::cout << "[3] Start a new quiz" << std::endl;
		std::cout << "[4] Display your scores statistics" << std::endl;
		std::cout << "[5] Display all your scores" << std::endl;
		std::cout << "[6] Display details of your last 2 quizzes" << std::endl;
		std::cout << "[7] Exit the program" << std::endl;
	}

	/** Default constructor with parameterized list initialization to the base (user) class **/
	player(std::string us, std::string pa, std::string fn, std::string ls) :user(us, pa, fn, ls) {}

	/** Getters **/

	std::string get_name() { return username; }
	std::string get_password() { return password; }
	std::string get_fs() { return first_name; }
	std::string get_ls() { return last_name; }

	/** Setters **/

	void set_fs(std::string fs) { first_name = fs; }
	void set_ls(std::string ls) { last_name = ls; }

	/**Operator overriding to check for equality **/

	bool operator==(std::string user)
	{
		if (username == user)
		{
			return 1;
		}
		return 0;
	}

	/** displaying statistics for the user **/

	void display_stat()
	{
		int max = results[0], min = results[0];
		double mcq_total = 0, tf_total = 0, c_total = 0, total = 0;

		/** looping through quizzes results and evaluate minimum and maximum results and score of total # of type-questioned. **/

		for (unsigned int i = 0; i < results.size(); i++)
		{
			if (min > results[i])
				min = results[i]; /** sets the minimum **/
			else if (max < results[i])
				max = results[i]; /** sets the maximum **/

			total += results[i];
			mcq_total += mcq_result[i];
			tf_total += tf_result[i];
			c_total += c_result[i];
		}
		std::cout << "score statistics per quiz : \n";
		std::cout << "Number of Quizzes taken : " << quiz_taken << '\n';
		std::cout << "Highest quiz score : " << max << "/ 11\n";
		std::cout << "Lowest quiz score : " << min << "/ 11\n";
		std::cout << "Average quiz score : " << total/results.size() << "/ 11\n";
		std::cout << "Your score statistics per question type : \n";
		std::cout << "Number of MC questions : " << quiz_taken * 3 << '\n';
		std::cout << "Number of Complete questions : " << quiz_taken << '\n';
		std::cout << "Number of T / F Questions : " << quiz_taken * 2 << '\n';
		std::cout << "Average grade for MCQ questions : "<< (mcq_total * 2)/ (quiz_taken * 3) << " / 2 \n";
		std::cout << "Average grade for Complete questions "<< (c_total * 3) / (quiz_taken) << " / 3 \n";
		std::cout << "Average grade for T / F questions : " << tf_total / (quiz_taken * 2) << " / 1 \n";
	}

	/** displays all quizzes with all there scores **/

	void display_quizes()
	{
		for (unsigned int i = 0; i < results.size(); i++)
		{
			std::cout << "Quiz " << i + 1 << "\n"; /** Quiz 1,2,....., quizzes taken **/
			std::cout << "*******************************************************************\n";
			std::cout << "Total Result : " << results[i] << '\n'; /** total result per quiz **/
			std::cout << "Right MCQ Questions : " << mcq_result[i] << '\n';
			std::cout << "Wrong MCQ Questions : " << 3 - mcq_result[i] << '\n';
			std::cout << "Right TF Questions : " << tf_result[i] << '\n';
			std::cout << "Wrong TF Questions : " << 2 - tf_result[i] << '\n';
			std::cout << "Right Complete Questions : " << c_result[i] << '\n';
			std::cout << "Wrong Complete Questions : " << 1 - c_result[i] << '\n';
			std::cout << "*******************************************************************\n";
		}
	}

	/** displays the last two quizzes with specific details **/
	void displayTwoQuizes()
	{
		for (int i = quiz_taken - 2; i < quiz_taken; i++)
		{   /** starting point of the outer for-loop **/
			std::cout << "***********************************************************************\n";
			std::cout << "Quiz NO. " << i + 1 << '\n';
			std::cout << "***********************************************************************\n\n";
			std::cout << "MCQ\n";
			std::cout << "***********************************************************************\n\n";
			for (int m = 0; m < 3; m++)
			{ /** starting point of the inner for-loop - MCQ-questions loop **/

				std::string correct_answer;
				std::cout << mcq_questions[m + (i * 3)] << std::endl << std::endl;
				for (int j = 0; j < 4; j++)
				{   /** starting point of the inner inner for-loop - MCQ-choices loop **/

					if (j == 0)
					{
						std::cout << "[1]" << mcq_answers[j + (m * 4) + (i * 12)] << "\t";
						correct_answer = mcq_answers[j + (m * 4) + (i * 12)];
					}
					else if (j == 1)
						std::cout << "[2]" << mcq_answers[j + (m * 4) + (i * 12)] << "\t";
					else if (j == 2)
						std::cout << "[3]" << mcq_answers[j + (m * 4) + (i * 12)] << "\t";
					else if (j == 3)
						std::cout << "[4]" << mcq_answers[j + (m * 4) + (i * 12)] << "\t";

				}   /** ending point of the inner inner for-loop - MCQ-choices loop **/

				std::cout << "\n\nCorrect Answer : " << correct_answer << std::endl;
				std::cout << "Entered Answer : " << answers_entered[m + (i * 6)] << std::endl;
				if (correct_answer == answers_entered[m + (i * 6)])
					std::cout << "\nAnswer : Correct - Score : 2/2\n";
				else
					std::cout << "\nAnswer : Wrong - Score : 0/2\n";

			} /** ending point of the inner for-loop - MCQ-questions loop **/
			std::cout << "***********************************************************************\n";
			std::cout << "TF\n";
			std::cout << "***********************************************************************\n";
			for (int m = 0; m < 2; m ++)
			{
				std::cout << tf[(m * 2) + (i * 4)] << std::endl;
				std::cout << "Correct Answer : " << tf[(m * 2 + 1) + (i * 4)] << std::endl;
				std::cout << "Entered Answer : " << answers_entered[(m + 3)  + (i * 6)] << std::endl;
				if (tf[(m * 2 + 1) + (i * 4)] == answers_entered[(m + 3) + (i * 6)])
					std::cout << "\nAnswer : Correct - Score : 1/1\n";
				else
					std::cout << "Answer : Wrong - Score : 0/1\n";
			}
			std::cout << "***********************************************************************\n";
			std::cout << "Complete\n";
			std::cout << "***********************************************************************\n";
			std::cout << complete[i * 2] << std::endl;
			std::cout << "Correct Answer : " << complete[1 + i * 2] << std::endl;
			std::cout << "Entered Answer : " << answers_entered[5 + (i * 6)] << std::endl;
			if (complete[1 + i * 2] == answers_entered[5 + (i * 6)])
				std::cout << "\nAnswer : Correct - Score : 3/3\n";
			else
				std::cout << "\nAnswer : Wrong - Score : 0/3\n";
			std::cout << "Total Result : " << results[i] << "\n\n";
		}
	}
};

