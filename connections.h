#include <bits/stdc++.h>
using namespace std;

#define yellow_bold "\033[1;33m" //Colour codes
#define yellow "\033[0;33m"
#define red_bold "\033[1;31m"
#define green_bold "\033[1;32m"
#define green "\033[0;32m"
#define white "\033[0;37m"
#define cyan "\033[0;36m"
#define cyan_bold "\033[1;33m"

class Connection
{
protected:
    string username;
    string password;

public:
    void admin();
    void user();
};

class Graph
{
protected:
    unordered_map<string, vector<string>> GM; //Adjacency Hash Map

public:
    void addEdge(string X, string Y);
    int checkUsername(string uname);
    void checkUsername2(string, unordered_map<string, int> &, unordered_set<string> &);
    void PrintAdjList();
    int ShortestDistance(string src, string dest);
    int checkExists(string uname1, string uname2);
    void RemoveConnections(string uname);
    void RemoveConnections();
};

class User : public Connection
{
protected:
    string mobile;
    string name;
    string college;
    int ref_no;

public:
    void getdata();
    void showdata();
    string getusername()
    {
        return username;
    }
    string getpassword()
    {
        return password;
    }
    int getref()
    {
        return ref_no;
    }
};

class Admin : public Connection
{
protected:
    string password;

public:
    Admin()
    {
        password = "skv"; // admin password
    }
    string getpassword()
    {
        return password;
    }
};

pair<string, int> Login();
void DisplayConnections(string uname);
void AddConnections(string uname);
void AddConnections(string uname1, string uname2);
void SearchUserDetails(string uname);
void FormConnections();