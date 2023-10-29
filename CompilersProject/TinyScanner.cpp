#include "TinyScanner.h"

using namespace std;

/*
* enum for each token type in tiny language
*/
enum tokenType {
	SEMICOLON, IF, THEN, END, REPEAT, UNTIL, IDENTIFIER, ASSIGN, READ, WRITE, LESSTHAN, MORETHAN, EQUAL,
	PLUS, MINUS, MULT, DIV, OPENBRACKET, CLOSEDBRACKET, NUMBER, OPENCOMMENT, CLOSEDCOMMENT
};




/*
* Array of strings corresponding to tokenType
*/
std::string tokenTypeStrings[] = {
	"SEMICOLON", "IF", "THEN", "END", "REPEAT", "UNTIL", "IDENTIFIER", "ASSIGN",
	"READ", "WRITE", "LESSTHAN", "MORETHAN", "EQUAL", "PLUS", "MINUS", "MULT", "DIV",
	"OPENBRACKET", "CLOSEDBRACKET", "NUMBER","OPENCOMMENT","CLOSEDCOMMENT"
};


/*
* structure for token which has:
* number if token is number if not number is assigned to zero
* string for value of token
* type of token
*/
struct token {
	int number;
	std::string value;
	tokenType type;
};


/*
* hash function for all reserved word in tiny language
*/
unordered_map<string, tokenType> reservedWords;


//array of tokens
vector<token> tokens;


//string displays all tokens
string tokenList = "";

void scannerInit(void)
{
	reservedWords[";"] = SEMICOLON;
	reservedWords["if"] = IF;
	reservedWords["then"] = THEN;
	reservedWords["end"] = END;
	reservedWords["repeat"] = REPEAT;
	reservedWords["until"] = UNTIL;
	reservedWords[":="] = ASSIGN;
	reservedWords["read"] = READ;
	reservedWords["write"] = WRITE;
	reservedWords["<"] = LESSTHAN;
	reservedWords[">"] = MORETHAN;
	reservedWords["="] = EQUAL;
	reservedWords["+"] = PLUS;
	reservedWords["-"] = MINUS;
	reservedWords["*"] = MULT;
	reservedWords["/"] = DIV;
	reservedWords["("] = OPENBRACKET;
	reservedWords[")"] = CLOSEDBRACKET;
	reservedWords["{"] = OPENCOMMENT;
	reservedWords["}"] = CLOSEDCOMMENT;
	tokenList = "";
	tokens.clear();
}




//convert system string to standard string
static void System2StdString(System::String^ s, string& os) {
	using namespace System::Runtime::InteropServices;
	const char* chars =
		(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
	os = chars;
	Marshal::FreeHGlobal(System::IntPtr((void*)chars));
}


//function to check identifiers and numbers
void checkIdentifiersNumbers(string value,token &t)
{
	/*check if name is number or string assuming
	* assuming number contains only numbers
	* and string contains only strings
	*/
	if (value[0] >= '0' && value[0] <= '9')
	{
#if(DEBUGGING == true)
		cout << "Number: " << value << endl;
#endif
		t = {stoi(value), value, NUMBER};
		tokens.push_back(t);
	}
	else
	{
#if(DEBUGGING == true)
		cout << "Identifier: " << value << endl;
#endif
		t = {0, value, IDENTIFIER };
		tokens.push_back(t);
	}
}



//function for scanner phase in compiler for tiny language
void scanCode(System::String^ codeContentSystem) {
	scannerInit();
	string codeContent;
	System2StdString(codeContentSystem, codeContent);

	string value = "";
	for (int i = 0; i < codeContent.size(); i++) {
		char ch = codeContent[i];

		//special character found
		if (ch == ';' || ch == '>' || ch == '<' || ch == '\\' || ch == '*' || ch == '+' || ch == '-'
			|| ch == '(' || ch == ')' || ch == '=')
		{
			token t;
			if (value != "")
			{
				//check if token is a reserved word or identifier or number
				if (reservedWords.find(value) != reservedWords.end()) {
#if(DEBUGGING ==  true)
					cout << "Found reserved word: " << value << " with type " <<
						tokenTypeStrings[reservedWords[value]] << endl;
#endif
					t = {0, value, reservedWords[value] };
					tokens.push_back(t);
				}
				else {

					checkIdentifiersNumbers(value, t);
				}
				value = "";
			}
			//store special character in a token
			string str(1, ch);
#if(DEBUGGING ==  true)
			cout << "Found reserved word: " << str << " with type " <<
				tokenTypeStrings[reservedWords[str]] << endl;
#endif
			token t2 = {0,str,reservedWords[str]};
			tokens.push_back(t2);
		}

		//ignore whitespaces and check new token
		else if (ch == ' ' && value != "") {
			token t;
			//check if it is a reserved word or identifier or number
			if (reservedWords.find(value) != reservedWords.end()) {
#if(DEBUGGING ==  true)
				cout << "Found reserved word: " << value << " with type " <<
					tokenTypeStrings[reservedWords[value]] << endl;
#endif
				t = {0,value, reservedWords[value] };
				tokens.push_back(t);
			}
			else {
				checkIdentifiersNumbers(value, t);
			}
			value = "";
		}


		/*
		* if found character : then afterwards we will find = and a new token is found assign(:=)
		* after that check token before assign
		*/
		else if (ch == ':') {
			token t;
			if (value != "")
			{
				//check if token is a reserved word or identifier or number
				if (reservedWords.find(value) != reservedWords.end()) {
#if(DEBUGGING ==  true)
					cout << "Found reserved word: " << value << " with type " <<
						tokenTypeStrings[reservedWords[value]] << endl;
#endif
					t = {0, value, reservedWords[value] };
					tokens.push_back(t);
				}
				else {
					checkIdentifiersNumbers(value, t);
				}
				value = "";
			}
			//store assign(:=) in a token
			string str;
			str.push_back(ch);
			i++;
			ch = codeContent[i];
			str.push_back(ch);
			token t2 = {0, str,reservedWords[str] };
			tokens.push_back(t2);
		}

		//found a comment then we will ignore it and store any token before that comment
		else if (ch == '{') {
			token t;
			if (value != "")
			{
				//check if it is a reserved word or identifier or number
				if (reservedWords.find(value) != reservedWords.end()) {
#if(DEBUGGING ==  true)
					cout << "Found reserved word: " << value << " with type " <<
						tokenTypeStrings[reservedWords[value]] << endl;
#endif
					t = {0, value, reservedWords[value] };
					tokens.push_back(t);
				}
				else {
					checkIdentifiersNumbers(value, t);
				}
				value = "";
			}
			//ignore comment
			while (ch != '}')
			{
				i++;
				ch = codeContent[i];
			}
		}


		else
		{
			//ignore new lines,tabs,white spaces in token value
			if (ch != '\n' && ch != '\r' && ch != '\r\n' && ch != ' ' && ch != '\t') {
				value.push_back(ch);
			}
		}
	}

	/*
	* check last token
	*/
	token t;

	//check if token is a reserved word or identifier or number
	if (value != "")
	{
		if (reservedWords.find(value) != reservedWords.end()) {
#if(DEBUGGING ==  true)
			cout << "Found reserved word: " << value << " with type " <<
				tokenTypeStrings[reservedWords[value]] << endl;
#endif
			t = {0, value, reservedWords[value] };
			tokens.push_back(t);
		}
		else {
			checkIdentifiersNumbers(value, t);
		}
		value = "";
	}

#if(DEBUGGING == true)
	std::cout << "------------------------" << std::endl;
	std::cout << "------------------------" << std::endl;
	std::cout << "------------------------" << std::endl;
#endif

	int i = 1;
	for (const token& t : tokens) {
#if(DEBUGGING == true)
		std::wcout << "Token No." << i << std::endl << std::endl;
		std::cout << "Token :" << std::endl << t.value << std::endl << std::endl;
		std::cout << "Token Type :" << std::endl << tokenTypeStrings[t.type] << std::endl;
		std::cout << "------------------------" << std::endl;
#endif
		tokenList += "Token No.";
		string strNumber = to_string(i);
		tokenList += strNumber;
		tokenList += "\r\n";
		tokenList += "\r\n";
		tokenList += "Token :";
		tokenList += "\r\n";
		tokenList += "  ";
		tokenList += t.value;
		tokenList += "\r\n";
		tokenList += "\r\n";
		tokenList += "Token Type :";
		tokenList += "\r\n";
		tokenList += "  ";
		tokenList += tokenTypeStrings[t.type];
		tokenList += "\r\n";
		tokenList += "------------------------";
		tokenList += "\r\n";
		i++;
	}

}

//function to show tokens in gui and save it in text file
void printTokens(System::String^& tokenListSystem)
{
	tokenListSystem = gcnew System::String(tokenList.data());
	string filename = "Token List";
	ofstream out(filename + ".txt");
	out << tokenList;
	out.close();
}
