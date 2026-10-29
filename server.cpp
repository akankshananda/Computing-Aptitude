#include <iostream>
#include <string>
#include <winsock2.h>
#include <sstream>
#include <cstdlib>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

class Student {
public:
    int id;
    string name;
    string department;
    int marks;
    Student* next;

    Student(int i, string n, string d, int m) {
        id = i;
        name = n;
        department = d;
        marks = m;
        next = NULL;
    }
};

Student* head = NULL;

string getValue(string data, string key) {
    size_t start = data.find(key + "=");

    if (start == string::npos) {
        return "";
    }

    start += key.length() + 1;

    size_t end = data.find("&", start);

    if (end == string::npos) {
        return data.substr(start);
    }

    return data.substr(start, end - start);
}

void addStudent(string data) {
    int id = stoi(getValue(data, "id"));
    string name = getValue(data, "name");
    string department = getValue(data, "department");
    int marks = stoi(getValue(data, "marks"));

    Student* newStudent = new Student(id, name, department, marks);

    if (head == NULL) {
        head = newStudent;
    } else {
        Student* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newStudent;
    }
}

string getStudents() {
    string result = "[";

    Student* temp = head;

    while (temp != NULL) {
        result += "{";
        result += "\"id\":" + to_string(temp->id) + ",";
        result += "\"name\":\"" + temp->name + "\",";
        result += "\"department\":\"" + temp->department + "\",";
        result += "\"marks\":" + to_string(temp->marks);
        result += "}";

        if (temp->next != NULL) {
            result += ",";
        }

        temp = temp->next;
    }

    result += "]";

    return result;
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(8080);

    bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    listen(serverSocket, 5);

    cout << "DataX C++ Backend Server running..." << endl;
    cout << "http://127.0.0.1:8080" << endl;

    while (true) {
        SOCKET clientSocket = accept(serverSocket, NULL, NULL);

        if (clientSocket == INVALID_SOCKET) {
            continue;
        }

        char request[4096] = {};
        int received = recv(clientSocket, request, sizeof(request) - 1, 0);

        if (received <= 0) {
            closesocket(clientSocket);
            continue;
        }

        string requestData(request);

        string body;

        if (requestData.find("POST /add") == 0) {
            size_t bodyStart = requestData.find("\r\n\r\n");

            if (bodyStart != string::npos) {
                string data = requestData.substr(bodyStart + 4);
                addStudent(data);
                body = "Student added successfully";
            } else {
                body = "Invalid request";
            }
        } else if (requestData.find("GET /students") == 0) {
            body = getStudents();
        } else {
            body = "DataX C++ Backend Connected Successfully!";
        }

        string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + to_string(body.length()) + "\r\n"
            "Access-Control-Allow-Origin: *\r\n"
            "Connection: close\r\n"
            "\r\n" +
            body;

        send(clientSocket, response.c_str(), response.length(), 0);

        closesocket(clientSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}