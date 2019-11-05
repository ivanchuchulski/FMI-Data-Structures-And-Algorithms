#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    bool data;
    std::vector<Node*> connectedWith;

    Node (int data) : data(data) {

    }
};

int calculateService(Node* root, int currCoffee, int maxCoffee) {

    if (root->data == 0) {
        currCoffee = 0;
    }
    if (root->data == 1) {
        ++currCoffee;
    }
    if (currCoffee > maxCoffee) {
        return 0;
    }
    if (root->connectedWith.size() == 0) {
        return 1;
    }

    int counterServices = 0;

    while (root->connectedWith.size() != 0) { //Tuk na vseki vuzel mu minavam ostanalite elementi
        Node* newRoot = root->connectedWith[0];

        int counter = 0;

        while (root != root->connectedWith[0]->connectedWith[counter]) {
            ++counter;
        }

        root->connectedWith[0]->connectedWith.erase(root->connectedWith[0]->connectedWith.begin() + counter); // Premahvam vruzkata i ot dvata vuzela, za da ne se vurne obratno
        root->connectedWith.erase(root->connectedWith.begin());                                               //
        counterServices += calculateService(newRoot, currCoffee, maxCoffee);
    }

    return counterServices;
}

int main() {

    int requests, maxCoffee;
    std::cin >> requests >> maxCoffee;

    std::vector<Node*> nodes;

    bool data;

    for (int i = 0; i < requests; ++i) {

        std::cin >> data;
        nodes.push_back(new Node(data));
    }

    int first, second;

    for (int i = 0; i < requests - 1; ++i) {
        std::cin >> first >> second;

        if (first > 0 && second > 0 && first <= nodes.size() && second <= nodes.size()) {

            nodes[first - 1]->connectedWith.push_back(nodes[second - 1]); // Dobavqm vruzkata i v dvata vuzela, i dvata da znaqt che sa svuzani edin s drug
            nodes[second - 1]->connectedWith.push_back(nodes[first - 1]); //
        }
    }

    std::cout << calculateService(nodes[0], 0, maxCoffee);

    return 0;
}
