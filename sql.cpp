#include "sql.h"

SQL::SQL(std::string databaseName) {
  int rc = sqlite3_open(databaseName.c_str(), &db);
  if (rc) {
    throw "Failed to open database.";
  }
}

/////////////////////////////////////////////////
/// @param name Username of the new user
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::addUser(std::string name) {
  std::string sql = "INSERT INTO " + std::string(USERS_TABLE) + " (username) VALUES ('" + name + "');";
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param userId User ID of the user to drop from the database
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::deleteUser(int userId) {
  std::string sql = "DELETE FROM " + std::string(USERS_TABLE) + " WHERE id='" + std::to_string(userId) + "';";
  std::cout << sql << '\n';
  return sqlite3_exec(db, (char *) sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param name Username of the user to find
/// @return `int` Returns the first instance of the
/// user id in the database
/////////////////////////////////////////////////
int SQL::getUser(std::string name) {
  std::string sql = "SELECT id FROM " + std::string(USERS_TABLE) + " WHERE username='" + name + "';";
  char **result;
  int rowCount;
  int colCount;
  sqlite3_get_table(db, (char *) sql.c_str(), &result, &rowCount, &colCount, &error);
  return atoi(result[1]);
}

/////////////////////////////////////////////////
/// @param id Id of the user to find
/// @return `char *` Returns a char array containing
/// the username of the corresponding user id
/////////////////////////////////////////////////
char* SQL::getUser(int id) {
  std::string sql = "SELECT username FROM " + std::string(USERS_TABLE) + " WHERE id='" + std::to_string(id) + "';";
  char **result;
  int rowCount;
  int colCount;
  sqlite3_get_table(db, (char *) sql.c_str(), &result, &rowCount, &colCount, &error);
  return result[1];
}

/////////////////////////////////////////////////
/// @param userId Id of the user to add the role
/// @param roleId Role to be added to the user
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::addRoleToUser(int userId, int roleId) {
  std::string sql = "INSERT INTO " + std::string(ASSIGNED_ROLES_TABLE) + " (user_id, role_id) VALUES ('" + std::to_string(userId) + "', '" + std::to_string(roleId) + "')";
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param userId Id of the user to remove the role
/// @param roleId Role to be removed from the user
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::removeRoleFromUser(int userId, int roleId) {
  std::string sql = "DELETE FROM " + std::string(ASSIGNED_ROLES_TABLE) + " WHERE user_id='" + std::to_string(userId) + "' AND role_id='" + std::to_string(roleId) + "';";
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param name Name of the new role to be created
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::createRole(std::string name) {
  std::string sql = "INSERT INTO " + std::string(ROLES_TABLE) + " (name) VALUES('" + name + "');";
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param name roleId Id of the role to be deleted
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::deleteRole(int roleId) {
  std::cout << roleId << '\n';
  std::string sql = "DELETE FROM " + std::string(ROLES_TABLE) + " WHERE id='" + std::to_string(roleId) + "';";
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param name Name of the new role to be returned
/// @return `int` Returns the Roles ID
/////////////////////////////////////////////////
int SQL::getRole(std::string name) {
  std::string sql = "SELECT id FROM " + std::string(ROLES_TABLE) + " WHERE name='" + name + "';";
  char **result;
  int rowCount;
  int colCount;
  sqlite3_get_table(db, (char *) sql.c_str(), &result, &rowCount, &colCount, &error);
  return atoi(result[1]);
}

/////////////////////////////////////////////////
/// @param id Id of role to be returned
/// @return `char *` Char array containing the roles name
/////////////////////////////////////////////////
char* SQL::getRole(int id) {
  std::string sql = "SELECT name FROM " + std::string(ROLES_TABLE) + " WHERE id='" + std::to_string(id) + "';";
  char **result;
  int rowCount;
  int colCount;
  sqlite3_get_table(db, (char *) sql.c_str(), &result, &rowCount, &colCount, &error);
  return result[1];
}

/////////////////////////////////////////////////
/// @param roleId Id of the role to be assigned permissions
/// @param permissionId Permission to be added to the role
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::addPermisionToRole(int roleId, int permissionId) {
  std::string sql = "INSERT INTO " + std::string(ASSIGNED_PERMISSIONS_TABLE) + " (role_id, permissions_id) VALUES('" + std::to_string(roleId) + "','" + std::to_string(permissionId) + "');";
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param roleId Id of the role to have permissions removed
/// @param permissionId Permission to be removed from the role
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::removePermisionFromRole(int roleId, int permissionId) {
  std::string sql = "DELETE FROM " + std::string(ASSIGNED_PERMISSIONS_TABLE) + " WHERE role_id='" + std::to_string(roleId) + "' AND permissions_id='" + std::to_string(permissionId) + "';";
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param name Name of the new permission to be created
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::createPermission(std::string name) {
  std::string sql = "INSERT INTO " + std::string(PERMISSIONS_TABLE) + " (name) VALUES('" + name + "');";
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param id Id of the permission to be deleted
/// @return `bool` Returns true on failure and false on success
/////////////////////////////////////////////////
bool SQL::deletePermission(int id) {
  std::string sql = "DELETE FROM " + std::string(PERMISSIONS_TABLE) + " WHERE id='" + std::to_string(id) + "';";;
  return sqlite3_exec(db, sql.c_str(), callback, 0, &error);
}

/////////////////////////////////////////////////
/// @param name Name of the permission to be Returned
/// @return `int` Id of the permission
/////////////////////////////////////////////////
int SQL::getPermission(std::string name) {
  std::string sql = "SELECT id FROM " + std::string(PERMISSIONS_TABLE) + " WHERE name='" + name + "';";
  char **result;
  int rowCount;
  int colCount;
  sqlite3_get_table(db, (char *) sql.c_str(), &result, &rowCount, &colCount, &error);
  return atoi(result[1]);
}

/////////////////////////////////////////////////
/// @param id Id of the permission to be Returned
/// @return `char *` char array containing the name of the permission
/////////////////////////////////////////////////
char* SQL::getPermission(int id) {
  std::string sql = "SELECT name FROM " + std::string(PERMISSIONS_TABLE) + " WHERE id='" + std::to_string(id) + "';";;
  char **result;
  int rowCount;
  int colCount;
  sqlite3_get_table(db, (char *) sql.c_str(), &result, &rowCount, &colCount, &error);
  return result[1];
}

SQL::~SQL() {
  sqlite3_close(db);
}
