#pragma once

#include <nlohmann/json.hpp>
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
};