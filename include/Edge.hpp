/**
 *
 * Implementation of a Edge in a Neural Net. An Edge stores the weight
 * of a relationship in the Neural Net, and updates the relationships
 * between nodes on construction.
 *
 * @author Alex Chu
 *
 */

#ifndef EDGE_H
#define EDGE_H

#define DEFAULT_WEIGHT (0)

class Node;

class Edge{
    public:
        friend class Node;

        /**
         *
         * Constructs a new Edge and updates the each involved
         * Node's list of incoming and outgoing edges to match
         * the updated state of the neural net.
         *
         */
        Edge(Node& source, Node& target);

        /**
         *
         * Gets the weight of an edge.
         *
         * @return the weight of the edge.
         *
         */
        float getWeight();

        /**
         *
         * Gets a reference to the source node of an edge.
         *
         * @return a reference to the source node of an edge.
         *
         */
        Node& getSource();

        /**
         *
         * Gets a reference to the target node of an edge.
         *
         * @return a reference to the target node of the edge.
         *
         */
        Node& getTarget();

    protected:
        Node* source;
        Node* target;
        float weight;
};
#endif
