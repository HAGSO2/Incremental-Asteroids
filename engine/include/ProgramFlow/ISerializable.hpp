#pragma once

// Libraries required for serialization:
// - nlohmann/json.hpp: provides the JSON type used to represent
//   the data being saved and retrieved.
// - iostream and fstream: input/output utilities, presumably
//   used for file read and write operations.
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

// Define "json" as an alias for the nlohmann type to simplify its use
// in the method declarations of this interface.
using json = nlohmann::json;

// Interface for objects that can be serialized.
// A class that inherits from ISerializable must define how to convert
// its internal state to JSON and how to restore it from JSON.
//
// Furthermore, each serializable object is associated with a filename,
// which is used during save and load operations.

class ISerializable
{
    // Name or path of the file associated with the object.
    // It is kept private so that derived classes cannot modify it
    // directly; the interface uses it for its file operations.
    std::string filename;

public:
    // Construct a serializable object and store the file that will be used
    // to save and load its data.
    ISerializable(std::string fn) : filename(fn) {};

    ~ISerializable() = default;

    // Converts the state of the derived object into JSON information.
    // The class implementing the interface must write the data it wishes to persist to "out".
    // It is marked as const because saving should not modify the object's state.
    virtual void Save(json &out) const = 0;
    // Restores the state of the derived object based on the JSON information
    // received in "in". Each class decides which fields it needs to recover.
    virtual void Load(const json &in) = 0;

    // File-level persistence operations.
    // As their names suggest, DumpToFile() writes the JSON representation of the object
    // to the associated file, while LoadFromFile() reads it and restores the object.
    void DumpToFile() const;
    void LoadFromFile();
};

    // Example implementation in a derived class:
    //
    // These attributes represent the state that the class wants to save.
    // int health = 100;
    // float speed = 5.5f;
    // std::string name = "Player1";
    // std::vector<int> inventoryIds;
    //
    // Save() copies the object's attributes to the corresponding keys
    // in the JSON document.
    //
    // void Save(json& out) const override {
    //     out["health"] = health;
    //     out["speed"] = speed;
    //     out["name"] = name;
    //     out["inventoryIds"] = inventoryIds;
    // }
    //
    // Load() reads those keys and assigns the values ​​to the attributes.
    // value(key, defaultValue) allows for an alternative value to be used
    // when the key is not present in the JSON.
    //
    // void Load(const json& in) override {
    //     health = in.value("health", 100);
    //     speed = in.value("speed", 0.0f);
    //     name = in.value("name", std::string());
    //     inventoryIds = in.value("inventoryIds", std::vector<int>{});
    // }
