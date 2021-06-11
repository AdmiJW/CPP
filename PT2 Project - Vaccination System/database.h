#ifndef DATABASE_H
#define DATABASE_H

#include "./project.h"

#define MAX_USER_SIZE 10000
#define MAX_ADMIN_SIZE 100

//	File location. Should be relative
#define VACCINE_CENTER_FILELOC "data/vaccinecenter.txt"
#define USER_FILELOC "data/user.txt"
#define ADMIN_FILELOC "data/admin.txt"

//	Arrays of Objects
extern VaccineCenter vaccineCenterLists[13];
extern User userLists[MAX_USER_SIZE];
extern Admin adminLists[MAX_ADMIN_SIZE];
extern int user_size;
extern int admin_size;

//	Methods
bool saveVaccineCenter();
bool loadVaccineCenter();
VaccineCenter* getVaccineCenter(string);

bool saveUsers();
bool loadUsers();
User* getUser(string);
bool addUser(User&);

bool saveAdmins();
bool loadAdmins();
Admin* getAdmin(string);
bool addAdmin(Admin&);

#endif