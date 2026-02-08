#ifndef INVENTORYSYSTEM_HPP
#define INVENTORYSYSTEM_HPP

#include "raylib.h"
#include <vector>
#include <string>

struct InventoryItem {
    std::string name;
    int quantity;
};

class InventorySystem {
private:
    std::vector<InventoryItem> items;
    int maxSlots;
    
    Rectangle inventoryBounds;

public:
    InventorySystem();
    
    void Render();
    void Update();
    
    // Gerenciamento
    bool AddItem(const std::string& itemName);
    bool RemoveItem(const std::string& itemName);
    bool HasItem(const std::string& itemName) const;
    int GetItemQuantity(const std::string& itemName) const;
    void Clear();
    
    // Despejar (primeiro item)
    std::string GetFirstItem() const;
    bool RemoveFirstItem();
    bool IsEmpty() const { return items.empty(); }
    int GetItemCount() const { return items.size(); }
    
    // Getters
    std::vector<InventoryItem> GetAllItems() const { return items; }
};

#endif // INVENTORYSYSTEM_HPP