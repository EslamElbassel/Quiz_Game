#pragma once
#include<string>
#include<iostream>

/** Parent class **/

class Question
{
protected:
	std::string question;
	int ID;
public:
	/** Default constructor to initialize question's data **/

	Question(std::string qu, int id) { question = qu; ID = id; }
};

/**Child Classes**/

class TFQuestion : public Question
{
private:
	std::string answer;
public:
    /** Getters **/

	std::string get_question() { return question; }
	std::string get_answer() { return answer; }
	int get_id(){ return ID; }

	/** Default constructor with parameterized list initialization to the base (question) class and setting the answer of the question **/

	TFQuestion(std::string qu, std::string an,int id) :Question(qu,id) { answer = an; }

	/** Prints a Question **/

	void display_question()
	{
		std::cout << "[ID : " << ID <<"]"<< " " << question << std::endl << std::endl << "Answer : " << answer << std::endl << std::endl;
	}

	/** operator overload for == **/

	bool operator==(std::string question)
	{
		if (this->question == question)
		{
			return 1;
		}
		return 0;
	}
};

class MCQuestion : public Question
{
private:

	std::string choiceA , choiceB , choiceC , choiceD;

public:

	/** Default constructor with parameterized list initialization to the base (question) class and setting the answers of the question **/

	MCQuestion(std::string qu, std::string a, std::string b, std::string c, std::string d,int id)
		:Question(qu,id)
	{
		choiceA = a;
		choiceB = b;
		choiceC = c;
		choiceD = d;
	}

	/**Prints a Question**/

	void display_question()
	{
		std::cout << "[ID : " << ID <<"]"<< " " <<  question << std::endl <<std::endl<< "[1]" << choiceA << "\t[2]" << choiceB << "\t[3]" << choiceC << "\t[4]" << choiceD << std::endl << std::endl;
	}

	/** Getters **/

	int get_id() { return ID; }
	std::string get_question(){ return question; }
	std::string get_a() { return choiceA; }
	std::string get_b() { return choiceB; }
	std::string get_c() { return choiceC; }
	std::string get_d() { return choiceD; }

	//operator overload for ==
	bool operator==(std::string question)
	{
		if (this->question == question)
		{
			return 1;
		}
		return 0;
	}
};
class CQuestion : public Question
{
private:

	std::string answer;

public:

	/** Getters**/

	int get_id() { return ID; }
	std::string get_question() { return question; }
	std::string get_answer() { return answer; }

	/** Default constructor with parameterized list initialization to the base (question) class and setting the answer of the question **/

	CQuestion(std::string qu, std::string an,int id) :Question(qu,id) { answer = an; }

	/** Prints a Question **/

	void display_question()
	{
		std::cout << "[ID : " << ID <<"]"<< " " << question << std::endl << std::endl << "Answer : " << answer << std::endl << std::endl;
	}

	/** operator overload for == **/

	bool operator==(std::string question)
	{
		if (this->question == question)
		{
			return 1;
		}
		return 0;
	}

};
