#pragma once

#include "Framework/BaseLevel.h"

struct Node
{
    sf::Vector2i pos;  // node position
    int totalCost;      //Hueristic + Cost
    int cost;           //Neighbor ChainCost
    int hueristic;      // the hueristic cost
private:
    Node* parent;        // ptr that points to the parent node

public:
    std::vector<Node*> neighbors;

    void setParent(Node* n) {
        if (n == this) {
            // Avoid setting the parent to itself
            std::cout << "Attempted to set parent to itself." << std::endl;
            return;
        }
        else {
            parent = n;
        }
    }

      Node* GetParent(){
          return parent;
      }

      Node() : pos(0, 0), totalCost(0), cost(0), hueristic(0), parent(nullptr) {}
      Node(sf::Vector2i Cpos, int Ctotalcost,int Ccost,int Chueristtic,Node* Cparent) {
          pos = Cpos;
          totalCost = Ctotalcost;
          cost = Ccost;
          hueristic = Chueristtic;
          setParent(Cparent);

      }
    bool operator==(const Node& other) const {
        return pos == other.pos;
    }
    bool operator<=(const Node& other) const {
        return totalCost <= other.totalCost;
    }
};
