#include "ProgramFlow/ISerializable.hpp"

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
    UpgradeManager() = default;
    virtual ~UpgradeManager() = default;
    void Save(json &out) const override
    {
        out["upgrades"] = json::array();
        for (const auto &upgrade : upgrades)
        {
            json upgradeJson;
            upgradeJson["id"] = upgrade.id;
            upgradeJson["name"] = upgrade.name;
            upgradeJson["description"] = upgrade.description;
            upgradeJson["x"] = upgrade.x;
            upgradeJson["y"] = upgrade.y;
            upgradeJson["iconPath"] = upgrade.iconPath;
            upgradeJson["cost"] = upgrade.cost;
            upgradeJson["unlocked"] = upgrade.unlocked;
            upgradeJson["level"] = upgrade.level;
            out["upgrades"].push_back(upgradeJson);
        }
    }
    void Load(const json &in) override
    {
        upgrades.clear();
        for (const auto &upgradeJson : in["upgrades"])
        {
            Upgrade upgrade(
                upgradeJson.value("id", 0),
                upgradeJson.value("name", std::string()),
                upgradeJson.value("description", std::string()),
                upgradeJson.value("x", 0.0f),
                upgradeJson.value("y", 0.0f),
                upgradeJson.value("iconPath", std::string()),
                upgradeJson.value("cost", 0),
                upgradeJson.value("unlocked", false),
                upgradeJson.value("level", 0));
            upgrades.push_back(upgrade);
        }
    }
    void AddUpgrade(const Upgrade &upgrade)
    {
        upgrades.push_back(upgrade);
    }
    vector<Upgrade> GetUpgrades() const
    {
        return upgrades;
    }
};