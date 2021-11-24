#include <iostream>
#include <vector>

extern "C"
{
#include "lua542/include/lauxlib.h"
#include "lua542/include/lua.h"
#include "lua542/include/lualib.h"
}

/* Puedes escribir otras funciones auxiliares aquí */

int getNumberOfGroups(int nRows, int nColumns, int aisleSeat,
                      std::vector<std::pair<int, int> > positions, int groupSize)
{
  /*
   * Escribe tu código para la función principal aquí
   */
  lua_State *L = luaL_newstate();
  luaopen_base(L);
  luaL_requiref(L, "io", luaopen_io, 1);
  luaL_dofile(L, "solution.lua");
  lua_getglobal(L, "getNumberOfGroups");
  lua_pushinteger(L, nRows);
  lua_pushinteger(L, nColumns);
  lua_pushinteger(L, aisleSeat);
  lua_newtable(L);
  for (int i = 0; i < positions.size(); i++)
  {
    lua_pushinteger(L, i + 1);
    lua_newtable(L);
    lua_pushinteger(L, 1);
    lua_pushinteger(L, positions[i].first);
    lua_settable(L, -3);
    lua_pushinteger(L, 2);
    lua_pushinteger(L, positions[i].second);
    lua_settable(L, -3);
    lua_settable(L, -3);
  }
  lua_pushinteger(L, groupSize);
  lua_call(L, 5, 1);
  int result = lua_tonumber(L, -1);
  return result;
}

/* NO EDITAR MAIN */

int main()
{
  std::vector<int> problems;
  std::vector<int> solutions;
  std::vector<std::string> titles;

  /*
    1.1 Von Neumann
    ===============

    0 X || 0 0 0 0
    0 0 || 0 0 0 0
    0 0 || 0 0 X 0
    0 0 || 0 0 X 0
  */
  titles.push_back("1.1 Von Neumann");
  problems.push_back(getNumberOfGroups(4, 6, 2,
                                       {{1, 2}, {3, 5}, {4, 5}}, 3));
  solutions.push_back(2);

  /*
    1.2 Turing
    ==========

    0 X || 0 0 0 0
    0 0 || 0 0 0 0
    0 0 || 0 0 X 0
    0 0 || 0 X 0 0
  */
  titles.push_back("1.2 Turing");
  problems.push_back(getNumberOfGroups(4, 6, 2,
                                       {{1, 2}, {3, 5}, {4, 4}}, 4));
  solutions.push_back(3);

  /*
    1.3 Boole
    =========

    0 X 0 0 || 0 0
    0 0 X 0 || 0 X
    0 0 0 0 || 0 X
    0 0 X 0 || 0 0
  */
  titles.push_back("1.3 Boole");
  problems.push_back(getNumberOfGroups(4, 6, 4,
                                       {{1, 2}, {2, 3}, {2, 6}, {3, 6}, {4, 3}}, 2));
  solutions.push_back(7);

  /*
    2.1 Ada Byron
    =============

    0 0 0 X || 0 0 0 0
    X X 0 0 || 0 0 X 0
    0 0 0 0 || 0 0 0 0
    0 0 0 0 || 0 0 0 X
  */
  titles.push_back("2.1. Ada Byron");
  problems.push_back(getNumberOfGroups(4, 8, 4,
                                       {{1, 4}, {2, 1}, {2, 2}, {2, 7}, {4, 8}}, 4));
  solutions.push_back(5);

  /*
    2.4 Donald Knuth
    ================

    X 0 0 0 || 0 0 X 0
    0 0 0 X || 0 0 0 0
    0 X 0 0 || 0 0 0 0
    0 0 0 0 || 0 0 0 X
  */
  titles.push_back("2.4 Donald Knuth");
  problems.push_back(getNumberOfGroups(4, 8, 4,
                                       {{1, 1}, {1, 7}, {2, 4}, {3, 2}, {4, 8}}, 5));
  solutions.push_back(3);

  /*
    Carrel 1
    ========

    0 0 0 ||
  */
  titles.push_back("Carrel 1");
  problems.push_back(getNumberOfGroups(1, 3, 3, {}, 3));
  solutions.push_back(1);

  /*
    Carrel 2
    ========

    0 0 || 0
  */
  titles.push_back("Carrel 2");
  problems.push_back(getNumberOfGroups(1, 3, 2, {}, 3));
  solutions.push_back(0);

  /*
    Carrel 3
    ========

    || 0 0 0
  */
  titles.push_back("Carrel 3");
  problems.push_back(getNumberOfGroups(1, 3, 0, {}, 3));
  solutions.push_back(1);

  std::cout << "\n";
  for (size_t i = 0; i < problems.size(); i++)
  {
    bool right = problems[i] == solutions[i];
    std::cout << (right ? "✅" : "❌") << " Test " << i + 1 << " - "
              << titles[i] << ": " << (right ? "" : "NOT ") << "passed\n";
    if (!right)
    {
      std::cout << "The solution was " << solutions[i]
                << " and the output was " << problems[i] << "\n";
    }
    std::cout << "\n";
  }
  return 0;
}