// ---- Created by TamHuynh _ June 4th 2020 ---

/*
	Dijkstra algorithm using common matrix from .txt input file
	Nodes are non-zero digits
	*Go to Project-> "Project name" properties-> C/C++ -> Advanced -> Disabled warnings = 4996
	if scanf and fopen is being warned
*/

#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define input "DijkstraInput.txt" // Change your file name if you want
#define MAX 100
#define INFINITE 99999

int Graph[MAX][MAX];// Matrix in use
int size;// Size of matrix
int start;// Input starting node
int Path[MAX];// Save path to each node
int Cost[MAX];// Save cost from start to each node
int Visited[MAX];// Save visited nodes here
int Unvisited[MAX];// Save unvisited nodes here
int unVi;// Number of unvisited

void file_Input()// Graph received from file
{
	FILE *fi = fopen(input, "rt");
	if (fi == NULL)
	{
		printf("File not found!\n");
		_sleep(1000);
		exit(0);
	}
	fscanf_s(fi, "%d", &size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			fscanf_s(fi, "%d", &Graph[i][j]);
	fclose(fi);
}

bool check_Starting_Node_Error()// Check start node
{
	return start < 1 || start > size;
}

void startPoint_Input()
{
	printf("Choose a starting node: ");
	scanf("%d", &start);

	while (check_Starting_Node_Error())
	{
		printf("Choose again: ");
		scanf("%d", &start);
	}
}

void initiate_Objects()
{
	for (int i = 0; i < size; i++)
	{
		Path[i] = 0;
		Cost[i] = INFINITE;
		Visited[i] = 0;
		Unvisited[i] = i + 1;
	}
	unVi = size;
	// Make start node cost 0 and no path leads to it 
	Path[start - 1] = 0;
	Cost[start - 1] = 0;
}

bool exist_in_Visited(int check)
{
	for (int i = 0; i < size; i++)
		if (check == Visited[i])
			return true;
	return false;
}

int Min_of_Unvisited()
{
	int min = Cost[Unvisited[0] - 1];
	int address = Unvisited[0] - 1;
	for (int i = 1; i < unVi; i++)
		if (min > Cost[Unvisited[i] - 1])
		{
			min = Cost[Unvisited[i] - 1];
			address = Unvisited[i] - 1;
		}
	return address;
}

int Path_Cost(int visiting, int j)
{
	return Graph[visiting][j] + Cost[visiting];
}

void Delete_unvisited(int value)
{
	for (int i = 0; i < unVi; i++)
		if (Unvisited[i] == value)
		{
			for (int j = i; j < unVi - 1; j++)
				Unvisited[j] = Unvisited[j + 1];
		}
	unVi--;
}

void Dijkstra()// Main path searching algorithm
{
	// Starts from: 
	startPoint_Input();
	// Create Path, Cost and Unvisited Nodes
	initiate_Objects();
	// Base
	int loop = size - 1;// Loop for size - 1 is enough
	int visitedNum = 0;// Number of visited nodes
	while (loop > 0)
	{
		int visiting = Min_of_Unvisited();// Visit the minimum path
		Visited[visitedNum] = visiting + 1;
		Delete_unvisited(visiting + 1);
		for (int j = 0; j < size; j++)
		{
			if (exist_in_Visited(j + 1) == false)// Skip the j + 1 node if exists in Visited
			{
				int cost = Path_Cost(visiting, j);// Calculate the path cost from node visiting to node j
				if (Graph[visiting][j] != 0 && cost < Cost[j])// Choose the better path
				{
					Path[j] = visiting + 1;
					Cost[j] = cost;
				}
			}
		}
		visitedNum++;
		loop--;
	}
	Visited[visitedNum] = Unvisited[0];
	Delete_unvisited(0);
}

void track_Path(int node)
{
	printf("%d <-- ", node + 1);
	while (Path[node] != start && Path[node] != 0)
	{
		printf("%d <-- ", Path[node]);
		node = Path[node] - 1;
	}
	printf("%d ", start);
}

void Show_Path()
{
	for (int node = 0; node < size; node++)// Show path of each nodes from start in the graph and its cost
	{
		track_Path(node);
		printf(": %d", Cost[node]);
		printf("\n");
	}
	printf("\n*---------------------------------------------*\n\n");
}

void main()
{
	file_Input();
	while (1)
	{
		Dijkstra();
		Show_Path();
	}
	_getch();
}