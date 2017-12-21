#include <vector>
#include <unordered_set>
#include <iostream>
#include <memory>
#include <queue>

struct Vertex { 
    int val;
    std::vector<std::shared_ptr<Vertex> > neighbors;
    
    Vertex(int v): val(v){}
    void add_edge(std::shared_ptr<Vertex> &v) { 
        if (v !=nullptr) {
            neighbors.push_back(v);
        }
    }
};

typedef std::vector<std::shared_ptr<Vertex> >::iterator VITER;

class Graph {
    private:
        std::vector<std::shared_ptr<Vertex> > m_vertices;
        
    public:
        Graph() {
            /*     6
                 /   \ 
                 1- 2- 5 - 7
                 |   \/
                 - 3- 4
            */
            std::shared_ptr<Vertex> v1 = std::make_shared<Vertex>(1);
            std::shared_ptr<Vertex> v2 = std::make_shared<Vertex>(2);
            std::shared_ptr<Vertex> v3 = std::make_shared<Vertex>(3);
            std::shared_ptr<Vertex> v4 = std::make_shared<Vertex>(4);
            std::shared_ptr<Vertex> v5 = std::make_shared<Vertex>(5);
            std::shared_ptr<Vertex> v6 = std::make_shared<Vertex>(6);
            std::shared_ptr<Vertex> v7 = std::make_shared<Vertex>(7);

            v1->add_edge(v2);
            v1->add_edge(v6);       
            v1->add_edge(v3);
            m_vertices.push_back(v1);

            v2->add_edge(v5);
            v2->add_edge(v4);
            v2->add_edge(v1);
            m_vertices.push_back(v2);

            v3->add_edge(v1);
            v3->add_edge(v4);
            m_vertices.push_back(v3);
            
            v4->add_edge(v2);
            v4->add_edge(v5);
            m_vertices.push_back(v4);

            v5->add_edge(v6);
            v5->add_edge(v2);
            v5->add_edge(v4);
            v5->add_edge(v7);
            m_vertices.push_back(v5);

            v6->add_edge(v1);
            v6->add_edge(v5);
            m_vertices.push_back(v6);


            v7->add_edge(v5);
            m_vertices.push_back(v7);

        }
        void dfs();
        void bfs();
        void debug();
    private:
        void dfs_helper(std::shared_ptr<Vertex> &v, std::unordered_set<int> &visited);
        void bfs_helper(std::shared_ptr<Vertex> &v);
};


void Graph::dfs() {
    std::unordered_set<int> visited;
    std::cout <<"======= dfs =========" << std::endl;
    std::shared_ptr<Vertex> &root = m_vertices[0];
    dfs_helper(root,visited);
}

void Graph::dfs_helper(std::shared_ptr<Vertex> &v,std::unordered_set<int> &visited) {
    for (VITER i = (v->neighbors).begin(); i != (v->neighbors).end(); ++i) {
        if (visited.find((*i)->val) == visited.end()) {
            std::cout <<(*i)->val << std::endl;
            visited.insert((*i)->val);
            dfs_helper(*i,visited);
        }   
    }
}

void Graph::bfs() {
    std::cout <<"======= bfs =========" << std::endl;
    std::queue<std::shared_ptr<Vertex> > q;
    std::unordered_set<int> visited;
    q.push(m_vertices[0]);

    while(!q.empty()) {
        std::shared_ptr<Vertex> current_node = q.front();
        std::vector<std::shared_ptr<Vertex> > &current_level = current_node->neighbors;
        
        for (VITER i = current_level.begin(); i != current_level.end(); ++i) {
            if (visited.find((*i)->val) == visited.end()) {
                std::cout <<(*i)->val << std::endl;
                visited.insert((*i)->val);
                q.push(*i);
            }   
        }
        q.pop();
    }
}

void Graph::bfs_helper(std::shared_ptr<Vertex> &v) {
    
}

int main() {
    Graph g;
    g.bfs();
}