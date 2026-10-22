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
    
    Upgrade(int id, std::string name, std::string description, const float x, const float y, std::string iconPath, int cost, bool unlocked) : id(id), name(name), description(description), x(x), y(y), iconPath(iconPath), cost(cost), unlocked(unlocked) {};
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
            out["upgrades"].push_back(upgradeJson);
        }
    }
    virtual void Load(const json &in) override
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
                upgradeJson.value("unlocked", false));
            upgrades.push_back(upgrade);
        }
    }
};