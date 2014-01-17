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
        friend class NeuralGrid;

        /**
         *
         * Constructs a new Edge and updates the each involved
         * Node's list of incoming and outgoing edges to match
         * the updated state of the neural net.
         *
         * @param source the source node of the edge
         * @param target the target node of the edge
         *
         */
        Edge(Node& source, Node& target);

        /**
         *
         * Constructs a new Edge and updates the each involved
         * Node's list of incoming and outgoing edges to match
         * the updated state of the neural net.
         *
         * @param source the source node of the edge
         * @param target the target node of the edge
         * @param weight the weight of the resulting edge
         *
         */
        Edge(Node& source, Node& target, double weight);

        /**
         *
         * Destructor for Edges. Removes the edge from the 
         * source and target nodes' lists.
         *
         */
        ~Edge();

        /**
         *
         * Gets the weight of an edge.
         *
         * @return the weight of the edge.
         *
         */
        double getWeight();

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
        double weight;
};
#endif
