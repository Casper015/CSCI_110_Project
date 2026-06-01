/*
* mail.cpp - CSCI 110 Project #2: Simple Mail program
*
* 11/18/25 Chun Wong - Initial version
* 5/17/26 Chun Wong - Updated cloud server IP address
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <ctime>
#include "httplib.h"
#pragma warning(disable: 4996)	// deprecation of ctime, locatime, getenv

using namespace std;

const string AppVersion = "1.0";					// This app version
const string MailServer = "http://34.57.53.121:80";	// Cloud server
const int ServerTimeout = 5;						// Cloud server timeout
const string MailExt = ".mail";						// File extension of off-line mail
const string HIGHLIGHT = "\x1b[7m";					// ANSI reverse
const string RESET = "\x1b[0m";						// ANSI normal

string Username;
string MailPath;									// Path of off-line mail storage

struct Mail
{
	string MessageId;
	string From, To;
	string Subject;
	string Body;
	time_t Date;
};

#pragma region Function Prototypes
void init();
bool login();
void menu();
void listMail();
vector<Mail> getMail();
bool downloadMail();
bool purgeMail();
void writeMail(const Mail&);
void writeMail(ofstream&, const Mail&);
void writeMail(stringstream&, const Mail&);
void composeMail();
bool sendMail(const Mail&);
void readMail();
void deleteMail();
bool deleteMail(const string);
bool readMail(const ifstream&, Mail&);
bool readMail(stringstream&, Mail&);
void findMail();
string createMailId(); 
string absoluteDate(time_t);
string relativeDate(time_t);
string tolower(const string&);
int casefind(const string&, const string&, size_t = 0);  ///casefind - Finds the first occurrence of a pattern within a larger text, returning the character position of the match.
int max(const int, const int);
string trim(string);
bool mailApi(string, httplib::Params&, string&);
#pragma endregion

#pragma dev
string highlightText(string& text, string& pattern);
void convertMail();
#pragma endregion


// main
int main()
{
	init();
	while (login())
	{
		menu();
	}
	return 0;
}

// init - one-time code
void init()
{
	// For mail message id generator
	srand(static_cast<unsigned int>(time(NULL)));

	// For local mail storage
	auto tmpDir = getenv("TEMP");						// Windows
	MailPath = tmpDir ? tmpDir : getenv("TMPDIR");		// Mac
}

// login - Prompt for a username, any username. No password authentication.
bool login()
{
	Username = "";
	do
	{
		cout << "Simple Mail v" << AppVersion << endl;
		cout << "Username: ";
		getline(cin, Username);
	} while (cin.good() && Username.empty());

	return !Username.empty();
}

// menu - Prompt for menu choice and dispatch.
void menu()
{
	while (!Username.empty())
	{
		cout << endl;
		cout << string(60, '*') << endl;
		cout << "Mail server:  " << MailServer << endl;
		cout << "Mail folder:  " << MailPath << endl;
		cout << "Logged-in as: " << Username << endl;
		cout << "(L)ist, (R)ead, (S)end, (D)elete, (F)ind, Do(w)nload, Lo(g)out: ";
		char c;
		cin >> c;
		c = tolower(c);
		cout << endl;
		cin.ignore(100, '\n');
		if (cin.fail())
		{
			cin.clear();
			continue;
		}

		switch (c)
		{
			case 'l': listMail(); break;
			case 'r': readMail(); break;
			case 's': composeMail(); break;
			case 'd': deleteMail(); break;
			case 'f': findMail(); break;
			case 'w': downloadMail(); break;
			case 'g': Username = ""; break;
			default: cout << "Invalid choice. Try again." << endl;
		}
	}
}

// listMail - Display off-line mail summary.
void listMail()
{
	auto allMail = getMail();
	if (allMail.empty())
	{
		cout << "You have no mail." << endl;
		return;
	}

	int cnt = 1;
	cout << left << setw(3) << "#" << setw(10) << "From" << setw(30) << "Subject" << setw(20) << "Date" << endl;
	cout << string(60, '-') << endl;
	for (auto mail : allMail)
	{
		cout << setw(3) << cnt++ << setw(10) << mail.From.substr(0, 20) << setw(30) << mail.Subject.substr(0, 20) << setw(20) << relativeDate(mail.Date) << endl;
	}
}

// readMail - Prompt user for off-line message # to display.
void readMail()
{
	auto allMail = getMail();

	cout << "Read message # (1-" << allMail.size() << ") : ";
	int n;
	cin >> n;
	if (cin.fail())
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout << "Invalid entry." << endl;
		return;
	}
	cin.ignore(100, '\n');

	n--;
	if (n < 0 || n >= allMail.size())
	{
		cout << "Invalid entry." << endl;
		return;
	}

	auto mail = allMail.at(n);
	cout << "From: " << mail.From << endl;
	cout << "To: " << mail.To << endl;
	cout << "Date: " << absoluteDate(mail.Date) << endl;
	cout << "Message-Id: " << mail.MessageId << endl;
	cout << "Subject: " << mail.Subject << endl;
	cout << endl;
	cout << mail.Body << endl;
}

// deleteMail - Prompt user for off-line message # to delete.
void deleteMail()
{
	cout << "Delete message #: ";
	string line;
	getline(cin, line);
	stringstream ss(line);
	int n;
	vector<int> nums;
	auto allMail = getMail();
	while (ss >> n)
	{
		auto mail = allMail.at(n - 1);
		if (deleteMail(mail.MessageId))
			nums.push_back(n);
	}
	if (nums.size() > 0)
	{
		cout << "Deleted messages " << nums.at(0);
		for (int i = 1; i < nums.size(); i++)
			cout << "," << nums.at(i);
		cout << endl;
	}
}

// sendMail - Prompt user to compose and send email to mail server in real-time.
void composeMail()
{
	Mail m;
	m.MessageId = createMailId();
	m.From = Username;
	cout << "To: ";
	getline(cin, m.To);
	cout << "Subject: ";
	getline(cin, m.Subject);
	cout << "Body (. to end):" << endl;
	string line;
	while (getline(cin, line) && line != ".")
		m.Body += line + "\n";
	m.Date = time(NULL);

	if (sendMail(m))
		cout << "Message sent." << endl;
	else
		cout << "Send aborted." << endl;
}

// findMail - Search all off-line mail for user-entered pattern.
void findMail()
{
	cout << "Search: ";
	string pattern;
	getline(cin, pattern);
	if (pattern.empty()) return;

	cout << endl;
	int count = 0;
	auto allMail = getMail();
	for (int i = 0; i < allMail.size(); i++)
	{
		auto mail = allMail[i];
		auto inBody = casefind(mail.Body, pattern);
		auto inSubj = casefind(mail.Subject, pattern);
		if (inBody >= 0 || inSubj >= 0)
		{
			cout << "Message #" << (i + 1) << endl;
			cout << "From: " << mail.From << endl;
			cout << "To: " << mail.To << endl;
			

			// cout << mail.Body << endl
			// cout << "Subject: " << mail.Subject << endl;

			cout << "Subject: "  << (inSubj >= 0 ? " (matched in subject)" : "") << endl;
			cout << (inBody >= 0 ? " (matched in body)" : "") << endl;

			cout << string(60, '-') << endl;
			count++;
		}
	}
	if (count == 0)
		cout << "No messages matched." << endl;
	else
		cout << count << " message" << (count > 1 ? "s" : "") << " matched." << endl;
}

// downloadMail - Retrieve email from mail server. 
bool downloadMail()
{
	httplib::Params params = {
		{ "user", Username },
	};
	string rawMailText;
	if (!mailApi("recv", params, rawMailText))
		return false;

	cout << "BEGIN: RAW MAIL TEXT" << endl;
	cout << rawMailText << endl;
	cout << "END: RAW MAIL TEXT" << endl;

#if false
	int count = 0;
	stringstream sin(rawMailText);
	while (sin.good())
	{
		Mail m;

		//
		// ADD CODE HERE TO PARSE rawMailText to create multiple Mail objects
		//

		if (sin.good())
		{
			writeMail(m);
			count++;
		}
	}

	cout << "Downloaded " << count << " messages." << endl;
	purgeMail();	// Purge mail from server after successful download

	return true;
}

bool purgeMail()
{
	httplib::Params params = { { "user", Username }, };
	string res;
	if (!mailApi("purge", params, res))		// returns # of messages purged
		return false;
	return true;
}

// getMail - Read local folder for mail files into memory and return as vector<Mail>.
vector<Mail> getMail()
{
	vector<Mail> mailList;
	for (const auto& entry : filesystem::directory_iterator(MailPath))
	{
		if (entry.path().extension() == MailExt)
		{
			Mail mail;
			ifstream ifs(entry.path().string());
			if (readMail(ifs, mail))
				mailList.push_back(mail);
			ifs.close();
		}
	}
	return mailList;
}

// readMail - Create a Mail object from an ifstream
bool readMail(const ifstream& ifs, Mail& mail)
{
	stringstream ss;
	ss << ifs.rdbuf();
	return readMail(ss, mail);
}

// readMail - Create a Mail object from a stringstream
bool readMail(stringstream& ssMail, Mail& m)
{
	// Parse header
	string line;
	while (getline(ssMail, line) && !line.empty())
	{
		stringstream ssLine(line);
		string keyword;
		ssLine >> keyword;
		auto key = tolower(keyword);
		if (key == "to:")
		{
			getline(ssLine, m.To);
			m.To = trim(m.To);
			// Only read your own email
			if (tolower(m.To) != tolower(Username)) return false;
		}
		else if (key == "from:")
		{
			getline(ssLine, m.From);
			m.From = trim(m.From);
		}
		else if (key == "date:")
		{
			string s;
			getline(ssLine, s);
			stringstream sDate(s);
			sDate >> m.Date;
		}
		else if (key == "message-id:")
		{
			getline(ssLine, m.MessageId);
			m.MessageId = trim(m.MessageId);
		}
		else if (key == "subject:")
		{
			getline(ssLine, m.Subject);
			m.Subject = trim(m.Subject);
		}
	}

	// Parse body
	while (getline(ssMail, line))
		m.Body += line + "\n";

	return true;
}

// sendMail - Send a Mail object to mail server
bool sendMail(const Mail& mail)
{
	httplib::Params params = {
		{ "mid", mail.MessageId },
		{ "from", mail.From },
		{ "to", mail.To },
		{ "sdate", to_string(mail.Date) },
		{ "subj", mail.Subject },
		{ "body", mail.Body }
	};
	string res;
	return mailApi("send", params, res);
}

// writeMail - Writes a Mail object the local storage
void writeMail(const Mail& mail)
{
	string fullPath = MailPath + "/" + mail.MessageId + MailExt;
	ofstream ofs(fullPath);
	writeMail(ofs, mail);
	ofs.close();
}

// writeMail - Writes a Mail object to an ofstream
void writeMail(ofstream& ofs, const Mail& mail)
{
	stringstream ss;
	writeMail(ss, mail);
	ofs << ss.rdbuf();
}

// writeMail - Writes a Mail object to a stringstream
void writeMail(stringstream& ss, const Mail& mail)
{
	ss << "From: " << mail.From << endl;
	ss << "To: " << mail.To << endl;
	ss << "Message-Id: " << mail.MessageId << endl;
	ss << "Date: " << mail.Date << endl;
	ss << "Subject: " << mail.Subject << endl;
	ss << endl;
	ss << mail.Body;
}

// deleteMail - Deletes a Mail from local storage
bool deleteMail(const string id)
{
	string fname = MailPath + "/" + id + MailExt;
	auto res = remove(fname.c_str());
	return (res == 0);
}

// createMailId - Generate a unique Mail id
string createMailId()
{
	stringstream ss;
	for (int i = 0; i < 20; i++)
		ss << hex << rand() % 16;
	return ss.str();
}

// absoluteDate - Convert a time_t structure into a full date format (e.g. 11/18/25 04:15 pm)
string absoluteDate(time_t time)
{
	tm* local_time = localtime(&time);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%m/%d/%y %I:%M %p", local_time);
	return buffer;
}

// relativeDate - Convert a time_t structure into a short date format.  If it's today, show time only (e.g. Today 04:15 pm).
// If it's not today, show date and time (e.g. 11/18/25 04:15 pm)
string relativeDate(time_t observed)
{
	tm* t = localtime(&observed);
	tm obs_t = *t;	// copy from static struct
	auto now = time(NULL);
	t = localtime(&now);
	tm now_t = *t;	// copy from static struct
	const char* sfmt;
	// Compare if same date (year, month and day)
	if (obs_t.tm_year == now_t.tm_year && obs_t.tm_mon == now_t.tm_mon && obs_t.tm_mday == now_t.tm_mday)
		sfmt = "Today %I:%M %p";
	else
		sfmt = "%m/%d/%y %I:%M %p";
	char buffer[80];
	strftime(buffer, sizeof(buffer), sfmt, &obs_t);
	return buffer;
}

// tolower - Converts a string to lowercase.  Returns a newly allocated string.  Input string is not altered.
string tolower(const string& s)
{
	string t;
	for (auto c : s)
		t += tolower(c);
	return t;
}

// casefind - Finds the first occurrence of a pattern within a larger text, returning the character position of the match.
// If offset (3rd parameter) is provided, the match would start at the offset position.
int casefind(const string& text, const string& pattern, size_t offset)
{
	auto text2 = tolower(text);
	auto pat2 = tolower(pattern);
	auto pos = text2.find(pat2, offset);
	return pos != string::npos ? static_cast<int>(pos) : -1;
}

// max - Returns the larger of 2 integers
int max(const int a, const int b)
{
	return a > b ? a : b;
}

// trim - Removes leading and trailing spaces in a string.  A newly allocated string is returned.  Input string is not altered.
string trim(string s)
{
	s.erase(0, s.find_first_not_of(" \n\r\t"));
	s.erase(s.find_last_not_of(" \n\r\t") + 1);
	return s;
}

// mailApi - Calls a cloud service using httplib.  Makes a POST call and returns the raw data from the call.
bool mailApi(string route, httplib::Params& params, string& retVal)
{
	httplib::Client cli(MailServer);
	cli.set_connection_timeout(ServerTimeout);
	auto res = cli.Post("/" + route, params);
	if (!res)
	{
		const auto err = res.error();
		cerr << "HTTP error: " << httplib::to_string(err) << endl;
		return false;
	}

	if (res->status != 200)
	{
		cerr << "HTTP Status: " << res->status << endl;
		return false;
	}
	retVal = res->body.data();
	return true;
}

string highlightText(string& text, string& pattern)
{
	if (pattern.empty()) return text;
	string output;

	int pos = 0, matchPos = 0, patternLen = static_cast<int>(pattern.length());

	// Loop through the internal function casefind.
	while(casefind(text, pattern, pos) != -1)
	{

		output += text.substr(pos, matchPos - pos);
		output += HIGHLIGHT + text.substr(matchPos, patternLen) + RESET;
		pos = matchPos + patternLen;
	}

	output += text.substr(pos);
	return output;
}
