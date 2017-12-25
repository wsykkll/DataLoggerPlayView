#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <list>

// 点坐标信息
struct METKeyPoint
{
	double dLatitude;
	double dLongitude;
	// double dAltitude;
};

// 描述一个区域范围，用来表示Road、Section、Intersection和ZebraLine的范围（外包络矩形框）
struct METBox
{
	int iPointNum;
	std::vector<METKeyPoint> vec_EdgePoints;
	//double dLeft;//左边经度坐标
	//double dRight;//右边经度坐标
	//double dTop;//上边纬度坐标
	//double dBottom;//下边纬度左边
};


// 车道线的路点，车道线点集
struct METRoadPoint
{
	METKeyPoint stPoint;
	float fHeading;
};

// 交通标志与交通信号灯
// 位置、类型、颜色、宽度和所在Road的ID号
//TSR 包括交通信号灯（TL）和交通标志牌（TS）
enum TSRType
{
	TS_RECTANGLE,//矩形交通标志牌
	TS_CIRCLE,//圆形交通标志牌
	TS_TRIANGLE,//三角形交通标志牌
	TL_HORIZONTAL,//横向排列交通信号灯
	TL_VERTICAL//纵向排列交通信号灯
};
//交通信号灯的颜色默认为UNKNOWN
enum COLORTYPE
{
	UNKNOWN_COLOR,
	YELLOW,
	BLUE,
	GREEN,
	BLACK,
	WHITE
};
struct METTSR
{
	double dLPLatitude;
	double dLPLongitude;
	TSRType enTSRType;
	COLORTYPE enTSRColor;
	float fWidth;
	float fHeight;
	float fTheta;
	int nLinkedRoadID;
};

// 车道线的编号信息
struct METLanelineIndex
{
	int nRoadId;
	int nSectionSeq;
	int nEdgeNum;
};

// 车道线
// ID号、索引编号、颜色、车道线类型和点集链表
// 车道线索引号与车道编号：以车体运动方向为参考，从左向右给车道线编号，车道的编号和车道左车道线编号相同
enum LINEType
{
	UNKNOWN_LINE,
	SIGNLE_SOLID,//单实线
	SINGLE_DASHED,//单虚线
	DOUBLE_SOLID,//双实线
	SOLID_DASHED,//双线（左实右虚）
	DASHED_SOLID,//双线（左虚右实）
	DUMMY,//虚拟线
	DOUBLE_DASHED//双虚线
};

struct METLine
{
	int nLineID;//车道线索引号,从车辆运行方向左边开始计数
	METLanelineIndex stKeyIndex;//车道线所在的RoadID、SectionID和LineID
	COLORTYPE enColor;
	LINEType enType;
	std::list<METRoadPoint> list_points;
	std::vector<METRoadPoint> vec_points;
};

// 路段
// ID号、矩形包络框、是否与路口相连、车道数量与车道线
enum LaneDiversion//车道导流信息
{
	UNKNOWN_DIVERSION,
	UTURN,//掉头
	LEFT,//左转
	LEFT_STRAIGHT,//直行+左转
	LEFT_UTURN,//左转+掉头
	LEFT_STRAIGHT_UTURN,//直行+左转+掉头
	STRAIGHT,//直行
	STRAIGHT_RIGHT,//直行+右转
	RIGHT//右转
};

struct METLane
{
	LaneDiversion enLaneDiversion;//当Section与路口不相连时，车道的导流信息设为UNKNOWN
};
enum ROADTYPE
{
	UNKNOWN_ROAD,
	COMMON,//一般道路
	HIGHWAY,//高速公路
	OVERPASS,//高架桥
	INRAMP,//进入高速或高架的匝道
	OUTRAMP,//驶出高速或高架的匝道
	ROUNDABOUT,//环岛
	SIDEROAD//辅路
};
struct METSection
{
	int nSectionID;
	METBox stSectionBox;
	ROADTYPE enRoadType;
	bool bConnected;//该Section是否与路口相连
	std::vector<METLine> vec_lines;
	std::vector<METLane> vec_lanes;
};

// 路口虚拟车道线由拓扑关系决定
struct METVirtualLine
{
	int nLineID;//车道线索引号
	int nWayInRoadID;
	int nWayOutRoadID;
	int nWayInLaneID;
	int nWayOutLaneID;
	int nWayInSectionID;
	int nWayOutSectionID;
	std::list<METRoadPoint> list_points;
};
//连接道路 nWayInRoadID 和 nWayOutRoadID的虚拟车道线
struct METVirtualLane
{
	int nVirtualLaneID;
	int nWayInRoadID;
	int nWayOutRoadID;
	
	std::vector<METVirtualLine> vec_VirtualLanes;
};

//停止线
struct METStopLine
{
	int nLinkedRoadID;//关联的道路ID号
	METKeyPoint StartPoint;//停止线的起点
	METKeyPoint EndPoint;//停止线的终点
};

// 斑马线，以矩形框代替
struct METZebraLine
{
	int nLinkedRoadID;//关联的道路ID号
	METBox stZebralineBox;
};

/*======================================================================================
地图的基础数据结构分为Road（道路，两个路口之间作为一段Road）和Intersection（交叉路口）
======================================================================================*/

// Road数据包括道路编号，道路的范围（以四个角点表示）和在这段道路上所有的交通标志，将Road分成不同的Section，依据车道数量的变化进行划分
struct METRoad
{
	int nRoadID;//道路ID号
	METBox stRoadBox;//道路区域包络
	std::list<METSection> list_sections;
	std::vector<METTSR> vec_trafficsigns;//Traffic sign on this road
};

// 交叉路口分为十字路口，T形路口；Intersection数据包括路口编号、类型、范围，停止线和斑马线，与道路的拓扑关系，虚拟车道线
enum INTERSECTIONTYPE
{
	INTERCROSS,
	T_CROSS,
	Y_CROSS,
};
struct METIntersection
{
	int nIntersectionID;//交叉路口ID号
	INTERSECTIONTYPE enIntersectionType;//
	METBox stIntersectionBox;//路口区域的包络
	std::vector<int> vec_InRoadID;//进入路口的RoadID
	std::vector<int> vec_OutRoadID;//驶出路口的RoadID
	std::vector<METZebraLine> vec_zebraline;
	std::vector<METTSR> vec_TrafficSignsLights;
	std::vector<METStopLine> vec_stoplines;

	std::vector<METVirtualLine> vec_VirtualLaneLines;
	//std::vector<METVirtualLane> vec_VirtualLanes;//根据与Road的连接关系生成不同的虚拟车道线
};

struct METMAP
{
	std::vector<METRoad> vec_Roads;
	std::vector<METIntersection> vec_InterSections;
};