#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include "CoordinateTrans/CoordinateTrans.h"
using namespace std;

#define MIN_E 1e-10
#define MAX_E 1e8

struct Segment
{
	PointXY SPoint;
	PointXY EPoint;
};

enum GraphKind
{
	DG,//direction graph
	WDG,//weighted direction graph
	UDG,//none direction graph
	WUDG//weighted none direction graph
};

struct ArcNode
{
	int iAdjVertexIndex;
	ArcNode* pNextArc;
	int info;
};

struct VertexNode
{
	char* cTypeData;
	int iNodeID;
	ArcNode* pFirstArc;
	VertexNode()
	{
		pFirstArc = NULL;
	}
};

class CMapGraph
{
public:
	CMapGraph();
	~CMapGraph();

	int m_iVertexNum;//the num of vertex node
	int m_iEdgeNum;//the num of edge node
	GraphKind m_enGraphKind;
	vector<VertexNode> m_vecVerteices;
	vector<VertexNode> m_vecPathVerteies;

	void InitMapGraph(int iVertexNum, GraphKind _kind);
	void InsertArc(int iVHead, int iVTail, int iWeight);
	void DisplayGraph();
	void DeepFirstSearch(int StartIndex, int EndIndex);
	void BreadthFirstSearch(int StartIndex, int EndIndex);
	//void CreateGraph();
	double PointMulti(PointXY p1, PointXY p2, PointXY p0);
	double CrossMulti(PointXY p1, PointXY p2, PointXY p0);
	//double DistancePoint2Segment(PointXY p1, PointXY p2, PointXY p);
	bool IsInArea(PointXY pt, vector<PointXY> vecPt);
private:
	void DFS(int v);
	void BFS(int v);
	vector<bool> m_vecNodeIsVisited;
	//void CreateDG();
	//void CreateWDG();
	//void CreateUDG();
	//void CreateWUDG();
	bool IsOnline(PointXY p, Segment segment);
	bool IsSegmentCrossing(Segment s1, Segment s2);
};

