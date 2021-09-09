#include <unistd.h>
#include "connections.h"
using namespace std;

Admin A;
User U[10];
Graph G;
int usercount = 0; // no of users -> vertices
int concount = 0;  // connection count -> edges

void Connection::admin()
{
    int ch, flag = 0;
    string password;
    cout << "\nEnter admin password to continue: "; //password is skv
    cout << yellow;
    cin >> password;
    cout << cyan;
    if (A.getpassword() != password)
    {
        cout << red_bold;
        cout << "\nPassword entered is wrong! Returning to home page.";
        cout.flush();
        sleep(1);
        cout << ".";
        cout.flush();
        sleep(1);
        cout << ".";
        cout.flush();
        sleep(1);
        cout << ".\n\n";
        system("clear");
        return;
    }
    else
    {
        system("clear");
        cout << yellow_bold;
        cout << "\n\n***************************** ENTERED ADMIN MODE ********************************\n";
    }
    while (flag == 0)
    {
        cout << cyan;
        cout << "\n1. Create New User\n";
        cout << "2. Establish Connections\n";
        cout << "3. Display all existing users\n";
        cout << "4. Display all existing connections\n";
        cout << "5. Remove Connections\n";
        cout << "6. Return to home page\n";
        cout << "Enter your choice: ";
        cout << yellow;
        cin >> ch;
        cout << cyan;
        cout << "\n";
        switch (ch)
        {
        case 1:
            U[usercount].getdata();
            usercount++;
            cout << green_bold;
            cout << "\nUser Details Entered Successully!\n\n";
            break;

        case 2:
            FormConnections();
            break;
        case 3:
            cout << yellow;
            cout << "\nPrinting all existing users: \n\n";
            for (int i = 0; i < usercount; i++)
            {
                cout << white;
                U[i].showdata();
                cout << endl;
            }
            break;
        case 4:
            cout << yellow;
            cout << "Displaying all existing connections: \n";
            G.PrintAdjList();
            break;
        case 5:
            G.RemoveConnections();
            break;
        case 6:
            flag = 1;
            cout << green;
            cout << "Returning to home page.";
            cout.flush();
            sleep(1);
            cout << ".";
            cout.flush();
            sleep(1);
            cout << ".";
            cout.flush();
            sleep(1);
            cout << ".\n\n";
            system("clear");
            return;
        default:
            cout << "Enter valid choice: ";
        }
    }
}

void Connection::user()
{
    string username;
    int ch, ref;
    pair<string, int> p = Login();
    username = p.first;
    ref = p.second;
    if (username != "0")
    {
        while (true)
        {
            cout << cyan;
            cout << "\n1. Show primary, secondary and tertiary connections";
            cout << "\n2. Add connections";
            cout << "\n3. Search for a user";
            cout << "\n4. Show personal info";
            cout << "\n5. Remove connections";
            cout << "\n6. Return to home page";
            cout << "\nEnter your choice: ";
            cout << yellow;
            cin >> ch;
            cout << cyan;
            cout << "\n";
            switch (ch)
            {
            case 1:
                DisplayConnections(username);
                break;
            case 2:
                AddConnections(username);
                break;
            case 3:
                SearchUserDetails(username);
                break;
            case 4:
                cout << white;
                U[ref].showdata();
                cout << cyan;
                break;
            case 5:
                G.RemoveConnections(username);
                break;
            case 6:
                cout << green;
                cout << "Returning to home page.";
                cout.flush();
                sleep(1);
                cout << ".";
                cout.flush();
                sleep(1);
                cout << ".";
                cout.flush();
                sleep(1);
                cout << ".\n\n";
                system("clear");
                return;
            default:
                cout << red_bold;
                cout << "Wrong choice! Try again\n";
                break;
            }
        }
    }
    else
    {
        cout << "Going back to the home page.";
        cout.flush();
        sleep(1);
        cout << ".";
        cout.flush();
        sleep(1);
        cout << ".";
        cout.flush();
        sleep(1);
        cout << ".";
        cout.flush();
        sleep(1);
        cout << ".\n\n";
        return;
    }
}

void User::getdata()
{
    cout << cyan;
    cout << "Enter Name: ";
    cout << yellow;
    cin >> name;
    cout << cyan;
    cout << "Enter College: ";
    cout << yellow;
    cin >> college;
    while (true)
    {
        cout << cyan;
        cout << "Enter Mobile No.: ";
        cout << yellow;
        cin >> mobile;
        cout << cyan;
        if (mobile.length() != 10)
        {
            cout << red_bold << "\nInvalid Mobile No.!\n\n";
        }
        else
            break;
    }
    while (true)
    {
        int flag = 1;
        cout << cyan;
        cout << "Enter Username: ";
        cout << yellow;
        cin >> username;
        for (int i = 0; i < usercount; i++)
        {
            if (U[i].getusername() == username)
            {
                cout << red_bold << "\nUsername already exists!\n\n";
                flag = 0;
            }
        }
        if (flag == 1)
        {
            break;
        }
    }
    cout << cyan;
    cout << "Enter Password: ";
    cout << yellow;
    cin >> password;
    ref_no = usercount;
}

void User::showdata()
{

    cout << "Name: " << name << endl;
    cout << "College: " << college << endl;
    cout << "Mobile No.: " << mobile << endl;
}

void Graph::addEdge(string X, string Y)
{
    if (GM.find(X) != GM.end())
    {
        GM[X].push_back(Y);
    }
    else
    {
        GM.insert({X, {Y}});
    }
    concount++;
}

void Graph::checkUsername2(string src, unordered_map<string, int> &visited, unordered_set<string> &s)
{
    queue<string> q;
    q.push(src);
    visited[src] = 1;
    int found = -1;
    while (!q.empty())
    {
        string node = q.front();
        q.pop();
        s.insert(node);
        for (auto neighbour : GM[node])
        {
            if (!visited[neighbour])
            {
                q.push(neighbour);
                visited[neighbour] = 1;
            }
        }
    }
}
int Graph::checkUsername(string src)
{
    unordered_map<string, int> visited;
    unordered_set<string> s;

    for (int i = 0; i < usercount; i++)
    {
        visited[U[i].getusername()] = 0;
    }

    for (int u = 0; u < usercount; u++)
    {
        if (visited[U[u].getusername()] == 0)
        {
            checkUsername2(U[u].getusername(), visited, s);
        }
    }
    if (s.find(src) != s.end())
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

pair<string, int> Login()
{
    string uname;
    string pass;
    int flag = -1;
    int ref;
    cout << yellow_bold;
    system("clear");
    cout << "\n\n**************************** ENTERED USER MODE ********************************\n";
    cout << cyan;
    cout << "\nEnter Username: ";
    cout << yellow;
    cin >> uname;
    for (int i = 0; i < usercount; i++)
    {
        if (U[i].getusername() == uname)
        {
            flag = 0;
            ref = U[i].getref();
            break;
        }
    }

    pair<string, int> det = make_pair(uname, ref);
    if (flag != -1)
    {
        cout << cyan;
        cout << "Enter Password: ";
        cout << yellow;
        cin >> pass;
        if (U[ref].getpassword() == pass)
        {
            return det;
        }
        else
        {
            cout << red_bold;
            cout << "\nWrong password!\n";
        }
    }
    else
    {
        cout << red_bold;
        cout << "\nUser not found!\n";
    }
    return make_pair("0", 0);
}

void Graph::PrintAdjList()
{
    for (auto p : GM)
    {
        string name1 = p.first;
        vector<string> name2 = p.second;
        cout << white;
        cout << name1;
        cout << red_bold;
        cout << " -> ";
        for (auto n2 : name2)
        {
            cout << white;
            cout << n2 << "  ";
        }
        cout << endl;
    }
}

int Graph::checkExists(string uname1, string uname2)
{
    for (auto p : GM)
    {
        string name1 = p.first;

        if (name1 == uname1)
        {
            vector<string> name2 = p.second;
            if (find(name2.begin(), name2.end(), uname2) != name2.end())
                return -1;
        }
    }
    return 1;
}

void FormConnections()
{
    string uname1, uname2;
    int flag = 1;
    cout << cyan;
    cout << "Enter the two usernames: ";
    cout << yellow;
    cin >> uname1 >> uname2;
    cout << endl;
    if (G.checkUsername(uname1) == -1)
    {
        cout << red_bold;
        cout << uname1 << " does not exist in the database!\n";
        flag = 0;
    }
    if (G.checkUsername(uname2) == -1)
    {
        cout << red_bold;
        cout << uname2 << " does not exist in the database!\n\n";
        flag = 0;
    }
    if (flag == 1)
    {
        if (G.checkExists(uname1, uname2) == -1)
        {
            cout << red_bold;
            cout << "Connection already exists!\n\n";
        }
        else
        {
            cout << green_bold;
            G.addEdge(uname1, uname2);
            cout << "Connection successfully established!\n\n";
        }
    }
}

void DisplayConnections(string uname)
{
    int f1 = 0, f2 = 0, f3 = 0;
    vector<int> P, S, T;
    for (int i = 0; i < usercount; i++)
    {
        int pathlength;
        if (U[i].getusername() != uname)
        {
            pathlength = G.ShortestDistance(uname, U[i].getusername());
            switch (pathlength)
            {
            case 1:
                P.push_back(i);
                break;
            case 2:
                S.push_back(i);
                break;
            case 3:
                T.push_back(i);
                break;
            }
        }
    }
    cout << white;
    cout << "\nPrimary Connections: ";
    for (auto i : P)
    {
        cout << U[i].getusername() << " ";
        f1 = 1;
    }
    if (f1 == 0)
    {
        cout << "None! You don't follow anyone";
    }
    if (f1 != 0)
    {
        cout << "\nSecondary Connections: ";
        for (auto i : S)
        {
            cout << U[i].getusername() << " ";
            f2 = 1;
        }
        if (f2 == 0)
        {
            cout << "None! You don't have any secondary connections\n\n";
        }
    }
    if (f2 != 0)
    {
        cout << "\nTertiary Connections: ";

        for (auto i : T)
        {
            f3 = 1;
            cout << U[i].getusername() << " ";
        }
        if (f3 == 0)
        {
            cout << "None! You have small circle of friends\n\n";
        }
    }
    cout << endl;
}

void AddConnections(string uname1)
{
    string uname2;
    cout << "Enter Username to Add Connection to: ";
    cout << yellow;
    cin >> uname2;
    int found = G.checkUsername(uname2);
    if (found != -1)
    {
        if (G.checkExists(uname1, uname2) == -1)
        {
            cout << red_bold;
            cout << "Connection already exists!\n\n";
        }
        else
        {
            G.addEdge(uname1, uname2);
            cout << green_bold;
            cout << "Connection established successfully!\n\n";
        }
    }
    else
    {
        cout << red_bold;
        cout << "User doesn't exist!\n";
    }
}

void AddConnections(string uname1, string uname2)
{
    if (G.checkExists(uname1, uname2) == -1)
    {
        cout << red_bold;
        cout << "Connection already exists!\n\n";
    }
    else
    {
        G.addEdge(uname1, uname2);
        cout << green;
        cout << "\nConnection added successfully\n";
    }
}

void SearchUserDetails(string uname1)
{
    string uname2;
    char addcon;
    cout << cyan;
    cout << "Enter Username: ";
    cout << yellow;
    cin >> uname2;
    int refno = G.checkUsername(uname2);
    if (refno != -1)
    {
        for (int i = 0; i < usercount; i++)
        {
            if (U[i].getusername() == uname2)
            {
                cout << "\033[;37m";
                refno = U[i].getref();
                cout << "\n";
            }
        }
        U[refno].showdata();
        int pathLength = G.ShortestDistance(uname1, uname2);
        switch (pathLength)
        {
        case 1:
            cout << white << "This user is a Primary connection\n";
            break;
        case 2:
            cout << white << "This user is a Secondary connection\n";
            break;
        case 3:
            cout << white << "This user is a Tertiary connection\n";
            break;
        default:
            cout << white << "This user is Out of your network\n";
            break;
        }
        cout << cyan;
        if (pathLength != 1)
        {
            cout << "\nDo you want to add connection? Enter Y if yes, N if no: ";
            cout << yellow;
            cin >> addcon;
            if (addcon == 'Y' || addcon == 'y')
            {
                AddConnections(uname1, uname2);
                cout << cyan;
            }
        }
    }
    else
    {
        cout << red_bold;
        cout << "User doesn't exist!\n";
    }
}

int Graph::ShortestDistance(string source, string dest)
{
    unordered_map<string, int> dist;
    unordered_map<string, string> path;
    queue<string> q;
    q.push(source);

    for (int i = 0; i < usercount; i++)
    {
        dist.insert({U[i].getusername(), -1});
        path.insert({U[i].getusername(), ""});
    }
    dist[source] = 0;
    path[source] = source;

    while (!q.empty())
    {
        int size = q.size();
        while ((size--) > 0)
        {
            string vertex = q.front();
            q.pop();
            vector<string> adjVertices = GM[vertex];
            for (auto adjVertex : adjVertices)
            {
                if (dist[adjVertex] == -1)
                {
                    dist[adjVertex] = dist[vertex] + 1;
                    path[adjVertex] = vertex;
                    q.push(adjVertex);
                }
            }
        }
    }
    return dist[dest];
}

void Graph::RemoveConnections()
{
    string uname1, uname2;
    int flag = 1;
    cout << cyan;
    cout << "Enter the two usernames: ";
    cout << yellow;
    cin >> uname1 >> uname2;
    cout << endl;
    if (G.checkExists(uname1, uname2) != -1)
    {
        cout << red_bold;
        cout << "Connection does not exist!\n";
    }
    else
    {
        vector<string> p = GM[uname1];
        p.erase(find(p.begin(), p.end(), uname2));
        GM[uname1] = p;
        cout << green;
        cout << "Connection removed successfully!\n";
    }
}

void Graph::RemoveConnections(string uname1)
{
    string uname2;
    cout << "Enter the username: ";
    cout << yellow;
    cin >> uname2;
    if (G.checkExists(uname1, uname2) != -1)
    {
        cout << red_bold;
        cout << "Connection does not exist!\n";
    }
    else
    {
        vector<string> p = GM[uname1];
        p.erase(find(p.begin(), p.end(), uname2));
        GM[uname1] = p;
        cout << green;
        cout << "Connection removed successfully!\n";
    }
}