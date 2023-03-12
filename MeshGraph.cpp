#include "MeshGraph.h"
#include "BinaryHeap.h"

// For printing
#include <fstream>
#include <iostream>
#include <sstream>

MeshGraph::MeshGraph(const std::vector<Double3>& vertexPositions,
                     const std::vector<IdPair>& edges)
{
    // TODO:
    vertexCount = vertexPositions.size();
    edgeCount = edges.size();
    
    elemFor1.resize(edgeCount);
    elemFor2.resize(edgeCount);
    
    vertices.resize(vertexCount);
    adjList.resize(edgeCount*2);
    
    for(int i=0; i<vertexCount; i++)
    {
        vertices[i].id = i;
        vertices[i].position3D = vertexPositions[i];
    }
   
     
    for(int i=0; i<edgeCount ; i++)
    {
       
        std::list<Vertex*>::iterator pos = adjList[edges[i].vertexId0].begin();
        elemFor1[i].id = edges[i].vertexId1;
        elemFor1[i].position3D = vertexPositions[edges[i].vertexId1];
       
        
        if (pos != adjList[edges[i].vertexId0].end()) {
            pos++;
        }
        adjList[edges[i].vertexId0].insert(pos, &elemFor1[i]);
    }
    
    for(int i=0; i<edgeCount ; i++)
    {
        
        std::list<Vertex*>::iterator pos = adjList[edges[i].vertexId1].begin();
        elemFor2[i].id = edges[i].vertexId0;
        elemFor2[i].position3D = vertexPositions[edges[i].vertexId0];
       
        
        if (pos != adjList[edges[i].vertexId1].end()) {
            pos++;
        }
        adjList[edges[i].vertexId1].insert(pos, &elemFor2[i]);
    }
}

double MeshGraph::AverageDistanceBetweenVertices() const
{
    // TODO:
    Double3 a;
    double totalWeight = 0;
    std::list<Vertex*>::const_iterator pos;
    for(int i=0; i<(vertexCount) ; i++)
    {
        for(pos = adjList[i].begin(); pos != adjList[i].end(); pos++)
        {
            totalWeight += a.Distance(vertices[i].position3D, (*pos)->position3D);
        }
    }
    return (double) totalWeight/(edgeCount*2);
}

double MeshGraph::AverageEdgePerVertex() const
{
    // TODO:
    return (double) edgeCount/(vertexCount);
}

int MeshGraph::TotalVertexCount() const
{
    // TODO:
    return vertexCount;
}

int MeshGraph::TotalEdgeCount() const
{
    // TODO:
    return edgeCount;
}

int MeshGraph::VertexEdgeCount(int vertexId) const
{
    // TODO:
    
    for(int i=0; i<vertexCount; i++)
    {
        int vertexEdgeCount = 0;
        if(i == vertexId)
        {
            std::list<Vertex*>::const_iterator pos ;
            for (pos = adjList[i].begin();pos != adjList[i].end();pos++) {
                vertexEdgeCount++;
            }
            return vertexEdgeCount;    
        }
    }
    return -1;
}

void MeshGraph::ImmediateNeighbours(std::vector<int>& outVertexIds,
                                    int vertexId) const
{
    // TODO:
    for(int i=0; i<vertexCount; i++)
    {
        if(i == vertexId)
        {
            int index =0;
            int neighbourSize = 0;
            std::list<Vertex*>::const_iterator pos ;
            for (pos = adjList[i].begin();pos != adjList[i].end();pos++) {
                neighbourSize++;
            }
            outVertexIds.resize(neighbourSize);
            
            for (pos = adjList[i].begin();pos != adjList[i].end();pos++) {
                outVertexIds[index] = (*pos)->id;
                index++;
            }
        }
    }
}
                 
void MeshGraph::PaintInBetweenVertex(std::vector<Color>& outputColorAllVertex,
                                     int vertexIdFrom, int vertexIdTo,
                                     const Color& color) const
{
    // TODO:
    bool from = false;
    bool to = false;
    for(int i=0; i<vertexCount; i++)
    {
        if(i == vertexIdFrom) from = true;
        
        if(i == vertexIdTo) to = true;
    }
    
    if(from && to)
    {
        outputColorAllVertex.resize(vertexCount);
        
        for(int i=0; i<vertexCount; i++)
        {
            outputColorAllVertex[i].r = 0;
            outputColorAllVertex[i].g = 0;
            outputColorAllVertex[i].b = 0;
        }
        Double3 a;
        BinaryHeap hp;
        
        std::vector<double> distance;
        std::vector<int> previous;
    
        distance.resize(vertexCount);
        previous.resize(vertexCount);
        
        for(int i=0; i<vertexCount ; i++)
        {
            distance[i] = INFINITY;
            previous[i] = -1;
        }
       
        distance[vertexIdFrom] = 0;
        
        for(int i=0; i<vertexCount ; i++)
        {
            hp.Add(vertices[i].id, distance[i]);
        }
        
        while(hp.HeapSize() > 0)
        {
           
            Vertex popElement;
            double indexW;
           
            hp.PopHeap(popElement.id, indexW);
            distance[popElement.id] = indexW;
            popElement.position3D = vertices[popElement.id].position3D;
            std::vector<int> neighbour;
            ImmediateNeighbours(neighbour, popElement.id);
            
            for(int i=0; i<neighbour.size(); i++)
            {
                double newDistance;
                newDistance = indexW + a.Distance(popElement.position3D, vertices[neighbour[i]].position3D);
                if(newDistance < distance[neighbour[i]])
                {
                    distance[neighbour[i]] = newDistance;
                    previous[neighbour[i]] = popElement.id;
                    hp.ChangePriority(neighbour[i], (double) newDistance);
                }
            }
        }
        
        std::vector<int> verticesToColor;
        verticesToColor.push_back(vertexIdTo);
        int col=vertexIdTo;
        
        while(col != vertexIdFrom)
        {
            verticesToColor.push_back(previous[col]);
            col = previous[col];
        }
        
        for(int i=0; i<verticesToColor.size(); i++)
        {
            outputColorAllVertex[verticesToColor[i]] = color;
        }
        
    }
}

void MeshGraph::PaintInRangeGeodesic(std::vector<Color>& outputColorAllVertex,
                                    int vertexId, const Color& color,
                                    int maxDepth, FilterType type,
                                    double alpha) const
{
    // TODO:
    bool Id = false;
    for(int i=0; i<vertexCount; i++)
    {
        if(i == vertexId) Id = true;
    }
    
    if(Id)
    {
        outputColorAllVertex.resize(vertexCount);
        
        for(int i=0; i<vertexCount; i++)
        {
            outputColorAllVertex[i].r = 0;
            outputColorAllVertex[i].g = 0;
            outputColorAllVertex[i].b = 0;
        }
        
        Double3 a;
        BinaryHeap hp;

        std::vector<bool> visited;
        std::vector<int> previous;
        
        double myW = 0;
        
        visited.resize(vertexCount, false);
        previous.resize(vertexCount, -1);
        visited[vertexId] = true;
        hp.Add(vertices[vertexId].id, myW++);
        outputColorAllVertex[vertexId] = color;
        
        int depth = 0;
        while(depth != maxDepth)
        {
            depth++;
            int hSize = hp.HeapSize();
            for(int anan=0; anan<hSize; anan++)
            {
                Vertex heapElement;
                double indexWeight;
    
                std::vector<int> neig;
                std::list<int> neighbour;
                std::list<int>::iterator it;
                
                hp.PopHeap(heapElement.id, indexWeight);
                heapElement.position3D = vertices[heapElement.id].position3D;
                
                ImmediateNeighbours(neig, heapElement.id);
                
                for(int n=0; n<neig.size(); n++)
                {
                    neighbour.push_back(neig[n]);
                }
                neighbour.sort();
                neig.clear();
                for(it = neighbour.begin(); it!=neighbour.end(); it++)
                {   
                    neig.push_back((*it));
                }
                
                for(int n=0; n<neig.size(); n++)
                {
                    
                    if(!visited[neig[n]])
                    {
                        visited[neig[n]] = true;
                        previous[neig[n]] = heapElement.id;
                        hp.Add(neig[n], myW++);
                        
                        double colorDist=0;
                        int col = neig[n];
                        while(col != vertexId)
                        {
                            colorDist += a.Distance(vertices[col].position3D, vertices[previous[col]].position3D);
                            col = previous[col];
                        }
                        
                        if(type == FILTER_GAUSSIAN)
                        {
                            double ex = (double) (pow(colorDist, 2) / pow(alpha, 2));
                            
                            outputColorAllVertex[neig[n]].r = (int) (std::exp(-ex)*color.r);
                            outputColorAllVertex[neig[n]].g = (int) (std::exp(-ex)*color.g);
                            outputColorAllVertex[neig[n]].b = (int) (std::exp(-ex)*color.b);
                        }
                        
                        if(type == FILTER_BOX)
                        {
                            if(colorDist > (-alpha) && colorDist < alpha)
                            {
                                outputColorAllVertex[neig[n]] = color;
                            }
                            
                            else
                            {
                                outputColorAllVertex[neig[n]].r = 0;
                                outputColorAllVertex[neig[n]].g = 0;
                                outputColorAllVertex[neig[n]].b = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

void MeshGraph::PaintInRangeEuclidian(std::vector<Color>& outputColorAllVertex,
                                      int vertexId, const Color& color,
                                      int maxDepth, FilterType type,
                                      double alpha) const
{
    // TODO:
    bool Id = false;
    for(int i=0; i<vertexCount; i++)
    {
        if(i == vertexId) Id = true;
    }
    
    if(Id)
    {
        outputColorAllVertex.resize(vertexCount);
        
        for(int i=0; i<vertexCount; i++)
        {
            outputColorAllVertex[i].r = 0;
            outputColorAllVertex[i].g = 0;
            outputColorAllVertex[i].b = 0;
        }
        
        Double3 a;
        BinaryHeap hp;

        std::vector<bool> visited;
        std::vector<int> previous;
        
        double myW = 0;
        
        visited.resize(vertexCount, false);
        previous.resize(vertexCount, -1);
        visited[vertexId] = true;
        hp.Add(vertices[vertexId].id, myW++);
        outputColorAllVertex[vertexId] = color;
        
        int depth = 0;
        while(depth != maxDepth)
        {
            depth++;
            int hSize = hp.HeapSize();
            for(int anan=0; anan<hSize; anan++)
            {
                Vertex heapElement;
                double indexWeight;
    
                std::vector<int> neig;
                std::list<int> neighbour;
                std::list<int>::iterator it;
                
                hp.PopHeap(heapElement.id, indexWeight);
                heapElement.position3D = vertices[heapElement.id].position3D;
                
                ImmediateNeighbours(neig, heapElement.id);
                
                for(int n=0; n<neig.size(); n++)
                {
                    neighbour.push_back(neig[n]);
                }
                neighbour.sort();
                neig.clear();
                for(it = neighbour.begin(); it!=neighbour.end(); it++)
                {   
                    neig.push_back((*it));
                }
                
                for(int n=0; n<neig.size(); n++)
                {
                    
                    if(!visited[neig[n]])
                    {
                        visited[neig[n]] = true;
                        previous[neig[n]] = heapElement.id;
                        hp.Add(neig[n], myW++);
                        
                        double colorDist=a.Distance(vertices[neig[n]].position3D, vertices[vertexId].position3D);;
                        
                        if(type == FILTER_GAUSSIAN)
                        {
                            double ex = (double) (pow(colorDist, 2) / pow(alpha, 2));
                            
                            outputColorAllVertex[neig[n]].r = (int) (std::exp(-ex)*color.r);
                            outputColorAllVertex[neig[n]].g = (int) (std::exp(-ex)*color.g);
                            outputColorAllVertex[neig[n]].b = (int) (std::exp(-ex)*color.b);
                        }
                        
                        if(type == FILTER_BOX)
                        {
                            if(colorDist > (-alpha) && colorDist < alpha)
                            {
                                outputColorAllVertex[neig[n]] = color;
                            }
                            
                            else
                            {
                                outputColorAllVertex[neig[n]].r = 0;
                                outputColorAllVertex[neig[n]].g = 0;
                                outputColorAllVertex[neig[n]].b = 0;
                            }
                        }
                    }
                }
            }
        }
    }
}

void MeshGraph::WriteColorToFile(const std::vector<Color>& colors,
                                 const std::string& fileName)
{
    // IMPLEMENTED
    std::stringstream s;
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        int r = static_cast<int>(colors[i].r);
        int g = static_cast<int>(colors[i].g);
        int b = static_cast<int>(colors[i].b);

        s << r << ", " << g << ", " << b << "\n";
    }
    std::ofstream f(fileName.c_str());
    f << s.str();
}

void MeshGraph::PrintColorToStdOut(const std::vector<Color>& colors)
{
    // IMPLEMENTED
    for(int i = 0; i < static_cast<int>(colors.size()); i++)
    {
        std::cout << static_cast<int>(colors[i].r) << ", "
                  << static_cast<int>(colors[i].g) << ", "
                  << static_cast<int>(colors[i].b) << "\n";
    }
}