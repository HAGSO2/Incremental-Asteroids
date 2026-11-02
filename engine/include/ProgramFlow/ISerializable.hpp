#pragma once

#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
using json = nlohmann::json;

// Interface for serializable objects

// Any Serializable object must have a file in wich is saved and loaded.

class ISerializable
{
    // The filename to save/load the object
    std::string filename;

public:
    ISerializable(std::string fn) : filename(fn) {};
    virtual ~ISerializable() = default;
    virtual void Save(json &out) const = 0;
    virtual void Load(const json &in) = 0;

    // Example

    // int health = 100;
    // float speed = 5.5f;
    // std::string name = "Jugador1";
    // std::vector<int> inventoryIds;

    // void Save(json& out) const override {
    //     out["health"] = health;
    //     out["speed"] = speed;
    //     out["name"] = name;
    //     out["inventoryIds"] = inventoryIds;
    // }

    // void Load(const json& in) override {
    //     health = in.value("health", 100);
    //     speed = in.value("speed", 0.0f);
    //     name = in.value("name", std::string());
    //     inventoryIds = in.value("inventoryIds", std::vector<int>{});
    // }

    void DumpToFile() const;
    void LoadFromFile();
};