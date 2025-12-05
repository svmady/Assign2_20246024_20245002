#include "User.h"

using namespace std;

int User::totalUsers = 0;

User::User() : userId(""), name(""), phoneNumber("") {
	totalUsers++;
}

User::User(const string& id, const string& n, const string& phone)
	: userId(id), name(n), phoneNumber(phone) {
	totalUsers++;
}

int User::getTotalUsers() {
	return totalUsers;
}

User::~User() {
	totalUsers--;
}