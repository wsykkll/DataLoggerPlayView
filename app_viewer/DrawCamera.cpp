#include "DrawCamera.h"


CDrawCamera::CDrawCamera() :
m_nImageW(1280),
m_nImageH(720),
m_nlastPosTimestamp(0),
m_nCurrentTimestamp(0),
m_dInitLatitude(0.0),
m_dInitLongitude(0.0),
m_dLastHeading(0.0),
m_iLastRecvPosTime(0),
m_bMapLoaded(true),
m_bMapSplitLoaded(true),
m_bMapCalibrationLoaded(true),
m_bMapTSRLoaded(true),
m_bPostureReceived(false),
m_bLanemarkReceived(false),
m_bRecrveImg(false), 
m_bCalLocalPos(false)
{
	m_pImg = cvCreateImage(cvSize(m_nImageW, m_nImageH), IPL_DEPTH_8U, 3);
	//LoadLaneMark();
	//LoadLaneMarkTotally();
	//LoadTSRInfo();
	LoadMap();
	//CreateMapGraph();
	//LoadCalibrationLanelines();
}


CDrawCamera::~CDrawCamera()
{
	delete m_pImg;
}

inline void CDrawCamera::PrintMatrix(CvMat *Matrix, int Rows, int Cols, int Channels)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Cols; j++)
		{
			for (int k = 0; k < Channels; k++)
			{
				printf("%.10f ", cvGet2D(Matrix, i, j).val[k]);
			}
		}
		printf("\n");
	}
}

PointXY CDrawCamera::CrossPoint(PointXY p1, PointXY p2)
{
	if (p1.theta < 0)
	{
		p1.theta = p1.theta + 360;
	}
	if (p2.theta < 0)
	{
		p2.theta = p2.theta + 360;
	}
	PointXY RePoint;
	double dDeltaTheta = fabs(p2.theta - p1.theta);
	if (dDeltaTheta < 0.5)
	{

	}
	else if (fabs(dDeltaTheta-180) < 0.5)
	{
		RePoint.x = (p1.x + p2.x) / 2.0;
		RePoint.y = (p1.y + p2.y) / 2.0;
	}
	else
	{
		double t1 = tan(p1.theta*DEGREE_TO_RADIAN);
		double t2 = tan(p2.theta*DEGREE_TO_RADIAN);
		RePoint.x = (t1*p1.x - t2*p2.x + p2.y - p1.y) / (t1 - t2);
		RePoint.y = t1*(RePoint.x - p1.x) + p1.y;
	}
	return RePoint;
}


vector<PointXY> CDrawCamera::GenerateBezier(PointXY* Anchor1, PointXY* Anchor2, PointXY* Control, int NUM)
{
	vector<PointXY> returnVecPoints;
	PointXY tmpPoint;
	returnVecPoints.push_back(*Anchor1);
	float step = 1.0 / float(NUM);
	for (int i = 1; i < NUM; i++)
	{
		float t = i*step;
		tmpPoint.x = (1 - t)*(1 - t)*Anchor1->x + 2 * t*(1 - t)*Control->x + t*t*Anchor2->x;
		tmpPoint.y = (1 - t)*(1 - t)*Anchor1->y + 2 * t*(1 - t)*Control->y + t*t*Anchor2->y;
		returnVecPoints.push_back(tmpPoint);
	}
	returnVecPoints.push_back(*Anchor2);
	return returnVecPoints;
}

void CDrawCamera::LoadMap()
{
	XMLDocument* doc = new XMLDocument();
	XMLError errorID = doc->LoadFile("..\\Data\\METMap.xml");
	if (errorID != 0)
	{
		m_bIsMapLoaded = false;
		//return false;
	}
	XMLElement* pRootElem = doc->RootElement();
	int iRoadAmount = 0;
	pRootElem->QueryIntAttribute("RoadAmount", &iRoadAmount);
	XMLElement* pRoadElem = pRootElem->FirstChildElement("Road");
	for (pRoadElem; pRoadElem; pRoadElem = pRoadElem->NextSiblingElement("Road"))
	{
		METRoad tmpMETRoad;
		vector<cv::Point2f> vecRoadOutlinePoints;
		double dGlobalInitLat = 0.0;
		double dGlobalInitLon = 0.0;
		pRoadElem->QueryIntAttribute("Id", &(tmpMETRoad.nRoadID));
		int iSectionIndex = 0;
		int iLineIndex = 0;
		XMLElement* pRoadSectionElem = pRoadElem->FirstChildElement("Section");
		for (pRoadSectionElem; pRoadSectionElem; pRoadSectionElem = pRoadSectionElem->NextSiblingElement("Section"))
		{
			METSection tmpRoadSection;
			pRoadSectionElem->QueryBoolAttribute("Connected", &(tmpRoadSection.bConnected));
			pRoadSectionElem->QueryIntAttribute("Id", &(tmpRoadSection.nSectionID));
			int iLaneAmount = 0;
			int iLineAmount = 0;
			pRoadSectionElem->QueryIntAttribute("LaneAmount", &iLaneAmount);
			pRoadSectionElem->QueryIntAttribute("LaneLineAmount", &iLineAmount);
			XMLElement* pLineElem;
			pLineElem = pRoadSectionElem->FirstChildElement("Line");
			for (pLineElem; pLineElem; pLineElem = pLineElem->NextSiblingElement("Line"))
			{
				METLine tmpLine;
				pLineElem->QueryIntAttribute("RoadId", &(tmpLine.stKeyIndex.nRoadId));
				pLineElem->QueryIntAttribute("SectionId", &(tmpLine.stKeyIndex.nSectionSeq));
				pLineElem->QueryIntAttribute("EdgeId", &(tmpLine.stKeyIndex.nEdgeNum));
				pLineElem->QueryIntAttribute("UniqueId", &(tmpLine.nLineID));
				int iType, iColor;
				pLineElem->QueryIntAttribute("TypeLanLine", &(iType));
				pLineElem->QueryIntAttribute("Color", &(iColor));
				tmpLine.enColor = COLORTYPE(iColor);
				tmpLine.enType = LINEType(iType);

				XMLElement* pRoadPointElem = pLineElem->FirstChildElement("Point");
				for (pRoadPointElem; pRoadPointElem; pRoadPointElem = pRoadPointElem->NextSiblingElement("Point"))
				{
					METRoadPoint tmpRoadPoint;
					int iID = 0;
					pRoadPointElem->QueryIntAttribute("Id", &iID);
					pRoadPointElem->QueryFloatAttribute("Heading", &(tmpRoadPoint.fHeading));
					pRoadPointElem->QueryDoubleAttribute("Lon", &(tmpRoadPoint.stPoint.dLongitude));
					pRoadPointElem->QueryDoubleAttribute("Lat", &(tmpRoadPoint.stPoint.dLatitude));
					tmpLine.list_points.push_back(tmpRoadPoint);
					if (iSectionIndex == 0 && iLineIndex == 0)
					{
						dGlobalInitLat = tmpRoadPoint.stPoint.dLatitude;
						dGlobalInitLon = tmpRoadPoint.stPoint.dLongitude;
					}
				}
				//interpolate the points
				list<METRoadPoint>::iterator Fit = tmpLine.list_points.begin();
				list<METRoadPoint>::iterator Nit = tmpLine.list_points.begin();
				Nit++;
				for (int i = 0; i < (tmpLine.list_points.size() - 1); i++)
				{
					METRoadPoint pta = *(Fit); Fit++;
					METRoadPoint ptb = *(Nit); Nit++;
					tmpLine.vec_points.push_back(pta);
					PointXY StartPoint, EndPoint, InPoint;
					EndPoint = GCS2CCS(pta.stPoint.dLatitude, pta.stPoint.dLongitude, ptb.stPoint.dLatitude, ptb.stPoint.dLongitude);
					//int iNum = floor(Distance(EndPoint));
					int iNum = floor(DistanceInGps(pta.stPoint.dLatitude, pta.stPoint.dLongitude, ptb.stPoint.dLatitude, ptb.stPoint.dLongitude));
					double dDeltaLat = ptb.stPoint.dLatitude - pta.stPoint.dLatitude;
					double dDeltaLon = ptb.stPoint.dLongitude - pta.stPoint.dLongitude;
					double dStepLat = dDeltaLat / iNum;
					double dStepLon = dDeltaLon / iNum;
					double dStepX = EndPoint.x / iNum;
					double dStepY = EndPoint.y / iNum;
					METRoadPoint InterploatePoint;
					InterploatePoint.fHeading = pta.fHeading;
					for (int k = 1; k <= iNum; k++)
					{
						//InPoint.x = k*dStepX;
						//InPoint.y = k*dStepY;
						//InPoint = CCS2GCS(pta.stPoint.dLatitude, pta.stPoint.dLongitude, k*dStepX, k*dStepX);
						//InterploatePoint.stPoint.dLatitude = InPoint.y;
						//InterploatePoint.stPoint.dLongitude = InPoint.x;
						InterploatePoint.stPoint.dLatitude = pta.stPoint.dLatitude + k*dStepLat;
						InterploatePoint.stPoint.dLongitude = pta.stPoint.dLongitude + k*dStepLon;
						tmpLine.vec_points.push_back(InterploatePoint);
					}
				}
				iLineIndex++;
				tmpRoadSection.vec_lines.push_back(tmpLine);
			}
//Section Box
			vector<cv::Point2f> vecOutlinePoints;
			vector<METLine>::iterator it = tmpRoadSection.vec_lines.begin();
			double dInitLat = it->list_points.front().stPoint.dLatitude;
			double dInitLon = it->list_points.front().stPoint.dLongitude;
			tmpRoadSection.stSectionBox.iPointNum = 4;
			for (; it != tmpRoadSection.vec_lines.end(); it++)
			{
				list<METRoadPoint>::iterator Pit = it->list_points.begin();
				for (; Pit != it->list_points.end(); Pit++)
				{
					PointXY tmpPt = GCS2CCS(dInitLat, dInitLon, Pit->stPoint.dLatitude, Pit->stPoint.dLongitude);
					cv::Point2f Pt;
					Pt.x = (float)(tmpPt.x); Pt.y = (float)(tmpPt.y);
					vecOutlinePoints.push_back(Pt);

					tmpPt = GCS2CCS(dGlobalInitLat, dGlobalInitLon, Pit->stPoint.dLatitude, Pit->stPoint.dLongitude);
					Pt.x = (float)(tmpPt.x); Pt.y = (float)(tmpPt.y);
					vecRoadOutlinePoints.push_back(Pt);
				}
			}
			//vecRoadOutlinePoints.insert(vecRoadOutlinePoints.end(), vecOutlinePoints.begin(), vecOutlinePoints.end());
			cv::Point2f OutlinePoints[4];
			cv::minAreaRect(cv::Mat(vecOutlinePoints)).points(OutlinePoints);
			for (size_t i = 0; i < 4; i++)
			{
				PointXY tmpPt = CCS2GCS(dInitLat, dInitLon, OutlinePoints[i].x, OutlinePoints[i].y);
				METKeyPoint PT;
				PT.dLatitude  = tmpPt.y;
				PT.dLongitude = tmpPt.x;
				tmpRoadSection.stSectionBox.vec_EdgePoints.push_back(PT);
			}

			XMLElement* pLaneElem;
			pLaneElem = pRoadSectionElem->FirstChildElement("Lane");
			for (pLaneElem; pLaneElem; pLaneElem = pLaneElem->NextSiblingElement("Lane"))
			{
				METLane tmpMETLane;
				int iLaneDiversion;
				pLaneElem->QueryIntAttribute("Diversion", &iLaneDiversion);
				tmpMETLane.enLaneDiversion = LaneDiversion(iLaneDiversion);
				tmpRoadSection.vec_lanes.push_back(tmpMETLane);
			}
			iSectionIndex++;
			tmpMETRoad.list_sections.push_back(tmpRoadSection);
		}
//Road box
		tmpMETRoad.stRoadBox.iPointNum = 4;
		cv::Point2f RoadOutlinePoints[4];
		cv::minAreaRect(cv::Mat(vecRoadOutlinePoints)).points(RoadOutlinePoints);
		for (size_t i = 0; i < 4; i++)
		{
			PointXY tmpPt = CCS2GCS(dGlobalInitLat, dGlobalInitLon, RoadOutlinePoints[i].x, RoadOutlinePoints[i].y);
			METKeyPoint PT;
			PT.dLatitude = tmpPt.y;
			PT.dLongitude = tmpPt.x;
			tmpMETRoad.stRoadBox.vec_EdgePoints.push_back(PT);
		}
		m_stMap.vec_Roads.push_back(tmpMETRoad);
	}

	XMLElement* pInterSectionElem = pRootElem->FirstChildElement("InterSection");
	for (pInterSectionElem; pInterSectionElem; pInterSectionElem = pInterSectionElem->NextSiblingElement("InterSection"))
	{
		METIntersection tmpInterSection;
		pInterSectionElem->QueryIntAttribute("Id", &(tmpInterSection.nIntersectionID));
		int iInRoadID = -1;
		int iOutRoadID = -1;
		XMLElement* pInRoadElem = pInterSectionElem->FirstChildElement("InRoad");
		XMLElement* pInRoadIDElem = pInRoadElem->FirstChildElement("RoadId");
		for (pInRoadIDElem; pInRoadIDElem; pInRoadIDElem = pInRoadIDElem->NextSiblingElement("RoadId"))
		{
			pInRoadIDElem->QueryIntAttribute("RoadId", &iInRoadID);
			tmpInterSection.vec_InRoadID.push_back(iInRoadID);
		}
		XMLElement* pOutRoadElem = pInterSectionElem->FirstChildElement("OutRoad");
		XMLElement* pOutRoadIDElem = pOutRoadElem->FirstChildElement("RoadId");
		for (pOutRoadIDElem; pOutRoadIDElem; pOutRoadIDElem = pOutRoadIDElem->NextSiblingElement("RoadId"))
		{
			pOutRoadIDElem->QueryIntAttribute("RoadId", &iOutRoadID);
			tmpInterSection.vec_OutRoadID.push_back(iOutRoadID);
		}

		XMLElement* pInterSectionBoxElem = pInterSectionElem->FirstChildElement("OutLine");
		XMLElement* pBoxLineElem = pInterSectionBoxElem->FirstChildElement("Line");
		pBoxLineElem->QueryIntAttribute("PointNum", &(tmpInterSection.stIntersectionBox.iPointNum));
		XMLElement* pBoxPointElem = pBoxLineElem->FirstChildElement("Point");
		for (pBoxPointElem; pBoxPointElem; pBoxPointElem = pBoxPointElem->NextSiblingElement("Point"))
		{
			METKeyPoint tmpPt;
			pBoxPointElem->QueryDoubleAttribute("Lon", &(tmpPt.dLongitude));
			pBoxPointElem->QueryDoubleAttribute("Lat", &(tmpPt.dLatitude));
			tmpInterSection.stIntersectionBox.vec_EdgePoints.push_back(tmpPt);
		}

		XMLElement* pZebraLineElem = pInterSectionElem->FirstChildElement("ZebraLine");
		XMLElement* pZebraLineDataElem = pZebraLineElem->FirstChildElement("Line");
		for (pZebraLineDataElem; pZebraLineDataElem; pZebraLineDataElem = pZebraLineDataElem->NextSiblingElement("Line"))
		{
			METZebraLine tmpZebraLine;
			pZebraLineDataElem->QueryIntAttribute("InRoadId", &(tmpZebraLine.nLinkedRoadID));
			pZebraLineDataElem->QueryIntAttribute("PointNum", &(tmpZebraLine.stZebralineBox.iPointNum));
			XMLElement* pZebraLineBoxElem = pZebraLineDataElem->FirstChildElement("Point");
			METKeyPoint tmpPt;
			for (pZebraLineBoxElem; pZebraLineBoxElem; pZebraLineBoxElem = pZebraLineBoxElem->NextSiblingElement("Point"))
			{
				pZebraLineBoxElem->QueryDoubleAttribute("Lon", &(tmpPt.dLongitude));
				pZebraLineBoxElem->QueryDoubleAttribute("Lat", &(tmpPt.dLatitude));
				tmpZebraLine.stZebralineBox.vec_EdgePoints.push_back(tmpPt);
			}
			tmpInterSection.vec_zebraline.push_back(tmpZebraLine);
		}

		XMLElement* pVirtualLanesElem = pInterSectionElem->FirstChildElement("VirtualLaneLine");
		XMLElement* pVirtualLaneLineElem = pVirtualLanesElem->FirstChildElement("Line");
		for (pVirtualLaneLineElem; pVirtualLaneLineElem; pVirtualLaneLineElem = pVirtualLaneLineElem->NextSiblingElement("Line"))
		{
			METVirtualLine tmpVirtualLine;
			pVirtualLaneLineElem->QueryIntAttribute("InRoadId", &(tmpVirtualLine.nWayInRoadID));
			pVirtualLaneLineElem->QueryIntAttribute("InSectionId", &(tmpVirtualLine.nWayInSectionID));
			pVirtualLaneLineElem->QueryIntAttribute("InLaneId", &(tmpVirtualLine.nWayInLaneID));
			pVirtualLaneLineElem->QueryIntAttribute("OutRoadId", &(tmpVirtualLine.nWayOutRoadID));
			pVirtualLaneLineElem->QueryIntAttribute("OutSectionId", &(tmpVirtualLine.nWayOutSectionID));
			pVirtualLaneLineElem->QueryIntAttribute("OutLaneId", &(tmpVirtualLine.nWayOutLaneID));
			pVirtualLaneLineElem->QueryIntAttribute("EdgeId", &(tmpVirtualLine.nLineID));
			
			//XMLElement* pVirtualLinePoint = pVirtualLaneLineElem->FirstChildElement("Point");
			//for (pVirtualLinePoint; pVirtualLinePoint; pVirtualLinePoint = pVirtualLinePoint->NextSiblingElement("Point"))
			//{
			//	METRoadPoint tmpRoadPt;
			//	pVirtualLinePoint->QueryDoubleAttribute("Lon", &(tmpRoadPt.stPoint.dLongitude));
			//	pVirtualLinePoint->QueryDoubleAttribute("Lat", &(tmpRoadPt.stPoint.dLatitude));
			//	tmpVirtualLine.list_points.push_back(tmpRoadPt);
			//}
			bool bLeft = false;
			if (tmpVirtualLine.nLineID % 2 == 1)
			{
				bLeft = true;
			}
			METRoadPoint StartPoint, EndPoint;
			for (vector<METRoad>::iterator Road_it = m_stMap.vec_Roads.begin(); Road_it != m_stMap.vec_Roads.end(); Road_it++)
			{
				if (Road_it->nRoadID == tmpVirtualLine.nWayInRoadID)
				{
					if (bLeft)
					{
						StartPoint = Road_it->list_sections.back().vec_lines[tmpVirtualLine.nWayInLaneID - 1].list_points.back();
					}
					else
					{
						StartPoint = Road_it->list_sections.back().vec_lines[tmpVirtualLine.nWayInLaneID].list_points.back();
					}
				}
				if (Road_it->nRoadID == tmpVirtualLine.nWayOutRoadID)
				{
					if (bLeft)
					{
						EndPoint = Road_it->list_sections.front().vec_lines[tmpVirtualLine.nWayOutLaneID - 1].list_points.front();
					}
					else
					{
						EndPoint = Road_it->list_sections.front().vec_lines[tmpVirtualLine.nWayOutLaneID].list_points.front();
					}
				}
			}
			tmpVirtualLine.list_points.push_back(StartPoint);
			PointXY local_sPoint, local_ePoint;
			local_sPoint.x = 0.0; local_sPoint.y = 0.0; local_sPoint.theta = (90.0 - StartPoint.fHeading);
			local_ePoint = GCS2CCS(StartPoint.stPoint.dLatitude, StartPoint.stPoint.dLongitude, EndPoint.stPoint.dLatitude, EndPoint.stPoint.dLongitude);
			local_ePoint.theta = (90.0 - EndPoint.fHeading);
			PointXY controlPoint;
			controlPoint = CrossPoint(local_sPoint, local_ePoint);
			//double t1 = tan(local_sPoint.theta*DEGREE_TO_RADIAN);
			//double t2 = tan(local_ePoint.theta*DEGREE_TO_RADIAN);
			//controlPoint.x = (t2*local_ePoint.x - local_ePoint.y) / (t2 - t1);
			//controlPoint.y = t1*controlPoint.x;
			int PointNum = floor(Distance(local_ePoint));
			vector<PointXY> local_VecPoints = GenerateBezier(&local_sPoint, &local_ePoint, &controlPoint, PointNum);
			vector<PointXY>::iterator lp_it = local_VecPoints.begin();
			lp_it++;
			for (; lp_it != local_VecPoints.end(); lp_it++)
			{
				PointXY Pt;
				Pt = CCS2GCS(StartPoint.stPoint.dLatitude, StartPoint.stPoint.dLongitude, double(lp_it->x), double(lp_it->y));
				METRoadPoint tmpPt;
				tmpPt.stPoint.dLatitude = Pt.y;
				tmpPt.stPoint.dLongitude = Pt.x;
				tmpVirtualLine.list_points.push_back(tmpPt);
			}
			//double a[] = { 0.0, 0.0, 0.0, 1.0,
			//	0.0, 0.0, 1.0, 0.0,
			//	pow(local_ePoint.x, 3), pow(local_ePoint.x, 2), local_ePoint.x, 1.0,
			//	3 * pow(local_ePoint.x, 2), 2 * local_ePoint.x, 1.0, 0.0 };
			//CvMat* mat_A = cvCreateMat(4, 4, CV_64FC1);
			//cvSetData(mat_A, a, mat_A->step);
			//PrintMatrix(mat_A, 4, 4, 1);
			//CvMat* mat_A_=cvCreateMat(4, 4, CV_64FC1);
			//cvInvert(mat_A, mat_A_);
			//PrintMatrix(mat_A_, 4, 4, 1);
			//double b[] = { 0.0, tan(local_sPoint.theta*DEGREE_TO_RADIAN), local_ePoint.y, tan(local_ePoint.theta*DEGREE_TO_RADIAN) };
			//CvMat* mat_B = cvCreateMat(4, 1, CV_64FC1);
			//CvMat* mat_result = cvCreateMat(4, 1, CV_64FC1);
			//cvSetData(mat_B, b, mat_B->step);
			//cvMatMul(mat_A_, mat_B, mat_result);
			//PrintMatrix(mat_result, 4, 1, 1);
			//if (local_ePoint.x > 0.0)
			//{
			//	for (int i = 1; i <= floor(local_ePoint.x); i++)
			//	{
			//		double Value_a = cvGet2D(mat_result, 0, 0).val[0];
			//		double Value_b = cvGet2D(mat_result, 1, 0).val[0];
			//		double Value_c = cvGet2D(mat_result, 2, 0).val[0];
			//		double Value_d = cvGet2D(mat_result, 3, 0).val[0];
			//		double y = Value_a * (double)(i*i*i) + Value_b * (double)(i*i) + Value_c * (double)(i)+Value_d;
			//		PointXY Pt = CCS2GCS(StartPoint.stPoint.dLatitude, StartPoint.stPoint.dLongitude, double(i), y);
			//		METRoadPoint tmpPt;
			//		tmpPt.stPoint.dLatitude = Pt.y;
			//		tmpPt.stPoint.dLongitude = Pt.x;
			//		tmpPt.fHeading = 3 * Value_a * (double)(i*i) + 2 * Value_b * (double)(i)+Value_c;
			//		tmpVirtualLine.list_points.push_back(tmpPt);
			//	}
			//}
			//else
			//{
			//	for (int i = -1; i > floor(local_ePoint.x); i--)
			//	{
			//		double Value_a = cvGet2D(mat_result, 0, 0).val[0];
			//		double Value_b = cvGet2D(mat_result, 1, 0).val[0];
			//		double Value_c = cvGet2D(mat_result, 2, 0).val[0];
			//		double Value_d = cvGet2D(mat_result, 3, 0).val[0];
			//		double y = Value_a * (double)(i*i*i) + Value_b * (double)(i*i) + Value_c * (double)(i)+Value_d;
			//		PointXY Pt = CCS2GCS(StartPoint.stPoint.dLatitude, StartPoint.stPoint.dLongitude, double(i), y);
			//		METRoadPoint tmpPt;
			//		tmpPt.stPoint.dLatitude = Pt.y;
			//		tmpPt.stPoint.dLongitude = Pt.x;
			//		tmpPt.fHeading = 3 * Value_a * (double)(i*i) + 2 * Value_b * (double)(i)+Value_c;
			//		tmpVirtualLine.list_points.push_back(tmpPt);
			//	}
			//}
			//tmpVirtualLine.list_points.push_back(EndPoint);
			tmpInterSection.vec_VirtualLaneLines.push_back(tmpVirtualLine);
		}

		XMLElement* pStopLineElem = pInterSectionElem->FirstChildElement("StopLine");
		XMLElement* pStopLineDataElem = pStopLineElem->FirstChildElement("Line");
		for (pStopLineDataElem; pStopLineDataElem; pStopLineDataElem = pStopLineDataElem->NextSiblingElement("Line"))
		{
			METStopLine tmpStopLine;
			pStopLineDataElem->QueryIntAttribute("InRoadId", &(tmpStopLine.nLinkedRoadID));

			XMLElement* pStopLinePointElem = pStopLineDataElem->FirstChildElement("Point");
			for (pStopLinePointElem; pStopLinePointElem; pStopLinePointElem = pStopLinePointElem->NextSiblingElement("Point"))
			{
				int iID = 0;
				pStopLinePointElem->QueryIntAttribute("Id", &iID);
				if (iID == 1)
				{
					pStopLinePointElem->QueryDoubleAttribute("Lon", &(tmpStopLine.StartPoint.dLongitude));
					pStopLinePointElem->QueryDoubleAttribute("Lat", &(tmpStopLine.StartPoint.dLatitude));
				}
				if (iID == 4)
				{
					pStopLinePointElem->QueryDoubleAttribute("Lon", &(tmpStopLine.EndPoint.dLongitude));
					pStopLinePointElem->QueryDoubleAttribute("Lat", &(tmpStopLine.EndPoint.dLatitude));
				}
			}

			tmpInterSection.vec_stoplines.push_back(tmpStopLine);
		}
		m_stMap.vec_InterSections.push_back(tmpInterSection);
	}
}

void CDrawCamera::CreateMapGraph()
{
	m_stMapGraph.InitMapGraph(m_stMap.vec_InterSections.size(), DG);
	vector<METIntersection>::iterator it = m_stMap.vec_InterSections.begin();
	int index = 0;
	for (; it != m_stMap.vec_InterSections.end(); it++)
	{
		m_stMapGraph.m_vecVerteices[index].cTypeData = "G";
		m_stMapGraph.m_vecVerteices[index].iNodeID = it->nIntersectionID;
		vector<METIntersection>::iterator s_it = it + 1;
		int NextIndex = index + 1;
		for (; s_it != m_stMap.vec_InterSections.end(); s_it++)
		{
			vector<int>::iterator OutID_it = it->vec_OutRoadID.begin();
			for (; OutID_it != it->vec_OutRoadID.end(); OutID_it++)
			{
				vector<int>::iterator InID_it = s_it->vec_InRoadID.begin();
				for (; InID_it != s_it->vec_InRoadID.end(); InID_it++)
				{
					if (*(OutID_it) == *(InID_it))
					{
						//m_stMapGraph.InsertArc(it->nIntersectionID, s_it->nIntersectionID, 0);
						m_stMapGraph.InsertArc(index, NextIndex, 0);
						break;
					}
				}
			}
			NextIndex++;
		}
		index++;
	}
	return;
}

void CDrawCamera::LoadLaneMarkTotally()
{
	fstream calibrateFile;
	char fileName[100] = { '\0' };
#ifdef ROUTE1
	sprintf_s(fileName, "LogLaneMarkLocalGPS_.txt");
#else
	sprintf_s(fileName, "LogLaneMarkLocalGPS.txt");
#endif // ROUTE1
	calibrateFile.open(fileName, ios::in);
	if (calibrateFile)
	{
		LogPoint tmp_point;
		string msg;
		double calibration_num;
		vector<double> Calibration_msg;
		while (!calibrateFile.eof())
		{
			getline(calibrateFile, msg);
			istringstream m(msg);
			while (m >> calibration_num)
			{
				Calibration_msg.push_back(calibration_num);
			}
		}
		vector<double>::iterator it = Calibration_msg.begin();
		for (; it != Calibration_msg.end(); it = it + 3)
		{
			tmp_point.x = *(it);
			tmp_point.y = *(it + 1);
			tmp_point.theta = *(it + 2);
			tmp_point.ntimestamp = 1;
			m_vecLaneMapPoints.push_back(tmp_point);
		}
		vector<double>().swap(Calibration_msg);
		calibrateFile.close();
	}
	else
	{
		m_bMapLoaded = false;
	}
}

void CDrawCamera::LoadLaneMark()
{
	fstream calibrateFile;
	char fileName[100] = { '\0' };
#ifdef ROUTE1
	sprintf_s(fileName, "LogLaneMarkLocalGPS_1_.txt");
#else
	sprintf_s(fileName, "LogLaneMarkLocalGPS_1.txt");
#endif // ROUTE1
	//sprintf_s(fileName, "LogLanelGPS_1.txt");
	calibrateFile.open(fileName, ios::in);
	if (calibrateFile)
	{
		LogPoint tmp_point;
		string msg;
		double calibration_num;
		vector<double> Calibration_msg;
		while (!calibrateFile.eof())
		{
			getline(calibrateFile, msg);
			istringstream m(msg);
			while (m >> calibration_num)
			{
				Calibration_msg.push_back(calibration_num);
			}
		}
		vector<double>::iterator it = Calibration_msg.begin();
		//for (; it != Calibration_msg.end(); it = it + 2)
		for (; it != Calibration_msg.end(); it = it + 3)
		{
			tmp_point.x = *(it);
			tmp_point.y = *(it + 1);
			tmp_point.theta = *(it + 2);
			tmp_point.ntimestamp = 1;
			m_vecLane1MapPoints.push_back(tmp_point);
		}
		vector<double>().swap(Calibration_msg);
		calibrateFile.close();
	}
	else
	{
		m_bMapSplitLoaded = false;
	}

#ifdef ROUTE1
	sprintf_s(fileName, "LogLaneMarkLocalGPS_2_.txt");
#else
	sprintf_s(fileName, "LogLaneMarkLocalGPS_2.txt");
#endif // ROUTE1
	//sprintf_s(fileName, "LogLanelGPS_2.txt");
	calibrateFile.open(fileName, ios::in);
	if (calibrateFile)
	{
		LogPoint tmp_point;
		string msg;
		double calibration_num;
		vector<double> Calibration_msg;
		while (!calibrateFile.eof())
		{
			getline(calibrateFile, msg);
			istringstream m(msg);
			while (m >> calibration_num)
			{
				Calibration_msg.push_back(calibration_num);
			}
		}
		vector<double>::iterator it = Calibration_msg.begin();
		//for (; it != Calibration_msg.end(); it = it + 2)
		for (; it != Calibration_msg.end(); it = it + 3)
		{
			tmp_point.x = *(it);
			tmp_point.y = *(it + 1);
			tmp_point.theta = *(it + 2);
			tmp_point.ntimestamp = 2;
			m_vecLane2MapPoints.push_back(tmp_point);
		}
		vector<double>().swap(Calibration_msg);
		calibrateFile.close();
	}
	else
	{
		m_bMapSplitLoaded = false;
	}

#ifdef ROUTE1
	sprintf_s(fileName, "LogLaneMarkLocalGPS_3_.txt");
#else
	sprintf_s(fileName, "LogLaneMarkLocalGPS_3.txt");
#endif // ROUTE1
	//sprintf_s(fileName, "LogLanelGPS_3.txt");
	calibrateFile.open(fileName, ios::in);
	if (calibrateFile)
	{
		LogPoint tmp_point;
		string msg;
		double calibration_num;
		vector<double> Calibration_msg;
		while (!calibrateFile.eof())
		{
			getline(calibrateFile, msg);
			istringstream m(msg);
			while (m >> calibration_num)
			{
				Calibration_msg.push_back(calibration_num);
			}
		}
		vector<double>::iterator it = Calibration_msg.begin();
		//for (; it != Calibration_msg.end(); it = it + 2)
		for (; it != Calibration_msg.end(); it = it + 3)
		{
			tmp_point.x = *(it);
			tmp_point.y = *(it + 1);
			tmp_point.theta = *(it + 2);
			tmp_point.ntimestamp = 3;
			m_vecLane3MapPoints.push_back(tmp_point);
		}
		vector<double>().swap(Calibration_msg);
		calibrateFile.close();
	}
	else
	{
		m_bMapSplitLoaded = false;
	}

#ifdef ROUTE1
	sprintf_s(fileName, "LogLaneMarkLocalGPS_4_.txt");
#else
	sprintf_s(fileName, "LogLaneMarkLocalGPS_4.txt");
#endif // ROUTE1
	//sprintf_s(fileName, "LogLanelGPS_4.txt");
	calibrateFile.open(fileName, ios::in);
	if (calibrateFile)
	{
		LogPoint tmp_point;
		string msg;
		double calibration_num;
		vector<double> Calibration_msg;
		while (!calibrateFile.eof())
		{
			getline(calibrateFile, msg);
			istringstream m(msg);
			while (m >> calibration_num)
			{
				Calibration_msg.push_back(calibration_num);
			}
		}
		vector<double>::iterator it = Calibration_msg.begin();
		//for (; it != Calibration_msg.end(); it = it + 2)
		for (; it != Calibration_msg.end(); it = it + 3)
		{
			tmp_point.x = *(it);
			tmp_point.y = *(it + 1);
			tmp_point.theta = *(it + 2);
			tmp_point.ntimestamp = 4;
			m_vecLane4MapPoints.push_back(tmp_point);
		}
		vector<double>().swap(Calibration_msg);
		calibrateFile.close();
	}
	else
	{
		m_bMapSplitLoaded = false;
	}
}

void CDrawCamera::LoadTSRInfo()
{
	fstream calibrateTSRFile;
	char fileName[100] = { '\0' };
	sprintf_s(fileName, "CalibrationSignResult_.txt");
	calibrateTSRFile.open(fileName, ios::in);
	if (calibrateTSRFile)
	{
		CalibrationTSR tmp_tsr;
		string msg;
		double calibration_num;
		vector<double> Calibration_msg;
		while (!calibrateTSRFile.eof())
		{
			getline(calibrateTSRFile, msg);
			istringstream m(msg);
			while (m >> calibration_num)
			{
				Calibration_msg.push_back(calibration_num);
			}
		}
		vector<double>::iterator it = Calibration_msg.begin();
		for (; it != Calibration_msg.end(); it = it + 7)
		{
			tmp_tsr.dPosx = *(it);
			tmp_tsr.dPosy = *(it + 1);
			tmp_tsr.fWidth = *(it + 2);
			tmp_tsr.fHeading = *(it + 5);
			tmp_tsr.fHeight = *(it + 4);
			tmp_tsr.fHeight_ = *(it + 3);//height to ground
			tmp_tsr.iColor = *(it + 6);
			m_vecMapTSR.push_back(tmp_tsr);
		}
		vector<double>().swap(Calibration_msg);
		calibrateTSRFile.close();
	}
	else
	{
		m_bMapTSRLoaded = false;
	}
}

void CDrawCamera::LoadCalibrationLanelines()
{
	//CvFileStorage* fs = cvOpenFileStorage("METMapLaneLine.xml", 0, CV_STORAGE_READ);
	//if (!fs)
	//{
	//	printf("No GPS xml file!\n");
	//}
	//else
	//{
	//	m_dInitLatitude = cvReadRealByName(fs, NULL, "Initialize_Latitude");
	//	m_dInitLongitude = cvReadRealByName(fs, NULL, "Initialize_Longitude");
	//	cvReleaseFileStorage(&fs);
	//	m_bCalLocalPos = true;
	//}
	XMLDocument* doc = new XMLDocument();
#ifdef ROUTE1
	XMLError errorID = doc->LoadFile("METMapLaneLine.xml");
#else
	XMLError errorID = doc->LoadFile("METMapLaneLine_1.xml");
#endif // ROUTE1
	if (errorID != 0)
	{
		m_bMapCalibrationLoaded = false;
	}
	XMLElement* pRootElem = doc->RootElement();
	pRootElem->QueryDoubleAttribute("VehicleWCX", &m_stTMap.stVehPos.dLatitude);
	pRootElem->QueryDoubleAttribute("VehicleWCY", &m_stTMap.stVehPos.dLongitude);
	//const XMLAttribute* pRootattribute = pRootElem->FirstAttribute();
	//while (pRootattribute)
	//{
	//	printf("name=%s,value=%s\n", pRootattribute->Name(), pRootattribute->Value());
	//	pRootattribute = pRootattribute->Next();
	//}
	XMLElement* pLaneElem = pRootElem->FirstChildElement("LaneLine");
	for (pLaneElem; pLaneElem; pLaneElem = pLaneElem->NextSiblingElement())
	{
		TLaneLine tmpLaneline;
		pLaneElem->QueryIntAttribute("Id", &(tmpLaneline.iLanelineID));
		pLaneElem->QueryIntAttribute("Type", &(tmpLaneline.iLanelineType));
		pLaneElem->QueryIntAttribute("Color", &(tmpLaneline.iLanelineColor));
		pLaneElem->QueryIntAttribute("LineSegmentNum", &(tmpLaneline.iSegNum));

		XMLElement* pSegmentElem = pLaneElem->FirstChildElement("LineSegment");
		for (pSegmentElem; pSegmentElem; pSegmentElem = pSegmentElem->NextSiblingElement())
		{
			TLineSegment tmpLineSeg;
			pSegmentElem->QueryIntAttribute("Id", &(tmpLineSeg.iSegID));
			pSegmentElem->QueryIntAttribute("PointNum", &(tmpLineSeg.iPointNum));

			XMLElement* pPointElem = pSegmentElem->FirstChildElement("Point");
			for (pPointElem; pPointElem; pPointElem = pPointElem->NextSiblingElement())
			{
				TPoint tmpPoint;
				pPointElem->QueryIntAttribute("Id", &(tmpPoint.iPointID));
				pPointElem->QueryDoubleAttribute("X", &(tmpPoint.dLatitude));
				pPointElem->QueryDoubleAttribute("Y", &(tmpPoint.dLongitude));
				tmpLineSeg.vec_Points.push_back(tmpPoint);
			}
			tmpLaneline.vec_Segments.push_back(tmpLineSeg);
		}
		m_stTMap.vec_Lanelines.push_back(tmpLaneline);
	}
}

void CDrawCamera::DecodeCameraImage(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtuImage.lock();
	m_msgImage.decode(recvBuf->data, 0, recvBuf->data_size);
	m_bRecrveImg = true;
	m_nCurrentTimestamp = m_msgImage.header.nTimeStamp;
	m_mtuImage.unlock();
}

void CDrawCamera::DecodeVehRTKInfo(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxRTK.lock();
	m_msgRTKInfo.decode(recvBuf->data, 0, recvBuf->data_size);
	m_stVehiclePos.dLatitude = m_msgRTKInfo.GGA_dwLat / 100;
	m_stVehiclePos.dLongitude = m_msgRTKInfo.GGA_dwLon / 100;
	m_stVehiclePos.dHeading = m_msgRTKInfo.TRA_dwHeading;
	m_stVehiclePos.dSpeed = m_msgRTKInfo.RMC_dwSpeedIn*0.5144f;
	m_nlastPosTimestamp = m_msgRTKInfo.header.nTimeStamp;
	if (!m_bCalLocalPos)
	{
		m_stVehiclePos.local_x = 0.0f;
		m_stVehiclePos.local_y = 0.0f;
		m_bCalLocalPos = true;
		m_dInitLatitude = m_stVehiclePos.dLatitude;
		m_dInitLongitude = m_stVehiclePos.dLongitude;
	}
	else
	{
		PointXY test = GCS2CCS(m_dInitLatitude, m_dInitLongitude, m_stVehiclePos.dLatitude, m_stVehiclePos.dLongitude);
		m_stVehiclePos.local_x = test.x;
		m_stVehiclePos.local_y = test.y;
	}
	m_mtxRTK.unlock();
}

void CDrawCamera::DecodeNextPosture(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxNextPos.lock();
	m_msgNextPosture.decode(recvBuf->data, 0, recvBuf->data_size);
	m_mtxNextPos.unlock();
}

void CDrawCamera::DecodeTSRInfo(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxtsr.lock();
	m_msgTsrInfo.decode(recvBuf->data, 0, recvBuf->data_size);
	m_mtxtsr.unlock();
}

void CDrawCamera::GLDrawCameraImage(int &width, int &height)
{
	m_mtuImage.lock();
	if (m_bRecrveImg)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////
		char *outdata = new char[m_msgImage.nLength];
		memcpy(outdata, m_msgImage.buf, m_msgImage.nLength);

		int nAdjust = 0; // 用于字节对齐
		BYTE *data = NULL;//new BYTE[bih.biWidth*bih.biHeight];
		int nComponent = 3;
		int nImageW = 1280;
		int nImageH = 720;

		// 声明解压缩对象及错误信息管理器
		struct jpeg_decompress_struct cinfo;
		struct jpeg_error_mgr jerr;

		cinfo.err = jpeg_std_error(&jerr);
		jpeg_create_decompress(&cinfo);

		// 下面代码用于解压缩，从本行开始解压缩
		jpeg_stdio_src(&cinfo, outdata, m_msgImage.nLength);
		jpeg_read_header(&cinfo, TRUE);
		delete[] data;

		data = new BYTE[(nImageW*nComponent + nAdjust)*cinfo.image_height];

		jpeg_start_decompress(&cinfo);

		JSAMPROW row_pointer[1];
		while (cinfo.output_scanline < cinfo.output_height)
		{
			row_pointer[0] = &data[(cinfo.output_height - cinfo.output_scanline - 1)*(cinfo.image_width*cinfo.num_components + nAdjust)];
			jpeg_read_scanlines(&cinfo, row_pointer, 1);
		}

		// 调整rgb顺序
		//for (int j = 0; j < nImageH; j++)
		//	for (int i = 0; i < nImageW; i++)
		//	{
		//		BYTE red = data[j*(cinfo.image_width*cinfo.num_components + nAdjust) + i * 3];
		//		data[j*(cinfo.image_width*cinfo.num_components + nAdjust) + i * 3] = data[j*(cinfo.image_width*cinfo.num_components + nAdjust) + i * 3 + 2];
		//		data[j*(cinfo.image_width*cinfo.num_components + nAdjust) + i * 3 + 2] = red;
		//	}

		jpeg_finish_decompress(&cinfo);
		jpeg_destroy_decompress(&cinfo);

		/*IplImage* objpIplImageUnCompress;
		objpIplImageUnCompress = cvCreateImage(cvSize(nImageW,nImageH), IPL_DEPTH_8U, 3);
		memcpy(objpIplImageUnCompress->imageData, data, nImageW*nImageH * 3);
		cvFlip(objpIplImageUnCompress, objpIplImageUnCompress, NULL);
		cvShowImage("Video", objpIplImageUnCompress);
		cvvWaitKey(1);*/
		memcpy(m_pImg->imageData, data, nImageW*nImageH * 3);
		cvFlip(m_pImg, m_pImg, NULL);
		//cvCvtColor(m_pImg,m_pImg,CV_BGR2RGB);
		//cvSaveImage("test.jpg", m_pImg);
		//cvUndistort2(m_pImg,m_pImg,&intrinsic_matrix,&distortion_coeffs);
		delete[] data;
		delete[] outdata;
		//////////////////////////////////////////////////////////////////////////////////////////////////
		//memcpy(m_pImg->imageData, &m_msgImage.buf, nImageW*nImageH * 3);
		//cvCvtColor(m_pImg,m_pImg,CV_BGR2RGB);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_nImageW, m_nImageH, 0, GL_RGB, GL_UNSIGNED_BYTE, m_pImg->imageData);
		width = m_nImageW;
		height = m_nImageH;
	}
	m_mtuImage.unlock();
}

void CDrawCamera::GLDrawTSRInfo(CDrawCoordinates& coordinates)
{
	m_mtxtsr.lock();
	coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
	glEnable(GL_BLEND);
	glLineWidth(2.0);
	glColor3ub(255, 255, 0);
	for (unsigned int i = 0; i < 64; i++)
	{
		if (m_msgTsrInfo.stTSRInfo[i].bActive > 0)
		{
			float SignHeightBottom = m_msgTsrInfo.stTSRInfo[i].fheight;
			float SignHeightTop = SignHeightBottom + m_msgTsrInfo.stTSRInfo[i].fHeight_;
			glBegin(GL_LINE_STRIP);
			PointXY LeftRelativePos,RightRelativePos;
			//LeftRelativePos = GCS2CCS(m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgTsrInfo.stTSRInfo[i].flx, m_msgTsrInfo.stTSRInfo[i].fly);
			//RightRelativePos = GCS2CCS(m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgTsrInfo.stTSRInfo[i].frx, m_msgTsrInfo.stTSRInfo[i].fry);

			LeftRelativePos = GCST2VEH(m_msgTsrInfo.stTSRInfo[i].flx, m_msgTsrInfo.stTSRInfo[i].fly,
				m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			RightRelativePos = GCST2VEH(m_msgTsrInfo.stTSRInfo[i].frx, m_msgTsrInfo.stTSRInfo[i].fry,
				m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			glVertex3f(LeftRelativePos.y*100.0, -LeftRelativePos.x*100.0, SignHeightBottom * 100.0);
			glVertex3f(RightRelativePos.y*100.0, -RightRelativePos.x*100.0, SignHeightBottom * 100.0);
			glVertex3f(RightRelativePos.y*100.0, -RightRelativePos.x*100.0, SignHeightTop * 100.0);
			glVertex3f(LeftRelativePos.y*100.0, -LeftRelativePos.x*100.0, SignHeightTop * 100.0);
			glVertex3f(LeftRelativePos.y*100.0, -LeftRelativePos.x*100.0, SignHeightBottom * 100.0);
			//glVertex3f(m_msgTsrInfo.stTSRInfo[i].ry*100.0, -m_msgTsrInfo.stTSRInfo[i].rx*100.0, 5 * 100.0);
			//glVertex3f(m_msgTsrInfo.stTSRInfo[i].ry*100.0, -m_msgTsrInfo.stTSRInfo[i].rx*100.0, 7 * 100.0);
			//glVertex3f(m_msgTsrInfo.stTSRInfo[i].ly*100.0, -m_msgTsrInfo.stTSRInfo[i].lx*100.0, 7 * 100.0);
			//glVertex3f(m_msgTsrInfo.stTSRInfo[i].ly*100.0, -m_msgTsrInfo.stTSRInfo[i].lx*100.0, 5 * 100.0);
			glEnd();
		}
	}
	glDisable(GL_BLEND);
	m_mtxtsr.unlock();
}

void CDrawCamera::DecodeLaneMarkPoint(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxLaneMarkPonits.lock();
	m_msgLaneMarkPointsList.decode(recvBuf->data, 0, recvBuf->data_size);
	m_bLanemarkReceived = true;
	m_mtxLaneMarkPonits.unlock();
}

void CDrawCamera::DecodeVehiclePosture(const lcm::ReceiveBuffer* recvBuf)
{
	m_mtxVehPosture.lock();
	m_msgVehiclePosture.decode(recvBuf->data, 0, recvBuf->data_size);
	if (!m_bPostureReceived)
	{
		m_bPostureReceived = true;
		m_dLastHeading = m_msgVehiclePosture.dHeading;
		m_iLastRecvPosTime = m_msgVehiclePosture.stheader.nTimeStamp;
	}
	else
	{
		if (abs(m_msgVehiclePosture.stheader.nTimeStamp - m_iLastRecvPosTime) > 1000000)
		{
			m_bPostureReceived = false;
		}
		else
		{
			double dDeltaTheta = abs(m_msgVehiclePosture.dHeading - m_dLastHeading);
			if (dDeltaTheta > 180)
			{
				dDeltaTheta = 360 - dDeltaTheta;
			}
			if (dDeltaTheta > 10)
			{
				m_msgVehiclePosture.dHeading = m_dLastHeading;
			}
			else
			{
				m_dLastHeading = m_msgVehiclePosture.dHeading;
			}
		}
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawLaneMarkPoints(CDrawCoordinates& coordinates)
{
	m_mtxLaneMarkPonits.lock();
	if (m_bLanemarkReceived)
	{
		double dHalfFov = 66.0;
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		COLOR_3UB linecolor(255, 0, 255);
		glEnable(GL_BLEND);
		glPointSize(2.0f);
		glColor4ub(linecolor.cR, linecolor.cG, linecolor.cB, 0xFF);
		glBegin(GL_POINTS);
		for (unsigned int i = 0; i < m_msgLaneMarkPointsList.num; i++)
		{
			double xa = m_msgLaneMarkPointsList.m_listLaneMarks[i].x;
			double ya = m_msgLaneMarkPointsList.m_listLaneMarks[i].y;
			if (abs(ya) < 6 && xa < (tan(dHalfFov*DEGREE_TO_RADIAN)*abs(ya) + 3))
			{
				glVertex3f(xa*100.0f, ya*100.0f, -120.0f);
			}
		}
		glEnd();
	}
	m_mtxLaneMarkPonits.unlock();
}

void CDrawCamera::GLDrawMapMarkPoints(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapLoaded && m_bPostureReceived)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		glEnable(GL_BLEND);
		glPointSize(2.0f);
		glColor4ub(153, 217, 234, 0xFF);
		glBegin(GL_POINTS);
		vector<LogPoint>::iterator it = m_vecLaneMapPoints.begin();
		for (; it != m_vecLaneMapPoints.end(); it++)
		{
			PointXY RelativePos;
			RelativePos = GCST2VEH(it->x, it->y,
				m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			double dDeltaTheta = abs(it->theta - m_msgVehiclePosture.dHeading);
			dDeltaTheta = (dDeltaTheta > 360) ? (dDeltaTheta - 360) : dDeltaTheta;
			if (Distance(RelativePos.x, RelativePos.y) < 80 && dDeltaTheta < 90)
			{
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -120.0f);
			}
		}
		glEnd();
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawMapTSRPoints(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapTSRLoaded && m_bPostureReceived)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		glEnable(GL_BLEND);
		glLineWidth(2.0);
		//glColor3ub(0, 255, 0);
		
		vector<CalibrationTSR>::iterator it = m_vecMapTSR.begin();
		for (; it != m_vecMapTSR.end(); it++)
		{
			switch (it->iColor)
			{
			case 0:
				glColor3ub(255, 255, 255);
				break;
			case 1:
				glColor3ub(255, 0, 0);
				break;
			case 2:
				glColor3ub(0, 255, 0);
				break;
			case 3:
				glColor3ub(0, 0, 255);
				break;
			default:
				glColor3ub(0, 0, 0);
				break;
			}
			PointXY RightPt = CCS2GCS(it->dPosx, it->dPosy, it->fWidth*cos(it->fHeading*DEGREE_TO_RADIAN),
				it->fWidth*sin(it->fHeading*DEGREE_TO_RADIAN));
			//PointXY tmpPoint;
			//tmpPoint = GCS2CCS(m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, it->dPosy, it->dPosx);
			//double Right_x = tmpPoint.x + it->fWidth*cos(it->fHeading*DEGREE_TO_RADIAN);
			//double Right_y = tmpPoint.y + it->fWidth*sin(it->fHeading*DEGREE_TO_RADIAN);

			float SignHeightBottom = it->fHeight_;
			float SignHeightTop = SignHeightBottom + it->fHeight;
			glBegin(GL_LINE_STRIP);
			PointXY LeftRelativePos, RightRelativePos;
			LeftRelativePos = GCST2VEH(it->dPosx, it->dPosy,m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			RightRelativePos = GCST2VEH(RightPt.y, RightPt.x,m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			glVertex3f(LeftRelativePos.y*100.0, -LeftRelativePos.x*100.0, SignHeightBottom * 100.0);
			glVertex3f(RightRelativePos.y*100.0, -RightRelativePos.x*100.0, SignHeightBottom * 100.0);
			glVertex3f(RightRelativePos.y*100.0, -RightRelativePos.x*100.0, SignHeightTop * 100.0);
			glVertex3f(LeftRelativePos.y*100.0, -LeftRelativePos.x*100.0, SignHeightTop * 100.0);
			glVertex3f(LeftRelativePos.y*100.0, -LeftRelativePos.x*100.0, SignHeightBottom * 100.0);

			//double D_theta = -m_msgVehiclePosture.dHeading*DEGREE_TO_RADIAN;
			//double Relative_x = cos(D_theta)*tmpPoint.x + sin(D_theta)*tmpPoint.y;
			//double Relative_y = -sin(D_theta)*tmpPoint.x + cos(D_theta)*tmpPoint.y;
			//m_stMapTSR.flx = Relative_x;
			//m_stMapTSR.fly = Relative_y;
			//Relative_x = cos(D_theta)*Right_x + sin(D_theta)*Right_y;
			//Relative_y = -sin(D_theta)*Right_x + cos(D_theta)*Right_y;
			//m_stMapTSR.frx = Relative_x;
			//m_stMapTSR.fry = Relative_y;
			//glBegin(GL_LINE_STRIP);
			//glVertex3f(m_stMapTSR.fly*100.0, -m_stMapTSR.flx*100.0, 5 * 100.0);//left bottom
			//glVertex3f(m_stMapTSR.fry*100.0, -m_stMapTSR.frx*100.0, 5 * 100.0);//right bottom
			//glVertex3f(m_stMapTSR.fry*100.0, -m_stMapTSR.frx*100.0, 7 * 100.0);//right top
			//glVertex3f(m_stMapTSR.fly*100.0, -m_stMapTSR.flx*100.0, 7 * 100.0);//left top
			//glVertex3f(m_stMapTSR.fly*100.0, -m_stMapTSR.flx*100.0, 5 * 100.0);
			glEnd();
		}
	}
	m_mtxVehPosture.unlock();
}

//for test
void CDrawCamera::GLDrawLane1MarkPoints(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapSplitLoaded && m_bPostureReceived)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		glEnable(GL_BLEND);
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		vector<LogPoint>::iterator it = m_vecLane1MapPoints.begin();
		for (; it != m_vecLane1MapPoints.end(); it++)
		{
			PointXY RelativePos;
			RelativePos = GCST2VEH(it->x, it->y, 
				GPGGA2WGS(m_msgVehiclePosture.dLatitude), GPGGA2WGS(m_msgVehiclePosture.dLongitude), m_msgVehiclePosture.dHeading);
			double dDeltaTheta = abs(it->theta - m_msgVehiclePosture.dHeading);
			dDeltaTheta = (dDeltaTheta > 360) ? (dDeltaTheta - 360) : dDeltaTheta;
			if (Distance(RelativePos.x, RelativePos.y) < 100 && dDeltaTheta < 90)
			{
				glColor4ub(0, 255, 255, 0xFF);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -120.0f);
			}
		}
		glEnd();
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawLane2MarkPoints(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapSplitLoaded && m_bPostureReceived)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		glEnable(GL_BLEND);
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		vector<LogPoint>::iterator it = m_vecLane2MapPoints.begin();
		for (; it != m_vecLane2MapPoints.end(); it++)
		{
			PointXY RelativePos;
			RelativePos = GCST2VEH(it->x, it->y, GPGGA2WGS(m_msgVehiclePosture.dLatitude), GPGGA2WGS(m_msgVehiclePosture.dLongitude), m_msgVehiclePosture.dHeading);
			double dDeltaTheta = abs(it->theta - m_msgVehiclePosture.dHeading);
			dDeltaTheta = (dDeltaTheta > 360) ? (dDeltaTheta - 360) : dDeltaTheta;
			if (Distance(RelativePos.x, RelativePos.y) < 100 && dDeltaTheta < 90)
			{
				glColor4ub(255, 255, 0, 0xFF);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -120.0f);
			}
		}
		glEnd();
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawLane3MarkPoints(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapSplitLoaded && m_bPostureReceived)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		glEnable(GL_BLEND);
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		vector<LogPoint>::iterator it = m_vecLane3MapPoints.begin();
		for (; it != m_vecLane3MapPoints.end(); it++)
		{
			PointXY RelativePos;
			RelativePos = GCST2VEH(it->x, it->y, GPGGA2WGS(m_msgVehiclePosture.dLatitude), GPGGA2WGS(m_msgVehiclePosture.dLongitude), m_msgVehiclePosture.dHeading);
			double dDeltaTheta = abs(it->theta - m_msgVehiclePosture.dHeading);
			dDeltaTheta = (dDeltaTheta > 360) ? (dDeltaTheta - 360) : dDeltaTheta;
			if (Distance(RelativePos.x, RelativePos.y) < 100 && dDeltaTheta < 90)
			{
				glColor4ub(255, 0, 255, 0xFF);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -120.0f);
			}
		}
		glEnd();
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawLane4MarkPoints(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapSplitLoaded && m_bPostureReceived)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		glEnable(GL_BLEND);
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		vector<LogPoint>::iterator it = m_vecLane4MapPoints.begin();
		for (; it != m_vecLane4MapPoints.end(); it++)
		{
			PointXY RelativePos;
			RelativePos = GCST2VEH(it->x, it->y, GPGGA2WGS(m_msgVehiclePosture.dLatitude), GPGGA2WGS(m_msgVehiclePosture.dLongitude), m_msgVehiclePosture.dHeading);
			double dDeltaTheta = abs(it->theta - m_msgVehiclePosture.dHeading);
			dDeltaTheta = (dDeltaTheta > 360) ? (dDeltaTheta - 360) : dDeltaTheta;
			if (Distance(RelativePos.x, RelativePos.y) < 100 && dDeltaTheta < 90)
			{
				glColor4ub(255, 255, 255, 0xFF);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -120.0f);
			}
		}
		glEnd();
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawCalibrationLaneLines(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapCalibrationLoaded && m_bPostureReceived)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		vector<TLaneLine>::iterator it = m_stTMap.vec_Lanelines.begin();
		for (; it != m_stTMap.vec_Lanelines.end(); it++)
		{
			bool dashed = false;
			bool bCrossed = false;
			COLOR_4UB color;
			switch (it->iLanelineColor)
			{
			case 5://white
				color.cR = 255;
				color.cG = 255;
				color.cB = 255;
				break;
			case 1://yellow
				color.cR = 255;
				color.cG = 255;
				color.cB = 0;
				break;
			default:
				break;
			}

			switch (it->iLanelineType)
			{
			case 2:
				dashed = true;
				break;
			case 3:
				bCrossed = true;
				break;
			default:
				break;
			}
			glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);
			glLineWidth(2.0f);
			glColor4ub(color.cR, color.cG, color.cB, 0xFF);
			if (dashed)
			{
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(8, 0xFF00);
			}
			glBegin(GL_LINE_STRIP);
			TLineSegment tmpSegment = it->vec_Segments[0];
			for (vector<TPoint>::iterator Pit = tmpSegment.vec_Points.begin(); Pit != tmpSegment.vec_Points.end(); Pit++)
			{
				PointXY RelativePos;
				RelativePos = GCST2VEH(Pit->dLatitude, Pit->dLongitude,
					m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -110.0f);
			}
			//for (vector<TLineSegment>::iterator Sit = it->vec_Segments.begin(); Sit != it->vec_Segments.end();Sit++)
			//{
			//	for (unsigned int i = 0; i < Sit->iPointNum; i++)
			//	{
			//		PointXY RelativePos;
			//		RelativePos = GCST2VEH(Sit->vec_Points[i].dLatitude, Sit->vec_Points[i].dLongitude,
			//			GPGGA2WGS(m_msgVehiclePosture.dLatitude), GPGGA2WGS(m_msgVehiclePosture.dLongitude), m_msgVehiclePosture.dHeading);
			//		glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -110.0f);
			//	}
			//}
			glEnd();
			if (dashed)
			{
				glDisable(GL_LINE_STIPPLE);
			}
			glDisable(GL_BLEND);
		}
	}
	m_mtxVehPosture.unlock();
}

double CDrawCamera::DistanceVeh2Line(METLine* line)
{
	PointXY RelativePoint_1, RelativePoint_2, InitPoint;
	InitPoint.x = 0.0;
	InitPoint.y = 0.0;
	//double dReturnDis = -0.1;
	list<METRoadPoint>::iterator it = line->list_points.begin();
	list<METRoadPoint>::iterator Nextit = line->list_points.begin();
	Nextit++;
	//for (; it != line->list_points.end(); it++)
	for (size_t i = 0; i < (line->list_points.size()-1); i++)
	{
		//RelativePoint_1 = GCST2VEH(it->stPoint.dLatitude, it->stPoint.dLongitude,
		//	m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
		RelativePoint_1 = GCS2CCS(m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, it->stPoint.dLatitude, it->stPoint.dLongitude);
		it++;
		RelativePoint_2 = GCS2CCS(m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, Nextit->stPoint.dLatitude, Nextit->stPoint.dLongitude);
		Nextit++;
		if ((m_stMapGraph.PointMulti(InitPoint, RelativePoint_2, RelativePoint_1) > 0)
			&& (m_stMapGraph.PointMulti(InitPoint, RelativePoint_1, RelativePoint_2) > 0))
		{
			if (m_stMapGraph.CrossMulti(RelativePoint_1, RelativePoint_2, InitPoint) > 0)
			{
				return 0.1;
			}
			else
			{
				return -0.1;
			}
		}
		//if (RelativePoint_1.y < 0)
		//{
		//	RelativePoint_2 = GCST2VEH(Nextit->stPoint.dLatitude, Nextit->stPoint.dLongitude,
		//		m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
		//	if (RelativePoint_2.y > 0)
		//	{
		//		dReturnDis = (RelativePoint_1.x + RelativePoint_2.x) / 2;
		//		return dReturnDis;
		//	}
		//	Nextit++;
		//}
	}
	return 0.0;
}

void CDrawCamera::GLDrawMETLine(METLine line)
{
	PointXY RelativePos;
	COLOR_4UB color;
	bool dashed = false;
	bool doubleline = false;
	int iDashedNum = -1;
	switch (line.enColor)
	{
	case UNKNOWN_COLOR:
		break;
	case WHITE:
		color.cR = 255;
		color.cG = 255;
		color.cB = 255;
		break;
	case BLUE:
		color.cR = 0;
		color.cG = 0;
		color.cB = 255;
		break;
	case GREEN:
		color.cR = 0;
		color.cG = 255;
		color.cB = 0;
		break;
	case BLACK:
		color.cR = 0;
		color.cG = 0;
		color.cB = 0;
		break;
	case YELLOW:
		color.cR = 255;
		color.cG = 255;
		color.cB = 0;
		break;
	default:
		break;
	}
	LINEType entype;
	switch (line.enType)
	{
	case UNKNOWN_LINE:
		break;
	case SINGLE_DASHED:
		dashed = true;
		break;
		//case DOUBLE_DASHED:
		//	doubleline = true;
		//	dashed = true;
		//	iDashedNum = 2;
		//	break;
	case DOUBLE_SOLID:
		doubleline = true;
		break;
	case DASHED_SOLID:
		doubleline = true;
		dashed = true;
		iDashedNum = 0;
		break;
	case SOLID_DASHED:
		doubleline = true;
		dashed = true;
		iDashedNum = 1;
		break;
	case DUMMY:
		break;
	default:
		break;
	}

	glLineWidth(2.0f);
	glColor4ub(color.cR, color.cG, color.cB, 0xFF);
	if (!doubleline)
	{
		if (dashed)
		{
			glEnable(GL_LINE_STIPPLE);
			glLineStipple(8, 0xFF00);
		}
		glBegin(GL_LINE_STRIP);
		//for (list<METRoadPoint>::iterator Pit = line.list_points.begin(); Pit != line.list_points.end(); Pit++)
		//{
		//	RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
		//		m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
		//	glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -110.0f);
		//}
		for (vector<METRoadPoint>::iterator Pit = line.vec_points.begin(); Pit != line.vec_points.end(); Pit++)
		{
			RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
				m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -110.0f);
		}
		glEnd();
		if (dashed)
		{
			glDisable(GL_LINE_STIPPLE);
		}
	}
	else
	{
		if (!dashed)
		{
			glBegin(GL_LINE_STRIP);
			for (list<METRoadPoint>::iterator Pit = line.list_points.begin(); Pit != line.list_points.end(); Pit++)
			{
				RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
					m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				glVertex3f(RelativePos.y*100.0f, (-RelativePos.x + 0.1)*100.0f, -110.0f);
			}
			glEnd();
			glBegin(GL_LINE_STRIP);
			for (list<METRoadPoint>::iterator Pit = line.list_points.begin(); Pit != line.list_points.end(); Pit++)
			{
				RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
					m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				glVertex3f(RelativePos.y*100.0f, (-RelativePos.x - 0.1)*100.0f, -110.0f);
			}
			glEnd();
		}
		else
		{
			switch (iDashedNum)
			{
			case 0:
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(8, 0xFF00);
				glBegin(GL_LINE_STRIP);
				for (list<METRoadPoint>::iterator Pit = line.list_points.begin(); Pit != line.list_points.end(); Pit++)
				{
					RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
						m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					glVertex3f(RelativePos.y*100.0f, (-RelativePos.x + 0.1)*100.0f, -110.0f);
				}
				glEnd();
				glDisable(GL_LINE_STIPPLE);
				glBegin(GL_LINE_STRIP);
				for (list<METRoadPoint>::iterator Pit = line.list_points.begin(); Pit != line.list_points.end(); Pit++)
				{
					RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
						m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					glVertex3f(RelativePos.y*100.0f, (-RelativePos.x - 0.1)*100.0f, -110.0f);
				}
				glEnd();
				break;
			case 1:
				glBegin(GL_LINE_STRIP);
				for (list<METRoadPoint>::iterator Pit = line.list_points.begin(); Pit != line.list_points.end(); Pit++)
				{
					RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
						m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					glVertex3f(RelativePos.y*100.0f, (-RelativePos.x + 0.1)*100.0f, -110.0f);
				}
				glEnd();
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(8, 0xFF00);
				glBegin(GL_LINE_STRIP);
				for (list<METRoadPoint>::iterator Pit = line.list_points.begin(); Pit != line.list_points.end(); Pit++)
				{
					RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
						m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					glVertex3f(RelativePos.y*100.0f, (-RelativePos.x - 0.1)*100.0f, -110.0f);
				}
				glEnd();
				glDisable(GL_LINE_STIPPLE);
				break;
				//case 2:
				//	glEnable(GL_LINE_STIPPLE);
				//	glLineStipple(8, 0xFF00);
				//	glBegin(GL_LINE_STRIP);
				//	for (list<METRoadPoint>::iterator Pit = Lit->list_points.begin(); Pit != Lit->list_points.end(); Pit++)
				//	{
				//		RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
				//			m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				//		glVertex3f((RelativePos.y - 0.1)*100.0f, -RelativePos.x*100.0f, -110.0f);
				//	}
				//	glEnd();
				//	glBegin(GL_LINE_STRIP);
				//	for (list<METRoadPoint>::iterator Pit = Lit->list_points.begin(); Pit != Lit->list_points.end(); Pit++)
				//	{
				//		RelativePos = GCST2VEH(Pit->stPoint.dLatitude, Pit->stPoint.dLongitude,
				//			m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				//		glVertex3f((RelativePos.y + 0.1)*100.0f, -RelativePos.x*100.0f, -110.0f);
				//	}
				//	glEnd();
				//	glDisable(GL_LINE_STIPPLE);
				//	break;
			default:
				break;
			}
		}
	}
}

void CDrawCamera::GLDrawMap(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bIsMapLoaded && m_bPostureReceived)
	{
		PointXY RelativePos;
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		vector<METRoad>::iterator it = m_stMap.vec_Roads.begin();
		for (; it != m_stMap.vec_Roads.end(); it++)
		{
			glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);
#ifdef DRAWROADBOX
			glLineWidth(3.0f);
			glColor3ub(255, 0, 0);
			glBegin(GL_LINE_STRIP);
			for (size_t i = 0; i < it->stRoadBox.iPointNum; i++)
			{
				RelativePos = GCST2VEH(it->stRoadBox.vec_EdgePoints[i].dLatitude, it->stRoadBox.vec_EdgePoints[i].dLongitude,
					m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
			}
			RelativePos = GCST2VEH(it->stRoadBox.vec_EdgePoints[0].dLatitude, it->stRoadBox.vec_EdgePoints[0].dLongitude,
				m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
			glEnd();
#endif // DRAWROADBOX
			list<METSection>::iterator Sit = it->list_sections.begin();
			for (;Sit!=it->list_sections.end();Sit++)
			{
#ifdef DRAWSECTIONBOX
				int icolor = (Sit->nSectionID % 5);
				switch (icolor)
				{
				case 0:
					glColor3ub(255, 255, 0);
					break;
				case 1:
					glColor3ub(255, 0, 255);
					break;
				case 2:
					glColor3ub(0, 255, 255);
					break;
				case 3:
					glColor3ub(100, 100, 100);
					break;
				case 4:
					glColor3ub(0, 0, 255);
					break;
				default:
					break;
				}
				glLineWidth(3.0f);
				//glColor3ub(0, 255, 0);
				glBegin(GL_LINE_STRIP);
				for (size_t i = 0; i < Sit->stSectionBox.iPointNum; i++)
				{
					RelativePos = GCST2VEH(Sit->stSectionBox.vec_EdgePoints[i].dLatitude, Sit->stSectionBox.vec_EdgePoints[i].dLongitude,
						m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
				}
				RelativePos = GCST2VEH(Sit->stSectionBox.vec_EdgePoints[0].dLatitude, Sit->stSectionBox.vec_EdgePoints[0].dLongitude,
					m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
				glEnd();
#endif // DRAWSECTIONBOX
				vector<METLine>::iterator Lit = Sit->vec_lines.begin();
				for (; Lit != Sit->vec_lines.end(); Lit++)
				{
					GLDrawMETLine(*(Lit));
					glDisable(GL_BLEND);
				}
			}
		}
		vector<METIntersection>::iterator InterSection_it = m_stMap.vec_InterSections.begin();
		for (; InterSection_it != m_stMap.vec_InterSections.end(); InterSection_it++)
		{
			PointXY RelativePos;
//draw intersection box
			glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);
			glLineWidth(3.0f);
			glColor3ub(0, 255, 0);
			glBegin(GL_LINE_STRIP);
			for (size_t i = 0; i < InterSection_it->stIntersectionBox.iPointNum; i++)
			{
				RelativePos = GCST2VEH(InterSection_it->stIntersectionBox.vec_EdgePoints[i].dLatitude,
					InterSection_it->stIntersectionBox.vec_EdgePoints[i].dLongitude, m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude,
					m_msgVehiclePosture.dHeading);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
			}
			RelativePos = GCST2VEH(InterSection_it->stIntersectionBox.vec_EdgePoints[0].dLatitude,
				InterSection_it->stIntersectionBox.vec_EdgePoints[0].dLongitude, m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude,
				m_msgVehiclePosture.dHeading);
			glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
			glEnd();
//draw virtual lines
			//glLineWidth(2.0f);
			glColor3ub(255, 0, 0);
			glPointSize(2.0f);
			vector<METVirtualLine>::iterator vlit = InterSection_it->vec_VirtualLaneLines.begin();
			for (; vlit != InterSection_it->vec_VirtualLaneLines.end(); vlit++)
			{
				glBegin(GL_POINTS); //glBegin(GL_LINE_STRIP);
				for (list<METRoadPoint>::iterator pit = vlit->list_points.begin(); pit != vlit->list_points.end(); pit++)
				{
					RelativePos = GCST2VEH(pit->stPoint.dLatitude, pit->stPoint.dLongitude, m_msgVehiclePosture.dLatitude,
						m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
				}
				glEnd();
			}
			glDisable(GL_BLEND);
		}
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawMapLanelineProcess(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapCalibrationLoaded && m_bPostureReceived && m_bMapLoaded)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		vector<TLaneLine>::iterator it = m_stTMap.vec_Lanelines.begin();
		for (; it != m_stTMap.vec_Lanelines.end(); it++)
		{
			bool dashed = false;
			bool bCrossed = false;
			COLOR_4UB color;
			switch (it->iLanelineColor)
			{
			case 5://white
				color.cR = 255;
				color.cG = 255;
				color.cB = 255;
				break;
			case 1://yellow
				color.cR = 255;
				color.cG = 255;
				color.cB = 0;
				break;
			default:
				break;
			}

			switch (it->iLanelineType)
			{
			case 2:
				dashed = true;
				break;
			case 3:
				bCrossed = true;
				break;
			default:
				break;
			}
			glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);
			glLineWidth(2.0f);
			glColor4ub(color.cR, color.cG, color.cB, 0xFF);
			if (dashed)
			{
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(4, 0xFF00);
			}
			glBegin(GL_LINE_STRIP);
			TLineSegment tmpSegment = it->vec_Segments[0];
			for (vector<TPoint>::iterator Pit = tmpSegment.vec_Points.begin(); Pit != tmpSegment.vec_Points.end(); Pit++)
			{
				PointXY RelativePos;
				RelativePos = GCST2VEH(Pit->dLatitude, Pit->dLongitude,
					m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				if (RelativePos.y < 0 /*&& abs(RelativePos.x) < 20*/)
				{
					glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -120.0f);
					PointXY RelativePosNext;
					RelativePosNext = GCST2VEH((Pit+1)->dLatitude, (Pit+1)->dLongitude,
						m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					if (RelativePosNext.y > 0 && abs(RelativePosNext.x) < 20)
					{
						double k = (RelativePosNext.x - RelativePos.x) / (RelativePosNext.y - RelativePos.y);
						double tx = RelativePos.x - k*RelativePos.y;
						glVertex3f(0.0f, -tx*100.0f, -120.0f);
						break;
					}
				}
			}
			glEnd();
			if (dashed)
			{
				glDisable(GL_LINE_STIPPLE);
			}
			glDisable(GL_BLEND);
		}

		glEnable(GL_BLEND);
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		glColor4ub(153, 217, 234, 0xFF);
		vector<LogPoint>::iterator pit = m_vecLaneMapPoints.begin();
		for (; pit != m_vecLaneMapPoints.end(); pit++)
		{
			PointXY RelativePos;
			RelativePos = GCST2VEH(pit->x, pit->y,
				m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			double dDeltaTheta = abs(pit->theta - m_msgVehiclePosture.dHeading);
			dDeltaTheta = (dDeltaTheta > 360) ? (dDeltaTheta - 360) : dDeltaTheta;
			if (Distance(RelativePos.x, RelativePos.y) < 80 && dDeltaTheta < 90 && (RelativePos.y>0))
			{
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -120.0f);
			}
		}
		glEnd();
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawMapLanelineProcessNext(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bMapCalibrationLoaded && m_bPostureReceived && m_bMapLoaded)
	{
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		vector<TLaneLine>::iterator it = m_stTMap.vec_Lanelines.begin();
		for (; it != m_stTMap.vec_Lanelines.end(); it++)
		{
			bool dashed = false;
			bool bCrossed = false;
			COLOR_4UB color;
			switch (it->iLanelineColor)
			{
			case 5://white
				color.cR = 255;
				color.cG = 255;
				color.cB = 255;
				break;
			case 1://yellow
				color.cR = 255;
				color.cG = 255;
				color.cB = 0;
				break;
			default:
				break;
			}

			switch (it->iLanelineType)
			{
			case 2:
				dashed = true;
				break;
			case 3:
				bCrossed = true;
				break;
			default:
				break;
			}
			glDisable(GL_LIGHTING);
			glEnable(GL_BLEND);
			glLineWidth(3.0f);
			glColor4ub(color.cR, color.cG, color.cB, 0xFF);
			if (dashed)
			{
				glEnable(GL_LINE_STIPPLE);
				glLineStipple(4, 0xFF00);
			}
			glBegin(GL_LINE_STRIP);
			TLineSegment tmpSegment = it->vec_Segments[0];
			for (vector<TPoint>::iterator Pit = tmpSegment.vec_Points.begin(); Pit != tmpSegment.vec_Points.end(); Pit++)
			{
				PointXY RelativePos;
				RelativePos = GCST2VEH(Pit->dLatitude, Pit->dLongitude,
					m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				if (RelativePos.y < 0 && abs(RelativePos.x) < 20)
				{
					glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -115.0f);
					PointXY RelativePosNext;
					RelativePosNext = GCST2VEH((Pit + 1)->dLatitude, (Pit + 1)->dLongitude,
						m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					if (RelativePosNext.y > 0 && abs(RelativePosNext.x) < 20)
					{
						double k = (RelativePosNext.x - RelativePos.x) / (RelativePosNext.y - RelativePos.y);
						double tx = RelativePos.x - k*RelativePos.y;
						glVertex3f(0.0f, -tx*100.0f, -115.0f);
						break;
					}
				}
			}
			glEnd();
			if (dashed)
			{
				glDisable(GL_LINE_STIPPLE);
			}
			glDisable(GL_BLEND);
		}

		glEnable(GL_BLEND);
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		glColor4ub(128, 0, 128, 0xFF);
		vector<LogPoint>::iterator pit = m_vecLaneMapPoints.begin();
		for (; pit != m_vecLaneMapPoints.end(); pit++)
		{
			PointXY RelativePos;
			RelativePos = GCST2VEH(pit->x, pit->y,
				m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
			double dDeltaTheta = abs(pit->theta - m_msgVehiclePosture.dHeading);
			dDeltaTheta = (dDeltaTheta > 360) ? (dDeltaTheta - 360) : dDeltaTheta;
			if (Distance(RelativePos.x, RelativePos.y) < 100 && dDeltaTheta < 90)
			{
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -120.0f);
			}
			//glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -125.0f);
		}
		glEnd();
	}
	m_mtxVehPosture.unlock();
}

void CDrawCamera::GLDrawLocalMap(CDrawCoordinates& coordinates)
{
	m_mtxVehPosture.lock();
	if (m_bIsMapLoaded && m_bPostureReceived)
	{
		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		PointXY RelativePos;
		coordinates.GLSwitch2Coordinates(m_msgImage.header.nTimeStamp, CFI_MOBILEYE);
		vector<METRoad>::iterator it = m_stMap.vec_Roads.begin();
		for (; it != m_stMap.vec_Roads.end(); it++)
		{
			vector<PointXY> vecRoadBoxPoints;
			PointXY tmpPt;
			tmpPt.x = 0.0; tmpPt.y = 0.0;
			for (size_t i = 0; i < it->stRoadBox.iPointNum; i++)
			{
				RelativePos = GCS2CCS(m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, it->stRoadBox.vec_EdgePoints[i].dLatitude,
					it->stRoadBox.vec_EdgePoints[i].dLongitude);
				vecRoadBoxPoints.push_back(RelativePos);
			}
			if (m_stMapGraph.IsInArea(tmpPt, vecRoadBoxPoints))
			{
#ifdef DRAWROADBOX
				glLineWidth(3.0f);
				glColor3ub(0, 250, 250);
				glBegin(GL_LINE_STRIP);
				for (size_t i = 0; i < it->stRoadBox.iPointNum; i++)
				{
					RelativePos = GCST2VEH(it->stRoadBox.vec_EdgePoints[i].dLatitude, it->stRoadBox.vec_EdgePoints[i].dLongitude,
						m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
					glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
				}
				RelativePos = GCST2VEH(it->stRoadBox.vec_EdgePoints[0].dLatitude, it->stRoadBox.vec_EdgePoints[0].dLongitude,
					m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
				glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
				glEnd();
#endif
				list<METSection>::iterator Sit = it->list_sections.begin();
				for (; Sit != it->list_sections.end(); Sit++)
				{
					vector<PointXY> vecBoxPoints;
					tmpPt.x = 0.0; tmpPt.y = 0.0;
					for (size_t i = 0; i < Sit->stSectionBox.iPointNum; i++)
					{
						RelativePos = GCS2CCS(m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, Sit->stSectionBox.vec_EdgePoints[i].dLatitude,
							Sit->stSectionBox.vec_EdgePoints[i].dLongitude);
						vecBoxPoints.push_back(RelativePos);
					}
					if (m_stMapGraph.IsInArea(tmpPt, vecBoxPoints))
					{
#ifdef DRAWSECTIONBOX
						glLineWidth(3.0f);
						glColor3ub(255, 0, 0);
						glBegin(GL_LINE_STRIP);
						for (size_t i = 0; i < Sit->stSectionBox.iPointNum; i++)
						{
							RelativePos = GCST2VEH(Sit->stSectionBox.vec_EdgePoints[i].dLatitude, Sit->stSectionBox.vec_EdgePoints[i].dLongitude,
								m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
							glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
						}
						RelativePos = GCST2VEH(Sit->stSectionBox.vec_EdgePoints[0].dLatitude, Sit->stSectionBox.vec_EdgePoints[0].dLongitude,
							m_msgVehiclePosture.dLatitude, m_msgVehiclePosture.dLongitude, m_msgVehiclePosture.dHeading);
						glVertex3f(RelativePos.y*100.0f, -RelativePos.x*100.0f, -100.0f);
						glEnd();
#endif // DRAWSECTIONBOX
						//vector<double> vecDis2line;
						double dDis2Line = -1.0;
						int iLeftID = 0;
						for (vector<METLine>::iterator Lit = Sit->vec_lines.begin(); Lit != Sit->vec_lines.end(); Lit++)
						{
							dDis2Line = DistanceVeh2Line(&(*Lit));
							if (dDis2Line < 0)
							{
								dDis2Line = DistanceVeh2Line(&(*(Lit+1)));
								if (dDis2Line > 0)
								{
									iLeftID = Lit->stKeyIndex.nEdgeNum;
									break;
								}
							}
							//vecDis2line.push_back(dDis2Line);
							//GLDrawMETLine(*(Lit));
						}
						//sort(vecDis2line.begin(), vecDis2line.end());
						for (vector<METLine>::iterator Lit = Sit->vec_lines.begin(); Lit != Sit->vec_lines.end(); Lit++)
						{
							if (iLeftID == 1)
							{
								if (Lit->stKeyIndex.nEdgeNum < 4)
								{
									GLDrawMETLine(*(Lit));
								}
							}
							else if (iLeftID >= 2)
							{
								if ((Lit->stKeyIndex.nEdgeNum <= iLeftID + 2) && (Lit->stKeyIndex.nEdgeNum >= iLeftID - 1))
								{
									GLDrawMETLine(*Lit);
								}
							}
						}
						break;
					}
				}
			}
		}
		glDisable(GL_BLEND);
	}
	m_mtxVehPosture.unlock();
}

double CDrawCamera::GPGGA2WGS(double dGpgga)
{
	double dReturn_;
	int iDegree = int(dGpgga);
	dGpgga = dGpgga - int(dGpgga);
	dReturn_ = iDegree + dGpgga * 5 / 3;
	return dReturn_;
}
