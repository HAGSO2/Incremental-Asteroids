#include "ProgramFlow/ISerializable.hpp"

void ISerializable::DumpToFile() const
{
  std::ofstream file(filename);
  if (file.is_open())
  {
    json out;
    Save(out);
    file << out.dump(4); // Pretty print with 4 spaces indentation
    file.close();
    return;
  }
  std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
}

void ISerializable::LoadFromFile()
{
  std::ifstream file(filename);
  if (file.is_open())
  {
    json in;
    file >> in;
    Load(in);
    file.close();
    return;
  }
  std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
}