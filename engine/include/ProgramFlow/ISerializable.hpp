#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
using json = nlohmann::json;

// Apply this to any scene

class ISerializable
{
public:
    virtual ~ISerializable() = default;
    virtual void Save(json &out) const = 0;
    virtual void Load(const json &in) = 0;

    // Example

    // int vida = 100;
    // float velocidad = 5.5f;
    // std::string nombre = "Jugador1";
    // std::vector<int> inventarioIDs;

    // void Save(json& out) const override {
    //     out["vida"] = vida;
    //     out["velocidad"] = velocidad;
    //     out["nombre"] = nombre;
    //     out["inventarioIDs"] = inventarioIDs;
    // }

    // void Load(const json& in) override {
    //     vida = in.value("vida", 100);
    //     velocidad = in.value("velocidad", 0.0f);
    //     nombre = in.value("nombre", std::string());
    //     inventarioIDs = in.value("inventarioIDs", std::vector<int>{});
    // }

    void DumpToFile(const std::string &filename) const
    {
        json out;
        Save(out);
        std::ofstream file(filename);
        if (file.is_open())
        {
            file << out.dump(4); // Pretty print with 4 spaces indentation
            file.close();
        }
        else
        {
            std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        }
    }
    void LoadFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            json in;
            file >> in;
            Load(in);
            file.close();
        }
        else
        {
            std::cerr << "Error: Could not open file " << filename << " for reading." << std::endl;
        }
    }
};