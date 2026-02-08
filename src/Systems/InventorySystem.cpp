#include "Systems/InventorySystem.hpp"
#include "Utils/Constants.hpp"
#include <iostream>

InventorySystem::InventorySystem()
    : maxSlots(10) {
    
    inventoryBounds = {10, (float)(SCREEN_HEIGHT - 200), 350, 190};
}

void InventorySystem::Update() {
    // Atualizar lógica se necessário
}

void InventorySystem::Render() {
    // Fundo do inventário
    DrawRectangleRec(inventoryBounds, COLOR_UI);
    DrawRectangleLinesEx(inventoryBounds, 2, COLOR_TEXT);
    
    // Título
    DrawText("INVENTARIO", inventoryBounds.x + 10, inventoryBounds.y + 10, 20, COLOR_TEXT);
    
    // Items
    int yOffset = 40;
    if (items.empty()) {
        DrawText("Vazio", inventoryBounds.x + 15, inventoryBounds.y + yOffset, 16, GRAY);
    } else {
        for (size_t i = 0; i < items.size() && i < 7; i++) {
            std::string itemText = items[i].name;
            if (items[i].quantity > 1) {
                itemText += " x" + std::to_string(items[i].quantity);
            }
            
            DrawText(itemText.c_str(), 
                    inventoryBounds.x + 15, 
                    inventoryBounds.y + yOffset, 
                    15, 
                    COLOR_TEXT);
            yOffset += 20;
        }
        
        // Se tiver mais itens
        if (items.size() > 7) {
            DrawText(("... +" + std::to_string(items.size() - 7) + " itens").c_str(),
                    inventoryBounds.x + 15,
                    inventoryBounds.y + yOffset,
                    14,
                    GRAY);
        }
    }
    
    // Contador
    std::string countText = std::to_string(items.size()) + "/" + std::to_string(maxSlots);
    DrawText(countText.c_str(), 
            inventoryBounds.x + inventoryBounds.width - 60,
            inventoryBounds.y + 10,
            18,
            COLOR_WARNING);
}

bool InventorySystem::AddItem(const std::string& itemName) {
    // Verificar se já existe
    for (auto& item : items) {
        if (item.name == itemName) {
            item.quantity++;
            std::cout << "[INVENTARIO] +" << itemName << " (x" << item.quantity << ")" << std::endl;
            return true;
        }
    }
    
    // Verificar se tem espaço
    if ((int)items.size() >= maxSlots) {
        std::cout << "[INVENTARIO] CHEIO! Nao foi possivel adicionar " << itemName << std::endl;
        return false;
    }
    
    // Adicionar novo item
    items.push_back({itemName, 1});
    std::cout << "[INVENTARIO] +" << itemName << std::endl;
    return true;
}

bool InventorySystem::RemoveItem(const std::string& itemName) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->name == itemName) {
            it->quantity--;
            
            if (it->quantity <= 0) {
                items.erase(it);
            }
            
            std::cout << "[INVENTARIO] -" << itemName << std::endl;
            return true;
        }
    }
    
    std::cout << "[INVENTARIO] Item nao encontrado: " << itemName << std::endl;
    return false;
}

bool InventorySystem::HasItem(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item.name == itemName) {
            return true;
        }
    }
    return false;
}

int InventorySystem::GetItemQuantity(const std::string& itemName) const {
    for (const auto& item : items) {
        if (item.name == itemName) {
            return item.quantity;
        }
    }
    return 0;
}

void InventorySystem::Clear() {
    items.clear();
    std::cout << "[INVENTARIO] Limpo!" << std::endl;
}

std::string InventorySystem::GetFirstItem() const {
    if (items.empty()) {
        return "";
    }
    return items[0].name;
}

bool InventorySystem::RemoveFirstItem() {
    if (items.empty()) {
        return false;
    }
    
    std::string firstName = items[0].name;
    return RemoveItem(firstName);
}