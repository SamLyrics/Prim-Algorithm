#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

struct ArcNode
{
	int adjvex;
	int weight;
	ArcNode *next;
};

struct VNode
{
	int number;
	int key;
	int state;
	VNode *parent;
	ArcNode *firstarc;
};

struct Graph
{
	int numVertexes;
	int numArcs;
	VNode *node;
};

int Wuv(VNode *node, VNode *u, VNode *v)
{
	ArcNode *p = new ArcNode;
	p = u->firstarc;
	while (p->next)
	{
		if (&node[p->next->adjvex] == v)
		{
			return p->next->weight;
		}
		p = p->next;
	}
	return 9999;
}

int IsIn(VNode *Q, VNode *v, int num)
{
	for (int counter = 0; counter < num; counter++)
	{
		if (Q[counter].number == v->number)
		{
			return 1;
		}
	}
	return 0;
}

void Prim(Graph *graph)
{
	for (int counter = 0; counter < graph->numVertexes; counter++)
	{
		graph->node[counter].key = 9999;
		graph->node[counter].parent = NULL;
	}
	VNode *root = &graph->node[0];
	root->key = 0;

	int num = 0;
	int cout = graph->numVertexes;
	VNode *U = new VNode[graph->numVertexes];

	for (int counter = 0; counter < graph->numVertexes; counter++)
	{
		graph->node[counter].state = 0;
	}

	while (cout > 0)
	{
		VNode *q = new VNode;
		q->key = 9999;
		int tax = 0;
		for (int counter = 0; counter < graph->numVertexes; counter++)
		{
			if (q->key > graph->node[counter].key && graph->node[counter].state == 0)
			{
				*q = graph->node[counter];
				tax = counter;
			}
		}

		graph->node[tax].state = 1;
		U[num++] = *q;
		cout--;

		for (int counter = 0; counter < num; counter++)
		{
			ArcNode *p = new ArcNode;
			p = U[counter].firstarc;
			int minkey = 9999;
			while (p->next)
			{
				if (p->next->weight < graph->node[p->next->adjvex].key && 
					graph->node[p->next->adjvex].state == 0)
				{
					graph->node[p->next->adjvex].key = p->next->weight;
					graph->node[p->next->adjvex].parent = &U[counter];
					minkey = p->next->weight;
				}
				p = p->next;
			}

		}
	}

}

void CreateGraph(Graph *graph)
{
	ifstream file("D:/学习/算法分析与设计/实验/程序相关/Prime and Krustal Input.txt", 
		ios::in);
	file >> graph->numVertexes;
	file >> graph->numArcs;
	graph->node = new VNode[graph->numVertexes];
	for (int counter = 0; counter < graph->numVertexes; counter++)
	{
		graph->node[counter].number = counter + 1;
		graph->node[counter].firstarc = new ArcNode;
		graph->node[counter].firstarc->next = NULL;
	}
	for (int counter = 0; counter < graph->numArcs; counter++)
	{
		ArcNode *arcnode = new ArcNode;
		ArcNode *arcnode2 = new ArcNode;
		int num1, num2;
		file >> num1;
		file >> arcnode->weight;
		file >> num2;

		arcnode->next = graph->node[num1 - 1].firstarc->next;
		graph->node[num1 - 1].firstarc->next = arcnode;
		arcnode->adjvex = num2 - 1;



		arcnode2->next = graph->node[num2 - 1].firstarc->next;
		arcnode2->weight = arcnode->weight;
		graph->node[num2 - 1].firstarc->next = arcnode2;
		arcnode2->adjvex = num1 - 1;

	}
	file.close();
}

int main()
{
	Graph *graph = new Graph;
	CreateGraph(graph);
	Prim(graph);
	system("cls");
	ofstream file("D:/学习/算法分析与设计/实验/程序相关/Prime and Krustal Output.txt", 
		ios::trunc);
	for (int counter = 0; counter < graph->numVertexes; counter++)
	{
		if (graph->node[counter].parent)
		{
			file << "V" << graph->node[counter].number << "--V";
			file << graph->node[counter].parent->number << endl;
		}
	}
	file.close();
	return 0;
}