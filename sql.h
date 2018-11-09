/////////////////////////////////////////////////
/// @mainpage Welcome to the RBAC SQLite3 C++ Interface Library
/// @description The purpose of this library is to
/// provide and easy to use, object oriented interface to manipulate SQLite3
/// in reference to RBAC Computer Security assignement from Florida Polytechnic University
/// @author Derick Vigne
/////////////////////////////////////////////////

#ifndef __sqlh__
#define __sqlh__

//SQLite Defines
#define ASSIGNED_PERMISSIONS_TABLE "assigned_permissions"
#define PERMISSIONS_TABLE "permissions"
#define USERS_TABLE "users"
#define ASSIGNED_ROLES_TABLE "assigned_roles"
#define ROLES_TABLE "roles"
#define tostr(str) #str
#define DEBUG

#include "sqlite3.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdio.h>

/////////////////////////////////////////////////
/// SQL Object
/// @author Derick Vigne
/// @copyright MIT License
/////////////////////////////////////////////////

class SQL {
private:
  sqlite3* db;
  char* error;
  static int id;

  static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    #ifdef DEBUG
      std::ofstream logFile;
      logFile.open("sql.log");
      for(int i = 0; i < argc; i++) {
        logFile << azColName[i] << " = " << argv[i] ? argv[i] : "NULL";
        // printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      }
      logFile << std::endl;
    #endif
    return 0;
  }

/////////////////////////////////////////////////
/// @fn SQL::SQL(char* databaseName)
/// @brief Constructor
///
/// Creates the database connection handle
/// @param databaseName Name of the SQLite3 database
/// if the database file doesn't exist a new one will be created
/// @return `void`
/////////////////////////////////////////////////A
public:
  SQL (std::string databaseName); ///< Constructor
  bool addUser(std::string name); ///< Creates a user
  bool deleteUser(int userId); ///< Deletes a user
  int getUser(std::string name); ///< Returns a user
  char* getUser(int id); ///< Returns a user
  bool addRoleToUser(int userId, int roleId); ///< Adds a role to an user
  bool removeRoleFromUser(int userId, int roleId); ///< Removes a role from a user
  bool createRole(std::string name); ///< Crates a new role
  bool deleteRole(int id); ///< Drops a role from the database
  int getRole(std::string name); ///< "Returns a role"
  char* getRole(int id); ///< Returns a role
  bool addPermisionToRole(int roleId, int permissionId); ///< Assign permissions to a role
  bool removePermisionFromRole(int roleId, int permissionId); ///< Remove permissions from a role
  bool createPermission(std::string name); ///< Create a new permission
  bool deletePermission(int id); ///< Delete a permission
  int getPermission(std::string name); ///< Returns a permission
  char* getPermission(int id); ///< Returns a permission
  char* getError() {return error;} ///< Get error message
  ~SQL ();
};
/////////////////////////////////////////////////
/// @fn SQL::~SQL()
/// @brief Destructor
///
/// Deallocates the database connection handle and memeory used
/// for query response data
/// @return `void`
/////////////////////////////////////////////////A

#endif
