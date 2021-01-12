/** Classes **/
#include "question.h"
#include "User.h"
#include "Quiz.h"

/** Libraries **/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

/** General Functions **/
string lower_case(string);

/** login functions **/
int enter_up();
int admin_or_user(string, string);

/** admin functions**/
int admin_list(int);
void print_users();
void update_name(int);
void add_user();
void add_question();
void view_all_questions();
string check_user();
void read_from_files();

/** player functions **/
int user_list(int);

/** Vectors and Variables **/
vector <admin> admins;
vector <player> players;

Quiz quiz;
static int id = 1;
int current_user = 0;

int main()
{
	/** Default users **/
	admins.push_back(admin("admin", "admin", "admin", "admin"));
	players.push_back(player("player", "player", "player", "player"));

	/** Main loop **/
	while (1)
	{
		int answer = enter_up();
		bool exit = 1; /** Checks if the user want to switch account or exit the program (0 exit , 1 enter username and password) **/
		if (answer == 0)
			cout << "wrong username and password\n";
		else if (answer == -1)
			exit = user_list(answer);
		else
			exit = admin_list(answer);
		if (!exit)
		{
			cout << "Thanks for using our program.";
			break;
		}
	}

}

//Log In Menu
int enter_up()
{
	string pass, user;
	cout << "*******************************************************************\n";
	cout << "Welcome to the Quiz game program V2.0!\n";
	cout << "*******************************************************************\n";
	cout << "Enter your username : ";
	cin >> user;
	cout << "Enter your password : ";
	cin >> pass;
	int answer = admin_or_user(user, pass);
	return answer;
}

/** Checks if Admin(1) or User(-1) or None(0) (Used in Enter_up) **/
int admin_or_user(string us,string pa)
{
	for (unsigned int i = 0 ; i < admins.size() ; i++)
	{
		if (admins[i].get_name() == us && admins[i].get_password() == pa)
		{
			current_user = i;
			return 1;
		}
	}

	for (unsigned int i = 0; i < players.size(); i++)
	{
		if (players[i].get_name() == us && players[i].get_password() == pa)
		{
			current_user = i;
			return -1;
		}
	}
	return 0;
}

/** Switch any word/sentence to lower case **/
string lower_case(string name)
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

/** Admin menu options **/

int admin_list(int ad)
{
	while (true)
	{
		int answer = 0;
		admins[current_user].print_menu();
		do {
			std::cout << "My choice : ";
			cin >> answer;
		} while (answer < 1 || answer > 8);
		switch (answer)
		{
		case 1:
			return 1;
			break;
		case 2:
			update_name(ad);
			break;
		case 3:
			print_users();
			break;
		case 4:
			add_user();
			break;
		case 5:
			/** Checks if there is a Question or not **/
			if (quiz.get_mcqsize() == 0 && quiz.get_cqsize() == 0 && quiz.get_tfsize() == 0)
				cout << "\nThere isn't any Questions.\n\n";
			else
				view_all_questions();
			break;
		case 6:
			add_question();
			break;
		case 7:
			read_from_files();
			break;
		case 8:
			return 0;
			break;
		}
	}
}

/** Prints all the users with the option to add a new user **/
void print_users()
{
	char answer = '0';
		cout << "First name\tLast name\tUsername\tRole\n";

		/** prints admins **/
		for (unsigned int i = 0; i < admins.size(); i++)
			cout << admins[i].get_fs() << "\t\t" << admins[i].get_ls() << "\t\t" << admins[i].get_name() << "\t\t" << "Admin" << endl;

		/** prints users**/
		for (unsigned int i = 0; i < players.size(); i++)
			cout << players[i].get_fs() << "\t\t" << players[i].get_ls() << "\t\t" << players[i].get_name() << "\t\t" << "player" << endl;

		/** a loop that takes n to add a user or b to go back to the main menu
		if any other value is taken a error is prompt and you are requested to enter it again
		**/
		do {
			cout << "Press [n] if you want to add a new user or [b] to go back to the main menu : ";
			cin >> answer;
			if (answer == 'n')
			{
				add_user();
				cout << "\n User added. \n";
			}
			else if (answer == 'b'){}
			else
				cout << "\n invalid input. \n\n";
		} while (answer != 'b');
}

//Changes name of admin/player
void update_name(int AdminorUser)
{
	string fs,ls;
	cout << "Enter The First Name :" << endl;
	cin >> fs;
	cout << "Enter The last Name :" << endl;
	cin >> ls;
	if (AdminorUser == 1)
	{
		admins[current_user].set_fs(fs);
		admins[current_user].set_ls(ls);
	}
	else
	{
		players[current_user].set_fs(fs);
		players[current_user].set_ls(ls);
	}
}

//Checks if the user already exists before adding (used in add_user)
string check_user()
{
	string user;
	bool answer;
	do
	{
		cout << "Enter Your Username : ";
		cin >> user;
		answer = 1;

		//checks if user is an already registered admin
		for (unsigned int i = 0; i < admins.size(); i++)
		{
			if (admins[i] == user)
			{
				cout << "\nThis Username is already used \n";
				answer = 0;
			}
		}

		//checks if user is an already registered admin
		for (unsigned int i = 0; i < players.size(); i++)
		{
			if (players[i] == user)
			{
				cout << "\nThis Username is already used \n";
				answer = 0;
			}
		}

	} while (answer == 0);
	return user;
}

/** adds player/admin according to the role **/
void add_user()
{
	string fs, ls, role, user, pass;
	user = check_user();
	cout << "Enter Your Password : ";
	cin >> pass;
	cout << "Enter Your First Name : ";
	cin >> fs;
	cout << "Enter Your Last Name : ";
	cin >> ls;
	while (true) {
		cout << "Enter Your Role : ";
		cin >> role;
		if (role == "admin")
		{
			admins.push_back(admin(user, pass, fs, ls));
			break;
		}
		else if (role == "player")
		{
			players.push_back(player(user, pass, fs, ls));
			break;
		}
		cout << "\n Invalid Role \n";
	}
}

//the list of the player
int user_list(int us)
{
	int answer = 0;
	while (true)
	{
		players[current_user].print_menu();
		do {
			std::cout << "My choice : ";
			cin >> answer;
		} while (answer < 1 || answer > 7);
		switch (answer)
		{
			case 1:
				return 1;
				break;
			case 2:
				update_name(us);
				break;
			case 3:
				//checks if there is enough questions for a quiz (mcq : 3 , tf : 2 , complete : 1)
				if (quiz.get_mcqsize() < 3 && quiz.get_cqsize() < 1 && quiz.get_tfsize() < 2)
				{
					cout << "The questions you need left : \nMCQ : " << 3 - quiz.get_mcqsize() << "\nTF : " << 2 - quiz.get_tfsize()
						<< "\nComplete : " << 1 - quiz.get_cqsize() << "\n\n";
				}
				else
				//starts the quiz
					quiz.start(players[current_user]);
				break;
			case 4:
				//checks to see if there was even a quiz taken first
				if (players[current_user].quiz_taken == 0)
					cout << "\nTake a quiz first.\n\n";
				else
					players[current_user].display_stat();
				break;
			case 5:
				//checks to see if there was even a quiz taken first
				if (players[current_user].quiz_taken == 0)
					cout << "\nTake a quiz first.\n\n";
				else
					players[current_user].display_quizes();
				break;
			case 6:
				//checks to see if there were 2 quizzes taken

				if (players[current_user].quiz_taken == 0 )
					cout << "\nYou have to take two Quizzes first.\n\n";
                else if(players[current_user].quiz_taken ==1)
                {
                    cout << "\nYou have to take one more quiz.\n\n";
                }
				else
					players[current_user].displayTwoQuizes();
				break;
			case 7:
				return 0;
				break;
		}
	}
}

/** A function that adds any type of specified questions **/
void add_question()
{
	cout << "What Type of Questions do you want to add (Mcq , TF , Complete) : ";
	string answer;
	cin >> answer;
	answer = lower_case(answer);
	if (answer == "mcq")
	{
		string Question, answera, answerb, answerc, answerd;
		cout << "Enter the New Question : ";
		cin.ignore();
		getline(cin, Question);
		/** checks to see if the question already exists **/
		if (!quiz.check_mcq(Question))
		{
			cout << "Enter the Choice 1 (the correct one) : ";
			getline(cin, answera);
			cout << "Enter the Choice 2 : ";
			getline(cin, answerb);
			cout << "Enter the Choice 3 : ";
			getline(cin, answerc);
			cout << "Enter the Choice 4 : ";
			getline(cin, answerd);
			quiz.pushmcq(MCQuestion(Question, answera, answerb, answerc, answerd, id));
			id++;
		}
		else
			cout << "\nThis Question Already Exists.\n\n";
	}
	else if (answer == "tf")
	{
		string Question, answer;
		cout << "Enter the New Question : ";
		cin.ignore();
		getline(cin, Question);
		if (!quiz.check_tf(Question))
		{
			cout << "True or False : ";
			getline(cin, answer);
			quiz.pushtf(TFQuestion(Question, answer, id));
			id++;
		}
		else
			cout << "\nThis Question Already Exists.\n\n";
	}
	else if (answer == "complete")
	{
		string Question, answer;
		cout << "Enter the New Question : ";
		cin.ignore();
		getline(cin, Question);
		if (!quiz.check_complete(Question))
		{
			cout << "The Answer : ";
			getline(cin, answer);
			quiz.pushcomplete(CQuestion(Question, answer, id));
			id++;
		}
		else
			cout << "\nThis Question Already Exists.\n\n";
	}
}

/** A function that prints all questions with an option to delete them **/
void view_all_questions()
{
	char answer = '0';
	do {
    cout << endl;
    cout << "Number of questions available : " << ( quiz.get_mcqsize()+quiz.get_tfsize()+quiz.get_cqsize() ) << endl;
    cout << "*********************************************************\n";
	cout << "MCQ Question : " << quiz.get_mcqsize() << " Questions\n";
	cout << "*********************************************************\n";
	quiz.display_mcq();
	cout << "*********************************************************\n";
	cout << "TF Question : " << quiz.get_tfsize() << " Questions\n";
	cout << "*********************************************************\n";
	quiz.display_tf();
	cout << "*********************************************************\n";
	cout << "Complete Question : " << quiz.get_cqsize() << " Questions\n";
	cout << "*********************************************************\n";
	quiz.display_complete();
	cout << "*********************************************************\n";
	cout << "Press [d] and the question ID if you want to delete a question (Example: d 2)  \nPress [b] if you want to go back to the main menu : ";
		cin >> answer;
		if (answer == 'd')
		{
			int id;
			cin >> id;
			quiz.erase(id);
		}
		else if (answer == 'b') {}
		else
			cout << "\n invalid input. \n\n";
	} while (answer != 'b');
}

/** The functions that reads from file **/
void read_from_files()
{
	int repeated = 0;   /**repeated questions**/
	int added = 0;      /** added questions **/
	cout << "Enter the file name : ";
	string file_name;
	cin.ignore();
	getline(std::cin, file_name);
	ifstream inFile;
	inFile.open(file_name.c_str());
	string type;
	while (getline(inFile, type))
	{
		if (type == "MCQ")
		{
			string question, a, b, c, d;
			getline(inFile, question);
			getline(inFile, a);
			getline(inFile, b);
			getline(inFile, c);
			getline(inFile, d);
			/** checks to see if the questions is repeated**/
			if (!quiz.check_mcq(question))
			{
				quiz.pushmcq(MCQuestion(question, a, b, c, d, id));
				id++;
				added++;
			}
			else
				repeated++;
		}
		else if (type == "TF")
		{
			string question, answer;
			getline(inFile, question);
			getline(inFile, answer);
			if (!quiz.check_tf(question))
			{
				/** checks if the answer isn't false or true **/
				if (answer == "false" || answer == "true")
				{
					quiz.pushtf(TFQuestion(question, answer, id));
					id++;
					added++;
				}
				else
				{
					cout << "\nInvalid answer in a TF Question.\n\n";
					break;
				}
			}
			else
				repeated++;
		}
		else if (type == "COMPLETE")
		{
			string question, answer;
			getline(inFile, question);
			getline(inFile, answer);
			if (!quiz.check_complete(question))
			{
				/** checks if the answer is empty**/
				if (answer == "")
				{
					cout << "\nEmpty answer in a complete question\n\n";
					break;
				}
				else
				{
					answer = lower_case(answer);
					quiz.pushcomplete(CQuestion(question, answer, id));
					id++;
					added++;
				}
			}
			else
				repeated++;
		}
		else
		{
			cout << "Invalid Type : " << type; /** if the type wasnt mcq , tf , complete **/
			break;
		}
	}
	inFile.close();
	if (repeated >= 1){
		cout << "Repeated Questions : " << repeated << '\n';
		cout << "Added Questions : " << added << '\n';
	}
	cout << endl;
}
