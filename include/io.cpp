#include "io.hpp"


string fichier_vers_string(const string& chemin)
{
  auto ss = ostringstream{};
  ifstream input_file(chemin);
  if (!input_file.is_open()) {
    cerr << "impossible ouvrir le fichier - '" << chemin << "'" << endl;
    exit(1);
  }
  ss << input_file.rdbuf();
  return ss.str();
}