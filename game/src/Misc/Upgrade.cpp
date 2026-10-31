#include "Misc/Upgrade.h"

void UpgradeManager::Save(json &out) const
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
void UpgradeManager::Load(const json &in)
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
