# 3D-Object-Painter-with-Graph-Structure
3D Object Painter created using by MeshGraph, Binary Heap, Breadth-First
Search and Dijkstra Shortest Path Algorithm implementations. \
Binary Heap is used as STL Heap data structure. BinaryHeap.cpp has the necessary functions such as Add, PopHeap, ChangePriority, HeapSize and those functions help the coloring proccess using and updating the weight of the edges. MeshGraph.cpp has the important functions to implement Dijkstra Shortest Path Algorithm and Breadth-First
Search. MeshGraph.cpp forms edges and paints specific edges and nodes. MeshGraph uses adjacency list style of implementation with slight differences.\
Here are the examples of 3D painted objects from different angles.\
A Face:
![2023-03-12_03-30-36](https://user-images.githubusercontent.com/89254644/224518272-556bb51d-7e1e-47f5-b0cd-30ee5def16a8.png)
![2023-03-12_03-31-27](https://user-images.githubusercontent.com/89254644/224518277-318f6f17-4ed2-4982-9cd6-983995c5746d.png)
A Standing Human:
![2023-03-12_03-33-36](https://user-images.githubusercontent.com/89254644/224518296-b2e98d42-f872-4700-823f-3f26c495dad7.png)
![2023-03-12_03-34-24](https://user-images.githubusercontent.com/89254644/224518298-5d383bfa-91c5-411c-8a45-587df7c8288c.png)
A plane:
![2023-03-12_03-35-46](https://user-images.githubusercontent.com/89254644/224518306-52cd5e43-168b-4289-85a3-0c484b27122a.png)
![2023-03-12_03-35-11](https://user-images.githubusercontent.com/89254644/224518307-d7aa6064-cd17-45b2-aab4-0dd773c94de6.png)

Usage:
On Linux type: " ./CENG-213-OBJ-Loader "path_to_.obj_file" "path_to_color_file" t" (or q) without any quotes.
On Windows type: " ./ObjViewer.exe "path_to_.obj_file" "path_to_color_file" t" (or q) without any quotes.

While using these programs, you should be in the directory that the program is on (from the terminal). Use "q" (third argument) for plane.obj and plane-low.obj files, and "t" for facem-low2.obj and man-low.obj files (again no quotes).
