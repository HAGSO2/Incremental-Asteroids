#include "ProgramFlow/ISerializable.hpp"

#pragma once

using namespace std;

struct Upgrade
{
    int id;
    string name;
    string description;
    float x;
    float y;
    string iconPath;
    int cost;
    bool unlocked;
    int level;

    Upgrade(int id, std::string name, std::string description, const float x, const float y, std::string iconPath, int cost, bool unlocked, int level) : id(id), name(name), description(description), x(x), y(y), iconPath(iconPath), cost(cost), unlocked(unlocked), level(level) {};
    json ToJson() const
    {
        json upgradeJson;
        upgradeJson["id"] = id;
        upgradeJson["name"] = name;
        upgradeJson["description"] = description;
        upgradeJson["x"] = x;
        upgradeJson["y"] = y;
        upgradeJson["iconPath"] = iconPath;
        upgradeJson["cost"] = cost;
        upgradeJson["unlocked"] = unlocked;
        upgradeJson["level"] = level;
        return upgradeJson;
    }
};

class UpgradeManager : public ISerializable
{
    vector<Upgrade> upgrades;

public:
    UpgradeManager(std::string filename) : ISerializable(filename) {};
    virtual ~UpgradeManager() = default;
    void Save(json &out) const override;
    void Load(const json &in) override;
    void AddUpgrade(const Upgrade &upgrade)
    {
        upgrades.push_back(upgrade);
    }
    vector<Upgrade> GetUpgrades() const
    {
        return upgrades;
    }
};